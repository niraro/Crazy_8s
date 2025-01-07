/**
 * @author Crazy-8 groups
 * @date 2023-02
*/

#include <iostream>
#include <typeinfo>
#include "Game.h"
#include "Player.h"
#include "CI.h"
#include "EndGameUI.h"
#include "StartGameUI.h"
#include "TurnUI.h"

const int CARDS_TWO_PLAYERS = 7;
const int CARDS_THREE_OR_MORE_PLAYERS = 5;
bool QUIT = false;

Game::Game(std::vector<Player*> players, Deck* playing, Deck* discard) :
gamePlayers{players}, playingDeck{playing}, discardDeck{discard} {
    if (players.size() != 0)
        currentPlayer = players[0];
}

Game::~Game() {
    for (Player* p : gamePlayers) {
        delete p;
    }
    delete playingDeck;
    delete discardDeck;
}

void Game::setUI(UI* ui) {
    currentUI = ui;
}

Player* Game::playGame() {
    dealCards();
    bool gameOver = false;
    do {
        for (std::vector<Player*>::iterator player = gamePlayers.begin();
        player != gamePlayers.end(); ++player) {
            currentPlayer = (*player);
            bool human = (*player)->isHumanPlayer();
            if (human) {
                playHumanTurn();
            } else {
                playCITurn();
            }
            if (isGameOver()) {
                gameOver = true;
                break;
            }
            if (QUIT) {
                return nullptr;
            }
            std::cout << "Press Enter to Continue... " << std::endl;
            std::cin.get();
        }
    } while (!gameOver);

    Player* winningPlayer = determineWinner();
    return winningPlayer;
}

void Game::endGame(Player* winningPlayer) {
    if (winningPlayer == nullptr) {
        std::cout << "Game finished, no one won the game." << std::endl
        << std::endl;
    } else {
        EndGameUI endGameUI;
        calculatePlayerScore(winningPlayer);
        endGameUI.display(gamePlayers, winningPlayer);
    }
}

void Game::playHumanTurn() {
    Hand* playerHand = currentPlayer->getHand();
    TurnUI* turnUI = static_cast<TurnUI*>(currentUI);
    turnUI->setCurrentPlayer(currentPlayer);
    turnUI->display();

    bool cardPlayed = false;
    bool discardEmpty = false;
    bool cantPlay = false;
    do {
        Action playerAction = turnUI->getPlayerAction();

        //Checking if the player cant play a card.
        if ((playerHand->findCard(discardDeck->getTopCard()->getSuit()) < 0) &&
            (playerHand->findCard(discardDeck->getTopCard()->getRank()) < 0)) {
            cantPlay = true;
        }

        if (playerAction == Action::PlayCard) {
            int cardIndex = turnUI->getPlayedCardIndex();
            Card* playerCard = playerHand->removeFromHand(cardIndex);

            if (playerCard == nullptr) {
                turnUI->invalidInput("Card not in hand. Try again");
            } else if (!matchCards(playerCard)) {
                turnUI->invalidInput("Not a match. Try again");
                playerHand->addToHand(playerCard);
            } else {
                discardDeck->addToDeck(playerCard);

                if (playerCard->isEight()) {
                    Suit newSuit = turnUI->setCardSuitPrompt();
                    playerCard->setSuit(newSuit);
                }
                cardPlayed = true;
            }
        } else if (playerAction == Action::DrawCard) {
            if (playingDeck->getSize() == 0 &&
                discardDeck->getSize() <= 1) {
                    std::cout << "You cannot draw. Discard is empty."
                    << std::endl;
                    discardEmpty = true;
            } else {
                turnUI->displayDrawCard();
                if (playingDeck->getSize() == 0) {
                    turnUI->displaySwapDecks();
                    swapDecks();
                }
                Card* drawnCard = playingDeck->removeTopCard();
                playerHand->addToHand(drawnCard);

                turnUI->display();
            }
        } else if (playerAction == Action::SortHand) {
            turnUI->displaySortHand();
            playerHand->sortHand();
            turnUI->displayHand();
        } else if (playerAction == Action::GetHelp) {
            turnUI->displayHelp();
        } else {
            turnUI->displayQuit();
            QUIT = true;
            break;
        }

        if (discardEmpty && cantPlay) {
            std::cout << "You cannot play or draw. Skip turn" << std::endl;
            break;
        }
    } while (!cardPlayed);
}

