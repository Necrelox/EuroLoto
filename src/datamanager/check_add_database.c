/*
** EPITECH PROJECT, 2021
** loto
** File description:
** check_add_database
*/

#include "file_manager.h"
#include "data_structure.h"
#include "tools.h"
#include <stdlib.h>
#include <string.h>

#define LOTO 1
#define EURO 2

char *get_description_field(size_t *pos)
{
    *pos = file_search(file_storage_getset(FILE_GET, NULL), *pos, "<description>", strlen("<description>") - 1);
    if (*pos == (size_t)-1)
        return NULL;
    return file_read(file_storage_getset(FILE_GET, NULL), 125, *pos + 12 );
}

void write_date_instruct_data(data_s **data, const char *unparse_date)
{
    char **tab = str_to_word_array(unparse_date, ' ');
    char month[][14] = {{"janvier"}, {"fevrier"}, {"mars"}, {"avril"}, {"mai"}, {"juin"}, {"juillet"}, {"août"},
        {"septembre"}, {"octobre"}, {"novembre"}, {"decembre"}};
    int keep = -1;
    for (int i = 0; tab[i] ; ++i) {
        for (int j = 0; j < 12 ;++j) {
            if (strcmp(tab[i], month[j]) == 0) {
                (*data)->month = j + 1;
                keep = i;
            }
        }
        if (keep > -1) {
            (*data)->years = atoi(tab[i+1]);
            (*data)->day = atoi(tab[i-1]);
            break;
        }
    }
    for (int i = 0; tab[i] ; ++i)
        free(tab[i]);
    free(tab);
}

void write_number_instruct_data(data_s **data, const char *unparse_number)
{
    char **split_two = str_to_word_array(unparse_number, ':');
    char **tab_number = str_to_word_array(split_two[1], '-');
    for (int i = 0; tab_number[i] ; ++i)
        (*data)->number[i] = atoi(tab_number[i]);
    for (int i = 0; tab_number[i] ; ++i)
        free(tab_number[i]);
    free(tab_number);
    for (int i = 0; split_two[i] ; ++i)
        free(split_two[i]);
    free(split_two);
}

void write_luck_instruct_data_loto(data_s **data, const char *unparse_lucknumber)
{
    char **split_two = str_to_word_array(unparse_lucknumber, ':');
    (*data)->luck_number[0] = atoi(split_two[1]);
    for (int i = 0; split_two[i] ; ++i)
        free(split_two[i]);
    free(split_two);
}

void write_luck_instruct_data_euro(data_s **data, const char *unparse_lucknumber)
{
    char **split_two = str_to_word_array(unparse_lucknumber, ':');

    char **split_four = str_to_word_array(split_two[1], '-');

    (*data)->luck_number[0] = atoi(split_four[0]);
    (*data)->luck_number[1] = atoi(split_four[1]);
    for (int i = 0; split_four[i] ; ++i)
        free(split_four[i]);
    free(split_four);

    for (int i = 0; split_two[i] ; ++i)
        free(split_two[i]);
    free(split_two);
}

data_s *parse_description(short want, const char *description)
{
    char **tab = str_to_word_array(description, '\n');
    if (!tab) {
        fprintf(stderr, "Error : parsing of description.\n");
        return NULL;
    }
    data_s *data = malloc(sizeof(*data));
    if (!data) {
        fprintf(stderr, "Error : creation of data structure in parsing.\n");
        return NULL;
    }

    write_date_instruct_data(&data, tab[1]);
    write_number_instruct_data(&data, tab[2]);
    if (want == LOTO)
        write_luck_instruct_data_loto(&data, tab[3]);
    else if (want == EURO)
        write_luck_instruct_data_euro(&data, tab[3]);

    for (int i = 0; tab[i] ; ++i)
        free(tab[i]);
    free(tab);
    return data;
}

int open_loto_db(file_s **floto)
{
    if (file_check("./database/loto.ech", EXIST) != 0) {
        (*floto) = file_create("./database/loto.ech");
        if (!(*floto)) {
            fprintf(stderr, "Error : creation loto database.\n");
            return -1;
        }
    } else {
        (*floto) = file_open("./database/loto.ech");
        if (!(*floto)) {
            fprintf(stderr, "Error : open loto database.\n");
            return -1;
        }
    }
    return 0;
}

int open_euro_db(file_s **feuro)
{
    if (file_check("./database/loto.ech", EXIST) == 0) {
        (*feuro) = file_create("./database/euro.ech");
        if (!(*feuro)) {
            fprintf(stderr, "Error : creation loto database.\n");
            return -1;
        }
    } else {
        (*feuro) = file_open("./database/euro.ech");
        if (!(*feuro)) {
            fprintf(stderr, "Error : open loto database.\n");
            return -1;
        }
    }
    return 0;
}

