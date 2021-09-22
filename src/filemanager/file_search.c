/*
** EPITECH PROJECT, 2021
** loto
** File description:
** file_search
*/

#include "file_manager.h"
#include <stdlib.h>

size_t file_search(file_s *file, size_t pos, const char *wantbyte, size_t wantbytesize)
{
    file->file = fopen(file->path, "r");
    if (!file->file)
        return -1;
    fseek(file->file, 0, SEEK_END);
    size_t size = ftell(file->file);
    fseek(file->file, pos, SEEK_SET);

    char *bf = malloc(sizeof(char) * 1);
    for (size_t i = 0, j = 0; i < size ; ++i) {
        fread(bf, 1, 1, file->file);
        int keeppos= ftell(file->file);
        for (j = 0; bf[0] == wantbyte[j] && j < wantbytesize; ++j)
            fread(bf, 1, 1, file->file);
        if (j == wantbytesize) {
            free(bf);
            fclose(file->file);
            return keeppos;
        }
    }
    free(bf);
    file->head_pos = ftell(file->file);
    fclose(file->file);
    return -1;
}
