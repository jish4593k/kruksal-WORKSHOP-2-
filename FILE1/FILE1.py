import random
import collections
import statistics

NO_OF_CARDS = 52
Deck = []

# Initialize the deck with values from 1 to 13 (representing cards Ace to King)
Deck = [(i % 13) + 1 for i in range(NO_OF_CARDS)]

# For cards with values greater than 10 (representing face cards), set them to 5
for i in range(NO_OF_CARDS):
    if ((i % 13) + 1) > 10:
        Deck[i] = 5

# Simulate the trick and check for matches
match = 0
Run_count = 0

# Lists to store shuffled decks and card counts
shuffled_decks = []
card_counts = []

for k in range(1000000):
    # Shuffle the deck
    i = NO_OF_CARDS - 1
    while i > 0:
        j = (random.randint(0, 1000000)) % i
        temp = Deck[i]
        Deck[i] = Deck[j]
        Deck[j] = temp
        i = i - 1

    # Count the occurrences of each card in the shuffled deck
    card_count = collections.Counter(Deck)
    card_counts.append(card_count)

    # Append the shuffled deck to the list for analysis
    shuffled_decks.append(list(Deck))

    Ctr_victim = random.randint(0, 10)
    while Ctr_victim + Deck[Ctr_victim] < NO_OF_CARDS:
        Ctr_victim = Ctr_victim + Deck[Ctr_victim]

    Ctr_mag = random.randint(0, 10)
    while Ctr_mag + Deck[Ctr_mag] < NO_OF_CARDS:
        Ctr_mag = Ctr_mag + Deck[Ctr_mag]

    if Ctr_mag == Ctr_victim:
        match = match + 1
    Run_count = Run_count + 1

percentage_of_matches = 100 * (match / Run_count)
print(f"Percentage of matches: {percentage_of_matches:.2f}%")

# Additional functionality: Display shuffled decks and card counts
for i in range(10):
    print(f"Shuffled Deck {i + 1}: {shuffled_decks[i]}")
    print(f"Card Counts {i + 1}: {card_counts[i]}")

# Calculate and display statistics about card counts
average_count = {card: statistics.mean([count[card] for count in card_counts]) for card in range(1, 14)}
highest_count = max(average_count, key=average_count.get)
lowest_count = min(average_count, key=average_count.get)
std_deviation = {card: statistics.stdev([count[card] for count in card_counts]) for card in range(1, 14)}

print("\nStatistics of Card Counts:")
for card in range(1, 14):
    print(f"Card {card}:")
    print(f"  - Average Count: {average_count[card]:.2f}")
    print(f"  - Highest Count: {card_counts[shuffled_decks.index(max(shuffled_decks, key=lambda deck: deck.count(card)))][card]}")
    print(f"  - Lowest Count: {card_counts[shuffled_decks.index(min(shuffled_decks, key=lambda deck: deck.count(card)))][card]}")
    print(f"  - Standard Deviation: {std_deviation[card]:.2f}")

