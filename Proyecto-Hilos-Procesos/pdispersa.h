/*Nombre del archivo: pdispersa.h
Autores: Jose Manuel Rodriguez, Laura Valentina Ovalle, Juan Miguel Zuluaga
Objetivo: Definir la estructura de datos y las funciones
necesarias para implementar la determinación de si una matriz es dispersa o no
mediante concurrencia utilizando procesos. Ademas de proporcionar
una interfaz coherente y reutilizable para el archivo de implementación
pdispersa.c. utilizando procesos 
Fecha de finalizacion: 30/09/2023
*/
#ifndef MI_HEADER_H
#define MI_HEADER_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Estructura que almacena los comandos y sus valores correspondientes
struct comando {
  char *comando_f;
  int valor_f;
  char *comando_c;
  int valor_c;
  char *comando_a;
  char *valor_a;
  char *comando_n;
  int valor_n;
  char *comando_p;
  int valor_p;
};
// Estructura para almacenar índices de filas y columnas
struct indices {
  int fila_inicio;
  int fila_fin;
};
// Funciones para verificar si una cadena es un número o porcentaje
int EsNumero(char *cadena);
int EsPorcentaje(char *cadena);
// Funciones para contar comandos, validar comandos y verificar comandos ingresados
bool ContadorComando(int argc, char *argv[], int comando);
bool ValidarComando(int argc, char *argv[], struct comando *comandoIngresado);
bool ValoresCorrectos(int argc, char *argv[], struct comando *comandoIngresado);
int VerificarComando(int argc, char *argv[], struct comando *comandoIngresado);
// Función para leer un archivo y llenar la matriz
int LeerArchivo(const char *nombreArchivo, int **matriz, int filas, int columnas);
// Funciones relacionadas con la dispersión de la matriz
void EsDispersa(int cant_elementos, int valor_p, int diferentes_de_cero, char *nombre_archivo);
// Funciones para la gestión de procesos
int CrearProcesosElem(int valor_n, int **matriz, int cant_filas, int cant_col, double elementos_por_proceso, int valor_p, char *valor_a);
int AsignarProcesos(int valor_n, int **matriz, int cant_filas, int cant_col, int valor_p, char *valor_a);
int main(int argc, char *argv[]);

#endif /* MI_HEADER_H */
