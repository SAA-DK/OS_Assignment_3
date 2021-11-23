#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Oprettet 8 personer
 * Oprettet 4 individuelle terninger, størrelsen er underordnet
 * En person skal bruge et sæt terninger, 2 terninger, for at kunne slå.
 * En person må kun holde ét sæt terninger ad gangen.
 * Når en person har slået, gives terningerne videre til en tilfældig person.
 * En person må ikke slå 2 gange i træk, med det samme sæt terninger.
 * Spillet slutter når en person har slået dobbeltsekser tre gange.
 * Ved tilfælde af en deadlock, hvor terningerne bliver splittet op, så der sidder mere en to personer med terninger, er det en fejl, og spillet starter forfra.
 * Det sæt terninger man lige har slået med, kan ikke komme tilbage til en selv, før at mindst en anden person har slået med sættet.
 *
 * Hvis begge sæt terninger bliver givet til den samme person, må den ene person der prøver at give sine terninger væk blive siddende med dem, indtil
 * den person terningerne skal gives til, er færdige med at slå med det andet sæt terninger, og har givet sættet videre: Spinlock
 *
 * @return
 */

void playing(int person1, person2, die1, die2, die3, die4);
void printResult(int person, int die1, int die2);
int nextPlayer(int currentPlayer, otherPlayer);
int throwDie(int die);
int chooseRandomPlayer (int player);

int turn;
int die1; die2; die3; die4;

int main() {
    int numGen1 = chooseRandomPlayer(0); //Chooses first player A-H
    int numGen2 = chooseRandomPlayer(0); //Chooses second player

    //Starts playing
    playing(numGen1, numGen2, die1, die2, die3, die4);

    for(int i = 0; i < 10; i++){
        die1 = ((rand() % 6) + 1);
        die2 = ((rand() % 6) + 1);
        printf("Die 1 = %d and Die 2 = %d \n", die1, die2);
    }
}

//Peterson's Algorithm for Two Processes
bool flag [2];
int turn;

//Game ongoing
void playing(int player1, player2, die1, die2, die3, die4) {
    //Game1 - current player of this game is called player1
    //Kig denne del igennem igen. Skal finde en måde at fjerne break-statement
    while (1) {
        die1 = throwDie(die1);
        die2 = throwDie(die2);
        printResult(player1, die1, die2);

        while (1) {
            flag[0] = true;
            turn = 1;
            while (flag[1] && turn == 1) { /*do nothing*/ }
            //Critical section -> give away dice
            nextPlayer(player1, player2); //Choose next player

            flag[0] = false;
            break;
        }
        break;
    }

    //Game2  - current player of this game is called player2
    while (1) {
        die3 = throwDie(die3);
        die4 = throwDie(die4);
        printResult(player2, die1, die2);

        while (1) {
            flag[1] = true;
            turn = 0;
            while (flag[0] && turn == 0) { /*do nothing*/ }
            //Critical section -> give away dice
            nextPlayer(player2, player1); //Choose next player

            flag[1] = false;
            break;
        }
        break;
    }
}

int i;  //Skal slettes igen.

int nextPlayer (int currentPlayer, otherPlayer){  //OBS! Vi har ikke taget højde for at otherPlayer ændrer sig mens nextPlayer() kører
    int numGen = chooseRandomPlayer(currentPlayer);
    while (1) {
        if (numGen != currentPlayer && numGen != otherPlayer) {
            turn = numGen;
            return turn;
        } else {
            numGen = chooseRandomPlayer(currentPlayer);
        }
    }
}
int chooseRandomPlayer (int player) {
    player = ((rand() % 8) + 1);
    return player;
}

int throwDie (int die) {
    die = ((rand() % 6) + 1);
    return die;
}

int count1= 0, count2= 0, count3= 0, count4= 0, count5= 0, count6 = 0, count7 = 0, count8 = 0; //Double sixes count to end game. One for each player
void printResult (int person, int die1, int die2) {
    switch (person) {
        case 1:
            if (die1 == die2 && die1 == 6) { // Double sixes instance
                count1++;
            } if (count1 == 3) { //Game won
                printf("Person A rolled %d and %d three times, and has won the game!\n", die1, die2);
                exit(1);
            }
            printf("Person A rolled: %d and %d \n", die1, die2);
            break;
        case 2:
            if (die1 == die2 && die1 == 6) { // Double sixes instance
                count2++;
            } if (count2 == 3) { //Game won
                printf("Person B rolled %d and %d three times, and has won the game!\n", die1, die2);
                exit(1);
            }
            printf("Person B rolled: %d and %d \n", die1, die2);
            break;
        case 3:
            if (die1 == die2 && die1 == 6) { // Double sixes instance
                count3++;
            }
            if (count3 == 3) { //Game won
                printf("Person C rolled %d and %d three times, and has won the game!\n", die1, die2);
                exit(1);
            }
            printf("Person C rolled: %d and %d \n", die1, die2);
            break;
        case 4:
            if (die1 == die2 && die1 == 6) { // Double sixes instance
                count4++;
            }
            if (count4 == 3) { //Game won
                printf("Person D rolled %d and %d three times, and has won the game!\n", die1, die2);
                exit(1);
            }
            printf("Person D rolled: %d and %d \n", die1, die2);
            break;
        case 5:
            if (die1 == die2 && die1 == 6) { // Double sixes instance
                count5++;
            }
            if (count5 == 3) { //Game won
                printf("Person E rolled %d and %d three times, and has won the game!\n", die1, die2);
                exit(1);
            }
            printf("Person E rolled: %d and %d \n", die1, die2);
            break;
        case 6:
            if (die1 == die2 && die1 == 6) { // Double sixes instance
                count6++;
            }
            if (count6 == 3) { //Game won
                printf("Person F rolled %d and %d three times, and has won the game!\n", die1, die2);
                exit(1);
            }
            printf("Person F rolled: %d and %d \n", die1, die2);
            break;
        case 7:
            if (die1 == die2 && die1 == 6) { // Double sixes instance
                count7++;
            }
            if (count7 == 3) { //Game won
                printf("Person G rolled %d and %d three times, and has won the game!\n", die1, die2);
                exit(1);
            }
            printf("Person G rolled: %d and %d \n", die1, die2);
            break;
        case 8:
            if (die1 == die2 && die1 == 6) { // Double sixes instance
                count8++;
            }
            if (count8 == 3) { //Game won
                printf("Person H rolled %d and %d three times, and has won the game!\n", die1, die2);
                exit(1);
            }
            printf("Person H rolled: %d and %d \n", die1, die2);
            break;
        default:
            return;
    }
}