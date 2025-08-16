#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "hashtable.h"
#include "indexing.h"

int main() {
    char filename[] = "animal_farm.txt";
    hash_table *table = create_file_index(filename);

    if(table == NULL) {
        printf("failed to create file index");
        return 1;
    }

    printf("Successfully indexed `%s`\n\n", filename);
    printf("Enter keyword to search (Ctrl^D to quit): ");

    char search[50];
    while (fgets(search, sizeof(search), stdin) != NULL) {
        // Remove trailing newline if present
        search[strcspn(search, "\n")] = '\0';
        entry *found = hash_table_lookup(table, search);
        if(found == NULL) {
            printf("NOT FOUND (%s)", search);
        } else {
            search_result(filename, found);
        }
        printf("\n\nEnter keyword to search (Ctrl^D to quit): ");
    }

    hash_table_destroy(table);
    return 0;
}

