/**
 * @author Crazy-8 groups
 * @date 2023-02
*/

#include <iostream>
#include "gtest/gtest.h"
#include "Player.h"
#include "Human.h"
#include "CI.h"

TEST(TestPlayer, TestConstructorAndGetters) {
  for (int i = 0; i < 4; i++) {
    Player p("Player " + std::to_string(i), i, nullptr);
    Human h("Player " + std::to_string(i), i, nullptr);
    CI c("Player " + std::to_string(i), i, nullptr);
    EXPECT_EQ("Player " + std::to_string(i), p.getName());
    EXPECT_EQ("Player " + std::to_string(i), h.getName());
    EXPECT_EQ("Player " + std::to_string(i), c.getName());
    EXPECT_EQ(i, p.getPlayerNumber());
    EXPECT_EQ(i, h.getPlayerNumber());
    EXPECT_EQ(i, c.getPlayerNumber());
  }
}

TEST(TestPlayer, TestGetHand) {
    std::vector<Card*> cards;
    cards.push_back(new Card(Rank::Eight, Suit::Diamond));
    cards.push_back(new Card(Rank::Four, Suit::Diamond));
    cards.push_back(new Card(Rank::Three, Suit::Heart));
    cards.push_back(new Card(Rank::Two, Suit::Spade));
    cards.push_back(new Card(Rank::Ace, Suit::Club));

    Hand *hand = new Hand(cards);
    Player* p = new Player("Player 1", 1, hand);

    Hand* playerHand = p->getHand();
    int handSize = playerHand->getHandSize();
    EXPECT_EQ(handSize, 5);

    for (int i = 4; i > -1; i--) {
        Card* card = hand->removeFromHand(i);
        delete card;
    }

    EXPECT_TRUE(playerHand->isEmpty());

    delete p;
}

TEST(TestPlayer, TestGetScore) {
  Player p("Player 1", 1, nullptr);
  p.setScore(0);
  EXPECT_EQ(0, p.getScore());
}

TEST(TestPlayer, TestGetName) {
  Player p("Player 1", 1, nullptr);
  EXPECT_EQ("Player 1", p.getName());

  Player q("Player q", 2, nullptr);
  EXPECT_EQ(q.getName(), "Player q");
}

TEST(TestPlayer, TestChangeScore) {
  Player p("Player 1", 1, nullptr);
  EXPECT_EQ(0, p.getScore());
  p.setScore(5);
  EXPECT_EQ(5, p.getScore());
  p.setScore(3);
  EXPECT_EQ(3, p.getScore());
}

TEST(TestPlayer, TestGetPlayerNumber) {
  Player p("Player 1", 1, nullptr);
  EXPECT_EQ(1, p.getPlayerNumber());
}

TEST(TestPlayer, TestSetPlayerType) {
  Player p("Player 1", 1, nullptr);
  p.setPlayerType(true);
  EXPECT_TRUE(p.isHumanPlayer());

  p.setPlayerType(false);
  EXPECT_FALSE(p.isHumanPlayer());
}

TEST(TestPlayer, CIStratTest) {
  CI c("Player ", 1, nullptr);
  c.setStrategy(CIStrategy::PlaySameSuit);
  EXPECT_EQ(c.getStrategy(), CIStrategy::PlaySameSuit);
}

TEST(TestPlayer, humanTest) {
  Human h;
  EXPECT_TRUE(h.isHumanPlayer());
}
