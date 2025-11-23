#ifndef NOTES_H_
#define NOTES_H_
#include "auth.h"
#include <time.h>

#define MAX_NOTE_CONTENT 1000 
#define MAX_NOTES 500
#define MAX_TITLE_LEN 100

typedef struct{
    char *content;
    char title[MAX_TITLE_LEN];
    char owner[MAX_USERNAME_LEN];
    time_t created_at;
} Note;

void createNote(Note* all_notes, int* note_count, User* currentUser);

void listNotes(Note* all_notes, int note_count, User* currentUser);

void readNote(Note* all_notes, int note_index, int note_count, User* currentUser);

void modifyNote(Note* all_notes, int note_index, int note_count, User* currentUser);

void freeNotes(Note* all_notes, int note_count);

void deleteNote(Note* all_notes, int note_index, int* note_count, User* currentUser);

void searchNotes(Note* all_notes, int note_count, User* currentUser, char* query);

#endif