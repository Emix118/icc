#include <stdio.h>
#include <stdlib.h>

#define LEN 11 // Maximo de caracteres para los meses
#define CANT 12 // Numero de meses

void salida(char [][LEN], float [], float [], float []);
void calculo_isr(float [], float []);
void calculo_neto(float [], float [], float []);
float proyectado(float n);
void ingreso_sueldo(char [][LEN], float [], int);

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

   // Definicion de arreglos de datos
   float bruto[CANT] = {0,0,0,0,0,0,0,0,0,0,0,0}; //Inicializados en 0 para verificar mas adelante si tienen valor o no
   float isr[CANT];
   float neto[CANT];

   // Ingreso y validacion de los sueldos de cada mes
   for (int i = 0; i < CANT; i++) {
      ingreso_sueldo(meses, bruto, i);
   }

   // Loop para modificar los sueldos
   int mes;
   do {

      // Llamada de funciones para calculos
      calculo_isr(bruto, isr);
      calculo_neto(bruto, isr, neto);

      // Llamada de funcion para la salida de datos
      salida(meses, bruto, isr, neto);

      // Validacion del mes
      do {
         printf("Desea modificar algun sueldo? Elija un mes (1-12):\n");
         scanf("%d", &mes);

         if (mes < 1 || mes > 12) {
            printf("Mes invalido\n");
         }

      } while(mes < 1 || mes > 12);

      // Cambio de sueldo en el arreglo
      ingreso_sueldo(meses, bruto, mes-1);

   } while(1);

   return 0;
}

/*
   Funcion: ingreso_sueldo
   Argumentos: (char[]) meses. Un arreglo con todos los meses del año
               (float[]) bruto. Arreglo con el sueldo bruto de cada mes
               (int) i. Indice en el arreglo bruto[]
   Objetivo: Validar y popular/modificar un indice del arreglo bruto[]
   Retorno: void
*/
void ingreso_sueldo(char meses[][LEN], float bruto[], int i) {
   do {
      printf("Ingrese el sueldo bruto de %s:\n", meses[i]);
      fflush(stdin);
      scanf("%f", &bruto[i]);

      // Chequeo si es menero o igual a cero
      if (bruto[i] <= 0) {
         printf("Ingrese un numero mayor que cero\n");
      }

      // Chequeo si es menor que el numero previo
      if (i ? bruto[i] < bruto[i-1]: 0) {
         printf("No puede ingresar un numero menor que el previo\n");
      }

      // Chequeo si es mayor que el numero que lo sigue si este tiene valor
      if (bruto[i+1] ? bruto[i] > bruto[i+1] : 0) {
         printf("El sueldo no puede ser mayor que el sueldo que le sigue\n");
      }

   } while(bruto[i] <= 0 || (i ? bruto[i] < bruto[i-1]: 0) || (bruto[i+1] ? bruto[i] > bruto[i+1] : 0) );
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
   // Divisor
   printf("--------------\n");
}

/*
   Funcion: calculo_neto
   Argumentos: (float[]) bruto. Arreglo con el sueldo bruto de cada mes
               (float[]) isr. Arreglo con el ISR de cada mes
               (float[]) neto. Arreglo a poblar con el sueldo neto de cada mes
   Objetivo: Calcular el sueldo neto y popular el arreglo neto[].
   Retorno: void
*/
void calculo_neto(float bruto[], float isr[], float neto[]) {
   for (int i = 0; i < CANT; i++) {
      neto[i] = bruto[i] - isr[i];
   }
}

/*
   Funcion: calculo_isr
   Argumentos: (float[]) bruto. Arreglo con el sueldo bruto de cada mes
               (float[]) isr. Arreglo que se poblara con el ISR de cada mes
   Objetivo: Calcular el IRS de cada mes y poblar el arreglo isr
   Retorno: void
*/
void calculo_isr(float bruto[], float isr[]) {
   // Definicion de valores segun el primer sueldo
   float total = bruto[0];
   float calc = bruto[0]*CANT;
   float res = proyectado(calc)/CANT;
   float t_isr = res;
   isr[0] = res;

   // Calculo de valores de los siguientes meses
   for (int i = 1; i < CANT; i++) {

      if (bruto[i] == bruto[i-1]) {
         // Si el sueldo no cambia, el ISR se mantiene

         isr[i] = res;
         t_isr += res;
      } else {
         // Si hay un cambio en el sueldo se calcula un nuevo ISR

         /*
         Se calcula en base al total acumulado de los sueldos hasta el momento (total)
         y proyectando el nuevo sueldo a lo que resta del año. Luego, se le restan los
         pagos previos de ISR y se divide por lo que resta del año.
         */
         res = (proyectado(total+(bruto[i]*(CANT-i))) - t_isr)/(CANT-i);
         isr[i] = res;
         t_isr += res;
      }

      total += bruto[i];
   }

}

/*
   Funcion: proyectado
   Argumentos: (float) n. Sueldo proyectado
   Objetivo: Calcular las partes del sueldo que caen en los diferentes grupos y
            determinar el porcentaje a pagar de cada una
   Retorno: total. El numero total a pagar (Falta dividirlo por los meses en los
            que se mantuvo ese sueldo)
*/
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
