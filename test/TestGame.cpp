/**
 * @author Crazy-8 groups
 * @date 2023-02
*/

#ifndef TESTGAME_H
#define TESTGAME_H

#include <vector>
#include <string>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Game.h"
#include "Card.h"
#include "MockCard.h"
#include "MockDeck.h"
#include "MockHand.h"
#include "MockPlayer.h"
#include "MockViews.h"

using ::testing::Return;
using ::testing::_;
using ::testing::Expectation;
using ::testing::Sequence;

TEST(TestGame, TestPlayGame) {
    Human* human = new Human("Human", 1, new Hand());
    CI* ci = new CI("CI", 2, new Hand());
    CI* ci2 = new CI("CI", 3, new Hand());

    std::vector<Player*> players;
    players.push_back(human);
    players.push_back(ci);
    players.push_back(ci2);

    std::vector<Card*> playCards;
    for (int i = 0; i < 30; i++) {
        playCards.push_back(new Card(Rank(8), Suit(1)));
    }

    Deck* playing = new Deck(playCards);
    Deck* discard = new Deck();

    MockTurnUI turnUI;

    EXPECT_CALL(turnUI, getPlayerAction())
    .Times(9)
    .WillOnce(Return(Action::GetHelp))
    .WillOnce(Return(Action::SortHand))
    .WillOnce(Return(Action::DrawCard))
    .WillRepeatedly(Return(Action::PlayCard));

    EXPECT_CALL(turnUI, displayHelp())
    .Times(1);

    EXPECT_CALL(turnUI, displaySortHand())
    .Times(1);

    EXPECT_CALL(turnUI, displayHand())
    .Times(1);

    EXPECT_CALL(turnUI, display())
    .Times(6);

    EXPECT_CALL(turnUI, displayDrawCard())
    .Times(1);

    EXPECT_CALL(turnUI, getPlayedCardIndex())
    .Times(6)
    .WillOnce(Return(-1))
    .WillRepeatedly(Return(0));

    EXPECT_CALL(turnUI, invalidInput("Card not in hand. Try again"))
    .Times(1);

    EXPECT_CALL(turnUI, setCardSuitPrompt())
    .Times(5)
    .WillRepeatedly(Return(Suit::Heart));

    Game* game = new Game(players, playing, discard);
    game->setUI(&turnUI);

    Player* winningPlayer = game->playGame();

    EXPECT_EQ(winningPlayer, ci);
    EXPECT_EQ(human->getHand()->getHandSize(), 1);
    EXPECT_EQ(ci->getHand()->getHandSize(), 0);
    EXPECT_EQ(ci2->getHand()->getHandSize(), 1);

    delete game;
}

TEST(TestGame, TestPlayerTurn) {
    std::vector<Card*> playerCards;
    playerCards.push_back(new Card (Rank(1), Suit(1)));
    playerCards.push_back(new Card (Rank(2), Suit(1)));
    Hand* hand = new Hand(playerCards);
    Human* human = new Human("Human", 1, hand);

    std::vector<Player*> players;
    players.push_back(human);

    Deck* playing = new Deck();
    std::vector<Card*> dis;
    dis.push_back(new Card(Rank(2), Suit(2)));
    dis.push_back(new Card(Rank(2), Suit(2)));
    dis.push_back(new Card(Rank(2), Suit(2)));
    Deck* discard = new Deck(dis);

    MockTurnUI turnUI;

    EXPECT_CALL(turnUI, getPlayerAction())
    .Times(3)
    .WillOnce(Return(Action::PlayCard))
    .WillOnce(Return(Action::DrawCard))
    .WillOnce(Return(Action::QuitGame));

    EXPECT_CALL(turnUI, getPlayedCardIndex())
    .Times(1)
    .WillOnce(Return(0));

    EXPECT_CALL(turnUI, invalidInput("Not a match. Try again"))
    .Times(1);

    EXPECT_CALL(turnUI, displayDrawCard())
    .Times(1);

    EXPECT_CALL(turnUI, displaySwapDecks())
    .Times(1);

    EXPECT_CALL(turnUI, display())
    .Times(2);

    EXPECT_CALL(turnUI, displayQuit())
    .Times(1);

    Game* game = new Game(players, playing, discard);
    game->setUI(&turnUI);

    game->playHumanTurn();

    delete game;
}

