#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Author: Your Name
// Description: Card Trick Simulation
// Features: Simulate a card trick,  calculate the percentage of matches,  and display statistics.
// Email: your.email@example.com

int main() {
    // Number of cards in the deck
    const int NO_OF_CARDS = 52;

    // Initialize the deck with values from 1 to 13 (representing cards Ace to King)
    int deck[NO_OF_CARDS];
    for (int i = 0; i < NO_OF_CARDS; i++) {
        deck[i] = (i % 13) + 1;
    }

 
    for (int i = 0; i < NO_OF_CARDS; i++) {
        if (deck[i] > 10) {
            deck[i] = 5;
        }
    }

    // Simulate the trick and check for matches
    int match = 0;
    int runCount = 0;

    // Lists to store shuffled decks and card counts
    int shuffledDecks[1000000][NO_OF_CARDS];
    int cardCounts[1000000][14];

    srand(time(NULL));

    for (int k = 0; k < 1000000; k++) {
        // Shuffle the deck
        int shuffledDeck[NO_OF_CARDS];
        for (int i = 0; i < NO_OF_CARDS; i++) {
            shuffledDeck[i] = deck[i];
        }
        for (int i = NO_OF_CARDS - 1; i > 0; i--) {
            int j = rand() % i;
            int temp = shuffledDeck[i];
            shuffledDeck[i] = shuffledDeck[j];
            shuffledDeck[j] = temp;
        }

        // Count the occurrences of each card in the shuffled deck
        int cardCount[14] = {0};
        for (int i = 0; i < NO_OF_CARDS; i++) {
            cardCount[shuffledDeck[i]]++;
        }
        for (int i = 1; i <= 13; i++) {
            cardCounts[k][i] = cardCount[i];
        }

        // Append the shuffled deck to the list for analysis
        for (int i = 0; i < NO_OF_CARDS; i++) {
            shuffledDecks[k][i] = shuffledDeck[i];
        }

        // Perform the card trick
        int ctrVictim = rand() % 11;
        while (ctrVictim + shuffledDeck[ctrVictim] < NO_OF_CARDS) {
            ctrVictim += shuffledDeck[ctrVictim];
        }

        int ctrMag = rand() % 11;
        while (ctrMag + shuffledDeck[ctrMag] < NO_OF_CARDS) {
            ctrMag += shuffledDeck[ctrMag];
        }

        if (ctrMag == ctrVictim) {
            match++;
        }
        runCount++;
    }

    double percentageOfMatches = 100.0 * ((double)match / runCount);
    printf("Percentage of matches: %.2f%%\n", percentageOfMatches);

    // Additional functionality: Display shuffled decks and card counts
    for (int i = 0; i < 10; i++) {
        printf("Shuffled Deck %d: ", i + 1);
        for (int j = 0; j < NO_OF_CARDS; j++) {
            printf("%d ", shuffledDecks[i][j]);
        }
        printf("\n");

        printf("Card Counts %d: ", i + 1);
        for (int j = 1; j <= 13; j++) {
            printf("Card %d = %d ", j, cardCounts[i][j]);
        }
        printf("\n");
    }

    // Calculate and display statistics about card counts
    for (int card = 1; card <= 13; card++) {
        double averageCount = 0.0;
        int highestCount = 0;
        int lowestCount = NO_OF_CARDS;
        double sumSquareDifferences = 0.0;

        for (int k = 0; k < 1000000; k++) {
            int cardCount = cardCounts[k][card];
            averageCount += (double)cardCount / runCount;
            if (cardCount > highestCount) {
                highestCount = cardCount;
            }
            if (cardCount < lowestCount) {
                lowestCount = cardCount;
            }
            sumSquareDifferences += pow(cardCount - averageCount, 2);
        }

        double standardDeviation = sqrt(sumSquareDifferences / runCount);

        printf("\nStatistics of Card %d:\n", card);
        printf("  - Average Count: %.2f\n", averageCount);
        printf("  - Highest Count: %d\n", highestCount);
        printf("  - Lowest Count: %d\n", lowestCount);
        printf("  - Standard Deviation: %.2f\n", standardDeviation);
    }

    return 0;
}
