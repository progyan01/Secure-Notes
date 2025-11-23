#ifndef FILE_IO_H
#define FILE_IO_H
#include "auth.h"
#include "notes.h"

void saveData(User* users, int u_count, Note* notes, int n_count);
void loadData(User* users, Note* notes, int* u_count, int* n_count);

#endif