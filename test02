#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
int main() {
    // Verilen tuz bilgisi  - 1.kullanicinin tuz bilgisi
    char tuz[] = "$y$j9T$vDaWwinzvc9BkLU95eYRJ0$";
    // 0-9 arasi
    for (int i = 0; i <= 9; i++) {
        char kullanici_sifresi = '0' + i;
        char *sifreli = crypt(&kullanici_sifresi, tuz);
        printf("Sifreniz %d - Kriptolasmis hali : %s\n", i, sifreli);
    }
    return 0;
}
