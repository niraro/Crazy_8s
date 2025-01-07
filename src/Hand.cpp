/**
 * @author Crazy-8 groups
 * @date 2023-02
*/

#include <algorithm>
#include <vector>
#include "Hand.h"

Hand::Hand() {
    handSize = 0;
    empty = true;
}

Hand::Hand(std::vector<Card*> cards) {
    for (Card* c : cards) {
        cardsInHand.push_back(c);
    }
}

Hand::~Hand() {
    for (Card* c : cardsInHand) {
        delete c;
    }
}

std::vector<Card*> Hand::getCards() {
  return cardsInHand;
}

void Hand::addToHand(Card* card) {
    cardsInHand.push_back(card);
}

Card* Hand::removeFromHand(int cardIndex) {
    if (cardIndex > cardsInHand.size() - 1 || cardIndex < 0)
        return nullptr;
    Card* card = cardsInHand.at(cardIndex);
    cardsInHand.erase(cardsInHand.begin() + cardIndex);
    return card;
}

bool compare(Card* first, Card* second) {
    return (first->getRank() < second->getRank());
}

void Hand::sortHand() {
    std::sort(cardsInHand.begin(), cardsInHand.end(), compare);
}

bool Hand::isEmpty() {
    return cardsInHand.empty();
}

int Hand::getHandSize() {
    return cardsInHand.size();
}

int Hand::findCard(Rank rank) {
    int i = 0;
    for (Card* c : cardsInHand) {
        if (c->getRank() == rank)
            return i;
        i++;
    }
    return -1;
}

int Hand::findCard(Suit suit) {
    int i = 0;
    for (Card* c : cardsInHand) {
        if (c->getSuit() == suit)
            return i;
        i++;
    }
    return -1;
}

Card* Hand::getFromHand(int cardIndex) {
    return cardsInHand[cardIndex];
}
