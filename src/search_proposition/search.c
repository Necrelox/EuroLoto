/*
** EPITECH PROJECT, 2021
** loto
** File description:
** search
*/

#include "file_manager.h"
#include "datamanager.h"
#include "search_list.h"
#include "ech_twister.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define LOTO 1
#define EURO 2

void free_nb_list(search_nb_s *list)
{
    list = list->first;
    for (search_nb_s *tmp; list;) {
        tmp = list;
        list = list->next;
        free(tmp);
    }
}

void free_luck_list(search_luck_s *list)
{
    list = list->first;
    for (search_luck_s *tmp; list;) {
        tmp = list;
        list = list->next;
        free(tmp);
    }
}

search_luck_s *get_node_luck_list(search_luck_s *list, int number)
{
    search_luck_s *tmp = list->first;
    for (; tmp && tmp->number != number; tmp = tmp->next);
    if (tmp)
        return tmp;
    return NULL;
}

search_nb_s *get_node_nb_list(search_nb_s *list, int number)
{
    search_nb_s *tmp = list->first;
    for (; tmp && tmp->number != number; tmp = tmp->next);
    if (tmp)
        return tmp;
    return NULL;
}

int add_node_search_luck_list(search_luck_s **searchlist, int number)
{
    search_luck_s *new = malloc(sizeof(*new));
    if (!new)
        return -1;
    new->number = number;
    new->occurence = 0;
    new->next = NULL;
    if (!(*searchlist)) {
        (*searchlist) = new;
        (*searchlist)->first = (*searchlist);
    } else {
        (*searchlist)->next = new;
        new->first = (*searchlist)->first;
        *(searchlist) = (*searchlist)->next;
    }
    return 0;
}

int add_node_search_nb_list(search_nb_s **searchlist, int number)
{
    search_nb_s *new = malloc(sizeof(*new));
    if (!new)
        return -1;
    new->number = number;
    new->occurence = 0;
    new->next = NULL;
    if (!(*searchlist)) {
        (*searchlist) = new;
        (*searchlist)->first = (*searchlist);
    } else {
        (*searchlist)->next = new;
        new->first = (*searchlist)->first;
        *(searchlist) = (*searchlist)->next;
    }
    return 0;
}

void propose_loto(search_nb_s *list_nb, search_luck_s *list_luck)
{
    int max_occurence_nb = 0;
    int max_occurence_luck = 0;
    int if_propose_nb[15];
    int if_propose_luck[3];

    for (search_nb_s *tmp = list_nb->first; tmp; tmp = tmp->next)
        max_occurence_nb = max_occurence_nb < tmp->occurence ? tmp->occurence : max_occurence_nb;
    for (search_luck_s *tmp = list_luck->first; tmp; tmp = tmp->next)
        max_occurence_luck = max_occurence_luck < tmp->occurence ? tmp->occurence : max_occurence_luck;

    printf("Les 15 Nombres qui reviennent le plus souvent sont : \n");
    for (int i = 0 ; i < 15 ;) {
        for (search_nb_s *tmp = list_nb->first; tmp && i < 15; tmp = tmp->next)
            if (max_occurence_nb == tmp->occurence) {
                printf("- [\e[1;93m%d\e[0m] qui revient \e[1;93m%d\e[0m fois\n", tmp->number, tmp->occurence);
                if_propose_nb[i] = tmp->number;
            ++i;
            }
        --max_occurence_nb;
    }
    printf("\nLes trois étoiles qui reviennent le plus souvent sont : \n");
    for (int i = 0 ; i < 3 ;) {
        for (search_luck_s *tmp = list_luck->first; tmp && i < 3; tmp = tmp->next)
            if (max_occurence_luck == tmp->occurence) {
                printf("- [\e[1;93m%d\e[0m] qui revient \e[1;93m%d\e[0m fois\n", tmp->number, tmp->occurence);
                if_propose_luck[i] = tmp->number;
                ++i;
            }
        --max_occurence_luck;
    }
    printf("\nVoulez vous des propositions ? (oui ou non)\n");
    char rep[4];
    scanf("%s", rep);
    if (strcmp(rep, "oui") == 0) {
        ECHMT_S search = ech_seedRand(time(NULL));
        for (int i = 0; i < 3 ; ++i) {
            int propose[6];
            for (int j = 0; j < 5 ; ++j) {
                int head = ech_genRandom(&search) % 15;
                while (if_propose_nb[head] == -1)
                    head = ech_genRandom(&search) % 15;
                propose[j] = if_propose_nb[head];
                if_propose_nb[head] = -1;
            }
            int head = ech_genRandom(&search) % 3;
            while (if_propose_luck[head] == -1)
                head = ech_genRandom(&search) % 3;
            propose[5] = if_propose_luck[head];
            if_propose_luck[head] = -1;
            printf("\e[1;92mProposition numéro %d : [\e[1;93m%d\e[1;92m]\e[1;92m [\e[1;93m%d\e[1;92m]\e[1;92m [\e[1;93m%d\e[1;92m]\e[1;92m [\e[1;93m%d\e[1;92m]\e[1;92m [\e[1;93m%d\e[1;92m]\e[1;92m et l'étoile [\e[1;93m%d\e[1;92m]\e[0m\n"
                , i+1, propose[0], propose[1], propose[2], propose[3], propose[4], propose[5]);
        }
    }
}

