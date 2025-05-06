#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <time.h>  // süre ölçmek için eklendi

#define USERNAME "kullanici1"  // Kendi kullanıcı adını buraya yaz

// Tuz bilgisini ayıklayan fonksiyon
void extract_salt(const char *hashed, char *salt, size_t size) {
    int dollar_count = 0;
    size_t i = 0;
    while (hashed[i] != '\0' && dollar_count < 4 && i < size - 1) {
        if (hashed[i] == '$') {
            dollar_count++;
        }
        i++;
    }
    strncpy(salt, hashed, i);
    salt[i] = '\0';
}

int main() {
    FILE *fp = fopen("/etc/shadow", "r");
    if (fp == NULL) {
        perror("Cannot open /etc/shadow. Run as root.");
        return 1;
    }

    char line[1024];
    char *hashed_password = NULL;
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, USERNAME, strlen(USERNAME)) == 0) {
            char *ptr = strchr(line, ':');
            if (ptr != NULL) {
                ptr++;
                char *end = strchr(ptr, ':');
                if (end != NULL) {
                    *end = '\0';
                    hashed_password = malloc(strlen(ptr) + 1);
                    if (hashed_password != NULL) {
                        strcpy(hashed_password, ptr);
                    }
                    break;
                }
            }
        }
    }
    fclose(fp);

    if (hashed_password == NULL) {
        printf("User not found or password is empty.\n");
        return 1;
    }

    char salt[256];
    extract_salt(hashed_password, salt, sizeof(salt));

    printf("Original hash: %s\n", hashed_password);
    printf("Extracted salt: %s\n", salt);

    // Süre ölçümü için başlangıç zamanı
    clock_t start_time = clock();

    for (int i = 0; i <= 999999; i++) {
        char guess[14];
        sprintf(guess, "%d", i);
        char *generated_hash = crypt(guess, salt);

        if (strcmp(generated_hash, hashed_password) == 0) {
            clock_t end_time = clock();  // Bitiş zamanı
            double elapsed = (double)(end_time - start_time) / CLOCKS_PER_SEC;

            printf("Password found! Password: %s\n", guess);
            printf("Time taken: %.2f seconds\n", elapsed);

            free(hashed_password);
            return 0;
        }
    }

    printf("Password not found between 0-999999.\n");

    free(hashed_password);
    return 1;
}
