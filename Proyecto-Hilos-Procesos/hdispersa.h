/*Nombre del archivo: hdispersa.h
Autores: Jose Manuel Rodriguez, Laura Valentina Ovalle, Juan Miguel Zuluaga
Objetivo: Definir la estructura de datos y las funciones
necesarias para implementar la determinación de si una matriz es dispersa o no
mediante concurrencia utilizando hilos. Ademas de proporcionar
una interfaz coherente y reutilizable para el archivo de implementación
hdispersa.c. utilizando hilos 
Fecha de finalizacion: 30/09/2023
*/
#ifndef HDISPERSA_H
#define HDISPERSA_H

#include <stdbool.h>

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

// Variables globales
int *numeros;
double elementos_por_hilo;

// Funciones para verificar si una cadena es un número o porcentaje
int EsNumero(char *cadena);
int EsPorcentaje(char *cadena);
// Funciones para contar comandos, validar comandos y verificar comandos
// ingresados
bool ContadorComando(int argc, char *argv[], int comando);
bool ValidarComando(int argc, char *argv[], struct comando *comandoIngresado);
bool ValoresCorrectos(int argc, char *argv[], struct comando *comandoIngresado);
int VerificarComando(int argc, char *argv[], struct comando *comandoIngresado);
// Función para leer un archivo y llenar la matriz
int LeerArchivo(const char *nombreArchivo, int **matriz, int filas,
                int columnas);
// Funciones relacionadas con la dispersión de la matriz
void EsDispersa(int cant_elementos, int valor_p, int diferentes_de_cero,
                char *nombre_archivo);
void *sumar_dif_cero(void *indice);
// Funciones para la gestión de hilos
int CrearHilosElem(int valor_n, int **matriz, int cant_filas, int cant_col,
                   int valor_p, char *valor_a);
int AsignarHilos(int valor_n, int **matriz, int cant_filas, int cant_col,
                 int valor_p, char *valor_a);

#endif /* MI_HEADER_H */
