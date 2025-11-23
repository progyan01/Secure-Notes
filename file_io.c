#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"

void saveData(User* users, int u_count, Note* notes, int n_count) {
    FILE *fp = fopen("data.dat", "wb");
    if (!fp) {
        perror("Failed to save data");
        return;
    }

    fwrite(&u_count, sizeof(int), 1, fp);
    fwrite(users, sizeof(User), u_count, fp);
    fwrite(&n_count, sizeof(int), 1, fp);

    for (int i = 0; i < n_count; i++) {
        fwrite(notes[i].title, sizeof(notes[i].title), 1, fp);
        fwrite(notes[i].owner, sizeof(notes[i].owner), 1, fp);
        
        int len = strlen(notes[i].content) + 1; 
        fwrite(&len, sizeof(int), 1, fp);
        fwrite(notes[i].content, sizeof(char), len, fp);
    }

    fclose(fp);
}

void loadData(User* users, Note* notes, int* u_count, int* n_count) {
    FILE *fp = fopen("data.dat", "rb");
    if (!fp) return; 

    fread(u_count, sizeof(int), 1, fp);
    fread(users, sizeof(User), *u_count, fp);

    fread(n_count, sizeof(int), 1, fp);
    for (int i = 0; i < *n_count; i++) {
        fread(notes[i].title, sizeof(notes[i].title), 1, fp);
        fread(notes[i].owner, sizeof(notes[i].owner), 1, fp);

        int len;
        fread(&len, sizeof(int), 1, fp);
        notes[i].content = (char*)malloc(len); 
        fread(notes[i].content, sizeof(char), len, fp);
    }

    fclose(fp);
}