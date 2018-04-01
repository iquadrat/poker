#include "CardSet.h"
#include "AllCards.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace poker {

TEST(Card, RankAndColor) {
    Card c1(Rank::Q, Color::DIAMONDS);
    Card c2(Rank::_3, Color::HEARTS);
    Card c3(Rank::A, Color::CLUBS);

    EXPECT_EQ(Rank::Q, c1.getRank());
    EXPECT_EQ(Rank::_3, c2.getRank());
    EXPECT_EQ(Rank::A, c3.getRank());

    EXPECT_EQ(Color::DIAMONDS, c1.getColor());
    EXPECT_EQ(Color::HEARTS, c2.getColor());
    EXPECT_EQ(Color::CLUBS, c3.getColor());
}

TEST(Card, ToString) {
    Card c1(Rank::Q, Color::DIAMONDS);
    Card c2(Rank::_3, Color::HEARTS);
    Card c3(Rank::A, Color::CLUBS);

    EXPECT_EQ("QD", c1.toString());
    EXPECT_EQ("3H", c2.toString());
    EXPECT_EQ("AC", c3.toString());
}

TEST(CardSet, Empty) {
    CardSet cs;
    EXPECT_EQ(0, cs.size());
    EXPECT_THAT(cs.toCardVector(), testing::ElementsAre());
}

TEST(CardSet, FullDeck) {
    CardSet cs = CardSet::fullDeck();
    EXPECT_EQ(52, cs.size());
}

TEST(CardSet, addCard) {
    CardSet cs;
    Card c1(Rank::Q, Color::DIAMONDS);
    cs.add(c1);
    ASSERT_THAT(cs.toCardVector(), testing::ElementsAre(c1));
    ASSERT_EQ(1, cs.size());

    Card c2(Rank::_5, Color::HEARTS);
    cs.add(c2);
    ASSERT_THAT(cs.toCardVector(), testing::ElementsAre(c1, c2));
    ASSERT_EQ(2, cs.size());

    Card c3(Rank::A, Color::HEARTS);
    Card c4(Rank::K, Color::DIAMONDS);
    cs.add(c3);
    cs.add(c4);
    ASSERT_THAT(cs.toCardVector(), testing::ElementsAre(c1, c4, c2, c3));
    ASSERT_EQ(4, cs.size());
}

TEST(CardSet, addAllCardSet) {
    CardSet cs1;
    CardSet cs2;

    cs1.addAll(cs2);
    ASSERT_THAT(cs1.toCardVector(), testing::ElementsAre());

    Card c1(Rank::Q, Color::CLUBS);
    Card c2(Rank::_3, Color::HEARTS);
    Card c3(Rank::A, Color::CLUBS);
    Card c4(Rank::_9, Color::HEARTS);

    cs1.add(c1);
    cs1.add(c2);
    cs2.add(c3);
    cs2.add(c4);

    cs1.addAll(cs2);
    ASSERT_THAT(cs1.toCardVector(), testing::ElementsAre(c1, c3, c2, c4));
    ASSERT_EQ(4, cs1.size());
}

TEST(FastDeck, deal) {
    FastDeck deck;
    CardSet cs;

    deck.shuffle();

    uint64_t dealt = 0;
    for(int i=0; i<52; ++i) {
        Card c = deck.deal();
        cs.add(c);
        uint64_t mask = static_cast<uint64_t>(1) << c.getValue();
        ASSERT_EQ(0, dealt & mask) << "Iteration " << i;
        dealt |= mask;
    }
    ASSERT_EQ(52, cs.size());
}

TEST(CardSet, contains) {
    CardSet cs( { _JC, _8H, _4H, _AD, _AS });
    ASSERT_TRUE(cs.contains(_JC));
    ASSERT_TRUE(cs.contains(_AD));
    ASSERT_TRUE(cs.contains(_8H));
    ASSERT_TRUE(cs.contains(_4H));

    ASSERT_FALSE(cs.contains( { Rank::A, Color::HEARTS }));
    ASSERT_FALSE(cs.contains( { Rank::J, Color::DIAMONDS }));
}

