/*
** EPITECH PROJECT, 2021
** loto
** File description:
** get_xml
*/

#include "file_manager.h"
#include <curl/curl.h>

size_t append_content_of_webpage(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    (void)userdata;
    file_append_bytes(file_storage_getset(FILE_GET, NULL), ptr, size * nmemb);
    return size * nmemb;
}

int get_xml(short want)
{
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error : curl init.\n");
        return -1;
    }

    if (want == 1)
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.lesbonsnumeros.com/loto/rss.xml");
    if (want == 2)
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.lesbonsnumeros.com/euromillions/rss.xml");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, append_content_of_webpage);

    CURLcode code = curl_easy_perform(curl);
    if (code != CURLE_OK) {
        fprintf(stderr, "Error : download of content has a problem : %s\n", curl_easy_strerror(code));
        return -1;
    }
    curl_easy_cleanup(curl);
    return 0;
}