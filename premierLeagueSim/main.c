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

    //Create initial list of premier leaue teams + team ratings [teamId][teamRating]
    //TODO: Can probably use dynamic memorry allocation here to avoid duplicated hardcoding!
    int numberOfTeamsPremier = 20;
    int numberOfTeamsChampionship = 24;

    int teamsPremierLeague[20][2] = {
        {1,	82},
        {2, 76},
        {3, 76},
        {4, 77},
        {5, 73},
        {6, 83},
        {7, 77},
        {8, 79},
        {9, 76},
        {10, 75},
        {11, 78},
        {12, 82},
        {13, 85},
        {14, 83},
        {15, 76},
        {16, 77},
        {17, 83},
        {18, 77},
        {19, 78},
        {20, 76}
    };

    int teamsChampionship[20][2] = {
        {21, 73},
        {22, 70},
        {23, 69},
        {24, 69},
        {25, 70},
        {26, 70},
        {27, 72},
        {28, 69},
        {29, 68},
        {30, 72},
        {31, 72},
        {32, 69},
        {33, 72},
        {34, 72},
        {35, 70},
        {36, 70},
        {37, 69},
        {38, 67},
        {39, 70},
        {40, 71},
        {41, 74},
        {42, 72},
        {43, 73},
        {44, 69}
    };

    //Fire up initial seasons for all leagues
    int leaguePremier[20][7] = {0};
    initializeNewSeason(leaguePremier, teamsPremierLeague, numberOfTeamsPremier);

    int leagueChampionship[24][8] = {0};
    initializeNewSeason(leagueChamptionship, teamsChampionship, numberOfTeamsChampionship);




    printf("changing it up\n");
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 7; j++) {
            printf("%i\t", leaguePremier2[i][j]);
        }
        printf("\n");
    }


    for (int season = 1; season <= numberOfSeasons; season++) {

        simulateSeason(leaguePremier);
        simulateSeason(leagueChampionship);

        //Print table headers
        printf("----------------------START SEASON %i----------------------\n", season);
        printf("Team\t Played\t Wins\t Losses\t Draws\t Points\n");

        _Bool secondHalf = 0;
        for (int i = 0; i < numberOfTeamsPremier; i++) {

            for (int j = 0; j < numberOfTeamsPremier; j++) {

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

        for (int i = 0; i < numberOfTeamsPremier; i++) {
            printf("%i\t %i\t %i\t %i\t %i\t %i\n", leaguePremier[i][0], leaguePremier[i][2], leaguePremier[i][3], leaguePremier[i][4], leaguePremier[i][5], leaguePremier[i][6]);
        }

        //Print table footer
        printf("----------------------END SEASON %i----------------------\n\n", season);

    }



    return 0;
}

void initializeNewSeason(int (*league)[7], int (*teams)[2], int numTeams) {

    //int numTeams = sizeof(league[0])/sizeof(league[0][0]);
    printf("Teams in the league: %i\n", numTeams);

    printf("in initialize league\n");
    printf("Did this work?: %i", league[1][1]);

    for (int i = 0; i < 20; i++) {

        league[i][0] = teams[i][0];
        league[i][1] = teams[i][1];

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
