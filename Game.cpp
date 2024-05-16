#include "Game.h"
#include "Deck.h"
#include <iostream>
#include <map>

// Constructor to initialise game class
Game::Game(const std::string& playerName) : player(playerName), computer("Computer"), rounds(5) {}

// Start game loop
void Game::startGame() {
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "Welcome to the Poker Game!" << std::endl;
    std::cout << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;

    Deck deck;
    int round = 1;
    std::string userChoice = "";

    // Store references to player and computer's hand
    Hand& playerHand = player.getHand();
    Hand& computerHand = computer.getHand();

    std::cout << std::endl;
    std::cout << player.getName() <<  ", please type 'start' when you are ready to begin.." << std::endl;
    std::cin >> userChoice;

    // Validate input
    while (userChoice != "start") {
        if (userChoice == "quit") {
            endGame();
            exit(0);
        }
        else {
            std::cout << player.getName() <<  ", please type 'start' when you are ready to begin.." << std::endl;
            std::cin >> userChoice;
        }
    }
    std::cout << std::endl;

    // Game loop starts
    while(userChoice == "start" || userChoice == "next") {
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << std::endl;
        std::cout << "Round " << round << std::endl;
        displayScores();
        std::cout << std::endl;

        // Deal hands and display player's hand
        player.dealHand(deck);
        computer.dealHand(deck);
        player.displayHand();

        // Player card swapping
        std::string swapChoice = "";
        std::cout << std::endl;

        // Allow swaps except for during every 5th round
        if (round % 5 != 0) {
            std::cout << "Would you like to swap any cards? (y/n)" << std::endl;
            std::cin >> swapChoice;

            // Validate input
            while (swapChoice != "y" && swapChoice != "n") {
                std::cout << "Invalid input. Please try again. Choices -> (y/n)" << std::endl;
                std::cin >> swapChoice;
            }

            if (swapChoice == "y") {
                // Swap cards
                swapCards(playerHand, deck);
            }
            else if (swapChoice == "n") {
                // Skip swapping
                std::cout << std::endl;
            }

            // Display player's hand again after swapping
            player.displayHand(); std::cout << std::endl;
        }
        else {
            // Output a no swapping message every 5th round
            std::cout << "Not enough cards in the deck. There will be no swapping in this round." << std::endl;
            std::cout << std::endl;
        }

        // Display computer's hand after swaps have been completed and determine round winner
        computer.displayHand();
        determineRoundWinner();

        // Check if it is the 5th round of the game (and multiples of 5) for reshuffling
        if (round % 5 == 0) {
            std::cout << std::endl;
            std::cout << "We have now reached the end of Round " << round << ". There are not enough cards remaining in the deck." << std::endl;
            std::cout << std::endl;
            std::cout << "If you want to keep playing, type 'next' to reshuffle the deck and continue to the next round." << std::endl;
            std::cout << "Or if you want to see the final scores, type 'quit'." << std::endl;

            std::cin >> userChoice;

            // Validate input
            while (userChoice != "next" && userChoice != "quit") {
                std::cout << "Invalid input. Please try again. Choices -> (next/quit)" << std::endl;
                std::cin >> userChoice;
            }

            if (userChoice == "next") {
                // Reshuffle deck and continue the game
                deck.clearDeck();
                deck.createDeck();
                deck.shuffle();
                ++round;
                continue;
            }
            else if (userChoice == "quit") {
                // Trigger end game phase
                endGame();
                break;
            }
        }

        ++round;
        std::cout << std::endl;
        std::cout << "Ready for next round? \nType 'next' if yes or type 'quit' if you want to end the game: " << std::endl;
        std::cin >> userChoice;

        // Validate input
        while (userChoice != "next" && userChoice != "quit") {
            std::cout << "Invalid input. Please try again. Choices -> (next/quit)" << std::endl;
            std::cin >> userChoice;
        }

        if(userChoice == "next") {
            // Continue to next round
            continue;
        }
        else if (userChoice == "quit") {
            // Trigger end game phase
            endGame();
        }
    }
}

