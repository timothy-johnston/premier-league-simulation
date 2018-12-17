#include <stdio.h>
#include <stdlib.h>

_Bool secondHalf = 0;

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

    int teamsChampionship[24][2] = {
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

    int leagueChampionship[24][7] = {0};
    initializeNewSeason(leagueChampionship, teamsChampionship, numberOfTeamsChampionship);

    printf("Initial PL:\n");
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 7; j++) {
            printf("%i\t", leaguePremier[i][j]);
        }
        printf("\n");
    }
    printf("Initial Championship:\n");
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 7; j++) {
            printf("%i\t", leagueChampionship[i][j]);
        }
        printf("\n");
    }


    for (int season = 1; season <= numberOfSeasons; season++) {

        printf("----------------------START SEASON %i----------------------\n", season);

        printf("----------Premier League------------\n");
        simulateSeason(leaguePremier, numberOfTeamsPremier);

        printf("-----------Championship-------------\n");
        simulateSeason(leagueChampionship, numberOfTeamsChampionship);

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

    for (int i = 0; i < numTeams; i++) {

        league[i][0] = teams[i][0];
        league[i][1] = teams[i][1];

    }

}

void simulateSeason(int (*league[7]), int numTeams) {

        //Print table headers
        printf("Team\t Rating\t Played\t Wins\t Losses\t Draws\t Points\n");

        //While in first half of season, false. While in 2nd half, true.
        //Used for loop control
        //

        printf("before outer loop");
        printf("number of teams: %i", numTeams);
        //Loop over all teams
        for (int i = 0; i < numTeams; i++) {

            printf("in outer loop");

            for (int j = 0; j < numTeams; j++) {

                printf("in innermost loop");

                //This conditional assures no simulation occurs for a team playing itself
                //or a team playing a team is has already played (in the current half of the season)
                //If j > i, then neither of the above are true
                if (j > i) {

                    //Increment games played count
                    league[i][2]++;
                    league[j][2]++;

                    //Determine the outcome of the match
                    int winner = determineResult(league[i][1], league[j][1]);

                    //Increment win/lose/draw counts, assign points (w = 3, l = 0, draw = 1)
                    //Could abstract this to new function
                    if (winner == 0) {
                        league[i][3]++;
                        league[j][4]++;
                        league[i][6]+=3;
                    } else if (winner == 1) {
                        league[j][3]++;
                        league[i][4]++;
                        league[j][6]+=3;
                    } else {
                        league[i][5]++;
                        league[j][5]++;
                        league[i][6]++;
                        league[j][6]++;
                    }
                }
            }

            //Each team plays each other twice.
            //After each team plays each other once, this will reset the outer array
            //index to the beginning of the array
            //The second time through (when secondHalf == true), this is skipped and loop exits
            if (i == 19 && secondHalf == 0) {
                i = -1;
                secondHalf = 1;
            }

        }

        for (int i = 0; i < numTeams; i++) {
            printf("%i\t %i\t %i\t %i\t %i\t %i\t %i\n", league[i][0], league[i][1], league[i][2], league[i][3], league[i][4], league[i][5], league[i][6]);
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
