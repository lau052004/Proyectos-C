/*Nombre del archivo: hdispersa.c
Autores: Jose Manuel Rodriguez, Laura Valentina Ovalle, Juan Miguel Zuluaga
Objetivo: Determinar mediante concurrencia si una matriz es dispersa o no utilizando hilos 
Fecha de finalizacion: 30/09/2023

Funciones que lo componen:
int EsNumero(char *cadena);
int EsPorcentaje(char *cadena);
bool ContadorComando(int argc, char *argv[], int comando);
bool ValidarComando(int argc, char *argv[], struct comando *comandoIngresado);
bool ValoresCorrectos(int argc, char *argv[], struct comando *comandoIngresado);
int VerificarComando(int argc, char *argv[], struct comando *comandoIngresado);
int LeerArchivo(const char *nombreArchivo, int **matriz, int filas,int
columnas); void EsDispersa(int cant_elementos, int valor_p, int
diferentes_de_cero, char *nombre_archivo); void *sumar_dif_cero(void *indice);
int CrearHilosElem(int valor_n, int **matriz, int cant_filas, int cant_col, int
valor_p, char *valor_a); int AsignarHilos(int valor_n, int **matriz, int
cant_filas, int cant_col, int valor_p, char *valor_a);
*/
#include "hdispersa.h" // Incluimos el archivo de cabecera personalizado
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*

      VALIDACIÓN DE LOS DATOS DE ENTRADA

*/

//-------------------------------------------------------------------------------------------------------
/*
Autores: Jose Manuel Rodriguez, Laura Valentina Ovalle, Juan Miguel Zuluaga
Parámetros de entrada:
                      - cadena: Arreglo de caracteres que se intenta convertir a número. 
Parámetros de salida:
                      - Retorna 1 si la cadena representa un número válido y no negativo, 0 en caso contrario. 
Función: Verificar si una cadena de caracteres representa un número válido y no negativo.
*/
int EsNumero(char *cadena) {
  char *endptr;
  long numero = strtol(cadena, &endptr, 10);

  // Verifica si no hay caracteres no numéricos en la cadena y si endptr apunta
  // al final.
  if (*endptr == '\0') {
    if (numero >= 0) {
      return 1; // Es un número válido y no negativo.
    }
  }
  return 0; // No es un número válido o es negativo.
}

//-------------------------------------------------------------------------------------------------------
/*
Autores: Jose Manuel Rodriguez, Laura Valentina Ovalle, Juan Miguel Zuluaga
Parámetros de entrada:
                      - cadena: Arreglo de caracteres que se intenta convertir a número. 
Parámetros de salida:
                      - Retorna 1 si la cadena representa un número válido y está en el rango [0, 100], 0 en caso contrario. 
Función: Verificar si una cadena de caracteres representa un número válido y está en el rango [0, 100].
*/
int EsPorcentaje(char *cadena) {
  // Intenta convertir la cadena en un número utilizando strtol.
  char *endptr;
  long numero = strtol(cadena, &endptr, 10);

  // Verifica si no hay caracteres no numéricos en la cadena y si endptr apunta
  // al final.
  if (*endptr == '\0') {
    // Verifica si el número no es negativo.
    if (numero >= 0 && numero <= 100) {
      return 1; // Es un número válido y no negativo.
    }
  }
  return 0; // No es un número válido o es negativo.
}

//-------------------------------------------------------------------------------------------------------
/*
Autores: Jose Manuel Rodriguez, Laura Valentina Ovalle, Juan Miguel Zuluaga
Parámetros de entrada:
                      - argc: Número de argumentos en la línea de comandos.
                      - argv: Arreglo de cadenas que contiene los argumentos de la línea de comandos.
                      - comando: Índice del comando que se está buscando. Parámetros de salida:
                      - Retorna true si el comando aparece exactamente una vez en la línea de comandos, false en caso contrario. 
Función: Contar las ocurrencias de un comando específico en la línea de comandos.
*/
bool ContadorComando(int argc, char *argv[], int comando) {
  int contador = 0; // contador para contar las ocurrencias del comando
  // Itera sobre los argumentos (saltando de 2 en 2, debido a que va el comando
  // seguido del valor) para buscar el comando.
  for (int i = 1; i < argc; i = i + 2) {
    if (strcmp(argv[i], argv[comando]) == 0) {
      contador++;
    }
  }
  // Verifica si el contador es exactamente 1 (el comando aparece una vez).
  if (contador != 1) {
    return false; // El comando no aparece exactamente una vez.
  } else {
    return true; // El comando aparece exactamente una vez.
  }
}

