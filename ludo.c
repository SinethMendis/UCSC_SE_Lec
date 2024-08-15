#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "types.c"

#define NUM_PIECES 16
#define NUM_PLAYERS 4
#define PIECES_PER_PLAYER (NUM_PIECES / NUM_PLAYERS)

struct pieces piece[NUM_PIECES];

void initializePieces(struct pieces piece[]) {
    const char *colors[] = {"Yellow", "Blue", "Red", "Green"};
    const char colorIds[] = {'Y', 'B', 'R', 'G'};

    for(int i = 0; i < NUM_PIECES; i++) {
        piece[i].pieceId = i % PIECES_PER_PLAYER + 1;
        strcpy(piece[i].color, colors[i / PIECES_PER_PLAYER]);
        piece[i].colorId = colorIds[i / PIECES_PER_PLAYER];
    }
}

void printFirstLine(struct pieces piece[]) {
    for(int i = 0; i < NUM_PLAYERS; i++) {
        printf("The %s player has four(4) pieces named %c%d,%c%d,%c%d and %c%d.\n",
            piece[i * PIECES_PER_PLAYER].color,
            piece[i * PIECES_PER_PLAYER].colorId, 1,
            piece[i * PIECES_PER_PLAYER].colorId, 2,
            piece[i * PIECES_PER_PLAYER].colorId, 3,
            piece[i * PIECES_PER_PLAYER].colorId, 4
        );
    }
    printf("\n");
}

void rollDice(int arr[]) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        arr[i] = RAND;
    }
}

void printRolls(struct pieces piece[], int arr[]) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("%s rolls %d\n", piece[i * PIECES_PER_PLAYER].color, arr[i]);
    }
    printf("\n");
}

int findMax(int arr[], int *max) {
    *max = arr[0];
    int maxIndex = 0;
    int count = 1;

    for (int i = 1; i < NUM_PLAYERS; i++) {
        if (arr[i] > *max) {
            *max = arr[i];
            maxIndex = i;
            count = 1;
        } else if (arr[i] == *max) {
            count++;
        }
    }
    return (count == 1) ? maxIndex : -1;
}

void printRoundOrder(int startingPlayer) {
    const char *order[] = {"first", "second", "third", "fourth"};
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("%s player will go %s.\n", piece[(startingPlayer + i) % NUM_PLAYERS * PIECES_PER_PLAYER].color, order[i]);
    }
    printf("\n");
}

void dicerolls_start(int startingPlayer, int player_rolled_values[], struct pieces piece[]) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        int playerIndex = (startingPlayer + i) % NUM_PLAYERS;
        player_rolled_values[playerIndex] = RAND;
        printf("%s rolled %d\n", piece[playerIndex * PIECES_PER_PLAYER].color, player_rolled_values[playerIndex]);
    }
}

int main() {
    srand(time(NULL));

    initializePieces(piece);
    printFirstLine(piece);

    int arr[NUM_PLAYERS];
    int max;
    int startingPlayer;

    do {
        rollDice(arr);
        printRolls(piece, arr);
        startingPlayer = findMax(arr, &max);
    } while (startingPlayer == -1);

    printf("%s player has the highest roll and will begin the game.\n", piece[startingPlayer * PIECES_PER_PLAYER].color);
    printRoundOrder(startingPlayer);

    int player_rolled_values[NUM_PLAYERS];
    dicerolls_start(startingPlayer, player_rolled_values, piece);

    return 0;
}