void Game::playCITurn() {
    CIStrategy strategy = static_cast<CI*>(currentPlayer)->getStrategy();
    TurnUI* turnUI = static_cast<TurnUI*>(currentUI);

    Hand* hand = currentPlayer->getHand();
    Card* topDiscardPileCard = discardDeck->getTopCard();
    int cardToPlayIndex;

    if (strategy == CIStrategy::PlaySameRank) {
        Rank topDiscardCardRank = topDiscardPileCard->getRank();
        cardToPlayIndex = hand->findCard(topDiscardCardRank);

        if (cardToPlayIndex < 0) {
            bool foundAfterDraw = false;
            do {
                if (playingDeck->getSize() == 0 &&
                    discardDeck->getSize() <= 1) {
                        std::cout << "Computer "
                        << currentPlayer->getPlayerNumber()
                        << " cannot play or draw. Skip turn"
                        << std::endl;
                        return;
                }
                if (playingDeck->getSize() == 0) {
                    turnUI->displaySwapDecks();
                    swapDecks();
                }
                Card* drawnCard = playingDeck->removeTopCard();
                hand->addToHand(drawnCard);

                if (drawnCard->getRank() == topDiscardCardRank) {
                    foundAfterDraw = true;
                    cardToPlayIndex = hand->findCard(topDiscardCardRank);
                }
            } while (!foundAfterDraw);
        }
    } else {
        Suit topDiscardCardSuit = topDiscardPileCard->getSuit();
        cardToPlayIndex = hand->findCard(topDiscardCardSuit);

        if (cardToPlayIndex < 0) {
            bool foundAfterDraw = false;
            do {
                if (playingDeck->getSize() == 0 &&
                    discardDeck->getSize() <= 1) {
                        std::cout << "Computer "
                        << currentPlayer->getPlayerNumber()
                        << " cannot play or draw. Skip turn"
                        << std::endl;
                        return;
                }
                if (playingDeck->getSize() == 0) {
                    turnUI->displaySwapDecks();
                    swapDecks();
                }
                Card* drawnCard = playingDeck->removeTopCard();
                hand->addToHand(drawnCard);

                if (drawnCard->getSuit() == topDiscardCardSuit) {
                    foundAfterDraw = true;
                    cardToPlayIndex = hand->findCard(topDiscardCardSuit);
                }
            } while (!foundAfterDraw);
        }
    }

    Card* cardToPlay = hand->removeFromHand(cardToPlayIndex);
    discardDeck->addToDeck(cardToPlay);

    std::string rank;
    std::string suit;
    if (cardToPlay->getSuit() == 0) {
        suit = "Club";
    } else if (cardToPlay->getSuit() == 1) {
        suit = "Spade";
    } else if (cardToPlay->getSuit() == 2) {
        suit = "Heart";
    } else {
        suit = "Diamond";
    }
    if (cardToPlay->getRank() == 1) {
        rank = "Ace";
    } else if (cardToPlay->getRank() == 11) {
        rank = "Jack";
    } else if (cardToPlay->getRank() == 12) {
        rank = "Queen";
    } else if (cardToPlay->getRank() == 13) {
        rank = "King";
    } else {
        rank = std::to_string(cardToPlay->getRank());
    }
    std::cout << "Computer " << currentPlayer->getPlayerNumber()
    << " Played: " << rank << " " << suit
    << std::endl << std::endl;
}

bool Game::matchCards(Card* playerCard) {
    Card* discardPileTopCard = discardDeck->getTopCard();

    if (playerCard->isEight() ||
        playerCard->getRank() == discardPileTopCard->getRank() ||
        playerCard->getSuit() == discardPileTopCard->getSuit()) {
        return true;
    }
    return false;
}