// TEST(TestGame, DISABLED_TestEndGameObject) {
//     std::vector<Card*> playerCards;
//     Hand* hand = new Hand(playerCards);
//     Human* human = new Human("Human", 1, hand);

//     std::vector<Card*> playerCards1;
//     playerCards1.push_back(new Card (Rank(1), Suit(1)));
//     playerCards1.push_back(new Card (Rank(2), Suit(1)));
//     Hand* hand1 = new Hand(playerCards1);
//     Human* human1 = new Human("Human1", 2, hand1);

//     std::vector<Player*> players;
//     players.push_back(human);
//     players.push_back(human1);

//     Deck* playing = new Deck();
//     std::vector<Card*> dis;
//     dis.push_back(new Card(Rank(3), Suit(2)));
//     Deck* discard = new Deck(dis);

//     TurnUI turnUI(players[0], discard, playing);

//     Game* game = new Game(players, playing, discard);
//     game->setUI(&turnUI);

//     game->endGame(human);

//     delete game;
// }

TEST(TestGame, TestPlayerTurnSkip) {
    std::vector<Card*> playerCards;
    playerCards.push_back(new Card (Rank(1), Suit(1)));
    playerCards.push_back(new Card (Rank(2), Suit(1)));
    Hand* hand = new Hand(playerCards);
    Human* human = new Human("Human", 1, hand);

    std::vector<Player*> players;
    players.push_back(human);

    Deck* playing = new Deck();
    std::vector<Card*> dis;
    dis.push_back(new Card(Rank(3), Suit(2)));
    Deck* discard = new Deck(dis);

    MockTurnUI turnUI;

    EXPECT_CALL(turnUI, display())
    .Times(1);

    EXPECT_CALL(turnUI, getPlayerAction())
    .Times(1)
    .WillOnce(Return(Action::DrawCard));

    Game* game = new Game(players, playing, discard);
    game->setUI(&turnUI);

    game->playHumanTurn();

    delete game;
}

TEST(TestGame, TestCiTurnRank) {
    MockTurnUI turnUI;

    std::vector<Card*> playCards;
    playCards.push_back(new Card(Rank(1), Suit(1)));
    Hand* hand = new Hand(playCards);
    CI* ci = new CI("CI", 1, hand);

    std::vector<Player*> players;
    players.push_back(ci);

    Deck* playing = new Deck();

    std::vector<Card*> deckDisCards;
    Card* c1 = new Card(Rank(2), Suit(1));
    Card* c2 = new Card(Rank(3), Suit(1));
    Card* c3 = new Card(Rank(2), Suit(1));
    Card* c4 = new Card(Rank(2), Suit(1));
    Card* c5 = new Card(Rank(2), Suit(1));
    Card* d1 = new Card(Rank(3), Suit(1));
    deckDisCards.push_back(c5);
    deckDisCards.push_back(c4);
    deckDisCards.push_back(c3);
    deckDisCards.push_back(c2);
    deckDisCards.push_back(c1);
    deckDisCards.push_back(d1);
    Deck* discard = new Deck(deckDisCards);

    Game* game = new Game(players, playing, discard);
    game->setUI(&turnUI);

    EXPECT_CALL(turnUI, displaySwapDecks())
    .Times(1);

    game->playCITurn();

    EXPECT_EQ(ci->getHand()->getHandSize(), 4);
    EXPECT_EQ(discard->getSize(), 2);
    EXPECT_EQ(playing->getSize(), 1);

    delete game;
}

