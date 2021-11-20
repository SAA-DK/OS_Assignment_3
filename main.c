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
 * Spillet slutter når en person har slået dobbeltsekser med begge sæt terninger.
 * Ved tilfælde af en deadlock, hvor terningerne bliver splittet op, så der sidder mere en to personer med terninger, er det en fejl, og spillet starter forfra.
 * Det sæt terninger man lige har slået med, kan ikke komme tilbage til en selv, før at mindst en anden person har slået med sættet.
 *
 * Hvis begge sæt terninger bliver givet til den samme person, må den ene person der prøver at give sine terninger væk blive siddende med dem, indtil
 * den person terningerne skal gives til, er færdige med at slå med det andet sæt terninger, og har givet sættet videre: Spinlock
 *
 * @return
 */

void process1(int person, int die1, int die2);
void process2(int person, int die1, int die2);
void printResult(int person, int die1, int die2);
int nextPlayer(int person);

int turn; //OBS! Tager kun højde for én tur
int die1; die2; die3; die4;

int main() {
    int numGen1 = ((rand() % 8) + 1); //Initierer første spiller
    int numGen2 = ((rand() % 8) + 1); //Initierer anden spiller

    process1(numGen1, die1, die2); //Starter
    process2(numGen2, die3, die4);

}


//Peterson's Algortihm for Two Processes
bool flag [2];
int turn;
void process1 (int person, int die1, int die2) {
    die1 = ((rand() % 6) + 1);
    die2 = ((rand() % 6) + 1);
    printResult(person, die1, die2);

    /*while (true) {
        flag [1] = true;
        turn = 1;
        while (flag[0] && turn == 1) {}
        /*Critical section -> give away dice*//*
        flag [1] = false;
    }*/
        //Critical section:
    nextPlayer(person); //What to do with this person??
}

void process2 (int person, int die1, int die2) {
    die1 = ((rand() % 6) + 1);
    die2 = ((rand() % 6) + 1);
    printResult(person, die1, die2);

    /*while (true) {
        flag [0] = true;
        turn = 0;
        while (flag[1] && turn == 0) {}
        /*Critical section -> give away dice*/
    /*flag [0] = false;
    }*/
}

int nextPlayer(int person){
    while (1) {
        int numGen1 = ((rand() % 8) + 1);
            if (numGen1 != person) {
                turn = person;
                return turn;
            }
    }
}

void printResult (int person, int die1, int die2) {
    switch (person) {
        case 1:
            printf("Person A rolled: %d and %d \n", die1, die2);
            break;
        case 2:
            printf("Person B rolled: %d and %d \n", die1, die2);
            break;
        case 3:
            printf("Person C rolled: %d and %d \n", die1, die2);
            break;
        case 4:
            printf("Person D rolled: %d and %d \n", die1, die2);
            break;
        case 5:
            printf("Person E rolled: %d and %d \n", die1, die2);
            break;
        case 6:
            printf("Person F rolled: %d and %d \n", die1, die2);
            break;
        case 7:
            printf("Person G rolled: %d and %d \n", die1, die2);
            break;
        case 8:
            printf("Person H rolled: %d and %d \n", die1, die2);
            break;
        default:
            return;
    }
}