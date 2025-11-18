#include <stdio.h>
#include <string.h>
#include "notes.h"
#include "auth.h"

void createNote(Note* all_notes, int* note_count, User* currentUser){
    if(*note_count>=MAX_NOTES){
        printf("Error: Storage full. Can't create more notes.\n");
        return;
    }

    Note* new_note=&all_notes[*note_count];
    strcpy(new_note->owner,currentUser->username);

    printf("Enter the title for this note: ");
    if(fgets(new_note->title,MAX_TITLE_LEN,stdin)!=NULL){
        new_note->title[strcspn(new_note->title,"\n")]='\0';
    }
    else{
        printf("Error reading input. Try again.\n");
        return;
    }

    printf("Enter your note: \n");
    if(fgets(new_note->content,MAX_NOTE_CONTENT,stdin)!=NULL){
        new_note->content[strcspn(new_note->content,"\n")]='\0';
    }
    else{
        printf("Error reading input. Try again.\n");
        return;
    }

    (*note_count)++;
    printf("Note created successfully!");
}
