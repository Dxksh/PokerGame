#include "Deck.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <stdexcept>

// Constructor to crate and shuffle a new deck of cards
Deck::Deck() {
    createDeck();
    shuffle();
}

// Creates a deck of cards
void Deck::createDeck() {
    for (int val = 2; val <= 14; ++val) {
        for (int st = 0; st < 4; ++st) {
            cards.emplace_back(val, static_cast<Suit>(st));
        }
    }
}

// Shuffles the deck of cards
void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

// Deals a card from the deck
Card Deck::dealCard() {
    /*if (cards.empty()) {
        createDeck();
        shuffle();
    }*/
    if (cards.empty()) {
        throw std::logic_error("Empty deck");
    }
    Card topCard = cards.back();
    cards.pop_back();
    return topCard;
}

// Displays the deck (for debugging purposes)
void Deck::displayDeck() {
    std::cout << "Current contents of the deck:" << std::endl;
    for (const Card& card : cards) {
        std::cout << card.getName() << std::endl;
    }
}

// Clears deck for reshuffling
void Deck::clearDeck() {
    cards.clear();
}

// Add card to the deck
void Deck::addCard(const Card &card) {
    cards.insert(cards.begin(), card);
}
