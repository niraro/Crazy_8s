/**
 * @author Crazy-8 groups
 * @date 2023-02
*/

#include <string>
#include "StartGameUI.h"

using std::cout;
using std::endl;

StartGameUI::StartGameUI() {}

void StartGameUI::display() {
    int human;
    int ci;

    cout << "Welcome to Crazy Eights"<< endl << endl;
    cout << "Enter the number of human players. (Max: 4)" << endl;
    while (!(std::cin >> human)) {
        cout << "Invalid Input. Try Again." << endl;
        std::cin.clear();
        std::cin.ignore(123, '\n');
    }
    if (human <= 0) {
        cout << "Invalid Input. Setting number of human players to 1." << endl;
        human = 1;
    }
    if (human > 4) {
        cout << "Invalid Input. Setting number of human players to 4." << endl;
        human = 4;
    }
    numHumanPlayers = human;
    cout << endl;

    cout << "Enter the number of computer players. (Max: 2)" << endl;
    while (!(std::cin >> ci)) {
        cout << "Invalid Input. Try Again." << endl;
        std::cin.clear();
        std::cin.ignore(123, '\n');
    }
    if (ci <= 0 && human == 1) {
        cout << "Cannot have 1 human and 0 computer players." << endl;
        cout << "Setting the number of computer players to 2." << endl << endl;
        ci = 2;
    }
    if (ci <= 0) {
        cout << "Invalid Input. Setting number of computer players to 0."
        << endl;
        ci = 0;
    }
    if (ci > 2) {
        cout << "Invalid Input. Setting number of computer players to 2."
        << endl;
        ci = 2;
    }
    numCIPlayers = ci;
    cout << endl;
}

int StartGameUI::getNumCIPlayers() {
    return numCIPlayers;
}

int StartGameUI::getNumHumanPlayers() {
    return numHumanPlayers;
}
