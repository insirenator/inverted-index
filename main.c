#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "hashtable.h"

#define MAX_LINE 200
#define MAX_WORD 25
#define MAX_mark 50

void clear_word(char *str) {
    for(int i = 0; i < MAX_WORD; i++) {
        str[i] = 0;
    }
}

bool is_noise_char(char c) {
    return c == '.' || c == '?' || c == '!' || c == ',' || c == '"' || c == ';';
}

int main() {
    hash_table *table = hash_table_create(1000, NULL);
    char filename[] = "animal_farm.txt";

    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("failed to open file: %s", filename);
    }
    char buf[MAX_LINE];
    char word[MAX_WORD];
    char mark[MAX_mark];
    int line = 0;

    while(!feof(fp) && fgets(buf, MAX_LINE, fp) != NULL) {
        if(buf[0] == '\n') {
            continue;
        }
        /*printf("%s", buf);*/
        
        int bi = 0;
        int wi = 0;
        int wordc = 0;
        int wordi = 0;
        clear_word(word);

        do {
            if(is_noise_char(buf[bi])) {
                bi++;
                continue;
            }
            if(buf[bi] == ' ' || buf[bi] == '\n') {
                /*printf(" <%s (%d:%d:%d)> ", word, line, ++wordc, wordi);*/
                sprintf(mark, "%d:%d:%d", line, ++wordc, wordi);
                hash_table_insert(table, word, mark);
                clear_word(word);
                wi = 0;
                bi++;
                wordi = bi;
                continue;
            }
            word[wi] = buf[bi];
            bi++;
            wi++;

        } while(buf[bi] != '\n' && buf[bi] != '\0');
        
        /*printf(" <%s (%d:%d:%d)> ", word, line, ++wordc, ++wordi);*/
        sprintf(mark, "%d:%d:%d", line, ++wordc, wordi);
        hash_table_insert(table, word, mark);
        line++;
        /*break;*/
    }
   
    fclose(fp);

    /*hash_table_print(table);*/
    char search[50];
    while (fgets(search, sizeof(search), stdin) != NULL) {
        // Remove trailing newline if present
        search[strcspn(search, "\n")] = '\0';
        entry *found = hash_table_lookup(table, search);
        if(found == NULL) {
            printf("NOT FOUND (%s)\n", search);
        } else {
            printf("FOUND (%s): %s\n", search, found->object);
        }
    }

    hash_table_destroy(table);
}

