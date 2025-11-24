#ifndef CRYPTO_H
#define CRYPTO_H


void vigenere_encrypt(const char* plaintext, char* key, char* ciphertext);
void vigenere_decrypt(const char* ciphertext, char* key, char* plaintext);
void hash_password(const char* password, char* outputBuffer)

#endif