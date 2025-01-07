// Minimal source file that allows the pipeline to pass.

#include <iostream>
#include "Game.h"
#include "Player.h"
#include "CI.h"
#include "Human.h"
#include "StartGameUI.h"
#include "TurnUI.h"

int main() {
    StartGameUI* ui = new StartGameUI();
    std::vector<Player*> players;
    Deck* discard = new Deck();
    Deck* draw = new Deck();
    draw->createPlayingDeck();
    draw->shuffleCards();
    ui->display();
    int playerNum = 1;

    for (int i = 0; i < ui->getNumHumanPlayers(); i++) {
        players.push_back(new Player("Player", playerNum, new Hand()));
        playerNum++;
    }

    for (int i = 0; i < ui->getNumCIPlayers(); i++) {
        CI* ci = new CI("CI", playerNum, new Hand());
        if (i % 2 == 0)
            ci->setStrategy(CIStrategy::PlaySameSuit);
        players.push_back(ci);
        playerNum++;
    }

    TurnUI* turn = new TurnUI(players[0], discard, draw);
    turn->displayHelp();

    Game* game = new Game(players, draw, discard);
    game->setUI(turn);

    game->endGame(game->playGame());

    delete ui;
    delete turn;
    delete game;
    return 0;
}
