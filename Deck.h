#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>

// Class representing a deck of 52 playing cards
class Deck {
private:
    std::vector<Card> cards;

public:
    // Constructor
    Deck();

    // Deck functions
    void createDeck();
    void displayDeck();
    void clearDeck();
    void shuffle();

    // Card functions
    Card dealCard();
    void addCard(const Card &card);
};

#endif // DECK_H