TEST(CardSet, rankTH_Poker) {
    CardSet nopoker({_7C, _7H, _KC, _KD, _KH, _JC, _4H});
    CardSet poker1({ _AC, _AD, _AH, _AS, _JC, _4H, _7D});
    CardSet poker2({ _AC, _AD, _AH, _AS, _8H, _7C, _7D});
    CardSet poker3({ _KC, _KD, _KH, _KS, _AC, _AD, _7D});
    CardSet poker4({ _KC, _KD, _KH, _KS, _AC, _8H, _4H});
    CardSet poker5({ _KC, _KD, _KH, _KS, _AC, _AD, _4H});

    HandRanking rank0 = nopoker.rankTexasHoldem();
    HandRanking rank1 = poker1.rankTexasHoldem();
    HandRanking rank2 = poker2.rankTexasHoldem();
    HandRanking rank3 = poker3.rankTexasHoldem();
    HandRanking rank4 = poker4.rankTexasHoldem();
    HandRanking rank5 = poker5.rankTexasHoldem();

    ASSERT_NE(HandRanking::FOUR_OF_A_KIND, rank0.getRanking());
    ASSERT_EQ(HandRanking::FOUR_OF_A_KIND, rank1.getRanking());
    ASSERT_EQ(HandRanking::FOUR_OF_A_KIND, rank2.getRanking());
    ASSERT_EQ(HandRanking::FOUR_OF_A_KIND, rank3.getRanking());
    ASSERT_EQ(HandRanking::FOUR_OF_A_KIND, rank4.getRanking());
    ASSERT_EQ(HandRanking::FOUR_OF_A_KIND, rank5.getRanking());

    ASSERT_GT(rank1, rank0);
    ASSERT_GT(rank1, rank2);
    ASSERT_GT(rank1, rank3);
    ASSERT_GT(rank2, rank3);
    ASSERT_GT(rank2, rank0);
    ASSERT_GT(rank3, rank0);
    ASSERT_EQ(rank3, rank4);
    ASSERT_EQ(rank3, rank5);
}

TEST(CardSet, rankTH_FullHouse) {
    HandRanking rank0 = CardSet({_7C, _7H, _6D, _KD, _KH, _6C, _AD}).rankTexasHoldem();
    HandRanking rank1 = CardSet({_7C, _7H, _7D, _KD, _KH, _JC, _AD}).rankTexasHoldem();
    HandRanking rank2 = CardSet({_7C, _7H, _7D, _AD, _AS, _JC, _4H}).rankTexasHoldem();
    HandRanking rank3 = CardSet({_7C, _7H, _KD, _KH, _KS, _JC, _4H}).rankTexasHoldem();
    HandRanking rank4 = CardSet({_7C, _7H, _KD, _KH, _KS, _AC, _4H}).rankTexasHoldem();
    HandRanking rank5 = CardSet({_7C, _7H, _KD, _KH, _KS, _9C, _9H}).rankTexasHoldem();
    HandRanking rank6 = CardSet({_6C, _6H, _KD, _KH, _KS, _9C, _9H}).rankTexasHoldem();
    HandRanking rank7 = CardSet({_KD, _KH, _KS, _9C, _9H, _9D, _AD}).rankTexasHoldem();
    HandRanking rank8 = CardSet({_9D, _9H, _9S, _AC, _AH, _6D, _JC}).rankTexasHoldem();

    ASSERT_NE(HandRanking::FULL_HOUSE, rank0.getRanking());
    ASSERT_EQ(HandRanking::FULL_HOUSE, rank1.getRanking());
    ASSERT_EQ(HandRanking::FULL_HOUSE, rank2.getRanking());
    ASSERT_EQ(HandRanking::FULL_HOUSE, rank3.getRanking());
    ASSERT_EQ(HandRanking::FULL_HOUSE, rank4.getRanking());
    ASSERT_EQ(HandRanking::FULL_HOUSE, rank5.getRanking());
    ASSERT_EQ(HandRanking::FULL_HOUSE, rank6.getRanking());
    ASSERT_EQ(HandRanking::FULL_HOUSE, rank7.getRanking());

    ASSERT_GT(rank2, rank1);
    ASSERT_GT(rank3, rank2);
    ASSERT_EQ(rank4, rank3);
    ASSERT_GT(rank5, rank4);
    ASSERT_EQ(rank6, rank5);
    ASSERT_EQ(rank7, rank6);
    ASSERT_GT(rank3, rank8);
    ASSERT_GT(rank8, rank2);
}

