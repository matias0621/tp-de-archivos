#include <stdio.h>
#include <stdlib.h>
#include <string.h> // agrego librerias pilas y string
#include "Pila.h"
#include <time.h>



/*                        PRACTICO 7 - ARCHIVOS
En cada ejercicio, el archivo debe abrirse y cerrarse dentro de cada función.
La variable de tipo FILE* debe ser local a la función.
Se puede pasar por parámetro una variable de tipo char[30] con el nombre del archivo,
o trabajar con una constante declarada ejemplos: “archivo.bin” o "Alumnos.dat",


Utilizando datos simples (int, char, float, etc):

1- Hacer una función que agregue un elemento al final de un archivo.
2- Hacer una función que muestre por pantalla el contenido de un archivo.
3- Hacer una función que retorne la cantidad de registros que contiene un archivo.

Utilizando la estructura:

typedef struct {
     int legajo;
     char nombreYapellido [30];
     int edad;
     int anio;
//año que cursa, recordar que no podemos utilizar la ñ para definir variables
} stAlumno;

4- Crear una función que cargue un archivo de alumnos. Abrirlo de manera tal de verificar si el
   archivo ya está creado previamente. Cargar el archivo con 5 datos. Cerrarlo dentro de la función
5- Crear una función que muestre por pantalla los registros de un archivo de alumnos. MODULARIZAR
6- Crear una función que permita agregar de a un elemento al final del archivo.
  O sea, se debe abrir el archivo, se piden los datos (se llena una variable de tipo struct Alumno),
  se escribe en el archivo y se cierra.
7- Crear una función que pase a una pila los números de legajo de los alumnos mayores de edad.
8- Dado un archivo de alumnos, hacer una función que cuente la cantidad de alumnos mayores
    a edad específica que se envía por parámetro.
9- Dado un archivo de alumnos, mostrar por pantalla el nombre de todos los alumnos entre un rango
   de edades específico (por ejemplo, entre 17 y 25 años). Dicho rango debe recibirse por parámetro. ModulariZAR
10- Dado un archivo de alumnos, mostrar los datos del alumno de mayor edad. Modularizar.
11- Crear una función que retorne la cantidad de alumnos que cursan un determinado año. El año
    buscado se pasa por parámetro.
12- Crear una función que reciba como parámetro un arreglo de tipo alumno y lo copie en el archivo.
    Asimismo, realice otra función que pase los elementos del archivo a un arreglo de alumnos, filtrando
    los estudiantes de un año en particular.
13- Crear una función que retorne la cantidad de registros que tiene el archivo. Usar fseek y ftell.
    Puede pensar la función para uso genérico, que sirva para averiguar la cantidad de registros de cualquier archivo.
14- Dado un archivo de alumnos, que tenga al menos 10 registros, hacer una función que muestre el contenido
    de un registro, cuyo número (entre 0 y 9) se pase por parámetro. Controlar no sobrepasar los límites del archivo.
15- Realice una (o varias) funciones que permitan modificar un registro existente en el archivo de alumnos.
    La misma debe permitir modificar uno o todos los campos de la estructura y sobreescribir el registro existente
    en el archivo.
16- Dado un archivo de alumnos, hacer una función que invierta los elementos del mismo. No se puede usar otro archivo
   auxiliar ni un arreglo auxiliar. Debe trabajar sobre el archivo. Puede utilizar variables de tipo alumno auxiliares.
17- Hacer una función principal que pruebe el funcionamiento de todos los incisos anteriores, con un menú de opciones
para poder ejecutar todas las funciones requeridas. Tengan presente la correcta declaración y el ámbito de variables.*/


////////////////////////////////////////////////////////////////////////////////////////////////
// DEFINE STRUCT:
typedef struct
{
    int legajo;
    char nya [30]; //nombreYapellido
    int edad;
    int anio; //año que cursa, recordar que no podemos utilizar la ñ para definir variables
} alumno;

