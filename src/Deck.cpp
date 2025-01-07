/**
 * @author Crazy-8 groups
 * @date 2023-02
*/

#include <vector>
#include <algorithm>
#include <random>
#include "Deck.h"

Deck::Deck() {}

Deck::Deck(std::vector<Card*> cards) {
  for (Card* c : cards) {
    deckCards.push_back(c);
  }
}

Deck::~Deck() {
  for (int i = 0; i < deckCards.size(); i++) {
    delete deckCards[i];
  }
}

Card* Deck::getTopCard() {
  return deckCards.back();
}

void Deck::shuffleCards() {
  std::random_device rd;
  auto rng = std::default_random_engine {rd()};
  std::shuffle(this->deckCards.begin(), this->deckCards.end(), rng);
}

void Deck::addToDeck(Card* card) {
  deckCards.push_back(card);
}

Card* Deck::removeTopCard() {
  Card* card = deckCards.back();
  deckCards.pop_back();
  return card;
}

int Deck::getSize() {
  return deckCards.size();
}

void Deck::createPlayingDeck() {
  deckCards.clear();
  for (int rank = 1; rank < 14; rank++) {
    for (int suit = 0; suit < 4; suit++) {
      deckCards.push_back(new Card(Rank(rank), Suit(suit)));
    }
  }
}