//-------------------------------------------------------------------------------------------------------
/*
Autores: Jose Manuel Rodriguez, Laura Valentina Ovalle, Juan Miguel Zuluaga
Parámetros de entrada:
                      - argc: Número de argumentos en la línea de comandos.
                      - argv: Arreglo de cadenas que contiene los argumentos de la línea de comandos.
                      - comandoIngresado: Estructura que contiene los comandos válidos. 
Parámetros de salida:
                      - Retorna true si todos los comandos en la línea de comandos son válidos, false en caso contrario. 
Función: Validar los comandos en la línea de comandos comparándolos con los comandos válidos almacenados en la estructura.
*/
bool ValidarComando(int argc, char *argv[], struct comando *comandoIngresado) {
  // Itera sobre los argumentos (saltando de 2 en 2) para validar los comandos.
  for (int i = 1; i < argc; i = i + 2) {
    // Compara el comando actual con los comandos válidos almacenados en la
    // estructura.
    if (strcmp(argv[i], comandoIngresado->comando_f) == 0 ||
        strcmp(argv[i], comandoIngresado->comando_c) == 0 ||
        strcmp(argv[i], comandoIngresado->comando_a) == 0 ||
        strcmp(argv[i], comandoIngresado->comando_n) == 0 ||
        strcmp(argv[i], comandoIngresado->comando_p) == 0) {
    } else {
      return false;
    }
  }
  return true;
}

//-------------------------------------------------------------------------------------------------------
/*
Autores: Jose Manuel Rodriguez, Laura Valentina Ovalle, Juan Miguel Zuluaga
Parámetros de entrada:
                      - argc: Número de argumentos en la línea de comandos.
                      - argv: Arreglo de cadenas que contiene los argumentos de la línea de comandos.
                      - comandoIngresado: Estructura que contiene los comandos válidos. 
Parámetros de salida:
                      - Retorna true si todos los valores asociados a los comandos son válidos, false en caso contrario. 
Función: Verificar la validez de los valores asociados a los comandos en la línea de comandos y almacenarlos en la estructura.
*/
bool ValoresCorrectos(int argc, char *argv[],
                      struct comando *comandoIngresado) {
  int num;
  // Itera sobre los argumentos (saltando de 2 en 2) para verificar los valores
  // asociados a los comandos.
  for (int i = 1; i < argc; i = i + 2) {
    if (strcmp(argv[i], comandoIngresado->comando_f) == 0) {
      num = EsNumero(argv[i + 1]);
      if (num != 1) { // Retorna false si el valor no es un número válido.
        return false;
      } else {
        comandoIngresado->valor_f = atoi(argv[i + 1]); // Almacena el valor convertido a entero.
      }
      // Verifica si el valor asociado al comando_n es un número válido.
    } else if (strcmp(argv[i], comandoIngresado->comando_c) == 0) {
      num = EsNumero(argv[i + 1]);
      if (num != 1) {
        return false;
      } else {
        comandoIngresado->valor_c = atoi(argv[i + 1]);
      }
    } else if (strcmp(argv[i], comandoIngresado->comando_n) == 0) {
      num = EsNumero(argv[i + 1]);
      if (num != 1) {
        return false;
      } else {
        comandoIngresado->valor_n = atoi(argv[i + 1]);
      }
    } else if (strcmp(argv[i], comandoIngresado->comando_p) == 0) {
      num = EsPorcentaje(argv[i + 1]);
      if (num != 1) {
        return false;
      } else {
        comandoIngresado->valor_p = atoi(argv[i + 1]);
      }
    } else if (strcmp(argv[i], comandoIngresado->comando_a) == 0) {
      comandoIngresado->valor_a = argv[i + 1];
    }
  }
  return true; // Todos los valores son válidos.
}

