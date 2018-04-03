#ifndef CARDSET_H_
#define CARDSET_H_

#include "SFMT.h"

#include <string>
#include <tuple>
#include <vector>
#include <ostream>
#include <functional>

#include <stdint.h>

#include <emmintrin.h>
#include <nmmintrin.h>

namespace poker {

inline bool all_zeros(__m128i v) {
#ifdef __SSE4_1__
    return _mm_testz_si128(v, v);
#endif
    return _mm_movemask_epi8(_mm_cmpeq_epi32(v, _mm_setzero_si128()))
            == 0xffff;
}

inline bool all_zeros(__m128i v, __m128i mask) {
#ifdef __SSE4_1__
    return _mm_testz_si128(v, mask);
#endif
    return all_zeros(_mm_and_si128(v, mask));
}

enum class Color {
    CLUBS = 0, DIAMONDS = 1, HEARTS = 2, SPADES = 3,
};

std::string toString(Color color);

enum class Rank {
    _2 = 0,
    _3 = 1,
    _4 = 2,
    _5 = 3,
    _6 = 4,
    _7 = 5,
    _8 = 6,
    _9 = 7,
    _T = 8,
    J = 9,
    Q = 10,
    K = 11,
    A = 12,
};

std::string toString(Rank rank);

class Card {
    constexpr static uint8_t COLOR_MULT = 16;
public:
    constexpr static uint8_t COUNT = 13 * 4;

    constexpr Card(Rank rank, Color color) :
            value(static_cast<int>(rank) + COLOR_MULT * static_cast<int>(color)) {
    }

    /*    explicit Card(uint8_t value) :
     value(value) {
     #ifdef CARD_CHECKS
     if (value >= COUNT)
     throw new std::string("Invalid card value " + value);
     #endif
     }*/

    Card(const Card&) = default;
    Card& operator=(const Card&) = default;
    bool operator==(const Card& o) const {
        return o.value == value;
    }

    uint8_t getValue() const {
        return value;
    }

    Color getColor() const {
        return static_cast<Color>(value / COLOR_MULT);
    }

    Rank getRank() const {
        return static_cast<Rank>(value % COLOR_MULT);
    }

    std::tuple<Rank, Color> getRankColor() const {
        return std::make_tuple(getRank(), getColor());
    }

    std::string toString() const;

    ::std::ostream& operator<<(::std::ostream& os) const {
        os << toString();
        return os;
    }

private:
    explicit Card(uint8_t value) : value(value) {}

    friend class FastDeck;

    const uint8_t value;
};

inline void PrintTo(const Card &c, ::std::ostream* os) {
    (*os) << c.toString();
}

class HandRanking {
public:
    enum Ranking {
        HIGH_CARD = 0,
        ONE_PAIR = 1,
        TWO_PAIRS = 2,
        THREE_OF_A_KIND = 3,
        STRAIGHT = 4,
        FLUSH = 5,
        FULL_HOUSE = 6,
        FOUR_OF_A_KIND = 7,
        STRAIGHT_FLUSH = 8,
    };

    HandRanking() = default;

    bool operator<(const HandRanking& other) const {
        __m128i eq = _mm_cmpeq_epi64(other.value, value);
        __m128i lt = _mm_cmpgt_epi64(other.value, value);

        __m128i unpack = _mm_unpacklo_epi64(lt, eq);
        return !all_zeros(lt, unpack);

/*        if (value_hi == other.value_hi) {
            return value_lo < other.value_lo;
        }
        return value_hi < other.value_hi;*/
    }

    bool operator==(const HandRanking& other) const {
        return all_zeros(_mm_xor_si128(value, other.value));
        //return (value_hi == other.value_hi) && (value_lo == other.value_lo);
    }

    friend bool operator<=(const HandRanking & a, const HandRanking & b) {
        return a < b || a == b;
    }
    friend bool operator>(const HandRanking & a, const HandRanking & b) {
        return !(a <= b);
    }
    friend bool operator!=(const HandRanking & a, const HandRanking & b) {
        return !(a == b);
    }
    friend bool operator>=(const HandRanking & a, const HandRanking & b) {
        return !(a < b);
    }

    Ranking getRanking() const {
        uint64_t bits = _mm_cvtsi128_si64x(value);
        return static_cast<Ranking>(bits >> RANKING_SHIFT);
    }

private:
    friend class CardSet;

    constexpr static int RANKING_SHIFT = 59;

    HandRanking(uint64_t value_hi): HandRanking(value_hi, 0) {}

    HandRanking(uint64_t value_hi, uint64_t value_lo): value(_mm_set_epi64x(value_lo, value_hi)) {}

    static HandRanking create(Ranking ranking, uint64_t height, uint64_t side_cards);
    static HandRanking with18bitHeight(Ranking ranking, uint32_t height, uint64_t side_cards);
    static HandRanking with42bitHeight(Ranking ranking, uint64_t height, uint32_t side_cards);
    static HandRanking with60bitHeight(Ranking ranking, uint64_t height);