TEST(TestGame, TestCiTurnSuit) {
    MockTurnUI turnUI;

    std::vector<Card*> playCards;
    playCards.push_back(new Card(Rank(1), Suit(1)));
    Hand* hand = new Hand(playCards);
    CI* ci = new CI("CI", 1, hand);
    ci->setStrategy(CIStrategy::PlaySameSuit);

    std::vector<Player*> players;
    players.push_back(ci);

    Deck* playing = new Deck();

    std::vector<Card*> deckDisCards;
    Card* c1 = new Card(Rank(1), Suit(2));
    Card* c2 = new Card(Rank(1), Suit(3));
    Card* c3 = new Card(Rank(1), Suit(2));
    Card* c4 = new Card(Rank(1), Suit(2));
    Card* c5 = new Card(Rank(1), Suit(2));
    Card* d1 = new Card(Rank(1), Suit(3));
    deckDisCards.push_back(c5);
    deckDisCards.push_back(c4);
    deckDisCards.push_back(c3);
    deckDisCards.push_back(c2);
    deckDisCards.push_back(c1);
    deckDisCards.push_back(d1);
    Deck* discard = new Deck(deckDisCards);

    Game* game = new Game(players, playing, discard);
    game->setUI(&turnUI);

    EXPECT_CALL(turnUI, displaySwapDecks())
    .Times(1);

    game->playCITurn();

    EXPECT_EQ(ci->getHand()->getHandSize(), 4);
    EXPECT_EQ(discard->getSize(), 2);
    EXPECT_EQ(playing->getSize(), 1);

    delete game;
}

TEST(TestGame, TestEndGame) {
    std::vector<Player*> players;
    std::vector<Card*> playCards;
    playCards.push_back(new Card(Rank(1), Suit(1)));
    Hand* hand = new Hand(playCards);
    Player* player1 = new Player("Player", 1, hand);
    Deck* playing = new Deck();
    Deck* discard = new Deck();

    MockEndGameUI endGameUI;

    Game* game = new Game(players, playing, discard);
    game->setUI(&endGameUI);
    game->endGame(player1);
    delete game;
    delete player1;
}

TEST(TestGame, TestMatchCardsEight) {
    Card* card1 = new Card(Rank(8), Suit(2));
    Card* dis = new Card(Rank(2), Suit(1));

    Deck* discard = new Deck();
    discard->addToDeck(dis);
    Deck* playing = new Deck();
    std::vector<Player*> players;

    Game* game = new Game(players, playing, discard);

    EXPECT_TRUE(game->matchCards(card1));

    delete game;
    delete card1;
}

TEST(TestGame, TestMatchCardsRank) {
    Card* card1 = new Card(Rank(2), Suit(2));
    Card* dis = new Card(Rank(2), Suit(1));

    Deck* discard = new Deck();
    discard->addToDeck(dis);
    Deck* playing = new Deck();
    std::vector<Player*> players;

    Game* game = new Game(players, playing, discard);

    EXPECT_TRUE(game->matchCards(card1));

    delete game;
    delete card1;
}

TEST(TestGame, TestMatchCardsSuit) {
    Card* card1 = new Card(Rank(1), Suit(1));
    Card* dis = new Card(Rank(2), Suit(1));

    Deck* discard = new Deck();
    discard->addToDeck(dis);
    Deck* playing = new Deck();
    std::vector<Player*> players;

    Game* game = new Game(players, playing, discard);

    EXPECT_TRUE(game->matchCards(card1));

    delete game;
    delete card1;
}

TEST(TestGame, TestMatchCardsNoMatch) {
    Card* card1 = new Card(Rank(1), Suit(1));
    Card* dis = new Card(Rank(2), Suit(2));

    Deck* discard = new Deck();
    discard->addToDeck(dis);
    Deck* playing = new Deck();
    std::vector<Player*> players;

    Game* game = new Game(players, playing, discard);

    EXPECT_FALSE(game->matchCards(card1));

    delete game;
    delete card1;
}

TEST(TestGame, TestSwapDecks) {
    Deck* discard = new Deck();
    Card* card1 = new Card();
    discard->createPlayingDeck();
    discard->addToDeck(card1);

    Deck* playing = new Deck();
    std::vector<Player*> players;

    Game* game = new Game(players, playing, discard);

    EXPECT_EQ(discard->getSize(), 53);
    EXPECT_EQ(playing->getSize(), 0);
    game->swapDecks();
    EXPECT_EQ(discard->getSize(), 1);
    EXPECT_EQ(playing->getSize(), 52);
    Card* topCard = discard->removeTopCard();
    EXPECT_EQ(topCard, card1);

    delete topCard;
    delete game;
}