void Game::swapDecks() {
    if (playingDeck->getSize() == 0 &&
        discardDeck->getSize() > 1) {
        Card* previousTopCard = discardDeck->removeTopCard();

        int numCards = discardDeck->getSize();
        for (int i = 0; i < numCards; i++) {
            Card* card = discardDeck->removeTopCard();
            playingDeck->addToDeck(card);
        }
        discardDeck->addToDeck(previousTopCard);
    } else {
        std::cout << "Draw and Discard piles empty." << std::endl << std::endl;
    }
}

bool Game::isGameOver() {
    Player* winningPlayer = determineWinner();

    if (winningPlayer == nullptr) {
        return false;
    }

    return true;
}

Player* Game::determineWinner() {
    std::vector<bool> playerCantPlay;
    for (std::vector<Player*>::iterator player = gamePlayers.begin();
        player != gamePlayers.end(); ++player) {
        Hand* playerHand = (*player)->getHand();

        if (playerHand->isEmpty()) {
            return (*player);
        }

        if (discardDeck->getSize() == 1) {
            Card* discard = discardDeck->getTopCard();
            if ((*player)->isHumanPlayer()) {
                if (playingDeck->getSize() == 0 &&
                    discardDeck->getSize() <= 1 &&
                    (playerHand->findCard(discard->getSuit()) < 0) &&
                    (playerHand->findCard(discard->getRank()) < 0)) {
                        playerCantPlay.push_back(true);
                } else {
                    playerCantPlay.push_back(false);
                }
            } else {
                CIStrategy strategy =
                static_cast<CI*>((*player))->getStrategy();
                if (strategy == CIStrategy::PlaySameRank) {
                    if (playingDeck->getSize() == 0 &&
                    discardDeck->getSize() <= 1 &&
                    (playerHand->findCard(discard->getRank()) < 0)) {
                        playerCantPlay.push_back(true);
                    } else {
                        playerCantPlay.push_back(false);
                    }
                } else {
                    if (playingDeck->getSize() == 0 &&
                    discardDeck->getSize() <= 1 &&
                    (playerHand->findCard(discard->getSuit()) < 0)) {
                        playerCantPlay.push_back(true);
                    } else {
                        playerCantPlay.push_back(false);
                    }
                }
            }
        }
    }

    for (int i = 0; i < playerCantPlay.size(); i++) {
        if (playerCantPlay[i] == false) {
            break;
        }
        if (i + 1 == playerCantPlay.size()) {
            std::cout << "All players cannot draw or play." << std::endl;
            QUIT = true;
        }
    }
    return nullptr;
}

void Game::dealCards() {
    int numPlayers = gamePlayers.size();
    int cardsPerPlayer = numPlayers == 2 ?
    CARDS_TWO_PLAYERS : CARDS_THREE_OR_MORE_PLAYERS;

    playingDeck->shuffleCards();

    for (int i = 0; i < cardsPerPlayer; i++) {
        for (int j = 0; j < numPlayers; j++) {
            currentPlayer = gamePlayers[j];
            Hand* playerHand = currentPlayer->getHand();
            if (playingDeck->getSize() > 1) {
                Card* drawnCard = playingDeck->removeTopCard();
                playerHand->addToHand(drawnCard);
            }
        }
    }

    Card* drawnCard = playingDeck->removeTopCard();
    if (drawnCard->getRank() == 8) {
        Card* drawnCard2 = playingDeck->removeTopCard();
        playingDeck->addToDeck(drawnCard);
        discardDeck->addToDeck(drawnCard2);
    } else {
        discardDeck->addToDeck(drawnCard);
    }
}

void Game::calculatePlayerScore(Player* winningPlayer) {
    int winningScore = 0;

    for (Player* player : gamePlayers) {
            if (player->getPlayerNumber() !=
                winningPlayer->getPlayerNumber()) {
                Hand* playerHand = player->getHand();

                std::vector<Card*> cardsInHand = playerHand->getCards();

                for (size_t i = 0; i < cardsInHand.size(); i++) {
                    Card* card = cardsInHand[i];
                    winningScore += card->getScore();
                }
            }
    }
    winningPlayer->setScore(winningScore);
}
