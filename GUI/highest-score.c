#include "highest-score.h"
#include"assets.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int ReturnNumberOfLines(struct GraphicAssets *assets) {
    FILE* fajl = fopen("documents/scores.bit", "rb");
    if (fajl == NULL) {
        printf("Greska pri otvaranju fajla!\n");
        return 0;
    }

    fseek(fajl, 0, SEEK_END);
    long fileSize = ftell(fajl);
    fclose(fajl);
    int numberOfLines = (int)(fileSize / sizeof(Score));

    if (numberOfLines <= 0) {
        printf("Fajl je prazan.\n");
        return 0;
    }
    else {
        return numberOfLines;
    }
}

void ReadScores(struct GraphicAssets *assets) {
    FILE* fajl = fopen("documents/scores.bit", "rb");
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
        printf("%02i.%02i.%04i. %02d:%02d\t %d\n",
                assets->highestScores[i].dan,
                assets->highestScores[i].mesec,
                assets->highestScores[i].godina,
                assets->highestScores[i].sat,
                assets->highestScores[i].minut,
                assets->highestScores[i].score);
    }*/

}

void DodajNoviRezultat(int s) {
    FILE *fajl = fopen("documents/scores.bit", "rb");
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
    time_t t = time(NULL);
    struct tm *currTime = localtime(&t);
    int dan = currTime->tm_mday;
    int mesec = currTime->tm_mon+1;
    int godina = currTime->tm_year + 1900;
    int sat = currTime->tm_hour;
    int minut = currTime->tm_min;

    Score *noviNiz = malloc((brojElemenata + 1) * sizeof(Score));
    Score novi = {dan, mesec, godina, sat, minut, s};

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

    fajl = fopen("documents/scores.bit", "wb");
    if (fajl != NULL) {
        fwrite(noviNiz, sizeof(Score), brojElemenata + 1, fajl);
        fclose(fajl);
    }

    if (privremeniNiz != NULL) free(privremeniNiz);
    free(noviNiz);
}