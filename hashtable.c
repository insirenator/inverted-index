#include "hashtable.h"
#include <stdio.h>
#include <string.h>

typedef struct _hash_table {
    uint32_t size;
    hashfunction *hash;
    entry **elements;
} hash_table;

static uint64_t hash(const char *name, size_t length) {
    uint64_t hash_value = 0;
    for(int i = 0; i < length; i++) {
        hash_value += name[i];
        hash_value = (hash_value * name[i]);
    }
    return hash_value;
}

static size_t hash_table_index(hash_table *ht, const char *key) {
    size_t result = (ht->hash(key, strlen(key)) % ht->size);
    return result;
}

hash_table *hash_table_create(uint32_t size, hashfunction *hf) {
    hash_table *ht = malloc(sizeof(*ht));
    ht->size = size;
    if(hf == NULL) {
        hf = hash;
    }
    ht->hash = hf;
    // calloc zeros out the memory
    ht->elements = calloc(ht->size, sizeof(entry*));

    return ht;
}

void hash_table_destroy(hash_table *ht) {
    // TODO: clean up individual elements;
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->elements[i] != NULL) {
            entry *tmp = ht->elements[i];
            entry *tmp2 = NULL;
            while(tmp != NULL) {
                tmp2 = tmp->next;
                free(tmp->key);
                free(tmp->object);
                free(tmp);
                tmp = tmp2;
            }
        }
    }
    free(ht->elements);
    free(ht);
}
void hash_table_print(hash_table *ht) {
    printf("___START__TABLE___\n");
    for (uint32_t i = 0; i < ht->size; i++) {
        if(ht->elements[i] == NULL) {
            // Do we wanna print null entries??
            printf("  %04i := <empty>\n", i);
        } else {
            printf("  %04i : ", i);
            entry *tmp = ht->elements[i];
            while(tmp != NULL) {
                printf("\"%s\"(%s) - ", tmp->key, tmp->object);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
    printf("____END__TABLE____\n");
}

bool hash_table_insert(hash_table *ht, const char *key, char *obj) {
    if(ht == NULL || key == NULL || obj == NULL) return false;

    size_t index = hash_table_index(ht, key);

    entry *already = hash_table_lookup(ht, key);
    if(already != NULL) {
        char *new_obj;
        asprintf(&new_obj, "%s,%s", already->object, obj); // allocates automatically
        free(already->object);
        already->object = new_obj;
        return true;
    }

    entry *e = malloc(sizeof(*e));
    e->object = malloc(strlen(obj)+1);
    strcpy(e->object, obj);
    e->key = malloc(strlen(key)+1);
    strcpy(e->key, key);

    e->next = ht->elements[index];
    ht->elements[index] = e;
    return true;
}

entry *hash_table_lookup(hash_table *ht, const char *key) {
    if (ht == NULL || key == NULL) return NULL;
    
    size_t index = hash_table_index(ht, key);
    
    entry *tmp = ht->elements[index];
    while(tmp != NULL && (strcmp(tmp->key, key)) != 0) {
        tmp = tmp->next;
    }
    
    if(tmp == NULL) return NULL;

    return tmp;
}

char *hash_table_delete(hash_table *ht, const char *key) {
    if (ht == NULL || key == NULL) return NULL;
    
    size_t index = hash_table_index(ht, key);
    
    entry *tmp = ht->elements[index];
    entry *prev = NULL;
    while(tmp != NULL && (strcmp(tmp->key, key)) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }
    
    if(tmp == NULL) return NULL;
    if(prev == NULL) {
        // deleting head node
        ht->elements[index] = tmp->next;
    } else {
        prev->next = tmp->next;
    }
    void *result = tmp->object;
    free(tmp);
    return result;
}