    /*uint64_t value_hi;
    uint64_t value_lo;*/
    __m128i value;
};

class CardSet {
public:
    static CardSet fullDeck() {
        return _mm_set_epi64x(0x0d0d0d0d3fffffff, 0xfffffe4924924924);
    }

    CardSet() {
        cv = _mm_setzero_si128();
    }

    template<typename C>
    CardSet(const C& cards) :
            CardSet() {
        for (const Card& card : cards) {
            add(card);
        }
    }

    CardSet(const std::initializer_list<Card>& cards) :
            CardSet() {
        for (const Card& card : cards) {
            add(card);
        }
    }

    uint32_t size() const {
        uint64_t sum_bits = color_cnts();
        return ((sum_bits) & 0xff) +
               ((sum_bits >> 8) & 0xff) +
               ((sum_bits >> 16) & 0xff) +
               ((sum_bits >> 24) & 0xff);
    }

    bool contains(Card c) const {
        uint32_t rank = static_cast<uint32_t>(c.getRank());
        uint32_t color = static_cast<uint32_t>(c.getColor());
        uint64_t card_bits = _mm_cvtsi128_si64x(_mm_srli_si128(cv, 5));
        uint64_t bit = 13 * color + rank + 2;
        return (card_bits & (static_cast<uint64_t>(1) << bit)) != 0;
    }

    void add(Card c) {
#ifdef CARD_CHECKS
        if (contains(c)) {
            throw new std::runtime_error(
                    "Card already contained!" + c.toString());
        }
#endif
        __m128i cv = toCardVec(c);
        this->cv = _mm_add_epi64(cv, this->cv);
    }

    void remove(Card c) {
#ifdef CARD_CHECKS
        if (!contains(c)) {
            throw new std::runtime_error("Card not contained!" + c.toString());
        }
#endif
        __m128i cv = toCardVec(c);
        this->cv = _mm_sub_epi64(cv, this->cv);
    }

    void addAll(const CardSet& cs) {
#ifdef CARD_CHECKS
        __m128i mask = _mm_and_si128(cs.cv, cardMask());
        if (!all_zeros(this->cv, mask)) {
            throw new std::runtime_error("CardSets are not disjoint!");
        }
#endif
        this->cv = _mm_add_epi64(cs.cv, this->cv);
    }

    HandRanking rankTexasHoldem() const;

    std::vector<Card> toCardVector() const;

private:
    class Table {
    public:
        Table();
        __m128i operator[](uint8_t idx) {
            return cv[idx];
        }
    private:
        __m128i cv[64];
    };

    uint32_t color_cnts() const {
#ifdef __SSE4_1__
        return _mm_extract_epi32(cv, 3);
#else
        return _mm_cvtsi128_si64x(_mm_shuffle_epi32(cv, -1));
#endif
    }

    static Table card_table;

    static __m128i toCardVec(Card c) {
#ifdef NO_CARD_TABLE
        return internalToCardVec(c);
#else
        return card_table[c.getValue()];
#endif
    }

    static __m128i internalToCardVec(Card c) {
        constexpr uint64_t one = 1;
        uint32_t rank = static_cast<uint32_t>(c.getRank());
        uint32_t color = static_cast<uint32_t>(c.getColor());
        __m128i card_bits = _mm_set_epi64x(0, one << (13 * color + rank + 2));
        __m128i card_cnts = _mm_set_epi64x(0, one << (3 * (rank + 1)));
        __m128i color_cnts = _mm_set_epi64x(0, one << (8 * color));
        return _mm_or_si128(card_cnts,
                  _mm_or_si128(_mm_slli_si128(card_bits, 5),
                               _mm_slli_si128(color_cnts, 12)));
    }

    static __m128i cardMask() {
        return _mm_set_epi64x(0x000000003fffffff, 0xfffffc0000000000);
    }

    CardSet(__m128i cv) :
            cv(cv) {
    }

    __m128i cv;
};

class FastDeck {
public:
    FastDeck();

    void shuffle() {
        remaining = 52;
    }

    Card deal() {
#ifdef CARD_CHECKS
        if (remaining == 0) {
            throw new std::runtime_error("No remaining cards!");
        }
#endif
        // Note: This has a slight bias towards lower indices.
        uint32_t random = sfmt_genrand_uint32(&sfmt);
        uint32_t index = (static_cast<uint64_t>(random) * remaining) >> 32;
        uint32_t card = cards[index];
        remaining--;
        std::swap(cards[remaining], cards[index]);
        return Card(card);
    }

private:
    uint8_t cards[64];
    int32_t remaining = 0;
    sfmt_t sfmt;
};

}
/* namespace poker */

#endif /* CARDSET_H_ */
