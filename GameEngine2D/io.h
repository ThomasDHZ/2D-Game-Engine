#pragma once
#include <stdlib.h>
#include <stdbool.h>

typedef struct fileState
{
	char* Data;
	size_t Size;
	bool Valid;
}FileState;

FileState File_Read(const char* path);
int  File_Write(void* buffer, size_t size, const char* path);