TEST(CardSet, rankTH_ThreeOfAKind) {
    HandRanking rank0 = CardSet({_7C, _7H, _6D, _KD, _KH, _6C, _AD}).rankTexasHoldem();
    HandRanking rank1 = CardSet({_7C, _7H, _7D, _KD, _AH, _6C, _9D}).rankTexasHoldem();
    HandRanking rank2 = CardSet({_9C, _9H, _9D, _8H, _4H, _6C, _JC}).rankTexasHoldem();
    HandRanking rank3 = CardSet({_9C, _9H, _9D, _8H, _4H, _6C, _KH}).rankTexasHoldem();
    HandRanking rank4 = CardSet({_9C, _9H, _9D, _JC, _4H, _6C, _KH}).rankTexasHoldem();
    HandRanking rank5 = CardSet({_9C, _9H, _9D, _JC, _4H, _7D, _KH}).rankTexasHoldem();
    HandRanking rank6 = CardSet({_AC, _AH, _AD, _JC, _4H, _7D, _KH}).rankTexasHoldem();
    HandRanking rank7 = CardSet({_AC, _AH, _AD, _QC, _4H, _7D, _KH}).rankTexasHoldem();
    HandRanking rank8 = CardSet({_AC, _AH, _AD, _QC, _4H, _9D, _KH}).rankTexasHoldem();

    ASSERT_NE(HandRanking::THREE_OF_A_KIND, rank0.getRanking());
    ASSERT_EQ(HandRanking::THREE_OF_A_KIND, rank1.getRanking());
    ASSERT_EQ(HandRanking::THREE_OF_A_KIND, rank2.getRanking());
    ASSERT_EQ(HandRanking::THREE_OF_A_KIND, rank3.getRanking());
    ASSERT_EQ(HandRanking::THREE_OF_A_KIND, rank4.getRanking());
    ASSERT_EQ(HandRanking::THREE_OF_A_KIND, rank5.getRanking());
    ASSERT_EQ(HandRanking::THREE_OF_A_KIND, rank6.getRanking());
    ASSERT_EQ(HandRanking::THREE_OF_A_KIND, rank7.getRanking());

    ASSERT_GT(rank1, rank0);
    ASSERT_GT(rank2, rank1);
    ASSERT_GT(rank3, rank2);
    ASSERT_GT(rank4, rank3);
    ASSERT_EQ(rank5, rank4);
    ASSERT_GT(rank6, rank5);
    ASSERT_GT(rank7, rank6);
    ASSERT_EQ(rank8, rank7);
}

TEST(CardSet, rankTH_TwoPairs) {
    HandRanking rank0 = CardSet({_7C, _9H, _6D, _KD, _KH, _JC, _AD}).rankTexasHoldem();
    HandRanking rank1 = CardSet({_7C, _7H, _6D, _KD, _KH, _JC, _AD}).rankTexasHoldem();
    HandRanking rank2 = CardSet({_9C, _9H, _6D, _KD, _KH, _JC, _AD}).rankTexasHoldem();
    HandRanking rank3 = CardSet({_6C, _6D, _7D, _AH, _QS, _JC, _AD}).rankTexasHoldem();
    HandRanking rank4 = CardSet({_6C, _6D, _7D, _AH, _KS, _JC, _AD}).rankTexasHoldem();
    HandRanking rank5 = CardSet({_6C, _6D, _QD, _AH, _4H, _QC, _AD}).rankTexasHoldem();
    HandRanking rank6 = CardSet({_9C, _6D, _QD, _AH, _4H, _QC, _AD}).rankTexasHoldem();
    HandRanking rank7 = CardSet({_9C, _6D, _QD, _AH, _5H, _QC, _AD}).rankTexasHoldem();
    HandRanking rank8 = CardSet({_9C, _6D, _QD, _AH, _7H, _QC, _AD}).rankTexasHoldem();
    HandRanking rank9 = CardSet({_9C, _9D, _QD, _AH, _7H, _QC, _AD}).rankTexasHoldem();
    HandRanking rankA = CardSet({_9C, _6D, _QD, _AH, _TH, _QC, _AD}).rankTexasHoldem();

    ASSERT_NE(HandRanking::TWO_PAIRS, rank0.getRanking());
    ASSERT_EQ(HandRanking::TWO_PAIRS, rank1.getRanking());
    ASSERT_EQ(HandRanking::TWO_PAIRS, rank2.getRanking());
    ASSERT_EQ(HandRanking::TWO_PAIRS, rank3.getRanking());
    ASSERT_EQ(HandRanking::TWO_PAIRS, rank4.getRanking());
    ASSERT_EQ(HandRanking::TWO_PAIRS, rank5.getRanking());
    ASSERT_EQ(HandRanking::TWO_PAIRS, rank6.getRanking());
    ASSERT_EQ(HandRanking::TWO_PAIRS, rank7.getRanking());
    ASSERT_EQ(HandRanking::TWO_PAIRS, rank8.getRanking());
    ASSERT_EQ(HandRanking::TWO_PAIRS, rank9.getRanking());
    ASSERT_EQ(HandRanking::TWO_PAIRS, rankA.getRanking());

    ASSERT_GT(rank1, rank0);
    ASSERT_GT(rank2, rank1);
    ASSERT_GT(rank3, rank2);
    ASSERT_GT(rank4, rank3);
    ASSERT_GT(rank5, rank4);
    ASSERT_GT(rank6, rank5);
    ASSERT_EQ(rank7, rank6);
    ASSERT_EQ(rank8, rank6);
    ASSERT_EQ(rank9, rank8);
    ASSERT_GT(rankA, rank9);
}

