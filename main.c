#include <stdio.h>

#define MAX_LINE 100
#define MAX_WORDS 10

int main() {
    FILE *fp = fopen("words.txt", "r");
    char buf[MAX_LINE];
    
    unsigned int lines = 0;

    while(!feof(fp) && fgets(buf, MAX_LINE, fp) != NULL) {
        printf("%s", buf);
        lines++;
    }

    char str[100];

    printf("Read %d lines: %s\n", lines, str);
}

