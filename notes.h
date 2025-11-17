#ifndef NOTES_H_
#define NOTES_H_
#include "auth.h"

#define MAX_NOTE_CONTENT 1000 
#define MAX_NOTES 500
#define MAX_TITLE_LEN 100

typedef struct{
    char content[MAX_NOTE_CONTENT];
    char title[MAX_TITLE_LEN];
    char owner[MAX_USERNAME_LEN];
} Note;

void createNote(Note* all_notes, int* note_count, User* currentUser);
void viewNotes(Note* all_notes, int note_count, User* currentUser);

#endif