#include "LRUCache.h"
#include <stdlib.h>
#include <stdio.h>

int hashFunction(int key) {
    return key % HASH_SIZE;
}

ListNode* createNode(int key, int val) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->key = key;
    newNode->val = val;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

LRUCache* createLRUCache(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->head = NULL;
    cache->tail = NULL;
    cache->num_nodes = 0;
    cache->capacity = capacity;
    pthread_mutex_init(&(cache->mutex), NULL);
    for (int i = 0; i < HASH_SIZE; i++) {
        cache->hashmap[i] = NULL;
    }
    return cache;
}

int get(LRUCache* cache, int key) {
    pthread_mutex_lock(&(cache->mutex));
    int index = hashFunction(key);
    HashMapNode* current = cache->hashmap[index];
    while (current != NULL) {
        if (current->key == key) {
            ListNode* node = current->node;
            int value = node->val;
            // Move the accessed node to the front of the cache
            if (node != cache->head) {
                if (node == cache->tail) {
                    cache->tail = node->prev;
                    node->prev->next = NULL;
                } else {
                    node->prev->next = node->next;
                    node->next->prev = node->prev;
                }
                node->next = cache->head;
                node->prev = NULL;
                cache->head->prev = node;
                cache->head = node;
            }
            pthread_mutex_unlock(&(cache->mutex));
            return value;
        }
        current = current->next;
    }
    pthread_mutex_unlock(&(cache->mutex));
    return -1; // Key not found in cache
}


void put(LRUCache* cache, int key, int value) {
    pthread_mutex_lock(&(cache->mutex));
    int index = hashFunction(key);
    HashMapNode* current = cache->hashmap[index];
    while (current != NULL) {
        if (current->key == key) {
            // Update existing key-value pair
            // Update the position of the node in the cache (if necessary)
            ListNode* node = current->node;
            node->val = value;
            if (node != cache->head) {
                // Move the accessed node to the front of the cache
                if (node == cache->tail) {
                    cache->tail = node->prev;
                    node->prev->next = NULL;
                } else {
                    node->prev->next = node->next;
                    node->next->prev = node->prev;
                }
                node->next = cache->head;
                node->prev = NULL;
                cache->head->prev = node;
                cache->head = node;
            }
            pthread_mutex_unlock(&(cache->mutex));
            return;
        }
        current = current->next;
    }

    // If the cache is full, evict the least recently used entry
    if (cache->num_nodes >= cache->capacity) {
        ListNode* tail = cache->tail;
        cache->tail = tail->prev;
        if (cache->tail != NULL) {
            cache->tail->next = NULL;
        } else {
            cache->head = NULL; // Cache is now empty
        }
        int eviction_key = tail->key;
        free(tail); // Free the memory associated with the evicted entry

        // Remove the evicted entry from the hashmap
        int eviction_index = hashFunction(eviction_key);
        HashMapNode* prev = NULL;
        current = cache->hashmap[eviction_index];
        while (current != NULL) {
            if (current->key == eviction_key) {
                if (prev == NULL) {
                    cache->hashmap[eviction_index] = current->next;
                } else {
                    prev->next = current->next;
                }
                free(current); // Free the memory associated with the hashmap node
                break;
            }
            prev = current;
            current = current->next;
        }

        cache->num_nodes--;
    }

    // Add the new entry to the cache
    ListNode* newNode = createNode(key, value);
    newNode->next = cache->head;
    if (cache->head != NULL) {
        cache->head->prev = newNode;
    }
    cache->head = newNode;
    if (cache->tail == NULL) {
        cache->tail = newNode;
    }
    HashMapNode* hashmapNode = (HashMapNode*)malloc(sizeof(HashMapNode));
    hashmapNode->key = key;
    hashmapNode->node = newNode;
    hashmapNode->next = cache->hashmap[index];
    cache->hashmap[index] = hashmapNode;
    cache->num_nodes++;

    pthread_mutex_unlock(&(cache->mutex));
}



void displayCache(LRUCache* cache) {
    pthread_mutex_lock(&(cache->mutex));
    ListNode* current = cache->head;
    printf("Cache contents:\n");
    while (current != NULL) {
        printf("(%d, %d) ", current->key, current->val);
        current = current->next;
    }
    printf("\n");
    pthread_mutex_unlock(&(cache->mutex));
}

void destroyCache(LRUCache* cache) {
    pthread_mutex_destroy(&(cache->mutex));
    free(cache);
}

void destroyLRUCache(LRUCache* cache) {
    pthread_mutex_lock(&(cache->mutex));
    ListNode* current = cache->head;
    while (current != NULL) {
        ListNode* next = current->next;
        free(current);
        current = next;
    }
    for (int i = 0; i < HASH_SIZE; i++) {
        HashMapNode* current = cache->hashmap[i];
        while (current != NULL) {
            HashMapNode* next = current->next;
            free(current);
            current = next;
        }
    }
    pthread_mutex_unlock(&(cache->mutex));
    pthread_mutex_destroy(&(cache->mutex));
    free(cache);
}

