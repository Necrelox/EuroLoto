/*
** EPITECH PROJECT, 2021
** file_insert
** File description:
** file_insert
*/

#include "file_structure.h"
#include <string.h>

int file_insert(file_s *file, size_t pos, const char *strinsert)
{
    file->file = fopen(file->path, "r+b");
    if (!file->file)
        return -1;
    fseek(file->file, 0, SEEK_END);
    size_t size = ftell(file->file);
    char buff[(size-pos)+1];
    buff[size-pos] = 0;
    fseek(file->file, pos, SEEK_SET);
    fread(buff, size-pos, 1, file->file);
    fseek(file->file, pos, SEEK_SET);
    fwrite(strinsert, strlen(strinsert), 1, file->file);
    fseek(file->file, pos + strlen(strinsert), SEEK_SET);
    fwrite(buff, size-pos, 1, file->file);
    file->head_pos = ftell(file->file);
    fclose(file->file);
    return 0;
}
