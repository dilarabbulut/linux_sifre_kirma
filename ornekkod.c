#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main() {
    char password;
    char charset[] = "0123456789";
    FILE *logFile;
    int attemptCount = 0;
    clock_t start, end;
    double time_spent;
    // Kullanıcıdan tek karakterli şifre al
    printf("Tek karakterli (0-9 arası) şifreyi girin: ");
    scanf(" %c", &password);  // Başında boşluk olması scanf hatalarını önler
    // Dosyayı aç (üzerine yazmak için)
    logFile = fopen("log.txt", "w");
    if (logFile == NULL) {
        printf("Dosya açılamadı.\n");
        return 1;
    }
    // Süreyi başlat
    start = clock();
    // Brute force başla
    for (int i = 0; i < 100; i++) {
        attemptCount++;
        // Her denemeyi dosyaya yaz
        fprintf(logFile, "Deneme %d: %c\n", attemptCount, charset[i]);
        if (charset[i] == password) {
            // Süreyi bitir

            end = clock();
            time_spent = (double)(end - start) / CLOCKS_PER_SEC;
            // Sonucu dosyaya yaz
            fprintf(logFile, "Doğru şifre bulundu: %c\n", password);
            fprintf(logFile, "Toplam deneme: %d\n", attemptCount);
            fprintf(logFile, "Geçen süre: %.3f saniye\n", time_spent);
            // Ekrana yazdır
            printf("Doğru şifre bulundu: %c\n", password);
            printf("Toplam deneme: %d\n", attemptCount);
            printf("Geçen süre: %.3f saniye\n", time_spent);
            break;
        }
    }
    fclose(logFile);
    return 0;
}
