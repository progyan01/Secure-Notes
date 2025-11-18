#include <string.h>
#include <ctype.h>
#include "crypto.h"
static char encrypt_char(char plain, char key_char) {
    if (isupper(plain)) {
        return ((plain - 'A') + (toupper(key_char) - 'A')) % 26 + 'A';
    }
    if (islower(plain)) {
        return ((plain - 'a') + (tolower(key_char) - 'a')) % 26 + 'a';
    }
    return plain;
}
static char decrypt_char(char cipher, char key_char) {
    if (isupper(cipher)) {
        return ((cipher - 'A') - (toupper(key_char) - 'A') + 26) % 26 + 'A';
    }
    if (islower(cipher)) {
        return ((cipher - 'a') - (tolower(key_char) - 'a') + 26) % 26 + 'a';
    }
    return cipher;
}

void vigenere_encrypt(const char *plaintext, const char *key, char *ciphertext) {
    int text_len = strlen(plaintext);
    int key_len = strlen(key);
    int key_index = 0;

    for (int i = 0; i < text_len; i++) {
        if (isalpha(plaintext[i])) {
            ciphertext[i] = encrypt_char(plaintext[i], key[key_index % key_len]);
            key_index++;
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[text_len] = '\0';
}

void vigenere_decrypt(const char *ciphertext, const char *key, char *plaintext) {
    int text_len = strlen(ciphertext);
    int key_len = strlen(key);
    int key_index = 0;

    for (int i = 0; i < text_len; i++) {
        if (isalpha(ciphertext[i])) {
            plaintext[i] = decrypt_char(ciphertext[i], key[key_index % key_len]);
            key_index++;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[text_len] = '\0';
}