//-------------------------------------------------------------------------------------------------------
/*
Autores: Jose Manuel Rodriguez, Laura Valentina Ovalle, Juan Miguel Zuluaga
Parámetros de entrada:
                      - argc: Número de argumentos en la línea de comandos.
                      - argv: Arreglo de cadenas que contiene los argumentos de la línea de comandos.
                      - comandoIngresado: Estructura que contiene los comandos y valores a validar. 
Parámetros de salida:
                      - Retorna 0 si todos los comandos y valores son válidos, 1 en caso contrario. 
Función: Verificar la validez de los comandos y valores en la línea de comandos.
*/
int VerificarComando(int argc, char *argv[], struct comando *comandoIngresado) {

  bool cantidad_correcta, comandos_correctos, valores_correctos;

  // Verificación de la cantidad de argumentos
  if (argc != 11) {
    printf("Cantidad de argumentos ERRONEA \n");
    printf("Uso: %s -f <Nro. Filas> –c <Nro. Columnas> –a <archivo> –n "
           "<nhilos> –p <porcentaje>\n",
           argv[0]);
    return 1;
  }

  // Verificar que todos los comandos sean válidos
  comandos_correctos = ValidarComando(argc, argv, comandoIngresado);

  if (comandos_correctos == false) {
    printf("Al menos uno de los comandos ingresados no es válido\n");
    return 1;
  }

  // Verificar si cada comando está una vez
  for (int i = 1; i < argc; i = i + 2) {
    cantidad_correcta = ContadorComando(argc, argv, i);
    if (cantidad_correcta == false) {
      printf("Cantidad de comandos incorrecta: Se repite un comando\n");
      return 1;
    }
  }

  // Verificar que los datos ingresados para cada comando sean válidos
  valores_correctos = ValoresCorrectos(argc, argv, comandoIngresado);

  if (valores_correctos == false) {
    printf("Los datos ingresados para al menos un comando son erroneos \n");
    return 1;
  }

  // Imprimir la estructura
  /*printf("f %d, c %d, a %s, n %d, p %d \n", comandoIngresado->valor_f,
         comandoIngresado->valor_c, comandoIngresado->valor_a,
         comandoIngresado->valor_n, comandoIngresado->valor_p);*/

  return 0;
}

//-------------------------------------------VALIDACIÓN DEL ARCHIVO-------------------------------------------
/*
Autores: Jose Manuel Rodriguez, Laura Valentina Ovalle, Juan Miguel Zuluaga
Parámetros de entrada:
                      - nombreArchivo: Nombre del archivo a leer.
                      - matriz: Puntero a la matriz donde se almacenarán los
valores leídos.
                      - filas: Número de filas de la matriz.
                      - columnas: Número de columnas de la matriz.
Parámetros de salida:
                      - Retorna 0 si la lectura del archivo fue exitosa, 1 en caso contrario. 
Función: Leer una matriz desde un archivo y almacenarla en la memoria.
*/
int LeerArchivo(const char *nombreArchivo, int **matriz, int filas,
                int columnas) {
  FILE *archivo;

  archivo = fopen(nombreArchivo, "r"); // Abre el archivo en modo lectura

  if (archivo == NULL) {
    perror("Error al abrir el archivo");
    return 1;
  }
  // Lee la matriz desde el archivo
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      if (fscanf(archivo, "%d", &matriz[i][j]) != 1) {
        fprintf(stderr, "Error al leer el archivo");
        printf("%d, %d\n", i, j);
        exit(1);
      }
    }
  }

  fclose(archivo); // Cierra el archivo

  // Imprime la matriz leída
  /*printf("Matriz:\n");
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      printf("%d ", matriz[i][j]);
    }
    printf("\n");
  }*/

  return 0;
}

//-------------------------------------------------------------------------------------------------------
/*
Autores: Jose Manuel Rodriguez, Laura Valentina Ovalle, Juan Miguel Zuluaga
Parámetros de entrada:
                      - cant_elementos: Número total de elementos en la matriz.
                      - valor_p: Porcentaje necesario para considerar la matriz como dispersa.
                      - diferentes_de_cero: Número de elementos distintos de cero en la matriz.
                      - nombre_archivo: Nombre del archivo que contiene la matriz. 
Función: Determinar si una matriz es dispersa o no, según el porcentaje
de ceros.
*/
void EsDispersa(int cant_elementos, int valor_p, int diferentes_de_cero,
                char *nombre_archivo) {
  // Calcula la cantidad de ceros en la matriz
  int cantidad_ceros = cant_elementos - diferentes_de_cero;
  printf("Cantidad de ceros en la matriz: %d \n", cantidad_ceros);
  // Calcula el porcentaje de ceros en la matriz
  int porcentaje_ceros = (cantidad_ceros * 100) / cant_elementos;
  printf("Porcentaje de ceros en la matriz: %d \n", porcentaje_ceros);
  // Determina si la matriz es dispersa o no, según el porcentaje de ceros
  if (porcentaje_ceros >= valor_p) {
    printf("La matriz en el archivo %s tiene un total de %d ceros (%d "
           "porciento) que es mayor o igual a %d porciento, por tanto, se "
           "considera dispersa.\n",
           nombre_archivo, cantidad_ceros, porcentaje_ceros, valor_p);
  } else {
    printf(
        "La matriz en el archivo %s tiene un total de %d ceros (%d porciento) "
        "que es menor a %d porciento, por tanto, no se considera dispersa.\n",
        nombre_archivo, cantidad_ceros, porcentaje_ceros, valor_p);
  }
}

