#ifndef CARDSET_H_
#define CARDSET_H_

#include <string>
#include <tuple>
#include <vector>
#include <ostream>
#include <random>

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
    _10 = 8,
    J = 9,
    Q = 10,
    K = 11,
    A = 12,
};

std::string toString(Rank rank);

class Card {

public:
    constexpr static uint8_t COUNT = 13 * 4;

    Card(Rank rank, Color color) :
            Card(static_cast<int>(rank) + 13 * static_cast<int>(color)) {
    }

    explicit Card(uint8_t value) :
            value(value) {
#ifdef CARD_CHECKS
        if (value >= COUNT)
            throw new std::string("Invalid card value " + value);
#endif
    }

    Card(const Card&) = default;
    Card& operator=(const Card&) = default;
    bool operator==(const Card& o) const {
        return o.value == value;
    }

    Color getColor() const {
        return static_cast<Color>(value / 13);
    }

    Rank getRank() const {
        return static_cast<Rank>(value % 13);
    }

    std::tuple<Rank, Color> getRankColor() const {
        return std::make_tuple(getRank(), getColor());
    }

    std::string toString() const;

    ::std::ostream& operator<<(::std::ostream& os) {
        os << toString();
        return os;
    }

private:
    uint8_t value;
};

static void PrintTo(const Card &c, ::std::ostream* os) {
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

    HandRanking() = default;

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
        for (int i = 0; i < 4; ++i) {
            cv.cards[i] = 0x5555554;
        }
        return CardSet(cv);
    }

    CardSet() = default;

    template<typename C>
    CardSet(const C& cards) {
        for (const Card& card : cards) {
            add(card);
        }
    }

    CardSet(const std::initializer_list<Card>& cards) {
        for (const Card& card : cards) {
            add(card);
        }
    }

    uint32_t size() const {
        const uint64_t* c = reinterpret_cast<const uint64_t*>(&cv.cards[0]);
        return _mm_popcnt_u64(c[0]) + _mm_popcnt_u64(c[1]);
    }

    bool contains(Card c) const {
        CardVec v = toCardVec(c);
        return !_mm_test_all_zeros(cv.v, v.v);
    }

    void add(Card c) {
#ifdef CARD_CHECKS
        if (contains(c)) {
            throw new std::runtime_error(
                    "Card already contained!" + c.toString());
        }
#endif
        CardVec cv = toCardVec(c);
        this->cv.v = _mm_xor_si128(cv.v, this->cv.v);
    }

    void remove(Card c) {
#ifdef CARD_CHECKS
        if (!contains(c)) {
            throw new std::runtime_error("Card not contained!" + c.toString());
        }
#endif
        add(c);
    }

    void addAll(const CardSet& cs) {
#ifdef CARD_CHECKS
        if (!_mm_test_all_zeros(cs.cv.v, this->cv.v)) {
            throw new std::runtime_error("CardSets are not disjoint!");
        }
#endif
        this->cv.v = _mm_or_si128(cs.cv.v, this->cv.v);
    }

    template< class Generator >
    Card dealRandomCard(Generator& g) {
        uint64_t* c = reinterpret_cast<uint64_t*>(&cv.cards[0]);
        uint32_t count_lo = _mm_popcnt_u64(c[0]);
        uint32_t count_hi = _mm_popcnt_u64(c[1]);

        std::uniform_int_distribution<> dis(0, count_lo + count_hi - 1);
        uint32_t r = dis(g);

        uint64_t mask;
        uint64_t s = r;
        if (r < count_lo) {
            mask = c[0];
        } else {
            mask = c[1];
            s -= count_lo;
        }

        for(uint32_t i=0; i<s;++i) {
            mask = mask & (mask - 1); // clear lowest bit
        }
        mask ^= mask & (mask - 1);

        uint32_t color;
        if (r < count_lo) {
            color = 0;
            c[0] ^= mask;
        } else {
            color = 2;
            c[1] ^= mask;
        }

        uint32_t card = __builtin_ctzll(mask);
        color += card / 32;
        card = (card % 32);
        card = card / 2;
        card = card - 1;

        return Card(static_cast<Rank>(card), static_cast<Color>(color));
    }


    HandRanking rankTexasHoldem() const;

    std::vector<Card> toCardVector() const;

private:
    union CardVec {
        uint32_t cards[4] = { 0, 0, 0, 0 };
        __m128i v;
    };

    static CardVec toCardVec(Card c) {
        CardVec cv;
        uint32_t idx = static_cast<uint32_t>(c.getColor());
        cv.cards[idx] = 4 << (static_cast<uint32_t>(c.getRank()) * 2);
        return cv;
    }

    CardSet(const CardVec& cv) :
            cv(cv) {
    }

    CardVec cv;
};

} /* namespace poker */

#endif /* CARDSET_H_ */
