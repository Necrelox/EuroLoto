/*
** EPITECH PROJECT, 2021
** loto
** File description:
** oldstrtab
*/

#include <stdlib.h>
#include <stdio.h>

int count_tab_len(const char *restrict str, const char sep)
{
    int count = 0;
    for (int i = 0; str[i] != 0; i++)
        str[i] == sep ? count++: 0;
    return count + 1;
}

int count_len(const char *restrict str, char sep)
{
    int count = 0;
    static int i = 0;

    if (sep > 0) {
        while (str[i] != 0 && str[i] != sep) {
            count++;
            i++;
        }
        str[i] != 0 ? i++ : 0;
        return count;
    }
    i = 0;
    return -1;
}

#include <stdio.h>

char **str_to_word_array(const char *restrict str, char sep)
{
    int tab_len = count_tab_len(str, sep);
    char **tab = malloc(sizeof(char *) * (tab_len + 1));
    tab[tab_len] = NULL;

    for (int i = 0, j = 0, k = 0; i < tab_len; i++) {
        int len = count_len(str, sep);
        tab[i] = malloc(sizeof(char) * len + 1);
        for (k = 0; k < len && str[j] != 0 ; k++, j++)
            tab[i][k] = str[j];
        j++;
        tab[i][k] = 0;
    }
    count_len(NULL, -1);
    return tab;
}