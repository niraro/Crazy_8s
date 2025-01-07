/**
 * @author Crazy-8 groups
 * @date 2023-02
*/

#include <iostream>
#include "EndGameUI.h"

using std::cout;
using std::endl;

EndGameUI::EndGameUI() {}

EndGameUI::~EndGameUI() {}

void EndGameUI::display(std::vector<Player*> players, Player* player) {
    cout << "Game Over" << endl;
    displayScores(players);
    displayWinner(player);
}

void EndGameUI::displayScores(std::vector<Player*> players) {
    cout << endl;
    cout << "Player Points" << endl;
    for (Player* p : players) {
        cout << p->getName() << " " << p->getPlayerNumber() << ": "
        << p->getScore() << endl;
    }
}

void EndGameUI::displayWinner(Player* player) {
    cout << endl;
    cout << "Winner of the game!" << endl;
    cout << player->getName() << " " << player->getPlayerNumber()
    << " won with a score of: " << player->getScore() << endl;
    cout << endl << "Thanks for Playing" << endl;
}