TEST(CardSet, rankTH_Pair) {
    HandRanking rank0 = CardSet({_7C, _4H, _6D, _KD, _8H, _JC, _AD}).rankTexasHoldem();
    HandRanking rank1 = CardSet({_7C, _4H, _6D, _KD, _6H, _JC, _AD}).rankTexasHoldem();
    HandRanking rank2 = CardSet({_7C, _4H, _7D, _KD, _6H, _JC, _2D}).rankTexasHoldem();
    HandRanking rank3 = CardSet({_7C, _4H, _7D, _AD, _6H, _9C, _2D}).rankTexasHoldem();
    HandRanking rank4 = CardSet({_7C, _4H, _7D, _AD, _6H, _QC, _2D}).rankTexasHoldem();
    HandRanking rank5 = CardSet({_7C, _4H, _7D, _AD, _9H, _QC, _2D}).rankTexasHoldem();
    HandRanking rank6 = CardSet({_7C, _6H, _7D, _AD, _9H, _QC, _2D}).rankTexasHoldem();
    HandRanking rank7 = CardSet({_7C, _6H, _7D, _AD, _9H, _QC, _4H}).rankTexasHoldem();
    HandRanking rank8 = CardSet({_7C, _8H, _7D, _AD, _9H, _JC, _QH}).rankTexasHoldem();
    HandRanking rank9 = CardSet({_7C, _8H, _7D, _AD, _TH, _JC, _QH}).rankTexasHoldem();

    ASSERT_NE(HandRanking::ONE_PAIR, rank0.getRanking());
    ASSERT_EQ(HandRanking::ONE_PAIR, rank1.getRanking());
    ASSERT_EQ(HandRanking::ONE_PAIR, rank2.getRanking());
    ASSERT_EQ(HandRanking::ONE_PAIR, rank3.getRanking());
    ASSERT_EQ(HandRanking::ONE_PAIR, rank4.getRanking());
    ASSERT_EQ(HandRanking::ONE_PAIR, rank5.getRanking());
    ASSERT_EQ(HandRanking::ONE_PAIR, rank6.getRanking());
    ASSERT_EQ(HandRanking::ONE_PAIR, rank7.getRanking());
    ASSERT_EQ(HandRanking::ONE_PAIR, rank8.getRanking());
    ASSERT_EQ(HandRanking::ONE_PAIR, rank9.getRanking());

    ASSERT_GT(rank1, rank0);
    ASSERT_GT(rank2, rank1);
    ASSERT_GT(rank3, rank2);
    ASSERT_GT(rank4, rank3);
    ASSERT_GT(rank5, rank4);
    ASSERT_EQ(rank6, rank5);
    ASSERT_EQ(rank7, rank6);
    ASSERT_GT(rank8, rank7);
    ASSERT_EQ(rank9, rank8);
}

