// Rajout de l'option -O3 pour gcc pour la release avec gcc

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 500
#define DEBUG 1

#define COLOR_BLACK "30"
#define COLOR_RED "31"
#define COLOR_GREEN "32"
#define COLOR_YELLOW "33"
#define COLOR_BLUE "34"
#define COLOR_WHITE "37"

#define color(param) printf("\033[%sm",param)

int gridSize = 0;

char grid[MAX_SIZE * MAX_SIZE];
char gridBis[MAX_SIZE][MAX_SIZE];
Contrainte* tabContrainte = NULL;
int tailleTab = 0;

typedef struct Contrainte{
    int v1, v2;
    char contrainte;
} Contrainte;

/* Met a jour la taille du tableau et ajoute la nouvelle contrainte */
void majContrainte (Contrainte) {
    tailleTab += 1;
    realloc(tabContrainte, tailleTab * sizeof(Contrainte));
    tabContrainte[tailleTab] = Contrainte;
}

/* Initialise la contrainte */
void initContrainte(Contrainte* contrainte, int a, int b, char c)
{
    contrainte->v1 = a;
    contrainte->v2 = b;
    contrainte->contrainte = c;
}


/* Adapte la taille du tableau a l'ajout d'une nouvelle contrainte */
void addContrainte (int a, int b, char c)
{
    Contrainte contrainte;
    initContrainte(contrainte, a, b, c);
    majContrainte(contrainte);
}


/* Renvoie le résultat de la vérification de contrainte */
int checkContrainte(Contrainte* c)
{
    switch (c->contrainte)
    {
        case '<':
            return grid[c->v1] < grid[c->v2];
        case '>':
            return grid[c->v1] > grid[c->v2];
        case '^':
            return grid[c->v1] < grid[c->v2];
        case 'v':
            return grid[c->v1] > grid[c->v2];
    }
    return -1;
}

/* Initialise les données de la grille
*  élément courant : nbLine * gridSize + i */
void gridLineManager(char* line, int nbLine) {
    int cpt = 0;
    for(int i = 0; i < (int)strlen(line); ++i)
    {
        if (line[i] == '<' || line[i] == '>')
            addContrainte(nbLine * gridSize + i, nbLine * gridSize + i + 1, line[i]);
        else if (line[i] == '^' ||line[i] == 'v')
            addContrainte(nbLine * gridSize + i, (nbLine + 1) * gridSize + i, line[i]);
        else if(line[i] != ' ' && line[i] != '\0' && line[i] != '\n') {
            gridBis[nbLine][cpt] = line[i];
            cpt++;
        }
    }
}

/* Lit le fichier en paramètre */
void readGrid(const char* path) {
    FILE* file = NULL;

    char buff[MAX_SIZE];

    file = fopen(path, "r");

    if (file != NULL) {
        fgets(buff, MAX_SIZE, file);
        gridSize = atoi(buff);

        int nbLigne = 0;
        while(fgets(buff, MAX_SIZE, file) != NULL) {
            gridLineManager(buff, nbLigne);
            nbLigne++;
        }

        fclose(file);
    }
}

/* Affiche la grille */
void printGrid() {
	for(int i = 0; i < gridSize*2 - 1; ++i) {
        printf("\n");

        for(int j = 0; j < gridSize; ++j)
                printf("%5c", gridBis[i][j]);
    }
}

/* Retourne -1 si aucune solution, dans le cas ou il existe une solution renvoie 1 */
int resolveFutoshiki() {

    // En attendant que l'algorithme soit fait, afin d'afficher la grille à tous les coups
    if(DEBUG)
        return 0;

    return -1;
}

void initTest1() {
    // Initialisation de la première ligne
    for(int i = 0; i < gridSize; ++i)
        grid[i] = '0' + i;

    // Initialisation de la première colonne
    for(int i = gridSize - 1; i < 2*gridSize; ++i)
        grid[i] = '0' + i;

    for(int i = 2*gridSize - 1; i < 3*gridSize; ++i)
        grid[i] = '0' + i;

    for(int i = 3*gridSize - 1; i < 4*gridSize; ++i)
        grid[i] = '0' + i;

}

void initTest2() {
    // Initialisation de la première ligne
    for(int i = 0; i < gridSize; ++i)
        grid[i] = '0' + i;

    // Initialisation de la première colonne
    for(int i = gridSize - 1; i < 2*gridSize; ++i)
        grid[i] = '0' + i;

    for(int i = 2*gridSize - 1; i < 3*gridSize; ++i)
        grid[i] = '0' + i;

    for(int i = 3*gridSize - 1; i < 4*gridSize; ++i)
        grid[i] = '0' + i;

    grid[3] = '0' + 4;
}