////////////////////////////////////////////////////////////////////////////////////////////////////
// PROTOTIPOS:
void agregaElementoAlFinalDelArchivo(char ArchivoEnteros[], int dato);
void mostrarArchivoBinario(char ArchivoEnteros[]);
int cuentaElementosArchivo(char ArchivoEnteros[]);
void guardaCantFijaAlumnos(char archivoAlumnos[], int cant);
void mostrarAlumno(alumno a);
void muestraAlumnos(char archivoAlumnos[]);
void guardaAlumnosDeAUno(char archivoAlumnos[]);
alumno cargaUnAlumno();
void pasaMayoresAPila(char archivoAlumnos[], Pila * p);
int cuentaAlumnosMayores(char archivoAlumnos[], int edadApasar);
void muestraAlumnosPorRangoEdad(char archivoAlumnos[], int edadMin, int edadMax);
alumno encuentraMayorAlumno(char archivo[]);
void encuentraMayorAlumno2(char archivo[]);
int cuentaAlumnosPorCurso (char archivoAlumnos[], int anio);
void arrayToArchivo(char archivoAlumnos[], alumno arregloAlumnos[], int validos);
int cuentaRegistrosArchivoFtell(char nombreArchivo[]);
int cuentaRegistrosArchivoParaCualquierArchivo(char nombreArchivo[], int sizeofDato);
void muestraAlumnoAEleccion(char archivo[], int pos);
int pasarArchivoToArreglo(char archivoAlumnos[], alumno facultad[], int dimension, int anio);
void invierteArchivo(char archivoAlumnos[]);
int cargaArregloAlumnos(alumno a[], int dimension);
alumno modificarDatosAlumno(alumno a);
void modificarAlumnoAeleccion(char archivo[], int pos);
void muestraArregloAlumnos(alumno a[], int validos);

///**************************************** MAIN: **********************************************************************

