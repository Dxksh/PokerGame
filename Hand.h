#ifndef HAND_H
#define HAND_H

#include "Deck.h"
#include "Card.h"
#include <vector>

// Class representing a hand of playing cards
class Hand {
private:
    std::vector<Card> cards;    // Card vector storing cards in the hand

public:

    // Hand functions
    void dealHand(Deck& deck);
    void displayHand() const;
    void setHand(const std::vector<int>& cardValues);
    void swapCard(const std::vector<int>& cardIndices, Deck& deck);

    // Sort cards
    void sortValue();
    void sortGroup();

    // Getter methods
    Card getCard(int i);
    std::vector<Card> getCards() const;
    std::string getBest() const;

    // Category checkers
    bool isStraightFlush() const;
    bool isFourOfAKind() const;
    bool isFullHouse() const;
    bool isFlush() const;
    bool isStraight() const;
    bool isThreeOfAKind() const;
    bool isTwoPair() const;
    bool isOnePair() const;
};

#endif // HAND_H
