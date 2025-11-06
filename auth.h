#ifndef AUTH_H_
#define AUTH_H_

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct{
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

void registerUser(User*, int*);
User* loginUser(User*, int);

#endif