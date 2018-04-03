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
    explicit Card(uint8_t value) :
            value(value) {
#ifdef CARD_CHECKS
        if (value >= COUNT)
        throw new std::string("Invalid card value " + value);
#endif
    }

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
        return value < other.value;
    }

    bool operator==(const HandRanking& other) const {
        return value == other.value;
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
        return static_cast<Ranking>(value >> RANKING_SHIFT);
    }

private:
    friend class CardSet;

    constexpr static int RANKING_SHIFT = 2 * 28;
    constexpr static int HEIGHT_SHIFT = 28;

    HandRanking(Ranking ranking, uint32_t height, uint32_t side_cards) {
        value = (static_cast<uint64_t>(ranking) << RANKING_SHIFT)
                | (static_cast<uint64_t>(height) << HEIGHT_SHIFT) | side_cards;
    }

    uint64_t value;
};

class CardSet {
public:
    static CardSet fullDeck() {
        CardVec cv;
        cv.v = _mm_set1_epi32(0xd5555554);
        return CardSet(cv);
    }

    CardSet() {
        cv.v = _mm_setzero_si128();
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
        __m128i count = _mm_srli_epi32(cv.v, 28);
        count = _mm_hadd_epi32(count, count);
        count = _mm_hadd_epi32(count, count);
        return _mm_cvtsi128_si32(count);
    }

    bool contains(Card c) const {
        CardVec v = toCardVec(c);
        __m128i mask = _mm_and_si128(v.v, cardMask());
        return !all_zeros(cv.v, mask);
    }

    void add(Card c) {
#ifdef CARD_CHECKS
        if (contains(c)) {
            throw new std::runtime_error(
                    "Card already contained!" + c.toString());
        }
#endif
        CardVec cv = toCardVec(c);
        this->cv.v = _mm_add_epi32(cv.v, this->cv.v);
    }

    void remove(Card c) {
#ifdef CARD_CHECKS
        if (!contains(c)) {
            throw new std::runtime_error("Card not contained!" + c.toString());
        }
#endif
        CardVec cv = toCardVec(c);
        this->cv.v = _mm_sub_epi32(cv.v, this->cv.v);
    }

    void addAll(const CardSet& cs) {
#ifdef CARD_CHECKS
        __m128i mask = _mm_and_si128(cs.cv.v, cardMask());
        if (!all_zeros(this->cv.v, mask)) {
            throw new std::runtime_error("CardSets are not disjoint!");
        }
#endif
        this->cv.v = _mm_add_epi32(cs.cv.v, this->cv.v);
    }

    HandRanking rankTexasHoldem() const;

    std::vector<Card> toCardVector() const;

private:
    union CardVec {
        uint32_t cards[4] = { 0, 0, 0, 0 };
        __m128i v;
    };

    class Table {
    public:
        Table();
        CardVec operator[](uint8_t idx) {
            return cv[idx];
        }
    private:
        CardVec cv[64];
    };

    static bool all_zeros(__m128i v) {
#ifdef __SSE4_1__
        return _mm_testz_si128(v, v);
#endif
        return _mm_movemask_epi8(_mm_cmpeq_epi32(v, _mm_setzero_si128()))
                == 0xffff;
    }

    static bool all_zeros(__m128i v, __m128i mask) {
#ifdef __SSE4_1__
        return _mm_testz_si128(v, mask);
#endif
        return all_zeros(_mm_and_si128(v, mask));
    }

    static Table card_table;

    static CardVec toCardVec(Card c) {
#ifdef NO_CARD_TABLE
        return internalToCardVec(c);
#else
        return card_table[c.getValue()];
#endif
    }

    static CardVec internalToCardVec(Card c) {
        CardVec cv;
        cv.v = _mm_setzero_si128();
        uint32_t shift = 26 - static_cast<uint32_t>(c.getRank()) * 2;
        cv.cards[static_cast<uint32_t>(c.getColor())] = (1 << 28)
                | ((1 << 28) >> shift);
        return cv;
    }

    static __m128i cardMask() {
        return _mm_set1_epi32((1 << 28) - 1);
    }

    CardSet(const CardVec& cv) :
            cv(cv) {
    }

    CardVec cv;
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
