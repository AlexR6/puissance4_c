
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>

void printGrid();
void requestUser(int *pRoundUser, char *charGrid);
bool updateGrid(bool *pIsEnd, int *pRoundUser, char *charGrid);
bool updateGridIA(bool *pIsEnd, int *pRoundUser, char *charGrid);
bool checkAllCombo(int *pRoundUser, char *chargrid);
bool checkVertical(int *pRoundUser, char *chargrid);
bool checkHorizontal(int *pRoundUser, char *chargrid);
bool checkDiagonal(int *pRoundUser, char *chargrid);
void updateRoundUser(int *pRoundUser);
double nb_aleatoire(void);
int nb_aleatoire_entre(int min, int max);

int main(void)
{
    char charGrid[43] = {
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
    };
    bool isEnd = false;
    bool *pIsEnd = &isEnd;
    int iaActive = 0;
    int roundUser = 1;
    int *pRoundUser = &roundUser;
    int i = 0;
    time_t t;

    if (time(&t) == (time_t)-1)
    {
        fprintf(stderr, "Impossible d'obtenir la date courante\n");
        return EXIT_FAILURE;
    }

    srand((unsigned)t);

    printf("Vous voulez joueur contre l'IA ou a deux ?\n");
    printf("Tapez 1 pour jouer seul ou 2 pour du duo : ");
    if (scanf("%d", &iaActive) == 1)
    {
        printGrid(charGrid);

        while (!isEnd)
        {
            if (iaActive == 1)
            {
                if (updateGridIA(pIsEnd, pRoundUser, charGrid))
                {
                    updateRoundUser(pRoundUser);
                    printGrid(charGrid);
                }
            }
            else
            {
                if (updateGrid(pIsEnd, pRoundUser, charGrid))
                {
                    updateRoundUser(pRoundUser);
                    printGrid(charGrid);
                }
            }
        }
    }
    return 0;
}

void printGrid(char *string)
{
    printf("\n ");
    for (int i = 0; i < strlen(string); i++)
    {
        if (i == 0)
        {
            for (int j = 0; j < 15; j++)
            {
                if (j % 2 == 0)
                    printf("+");
                else
                    printf("---");
            }
            printf("\n");
        }
        printf(" | ");
        printf("%c", string[i]);
        if (i == 6 || i == 13 || i == 20 || i == 27 || i == 34 || i == 41)
        {
            printf(" |");
            printf("\n ");
            for (int j = 0; j < 15; j++)
            {
                if (j % 2 == 0)
                    printf("+");
                else
                    printf("---");
            }
            printf("\n");
        }
    }
    printf(" ");
    for (int i = 0; i < 7; i++)
    {
        printf("  %d ", i + 1);
    }
    printf("\n");
    printf("\n");
}

bool updateGrid(bool *pIsEnd, int *pRoundUser, char *charGrid)
{
    printf("C'est au joueur %d de jouer : ", (*pRoundUser == 1) ? 1 : 2);
    int i = 0;
    if (scanf("%d", &i) == 1)
    {
        switch (i)
        {
        case 1:
            i = 35;
            break;
        case 2:
            i = 36;
            break;
        case 3:
            i = 37;
            break;
        case 4:
            i = 38;
            break;
        case 5:
            i = 39;
            break;
        case 6:
            i = 40;
            break;
        case 7:
            i = 41;
            break;
        default:
            printf("Veuillez saisir un chiffre entre 1 et 7 :");
            return false;
            break;
        }

        while (charGrid[i] != ' ')
        {
            i -= 7;
        }
        if (i < 0)
            return false;

        charGrid[i] = (*pRoundUser == 1) ? 'X' : 'O';
        *pIsEnd = checkAllCombo(pRoundUser, charGrid);
        return true;
    }
}