TEST(CardSet, rankTH_HighCard) {
    HandRanking rank0 = CardSet({_2H, _4H, _6D, _7D, _8H, _9S, _JC}).rankTexasHoldem();
    HandRanking rank1 = CardSet({_2H, _4H, _6D, _7D, _8H, _9S, _AC}).rankTexasHoldem();
    HandRanking rank2 = CardSet({_2H, _4H, _6D, _7D, _8H, _JC, _AC}).rankTexasHoldem();
    HandRanking rank3 = CardSet({_2H, _4H, _6D, _7D, _9H, _JC, _AC}).rankTexasHoldem();
    HandRanking rank4 = CardSet({_2H, _4H, _6D, _8H, _9H, _JC, _AC}).rankTexasHoldem();
    HandRanking rank5 = CardSet({_2H, _4H, _7D, _8H, _9H, _JC, _AC}).rankTexasHoldem();
    HandRanking rank6 = CardSet({_2H, _6H, _7D, _8H, _9H, _JC, _AC}).rankTexasHoldem();
    HandRanking rank7 = CardSet({_4H, _6H, _7D, _8H, _9H, _JC, _AC}).rankTexasHoldem();

    ASSERT_EQ(HandRanking::HIGH_CARD, rank0.getRanking());
    ASSERT_EQ(HandRanking::HIGH_CARD, rank1.getRanking());
    ASSERT_EQ(HandRanking::HIGH_CARD, rank2.getRanking());
    ASSERT_EQ(HandRanking::HIGH_CARD, rank3.getRanking());
    ASSERT_EQ(HandRanking::HIGH_CARD, rank4.getRanking());
    ASSERT_EQ(HandRanking::HIGH_CARD, rank5.getRanking());
    ASSERT_EQ(HandRanking::HIGH_CARD, rank6.getRanking());
    ASSERT_EQ(HandRanking::HIGH_CARD, rank7.getRanking());

    ASSERT_GT(rank1, rank0);
    ASSERT_GT(rank2, rank1);
    ASSERT_GT(rank3, rank2);
    ASSERT_GT(rank4, rank3);
    ASSERT_GT(rank5, rank4);
    ASSERT_EQ(rank6, rank5);
    ASSERT_EQ(rank7, rank6);
}

TEST(CardSet, rankTH_Straight) {
    HandRanking rank0 = CardSet({_6H, _6S, _6D, _7D, _8H, _9S, _JC}).rankTexasHoldem();
    HandRanking rank1 = CardSet({_2H, _3H, _4D, _5D, _7H, _JC, _KC}).rankTexasHoldem();
    HandRanking rank2 = CardSet({_2H, _3H, _4D, _5D, _7H, _JC, _AC}).rankTexasHoldem();
    HandRanking rank3 = CardSet({_2H, _3H, _4D, _5D, _6H, _JC, _AC}).rankTexasHoldem();
    HandRanking rank4 = CardSet({_2H, _3H, _4D, _5D, _6H, _JC, _KC}).rankTexasHoldem();
    HandRanking rank5 = CardSet({_4H, _5H, _6D, _7D, _8H, _JC, _KC}).rankTexasHoldem();
    HandRanking rank6 = CardSet({_4H, _5H, _6D, _7D, _8H, _JC, _AC}).rankTexasHoldem();
    HandRanking rank7 = CardSet({_4H, _5H, _6D, _7D, _8H, _QC, _AC}).rankTexasHoldem();

    ASSERT_NE(HandRanking::STRAIGHT, rank0.getRanking());
    ASSERT_NE(HandRanking::STRAIGHT, rank1.getRanking());
    ASSERT_EQ(HandRanking::STRAIGHT, rank2.getRanking());
    ASSERT_EQ(HandRanking::STRAIGHT, rank3.getRanking());
    ASSERT_EQ(HandRanking::STRAIGHT, rank4.getRanking());
    ASSERT_EQ(HandRanking::STRAIGHT, rank5.getRanking());
    ASSERT_EQ(HandRanking::STRAIGHT, rank6.getRanking());
    ASSERT_EQ(HandRanking::STRAIGHT, rank7.getRanking());

    ASSERT_GT(rank2, rank1);
    ASSERT_GT(rank3, rank2);
    ASSERT_EQ(rank4, rank3);
    ASSERT_GT(rank5, rank4);
    ASSERT_EQ(rank6, rank5);
    ASSERT_EQ(rank7, rank6);
}

