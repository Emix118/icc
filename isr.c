#include <stdio.h>
#include <stdlib.h>

#define LEN 11
#define CANT 12

void salida(char [][LEN], float [], float [], float []);
float calculo_isr(float []);

int main() {
   // Definicion del arreglo de los meses
   char meses[CANT][LEN] = { {'E','n','e','r','o'},
                           {'F','e','b','r','e','r','o'},
                           {'M','a','r','z','o'},
                           {'A','b','r','i','l'},
                           {'M','a','y','o'},
                           {'J','u','n','i','o'},
                           {'J','u','l','i','o'},
                           {'A','g','o','s','t','o'},
                           {'S','e','p','t','i','e','m','b','r','e'},
                           {'O','c','t','u','b','r','e'},
                           {'N','o','v','i','e','m','b','r','e'},
                           {'D','i','c','i','e','m','b','r','e'} };

   float bruto[CANT];

   for (int i = 0; i < CANT; i++) {
      do {
         printf("Ingrese el sueldo bruto de %s:\n", meses[i]);
         fflush(stdin);
         scanf("%f", &bruto[i]);

         if (bruto[i] <= 0) {
            printf("Ingrese un numero mayor que cero\n");
         }

      } while(bruto[i] <= 0);
   }

   float isr[CANT] = {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12};
   float neto[CANT] = {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12};
   salida(meses, bruto, isr, neto);

   return 0;
}

/*
   Funcion: salida
   Argumentos: (char[]) meses. Un arreglo con todos los meses del año
               (float[]) bruto. Arreglo con el sueldo bruto de cada mes
               (float[]) isr. Arreglo con el ISR de cada mes
               (float[]) neto. Arreglo con el sueldo neto de cada mes
   Objetivo: Imprimir los datos en forma de tabla a la consola.
   Retorno: void
*/
void salida(char meses[][LEN], float bruto[], float isr[], float neto[]) {
   // Divisor
   printf("--------------\n");

   // Salida Titulos
   printf("Meses\t\t");
   printf("Sueldo Bruto\t");
   printf("ISR\t\t");
   printf("Sueldo Neto\n");

   // Salida datos por mes
   for (int i = 0; i < CANT; i++) {
      printf("%-10s:\t", meses[i]);
      printf("%-10f\t", bruto[i]);
      printf("%-10f\t", isr[i]);
      printf("%-10f\n", neto[i]);
   }
}

/*
   Funcion: salida
   Argumentos: (char[]) meses. Un arreglo con todos los meses del año
               (float[]) bruto. Arreglo con el sueldo bruto de cada mes
               (float[]) isr. Arreglo con el ISR de cada mes
               (float[]) neto. Arreglo con el sueldo neto de cada mes
   Objetivo: Imprimir los datos en forma de tabla a la consola.
   Retorno: void
*/
float calculo_isr(float bruto[]) {
   float suma;
   float total;
   for (int i = 0; i < CANT; i++) {
      suma += bruto[i];
   }

   if (suma > 300000) {
      total += (suma - 300000)*0.25;
      suma = 300000;
   }

   if (suma > 200000) {
      total += (suma - 200000)*0.20;
      suma = 200000;
   }

   if (suma > 120000) {
      total += (suma - 120000)*0.15;
   }

   return total/12;

}