// Determine winner of current round
void Game::determineRoundWinner() {
    // Get hands of player and computer
    Hand& playerHand = player.getHand();
    Hand& computerHand = computer.getHand();

    // Get the best hand categories of both hands
    std::string playerCategory = playerHand.getBest();
    std::string computerCategory = computerHand.getBest();

    // Output the category of each hand
    std::cout << std::endl;
    std::cout << "You have a: " << categoryToText(playerCategory) << std::endl;
    std::cout << "Computer has a: " << categoryToText(computerCategory) << std::endl;
    std::cout << std::endl;

    // Compare the categories
    if (playerCategory != computerCategory) {
        // If categories are different, determine the winner based on category
        determineCategoryWinner(playerCategory, computerCategory);
    } else {
        // If categories are the same, compare the hands based on values
        determineValueWinner(playerHand, computerHand, playerCategory);
    }
}

// Determine the winner based on category
void Game::determineCategoryWinner(const std::string& playerCategory, const std::string& computerCategory) {
    // Map of categories to their ranks
    std::map<std::string, int> categoryRanks = {
            {"stfl", 1}, {"four", 2}, {"full", 3}, {"flsh", 4}, {"strt", 5},
            {"trio", 6}, {"twop", 7}, {"pair", 8}, {"high", 9}
    };

    // Compare the ranks of the categories
    int playerRank = categoryRanks[playerCategory];
    int computerRank = categoryRanks[computerCategory];

    // Determine the winner based on ranks
    if (playerRank < computerRank) {
        std::cout << "You win the round!" << std::endl;
        player.incrementScore();
    } else if (playerRank > computerRank) {
        std::cout << "Computer wins the round!" << std::endl;
        computer.incrementScore();
    } else {
        std::cout << "It's a draw!" << std::endl;
    }
}

