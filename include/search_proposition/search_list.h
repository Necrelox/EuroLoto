/*
** EPITECH PROJECT, 2021
** loto
** File description:
** search_list
*/

#ifndef SEARCH_LIST_H_
#define SEARCH_LIST_H_

typedef struct search_nb_t
{
    struct search_nb_t *next, *first;
    int occurence;
    int number;
}search_nb_s;

typedef struct search_luck_t
{
    struct search_luck_t *next, *first;
    int occurence;
    int number;
}search_luck_s;

#endif /* !SEARCH_LIST_H_ */
