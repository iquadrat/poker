#include "CardSet.h"

#include <benchmark/benchmark.h>
#include <memory>
#include <string.h>
#include <iostream>
#include <algorithm>

namespace poker {

Card _JC(Rank::J, Color::CLUBS);

Card _2C(Rank::_2, Color::CLUBS);
Card _2D(Rank::_2, Color::DIAMONDS);
Card _2H(Rank::_2, Color::HEARTS);
Card _2S(Rank::_2, Color::SPADES);

Card _3C(Rank::_3, Color::CLUBS);
Card _3D(Rank::_3, Color::DIAMONDS);
Card _3H(Rank::_3, Color::HEARTS);
Card _3S(Rank::_3, Color::SPADES);

Card _4C(Rank::_4, Color::CLUBS);
Card _4D(Rank::_4, Color::DIAMONDS);
Card _4H(Rank::_4, Color::HEARTS);
Card _4S(Rank::_4, Color::SPADES);

Card _5C(Rank::_5, Color::CLUBS);
Card _5D(Rank::_5, Color::DIAMONDS);
Card _5H(Rank::_5, Color::HEARTS);
Card _5S(Rank::_5, Color::SPADES);

Card _6C(Rank::_6, Color::CLUBS);
Card _6D(Rank::_6, Color::DIAMONDS);
Card _6H(Rank::_6, Color::HEARTS);
Card _6S(Rank::_6, Color::SPADES);

Card _7C(Rank::_7, Color::CLUBS);
Card _7D(Rank::_7, Color::DIAMONDS);
Card _7H(Rank::_7, Color::HEARTS);
Card _7S(Rank::_7, Color::SPADES);

Card _8C(Rank::_8, Color::CLUBS);
Card _8D(Rank::_8, Color::DIAMONDS);
Card _8H(Rank::_8, Color::HEARTS);
Card _8S(Rank::_8, Color::SPADES);

Card _9C(Rank::_9, Color::CLUBS);
Card _9D(Rank::_9, Color::DIAMONDS);
Card _9H(Rank::_9, Color::HEARTS);
Card _9S(Rank::_9, Color::SPADES);

Card _QC(Rank::Q, Color::CLUBS);
Card _QD(Rank::Q, Color::DIAMONDS);
Card _QH(Rank::Q, Color::HEARTS);
Card _QS(Rank::Q, Color::SPADES);

Card _KC(Rank::K, Color::CLUBS);
Card _KD(Rank::K, Color::DIAMONDS);
Card _KH(Rank::K, Color::HEARTS);
Card _KS(Rank::K, Color::SPADES);

Card _AC(Rank::A, Color::CLUBS);
Card _AD(Rank::A, Color::DIAMONDS);
Card _AH(Rank::A, Color::HEARTS);
Card _AS(Rank::A, Color::SPADES);

void assert_ranking(HandRanking::Ranking expected, HandRanking ranking) {
    if (expected != ranking.getRanking()) {
        throw new std::runtime_error("Invalid ranking!");
    }
}

void BM_fast_deck_deal(benchmark::State& state) {
    FastDeck deck;
    for (auto _ : state) {
        deck.shuffle();
        for (int i = 0; i < 8 * 2 + 5; ++i) {
            benchmark::DoNotOptimize(deck.deal());
        }
    }
}
BENCHMARK(BM_fast_deck_deal);

void BM_deal_full_table_th(benchmark::State& state) {
    FastDeck deck;
    for (auto _ : state) {
        deck.shuffle();
        CardSet table;
        for (int i = 0; i < 5; ++i) {
            table.add(deck.deal());
        }

        CardSet player[8];
        for (int i = 0; i < 8; ++i) {
            player[i].addAll(table);
            player[i].add(deck.deal());
            player[i].add(deck.deal());
        }
        for (int i = 0; i < 8; ++i) {
            benchmark::DoNotOptimize(player[i].contains(_AC));
        }
    }
}
BENCHMARK(BM_deal_full_table_th);

class RankTable {
public:
    RankTable() {
        memset(count, 0, 9 * sizeof(uint32_t));
    }

    void add(HandRanking ranking) {
        count[static_cast<int>(ranking.getRanking())]++;
        sum++;
    }

    void print() {
        std::cout << "sum: " << sum << std::endl;
        for (int i = 0; i < 9; ++i) {
            double frac = 1.0 * count[i] / sum;
            std::cout << i << ": " << count[i] << " = " << frac << std::endl;
        }
    }

private:
    uint32_t sum = 0;
    uint32_t count[9];
};

void BM_deal_and_rank_full_table_th(benchmark::State& state) {
    FastDeck deck;
    RankTable rt;
    for (auto _ : state) {
        deck.shuffle();
        CardSet table;
        for (int i = 0; i < 5; ++i) {
            table.add(deck.deal());
        }

        CardSet player[8];
        for (int i = 0; i < 8; ++i) {
            player[i].addAll(table);
            player[i].add(deck.deal());
            player[i].add(deck.deal());
        }
        for (int i = 0; i < 8; ++i) {
            benchmark::DoNotOptimize(player[i].rankTexasHoldem());
            //rt.add(player[i].rankTexasHoldem());
        }
    }
    //rt.print();
}
BENCHMARK(BM_deal_and_rank_full_table_th);

#define min(x, y) (x<y?x:y)
#define max(x, y) (x<y?y:x)
#define SWAP(x,y) {  HandRanking a = min(d[x], d[y]); \
        HandRanking b = max(d[x], d[y]); d[x] = a; d[y] = b;}

