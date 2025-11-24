#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "notes.h"
#include "file_io.h"

// Helper to safely get a number from user
int getIntInput() {
    char buffer[16];
    if (fgets(buffer, sizeof(buffer), stdin)) {
        return atoi(buffer);
    }
    return 0;
}

int main(void) {
    // 1. Setup Memory
    User users[MAX_USERS];
    Note notes[MAX_NOTES];
    int u_count = 0;
    int n_count = 0;

    // 2. Load existing data
    loadData(users, notes, &u_count, &n_count);

    User *currentUser = NULL;
    char query_buff[100]; // Buffer for search queries

    while (1) {
        if (currentUser == NULL) {
            // === GUEST MENU (Safe Mode) ===
            printf("\n--- SECURE NOTES APP (v1.0) ---\n");
            printf("1) Register\n");
            printf("2) Login\n");
            printf("3) Save & Exit\n");
            printf("Choose: ");
            
            int choice = getIntInput();

            if (choice == 1) {
                registerUser(users, &u_count);
            } else if (choice == 2) {
                currentUser = loginUser(users, u_count);
                if (currentUser) {
                    printf("\n>>> Login Successful! Welcome, %s. <<<\n", currentUser->username);
                }
            } else if (choice == 3) {
                saveData(users, u_count, notes, n_count);
                freeNotes(notes, n_count); // <--- CRITICAL: Clean up RAM
                printf("Data saved. Exiting.\n");
                break;
            } else {
                printf("Invalid choice.\n");
            }
        } 
        else {
            // === USER MENU (Logged In) ===
            printf("\n--- %s's Dashboard ---\n", currentUser->username);
            printf("1) Create Note\n");
            printf("2) View All Notes\n");
            printf("3) Read Specific Note\n");
            printf("4) Modify Note\n");
            printf("5) Delete Note\n");
            printf("6) Search Notes\n");
            printf("7) Logout\n");
            printf("Choose: ");
            
            int choice = getIntInput();

            switch (choice) {
                case 1: 
                    createNote(notes, &n_count, currentUser); 
                    break;
                case 2: 
                    listNotes(notes, n_count, currentUser); 
                    break;
                case 3: 
                    printf("Enter Note ID to read: ");
                    readNote(notes, getIntInput(), n_count, currentUser);
                    break;
                case 4: 
                    printf("Enter Note ID to modify: ");
                    modifyNote(notes, getIntInput(), n_count, currentUser);
                    break;
                case 5: 
                    printf("Enter Note ID to delete: ");
                    deleteNote(notes, getIntInput(), &n_count, currentUser);
                    break;
                case 6:
                    printf("Enter search term: ");
                    if (fgets(query_buff, sizeof(query_buff), stdin)) {
                        // Remove newline
                        query_buff[strcspn(query_buff, "\n")] = 0;
                        searchNotes(notes, n_count, currentUser, query_buff);
                    }
                    break;
                case 7:
                    currentUser = NULL;
                    printf("Logged out.\n");
                    break;
                default:
                    printf("Invalid choice.\n");
            }
        }
    }
    return 0;
}