bool updateGridIA(bool *pIsEnd, int *pRoundUser, char *charGrid)
{
    int i = 0;
    if (*pRoundUser == 1)
    {
        printf("C'est a vous de jouer : ");
        if (scanf("%d", &i) == 1)
        {
            switch (i)
            {
            case 1:
                i = 35;
                break;
            case 2:
                i = 36;
                break;
            case 3:
                i = 37;
                break;
            case 4:
                i = 38;
                break;
            case 5:
                i = 39;
                break;
            case 6:
                i = 40;
                break;
            case 7:
                i = 41;
                break;
            default:
                printf("Veuillez saisir un chiffre entre 1 et 7 :");
                return false;
                break;
            }

            while (charGrid[i] != ' ')
            {
                i -= 7;
            }
            if (i < 0)
                return false;

            charGrid[i] = 'X';
            *pIsEnd = checkAllCombo(pRoundUser, charGrid);
            return true;
        }
    }
    else
    {
        printf("L'ordinateur joue...");
        Sleep(1000);
        i = nb_aleatoire_entre(1, 7);
        switch (i)
        {
        case 1:
            i = 35;
            break;
        case 2:
            i = 36;
            break;
        case 3:
            i = 37;
            break;
        case 4:
            i = 38;
            break;
        case 5:
            i = 39;
            break;
        case 6:
            i = 40;
            break;
        case 7:
            i = 41;
            break;
        default:
            printf("Veuillez saisir un chiffre entre 1 et 7 :");
            return false;
            break;
        }
        while (charGrid[i] != ' ')
        {
            i -= 7;
        }
        if (i < 0)
            return false;

        charGrid[i] = 'O';
        *pIsEnd = checkAllCombo(pRoundUser, charGrid);
        return true;
    }
}

bool checkAllCombo(int *pRoundUser, char *charGrid)
{
    if (checkVertical(pRoundUser, charGrid) || checkHorizontal(pRoundUser, charGrid) || checkDiagonal(pRoundUser, charGrid))
        return true;

    return false;
}

bool checkHorizontal(int *pRoundUser, char *charGrid)
{
    char roundUser = (*pRoundUser == 1) ? 'X' : 'O';

    for (int i = 0; i < 42; i += 7)
    {
        if (charGrid[i] == roundUser && charGrid[i + 1] == roundUser && charGrid[i + 2] == roundUser && charGrid[i + 3] == roundUser ||
            charGrid[i + 1] == roundUser && charGrid[i + 2] == roundUser && charGrid[i + 3] == roundUser && charGrid[i + 4] == roundUser ||
            charGrid[i + 2] == roundUser && charGrid[i + 3] == roundUser && charGrid[i + 4] == roundUser && charGrid[i + 5] == roundUser ||
            charGrid[i + 3] == roundUser && charGrid[i + 4] == roundUser && charGrid[i + 5] == roundUser && charGrid[i + 6] == roundUser)
        {
            printf("Le joueur %d a gagner la partie", *pRoundUser);
            return true;
        }
    }
    return false;
}
bool checkVertical(int *pRoundUser, char *charGrid)
{
    char roundUser = (*pRoundUser == 1) ? 'X' : 'O';

    for (int i = 0; i < 7; i++)
    {
        if (charGrid[i] == roundUser && charGrid[i + 7] == roundUser && charGrid[i + 14] == roundUser && charGrid[i + 21] == roundUser ||
            charGrid[i + 7] == roundUser && charGrid[i + 14] == roundUser && charGrid[i + 21] == roundUser && charGrid[i + 28] == roundUser ||
            charGrid[i + 14] == roundUser && charGrid[i + 21] == roundUser && charGrid[i + 28] == roundUser && charGrid[i + 35] == roundUser)
        {
            printf("Le joueur %d a gagner la partie\n", *pRoundUser);
            return true;
        }
    }
    return false;
}
bool checkDiagonal(int *pRoundUser, char *charGrid)
{
    char roundUser = (*pRoundUser == 1) ? 'X' : 'O';

    for (int i = 0; i < 42; i++)
    {
        if (charGrid[i] == roundUser && charGrid[i - 6] == roundUser && charGrid[i - 12] == roundUser && charGrid[i - 18] == roundUser ||
            charGrid[i] == roundUser && charGrid[i + 6] == roundUser && charGrid[i + 12] == roundUser && charGrid[i + 18] == roundUser ||
            charGrid[i] == roundUser && charGrid[i + 8] == roundUser && charGrid[i + 16] == roundUser && charGrid[i + 24] == roundUser ||
            charGrid[i] == roundUser && charGrid[i - 8] == roundUser && charGrid[i - 16] == roundUser && charGrid[i - 24] == roundUser)
        {
            printf("Le joueur %d a gagner la partie\n", *pRoundUser);
            return true;
        }
    }
    return false;
}

void updateRoundUser(int *pRoundUser)
{
    if (*pRoundUser == 1)
        *pRoundUser = 2;
    else
        *pRoundUser = 1;
}

double nb_aleatoire(void)
{
    return rand() / (RAND_MAX + 1.);
}

int nb_aleatoire_entre(int min, int max)
{
    return nb_aleatoire() * (max - min + 1) + min;
}