#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <numeric>
#include <cmath>

// Author: Your Name
// Description: Card Trick Simulation
// Features: Simulate a card trick, calculate the percentage of matches, and display statistics.
// Email: your.email@example.com

int main() {
    // Number of cards in the deck
    const int NO_OF_CARDS = 52;

    // Initialize the deck with values from 1 to 13 (representing cards Ace to King)
    std::vector<int> deck(NO_OF_CARDS);
    std::iota(deck.begin(), deck.end(), 1);

    // For cards with values greater than 10 (representing face cards), set them to 5
    std::transform(deck.begin(), deck.end(), deck.begin(), [](int card) {
        return (card > 10) ? 5 : card;
    });

    // Simulate the trick and check for matches
    int match = 0;
    int runCount = 0;

    // Lists to store shuffled decks and card counts
    std::vector<std::vector<int>> shuffledDecks;
    std::vector<std::map<int, int>> cardCounts;

    for (int k = 0; k < 1000000; ++k) {
        // Shuffle the deck
        std::vector<int> shuffledDeck = deck;
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(shuffledDeck.begin(), shuffledDeck.end(), g);

        // Count the occurrences of each card in the shuffled deck
        std::map<int, int> cardCount;
        for (int card : shuffledDeck) {
            cardCount[card]++;
        }
        cardCounts.push_back(cardCount);

        // Append the shuffled deck to the list for analysis
        shuffledDecks.push_back(shuffledDeck);

        // Perform the card trick
        int ctrVictim = std::rand() % 11;
        while (ctrVictim + shuffledDeck[ctrVictim] < NO_OF_CARDS) {
            ctrVictim += shuffledDeck[ctrVictim];
        }

        int ctrMag = std::rand() % 11;
        while (ctrMag + shuffledDeck[ctrMag] < NO_OF_CARDS) {
            ctrMag += shuffledDeck[ctrMag];
        }

        if (ctrMag == ctrVictim) {
            match++;
        }
        runCount++;
    }

    double percentageOfMatches = 100.0 * (static_cast<double>(match) / runCount);
    std::cout << "Percentage of matches: " << percentageOfMatches << "%" << std::endl;

    // Additional functionality: Display shuffled decks and card counts
    for (int i = 0; i < 10; ++i) {
        std::cout << "Shuffled Deck " << (i + 1) << ": ";
        for (int card : shuffledDecks[i]) {
            std::cout << card << " ";
        }
        std::cout << std::endl;

        std::cout << "Card Counts " << (i + 1) << ": ";
        for (const auto& count : cardCounts[i]) {
            std::cout << "Card " << count.first << " = " << count.second << " ";
        }
        std::cout << std::endl;
    }

    // Calculate and display statistics about card counts
    for (int card = 1; card <= 13; ++card) {
        double averageCount = 0.0;
        int highestCount = 0;
        int lowestCount = NO_OF_CARDS;
        double sumSquareDifferences = 0.0;

        for (const auto& count : cardCounts) {
            int cardCount = count.count(card) ? count.at(card) : 0;
            averageCount += static_cast<double>(cardCount) / runCount;
            highestCount = std::max(highestCount, cardCount);
            lowestCount = std::min(lowestCount, cardCount);
            sumSquareDifferences += std::pow(cardCount - averageCount, 2);
        }

        double standardDeviation = std::sqrt(sumSquareDifferences / runCount);

        std::cout << "\nStatistics of Card " << card << ":" << std::endl;
        std::cout << "  - Average Count: " << averageCount << std::endl;
        std::cout << "  - Highest Count: " << highestCount << std::endl;
        std::cout << "  - Lowest Count: " << lowestCount << std::endl;
        std::cout << "  - Standard Deviation: " << standardDeviation << std::endl;
    }

    return 0;
}
