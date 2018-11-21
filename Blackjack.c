#include <stdio.h>
#include <stdlib.h>

char cards[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K' };
int cardsEqPoints[13] = { 11, 2, 3, 4, 5, 6, 7, 8, 9 , 10, 10, 10, 10 };

char isHoleCardHidden = 'T';

int charAt(char indexOfChar) {
    for (int i = 0; i < sizeof(cards); i++) {
        if (cards[i] == indexOfChar) {
            return i;
        }
    }
}

void printPlayerCards(char cardsInHand[]) {
    for (int i = 0; i < strlen(cardsInHand); i++) {
        cardsInHand[i] == '0' ? ((cardsInHand[i] == '0') ? printf("10 ") : printf("")) : printf("%c ", cardsInHand[i]);
    }
}

void printDealerCards(char cardsInHand[]) {
    for (int i = 0; i < strlen(cardsInHand); i++) {
        if ((cardsInHand[i + 1] == '\0') && (isHoleCardHidden == 'T')) {
            printf("X ");
        }
        else {
            cardsInHand[i] == '0' ? ((cardsInHand[i] == '0') ? printf("10 ") : printf("")) : printf("%c ", cardsInHand[i]);
        }
    }
}

int getPointsInHand(char cardsInHand[]) {
    int points = 0;
    for (int i = 0; i < strlen(cardsInHand); i++) {
        if (cardsInHand[i] == 'A') {
            int pointsBefore = 0;
            for (int j = 0; j < i; j++) {
                pointsBefore += cardsEqPoints[charAt(cardsInHand[j])];
            }

            (pointsBefore + 11) > 21 ? (points += 1) : (points += cardsEqPoints[charAt(cardsInHand[i])]);
        }
        else {
            points += cardsEqPoints[charAt(cardsInHand[i])];
        }
    }

    return points;
}

void nullifyArray(char cardsInHand[]) {
    for (int i = 0; i < sizeof(cardsInHand); i++) {
        cardsInHand[i] = '\0';
    }
}

void main() {
    char playersHand[20] = { '\0' };
    char dealersHand[20] = { '\0' };
    char isPlayerBlackJackHand = 'F';
    int dealerWinsCounter = 0, playerWinsCounter = 0;

    srand(time(NULL));

    char isContinueGame = 'T';

    do {
        int count = 0;
        char isPlayerOrCompBust = 'F';
        char playerInp;
        while (isPlayerOrCompBust == 'F') {
            if (count < 1) {
                playersHand[0] = cards[rand() % 13];
                playersHand[1] = cards[rand() % 13];

                dealersHand[0] = cards[rand() % 13];
                dealersHand[1] = cards[rand() % 13];

                if (playersHand[0] + playersHand[1] == 21) {
                    isPlayerBlackJackHand = 'T';
                    playerInp = 's';
                }

                printf("Player's Hand: ");
                printPlayerCards(playersHand);

                printf("\n");
                printf("Dealer's Hand: ");
                printDealerCards(dealersHand);


                printf("\n");
            }
            else {
                if (isPlayerBlackJackHand == 'F') {
                    printf("\nEnter command: ");
                    scanf(" %c", &playerInp);
                }

                if (playerInp == 'h') {
                    playersHand[count + 1] = cards[rand() % 13];

                    int totalPlayerPoints = getPointsInHand(playersHand);

                    printf("\n");

                    printf("Player's Hand: ");
                    printPlayerCards(playersHand);

                    printf("\n");
                    printf("Dealer's Hand: ");
                    printDealerCards(dealersHand);

                    printf("\n");

                    if (totalPlayerPoints == 21) {
                        playerInp = 's';
                        isPlayerBlackJackHand = 'T';
                    }
                    else if (totalPlayerPoints > 21) {
                        isPlayerOrCompBust = 'T';
                        dealerWinsCounter++;
                        printf("\nPlayer Busted!!", totalPlayerPoints);
                    }
                }
                else if (playerInp == 's') {
                    int totalDealerPoints = 0, totalDealerCards = 0, totalPlayerCards = 0, startingIndex = 0;

                    isHoleCardHidden = 'F';

                    for (int i = 0; i < strlen(dealersHand); i++) {
                        startingIndex = i;
                    }

                    dealersHand[startingIndex] = cards[rand() % 13];

                    totalDealerPoints = getPointsInHand(dealersHand);

                    int indexInc = 1;
                    while (totalDealerPoints < 17) {
                        dealersHand[startingIndex + indexInc] = cards[rand() % 13];
                        totalDealerPoints = getPointsInHand(dealersHand);
                        indexInc++;
                    }

                    printf("\nPlayer's Hand: ");
                    printPlayerCards(playersHand);

                    printf("\nDealer's Hand: ");
                    printDealerCards(dealersHand);

                    int totalPlayerPoints = getPointsInHand(playersHand);
                    totalDealerCards = strlen(dealersHand);
                    totalPlayerCards = strlen(playersHand);

                    if (totalDealerPoints > 21) {
                        playerWinsCounter++;
                        printf("\n\nPlayer Won!!");
                    } else {
                        if (totalDealerPoints > totalPlayerPoints) {
                            printf("\n\nDealer Won!!");
                            dealerWinsCounter++;
                        } else if (totalPlayerPoints > totalDealerPoints) {
                            printf("\n\nPlayer Won!!");
                            playerWinsCounter++;
                        } else {
                            if (totalDealerCards == totalPlayerCards) {
                                printf("\n\nPush!!");
                            } else {
                                if (totalDealerCards > totalPlayerCards) {
                                    printf("\n\nPlayer Won!!"); 
                                    playerWinsCounter++;
                                } else {
                                    printf("\n\nDealer Won!!");
                                    dealerWinsCounter++;
                                }
                            }
                        }
                    }

                    isPlayerOrCompBust = 'T';

                } else if (playerInp == 'q') {
                    isPlayerOrCompBust = 'T';
                    dealerWinsCounter++;
                    printf("\n\nGame Over. Dealer Wins!!");
                }
            }
            count++;
        }
        
        char isContinue;

        printf("\n\nEnter \'q\' to quit, anything else to play another hand:");
        scanf(" %c", &isContinue);

        if (isContinue == 'q') {
            isContinueGame = 'F';
            printf("\nGame Over!!\n");
        } else {
            isHoleCardHidden = 'T';
            nullifyArray(playersHand);
            nullifyArray(dealersHand);
            isPlayerOrCompBust = 'F';
            isPlayerBlackJackHand = 'F';

            printf("\n\n\n");
        }

    } while (isContinueGame == 'T');

    printf("\t\t\t Total Score\n\t\t\tDealer wins=%d\n\t\t\tPlayer wins=%d", dealerWinsCounter, playerWinsCounter);
    getch();
}