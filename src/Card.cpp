/**
 * @author Crazy-8 groups
 * @date 2023-02
*/


#include "Card.h"

Card::Card() {
    rank = Rank::Ace;
    suit = Suit::Club;
}

Card::Card(Rank cardRank, Suit cardSuit): suit{cardSuit}, rank{cardRank} {}

Card::~Card() {}

Rank Card::getRank() {
    return rank;
}

Suit Card::getSuit() {
    return suit;
}

void Card::setSuit(Suit cardSuit) {
    suit = cardSuit;
}

bool Card::isEight() {
    if (rank == Rank::Eight)
        return true;
    else
        return false;
}

int Card::getScore() {
    if (rank == Rank::Jack || rank == Rank::Queen || rank == Rank::King)
        return 10;
    else if (rank == Rank::Eight)
        return 50;
    else
        return rank;
}
