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

char grid[MAX_SIZE][MAX_SIZE];

typedef struct {
	int v1[2], v2[2];
	char contrainte;
} Contrainte;

typedef struct Contrainte{
	int* v1, *v2;
	char contrainte;
} Contrainte;

void initContrainte(Contrainte* contrainte, int a[], int b[], char c)
{
	contrainte->v1 = a;
	contrainte->v2 = b;
	contrainte->contrainte = c;
}

int checkContrainte(Contrainte* c)
{
	switch (c->contrainte)
	{
	case '<':
	  return grid[c->v1[0]][c->v1[1]] < grid[c->v2[0]][c->v2[1]];
	case '>':
	  return grid[c->v1[0]][c->v1[1]] > grid[c->v2[0]][c->v2[1]];
	case '^':
	  return grid[c->v1[0]][c->v1[1]] < grid[c->v2[0]][c->v2[1]];
  	case 'v':
	  return grid[c->v1[0]][c->v1[1]] > grid[c->v2[0]][c->v2[1]];
	}
	return -1;
}

// typedef struct {
//} Domaine;

//Domaine grille[10][10];

/* Initialise les données de la grille */
void gridLineManager(char* line, int nbLine) {
    int cpt = 0;
    for(int i = 0; i < (int)strlen(line); ++i)
    {
        if(line[i] != ' ' && line[i] != '\0' && line[i] != '\n') {
            grid[nbLine][cpt] = line[i];
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

        int nbLinee = 0;
        while(fgets(buff, MAX_SIZE, file) != NULL) {
            gridLineManager(buff, nbLinee);
            nbLinee++;
        }

        fclose(file);
    }
}

/* Affiche la grille */
void printGrid() {
	for(int i = 0; i < gridSize*2 - 1; ++i) {
        printf("\n");

        for(int j = 0; j < gridSize; ++j)
            if(grid[i][j] != '.' && grid[i][j] != '>'
                    && grid[i][j] != '<' && grid[i][j] != '^' && grid[i][j] != 'v' && grid[i][j] != 0)
                printf("%5c", grid[i][j]);
            else
                printf("%5c", grid[i][j]);
    }
}

/* Retourne -1 si aucune solution, dans le cas ou il existe une solution renvoie 1 */
int resolveFutoshiki() {

    // En attendant que l'algorithme soit fait, afin d'afficher la grille à tous les coups
    if(DEBUG)
        return 0;

    return -1;
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

    for(int i = 0; i < (((gridSize)/2)*3) - 1; ++i)
        printf("%c", '=');

    printf(" FUTOSHIKI ");

    for(int i = 0; i < (((gridSize)/2)*3) - 1; ++i)
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

    for(int i = 0; i < ((gridSize)*4) + 1; ++i)
    printf("%c", '=');

    printf("\n");

    return 0;
}