int main()
{
// ejer 1, 2 y 3
    char ArchivoEnteros[]= {"datossimples.bin"};
    char archivoAlumnos[]={"alumnos.dat"};

    srand(time(NULL));
    int numero= rand()%100;

    agregaElementoAlFinalDelArchivo(ArchivoEnteros, numero);

    puts("\nArchivo de datos simples\n");
    mostrarArchivoBinario(ArchivoEnteros);

    int cantidad=cuentaElementosArchivo(ArchivoEnteros);

    printf("\nLa cantidad de elementos en el archivo es %d\n", cantidad);
    system("pause");
    system("cls");

// ejer 4:
    guardaCantFijaAlumnos(archivoAlumnos, 5);
    system("pause");
    system("cls");

// ejer 5
    puts("\nDespues de agregar 5 alumnos\n");
    muestraAlumnos(archivoAlumnos);
    system("pause");
    system("cls");

// ejer 6
    puts("\n Cargue nuevos alumnos al archivo\n");
    guardaAlumnosDeAUno(archivoAlumnos);
    system("pause");
    system("cls");

    puts("\nDespues de agregar alumnos al final\n");
    muestraAlumnos(archivoAlumnos);
    system("pause");
    system("cls");

// ejer 7
    Pila mayores;
    inicpila(&mayores);

    pasaMayoresAPila(archivoAlumnos, &mayores);

    puts("\nPila con los legajos de los mayores:\n");
    mostrar(&mayores);
    system("pause");
    system("cls");

// ejer 8
    int edadApasar;
    printf("\nIngrese la edad a partir de la cual quiere buscar en el archivo los alumnos mayores a esa edad\n");
    scanf("%d", &edadApasar);
    int cantidadMayores=cuentaAlumnosMayores(archivoAlumnos, edadApasar);
    printf("\nLa cantidad de alumnos mayores de edad es %d\n ", cantidadMayores);
    system("pause");
    system("cls");

// ejer 9
    int edadMin, edadMax;
    printf("\nIngrese desde qué edad y hasta qué edad quiere buscar en el archivo y mostrar alumnos\n");
    scanf("%d", &edadMin);
    scanf("%d", &edadMax);

    printf("\nLos alumnos del archivo de entre %d y %d añios son: \n", edadMin, edadMax);
    muestraAlumnosPorRangoEdad(archivoAlumnos, edadMin, edadMax);
    system("pause");
    system("cls");

// ejer 10
    alumno mayorAl= encuentraMayorAlumno(archivoAlumnos);
    puts("\nEl alumno con mayor edad es:\n"); // luego mostramos por pantalla el result
    mostrarAlumno(mayorAl);
    system("pause");
    system("cls");

// ejer 11
    int curso, cantAnio;
    printf("\nIngrese de que anio quiere buscar alumnos en el archivo y mostrarlos\n");
    scanf("%d", &curso);

    cantAnio= cuentaAlumnosPorCurso(archivoAlumnos, curso);
    printf("\nCantidad de alumnos en %d anio: %d\n", curso, cantAnio);
    system("pause");
    system("cls");

/// ejer 12 - a)
    puts("\nArchivo de alumnos\n");
    muestraAlumnos(archivoAlumnos);
    alumno arreglo[50];
    int validos1=cargaArregloAlumnos(arreglo, 50);
    arrayToArchivo(archivoAlumnos, arreglo, validos1);
    puts("\nArchivo con los alumnos del arreglo agregados\n");
    muestraAlumnos(archivoAlumnos);
    system("pause");
    system("cls");

/// ejer 12 - b)
    alumno arregloPorAnio[50];
    int validos= pasarArchivoToArreglo(archivoAlumnos, arregloPorAnio, 50, 2);
    puts("\nArreglo con alumnos de 2do anio\n");
    muestraArregloAlumnos(arregloPorAnio, validos);
    system("pause");
    system("cls");

// ejer 13
    //int sizeofDato= sizeof(alumno);
    int cantEnArchivo= cuentaRegistrosArchivoFtell(archivoAlumnos);
    printf("\nLa cantidad de registros en el archivo de alumnos es %d\n", cantEnArchivo);
    system("pause");
    system("cls");

/// ejer 14
    int pos;
    printf("\nIngrese el nro de posicion del alumno que quiere mostrar\n");
    scanf("%d", &pos);
    printf("\nMostraremos el %d alumno del archivo\n", pos);
    muestraAlumnoAEleccion(archivoAlumnos, pos);

    system("pause");
    system("cls");

/// ejer 15
    int pos2;
    printf("\nIngrese el nro de posicion del alumno que quiere modificar\n");
    scanf("%d", &pos2);
    printf("\nModificaremos el %d° alumno del archivo\n", pos2);

    modificarAlumnoAeleccion(archivoAlumnos, pos2);

    puts("\nArchivo despues de modificacion\n");
    muestraAlumnos(archivoAlumnos);
    system("pause");
    system("cls");

// ejerc 16
    puts("\nArchivo antes de invertir\n");
    muestraAlumnos(archivoAlumnos);

    invierteArchivo(archivoAlumnos);

    puts("\nArchivo despues de invertir\n");
    muestraAlumnos(archivoAlumnos);

    return 0;
}


///***********************  FUNCIONES: *********************************************************************************

/// 1- Hacer una función que agregue un elemento al final de un archivo.

void agregaElementoAlFinalDelArchivo(char ArchivoEnteros[], int dato)
{
    FILE *buf= fopen(ArchivoEnteros, "ab");

    if(buf!=NULL)
    {
        fwrite(&dato, sizeof(int), 1, buf);
        fclose(buf);
    }
}

///2- Hacer una función que muestre por pantalla el contenido de un archivo.

void mostrarArchivoBinario(char ArchivoEnteros[])
{
    FILE *archi= fopen(ArchivoEnteros,"rb");

    if(archi!=NULL)
    {
        int aux;

        printf("\nContenido del archivo:\n\n");

        while( (fread(&aux, sizeof(int),1,archi) ) >0)
        {
            printf(" - %d -", aux);
        }
        fclose(archi);
    }
}

