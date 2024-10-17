#include "URLShortener.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

URLPair table[hash_table_size]; // Define table here

int hash(char* str) {
    int hash = 0;
    for (int i = 0; str[i]; i++)
        hash = (hash * 31 + str[i]) % hash_table_size;
    return hash;
}

void generateShortURL(char* long_url, char* short_url) {
    int hash_index = hash(long_url);
    int rand_num = rand() % 1000; // Generate a random number
    sprintf(short_url, "%d%d", hash_index, rand_num);
}


void storeURL(char* long_url) {
    char short_url[short_len];
    generateShortURL(long_url, short_url);
    int index = hash(short_url); // Use the short URL hash as index
    strcpy(table[index].long_url, long_url);
    strcpy(table[index].short_url, short_url);
    printf("Generated Short URL: %s\n", short_url); // Debugging output
    printf("Stored Short URL: %s\n", table[index].short_url); // Debugging output
    saveTable(); // Save the table after storing a new URL
}


char* getLongURL(char* short_url) {
    for (int i = 0; i < hash_table_size; i++)
        if (!strcmp(table[i].short_url, short_url))
            return table[i].long_url;
    return NULL;
}

void loadTable() {
    FILE* fp = fopen("table.txt", "r");
    if (fp == NULL)
        return;
    int index = 0;
    while (fscanf(fp, "%s %s", table[index].long_url, table[index].short_url) != EOF)
        index++;
    fclose(fp);
}

void saveTable() {
    FILE* fp = fopen("table.txt", "w");
    if (fp == NULL) {
        printf("Error: Unable to open file for writing.\n");
        return;
    }
    for (int i = 0; i < hash_table_size; i++) {
        if (table[i].long_url[0]) {
            fprintf(fp, "%s %s\n", table[i].long_url, table[i].short_url);
        }
    }
    fclose(fp);
}

// Function to validate a URL
int isValidURL(char* url) {
    // Basic validation: Check if the URL starts with http:// or https://
    if (strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0) {
        return 1;
    } else {
        return 0;
    }
}

// Function to sanitize a URL
void sanitizeURL(char* url) {
    // Remove any whitespace characters at the beginning and end of the URL
    int i, j;
    for (i = 0; isspace(url[i]); i++);
    for (j = strlen(url) - 1; j >= 0 && isspace(url[j]); j--);
    url[j + 1] = '\0';
    memmove(url, url + i, j - i + 2);

    // Remove any trailing slashes from the URL
    while (url[strlen(url) - 1] == '/') {
        url[strlen(url) - 1] = '\0';
    }
}