void propose_euro(search_nb_s *list_nb, search_luck_s *list_luck)
{
    int max_occurence_nb = 0;
    int max_occurence_luck = 0;
    int if_propose_nb[15];
    int if_propose_luck[6];

    for (search_nb_s *tmp = list_nb->first; tmp; tmp = tmp->next)
        max_occurence_nb = max_occurence_nb < tmp->occurence ? tmp->occurence : max_occurence_nb;
    for (search_luck_s *tmp = list_luck->first; tmp; tmp = tmp->next)
        max_occurence_luck = max_occurence_luck < tmp->occurence ? tmp->occurence : max_occurence_luck;

    printf("Les 15 Nombres qui reviennent le plus souvent sont : \n");
    for (int i = 0 ; i < 15 ;) {
        for (search_nb_s *tmp = list_nb->first; tmp && i < 15; tmp = tmp->next)
            if (max_occurence_nb == tmp->occurence) {
                printf("- [\e[1;93m%d\e[0m] qui revient \e[1;93m%d\e[0m fois\n", tmp->number, tmp->occurence);
                if_propose_nb[i] = tmp->number;
                ++i;
            }
        --max_occurence_nb;
    }
    printf("\nLes six étoiles qui reviennent le plus souvent sont : \n");
    for (int i = 0 ; i < 6 ;) {
        for (search_luck_s *tmp = list_luck->first; tmp && i < 6; tmp = tmp->next)
            if (max_occurence_luck == tmp->occurence) {
                printf("- [\e[1;93m%d\e[0m] qui revient \e[1;93m%d\e[0m fois\n", tmp->number, tmp->occurence);
                if_propose_luck[i] = tmp->number;
                ++i;
            }
        --max_occurence_luck;
    }

    printf("\nVoulez vous des propositions ? (oui ou non)\n");
    char rep[4];
    scanf("%s", rep);
    if (strcmp(rep, "oui") == 0) {
        ECHMT_S search = ech_seedRand(time(NULL));
        for (int i = 0; i < 3 ; ++i) {
            int propose[7];
            for (int j = 0; j < 5 ; ++j) {
                int head = ech_genRandom(&search) % 15;
                while (if_propose_nb[head] == -1)
                    head = ech_genRandom(&search) % 15;
                propose[j] = if_propose_nb[head];
                if_propose_nb[head] = -1;
            }
            for (int j = 0 ; j < 2 ; ++j) {
                int head = ech_genRandom(&search) % 6;
                while (if_propose_luck[head] == -1)
                    head = ech_genRandom(&search) % 6;
                propose[5 + j] = if_propose_luck[head];
                if_propose_luck[head] = -1;
            }
            printf("\e[1;92mProposition numéro %d : [\e[1;93m%d\e[1;92m]\e[1;92m [\e[1;93m%d\e[1;92m]\e[1;92m [\e[1;93m%d\e[1;92m]\e[1;92m [\e[1;93m%d\e[1;92m]\e[1;92m [\e[1;93m%d\e[1;92m]\e[1;92m et les étoiles [\e[1;93m%d\e[1;92m] [\e[1;93m%d\e[1;92m] \e[0m\n"
                , i+1, propose[0], propose[1], propose[2], propose[3], propose[4], propose[5], propose[6]);
        }
    }
}

