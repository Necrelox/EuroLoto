/*
** EPITECH PROJECT, 2021
** Tools
** File description:
** check_file
*/

#include <unistd.h>

short file_check(const char *path, int what)
{
    return access(path, what);
}