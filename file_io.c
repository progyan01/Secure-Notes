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
    
    for (int i = 0; i < u_count; i++) {
        fwrite(users[i].username, sizeof(users[i].username), 1, fp);
        fwrite(users[i].password, sizeof(users[i].password), 1, fp);
    }

    fwrite(&n_count, sizeof(int), 1, fp);

    for (int i = 0; i < n_count; i++) {
        fwrite(notes[i].title, sizeof(notes[i].title), 1, fp);
        fwrite(notes[i].owner, sizeof(notes[i].owner), 1, fp);
        fwrite(&notes[i].created_at, sizeof(time_t), 1, fp);
        
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

    for (int i = 0; i < *u_count; i++) {
        fread(users[i].username, sizeof(users[i].username), 1, fp);
        fread(users[i].password, sizeof(users[i].password), 1, fp);
        memset(users[i].session_key, 0, MAX_PASSWORD_LEN);
    }

    fread(n_count, sizeof(int), 1, fp);
    for (int i = 0; i < *n_count; i++) {
        fread(notes[i].title, sizeof(notes[i].title), 1, fp);
        fread(notes[i].owner, sizeof(notes[i].owner), 1, fp);
        fread(&notes[i].created_at, sizeof(time_t), 1, fp);

        int len;
        fread(&len, sizeof(int), 1, fp);
        notes[i].content = (char*)malloc(len); 
        fread(notes[i].content, sizeof(char), len, fp);
    }

    fclose(fp);
}