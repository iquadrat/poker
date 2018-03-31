#include "CardSet.h"

#include <iostream>

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
    case Rank::_10:
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
    std::vector<Card> result;
    for (uint32_t color = 0; color < 4; ++color) {
        for (uint32_t rank = 0; rank < 13; ++rank) {
            if ((cv.cards[color] & (4 << (rank * 2))) != 0) {
                result.push_back(
                        Card(static_cast<Rank>(rank),
                                static_cast<Color>(color)));
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

uint32_t highest_bit_index(uint32_t v) {
    return 31 - __builtin_clz(v);
}

uint32_t highest_bit(uint32_t v) {
    return 1 << highest_bit_index(v);
}

uint32_t lowest_bit(uint32_t v) {
    return 1 << __builtin_ctz(v);
}

uint32_t highest_two_bits(uint32_t v) {
    uint32_t r = highest_bit(v);
    return r | highest_bit(v ^ r);
}

uint32_t lowest_two_bits(uint32_t v) {
    uint32_t r = lowest_bit(v);
    return r | lowest_bit(v^r);
}

template<typename F>
inline __m128i combine4(__m128i v, F f) {
    __m128i r = f(v, _mm_shuffle_epi32(v, _MM_SHUFFLE(2,3,0,1)));
    return f(r, _mm_shuffle_epi32(r, _MM_SHUFFLE(1,0,3,2)));
}

inline __m128i and4(__m128i v) {
    return combine4(v, [](__m128i a, __m128i b) {return _mm_and_si128(a,b);});
}

inline __m128i vand(__m128i a, __m128i b) {
    return _mm_and_si128(a, b);
}
inline __m128i vor(__m128i a, __m128i b) {
    return _mm_or_si128(a, b);
}
inline __m128i vadd(__m128i a, __m128i b) {
    return _mm_add_epi32(a, b);
}

uint32_t get_straight(uint32_t cards) {
    // Copy ace bit to lowest position.
    uint32_t dup = cards | (cards >> 26);
    uint32_t straight = cards & (cards << 2);
    straight = straight & (straight << 4);
    straight = straight & (dup << 8);
    return straight;
}

} // namespace

HandRanking CardSet::rankTexasHoldem() const {
#ifdef CARD_CHECKS
    if (size() != 7) {
        throw new std::runtime_error("Invalid CardSet size: " + size());
    }
#endif
    // Check for four of a kind:
    __m128i poker = combine4(cv.v, vand);
    if (unlikely(!_mm_test_all_zeros(poker, poker))) {
        // Congratulations! You have a four of a kind!
        // Note that this makes straight flush impossible at the same time.
        // Now need the highest card not part of the poker as side card.
        __m128i merged = combine4(cv.v, vor);
        uint32_t poker_bit = _mm_extract_epi32(poker, 0);
        uint32_t side_cards = _mm_extract_epi32(merged, 0) ^ poker_bit;
        return HandRanking(HandRanking::FOUR_OF_A_KIND, poker_bit,
                highest_bit_index(side_cards));
    }

    uint32_t sum = _mm_extract_epi32(combine4(cv.v, vadd), 0);
    uint32_t two_of_a_kind = sum & 0xaaaaaaa;
    uint32_t three_of_a_kind = (sum << 1) & two_of_a_kind;
    uint32_t pairs = _mm_popcnt_u32(two_of_a_kind);

    HandRanking ranking;

    if (unlikely(three_of_a_kind != 0)) {
        // We could have two three-of-a-kind. Only keep the highest one.
        three_of_a_kind = highest_bit(three_of_a_kind);
        two_of_a_kind ^= three_of_a_kind;
        if (two_of_a_kind != 0) {
            // Full house!
            // Three could still be multiple two-of-a-kind. Keep highest only.
            return HandRanking(HandRanking::FULL_HOUSE, three_of_a_kind,
                    highest_bit_index(two_of_a_kind));
        }
        uint32_t side_cards = highest_two_bits(sum);
        ranking = HandRanking(HandRanking::THREE_OF_A_KIND, three_of_a_kind,
                side_cards);
    } else if (pairs == 0) {
        // Initialize with high card:
        uint32_t side_cards = sum ^ lowest_two_bits(sum);
        ranking = HandRanking(HandRanking::HIGH_CARD, 0, side_cards);
    } else if (pairs == 1) {
        uint32_t side_cards = sum ^ lowest_two_bits(sum);
        ranking = HandRanking(HandRanking::ONE_PAIR, two_of_a_kind,
                side_cards);
    } else if (pairs == 2) {
        // Kicker is highest card not part of any pairs.
        uint32_t kicker = highest_bit(sum ^ two_of_a_kind);
        ranking = HandRanking(HandRanking::TWO_PAIRS, two_of_a_kind,
                kicker);
    } else {
        // 3 pairs, only keep highest two.
        uint32_t tok3 = lowest_bit(two_of_a_kind);
        // Kicker is highest card not part of any pairs or one of the lowest pair cards.
        uint32_t kicker = highest_bit(sum ^ two_of_a_kind ^ (tok3 >> 1));
        ranking = HandRanking(HandRanking::TWO_PAIRS, two_of_a_kind ^ tok3,
                        kicker);
    }

    uint32_t colorless = _mm_extract_epi32(combine4(cv.v, vor), 0);
    uint32_t straight = get_straight(colorless);
    if (unlikely(straight != 0)) {
        ranking = HandRanking(HandRanking::STRAIGHT, 0, highest_bit_index(straight));
    }

    // TODO merge flush and flush_cards to single int? (more efficient cmov)
    // TODO use parallel popcnt?
    // TODO store count in higher bits?
    int32_t flush = -1;
    int32_t flush_card_count = 0;
    for (int i = 0; i < 4; ++i) {
        int count = _mm_popcnt_u32(cv.cards[i]);
        if (count >= 5) {
            flush = i;
            flush_card_count = count;
        }
    }
    if (unlikely(flush != -1)) {
        uint32_t flush_cards = cv.cards[flush];
        uint32_t straight_flush = get_straight(flush_cards);
        if (unlikely(straight_flush != 0)) {
            return HandRanking(HandRanking::STRAIGHT_FLUSH, 0, highest_bit_index(straight));
        }

        if (unlikely(flush_card_count == 6)) {
          flush_cards ^= lowest_bit(flush_cards);
        } else if (unlikely(flush_card_count == 7)) {
          flush_cards ^= lowest_two_bits(flush_cards);
        }

        return HandRanking(HandRanking::FLUSH, 0, flush_cards);
    }

    return ranking;
}

} /* namespace poker */
