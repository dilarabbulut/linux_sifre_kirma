#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
int main() {
    // Verilen tuz bilgisi  - 2.kullanicinin tuz bilgisini verdik
    char tuz[] = "$y$j9T$i7PK1Zjr/S3Nq/1H8K8991$";
    // Kullanıcıdan tek karakterli sayısal şifre alınması
    char kullanici_sifresi;
    printf("Lütfen 0-9 arası tek karakterli bir sayısal şifre giriniz: ");
    scanf(" %c", &kullanici_sifresi);
    // Kullanıcının girdiği şifre ile tuzu birleştirip şifrele
    char *sifreli = crypt(&kullanici_sifresi, tuz);
    // Şifreli halini ekrana yazdır
    printf("Karmasiklasmis sifre (sifreli hali): %s\n", sifreli);
    return 0;
}
