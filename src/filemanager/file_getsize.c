/*
** EPITECH PROJECT, 2021
** file_getsize
** File description:
** file_getsize
*/

#include "file_structure.h"

size_t file_getsize(file_s *file)
{
    file->file = fopen(file->path, "r");
    if (!file->file)
        return -1;
    fseek(file->file, 0, SEEK_END);
    size_t size = ftell(file->file);
    fclose(file->file);
    return size;
}