// Determine the winner based on hand values
void Game::determineValueWinner(const Hand& playerHand, const Hand& computerHand, std::string playerCategory) {

    std::cout << "Both you and the computer have a " << categoryToText(playerCategory) << "." << std::endl;

    // Get cards of both player and computer's hands
    std::vector<Card> playerCards = playerHand.getCards();
    std::vector<Card> computerCards = computerHand.getCards();

    // Straight flush
    if (playerCategory == "stfl") {
        if (playerCards[4].getValue() > computerCards[4].getValue()) {
            std::cout << "You win the round with a high card!" << std::endl;
            player.incrementScore();
        }
        else if (computerCards[4].getValue() > playerCards[4].getValue()) {
            std::cout << "Computer wins the round with a high card!" << std::endl;
            computer.incrementScore();
        }
        else {
            std::cout << "It's a draw!" << std::endl;
        }
        return;
    }
    // Four of a kind
    else if (playerCategory == "four") {
        // Compare the value of the four of a kind of both hands
        if (playerCards[2].getValue() > computerCards[2].getValue()) {
            std::cout << "You win the round with a higher valued four of a kind!" << std::endl;
            player.incrementScore();
        } else if (playerCards[2].getValue() < computerCards[2].getValue()) {
            std::cout << "Computer wins the round with a higher valued four of a kind!" << std::endl;
            computer.incrementScore();
        } else {
            std::cout << "It's a draw!" << std::endl;
        }
        return;
    }
    // Full house
    else if (playerCategory == "full") {
        // Compare the value of the three of a kind of both hands
        // (full house comprises a three of a kind and a pair)
        if (playerCards[2].getValue() > computerCards[2].getValue()) {
            std::cout << "You win the round with a higher valued full house!" << std::endl;
            player.incrementScore();
        } else if (playerCards[2].getValue() < computerCards[2].getValue()) {
            std::cout << "Computer wins the round with a higher valued full house!" << std::endl;
            computer.incrementScore();
        } else {
            std::cout << "It's a draw!" << std::endl;
        }
        return;
    }
    // Flush
    else if (playerCategory == "flsh") {
        // Compare the highest card of each player
        for (int i = 4; i > 0; --i) {
            if (playerCards[i].getValue() > computerCards[i].getValue()) {
                std::cout << "You win the round with a high card!" << std::endl;
                player.incrementScore();
                return;
            } else if (playerCards[i].getValue() < computerCards[i].getValue()) {
                std::cout << "Computer wins the round with a high card!" << std::endl;
                computer.incrementScore();
                return;
            }
        }
        std::cout << "It's a draw!" << std::endl;
        return;
    }
    // Straight
    else if (playerCategory == "strt") {
        // Compare the highest cards of each player
        if (playerCards[4].getValue() > computerCards[4].getValue()) {
            std::cout << "You win the round wtih a high card!" << std::endl;
            player.incrementScore();
        } else if (playerCards[4].getValue() < computerCards[4].getValue()) {
            std::cout << "Computer wins the round with a high card!" << std::endl;
            computer.incrementScore();
        } else {
            std::cout << "It's a draw!" << std::endl;
        }
        return;
    }
    // Three of a kind
    else if (playerCategory == "trio") {
        // Compare the value of the three of a kind of both hands
        if (playerCards[2].getValue() > computerCards[2].getValue()) {
            std::cout << "You win the round with a high card!" << std::endl;
            player.incrementScore();
        } else if (playerCards[2].getValue() < computerCards[2].getValue()) {
            std::cout << "Computer wins the round with a high card!" << std::endl;
            computer.incrementScore();
        } else {
            std::cout << "It's a draw!" << std::endl;
        }
        return;
    }
    // Two pair
    else if (playerCategory == "twop") {
        // Compare the values of the higher pair
        if (playerCards[3].getValue() > computerCards[3].getValue()) {
            std::cout << "You win the round with a higher value pair!" << std::endl;
            player.incrementScore();
        } else if (playerCards[3].getValue() < computerCards[3].getValue()) {
            std::cout << "Computer wins the round with a higher value pair!" << std::endl;
            computer.incrementScore();
        } else {
            // If the higher pairs are equal, compare the lower pairs
            if (playerCards[1].getValue() > computerCards[1].getValue()) {
                std::cout << "You win the round with a higher value pair!" << std::endl;
                player.incrementScore();
            } else if (playerCards[1].getValue() < computerCards[1].getValue()) {
                std::cout << "Computer wins the round with a higher value pair!" << std::endl;
                computer.incrementScore();
            } else {
                // Compare the 5th card
                for (int i = 4; i >= 0; --i) {
                    if (i == 0) {
                        if (playerCards[0].getValue() > computerCards[0].getValue()) {
                            std::cout << "You win the round with a high 5th card!" << std::endl;
                            player.incrementScore();
                        } else if (playerCards[0].getValue() < computerCards[0].getValue()) {
                            std::cout << "Computer wins the round with a high 5th card!" << std::endl;
                            computer.incrementScore();
                        }
                    }
                    else if (playerCards[i].getValue() == playerCards[i-1].getValue()) {
                        --i;
                    }
                    else {
                        if (playerCards[i].getValue() > computerCards[i].getValue()) {
                            std::cout << "You win the round with a high 5th card!" << std::endl;
                            player.incrementScore();
                        } else if (playerCards[i].getValue() < computerCards[i].getValue()) {
                            std::cout << "Computer wins the round with a high 5th card!" << std::endl;
                            computer.incrementScore();
                        }
                    }
                }
            }
        }
        return;
    }
    // Pair
    else if (playerCategory == "pair") {
        // Find the index of the pair for both hands
        int playerPairIndex = -1;
        int computerPairIndex = -1;
        for (int i = 0; i < 4; ++i) {
            if (playerCards[i].getValue() == playerCards[i + 1].getValue()) {
                playerPairIndex = i;
                break;
            }
        }
        for (int i = 0; i < 4; ++i) {
            if (computerCards[i].getValue() == computerCards[i + 1].getValue()) {
                computerPairIndex = i;
                break;
            }
        }

        // Compare the values of the pairs
        if (playerCards[playerPairIndex].getValue() > computerCards[computerPairIndex].getValue()) {
            std::cout << "You win the round with a higher value pair!" << std::endl;
            player.incrementScore();
        } else if (playerCards[playerPairIndex].getValue() < computerCards[computerPairIndex].getValue()) {
            std::cout << "Computer wins the round with a higher value pair!" << std::endl;
            computer.incrementScore();
        } else {
            // If the pairs are equal, compare the remaining cards
            for (int i = 4; i >= 0; --i) {
                if (i != playerPairIndex && playerCards[i].getValue() != playerCards[playerPairIndex].getValue()) {
                    if (playerCards[i].getValue() > computerCards[i].getValue()) {
                        std::cout << "You win the round with a high card!" << std::endl;
                        player.incrementScore();
                        return;
                    } else if (playerCards[i].getValue() < computerCards[i].getValue()) {
                        std::cout << "Computer wins the round with a high card!" << std::endl;
                        computer.incrementScore();
                        return;
                    }
                }
            }
            // If all cards are equal, it's a draw
            std::cout << "It's a draw!" << std::endl;
        }
        return;
    }
    // High card
    else if (playerCategory == "high") {
        // Compare the highest card of each player
        for (int i = 4; i > 0; --i) {
            if (playerCards[i].getValue() > computerCards[i].getValue()) {
                std::cout << "You win the round with a higher value card!" << std::endl;
                player.incrementScore();
                return;
            } else if (playerCards[i].getValue() < computerCards[i].getValue()) {
                std::cout << "Computer wins the round with a higher value card!" << std::endl;
                computer.incrementScore();
                return;
            }
        }
        std::cout << "It's a draw!" << std::endl;
        return;
    }
}

