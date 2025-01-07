/**
 * @author Crazy-8 groups
 * @date 2023-02
*/


#include "gtest/gtest.h"
#include "Card.h"

TEST(TestCard, TestConstructorAndGetters) {
  for (int rank = 1; rank < 14; rank++) {
    for (int suit = 0; suit < 4; suit++) {
      Card c{Rank(rank), Suit(suit)};
      EXPECT_EQ(Rank(rank), c.getRank());
      EXPECT_EQ(Suit(suit), c.getSuit());
    }
  }
}

TEST(TestCard, TestSetSuit) {
  Card c(Rank(1), Suit(0));
  EXPECT_EQ(Suit(0), c.getSuit());
  c.setSuit(Suit(1));
  EXPECT_EQ(Suit(1), c.getSuit());
  c.setSuit(Suit(2));
  EXPECT_EQ(Suit(2), c.getSuit());
  c.setSuit(Suit(3));
  EXPECT_EQ(Suit(3), c.getSuit());
}

TEST(TestCard, TestIsEight) {
  for (int suit = 0; suit < 4; suit++) {
    Card c(Rank(8), Suit(suit));
    EXPECT_TRUE(c.isEight());
    Card d(Rank(1), Suit(suit));
    EXPECT_FALSE(d.isEight());
  }
}

TEST(TestCard, TestGetScore) {
  Card c1(Rank(1), Suit(0));
  Card c2(Rank(13), Suit(0));
  Card c3(Rank(12), Suit(0));
  Card c4(Rank(11), Suit(0));
  Card c5(Rank(10), Suit(0));
  Card c6(Rank(7), Suit(0));
  Card c7(Rank(3), Suit(0));
  Card c8(Rank(8), Suit(0));

  EXPECT_EQ(c1.getScore(), 1);
  EXPECT_EQ(c2.getScore(), 10);
  EXPECT_EQ(c3.getScore(), 10);
  EXPECT_EQ(c4.getScore(), 10);
  EXPECT_EQ(c5.getScore(), 10);
  EXPECT_EQ(c6.getScore(), 7);
  EXPECT_EQ(c7.getScore(), 3);
  EXPECT_EQ(c8.getScore(), 50);
}