void sort8(HandRanking d[8]) {
    SWAP(0, 1);
    SWAP(2, 3);
    SWAP(0, 2);
    SWAP(1, 3);
    SWAP(1, 2);
    SWAP(4, 5);
    SWAP(6, 7);
    SWAP(4, 6);
    SWAP(5, 7);
    SWAP(5, 6);
    SWAP(0, 4);
    SWAP(1, 5);
    SWAP(1, 4);
    SWAP(2, 6);
    SWAP(3, 7);
    SWAP(3, 6);
    SWAP(2, 4);
    SWAP(3, 5);
    SWAP(3, 4);
}

template<typename RandIt>
void insertion_sort(RandIt begin, RandIt end)
{
    for (auto i = begin + 1; i != end; ++i)
    {
        auto key = *i;
        auto j = i - 1;

        while (j >= begin and *j > key)
        {
            *(j + 1) = *j;
            --j;
        }

        *(j + 1) = key;
    }
}

void BM_rank_sort_full_table_th(benchmark::State& state) {
    FastDeck deck;
    RankTable rt;
    for (auto _ : state) {
        deck.shuffle();
        CardSet table;
        for (int i = 0; i < 5; ++i) {
            table.add(deck.deal());
        }

        CardSet player[8];
        for (int i = 0; i < 8; ++i) {
            player[i].addAll(table);
            player[i].add(deck.deal());
            player[i].add(deck.deal());
        }

        HandRanking rank[8];
        for (int i = 0; i < 8; ++i) {
            rank[i] = player[i].rankTexasHoldem();
        }
        /*for (int i = 1; i < 8; ++i) {
            HandRanking r = rank[i];
            std::sort(r)
            int j = 0;
            while (j < i && rank[j] < r) {
                j++;
            }
            std::swap(rank[i], rank[j]);
        }*/
        //insertion_sort(rank, rank+8);
        sort8(rank);
        //std::sort(rank, rank+8);
/*        for(int i= 0; i<7; ++i) {
            if (rank[i] > rank[i+1]) {
                throw new std::runtime_error("invalid sorting");
            }
        }*/
        benchmark::DoNotOptimize(rank[0]);
    }
    //rt.print();
}
BENCHMARK(BM_rank_sort_full_table_th);

void BM_rank_full_table_th(benchmark::State& state) {
    constexpr int tables = 100;

    FastDeck deck;
    RankTable rt;
    std::unique_ptr<CardSet[]> hands(new CardSet[8 * tables]);

    for (int t = 0; t < tables; ++t) {
        deck.shuffle();
        CardSet table;
        for (int i = 0; i < 5; ++i) {
            table.add(deck.deal());
        }

        CardSet* player = &hands[8 * t];
        for (int i = 0; i < 8; ++i) {
            player[i].addAll(table);
            player[i].add(deck.deal());
            player[i].add(deck.deal());
        }
    }

    for (auto _ : state) {
        for (int i = 0; i < 8 * tables; ++i) {
            HandRanking r = hands[i].rankTexasHoldem();
            benchmark::DoNotOptimize(r);
            //rt.add(r);
            //std::cout << "r = " << r.getRanking() << std::endl;
        }
    }
    //rt.print();
}
BENCHMARK(BM_rank_full_table_th);

void BM_rank_th_high_card(benchmark::State& state) {
    CardSet cards = CardSet( { _2H, _4H, _6D, _7D, _8H, _9S, _JC });
    assert_ranking(HandRanking::HIGH_CARD, cards.rankTexasHoldem());
    for (auto _ : state) {
        benchmark::DoNotOptimize(cards.rankTexasHoldem());
    }
}
BENCHMARK(BM_rank_th_high_card);

void BM_rank_th_pair(benchmark::State& state) {
    CardSet cards = CardSet( { _2H, _4H, _6D, _6H, _8H, _9S, _JC });
    assert_ranking(HandRanking::ONE_PAIR, cards.rankTexasHoldem());
    for (auto _ : state) {
        benchmark::DoNotOptimize(cards.rankTexasHoldem());
    }
}
BENCHMARK(BM_rank_th_pair);

void BM_rank_th_two_pairs(benchmark::State& state) {
    CardSet cards = CardSet( { _2H, _4H, _6D, _6H, _9H, _9S, _JC });
    assert_ranking(HandRanking::TWO_PAIRS, cards.rankTexasHoldem());
    for (auto _ : state) {
        benchmark::DoNotOptimize(cards.rankTexasHoldem());
    }
}
BENCHMARK(BM_rank_th_two_pairs);

void BM_rank_th_straight(benchmark::State& state) {
    CardSet cards = CardSet( { _2H, _4H, _5D, _6H, _7H, _8S, _9C });
    assert_ranking(HandRanking::STRAIGHT, cards.rankTexasHoldem());
    for (auto _ : state) {
        benchmark::DoNotOptimize(cards.rankTexasHoldem());
    }
}
BENCHMARK(BM_rank_th_straight);

void BM_rank_th_flush(benchmark::State& state) {
    CardSet cards = CardSet( { _2H, _4H, _5D, _6H, _7H, _8S, _9C });
    assert_ranking(HandRanking::STRAIGHT, cards.rankTexasHoldem());
    for (auto _ : state) {
        benchmark::DoNotOptimize(cards.rankTexasHoldem());
    }
}
BENCHMARK(BM_rank_th_flush);

void BM_rank_th_three_of_kind(benchmark::State& state) {
    CardSet cards = CardSet( { _2H, _4H, _5D, _5H, _5S, _8S, _9C });
    assert_ranking(HandRanking::THREE_OF_A_KIND, cards.rankTexasHoldem());
    for (auto _ : state) {
        benchmark::DoNotOptimize(cards.rankTexasHoldem());
    }
}
BENCHMARK(BM_rank_th_three_of_kind);

}

BENCHMARK_MAIN()
;
