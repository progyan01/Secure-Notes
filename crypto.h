#ifndef CRYPTO_H
#define CRYPTO_H

#define SYSTEM_KEY "GHOST_OF_TSUSHIMA"

void vigenere_encrypt(const char* plaintext, char* key, char* ciphertext);
void vigenere_decrypt(const char* ciphertext, char* key, char* plaintext);

#endif