//-------------------------------------------------------------------------------------------------------
/*
Autores: Jose Manuel Rodriguez, Laura Valentina Ovalle, Juan Miguel Zuluaga
Parámetro de entrada:
                      - indice: Puntero a una estructura 'indices' que indica el rango de filas a procesar.
Variables globales:
                      - numeros: Puntero a un arreglo que representa la matriz
convertida a un vector. Función: Contar los elementos diferentes de cero en un
rango de filas de la matriz.
*/
void *sumar_dif_cero(void *indice) {
  int diferentes_de_cero = 0;
  // Convierte el puntero 'indice' al tipo correcto
  struct indices *index = (struct indices *)indice;
  int *resultado =
      (int *)malloc(sizeof(int)); // Asignar memoria para el resultado

  // Recorre el rango de filas y cuenta los elementos diferentes de cero
  for (int i = index->fila_inicio; i < index->fila_fin; ++i) {
    if (numeros[i] != 0) {
      diferentes_de_cero++;
    }
  }
  // Asigna memoria para el resultado
  *resultado = diferentes_de_cero;

  // Finaliza el hilo y devuelve el resultado
  pthread_exit(resultado);
}

//-------------------------------------------------------------------------------------------------------
/*
Autores: Jose Manuel Rodriguez, Laura Valentina Ovalle, Juan Miguel Zuluaga
Parámetros de entrada:
  - valor_n: Número de hilos a crear.
  - matriz: Matriz de entrada.
  - cant_filas: Número de filas en la matriz.
  - cant_col: Número de columnas en la matriz.
  - valor_p: Porcentaje para determinar si la matriz es dispersa.
  - valor_a: Nombre del archivo.
Variables globales:
                    - numeros: Puntero a un arreglo que representa la matriz
convertida a un vector.
                    - elementos_por_hilo: Número aproximado de elementos que
cada hilo procesará. Retorna: 0 si la ejecución fue exitosa, 1 en caso
contrario. Función: Crea y ejecuta hilos para procesar porciones de una matriz y
determinar si es dispersa.
*/
int CrearHilosElem(int valor_n, int **matriz, int cant_filas, int cant_col,
                   int valor_p, char *valor_a) {
  pthread_t threads[valor_n]; // arreglo de identificadores
  // int tarea_ids[valor_n];     // arreglo para pasar los parámetros
  int *resultado[valor_n];
  int k = 0, t;
  int cant_elementos = cant_filas * cant_col;
  int diferentes_de_cero = 0;
  struct indices *indice;

  // Convertir la matriz en un vector para poder recorrerlo por elementos
  // Asignar memoria para un vector de 10 elementos
  numeros = (int *)malloc(cant_elementos * sizeof(int));
  // Verificar si la asignación de memoria fue exitosa
  if (numeros == NULL) {
    printf("Error al asignar memoria para el vector.\n");
    return 1;
  }
  // Llenar el vector con los elementos de la matriz
  for (int i = 0; i < cant_filas; i++) {
    for (int j = 0; j < cant_col; j++) {
      numeros[k] = matriz[i][j];
      k++;
    }
  }

  // printf("Valor_n %d\n", valor_n);                       // debug
  // printf("filas %d\n", cant_filas);                      // debug
  // printf("columnas %d\n", cant_col);                     // debug
  printf("Elementos por hilo %f\n", elementos_por_hilo); // debug
  // Crear y ejecutar los hilos para procesar porciones de la matriz
  for (t = 0; t < valor_n; t++) {
    // Asignar memoria para una nueva estructura de índices
    indice = (struct indices *)malloc(
        sizeof(struct indices)); // Asignar memoria para una nueva estructura
    if (indice == NULL) {
      printf("Error al asignar memoria para la estructura indice.\n");
      return 1;
    }
    // Configurar los índices para la porción de la matriz que procesará el hilo
    indice->fila_inicio = t * elementos_por_hilo;
    if (t == valor_n - 1) {
      indice->fila_fin = cant_elementos;
    } else {
      indice->fila_fin = (t + 1) * elementos_por_hilo;
    }

    // Crear un hilo y pasarle la estructura de índices como argumento
    pthread_create(&threads[t], NULL, sumar_dif_cero, (void *)indice);

    // Calcular los índices de la matriz equivalente
    int fila_inicial = indice->fila_inicio / cant_col;
    int columna_inicial = indice->fila_inicio % cant_col;
    int fila_final = (indice->fila_fin - 1) / cant_col;
    int columna_final = (indice->fila_fin - 1) % cant_col;
    printf("Hijo %d: Evalua desde [%d,%d] hasta [%d,%d]\n", t, fila_inicial,
           columna_inicial, fila_final, columna_final);
  }

  for (t = 0; t < valor_n; t++) {
    // Aquí el padre espera por todos los hijos
    pthread_join(threads[t], (void *)&resultado[t]);
    printf("Diferentes de cero hijo %d: %d\n", t, *resultado[t]);
    diferentes_de_cero += *resultado[t];
    free(resultado[t]); // Liberar la memoria asignada para el resultado
  }

  printf("El padre con PID = %d termina. Total de números diferentes de cero: "
         "%d\n",
         getpid(), diferentes_de_cero);

  EsDispersa(cant_elementos, valor_p, diferentes_de_cero, valor_a);
  // Retornar 0 para indicar que la ejecución fue exitosa
  return 0;
}

