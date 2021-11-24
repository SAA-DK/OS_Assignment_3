#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/**
 * Til spillet er der 8 spillere
 * Der er 4 individuelle terninger, i dette spil har de seks sider
 * En person skal bruge et sæt terninger, 2 terninger, for at kunne slå
 * En person må kun holde ét sæt terninger ad gangen
 * Når en person har slået, gives terningerne videre til en tilfældig person
 * En person må ikke slå 2 gange i træk, med det samme sæt terninger
 * Spillet slutter når en person har slået dobbeltsekser tre gange
 * Hvis begge sæt terninger bliver givet til den samme person, må den ene person der prøver at give sine terninger væk blive siddende med dem, indtil
 * den person terningerne skal gives til, er færdig med at slå med det andet sæt terninger og har givet sættet videre: Spinlock
 *
 * @return
 */

//void* diceGame(int player1);
void printResult(int person, int die1, int die2);
int nextPlayer(int currentPlayer);
int throwDie(int die);
int chooseRandomPlayer(int player);

int die1, die2;
int count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0, count6 = 0, count7 = 0, count8 = 0; //Double sixes count to end game. One for each player

//Mutex lock
pthread_mutex_t mutex;
int player = 0;
void* diceGame() {
    if (!player) {
        player = chooseRandomPlayer(0); //Chooses first player A-H
    }
    die1 = throwDie(die1);
    die2 = throwDie(die2);
    printResult(player, die1, die2);

    //Mutex lock before choosing next player and using dice from the shared memory pool
    pthread_mutex_lock(&mutex);
    //Critical section -> give away dice
    player = nextPlayer(player); //Choose next player
    pthread_mutex_unlock(&mutex);
}

int main() {
    pthread_t game1, game2; //two thread structs created
    pthread_mutex_init(&mutex, NULL); //Initialize mutex

    while (count1 < 4) {
        if (pthread_create(&game1, NULL, &diceGame, NULL)) { //Create thread 1 for diceGame process
                return 1;
            }

            if (pthread_create(&game2, NULL, &diceGame, NULL)) { //Create thread 2 for diceGame process
                return 2;
            }

            if (pthread_join(game1, NULL)) { //First thread returns
                return 3;
            }

            if (pthread_join(game2, NULL)) { //Second thread returns
                return 4;
            }
    }
    pthread_mutex_destroy(&mutex); //Destroy mutex
}

int nextPlayer(int currentPlayer) {
    int numGen = chooseRandomPlayer(0);

    while (1) {
        if (numGen != currentPlayer) {
            return numGen;
        } else {
            numGen = chooseRandomPlayer(0);
        }
    }
}

int chooseRandomPlayer(int player) {
    player = ((rand() % 8) + 1);
    return player;
}

int throwDie(int die) {
    die = ((rand() % 6) + 1);
    return die;
}

void printResult(int person, int die1, int die2) {
    switch (person) {
        case 1:
            if (die1 == die2 && die1 == 6) { // Double sixes instance
                count1++;
            }
            if (count1 == 3) { //Game won
                printf("Person A rolled %d and %d three times, and has won the game!\n", die1, die2);
                exit(1);
            }
            printf("Person A rolled: %d and %d \n", die1, die2);
            break;
        case 2:
            if (die1 == die2 && die1 == 6) { // Double sixes instance
                count2++;
            }
            if (count2 == 3) { //Game won
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