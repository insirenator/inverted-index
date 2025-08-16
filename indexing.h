#ifndef INDEXING_H
#define INDEXING_H

#include "hashtable.h"

hash_table *create_file_index(char *filename);
void search_result(char *filename, entry *e);

#endif // !INDEXING_H