void initTest3() {
    // Initialisation de la première ligne
    for(int i = 0; i < gridSize; ++i)
        grid[i] = '0' + i;

    // Initialisation de la première colonne
    for(int i = gridSize - 1; i < 2*gridSize; ++i)
        grid[i] = '0' + i;

    for(int i = 2*gridSize - 1; i < 3*gridSize; ++i)
        grid[i] = '0' + i;

    for(int i = 3*gridSize - 1; i < 4*gridSize; ++i)
        grid[i] = '0' + i;

    grid[gridSize+3] = '0' + 4;
}

void initTest4() {
    // Initialisation de la première ligne
    for(int i = 0; i < gridSize; ++i)
        grid[i] = '0' + i;

    // Initialisation de la première colonne
    for(int i = gridSize - 1; i < 2*gridSize; ++i)
        grid[i] = '0' + i;

    for(int i = 2*gridSize - 1; i < 3*gridSize; ++i)
        grid[i] = '0' + i;

    for(int i = 3*gridSize - 1; i < 4*gridSize; ++i)
        grid[i] = '0' + i;


    grid[3*gridSize+2] = '0' + 2;
}

void initTest5() {
    // Initialisation de la première ligne
    for(int i = 0; i < gridSize; ++i)
        grid[i] = '0' + i;

    // Initialisation de la première colonne
    for(int i = gridSize - 1; i < 2*gridSize; ++i)
        grid[i] = '0' + i;

    for(int i = 2*gridSize - 1; i < 3*gridSize; ++i)
        grid[i] = '0' + i;

    for(int i = 3*gridSize - 1; i < 4*gridSize; ++i)
        grid[i] = '0' + i;

    grid[3*gridSize+1] = '0' + 2;
}


void initTest6() {
    for(int i = 0; i < gridSize; ++i)
        grid[i] = '0' + i;

    for(int i = gridSize - 1; i < 2*gridSize; ++i)
        grid[i] = '0' + i;

    for(int i = 2*gridSize - 1; i < 3*gridSize; ++i)
        grid[i] = '0' + i;

    for(int i = 3*gridSize - 1; i < 4*gridSize; ++i)
        grid[i] = '0' + i;


    grid[3*gridSize+1] = '0' + 2;
    grid[3*gridSize] = '0' + 2;
}

int checkFutushiki() {
    int nbColCheck = 1;
    for(int i = 0; i < gridSize*4 - 1; ++i) {
        for(int j = nbColCheck * gridSize - 1; j > 0; --j) {
            if (i != j && (j - 1)%4 == i%4 && grid[i] == grid[j]) {
                return 1;
            }
            
            // Inutile maintenant à voir si d'autre bug apparait
            /*
            if(i == j%nbColCheck && grid[i] == grid[j + gridSize * nbColCheck])
                return 1;
            */
        }
        nbColCheck++;
    }

    return 0;
}

void runTest(int (*f)(), void (*init)(), int result) {

    (*init)();
    int r = (*f)();

    printf("Run Test : ");

    if(r == result) {
        color(COLOR_GREEN);
        printf("OK\n");
        color(COLOR_WHITE);
    }
    else {
        color(COLOR_RED);
        printf("Fail\n");
        color(COLOR_WHITE);
        exit(-1);
    }
}
/* Ne plus toucher à cette fonction */
int main(int argc, char* argv[]) {

    if((argc - 1) != 1) {
		printf("Erreur d'argument\n");
        return -1;
	}

    printf("\033[H\033[2J"); // Efface la console sous linux

    readGrid(argv[1]);
    
    printf("    ");

    for(int i = 0; i < ((gridSize*5)/2) - 6; ++i)
        printf("%c", '=');

    printf(" FUTOSHIKI ");

    for(int i = 0; i < ((gridSize*5)/2) - 6; ++i)
        printf("%c", '=');

    int res = resolveFutoshiki();

    if(res < 0) {
        printf("La grille n'a pas de solution\n");
        return 0;
    }

    color(COLOR_GREEN); // Vert

    printGrid();

    color(COLOR_WHITE); // Blanc

    printf("\n    ");

    for(int i = 0; i < ((gridSize)*5) - 2; ++i)
    printf("%c", '=');

    printf("\n");

    runTest(checkFutushiki, initTest1, 0);
    runTest(checkFutushiki, initTest2, 1);
    runTest(checkFutushiki, initTest3, 0);
    runTest(checkFutushiki, initTest4, 1);
    runTest(checkFutushiki, initTest5, 0);
    runTest(checkFutushiki, initTest6, 1);

    return 0;
}