/// 3- Hacer una función que retorne la cantidad de registros que contiene un archivo.

int cuentaElementosArchivo(char ArchivoEnteros[])
{

    FILE* archi= fopen(ArchivoEnteros, "rb");
    int rta= 0;

    if(archi!=NULL)
    {
        int aux;

        while(fread(&aux, sizeof(int), 1, archi)>0) // contamos los registros leyendolos uno por uno
        {
            rta++;
        }
        fclose(archi);
    }
    return rta;
}

/// EJERC 4 - Utilizando la estructura:
/*
typedef struct
{
    int legajo;
    char nya [30]; //nombreYapellido
    int edad;
    int anio; //año que cursa, recordar que no podemos utilizar la ñ para definir variables
} alumno; */

/// Crear una función que cargue un archivo de alumnos. Abrirlo de manera tal de verificar si el archivo
/// ya está creado previamente. Cargar el archivo con 5 datos. Cerrarlo dentro de la función.

// void porq no retorna nada,los alumnos se guardan directamente en el archivo. char
// archivoAlumnos es el nombre del archivo, que esta guardado en un arreglo char


void guardaCantFijaAlumnos(char archivoAlumnos[], int cant)
{
    FILE* archi= fopen(archivoAlumnos,"ab");

    if(archi!=NULL)
    {
        int cont= 0;
        alumno a;

        while(cont<cant)
        {
            a= cargaUnAlumno();

            fwrite(&a,sizeof(alumno),1,archi);

            cont++;
        }
        fclose(archi);
    }
}

/// funcion aux que carga un solo alumno

alumno cargaUnAlumno()
{
    alumno a;

        puts("\n----------------------------------");
        printf("\n Ingrese legajo: ");
        scanf("%d", &a.legajo);

        printf("\n Ingrese nombre y apellido: ");
        fflush(stdin);
        gets(a.nya);

        printf("\n Ingrese edad: ");
        scanf("%d", &a.edad);

        printf("\n Ingrese año que cursa: ");
        scanf("%d", &a.anio);
        puts("----------------------------------\n");

    return a;
}

/// 5- Crear una función que muestre por pantalla los registros de un archivo de alumnos.

void mostrarAlumno(alumno a) /// funcion auxiliar que muestra uno solo
{
    puts("\n---------------------------------------");
    printf("\n           Legajo: %d", a.legajo);
    printf("\nNombre y Apellido: %s", a.nya);
    printf("\n             Edad: %d", a.edad);
    printf("\n              Anio: %d", a.anio);
    puts("\n---------------------------------------");
}

/// sin usar feof (mas aconsejable para no olvidarse de la doble verificacion)

void muestraAlumnos(char archivoAlumnos[])
{
    FILE *archi= fopen(archivoAlumnos, "rb");

    if (archi!=NULL)
    {
        alumno a;

        while( (fread(&a,sizeof(alumno),1,archi)) >0 )
        {
            mostrarAlumno(a);
        }
        fclose(archi);
    }
}

/// usando feof
void muestraAlumnosFEOF(char archivoAlumnos[])
{
    FILE *archi= fopen(archivoAlumnos, "rb");

    if (archi!=NULL)
    {
        alumno a;

        while(!feof(archi))
        {
            fread(&a,sizeof(alumno),1,archi);
            if(!feof(archi)) /// si se usa feof hay que hacer doble verificacion!!
            {
                mostrarAlumno(a);
            }
        }
        fclose(archi);
    }
}

/// 6- Crear una función que permita agregar de a un elemento al final del archivo. O sea:
/// Se debe abrir el archivo, se piden los datos (se llena 1 variable de tipo alumno), se escribe en el archivo y se cierra.

