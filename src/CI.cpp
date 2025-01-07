/**
 * @author Crazy-8 groups
 * @date 2023-02
*/

#include <string>
#include "CI.h"
#include "Hand.h"

CI::CI() {
    strategy = CIStrategy::PlaySameRank;
    setPlayerType(false);
}

CI::CI(std::string name, int playerNumber, Hand* hand):
    Player(name, playerNumber, hand) {
        strategy = CIStrategy::PlaySameRank;
        setPlayerType(false);
}

CI::~CI() {}

CIStrategy CI::getStrategy() {
    return strategy;
}

void CI::setStrategy(CIStrategy strat) {
    strategy = strat;
}
