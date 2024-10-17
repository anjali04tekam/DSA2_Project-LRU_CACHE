#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <pthread.h>

#define HASH_SIZE 100

typedef struct ListNode {
    int key;
    int val;
    struct ListNode* prev;
    struct ListNode* next;
} ListNode;

typedef struct HashMapNode {
    int key;
    ListNode* node;
    struct HashMapNode* next;
} HashMapNode;

typedef struct {
    ListNode* head;
    ListNode* tail;
    HashMapNode* hashmap[HASH_SIZE];
    int num_nodes;
    int capacity;
    pthread_mutex_t mutex;
} LRUCache;

LRUCache* createLRUCache(int capacity);
int get(LRUCache* cache, int key);
void put(LRUCache* cache, int key, int value);
void displayCache(LRUCache* cache);
void destroyCache(LRUCache* cache);
void destroyLRUCache(LRUCache* cache);

#endif /* LRUCACHE_H */

