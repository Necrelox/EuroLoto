/*
** EPITECH PROJECT, 2021
** Tools
** File description:
** file_structure
*/

#ifndef FILE_STRUCTURE_H_
#define FILE_STRUCTURE_H_

#include <stdio.h>

/**
* \struct file_t
* \brief contain parameter of file
*/
typedef struct file_t
{
    FILE *file; /** file you want manage */
    char *path; /***/
    size_t head_pos; /***/
}file_s;

#endif /* !FILE_STRUCTURE_H_ */
