// Rajout de l'option -O3 pour gcc pour la release avec gcc

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "constraint.h"
#include "util.h"
#include "initTest.h"
#include "file.h"

int indice = 0;
unsigned long long noeud = 0;

/***********************************************************************************************************************
* FONCTION DE VERIFICATION
***********************************************************************************************************************/

int checkFutoshiki(int indice);

/* Change les valeurs et v�rifie la r�solution du futoshiki */
int changerValeur()
{
    // Cette case n'est pas initilias�e
    if (grid[indice].value == 0) {
        grid[indice].value = 1;
    		noeud++;
    }

    // Evite de lancer de lancer plusieur fois la v�rification = Gain de temps
    int resultatCheck = checkFutoshiki(indice);

    // Si le futoshiki n'est a ce point pas correcte, il faut changer les valeurs plac�es
    if (resultatCheck >= 0 && grid[indice].canChange == true) {
        // la valeur maximale est atteinte pour cette case
        while (grid[indice].value == gridSize && grid[indice].canChange == true) {
            // place cette valeur de nouveau a 0
            grid[indice].value = 0;
            // si indice == 0, nous avons essay� toutes les valeurs
            if (indice != 0) {
                indice--;
                while (grid[indice].canChange == false) {
                    if (indice != 0)
                        indice--;
                    else {
                        color(COLOR_RED);
                        printf ("\nPas de solution : %f\n", getTimer());
                        printf ("Nombre de noeuds parcouru %llu\n\n", noeud);
                        color(COLOR_WHITE);
                        return false;
                    }
                }
            }
            else {
                stopChrono();
                color(COLOR_RED);
                printf ("\nPas de solution en %f\n", getTimer());
                printf ("Nombre de noeuds parcouru %llu\n\n", noeud);
                color(COLOR_WHITE);
                return false;
            }
        }

        // incr�mente la valeur de la case
        grid[indice].value++;
        noeud++;
    }
    else if (resultatCheck < 0 && indice == gridSize*gridSize -1) {
        stopChrono();
        color(COLOR_GREEN);
        printf ("\tSolution trouv�e en %f !\n", getTimer());
        printf ("\tNombre de noeuds parcouru %llu\n\n", noeud);
        color(COLOR_WHITE);
        return true;
    }
    else // on avance d'une case
        indice++;

    return -1;
}

/***********************************************************************************************************************
* Renvoie -1 si il y a pas de probl�me sinon il renvoi l'indice o� une des contrainte est viol�e
* Par exemple si il y a deux fois le m�me chiffre dans la m�me colonne
***********************************************************************************************************************/
int checkFutoshiki(int indice) {
    // Line verification
    for(int i = indice - indice%gridSize; i < indice - indice%gridSize + gridSize; ++i) {
        if(grid[indice].value != 0 && i != indice && grid[i].value == grid[indice].value) {
            #ifdef VERBOSE
                color(COLOR_BLUE);
                for (int j = 0; j < gridSize * gridSize; ++j) {
                    if(j == i || j == indice) color(COLOR_RED);
                    if (j % gridSize == 0) printf("\n");
                    printf("\t%d", grid[j].value);
                    if(j == i || j == indice) color(COLOR_BLUE);
                }
                color(COLOR_WHITE);
                printf("\n");
                sleep(1);
            #endif /* VERBOSE */

            return i;
        }
    }

    // Column verification
    for(int i = indice%gridSize; i < gridSize*gridSize; i += gridSize) {
        if(grid[indice].value != 0 && i != indice && grid[i].value == grid[indice].value) {
            #ifdef VERBOSE
                color(COLOR_BLUE);
                for (int j = 0; j < gridSize * gridSize; ++j) {
                    if(j == i || j == indice) color(COLOR_RED);
                    if (j % gridSize == 0) printf("\n");
                    printf("\t%d", grid[j].value);
                    if(j == i || j == indice) color(COLOR_BLUE);
                }
                color(COLOR_WHITE);
                printf("\n");
                sleep(1);
            #endif /* VERBOSE */
            return i;
        }
    }

    for(int i = 0; i < tailleTabContrainte; ++i) {
        if(checkContrainte(&tabContrainte[i]) == false)
            return i;
        else
            posContrainte++;
    }

    return -1;
}

int backTrack() {
    int res = -1;
    indice = 0;

    while(res < 0) {
        res = changerValeur();

        if(res == true) {
            #ifndef DEBUG
                //clearScreen();
                printBeautifulGrid(COLOR_BLUE);
            #endif
            #ifdef DEBUG
                printBeautifulGrid(COLOR_BLUE);
                sleep(SLEEP_TIME);
            #endif /* DEBUG */
            return true;
        }
    }

    return false;
}

// TODO : Faire le tableau de domaine (tableau de liste chain�e surement sera le plus simple)
int forwardChecking() {
    return false;
}

/* Retourne -1 si aucune solution, dans le cas ou il existe une solution renvoie 1 */
void resolveFutoshiki(int (*f)()) {
    startChrono();
    f();
}

int main(int argc, char* argv[]) {
    if((argc - 1) != 1) {
        color(COLOR_RED);
        printf("Erreur d'argument\n");
        color(COLOR_WHITE);
        return -1;
    }

    signal(SIGINT, logOnStop);

    clearScreen();

    readGrid(argv[1]);

    resolveFutoshiki(backTrack);

    /* Lancement de tous les tests unitaires (Avec l'option cmake DEBUG seulement) */
    #ifdef DEBUG
        printf("\n\n===> TEST UNIT\n\n");

        printf("==> TEST : checkFutoshiki()\n\n");
        // Test de la v�rification de la grille
        runTestWithIntArg(checkFutoshiki, initCheckFutoTest1, -1, 0);
        runTestWithIntArg(checkFutoshiki, initCheckFutoTest2, 4, 3);
        runTestWithIntArg(checkFutoshiki, initCheckFutoTest3, gridSize, 0);
        runTestWithIntArg(checkFutoshiki, initCheckFutoTest4, -1, 0);
        runTestWithIntArg(checkFutoshiki, initCheckFutoTest5, 4*gridSize + 3, 3);
        runTestWithIntArg(checkFutoshiki, initCheckFutoTest6, gridSize*3 + 1, gridSize*3);
        runTestWithIntArg(checkFutoshiki, initCheckFutoTest7, gridSize*4 + gridSize - 2, gridSize*4 + gridSize - 1);
        runTestWithIntArg(checkFutoshiki, initCheckFutoTest8, gridSize*2, gridSize*4);

        if(gridSize == 6)
            runTestWithIntArg(checkFutoshiki, initCheckFutoTest9, -1, 15);

        printf("\n==> TEST : testContrainte()\n\n");
        // Test de la v�rification des contraintes
        runTest(testContrainte, initContrainte1, false);
        runTest(testContrainte, initContrainte2, true);
        runTest(testContrainte, initContrainte3, true);
        runTest(testContrainte, initContrainte4, false);

        printf("\n===> TEST : backTrack() \n\n");
        runTest(backTrack, initBacktrackTest, true);
        runTest(backTrack, initBacktrackTest2, false);
    #endif /* DEBUG */

    return 0;
}
