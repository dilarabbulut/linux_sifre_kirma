#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <time.h>

#define MAX_USERNAME_LEN 128

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
    char username[MAX_USERNAME_LEN];

    // Kullanıcıdan kullanıcı adını al
    printf("Lütfen şifresi çözülecek kullanıcı adını girin: ");
    if (fgets(username, sizeof(username), stdin) == NULL) {
        fprintf(stderr, "Kullanıcı adı alınamadı.\n");
        return 1;
    }

    // fgets '\n' karakterini de alır, onu temizleyelim
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    FILE *fp = fopen("/etc/shadow", "r");
    if (fp == NULL) {
        perror("/etc/shadow dosyası açılamadı. Lütfen root olarak çalıştırın.");
        return 1;
    }

    char line[1024];
    char *hashed_password = NULL;
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, username, strlen(username)) == 0 && line[strlen(username)] == ':') {
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
        printf("Kullanıcı '%s' bulunamadı ya da şifresi boş.\n", username);
        return 1;
    }

    char salt[256];
    extract_salt(hashed_password, salt, sizeof(salt));

    printf("Kullanıcı '%s' için orijinal hash: %s\n", username, hashed_password);
    printf("Çıkarılan salt: %s\n", salt);

    clock_t start_time = clock();

    for (int i = 0; i <= 999999; i++) {
        char guess[14];
        sprintf(guess, "%d", i);
        char *generated_hash = crypt(guess, salt);

        if (strcmp(generated_hash, hashed_password) == 0) {
            clock_t end_time = clock();
            double elapsed = (double)(end_time - start_time) / CLOCKS_PER_SEC;

            printf("\n\033[1;32mŞifre bulundu! \033[0mKullanıcı: '%s' - Şifre: %s\n", username, guess);
            printf("Geçen süre: %.2f saniye\n\n", elapsed);  // 2 boş satır ekledim

            free(hashed_password);
            return 0;
        }
    }

    printf("\033[1;31mŞifre bulunamadı. \033[0mKullanıcı: '%s' için 0-999999 arası denendi.\n\n", username);  // 2 boş satır ekledim

    free(hashed_password);
    return 1;
}
