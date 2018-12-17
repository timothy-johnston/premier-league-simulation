
#include <stdio.h>
#include <stdlib.h>

int main()
{

    //Prompt user for # of seasons to play
    //TODO: Ensure valid integer input
    int numberOfSeasons;
    printf("Enter the number of seasons to simulate: ");
    scanf("%i", &numberOfSeasons);

    //Seed random number generator with current time
    srand (time(NULL));

    int testLeague[20][8];

    int teamsP = 20;

    int leaguePremier[20][8] = {
        {1, 95, 0, 0, 0, 0, 0, 1},
        {2, 75, 0, 0, 0, 0, 0, 1},
        {3, 70, 0, 0, 0, 0, 0, 1},
        {4, 70, 0, 0, 0, 0, 0, 1},
        {5, 70, 0, 0, 0, 0, 0, 1},
        {6, 70, 0, 0, 0, 0, 0, 1},
        {7, 70, 0, 0, 0, 0, 0, 1},
        {8, 70, 0, 0, 0, 0, 0, 1},
        {9, 70, 0, 0, 0, 0, 0, 1},
        {10, 70, 0, 0, 0, 0, 0, 1},
        {11, 70, 0, 0, 0, 0, 0, 1},
        {12, 70, 0, 0, 0, 0, 0, 1},
        {13, 70, 0, 0, 0, 0, 0, 1},
        {14, 70, 0, 0, 0, 0, 0, 1},
        {15, 70, 0, 0, 0, 0, 0, 1},
        {16, 70, 0, 0, 0, 0, 0, 1},
        {17, 70, 0, 0, 0, 0, 0, 1},
        {18, 70, 0, 0, 0, 0, 0, 1},
        {19, 70, 0, 0, 0, 0, 0, 1},
        {20, 50, 0, 0, 0, 0, 0, 1}
    };

    int leagueChampionship[24][8] = {
        {1, 95, 0, 0, 0, 0, 0, 1},
        {2, 70, 0, 0, 0, 0, 0, 1},
        {3, 70, 0, 0, 0, 0, 0, 1},
        {4, 70, 0, 0, 0, 0, 0, 1},
        {5, 70, 0, 0, 0, 0, 0, 1},
        {6, 70, 0, 0, 0, 0, 0, 1},
        {7, 70, 0, 0, 0, 0, 0, 1},
        {8, 70, 0, 0, 0, 0, 0, 1},
        {9, 70, 0, 0, 0, 0, 0, 1},
        {10, 70, 0, 0, 0, 0, 0, 1},
        {11, 70, 0, 0, 0, 0, 0, 1},
        {12, 70, 0, 0, 0, 0, 0, 1},
        {13, 70, 0, 0, 0, 0, 0, 1},
        {14, 70, 0, 0, 0, 0, 0, 1},
        {15, 70, 0, 0, 0, 0, 0, 1},
        {16, 70, 0, 0, 0, 0, 0, 1},
        {17, 70, 0, 0, 0, 0, 0, 1},
        {18, 70, 0, 0, 0, 0, 0, 1},
        {19, 70, 0, 0, 0, 0, 0, 1},
        {20, 50, 0, 0, 0, 0, 0, 1},
        {20, 50, 0, 0, 0, 0, 0, 1},
        {20, 50, 0, 0, 0, 0, 0, 1},
        {20, 50, 0, 0, 0, 0, 0, 1},
        {20, 50, 0, 0, 0, 0, 0, 1}
    };



    //int initializeLeague(int *leaguePremier[]);
    initializeLeague(testLeague);


    printf("changing it up\n");
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%i\t", testLeague[i][j]);
        }
        printf("\n");
    }

    for (int season = 1; season <= numberOfSeasons; season++) {

        //Print table headers
        printf("----------------------START SEASON %i----------------------\n", season);
        printf("Team\t Played\t Wins\t Losses\t Draws\t Points\n");

        _Bool secondHalf = 0;
        for (int i = 0; i < teamsP; i++) {

            for (int j = 0; j < teamsP; j++) {

                if (j > i) {
                    leaguePremier[i][2]++;
                    leaguePremier[j][2]++;

                    int winner = determineResult(leaguePremier[i][1], leaguePremier[j][1]);

                    if (winner == 0) {
                        leaguePremier[i][3]++;
                        leaguePremier[j][4]++;
                        leaguePremier[i][6]+=3;
                    } else if (winner == 1) {
                        leaguePremier[j][3]++;
                        leaguePremier[i][4]++;
                        leaguePremier[j][6]+=3;
                    } else {
                        leaguePremier[i][5]++;
                        leaguePremier[j][5]++;
                        leaguePremier[i][6]++;
                        leaguePremier[j][6]++;
                    }

                    //Debugging
                    //int winner = determineResult(90, 70);

                    //printf("The winner was team: %i\n", winner);

                }

            }

            if (i == 19 && secondHalf == 0) {
                i = -1;
                secondHalf = 1;
            }

        }

        for (int i = 0; i < teamsP; i++) {
            printf("%i\t %i\t %i\t %i\t %i\t %i\n", leaguePremier[i][0], leaguePremier[i][2], leaguePremier[i][3], leaguePremier[i][4], leaguePremier[i][5], leaguePremier[i][6]);
        }

        //Print table footer
        printf("----------------------END SEASON %i----------------------\n\n", season);

    }



    return 0;
}

void initializeLeague(int (*league)[8]) {

    int numTeams = sizeof(league)/sizeof(league[0][0]);
    printf("Teams in the league: %i\n", numTeams);

    printf("in initialize league\n");
    printf("Did this work?: %i", league[1][1]);

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 8; j++) {
            league[i][j] = 100;
        }
        printf("\n");
    }

}


//Returns 0 for team A win, 1 for team B win, 2 for tie
//Chances weighted by difference in team's ratings
int determineResult(int ratingA, int ratingB) {
    //srand ( time(NULL) );
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
