#ifndef INC_2026_CYBERATTACK_PAUSEMENI_H
#define INC_2026_CYBERATTACK_PAUSEMENI_H

#include"glavniMeni.h"
extern int isPaused;
extern MeniOpcija opcijePause[5];

void ResumeGame();
void HighestScores2();
void Settings2();
void Controls2();
void ExitAndSave();

void CrtajPause();
void InitPause();

#endif //INC_2026_CYBERATTACK_PAUSEMENI_H
