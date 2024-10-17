#ifndef URLSHORTENER_H
#define URLSHORTENER_H

#define hash_table_size 1000
#define short_len 20

typedef struct {
    char long_url[100];
    char short_url[short_len];
} URLPair;

extern URLPair table[hash_table_size]; // Declare table as an external variable

int hash(char* str);
void generateShortURL(char* long_url, char* short_url);
void storeURL(char* long_url);
char* getLongURL(char* short_url);
void loadTable();
void saveTable();

// Function declarations for URL validation and sanitization
int isValidURL(char* url);
void sanitizeURL(char* url);

#endif /* URLSHORTENER_H */

