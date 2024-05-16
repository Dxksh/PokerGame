#ifndef CARD_H
#define CARD_H

#include <string>

// Enum representing the suits of a standard deck of cards
enum class Suit { CLUBS, DIAMONDS, HEARTS, SPADES };

// Class representing a playing card
class Card {
private:
    int value;
    Suit suit;

public:
    // Constructor
    Card(int val, Suit st);

    // Getter methods
    int getValue() const;
    Suit getSuit() const;
    std::string getName() const;
    int getNumber() const;
};

#endif // CARD_H