void guardaAlumnosDeAUno(char archivoAlumnos[])
{
    FILE* archi= fopen(archivoAlumnos,"ab");

    if(archi!=NULL)
    {
        alumno a;
        char control= 's';

        while (control== 's'){
            a= cargaUnAlumno(); //reutilizo lo ya hecho. Si no hubieramodularizado no se podria
            fwrite(&a,sizeof(alumno),1,archi);

            printf("Quiere seguir cargando datos en el archivo? Presione s o n\n");
            fflush(stdin);
            scanf("%c", &control);
        }
        fclose(archi);
    }
}


/// 7- Crear una función que pase a una pila los números de legajo de los alumnos mayores de edad.

void pasaMayoresAPila(char archivoAlumnos[], Pila* p)
{
    FILE* archi= fopen(archivoAlumnos, "rb");

    if(archi!=NULL){
        alumno a;

        while( (fread(&a,sizeof(alumno),1,archi)) >0) {
            if(a.edad >= 18){
                apilar(p, a.legajo);
            }
        }
        fclose(archi);
    }
}

/// 8- Dado un archivo de alumnos, hacer una función que cuente la cantidad de alumnos mayores
///  a edad específica que se envía por parámetro.

int cuentaAlumnosMayores(char archivoAlumnos[], int edadApasar)
{
    FILE* archi= fopen(archivoAlumnos, "rb");
    int rta= 0;

    if(archi!=NULL)
    {
        alumno a;

        while( (fread(&a,sizeof(alumno),1,archi)) > 0)
        {
            if(a.edad >= edadApasar){
                rta++;
            }
        }

        fclose(archi);
    }
    return rta;
}

/// 9)Dado un archivo de alumnos, mostrar por pantalla el nombre de todos los alumnos entre un rango
/// de edades específico (por ej, entre 17 y 25 años). Dicho rango debe recibirse por parámetro. Modularizar

void muestraAlumnosPorRangoEdad(char archivoAlumnos[], int edadMin, int edadMax)
{
    FILE* archi= fopen(archivoAlumnos, "rb");

    if(archi!=NULL)
    {
        alumno a;

        while( (fread(&a,sizeof(alumno),1,archi)) > 0)
        {
            if( (a.edad >= edadMin) && (a.edad <= edadMax) )
            {
                mostrarAlumno(a);
            }
        }
        fclose(archi);
    }
}


/// 10- Dado un archivo de alumnos, mostrar los datos del alumno de mayor edad. Modularizar.

alumno encuentraMayorAlumno(char archivo[])
{
    FILE* archi= fopen(archivo, "rb");
    alumno mayor;

    if(archi)
    {
        alumno aux;

        fread(&mayor,sizeof(alumno),1,archi); // leemos un registro al que consideramos el mayor

        while(fread(&aux,sizeof(alumno),1,archi)>0) // y luego comparamos contra todos los registros del archivo
        {
            if(mayor.edad < aux.edad){
                mayor= aux;
            }
        }
        fclose(archi);
    }
    return mayor; //el mayor lo retornamos y lo mostramos en el main, para que la funcion sea mas reutilizable
}

/// 11- Crear una función que retorne la cantidad de alumnos que cursan un determinado año.
/// El año buscado se pasa por parámetro.

int cuentaAlumnosPorCurso (char archivoAlumnos[], int anio)
{
    FILE* archi= fopen(archivoAlumnos,"rb");
    int rta= 0;

    if(archi!=NULL)
    {
        alumno aux;

        while( (fread(&aux,sizeof(alumno),1,archi)) > 0)
        {
            if(aux.anio == anio){
                rta++;
            }
        }
        fclose(archi);
    }
    return rta;
}



/// 12- Crear una función que reciba como parámetro un arreglo de tipo alumno y lo copie en el archivo.

void arrayToArchivo(char archivoAlumnos[], alumno arregloAlumnos[], int validos)
{
    FILE* archi= fopen(archivoAlumnos,"ab");

    if(archi!=NULL)
    {
        fwrite(arregloAlumnos,sizeof(alumno),validos,archi); //arregloAlum va sin & porq 1 arreglo es 1 puntero,
                                                            // validos es cuantos hay en el arreglo y voy a grabar
        fclose(archi);
    }
}



