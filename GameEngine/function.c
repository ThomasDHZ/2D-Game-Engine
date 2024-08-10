#include "function.h"
#include <stdio.h>

GlobalData g_GlobalData;

void initializeGlobalData() {
    g_GlobalData.value = 0;
}

void updateGlobalData(int newValue) {
    g_GlobalData.value = newValue;
}

void printGlobalData() {
    printf("Global Data Value: %d\n", g_GlobalData.value);
}