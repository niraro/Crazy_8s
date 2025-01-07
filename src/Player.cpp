/**
 * @author Crazy-8 groups
 * @date 2023-02
*/


#include <string>
#include "Player.h"
#include "Hand.h"

Player::Player() {
  name = "";
  score = 0;
  playerHand = nullptr;
  humanPlayer = true;
}

Player::Player(std::string pName, int pNumber, Hand* pHand) : name{pName},
playerNumber{pNumber}, playerHand{pHand} {
  score = 0;
  humanPlayer = true;
}

Player::~Player() {
  if (playerHand != nullptr)
    delete playerHand;
}

Hand* Player::getHand() {
  return playerHand;
}

int Player::getScore() {
  return score;
}

std::string Player::getName() {
  return name;
}

void Player::setScore(int set) {
  score = set;
}

int Player::getPlayerNumber() {
  return playerNumber;
}

void Player::setPlayerType(bool human) {
  humanPlayer = human;
}

bool Player::isHumanPlayer() {
  return humanPlayer;
}
