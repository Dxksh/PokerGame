#include "Hand.h"
#include <algorithm>
#include <iostream>

// Deals a hand of 5 cards to the player
void Hand::dealHand(Deck& deck) {
    for (int i = 0; i < 5; ++i) {
        cards.push_back(deck.dealCard());
    }
}

// Display hand of player
void Hand::displayHand() const {
    for (const auto& card : cards) {
        std::cout << card.getName() << " | ";
    }
}

// Sorts hand by value
void Hand::sortValue() {
    std::sort(cards.begin(), cards.end(), [](const Card& a, const Card& b) {
        return a.getValue() < b.getValue();
    });
}

// Sorts hand by group
void Hand::sortGroup() {
    std::sort(cards.begin(), cards.end(), [](const Card& a, const Card& b) {
        return a.getNumber() > b.getNumber();
    });
}

void Hand::setHand(const std::vector<int>& cardValues) {
    cards.clear();
    for (int value : cardValues) {
        int suit = value / 100;
        int cardValue = value % 100;
        cards.emplace_back(cardValue, static_cast<Suit>(suit - 1));
    }
}

// Swap player's chosen card(s) with a new card from the deck
void Hand::swapCard(const std::vector<int>& cardIndices, Deck& deck) {
    for (int index : cardIndices) {
        if (index >= 0 && index < 5) {
            cards[index] = deck.dealCard();
        }
    }
}

// Returns all cards in the hand
std::vector<Card> Hand::getCards() const {
    return cards;
}

// Returns card in requested position
Card Hand::getCard(int i) {
    return cards[i];
}

// Returns player's best hand category
std::string Hand::getBest() const {
    if (isStraightFlush()) {
        return "stfl";
    } else if (isFourOfAKind()) {
        return "four";
    } else if (isFullHouse()) {
        return "full";
    } else if (isFlush()) {
        return "flsh";
    } else if (isStraight()) {
        return "strt";
    } else if (isThreeOfAKind()) {
        return "trio";
    } else if (isTwoPair()) {
        return "twop";
    } else if (isOnePair()) {
        return "pair";
    } else {
        return "high";
    }
}

// Check if the hand is a straight flush
bool Hand::isStraightFlush() const {
    if (isFlush() && isStraight())
        return true;
    else
        return false;
}

// Check if the hand is four of a kind
bool Hand::isFourOfAKind() const {
    for (int i = 0; i < 2; ++i) {
        if (cards[i].getValue() == cards[i + 1].getValue() &&
            cards[i + 1].getValue() == cards[i + 2].getValue() &&
            cards[i + 2].getValue() == cards[i + 3].getValue()) {
            return true;
        }
    }
    return false;
}

// Check if the hand is a full house
bool Hand::isFullHouse() const {
    bool threeOfAKind = false;
    bool pair = false;

    // Check for three of a kind and a pair
    for (int i = 0; i < 3; ++i) {
        if (cards[i].getValue() == cards[i + 1].getValue() &&
            cards[i + 1].getValue() == cards[i + 2].getValue()) {
            threeOfAKind = true;
            i+=2;
            continue;
        } else if (cards[i].getValue() == cards[i + 1].getValue()) {
            pair = true;
        }
    }

    if(threeOfAKind && pair) {
        return true;
    }
    return false;
}

// Check if the hand is a flush
bool Hand::isFlush() const {
    Suit firstSuit = cards[0].getSuit();
    for (int i = 1; i < cards.size(); ++i) {
        if (cards[i].getSuit() != firstSuit) {
            return false;
        }
    }
    return true;
}

// Check if the hand is a straight
bool Hand::isStraight() const {
    // Check for special case: Ace, 2, 3, 4, 5
    if (cards[0].getValue() == 2 && cards[1].getValue() == 3 &&
        cards[2].getValue() == 4 && cards[3].getValue() == 5 &&
        cards[4].getValue() == 14) {
        return true;
    }

    // Check if the cards form a consecutive sequence
    for (int i = 1; i < cards.size(); ++i) {
        if (cards[i].getValue() != cards[i - 1].getValue() + 1) {
            return false;
        }
    }
    return true;
}

// Check if the hand is three of a kind
bool Hand::isThreeOfAKind() const {
    for (int i = 0; i < 3; ++i) {
        if (cards[i].getValue() == cards[i + 1].getValue() &&
            cards[i + 1].getValue() == cards[i + 2].getValue()) {
            return true;
        }
    }
    return false;
}

// Check if the hand is two pair
bool Hand::isTwoPair() const {
    int pairsCount = 0;

    // Count the number of pairs
    for (int i = 0; i < 4; ++i) {
        if (cards[i].getValue() == cards[i + 1].getValue()) {
            ++pairsCount;
            // Skip to the next pair
            ++i;
        }
    }

    // If two pairs are found, return true
    return pairsCount == 2;
}

// Check if the hand is one pair
bool Hand::isOnePair() const {
    // Check for three of a kind and a pair
    for (int i = 0; i < 4; ++i) {
        if (cards[i].getValue() == cards[i + 1].getValue()) {
            return true;
        }
    }
    return false;
}


