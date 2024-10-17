#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LRUCache.h"
#include "URLShortener.h"

int main() {
    int choice;
    LRUCache* cache = NULL;
    loadTable(); // Load URL mappings from table.txt
    
    do {
        printf("\nMenu:\n");
        printf("1. Cache Memory Simulation\n");
        printf("2. URL Shortening\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        // Clear the input buffer
        while (getchar() != '\n');

        printf("\n");
        switch (choice) {
            case 1:
                // Cache memory simulation code remains unchanged
                // Cache memory simulation code
                if (cache == NULL) {
                    int capacity;
                    printf("Enter cache capacity: ");
                    scanf("%d", &capacity);
                    cache = createLRUCache(capacity);
                }
                int cache_choice;
                do {
                    printf("\nCache Memory Simulation Menu:\n");
                    printf("1. Add data to cache\n");
                    printf("2. Get data from cache\n");
                    printf("3. Display cache\n");
                    printf("4. Destroy cache and back to main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &cache_choice);
                    // Clear the input buffer
                    while (getchar() != '\n');
                    switch (cache_choice) {
                        case 1:
                            printf("Enter key and value to add to cache: ");
                            int key, value;
                            scanf("%d %d", &key, &value);
                            put(cache, key, value);
                            printf("Data added to cache.\n");
                            break;
                        case 2:
                            printf("Enter key to get data from cache: ");
                            scanf("%d", &key);
                            value = get(cache, key);
                            if (value == -1) {
                                printf("Data not found in cache.\n");
                            } else {
                                printf("Value found in cache: %d\n", value);
                            }
                            break;
                        case 3:
                            displayCache(cache);
                            break;
                        case 4:
                            printf("Destroying cache...\n");
                            destroyCache(cache);
                            cache = NULL;
                            printf("Cache destroyed. Returning to main menu...\n");
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }
                } while (cache_choice != 4);
                break;
           case 2:
    printf("* * * * * * * * * * * * * * * * * * * * * *\n");
    printf("*            URL Shortening Menu           *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * *\n\n");
    char long_url[1000];
    char short_url[short_len];
    printf("Enter a long URL: ");
    fgets(long_url, sizeof(long_url), stdin);

    // Remove the newline character from the input
    if (strlen(long_url) > 0 && long_url[strlen(long_url) - 1] == '\n') {
        long_url[strlen(long_url) - 1] = '\0';
    }

    // Validate the URL
    if (!isValidURL(long_url)) {
        printf("Invalid URL format. Please enter a valid URL starting with http:// or https://.\n");
        break;
    }

    // Sanitize the URL
    sanitizeURL(long_url);

    // Store the URL
    storeURL(long_url);
    generateShortURL(long_url, short_url);
    printf("URL shortened successfully!\n");
3
    // Retrieve long URL based on short URL
    char short_code[short_len];
    char* retrieved_long;
    printf("\nEnter short URL code to retrieve long URL: ");
    scanf("%s", short_code);
    retrieved_long = getLongURL(short_code);
    if (retrieved_long != NULL) {
        printf("Long URL: %s\n", retrieved_long);
    } else {
        printf("Short URL not found.\n");
    }
    break;

            case 3:
                printf("Exiting...\n");
                if (cache != NULL) {
                    destroyLRUCache(cache);
                }
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
    return 0;
}