/// 12- Asimismo, realice otra función que pase los elementos del archivo a un arreglo de alumnos, filtrando
/// los estudiantes de un año en particular.

int pasarArchivoToArreglo(char archivoAlumnos[], alumno facultad[], int dimension, int anio)
{
    FILE* buf= fopen(archivoAlumnos,"rb");

    int i= 0;

    if(buf)
    {
        alumno temp;

        while ( (fread(&temp,sizeof(alumno),1,buf)>0) && (i<dimension) )
        {
            if (anio == temp.anio){
                facultad[i] = temp;
                i++;
            }
        }
        fclose(buf);
    }
    return i;
}


/// 13- Crear una función que retorne la cantidad de registros que tiene el archivo.
/// Usar fseek y ftell.
/// Puede pensar la función para uso genérico, que sirva para averiguar la
/// cantidad de registros de cualquier archivo.

int cuentaRegistrosArchivoFtell(char nombreArchivo[])
{
    int cantidad =0;
    FILE* archi= fopen(nombreArchivo,"rb"); /// no funciona si abro con ab o a+b

    if(archi!=NULL){
        fseek(archi,0, SEEK_END); // me posiciono al final del archivo

        cantidad = ftell(archi)/ sizeof(alumno); // divido la cantidad de bytes totales del archivo por la cantidad de bytes de un registro de alumnos

        fclose(archi);              // si solo llamo a ftell sin dividir tengo que usar long en vez de int porque es un numero largo
    }
    return cantidad;
}


int cuentaRegistrosArchivoParaCualquierArchivo(char nombreArchivo[], int sizeofDato)
{
    int cantidad= 0;
    FILE* archi= fopen(nombreArchivo,"rb"); /// OJO!! No sirve usar modo ab ni a+b

    if(archi!=NULL)
    {
        fseek(archi,0,2); // me posiciono al final del archivo

        cantidad = ftell(archi)/ sizeofDato; // divido la cantidad de bytes totales del archivo por la cantidad de bytes de un registro de alumnos

        fclose(archi);              // si solo llamo a ftell sin dividir tengo que usar long en vez de int porque es un numero largo
    }
    return cantidad;
}



/// 14- Dado un archivo de alumnos, que tenga al menos 10 registros, hacer una función que muestre el contenido de un registro, cuyo
/// número (entre 0 y 9) se pase por parámetro. Controlar no sobrepasar los límites del archivo.

void muestraAlumnoAEleccion(char archivo[], int pos)
{
    int cant= cuentaRegistrosArchivoFtell(archivo); /// OJO!! esta abre y cierra el archivo,
                                                  ///asi q hay q hacerlo antes del fopen
    if (pos <= cant){

        FILE* archi= fopen(archivo, "rb");

        if(archi!=NULL){

            alumno a;

            fseek(archi, sizeof(alumno)*(pos-1), SEEK_SET); // tener en cuenta que para leer el registro n°1 del archivo tenemos que
                                                          // posicionarnos en cero, porq lo que entra por parametro es el Nro de registro, no la posicion, entonces hay que restarle 1
            fread(&a,sizeof(alumno),1,archi);

            mostrarAlumno(a); /// puedo mostrarlo o retornarlo

            fclose(archi);
        }
    }
}

/// 15- Realice una (o varias) funciones que permitan modificar un registro existente en el archivo de alumnos.
/// La misma debe permitir modificar 1 o todos los campos de la estructura y sobreescribir el registro existente en el archivo.


