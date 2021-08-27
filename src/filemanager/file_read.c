/*
** EPITECH PROJECT, 2021
** file_read
** File description:
** file_read
*/

#include "file_structure.h"
#include <stdlib.h>

char *file_read(file_s *file, size_t size, size_t pos)
{
    file->file = fopen(file->path, "r");
    if (!file->file)
        return NULL;
    fseek(file->file, pos, SEEK_SET);
    file->head_pos = ftell(file->file);
    char *buff = malloc(sizeof(char) * size + 1);
    fread(buff, size, 1, file->file);
    buff[size] = 0;
    fclose(file->file);
    return buff;
}