void search_occurence_loto(search_nb_s *list_nb, search_luck_s *list_luck)
{
    file_s *floto = file_open("./database/loto.ech");
    data_s read;
    floto->file = fopen(floto->path, "r");

    while (fscanf(floto->file, "[%d/%d/%d] : Number : %d %d %d %d %d Lucky Number : %d\n",
           &read.day, &read.month, &read.years,
        &read.number[0], &read.number[1], &read.number[2],
        &read.number[3], &read.number[4], &read.luck_number[0]) != EOF) {
        get_node_nb_list(list_nb, read.number[0])->occurence += 1;
        get_node_nb_list(list_nb, read.number[1])->occurence += 1;
        get_node_nb_list(list_nb, read.number[2])->occurence += 1;
        get_node_nb_list(list_nb, read.number[3])->occurence += 1;
        get_node_nb_list(list_nb, read.number[4])->occurence += 1;
        get_node_luck_list(list_luck, read.luck_number[0])->occurence += 1;
    }
    fclose(floto->file);
    file_struct_destroy(floto, 1);
}

void search_occurence_euro(search_nb_s *list_nb, search_luck_s *list_luck)
{
    file_s *feuro = file_open("./database/euro.ech");
    data_s read;
    feuro->file = fopen(feuro->path, "r");

    while (fscanf(feuro->file, "[%d/%d/%d] : Number : %d %d %d %d %d Lucky Number : %d %d\n",
           &read.day, &read.month, &read.years,
        &read.number[0], &read.number[1], &read.number[2],
        &read.number[3], &read.number[4], &read.luck_number[0], &read.luck_number[1]) != EOF) {
        get_node_nb_list(list_nb, read.number[0])->occurence += 1;
        get_node_nb_list(list_nb, read.number[1])->occurence += 1;
        get_node_nb_list(list_nb, read.number[2])->occurence += 1;
        get_node_nb_list(list_nb, read.number[3])->occurence += 1;
        get_node_nb_list(list_nb, read.number[4])->occurence += 1;
        get_node_luck_list(list_luck, read.luck_number[0])->occurence += 1;
        get_node_luck_list(list_luck, read.luck_number[1])->occurence += 1;
    }
    fclose(feuro->file);
    file_struct_destroy(feuro, 1);
}

int search_and_propose(short want)
{
   search_nb_s *list_nb = NULL;
   search_luck_s *list_luck = NULL;

    if (want == LOTO) {
        for (int i = 0; i < 49; ++i) {
            if (add_node_search_nb_list(&list_nb, i + 1) < 0) {
                free_nb_list(list_nb);
                return -1;
            }
        }
        for (int i = 0; i < 10; ++i) {
            if (add_node_search_luck_list(&list_luck, i + 1) < 0) {
                free_luck_list(list_luck);
                return -1;
            }
        }
        search_occurence_loto(list_nb, list_luck);
        propose_loto(list_nb, list_luck);

    } else if (want == EURO) {
        for (int i = 0; i < 50; ++i) {
            if (add_node_search_nb_list(&list_nb, i + 1) < 0) {
                free_nb_list(list_nb);
                return -1;
            }
        }
        for (int i = 0; i < 12; ++i) {
            if (add_node_search_luck_list(&list_luck, i + 1) < 0) {
                free_luck_list(list_luck);
                return -1;
            }
        }
        search_occurence_euro(list_nb, list_luck);
        propose_euro(list_nb, list_luck);
    }
    if (list_nb)
        free_nb_list(list_nb);
    if (list_luck)
        free_luck_list(list_luck);
    return 0;
}