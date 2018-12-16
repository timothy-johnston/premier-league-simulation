#include <stdio.h>
#include <stdlib.h>

int main()
{

    int teamsP = 20;

    int leaguePremier[20][8] = {
        {1, 90, 0, 0, 0, 0, 0, 1},
        {2, 90, 0, 0, 0, 0, 0, 1},
        {3, 90, 0, 0, 0, 0, 0, 1},
        {4, 90, 0, 0, 0, 0, 0, 1},
        {5, 90, 0, 0, 0, 0, 0, 1},
        {6, 90, 0, 0, 0, 0, 0, 1},
        {7, 90, 0, 0, 0, 0, 0, 1},
        {8, 90, 0, 0, 0, 0, 0, 1},
        {9, 90, 0, 0, 0, 0, 0, 1},
        {10, 90, 0, 0, 0, 0, 0, 1},
        {11, 90, 0, 0, 0, 0, 0, 1},
        {12, 90, 0, 0, 0, 0, 0, 1},
        {13, 90, 0, 0, 0, 0, 0, 1},
        {14, 90, 0, 0, 0, 0, 0, 1},
        {15, 90, 0, 0, 0, 0, 0, 1},
        {16, 90, 0, 0, 0, 0, 0, 1},
        {17, 90, 0, 0, 0, 0, 0, 1},
        {18, 90, 0, 0, 0, 0, 0, 1},
        {19, 90, 0, 0, 0, 0, 0, 1},
        {20, 90, 0, 0, 0, 0, 0, 1}
    };


    _Bool secondHalf = 0;
    for (int i = 0; i < teamsP; i++) {

        for (int j = 0; j < teamsP; j++) {

            if (j > i) {
                leaguePremier[i][2]++;
                leaguePremier[j][2]++;

                int winner = determineResult(leaguePremier[i][1], leaguePremier[j][1]);

                //Debugging
                //int winner = determineResult(90, 70);

                printf("The winner was team: %i\n", winner);

            }

        }

        if (i == 19 && secondHalf == 0) {
            i = -1;
            secondHalf = 1;
        }

    }

    for (int i = 0; i < teamsP; i++) {
        printf("Team: %i, GamesPlayed: %i\n", leaguePremier[i][0], leaguePremier[i][2]);
    }

    return 0;
}

//Returns 0 for team A win, 1 for team B win, 2 for tie
//Chances weighted by difference in team's ratings
int determineResult(int ratingA, int ratingB) {
    float roll = (float) rand() / (float) (RAND_MAX/1);

    float ratingModifier = ((float) (ratingA - ratingB) / 2) / 100;
    //printf("rating modifier is: %f\n", ratingModifier);


    if (roll <= 0.33 + ratingModifier) {
        return 0;
    } else if (roll >= 0.66 + ratingModifier) {
        return 1;
    } else {
        return 2;
    }

}

//int * testFunction()