TEST(TestGame, TestDetermineWinnerNoPlays) {
    Card* card1 = new Card(Rank(1), Suit(1));
    std::vector<Card*> cards1;
    cards1.push_back(card1);
    Hand* p1Hand = new Hand(cards1);
    Player* p1 = new Player("P1", 1, p1Hand);

    Card* card2 = new Card(Rank(1), Suit(1));
    std::vector<Card*> cards2;
    cards2.push_back(card2);
    Hand* p2Hand = new Hand(cards2);
    CI* p2 = new CI("P2", 2, p2Hand);
    p2->setStrategy(CIStrategy::PlaySameSuit);

    Card* card3 = new Card(Rank(1), Suit(1));
    std::vector<Card*> cards3;
    cards3.push_back(card3);
    Hand* p3Hand = new Hand(cards3);
    CI* p3 = new CI("P3", 3, p3Hand);

    std::vector<Player*> players;
    players.push_back(p1);
    players.push_back(p2);
    players.push_back(p3);

    Deck* discard = new Deck();
    discard->addToDeck(new Card(Rank(2), Suit(2)));
    Deck* playing = new Deck();
    Game* game = new Game(players, playing, discard);

    EXPECT_EQ(game->determineWinner(), nullptr);

    delete game;
}

TEST(TestGame, TestDetermineWinner) {
    Card* card1 = new Card(Rank(1), Suit(1));
    std::vector<Card*> cards1;
    cards1.push_back(card1);
    Hand* p1Hand = new Hand(cards1);
    Player* p1 = new Player("P1", 1, p1Hand);

    Card* card2 = new Card(Rank(1), Suit(1));
    std::vector<Card*> cards2;
    cards2.push_back(card2);
    Hand* p2Hand = new Hand(cards2);
    Player* p2 = new Player("P2", 2, p2Hand);

    Hand* p3Hand = new Hand();
    Player* p3 = new Player("P3", 3, p3Hand);

    std::vector<Player*> players;
    players.push_back(p1);
    players.push_back(p2);
    players.push_back(p3);

    Deck* discard = new Deck();
    Deck* playing = new Deck();
    playing->createPlayingDeck();
    Game* game = new Game(players, playing, discard);

    EXPECT_EQ(game->determineWinner(), p3);
    EXPECT_TRUE(game->isGameOver());

    delete game;
}

TEST(TestGame, TestDetermineWinnerNoWinner) {
    Card* card1 = new Card(Rank(1), Suit(1));
    std::vector<Card*> cards1;
    cards1.push_back(card1);
    Hand* p1Hand = new Hand(cards1);
    Player* p1 = new Player("P1", 1, p1Hand);

    Card* card2 = new Card(Rank(1), Suit(1));
    std::vector<Card*> cards2;
    cards2.push_back(card2);
    Hand* p2Hand = new Hand(cards2);
    Player* p2 = new Player("P2", 2, p2Hand);

    Card* card3 = new Card(Rank(1), Suit(1));
    std::vector<Card*> cards3;
    cards3.push_back(card3);
    Hand* p3Hand = new Hand(cards3);
    Player* p3 = new Player("P3", 3, p3Hand);

    std::vector<Player*> players;
    players.push_back(p1);
    players.push_back(p2);
    players.push_back(p3);

    Deck* discard = new Deck();
    Deck* playing = new Deck();
    playing->createPlayingDeck();
    Game* game = new Game(players, playing, discard);

    EXPECT_EQ(game->determineWinner(), nullptr);
    EXPECT_FALSE(game->isGameOver());

    delete game;
}

