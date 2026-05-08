#include "highest-score.h"
#include"assets.h"
#include<stdio.h>
#include<stdlib.h>

int ReturnNumberOfLines(struct GraphicAssets *assets) {
    FILE* fajl = fopen("highest-score/scores.bit", "rb");
    if (fajl == NULL) {
        printf("Greska pri otvaranju fajla!\n");
        return 0;
    }

    fseek(fajl, 0, SEEK_END);
    long fileSize = ftell(fajl);
    int numberOfLines = (int)(fileSize / sizeof(Score));

    if (numberOfLines <= 0) {
        printf("Fajl je prazan.\n");
        fclose(fajl);
        return 0;
    }
    else {
        return numberOfLines;
    }
}

void ReadScores(struct GraphicAssets *assets) {
    FILE* fajl = fopen("highest-score/scores.bit", "rb");
    if (fajl == NULL) {
        printf("Greska pri otvaranju fajla!\n");
        return;
    }

    int numberOfLines = ReturnNumberOfLines(assets);

    if (numberOfLines <= 0) {
        printf("Fajl je prazan.\n");
        fclose(fajl);
        return;
    }

    rewind(fajl);

    if (assets->highestScores != NULL) free(assets->highestScores);
    assets->highestScores = malloc(numberOfLines * sizeof(Score));

    fread(assets->highestScores, sizeof(Score), numberOfLines, fajl);
    fclose(fajl);

    /*printf("\n--- TOP REZULTATI ---\n");
    for (int i = 0; i < numberOfLines; i++) {
        printf("%02i.%02i.%04i.\t %d\n",
                assets->highestScores[i].dan,
                assets->highestScores[i].mesec,
                assets->highestScores[i].godina,
                assets->highestScores[i].score);
    }*/

}

void DodajNoviRezultat(int d, int m, int g, int s) {
    FILE *fajl = fopen("highest-score/scores.bit", "rb");
    Score *privremeniNiz = NULL;
    int brojElemenata = 0;

    if (fajl != NULL) {
        fseek(fajl, 0, SEEK_END);
        long fileSize = ftell(fajl);
        brojElemenata = (int)(fileSize / sizeof(Score));
        rewind(fajl);

        privremeniNiz = malloc(brojElemenata * sizeof(Score));
        fread(privremeniNiz, sizeof(Score), brojElemenata, fajl);
        fclose(fajl);
    }

    Score *noviNiz = malloc((brojElemenata + 1) * sizeof(Score));
    Score novi = {d, m, g, s};

    int j = 0;
    int ubacen = 0;

    if (privremeniNiz != NULL) {
        for (int i = 0; i < brojElemenata; i++) {
            if (!ubacen && s > privremeniNiz[i].score) {
                noviNiz[j++] = novi;
                ubacen = 1;
            }
            noviNiz[j++] = privremeniNiz[i];
        }
    }
    if (!ubacen) {
        noviNiz[j] = novi;
    }

    fajl = fopen("highest-score/scores.bit", "wb");
    if (fajl != NULL) {
        fwrite(noviNiz, sizeof(Score), brojElemenata + 1, fajl);
        fclose(fajl);
    }

    if (privremeniNiz != NULL) free(privremeniNiz);
    free(noviNiz);
}