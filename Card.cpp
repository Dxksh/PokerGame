#include "Card.h"

// Initialise the playing card
Card::Card(int val, Suit st) : value(val), suit(st) {}

// Returns value of card
int Card::getValue() const {
    return value;
}

// Returns suit of card
Suit Card::getSuit() const {
    return suit;
}

// Returns the name of the card as a String
std::string Card::getName() const {
    std::string name;
    if (value >= 2 && value <= 10) {
        name = std::to_string(value);
    } else {
        switch (value) {
            case 11:
                name = "Jack";
                break;
            case 12:
                name = "Queen";
                break;
            case 13:
                name = "King";
                break;
            case 14:
                name = "Ace";
                break;
            default:
                break;
        }
    }
    switch (suit) {
        case Suit::CLUBS:
            name += " ♣";
            break;
        case Suit::DIAMONDS:
            name += " ♦";
            break;
        case Suit::HEARTS:
            name += " ♥";
            break;
        case Suit::SPADES:
            name += " ♠";
            break;
        default:
            break;
    }
    return name;
}

// Returns numerical value of card
int Card::getNumber() const {
    return static_cast<int>(suit) * 100 + value;
}
