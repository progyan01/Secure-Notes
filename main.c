
#include <stdio.h>
#include <string.h>
#include "auth.h"
#include "notes.h"
#include "file_io.h"

int main(void) {
    User users[MAX_USERS];
    Note notes[MAX_NOTES];
    int u_count = 0;
    int n_count = 0;

    loadData(users, notes, &u_count, &n_count);

    User *currentUser = NULL;
    char choice_buff[16];

    while (1) {
        printf("\n--- NOTE APP ---\n");
        printf("1) Register\n2) Login\n3) Create Note\n4) View Notes\n5) Save & Exit\nChoose: ");
        if (!fgets(choice_buff, sizeof(choice_buff), stdin)) break;
        int choice = atoi(choice_buff);

        if (choice == 1) {
            registerUser(users, &u_count);
        } else if (choice == 2) {
            currentUser = loginUser(users, u_count);
            if (currentUser) printf("Welcome %s (id=%d)\n", currentUser->username, currentUser->id);
            else printf("Login failed.\n");
        } else if (choice == 3) {
            createNote(notes, &n_count, currentUser);
        } else if (choice == 4) {
            viewNotes(notes, n_count, currentUser);
        } else if (choice == 5) {
            saveData(users, u_count, notes, n_count);
            printf("Saved. Exiting.\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
