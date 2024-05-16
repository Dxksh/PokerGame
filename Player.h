#ifndef PLAYER_H
#define PLAYER_H

#include "Hand.h"
#include <string>

// Class representing the player (user/computer)
class Player {
private:
    std::string name;
    int score;
    Hand hand;

public:
    // Constructor
    Player(const std::string& n);

    // Getter methods
    std::string getName();
    Hand& getHand();
    int getScore() const;

    // Hand functions
    void dealHand(Deck& deck);
    void displayHand() const;

    void incrementScore();
};

#endif // PLAYER_H
