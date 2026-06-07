#ifndef INC_2026_CYBERATTACK_HIGHEST_SCORE_H
#define INC_2026_CYBERATTACK_HIGHEST_SCORE_H
struct GraphicAssets;
typedef struct {
    int dan;
    int mesec;
    int godina;
    int sat;
    int minut;
    int score;
    char dateTime[20];
}Score;
void ReadScores(struct GraphicAssets *assets);
void DodajNoviRezultat(int s);
int ReturnNumberOfLines(struct GraphicAssets *assets);


#endif //INC_2026_CYBERATTACK_HIGHEST_SCORE_H