void serialize_loto(file_s *floto, data_s *to_write)
{
    char buff[120];
    sprintf(buff, "[%d/%d/%d] : Number : %d %d %d %d %d Lucky Number : %d\n",
        to_write->day, to_write->month, to_write->years,
        to_write->number[0], to_write->number[1], to_write->number[2],
        to_write->number[3], to_write->number[4], to_write->luck_number[0]);
    file_insert(floto, 0, buff);
}

void serialize_euro(file_s *feuro, data_s *to_write)
{
    char buff[120];
    sprintf(buff, "[%d/%d/%d] : Number : %d %d %d %d %d Lucky Number : %d %d\n",
        to_write->day, to_write->month, to_write->years,
        to_write->number[0], to_write->number[1], to_write->number[2],
        to_write->number[3], to_write->number[4], to_write->luck_number[0], to_write->luck_number[1]);
    file_insert(feuro, 0, buff);
}

void write_loto_db(data_s *data, file_s *floto)
{
    data_s to_write;
    to_write.day = data->day;
    to_write.luck_number[0] = data->luck_number[0];
    to_write.month = data->month;
    to_write.number[0] = data->number[0];
    to_write.number[1] = data->number[1];
    to_write.number[2] = data->number[2];
    to_write.number[3] = data->number[3];
    to_write.number[4] = data->number[4];
    to_write.years = data->years;

    serialize_loto(floto, &to_write);
}

void write_euro_db(data_s *data, file_s *feuro)
{
    data_s to_write;
    to_write.day = data->day;
    to_write.luck_number[0] = data->luck_number[0];
    to_write.luck_number[1] = data->luck_number[1];
    to_write.month = data->month;
    to_write.number[0] = data->number[0];
    to_write.number[1] = data->number[1];
    to_write.number[2] = data->number[2];
    to_write.number[3] = data->number[3];
    to_write.number[4] = data->number[4];
    to_write.years = data->years;

    serialize_euro(feuro, &to_write);
}

int verif_can_append(short want, file_s *db, data_s *data)
{
    data_s read;
    if (want == LOTO) {
        db->file = fopen("./database/loto.ech", "r");
        while (fscanf(db->file, "[%d/%d/%d] : Number : %d %d %d %d %d Lucky Number : %d\n",
            &read.day, &read.month, &read.years, &read.number[0], &read.number[1], &read.number[2],
            &read.number[3], &read.number[4], &read.luck_number[0]) != EOF)
                if (data->years == read.years && data->month == read.month && data->day == read.day)
                    return -1;
        fclose(db->file);
    } else if (want == EURO) {
        db->file = fopen("./database/euro.ech", "r");
        while (fscanf(db->file, "[%d/%d/%d] : Number : %d %d %d %d %d Lucky Number : %d %d\n",
            &read.day, &read.month, &read.years, &read.number[0], &read.number[1], &read.number[2],
            &read.number[3], &read.number[4], &read.luck_number[0], &read.luck_number[1]) != EOF)
                if (data->years == read.years && data->month == read.month && data->day == read.day)
                    return -1;
        fclose(db->file);
    }
    return 1;
}

int datamanager(short want)
{
    if (want == LOTO) {
        file_s *floto = NULL;
        if (open_loto_db(&floto) < 0)
            return -1;
        size_t start = file_search(file_storage_getset(FILE_GET, NULL), 0, "<description>", strlen("<description>") - 1) + 1;

        for (size_t pos = start; pos != (size_t)-1 ;) {
            char *description = get_description_field(&pos);
            if (description) {
                data_s *data = parse_description(LOTO, description);
                if (!data) {
                    free(description);
                    return -1;
                } else {
                    if (verif_can_append(LOTO, floto, data) == 1)
                        write_loto_db(data, floto);
                    free(data);
                }
                free(description);
            }
        }
        file_struct_destroy(floto, 1);
    }
    else if (want == EURO) {
        file_s *feuro = NULL;
        if (open_euro_db(&feuro) < 0)
            return -1;
        size_t start = file_search(file_storage_getset(FILE_GET, NULL), 0, "<description>", strlen("<description>") - 1) + 1;

        for (size_t pos = start; pos != (size_t)-1 ;) {
            char *description = get_description_field(&pos);
            if (description) {
                data_s *data = parse_description(EURO, description);
                if (!data) {
                    free(description);
                    return -1;
                } else {
                    if (verif_can_append(EURO, feuro, data) == 1)
                        write_euro_db(data, feuro);
                    free(data);
                }
                free(description);
            }
        }
        file_struct_destroy(feuro, 1);
    }
    return 0;
}