void modificarAlumnoAeleccion(char archivo[], int pos)
{
    FILE* archi= fopen(archivo, "r+b"); /// importante!

    if(archi!=NULL)
    {
        alumno a;
        fseek(archi, sizeof(alumno)*(pos-1), SEEK_SET);
        fread(&a,sizeof(alumno),1,archi);

        a = modificarDatosAlumno(a);

               /// importante reposicionarse!!!!
        fseek(archi, sizeof(alumno)*(-1), SEEK_CUR); //voy 1 para atras para sobreescribirlo
               ///tambien puede ser: fseek(archi, sizeof(alumno)*(pos-1), SEEK_SET);
        fwrite(&a,sizeof(alumno),1,archi);

        fclose(archi);
    }
}


alumno modificarDatosAlumno(alumno a) //esta es una funcion auxiliar de la otra que modifica alumnos y lo graba en el archivo
{
        printf("\nEstos son los datos actuales del alumno\n");
        mostrarAlumno(a);

        char control = 'n'; // esto sirve para que pueda modificar un campo, dos, o LOS 3

        printf("\n Desea Modificar nombre y apellido PRESIONE s:? %s\n", a.nya);
        fflush(stdin);
        scanf("%c",&control);
        if (control == 's'){
            printf("Ingrese NUEVO nombre y apellido\n");
            fflush(stdin);
            gets(a.nya);
        }

        printf("\n Desea Modificar la edad: %d\n", a.edad);
        fflush(stdin);
        scanf("%c",&control);
        if (control == 's'){
            printf("Ingrese NUEVA edad\n");
            scanf("%d", &a.edad);
        }

        printf("\n Desea Modificar el año que cursa: %d\n", a.anio);
        fflush(stdin);
        scanf("%c",&control);
        if (control == 's'){
            printf("Ingrese NUEVO Año de Ingreso\n");
            scanf("%d", &a.anio);
        }

        printf("\nAsi quedo modificado el alumno\n");
        mostrarAlumno(a);

return a;
}


/// 16- Dado 1 archivo de alumnos, hacer 1 función que invierta los elementos del mismo.
/// No se puede usar otro archivo auxiliar ni 1 arreglo auxiliar.


void invierteArchivo(char archivoAlumnos[])
{
    alumno alu_principio, alu_final;
    int inicio= 0;
    int cantidad= cuentaRegistrosArchivoFtell(archivoAlumnos);// calculo cuántos regiatros hay en el archivo
    int fin= cantidad-1;

    FILE* archi= fopen(archivoAlumnos, "r+b");

    if(archi!=NULL)
    {
        while(inicio < fin)   // si inicio y fin se juntaron, o inicio pasó a fin, es porque llego al medio
        {          // vamos al ppio y leemos
            fseek(archi, inicio*sizeof(alumno),SEEK_SET);
            fread(&alu_principio, sizeof(alumno), 1, archi);
                  // vamos al final y leemos
            fseek(archi, fin*sizeof(alumno), SEEK_SET);
            fread(&alu_final, sizeof(alumno), 1, archi);

                  // vamos al ppio y escribimos
            fseek(archi, inicio*sizeof(alumno),SEEK_SET);
            fwrite(&alu_final, sizeof(alumno), 1, archi);
                  // vamos al final y escribimos
            fseek(archi, fin*sizeof(alumno), SEEK_SET);
            fwrite(&alu_principio, sizeof(alumno), 1, archi);

            inicio++;
            fin--;
        }
        fclose(archi);
    }
}



///****************************** FUNCIONES auxiliares PARA EL TP

int cargaArregloAlumnos(alumno a[], int dimension)
{
    int i=0;
    char letra ='s';
    printf("\n\nIngrese nuevos alumnos al arreglo\n\n");

    while(letra=='s' && i<dimension)
    {
        a[i]= cargaUnAlumno();
        i++;

        printf("\n Quiere seguir cargando? Presione s o n ");
        fflush(stdin);
        scanf("%c", &letra);
    }
    return i;
}


void muestraArregloAlumnos(alumno a[], int validos)
{
    int i=0;

    printf("\n\nArreglo de alumnos\n\n");

    while(i<validos)
    {
        mostrarAlumno(a[i]);
        i++;
    }
}
