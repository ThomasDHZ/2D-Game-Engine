#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vcruntime_string.h>
#include "mouse.h"

typedef struct
{
	void* Data;
	int ElementSize;
	int ItemCount;
	int Capacity;
}List;

void  List_StartUp(List* list, int elementSize);
void* List_GetElement(List* list, size_t index);
void  List_Add(List* list, void* data);
void  List_Remove(List* list, int index);
void  List_FreeMemory(List* list);