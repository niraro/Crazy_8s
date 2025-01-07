/**
 * @author Crazy-8 groups
 * @date 2023-02
*/

#include <vector>
#include "gtest/gtest.h"
#include "Deck.h"

TEST(TestDeck, GetTopCardTest) {
    std::vector<Card*> cards;
    cards.reserve(5);

    cards.push_back(new Card(Rank::Five, Suit::Club));
    cards.push_back(new Card(Rank::Six, Suit::Club));
    cards.push_back(new Card(Rank::Seven, Suit::Club));
    cards.push_back(new Card(Rank::Eight, Suit::Club));
    cards.push_back(new Card(Rank::Nine, Suit::Diamond));

    Deck* deck = new Deck(cards);

    Card* cardAtTop = deck->getTopCard();

    EXPECT_EQ(cardAtTop->getRank(), Rank::Nine);
    EXPECT_EQ(cardAtTop->getSuit(), Suit::Diamond);

    delete deck;
}

TEST(TestDeck, RemoveTopCardTest) {
    std::vector<Card*> cards;
    cards.reserve(3);

    cards.push_back(new Card(Rank::Five, Suit::Club));
    cards.push_back(new Card(Rank::Six, Suit::Spade));
    cards.push_back(new Card(Rank::Seven, Suit::Heart));

    Deck* deck = new Deck(cards);

    EXPECT_EQ(deck->getSize(), 3);
    Card* cardAtTop1 = deck->removeTopCard();
    EXPECT_EQ(cardAtTop1->getRank(), Rank::Seven);
    EXPECT_EQ(cardAtTop1->getSuit(), Suit::Heart);

    EXPECT_EQ(deck->getSize(), 2);
    Card* cardAtTop2 = deck->getTopCard();
    EXPECT_EQ(cardAtTop2->getRank(), Rank::Six);
    EXPECT_EQ(cardAtTop2->getSuit(), Suit::Spade);

    EXPECT_EQ(deck->getSize(), 2);
    Card* cardAtTop3 = deck->removeTopCard();
    EXPECT_EQ(cardAtTop3->getRank(), Rank::Six);
    EXPECT_EQ(cardAtTop3->getSuit(), Suit::Spade);

    EXPECT_EQ(deck->getSize(), 1);
    Card* cardAtTop4 = deck->removeTopCard();
    EXPECT_EQ(cardAtTop4->getRank(), Rank::Five);
    EXPECT_EQ(cardAtTop4->getSuit(), Suit::Club);

    delete deck;
    delete cardAtTop1;
    delete cardAtTop3;
    delete cardAtTop4;
}

TEST(TestDeck, ShuffleCardTest) {
    std::vector<Card*> cards;
    for (int i = 1; i < 14; i++) {
        for (int j = 0; j < 4; j++) {
            Card* card = new Card((Rank)i, (Suit)j);
            cards.push_back(card);
        }
    }

    Deck* deck = new Deck(cards);

    Card* testCard = new Card(Rank(1), Suit(0));
    int differentCount = 0;

    for (int i = 0; i < 100; i++) {
        bool different;

        deck->shuffleCards();

        different = (deck->getTopCard()->getRank() != testCard->getRank()) &&
                    (deck->getTopCard()->getSuit() != testCard->getSuit());

        if (different)
            differentCount++;
    }

    EXPECT_GT(differentCount, 50);

    delete deck;
    delete testCard;
}

TEST(TestDeck, AddCardToDeckTest) {
    std::vector<Card*> cards;
    Deck* deck = new Deck(cards);

    EXPECT_EQ(deck->getSize(), 0);

    deck->addToDeck(new Card(Rank::Eight, Suit::Spade));
    EXPECT_EQ(deck->getSize(), 1);

    Card* cardAtTop = deck->getTopCard();
    EXPECT_TRUE(cardAtTop->isEight());

    deck->addToDeck(new Card(Rank::King, Suit::Diamond));
    EXPECT_EQ(deck->getSize(), 2);

    cardAtTop = deck->getTopCard();
    EXPECT_FALSE(cardAtTop->isEight());
    EXPECT_EQ(cardAtTop->getRank(), Rank::King);
    EXPECT_EQ(cardAtTop->getSuit(), Suit::Diamond);

    delete deck;
}

TEST(TestDeck, GetDeckSizeTest) {
    std::vector<Card*> cards(10);
    for (size_t i = 0; i < cards.size(); i++) {
        cards[i] = new Card(Rank::Eight, Suit::Diamond);
    }
    Deck* deck = new Deck(cards);

    int size = deck->getSize();

    EXPECT_EQ(size, 10);

    delete deck;
}

TEST(TestDeck, CreateDeckTest) {
    Deck* deck = new Deck();
    int size = deck->getSize();
    EXPECT_EQ(size, 0);

    deck->createPlayingDeck();
    size = deck->getSize();
    EXPECT_EQ(size, 52);

    delete deck;
}

