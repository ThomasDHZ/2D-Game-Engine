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

void List_StartUp(List* list, int elementSize)
{
	list->Data = NULL;
	list->ElementSize = elementSize;
	list->ItemCount = 0;
	list->Capacity = 0;
}

void List_Resize(List* list)
{
	void* newPtr = malloc(list->ElementSize * list->Capacity);
	memcpy(newPtr, list->Data, list->ElementSize * list->ItemCount);
	
	free(list->Data);
	list->Data = (int*)newPtr;
}

void* List_Get(List* list, size_t index)
{
	char* startMemoryAddress = (char*)list->Data;
	char* readMemoryAddress = startMemoryAddress + (index * list->ElementSize);
	return (void*)readMemoryAddress;
}

void List_Add(List* list, void* data)
{
	if (list->ItemCount >= list->Capacity)
	{
		if (list->Capacity == 0)
		{
			list->Capacity = 1;
			List_Resize(list);
		}
		else
		{
			list->Capacity *= 2;
			List_Resize(list);
		}
	}

	char* targetLocation = (char*)list->Data + (list->ItemCount * list->ElementSize);
	memcpy(targetLocation, data, list->ElementSize);

	list->ItemCount++;
}