#include "auth.h"
#include "crypto.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int passwordValidity(const char* password){
    int length=strlen(password);
    int has_upper = 0;
    int has_lower = 0;
    int has_digit = 0;

    if(length<8){
        return 1;
    }

    for(int i=0;i<length;i++){
        char ch=password[i];
        if(isupper(ch)){
            has_upper = 1;
        }
        else if(islower(ch)){
            has_lower = 1;
        }
        else if(isdigit(ch)){
            has_digit = 1;
        }
    }

    if(has_upper==0){
        return 2;
    }
    else if(has_lower==0){
        return 3;
    }
    else if(has_digit==0){
        return 4;
    }

    return 5;
}

static int getCredentials(char* username, char* password){
    printf("Enter your username: ");
    if(fgets(username, MAX_USERNAME_LEN, stdin)!=NULL){
        username[strcspn(username,"\n")]='\0';
    }
    else{
        printf("Error reading input. Try again.\n");
        return 0;
    }

    printf("Enter your password: ");
    if(fgets(password,MAX_PASSWORD_LEN,stdin)){
        password[strcspn(password,"\n")]='\0';
    }
    else{
        printf("Error reading password. Try again.");
        return 0;
    }

    return 1;
}

void registerUser(User* all_users, int* user_count){
    char new_username[MAX_USERNAME_LEN];
    char new_password[MAX_PASSWORD_LEN];

    if (getCredentials(new_username,new_password)==0){
        return;
    }

    for(int i=0;i<*user_count;i++){
        if(strcmp(new_username,all_users[i].username)==0){
            printf("Username already taken.\n");
            return;
        }
    }

    int validity=passwordValidity(new_password);
    switch(validity){
        case 1:{
            printf("Paasword should have at least 8 characters.");
            return;
        }
        case 2:{
            printf("Password should have at least 1 uppercase character.");
            return;
        }
        case 3:{
            printf("Password should have at least 1 lowercase character.");
            return;
        }
        case 4:{
            printf("Password should have at least 1 digit.");
            return;
        }
    }

    char encrypted_pass[MAX_PASSWORD_LEN];
    vigenere_encrypt(new_password, SYSTEM_KEY, encrypted_pass);

    User* new_user=&all_users[*user_count];
    strcpy(new_user->username,new_username);
    strcpy(new_user->password,encrypted_pass);

    (*user_count)++;
    printf("Registration successful!\n");
}

User* loginUser(User* all_users, int user_count){
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    getCredentials(username,password);

    char encrypted_pass[MAX_PASSWORD_LEN];
    vigenere_encrypt(password,SYSTEM_KEY,encrypted_pass);

    for(int i=0;i<user_count;i++){
        if(strcmp(username,all_users[i].username)==0){
            if(strcmp(encrypted_pass,all_users[i].password)==0){
                strcpy(all_users[i].session_key, password);
                return &all_users[i];
            }
        }
    }

    printf("Wrong username or password. Try Again.");
    return NULL;
}