#include "indexing.h"
#include <stdio.h>

#define HASHTABLE_SIZE 1000
#define MAX_LINE 200
#define MAX_WORD 25
#define MAX_MARK 50

static void clear_str(char *str, size_t len) {
    for(int i = 0; i < len; i++) {
        str[i] = 0;
    }
}

static bool is_noise_char(char c) {
    return c == '.' || c == '?' || c == '!' || c == ',' || c == '"' || c == ';';
}

hash_table *create_file_index(char *filename) {
    
    if(filename == NULL) {
        printf("filename is required");
        return NULL;
    }
    
    // create a hash_table to store indices
    hash_table *table = hash_table_create(HASHTABLE_SIZE, NULL);
    if(table == NULL) {
        printf("failed to create hash table");
        return NULL;
    }
    
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("failed to open file: %s", filename);
        return NULL;
    }
    

    char buffer[MAX_LINE]; // to read each line from file
    char word[MAX_WORD];   // to parse and read each word
    
    // to store the position mark for each word
    // position mark is of the form: "line_number:word_position:char_position"
    // e.g. 2:9:37 means the word is present on line 2, it's the 9th word in
    // the line and starta at character position 37.
    char pos_mark[MAX_MARK];

    // to store line_count
    unsigned int line_count = 0;
    
    // start reading lines from file
    while(!feof(fp) && fgets(buffer, MAX_LINE, fp) != NULL) {
        // skip new lines
        if(buffer[0] == '\n') {
            continue;
        }

        unsigned int buf_idx = 0;
        unsigned int word_idx = 0;
        unsigned int word_pos = 0;
        unsigned int char_pos = 0;

        while(true) {
            if(is_noise_char(buffer[buf_idx])) {
                // ignore noise characters
                buf_idx++;
                continue;
            }
            
            if(buffer[buf_idx] != ' ' && buffer[buf_idx] != '\n') {
                // means a word has been read
                word[word_idx] = buffer[buf_idx];
                buf_idx++;
                word_idx++;
                continue;
            }
            
            // create a position marker for the word and insert into the hash table
            sprintf(pos_mark, "%d:%d:%d", line_count, ++word_pos, char_pos);
            hash_table_insert(table, word, pos_mark);

            // clear the word and pos_mark for next read
            clear_str(word, sizeof(word));
            clear_str(pos_mark, sizeof(pos_mark));
            
            word_idx = 0;
            buf_idx++;
            char_pos = buf_idx;
            
            // buf_idx - 1 because we incremented the buf_idx before check
            if(buffer[buf_idx - 1] == '\n'){
                // newline is hit, end the loop and start processing the next line
                break;
            }
        }

        line_count++;
    }
    
    // close the file
    fclose(fp);

    return table;

}