// Turns category string to readable text
std::string Game::categoryToText(std::string category) {
    if (category == "stfl")
        return "Straight Flush";
    else if (category == "four")
        return "Four of a Kind";
    else if (category == "full")
        return "Full House";
    else if (category == "flsh")
        return "Flush";
    else if (category == "strt")
        return "Straight";
    else if (category == "trio")
        return "Three of a Kind";
    else if (category == "twop")
        return "Two Pair";
    else if (category == "pair")
        return "Pair";
    else
        return "High card";

}

// Swap cards in player's hand
void Game::swapCards(Hand& playerHand, Deck& deck) {
    int numCardsToSwap;
    std::vector<int> cardsToSwapIndices;

    // Ask player to choose how many cards to swap
    std::cout << "How many cards do you want to swap? (1-3): ";
    std::cin >> numCardsToSwap;

    // Validate input
    if (numCardsToSwap < 1 || numCardsToSwap > 3) {
        std::cout << "Invalid number of cards. Please choose between 1 and 3 cards to swap." << std::endl;
        swapCards(playerHand, deck);
        return;
    }

    // Ask player to choose the index of which cards to swap
    std::cout << "Choose the position(s) of the cards you want to swap (1-5): ";
    for (int i = 0; i < numCardsToSwap; ++i) {
        int index;
        std::cin >> index;

        // Validate input
        if (index < 1 || index > 5) {
            std::cout << "Invalid card position. Please choose a number between 1 and 5." << std::endl;
            swapCards(playerHand, deck);
            return;
        }
        cardsToSwapIndices.push_back(index - 1); // Adjust index to 0-based
    }

    // Store the removed cards
    std::vector<Card> removedCards;
    for (int i : cardsToSwapIndices) {
        removedCards.push_back(playerHand.getCard(i));
    }

    // Swap the selected cards
    playerHand.swapCard(cardsToSwapIndices, deck);
    std::cout << "Your cards have been swapped." << std::endl;
    std::cout << std::endl;

    // Put the removed cards back into the deck
    for (const auto& card : removedCards) {
        deck.addCard(card);
    }

    // Re-sort cards by value after swapping
    playerHand.sortValue();
}

// Display scores of both player and computer
void Game::displayScores() {
    std::cout << std::endl;
    std::cout << "Your score: " << player.getScore();
    std::cout << std::endl;
    std::cout << "Computer's score: " << computer.getScore();
    std::cout << std::endl;
}

// End game phase
void Game::endGame() {
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "Thank you so much for playing! Here are the final scores: " << std::endl;
    displayScores();

    // Get overall winner
    if (player.getScore() > computer.getScore()) {
        std::cout << player.getName() << ", you win!" << std::endl;
    }
    else if (player.getScore() < computer.getScore()) {
        std::cout << player.getName() << ", you lose." << std::endl;
    }
    else {
        std::cout << "It's a draw!" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}

// Game main function
int main() {
    std::string playerName;
    std::cout << "Enter your name: ";
    std::cin >> playerName;

    Game game(playerName);
    game.startGame();

    return 0;
}
