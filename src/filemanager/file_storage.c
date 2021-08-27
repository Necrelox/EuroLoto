/*
** EPITECH PROJECT, 2021
** loto
** File description:
** file_storage
*/

#include "file_structure.h"

file_s *file_storage_getset(short action, void *file)
{
    static file_s *storefile = NULL;
    if (action == -2010)
        storefile = (file_s *)file;
    else if (action == 2010)
        return storefile;
    return NULL;
}