/**
 * @author Crazy-8 groups
 * @date 2023-02
*/

#include <string>
#include "TurnUI.h"

using std::cout;
using std::endl;

TurnUI::TurnUI() {}

TurnUI::TurnUI(Player* player, Deck* discard, Deck* playing) {
    this->currentPlayer = player;
    this->discardDeck = discard;
    this->playingDeck = playing;
}

TurnUI::~TurnUI() {}

void TurnUI::display() {
    cout << endl << "PLAYER INFORMATION" << endl;
    displayHand();
    std::string rank;
    std::string suit;
    Card* c = discardDeck->getTopCard();

    if (c->getSuit() == 0) {
        suit = "Club";
    } else if (c->getSuit() == 1) {
        suit = "Spade";
    } else if (c->getSuit() == 2) {
        suit = "Heart";
    } else {
        suit = "Diamond";
    }

    if (c->getRank() == 1) {
        rank = "Ace";
    } else if (c->getRank() == 11) {
        rank = "Jack";
    } else if (c->getRank() == 12) {
        rank = "Queen";
    } else if (c->getRank() == 13) {
        rank = "King";
    } else {
        rank = std::to_string(c->getRank());
    }

    cout << "Discard Card: " << rank << " " << suit << endl << endl;
}

Action TurnUI::getPlayerAction() {
    int input;
    char quit;
    cout << "Enter the action you would like to do." << endl
         << "Enter '0' to play a card" << endl
         << "Enter '1' to draw a card" << endl
         << "Enter '2' to sort your hand" << endl
         << "Enter '3' to display the rules of the game." << endl
         << "Enter '4' to quit the game" << endl;

    do {
        while (!(std::cin >> input)) {
            cout << "Invalid Input. Try Again." << endl;
            std::cin.clear();
            std::cin.ignore(123, '\n');
        }
        if (input < 0 || input > 4) {
            cout << "Invalid Input. Try Again." << endl;
        }
        if (input == 4) {
            cout << "Are you sure you want to quit? (Y/N)" << endl;
            std::cin >> quit;
            if (quit == 'Y') {
                break;
            }
            cout << "Enter the action you would like to do." << endl;
            input = 5;
        }
    } while (input < 0 || input > 4);
    cout << endl;
    return Action(input);
}

void TurnUI::invalidInput(std::string error) {
    cout << error << endl << endl;
}

Suit TurnUI::setCardSuitPrompt() {
    int input;
    cout << "Enter the Suit you would like to change to." << endl
         << "Enter '0' for  Club." << endl
         << "Enter '1' for  Spade." << endl
         << "Enter '2' for  Heart." << endl
         << "Enter '3' for  Diamond." << endl;
    do {
        while (!(std::cin >> input)) {
            cout << "Invalid Input. Try Again." << endl;
            std::cin.clear();
            std::cin.ignore(123, '\n');
        }
        if (input != 0 && input != 1 && input != 2 && input != 3) {
            cout << "Invalid Input. Try Again." << endl;
            input = -1;
        }
    } while (input != 0 && input != 1 && input != 2 && input != 3);

    return Suit(input);
}

int TurnUI::getPlayedCardIndex() {
    int input;
    cout << "Which card would you like the play?" << endl;
    cout << "Enter the position of the card in the hand." << endl;
    cout << "First card position is '0', second card's position is '1'. etc."
    << endl;
    do {
        while (!(std::cin >> input)) {
            cout << "Invalid Input. Try Again." << endl;
            std::cin.clear();
            std::cin.ignore(123, '\n');
        }
        if (input < 0 || input > currentPlayer->getHand()->getHandSize() - 1)
            cout << "Invalid Input. Try Again." << endl << endl;
    } while (input < 0 || input > currentPlayer->getHand()->getHandSize() - 1);
    cout << endl;
    return input;
}

void TurnUI::displayQuit() {
    cout << "Quitting the game." << endl <<endl;
}

void TurnUI::displayDrawCard() {
    cout << "Drawing a card" << endl << endl;
}

void TurnUI::displaySwapDecks() {
    cout << "Swapping stock and discard piles" << endl << endl;
}

void TurnUI::displaySortHand() {
    cout << "Sorting the hand" << endl << endl;
}

void TurnUI::displayHand() {
    cout << "Current Hand: " << endl;
    Hand* playerHand = currentPlayer->getHand();
    std::string suit;
    std::string rank;
    int i = 0;
    for (Card* c : playerHand->getCards()) {
        if (c->getSuit() == 0) {
            suit = "Club";
        } else if (c->getSuit() == 1) {
            suit = "Spade";
        } else if (c->getSuit() == 2) {
            suit = "Heart";
        } else {
            suit = "Diamond";
        }

        if (c->getRank() == 1) {
            rank = "Ace";
        } else if (c->getRank() == 11) {
            rank = "Jack";
        } else if (c->getRank() == 12) {
            rank = "Queen";
        } else if (c->getRank() == 13) {
            rank = "King";
        } else {
            rank = std::to_string(c->getRank());
        }
        cout << i << ": " << rank << " " << suit << endl;
        i++;
    }
    cout << endl << endl;
}

void TurnUI::displayHelp() {
    cout << "Objective of the game:" << endl
              << "The goal is to be the first player to get rid of all the"
              << " cards in your hand." << endl;
    cout << "Card Values/Scoring:\n"
                << "Whoever wins, earns points based on the cards in the other"
                << " players hands." << endl
                << "Each Eight = 50 points\n"
                << "Each King, Queen, Jack or 10 = 10 points\n"
                << "Each Ace = 1 point\n"
                << "Each other card = their respective value in points\n"
                 << endl;
    cout << "Rules of the game:\n"
              << "If there are 2 players, both players get dealt a card face "
              << "down each rotation, up to 7.\n"
              << "If there are 3 or more players, each player get dealt a card"
              << " face down each rotation, up to 5.\n"
              << "The remaining cards becomes the stock pile. The top of the "
              << "card gets placed down and becomes the 'upcard' card. If the "
              << "card is an Eight, place it back into the stock pile and turn"
              << " the next top card.\n"
              << "PLAYER INSTRUCTIONS" << endl
              << "Every turn, the player can choose to place down one card of "
              << "the same suit or value, draw from the stockpile, or play an "
              << "Eight card. Placing down an Eight allows the player to "
              << "change the suit (optional).\n"
              << "If no card in the hand matches the current card, draw from "
              << "the stock pile until a value or suit matches the current "
              << "'upcard'.\n"
              << "If the player cannot play and the discard pile is empty "
              << "their turn is then skipped.\n"
              << "The turns keep going until a player runs out of cards. "
              << "When that happens, the player(s) with cards remaining total"
              << " the value of their card(s). \nThe player with no hands"
              << " remaining in their hand earns the points from the other"
              << " players cards."
              << endl << endl;
}

void TurnUI::setCurrentPlayer(Player* player) {
    currentPlayer = player;
}
