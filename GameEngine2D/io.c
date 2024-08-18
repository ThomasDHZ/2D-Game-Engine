#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "Macro.h"

FileState File_Read(const char* path)
{
    FileState fileState = { .Valid = 0 };

    FILE* fp = fopen(path, "rb");
    if (!fp || ferror(fp))
    {
        ERROR_RETURN(fileState, IO_READ_ERROR_GENERAL, path, errno);
    }
}

int File_Write(void* buffer, size_t size, const char* path)
{
    return 0;
}
