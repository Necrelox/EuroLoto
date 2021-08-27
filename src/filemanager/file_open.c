/*
** EPITECH PROJECT, 2021
** file_open
** File description:
** file_open
*/

#include "file_structure.h"
#include <stdlib.h>
#include <string.h>

file_s *file_open(const char *path)
{
    file_s *file = malloc(sizeof(*file));
    if (!(file->path = strndup(path, strlen(path)))) {
        free(file);
        return NULL;
    }
    return file;
}