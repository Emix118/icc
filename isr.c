#include <stdio.h>
#include <stdlib.h>

#define LEN 11
#define CANT 12

void salida(char [][LEN], float [], float [], float []);
void calculo_isr(float [], float []);
void calculo_neto(float [], float [], float []);
float proyectado(float n);

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
   float isr[CANT];
   float neto[CANT];

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

   calculo_isr(bruto, isr);
   calculo_neto(bruto, isr, neto);

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
      printf("%-10.2f\t", bruto[i]);
      printf("%-10.2f\t", isr[i]);
      printf("%-10.2f\n", neto[i]);
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
void calculo_neto(float bruto[], float isr[], float neto[]) {
   for (int i = 0; i < CANT; i++) {
      neto[i] = bruto[i] - isr[i];
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
void calculo_isr(float bruto[], float isr[]) {
   float calc = bruto[0]*12;
   float res = proyectado(calc)/12;
   float t_isr = res;
   isr[0] = res;

   float total = bruto[0];

   for (int i = 1; i < CANT; i++) {

      if (bruto[i] == bruto[i-1]) {
         isr[i] = res;
         t_isr += res;
      } else {
         res = (proyectado(total+(bruto[i]*(12-i))) - t_isr)/(12-i);
         isr[i] = res;
         t_isr += res;
      }

      total += bruto[i];
   }

}

float proyectado(float n) {
   float total = 0;
   if (n > 300000) {
      total += (n - 300000)*0.25;
      n = 300000;
   }

   if (n > 200000) {
      total += (n - 200000)*0.20;
      n = 200000;
   }

   if (n > 120000) {
      total += (n - 120000)*0.15;
   }

   return total;
}
