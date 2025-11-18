#ifndef CRYPTO_H
#define CRYPTO_H

void vigenere_encrypt(const char* plaintext, char* key, char* ciphertext);
void vignere_decrypt(const char* ciphertext, char* key, char* plaintext);

#endif