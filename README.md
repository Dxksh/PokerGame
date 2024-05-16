# C++ Console Poker Card Game

This game is a simple console-based C++ card game, based loosely on the hands of the classic card game, Poker. The objective of the game is to beat a computer opponent with combinations of 5 cards (known as a Hand) worth the highest value.

How the game works:
1. Card values and ranks are calculated in the same manner as poker.
2. The cards are shuffled before each game.
3. For each Round, 10 cards taken from the shuffled Deck and distributed to the Player and the
Computer, making two hands with 5 cards each.
4. Each game consists of rounds. When a new round is started but there are less than 10 cards
left in the deck, the game ends (since we cannot deal full hands to the players).
5. At the start of each round, the game window displays a representation of the player’s
hand (5 cards) and the computer’s hand (5 cards).
6. The game works out the categories (and therefore the rank) of each of the hands.
7. The player is allowed to SWAP a certain number of cards. In rounds 1-4, the player is allowed to swap up to three cards from their hand with cards from the deck. (Swapping is not allowed in every 5th round because there will be only 2 cards left in the deck).
8. The cards that are swapped out of the player’s hand are shuffled back into the deck, and therefore remain in the game.
9. After the swapping is complete, both the Player and the Computer's hand is displayed.
10. The game then determines who has the strongest hand, and in turn determines the winner of the round.
11. The score is displayed and updated at the start of each round, that shows the player’s
score and the computer’s score. The scores represent the number of hands won in the game.
12. After the 5 rounds have been played, the scores are displayed, and the user can decide to either end the game, or reshuffle the deck and continue the game.