TEST(TestGame, TestDealCardsTwoPlayers) {
    Hand* p1Hand = new Hand();
    Player* p1 = new Player("P1", 1, p1Hand);
    Hand* p2Hand = new Hand();
    Player* p2 = new Player("P2", 2, p2Hand);

    std::vector<Player*> players;
    players.push_back(p1);
    players.push_back(p2);

    Deck* discard = new Deck();
    Deck* playing = new Deck();
    playing->createPlayingDeck();
    Game* game = new Game(players, playing, discard);

    EXPECT_EQ(playing->getSize(), 52);
    EXPECT_TRUE(p1->getHand()->isEmpty());
    EXPECT_TRUE(p2->getHand()->isEmpty());

    game->dealCards();

    EXPECT_EQ(playing->getSize(), 37);
    EXPECT_EQ(p1->getHand()->getHandSize(), 7);
    EXPECT_EQ(p2->getHand()->getHandSize(), 7);
    EXPECT_EQ(discard->getSize(), 1);

    delete game;
}

TEST(TestGame, TestDealCardsThreePlayers) {
    Hand* p1Hand = new Hand();
    Player* p1 = new Player("P1", 1, p1Hand);
    Hand* p2Hand = new Hand();
    Player* p2 = new Player("P2", 2, p2Hand);
    Hand* p3Hand = new Hand();
    Player* p3 = new Player("P3", 3, p3Hand);

    std::vector<Player*> players;
    players.push_back(p1);
    players.push_back(p2);
    players.push_back(p3);

    Deck* discard = new Deck();
    Deck* playing = new Deck();
    playing->createPlayingDeck();
    Game* game = new Game(players, playing, discard);

    EXPECT_EQ(playing->getSize(), 52);
    EXPECT_TRUE(p1->getHand()->isEmpty());
    EXPECT_TRUE(p2->getHand()->isEmpty());
    EXPECT_TRUE(p3->getHand()->isEmpty());

    game->dealCards();

    EXPECT_EQ(playing->getSize(), 36);
    EXPECT_EQ(p1->getHand()->getHandSize(), 5);
    EXPECT_EQ(p2->getHand()->getHandSize(), 5);
    EXPECT_EQ(p3->getHand()->getHandSize(), 5);
    EXPECT_EQ(discard->getSize(), 1);

    delete game;
}

TEST(TestGame, TestCalculatePlayerScoreThreePlayers) {
    Card* card1 = new Card(Rank(5), Suit(1));
    Card* card2 = new Card(Rank(4), Suit(1));
    Card* card3 = new Card(Rank(1), Suit(1));
    std::vector<Card*> p1Cards;
    p1Cards.push_back(card1);
    p1Cards.push_back(card2);
    p1Cards.push_back(card3);
    Hand* p1Hand = new Hand(p1Cards);
    Player* p1 = new Player("P1", 1, p1Hand);

    Card* card4 = new Card(Rank(8), Suit(1));
    Card* card5 = new Card(Rank(10), Suit(1));
    Card* card6 = new Card(Rank(11), Suit(1));
    Card* card7 = new Card(Rank(12), Suit(1));
    std::vector<Card*> p2Cards;
    p2Cards.push_back(card4);
    p2Cards.push_back(card5);
    p2Cards.push_back(card6);
    p2Cards.push_back(card7);
    Hand* p2Hand = new Hand(p2Cards);
    Player* p2 = new Player("P2", 2, p2Hand);
    Hand* p3Hand = new Hand();
    Player* p3 = new Player("P3", 3, p3Hand);

    std::vector<Player*> players;
    players.push_back(p1);
    players.push_back(p2);
    players.push_back(p3);

    Deck* discard = new Deck();
    Deck* playing = new Deck();
    Game* game = new Game(players, playing, discard);

    EXPECT_EQ(p1->getScore(), 0);
    EXPECT_EQ(p2->getScore(), 0);
    EXPECT_EQ(p3->getScore(), 0);

    game->calculatePlayerScore(p3);

    EXPECT_EQ(p1->getScore(), 0);
    EXPECT_EQ(p2->getScore(), 0);
    EXPECT_EQ(p3->getScore(), 90);

    delete game;
}

#endif // TESTGAME_H
