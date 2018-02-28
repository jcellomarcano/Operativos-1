#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
// Lectura Proyecto I

typedef struct ruta{
   char name[200]; // Nombre del Producto
}Paths;
// Funciones

int countlines(char *filename){
    FILE *fp;
    int count = 0;  // contador de lineas
    char c;  // To store a character read from file

    // Abrimos el archivo
    fp = fopen(filename, "r");

    // chequea si el archivo existe
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 0;
    }

    // extraemos los caracteres y los guardamos en la variable c
    for (c = getc(fp); c != EOF; c = getc(fp)){
        if (c == '\n'){
            count = count + 1;
        }
    }
    // cerramos el archivo
    fclose(fp);

    return count;
};

Paths* readd(int numLines, char *filename){
  Paths* arrayP = malloc(numLines * sizeof(Paths));
  Paths* InicioArray = arrayP;
  char* line = NULL;
  //char *line2 = NULL;
  size_t len = 0;
  ssize_t readd;
  char *token;
  Paths ruta;

  FILE *file = fopen ( filename, "r" );

  if (file == NULL){
		exit(EXIT_FAILURE);
  }

	while ((readd = getline(&line, &len, file)) != -1) {
    char* dirs;
    token = strtok(line,"\n");
    //printf("%s \n", token);
    strcpy(ruta.name,token);
    *arrayP = ruta;
    //printf("%s \n", arrayP->name);
    arrayP++;
  }

  free(line);
  fclose(file);
  return InicioArray;
}

int main(int argc, char *argv[]) {

  // primero buscamos los directorios hojas para luego buscar las rutas de los archivos
  long size;
  char *buf;
  char *ptr;

  // Buscamos la direccion del path donde estamos situados para despues poder buscar el archivo.txt creado mas adelante
  size = pathconf(".", _PC_PATH_MAX);
  if ((buf = (char *)malloc((size_t)size)) != NULL);
  ptr = getcwd(buf, (size_t)size); // poner condicional para saber si la ruta que vamos a usar es la de donde estamos parados o la dada por el flag

  //printf("%s\n",ptr ); // print para verificar el path

  char *comand = "find /home/fadasgo/Escritorio/Operativos -type d -links 2  | tee archivo.txt";
  system(comand);
  system("clear");

  // ahora procedemos a leer el archivo creado para buscar los archivos de los directorios hojas

  Paths* arrayDirs;
  Paths* copiaArrayDirs; // Copia de la direccion en donde comienza la lista de productos
  int lines;   // lines contiene el numero de lineas en el archivo
  char* cod1 = "find ";
  char* cod2 = " -type f >> rutas.txt ";

  lines = countlines(argv[1]);
  //printf("LINES: %d\n",lines);
  //printf("Lineas \n");
  // Recibimos la direccion donde comienza el arreglo
  arrayDirs = readd(lines,argv[1]);
  copiaArrayDirs = arrayDirs; // creamos copia del inicio del arreglo dinamico

  //printf("PATH i: %s\n",copiaArrayDirs->name);

  // Creamos un archivo nuevo en el cual se van a encontrar las rutas finales
  system("touch rutas.txt");
  char path[500];
  // Procedemos a buscar por cada directorio hoja sus archivos
  for (int i = 0; i < lines; i++) {
    //printf("%s \n",arrayDirs->name);
    memset(path,0,500);
    strcat(path,cod1);
    strcat(path,arrayDirs->name);
    strcat(path,cod2);
    printf(" %s \n",path);
    arrayDirs++;
  }

  return 0;
}