TEST(CardSet, rankTH_Flush) {
    HandRanking rank0 = CardSet({_4H, _5H, _6D, _7D, _8H, _JC, _AC}).rankTexasHoldem();
    HandRanking rank1 = CardSet({_4H, _5H, _7H, _8H, _QH, _5S, _AC}).rankTexasHoldem();
    HandRanking rank2 = CardSet({_4H, _5H, _7H, _8H, _QH, _AH, _AC}).rankTexasHoldem();
    HandRanking rank3 = CardSet({_4H, _5H, _7H, _8H, _QH, _KH, _AH}).rankTexasHoldem();
    HandRanking rank4 = CardSet({_4S, _5H, _7H, _8H, _QH, _KH, _AH}).rankTexasHoldem();
    HandRanking rank5 = CardSet({_4S, _5S, _7H, _8H, _QH, _KH, _AH}).rankTexasHoldem();
    HandRanking rank6 = CardSet({_4S, _5S, _2H, _9H, _QH, _KH, _AH}).rankTexasHoldem();
    HandRanking rank7 = CardSet({_4S, _5S, _3H, _9H, _QH, _KH, _AH}).rankTexasHoldem();

    ASSERT_NE(HandRanking::FLUSH, rank0.getRanking());
    ASSERT_EQ(HandRanking::FLUSH, rank1.getRanking());
    ASSERT_EQ(HandRanking::FLUSH, rank2.getRanking());
    ASSERT_EQ(HandRanking::FLUSH, rank3.getRanking());
    ASSERT_EQ(HandRanking::FLUSH, rank4.getRanking());
    ASSERT_EQ(HandRanking::FLUSH, rank5.getRanking());
    ASSERT_EQ(HandRanking::FLUSH, rank6.getRanking());
    ASSERT_EQ(HandRanking::FLUSH, rank7.getRanking());

    ASSERT_GT(rank1, rank0);
    ASSERT_GT(rank2, rank1);
    ASSERT_GT(rank3, rank2);
    ASSERT_EQ(rank4, rank3);
    ASSERT_EQ(rank5, rank4);
    ASSERT_GT(rank6, rank5);
    ASSERT_GT(rank7, rank6);
}

TEST(CardSet, rankTH_StraightFlush) {
    HandRanking rank0 = CardSet({_4H, _4S, _4D, _4C, _8H, _JC, _AC}).rankTexasHoldem();
    HandRanking rank1 = CardSet({_4H, _4S, _4D, _5D, _6D, _7D, _8D}).rankTexasHoldem();
    HandRanking rank2 = CardSet({_4H, _4D, _5D, _6D, _7D, _8D, _9D}).rankTexasHoldem();
    HandRanking rank3 = CardSet({_3D, _4D, _5D, _6D, _7D, _8D, _9D}).rankTexasHoldem();
    HandRanking rank4 = CardSet({_AC, _AD, _5D, _6D, _7D, _8D, _9D}).rankTexasHoldem();
    HandRanking rank5 = CardSet({_KD, _AD, _5D, _6D, _7D, _8D, _9D}).rankTexasHoldem();
    HandRanking rank6 = CardSet({_TS, _AD, _5D, _6D, _7D, _8D, _9D}).rankTexasHoldem();

    ASSERT_NE(HandRanking::STRAIGHT_FLUSH, rank0.getRanking());
    ASSERT_EQ(HandRanking::STRAIGHT_FLUSH, rank1.getRanking());
    ASSERT_EQ(HandRanking::STRAIGHT_FLUSH, rank2.getRanking());
    ASSERT_EQ(HandRanking::STRAIGHT_FLUSH, rank3.getRanking());
    ASSERT_EQ(HandRanking::STRAIGHT_FLUSH, rank4.getRanking());
    ASSERT_EQ(HandRanking::STRAIGHT_FLUSH, rank5.getRanking());
    ASSERT_EQ(HandRanking::STRAIGHT_FLUSH, rank6.getRanking());

    ASSERT_GT(rank1, rank0);
    ASSERT_GT(rank2, rank1);
    ASSERT_EQ(rank3, rank2);
    ASSERT_EQ(rank4, rank2);
    ASSERT_EQ(rank5, rank2);
    ASSERT_EQ(rank6, rank2);
}


} // namespace poker