//-------------------------------------------------------------------------------------------------------
/*
Autores: Jose Manuel Rodriguez, Laura Valentina Ovalle, Juan Miguel Zuluaga
Parámetros de entrada:
  - valor_n: Número de hilos a crear.
  - matriz: Matriz de entrada.
  - cant_filas: Número de filas en la matriz.
  - cant_col: Número de columnas en la matriz.
  - valor_p: Porcentaje para determinar si la matriz es dispersa.
  - valor_a: Nombre del archivo.
Variables globales:
  - elementos_por_hilo: Número aproximado de elementos que cada hilo procesará.
Retorna: 0 si la ejecución fue exitosa, 1 en caso contrario.
Función: Asigna la cantidad de elementos que cada hilo procesará y llama a la
función que crea y ejecuta hilos.
*/
int AsignarHilos(int valor_n, int **matriz, int cant_filas, int cant_col,
                 int valor_p, char *valor_a) {
  // Calcular el número de elementos que cada hilo procesará aproximadamente
  elementos_por_hilo = floor((cant_filas * cant_col) / valor_n);
  // Se llama a la función sobrecargada que reparte los hilos
  CrearHilosElem(valor_n, matriz, cant_filas, cant_col, valor_p, valor_a);
  return 0;
}

//-------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  int retorno_archivo = 0;

  struct comando comandoIngresado = {.comando_f = "-f",
                                     .comando_c = "-c",
                                     .comando_a = "-a",
                                     .comando_n = "-n",
                                     .comando_p = "-p"};

  int **matriz;
  // Verifica los comandos ingresados
  VerificarComando(argc, argv, &comandoIngresado);

  // Aloja memoria para el arreglo de punteros a arreglos (matriz)
  matriz = (int **)malloc(comandoIngresado.valor_f * sizeof(int *));
  if (matriz == NULL) {
    printf("Error al asignar memoria.\n");
    return 1;
  }

  // Aloja memoria para cada fila de la matriz
  for (int i = 0; i < comandoIngresado.valor_f; i++) {
    matriz[i] = (int *)malloc(comandoIngresado.valor_c * sizeof(int));
    if (matriz[i] == NULL) {
      printf("Error al asignar memoria.\n");
      return 1;
    }
  }
  // Lee el archivo y llena la matriz
  retorno_archivo =
      LeerArchivo(comandoIngresado.valor_a, matriz, comandoIngresado.valor_f,
                  comandoIngresado.valor_c);

  if (retorno_archivo == 1) {
    printf("FINALIZA EL PROGRAMA\n");
  } else {
    // Asigna hilos (función faltante en el código proporcionado)
    AsignarHilos(comandoIngresado.valor_n, matriz, comandoIngresado.valor_f,
                 comandoIngresado.valor_c, comandoIngresado.valor_p,
                 comandoIngresado.valor_a);

    // Liberar la memoria asignada a la matriz
    for (int i = 0; i < comandoIngresado.valor_f; i++) {
      free(matriz[i]);
    }
    free(matriz);
  }

  return 0;
}
