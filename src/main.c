/*
** EPITECH PROJECT, 2021
** loto
** File description:
** main
*/

#include "cli.h"
#include "file_manager.h"
#include "datamanager.h"
#include "search_propose.h"
#include <string.h>

int main(int ac, char **av)
{
    file_s *tampon = file_create("./tmp/xml.bad");
    if (!tampon) {
        fprintf(stderr, "Error : temp file for get xml can't create.\n");
        return 84;
    }
    file_storage_getset(FILE_SET, tampon);

    if (ac == 2) {
        if (strcmp(av[1], "euro") == 0 || strcmp(av[1], "Euro") == 0) {
            if (get_xml(2) < 0)
                goto error;
            if (datamanager(2) < 0)
                goto error;
            search_and_propose(2);
            return 0;
        }

        if (strcmp(av[1], "loto") == 0 || strcmp(av[1], "Loto") == 0) {
            if (get_xml(1) < 0)
                goto error;
            if (datamanager(1) < 0)
                goto error;
            search_and_propose(1);
            return 0;
        }
    }

    error:
        file_struct_destroy(tampon, 1);
    return 84;
}