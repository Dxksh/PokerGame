#ifndef GAME_H
#define GAME_H

#include "Player.h"

// Class representing the game
class Game {
private:
    Player player;
    Player computer;
    int rounds;

public:
    // Constructor
    Game(const std::string& playerName);

    // Game functions
    void startGame();
    void endGame();
    void determineRoundWinner();
    void determineCategoryWinner(const std::string& playerCategory, const std::string& computerCategory);
    void determineValueWinner(const Hand& playerHand, const Hand& computerHand, std::string playerCategory);
    void swapCards(Hand &playerHand, Deck &deck);
    void displayScores();
    std::string categoryToText(std::string category);

};

#endif // GAME_H
