#ifndef MY_GLOBAL_DATA_H
#define MY_GLOBAL_DATA_H

typedef struct {
    int value;
} GlobalData;

extern GlobalData g_GlobalData;

void initializeGlobalData();
void updateGlobalData(int newValue);
void printGlobalData();

#endif