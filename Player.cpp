#include "Player.h"
#include <iostream>

// Constructor to initialise player
Player::Player(const std::string& n) : name(n), score(0) {}

// Deal a hand of 5 cards to player and sort them by value by default
void Player::dealHand(Deck& deck) {
    hand = Hand();
    hand.dealHand(deck);
    hand.sortValue();
}

// Display player's hand
void Player::displayHand() const {
    std::cout << name << "'s hand:" << std::endl;
    hand.displayHand();
    std::cout << std::endl;
}

// Get player's name
std::string Player::getName() {
    return name;
}

// Get player's hand
Hand& Player::getHand() {
    return hand;
}

// Get player's score
int Player::getScore() const {
    return score;
}

// Increment player's score
void Player::incrementScore() {
    ++score;
}

