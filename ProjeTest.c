#define _XOPEN_SOURCE
#include <stdio.h>
#include <crypt.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
   // $y$j9T$vDaWwinzvc9BkLU95eYRJ0$XC/Hp5tZwryanP6IFtMEdAdtjR2H1Xl03Ekv1R5qax3
   char sifre[] = "1";
   char tuz[]="$y$j9T$vDaWwinzvc9BkLU95eYRJ0$";
   printf("Uretilen: %s\n",crypt(sifre,tuz));   
   printf("Orijinal: %s\n", "$y$j9T$vDaWwinzvc9BkLU95eYRJ0$XC/Hp5tZwryanP6IFtMEdAdtjR2H1Xl03Ekv1R5qax3");
   return 0;
}
