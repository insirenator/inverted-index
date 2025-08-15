#include <stdio.h>
#include <stdbool.h>

#define MAX_LINE 200
#define MAX_WORD 25

void clear_word(char *str) {
    for(int i = 0; i < MAX_WORD; i++) {
        str[i] = 0;
    }
}

bool is_noise_char(char c) {
    return c == '.' || c == '?' || c == '!' || c == ',' || c == '"' || c == ';';
}

int main() {
    char filename[] = "animal_farm_short.txt";

    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("failed to open file: %s", filename);
    }
    char buf[MAX_LINE];
    char word[MAX_WORD];
    int line = 0;

    while(!feof(fp) && fgets(buf, MAX_LINE, fp) != NULL) {
        if(buf[0] == '\n') {
            continue;
        }
        printf("%s", buf);
        
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
                printf(" <%s (%d:%d:%d)> ", word, line, ++wordc, wordi);
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
        
        printf(" <%s (%d:%d:%d)> ", word, line, ++wordc, ++wordi);
        line++;
    }
   
    fclose(fp);
}

