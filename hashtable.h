#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef uint64_t hashfunction (const char*, size_t);
typedef struct _hash_table hash_table;
typedef struct entry {
    char *key;
    char *object;
    struct entry *next;
} entry;

hash_table *hash_table_create(uint32_t size, hashfunction *hf);
void hash_table_destroy(hash_table *ht);
void hash_table_print(hash_table *ht);
bool hash_table_insert(hash_table *ht, const char *key, char *str);
entry *hash_table_lookup(hash_table *ht, const char *key);
char *hash_table_delete(hash_table *ht, const char *key);

#endif // !HASHTABLE_H

