#include "CardSet.h"
#include "AllCards.h"

#include <iostream>
#include <string.h>

namespace poker {

std::string toString(Color color) {
    switch (color) {
    case Color::CLUBS:
        return "C";
    case Color::DIAMONDS:
        return "D";
    case Color::HEARTS:
        return "H";
    case Color::SPADES:
        return "S";
    default:
        return "?";
    }
}

std::string toString(Rank rank) {
    switch (rank) {
    case Rank::_2:
        return "2";
    case Rank::_3:
        return "3";
    case Rank::_4:
        return "4";
    case Rank::_5:
        return "5";
    case Rank::_6:
        return "6";
    case Rank::_7:
        return "7";
    case Rank::_8:
        return "8";
    case Rank::_9:
        return "9";
    case Rank::_T:
        return "T";
    case Rank::J:
        return "J";
    case Rank::Q:
        return "Q";
    case Rank::K:
        return "K";
    case Rank::A:
        return "A";
    default:
        return "?";
    }
}

std::string Card::toString() const {
    std::tuple<Rank, Color> rank_color = getRankColor();
    return ::poker::toString(std::get<0>(rank_color))
            + ::poker::toString(std::get<1>(rank_color));
}

std::vector<Card> CardSet::toCardVector() const {
    // TODO this could be optimized more
    std::vector<Card> result;
    for (uint8_t c = 0; c < 4; ++c) {
        for (uint8_t r = 0; r < 13; ++r) {
            Card card(static_cast<Rank>(r), static_cast<Color>(c));
            if (contains(card)) {
                result.push_back(card);
            }
        }
    }
    return result;
}

namespace {

template<typename T>
T unlikely(T t) {
    return __builtin_expect(t, 0);
}

template<typename T>
T likely(T t) {
    return __builtin_expect(t, 1);
}

bool multiple_bits_set(uint64_t v) {
    return v & (v - 1);
}

uint64_t lowest_bit(uint64_t v) {
    return v & (-v);
}

template<typename T>
T erase_lowest_bit(T v) {
    return v & (v - 1);
}

uint64_t erase_lowest_two_bits(uint64_t v) {
    v &= (v - 1);
    v &= (v - 1);
    return v;
}

uint32_t highest_bit_ranking(uint64_t v) {
    return -__builtin_clzll(v);
}

uint32_t trailing_zeros32(uint32_t v) {
    return __builtin_ctz(v);
}

#if CARD_CHECKS
bool has_upper_bit_set(uint64_t v, uint32_t lower_bit_count) {
    return (v >> lower_bit_count) != 0;
}
#endif

}
 // namespace

HandRanking HandRanking::create(Ranking ranking, uint64_t height,
    uint64_t side_cards) {
#if CARD_CHECKS
if (has_upper_bit_set(height, 42)) {
    throw new std::runtime_error("Invalid height");
}
#endif
return HandRanking((static_cast<uint64_t>(ranking) << RANKING_SHIFT) | height,
        side_cards);
}

HandRanking HandRanking::with18bitHeight(Ranking ranking, uint32_t height,
    uint64_t side_cards) {
#if CARD_CHECKS
if (has_upper_bit_set(height, 18)) {
    throw new std::runtime_error("Invalid height");
}
if (has_upper_bit_set(side_cards, 42)) {
    throw new std::runtime_error("Invalid side_cards");
}
#endif
return HandRanking(
        (static_cast<uint64_t>(ranking) << RANKING_SHIFT)
                | (static_cast<uint64_t>(height) << 42) | side_cards);
}

HandRanking HandRanking::with42bitHeight(Ranking ranking, uint64_t height,
    uint32_t side_cards) {
#if CARD_CHECKS
if (has_upper_bit_set(height, 42)) {
    throw new std::runtime_error("Invalid height");
}
if (has_upper_bit_set(side_cards, 18)) {
    throw new std::runtime_error("Invalid side_cards");
}
#endif
return HandRanking(
        (static_cast<uint64_t>(ranking) << RANKING_SHIFT)
                | (static_cast<uint64_t>(height) << 18) | side_cards);
}

HandRanking HandRanking::with60bitHeight(Ranking ranking, uint64_t height) {
#if CARD_CHECKS
if (has_upper_bit_set(height, 60)) {
    throw new std::runtime_error("Invalid height");
}
#endif
return HandRanking((static_cast<uint64_t>(ranking) << RANKING_SHIFT) | height);
}

HandRanking CardSet::rankTexasHoldem() const {
#ifdef CARD_CHECKS
  if (size() != 7) {
      throw new std::runtime_error("Invalid CardSet size: " + size());
  }
#endif
    __m128i flush = _mm_cmpgt_epi8(cv, _mm_set1_epi8(4));
    if (unlikely(!all_zeros(flush, _mm_set_epi32(-1, 0, 0, 0)))) {
        uint32_t color = trailing_zeros32(_mm_movemask_epi8(flush) >> 12);
        uint32_t flush_cards = (_mm_cvtsi128_si64x(_mm_srli_si128(cv, 5)) >> (color * 13)) & 0x7ffc;
        uint32_t flush_cards_dup = flush_cards | (flush_cards >> 13);

        uint32_t straight_flush = flush_cards & (flush_cards_dup << 1);
        straight_flush &= (straight_flush << 2);
        straight_flush &= (flush_cards_dup << 4);
        if (unlikely(straight_flush != 0)) {
            return HandRanking::with60bitHeight(HandRanking::STRAIGHT_FLUSH,
                    highest_bit_ranking(straight_flush));
        }
        uint32_t flush_card_count = (color_cnts() >> (8 * color)) & 0xff;
        //uint32_t flush_card_count = _mm_popcnt_u32(flush_cards);
        if (flush_card_count > 5) {
            flush_cards = erase_lowest_bit(flush_cards);
        }
        if (flush_card_count > 6) {
            flush_cards = erase_lowest_bit(flush_cards);
        }
        return HandRanking::with60bitHeight(HandRanking::FLUSH, flush_cards);
    }

    uint64_t sum_bits = _mm_cvtsi128_si64(cv);
    uint64_t one_of_a_kind = (sum_bits << 2) & 044444444444444;
    uint64_t two_of_a_kind = (sum_bits << 1) & 044444444444444;
    uint64_t colorless = one_of_a_kind | two_of_a_kind;

    // Check for four of a kind:
    uint64_t four_of_a_kind = sum_bits & 044444444444444;
    if (unlikely(four_of_a_kind != 0)) {
        // Congratulations! You have a four of a kind!
        // Note that this makes straight flush impossible at the same time.
        // Now need the highest card not part of the poker as side card.
        return HandRanking::create(HandRanking::FOUR_OF_A_KIND, four_of_a_kind,
                highest_bit_ranking(colorless));
    }

    // Straight:
    uint64_t straight_bits = colorless | (colorless >> 39);
    uint64_t straight = colorless & (straight_bits << 3);
    straight = straight & (straight << 6);
    straight = straight & (straight_bits << 12);
    if (unlikely(straight != 0)) {
        return HandRanking::with60bitHeight(HandRanking::STRAIGHT,
                highest_bit_ranking(straight));
    }

    // Three of a kind:
    uint64_t three_of_a_kind = one_of_a_kind & two_of_a_kind;
    if (unlikely(three_of_a_kind != 0)) {
        two_of_a_kind ^= three_of_a_kind;
        if (multiple_bits_set(three_of_a_kind)) {
            // Two three-of-a-kind. The lower one is our pair for the full house.
            two_of_a_kind = lowest_bit(three_of_a_kind);
            three_of_a_kind ^= two_of_a_kind;
        }
        if (two_of_a_kind != 0) {
            // Full house!
            // There could still be multiple two-of-a-kind. Keep highest only.
            return HandRanking::create(HandRanking::FULL_HOUSE, three_of_a_kind,
                    highest_bit_ranking(two_of_a_kind));
        }
        uint64_t side_cards = erase_lowest_two_bits(colorless ^ three_of_a_kind);
        return HandRanking::create(HandRanking::THREE_OF_A_KIND, three_of_a_kind,
                side_cards);
    }

#ifdef __POPCNT__
    uint32_t pairs = _mm_popcnt_u64(two_of_a_kind);
    bool has_three_pairs = (pairs == 3);
#else
    // Emulate popcnt for 0-2 bits:
    uint64_t remaining_pairs = two_of_a_kind;
    uint32_t pairs = (remaining_pairs == 0) ? 0 : 1;
    remaining_pairs = erase_lowest_bit(remaining_pairs);
    pairs += (remaining_pairs == 0) ? 0 : 1;
    remaining_pairs = erase_lowest_bit(remaining_pairs);
    bool has_three_pairs = (remaining_pairs != 0);
#endif
    if (unlikely(has_three_pairs)) {
        // Three pairs, only keep highest two.
        uint64_t tok3 = lowest_bit(two_of_a_kind);
        // Kicker is either highest card not part of any pairs or one of the lowest pair cards.
        uint64_t side_cards = std::max(colorless ^ two_of_a_kind, tok3);
        return HandRanking::create(HandRanking::TWO_PAIRS, two_of_a_kind ^ tok3,
                side_cards);
    }

    // Zero to two pairs. Kicker are those cards that remain after removing the pairs and the lowest two cards.
    uint64_t side_cards = erase_lowest_two_bits(colorless ^ two_of_a_kind);
    return HandRanking::create(static_cast<HandRanking::Ranking>(pairs),
            two_of_a_kind, side_cards);
}

CardSet::Table::Table() {
    for (uint8_t c = 0; c < 4; ++c) {
        for (uint8_t r = 0; r < 13; ++r) {
            Card card(static_cast<Rank>(r), static_cast<Color>(c));
            cv[card.getValue()] = internalToCardVec(card);
        }
    }
}

CardSet::Table CardSet::card_table;

FastDeck::FastDeck() {
sfmt_init_gen_rand(&sfmt, 12345);
__m128i* cv= reinterpret_cast<__m128i*>(cards);
cv[0] = _mm_setr_epi8(_2C.value, _3C.value, _4C.value, _5C.value, _6C.value,
        _7C.value, _8C.value, _9C.value, _TC.value, _JC.value, _QC.value,
        _KC.value, _AC.value, _2D.value, _3D.value, _4D.value);
cv[1] = _mm_setr_epi8(_5D.value, _6D.value, _7D.value, _8D.value, _9D.value,
        _TD.value, _JD.value, _QD.value, _KD.value, _AD.value, _2H.value,
        _3H.value, _4H.value, _5H.value, _6H.value, _7H.value);
cv[2] = _mm_setr_epi8(_8H.value, _9H.value, _TH.value, _JH.value, _QH.value,
        _KH.value, _AH.value, _2S.value, _3S.value, _4S.value, _5S.value,
        _6S.value, _7S.value, _8S.value, _9S.value, _TS.value);
cv[3] = _mm_setr_epi8(_JS.value, _QS.value, _KS.value, _AS.value, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0);
}

} /* namespace poker */
