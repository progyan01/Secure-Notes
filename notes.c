#include <stdio.h>
#include <string.h>
#include "notes.h"
#include "auth.h"
#include "crypto.h"

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
    char tempBuffer[MAX_NOTE_CONTENT]; 
    if (fgets(tempBuffer, MAX_NOTE_CONTENT, stdin) != NULL){
        tempBuffer[strcspn(tempBuffer, "\n")] = '\0';
        
        new_note->content = (char*)malloc(strlen(tempBuffer) + 1);
        
        if(new_note->content != NULL){
            vigenere_encrypt(tempBuffer, currentUser->password, new_note->content);

            (*note_count)++;
            printf("Note created successfully!");
        } 
        else{
            printf("Memory allocation failed!\n");
            return;
        }
    }
}

void listNotes(Note* all_notes, int note_count, User* currentUser){
    char *username=currentUser->username;
    int found=0;
    printf("\n----- %s's Notes -----\n", username);

    for(int i=0;i<note_count;i++){
        if(strcmp(all_notes[i].owner,username)==0){
            printf("[%d]. %s\n", i, all_notes[i].title);
            found=1;
        }
    }

    if(found==0){
        printf("No note found.\n");
    }
    printf("------------------\n");
}

void readNote(Note* all_notes, int note_index, int note_count, User* currentUser){
    if(note_index<0 || note_index>=note_count) { 
        printf("Invalid Note ID.\n");
        return;
    }
    if(strcmp(currentUser->username,all_notes[note_index].owner)!=0){
        printf("You do not own this note.\n");
        return;
    }

    char *plainText=(char*)malloc(strlen(all_notes[note_index].content) + 1);

    if(plainText){
        vigenere_decrypt(all_notes[note_index].content, currentUser->password, plainText);
        
        printf("----- %s -----\n", all_notes[note_index].title);
        printf("%s\n", plainText);
        printf("-----------------------\n");
        
        free(plainText);
    }
}

void modifyNote(Note* all_notes, int note_index, int note_count, User* currentUser){
    if(note_index<0 || note_index>=note_count){ 
        printf("Invalid Note ID.\n");
        return;
    }
    if(strcmp(currentUser->username,all_notes[note_index].owner)!=0){
        printf("You do not own this note.\n");
        return;
    }

    printf("Current Title: %s\n", all_notes[note_index].title);
    char *plainText = (char*)malloc(strlen(all_notes[note_index].content) + 1);
    if(plainText){
        vigenere_decrypt(all_notes[note_index].content, currentUser->password, plainText);
        printf("Current Content: %s\n", plainText);
        free(plainText);
    }

    printf("Enter new content: ");
    char tempBuffer[MAX_NOTE_CONTENT];

    if(fgets(tempBuffer, MAX_NOTE_CONTENT, stdin) != NULL) {
        tempBuffer[strcspn(tempBuffer, "\n")] = '\0';
        free(all_notes[note_index].content);

        all_notes[note_index].content = (char*)malloc(strlen(tempBuffer) + 1);
        vigenere_encrypt(tempBuffer, currentUser->password, all_notes[note_index].content);
        
        printf("Note updated successfully!\n");
    }
}

void deleteNote(Note* all_notes, int note_index, int* note_count, User* currentUser){
    if(note_index < 0 || note_index >= *note_count) {
        printf("Invalid Note ID.\n");
        return;
    }
    if(strcmp(currentUser->username, all_notes[note_index].owner) != 0){
        printf("Error: You do not own this note.\n");
        return;
    }
    free(all_notes[note_index].content);

    for (int i = note_index; i < *note_count - 1; i++) {
        all_notes[i] = all_notes[i + 1];
    }
    (*note_count)--;
    printf("Note deleted successfully.\n");
}

void freeNotes(Note* all_notes, int note_count){
    for(int i = 0; i < note_count; i++){
        if(all_notes[i].content != NULL){
            free(all_notes[i].content);
        }
    }
}