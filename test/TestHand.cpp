/**
 * @author Crazy-8 groups
 * @date 2023-02
*/


#include <vector>
#include "gtest/gtest.h"
#include "Hand.h"
#include "Card.h"

TEST(TestHand, TestConstructorAndGetter) {
  std::vector<Card*> cards;
  Card* c = new Card(Rank(1), Suit(0));
  cards.push_back(c);
  Hand* h = new Hand(cards);
  std::vector<Card*> hand;
  hand = h->getCards();
  EXPECT_EQ(cards.size(), hand.size());

  delete h;
}

TEST(TestHand, TestAddCard) {
  std::vector<Card*> cards;
  Card* c = new Card(Rank(1), Suit(0));
  Hand* h = new Hand(cards);
  h->addToHand(c);
  std::vector<Card*> hand;
  hand = h->getCards();
  EXPECT_EQ(hand.size(), 1);
  EXPECT_EQ(hand[0], c);

  delete h;
}

TEST(TestHand, TestRemoveCard) {
  std::vector<Card*> cards;
  Card* c1 = new Card(Rank(1), Suit(0));
  Card* c2 = new Card(Rank(1), Suit(0));
  Card* c3 = new Card(Rank(1), Suit(0));
  cards.push_back(c3);
  cards.push_back(c2);
  cards.push_back(c1);
  Hand* h = new Hand(cards);

  EXPECT_EQ(h->getHandSize(), 3);
  EXPECT_EQ(h->removeFromHand(4), nullptr);
  EXPECT_EQ(h->getHandSize(), 3);

  Card* d1 = h->removeFromHand(2);
  EXPECT_EQ(d1, c1);
  EXPECT_EQ(h->getHandSize(), 2);

  Card* d2 = h->removeFromHand(1);
  EXPECT_EQ(d2, c2);
  EXPECT_EQ(h->getHandSize(), 1);

  Card* d3 = h->removeFromHand(0);
  EXPECT_EQ(d3, c3);
  EXPECT_TRUE(h->isEmpty());

  delete h;
  delete d1;
  delete d2;
  delete d3;
}

TEST(TestHand, TestSortHand) {
  std::vector<Card*> cards;
  Card* c1 = new Card(Rank(1), Suit(0));
  Card* c2 = new Card(Rank(2), Suit(1));
  Card* c3 = new Card(Rank(3), Suit(2));
  Card* c4 = new Card(Rank(5), Suit(2));
  Card* c5 = new Card(Rank(8), Suit(2));
  Card* c6 = new Card(Rank(10), Suit(2));
  Card* c7 = new Card(Rank(11), Suit(2));
  Card* c8 = new Card(Rank(13), Suit(2));
  cards.push_back(c3);
  cards.push_back(c6);
  cards.push_back(c7);
  cards.push_back(c2);
  cards.push_back(c8);
  cards.push_back(c1);
  cards.push_back(c4);
  cards.push_back(c5);
  Hand* h = new Hand(cards);
  h->sortHand();
  std::vector<Card*> hand;
  hand = h->getCards();
  EXPECT_EQ(hand.size(), 8);
  EXPECT_EQ(hand[0], c1);
  EXPECT_EQ(hand[1], c2);
  EXPECT_EQ(hand[2], c3);
  EXPECT_EQ(hand[3], c4);
  EXPECT_EQ(hand[4], c5);
  EXPECT_EQ(hand[5], c6);
  EXPECT_EQ(hand[6], c7);
  EXPECT_EQ(hand[7], c8);

  delete h;
}


TEST(TestHand, TestFindCard) {
    std::vector<Card*> cards;
    cards.push_back(new Card(Rank::Eight, Suit::Diamond));
    cards.push_back(new Card(Rank::Two, Suit::Spade));
    cards.push_back(new Card(Rank::Four, Suit::Heart));

    Hand* hand = new Hand(cards);

    int cardIndex = hand->findCard(Suit::Diamond);
    EXPECT_EQ(cardIndex, 0);

    cardIndex = hand->findCard(Rank::Two);
    EXPECT_EQ(cardIndex, 1);

    cardIndex = hand->findCard(Rank::Seven);
    EXPECT_EQ(cardIndex, -1);

    Card* card = hand->removeFromHand(2);

    cardIndex = hand->findCard(Suit::Heart);
    EXPECT_EQ(cardIndex, -1);

    delete card;
    delete hand;
}

TEST(TestHand, TestGetFromHand) {
    std::vector<Card*> cards;
    cards.push_back(new Card(Rank::Eight, Suit::Diamond));
    cards.push_back(new Card(Rank::Two, Suit::Spade));
    cards.push_back(new Card(Rank::Four, Suit::Heart));

    Hand* hand = new Hand(cards);

    Card* card = hand->getFromHand(1);
    EXPECT_EQ(card->getRank(), Rank::Two);

    card = hand->getFromHand(2);
    EXPECT_NE(card->getRank(), Rank::Two);
    EXPECT_EQ(card->getSuit(), Suit::Heart);

    delete hand;
}
