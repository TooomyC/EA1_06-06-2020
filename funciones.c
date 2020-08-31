#include "funciones.h"

#define MINIMO(X, Y) ((X) < (Y) ? (X) : (Y))
#define MAXIMO(X, Y) ((X) > (Y) ? (X) : (Y))

#define TAM_CAD 1000

#define FALSO 0
#define VERDADERO 1

#define TODO_OK 0

///FUNCIONES PROPIAS ADICIONALES
//EJERCICIO 1
int matching(const char* cad, const char* sub);
int tolower (int ch);

//EJERCICIO 2
void revertirColum(int m[][COLUM], int filas, int colum);
void revertirFilas(int m[][COLUM], int filas, int colum);
void intercambiar(int* a, int* b);

//EJERCICIO 3
int contPal(const char* cad);
int contPalabra(const char* cad);
int comparador(const char* cad1, const char* cad2);
int isAlpha(char ch);

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//* FUNCIONES A DESARROLLAR                                            *//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

///EJERCICIO 1

int contarOcurrencias1_MIO(const char *cad, const char *sub) //CUENTA LA CANTIDAD MULTIPLE DE APARICIONES DE LA SUBCADENA
{
    int contMatch = 0;
    while(*cad)
    {
        if(tolower(*cad) != tolower(*sub))
            cad++;
        else
        {
            contMatch += matching(cad, sub);
            cad ++;
        }
    }

    contMatch += matching(cad, sub);

    return contMatch;
}

int contarOcurrencias2_MIO(const char *cad, const char *sub) //CUENTA LAS APARICIONES DE LA SUBCADENA
{
    int contMatch = 0, ret;

    while(*cad)
    {
        if(tolower(*cad) != tolower(*sub))
            cad++;
        else
        {
            ret = matching(cad, sub);
            if(ret)
                cad += strlen(sub);
            else
                cad ++;

            contMatch += ret;
        }
    }

    contMatch += matching(cad, sub);

    return contMatch;
}

int matching(const char* cad, const char* sub)
{   //SI COINCIDEN LOS ELEMENTOS, AVANZA CADENA Y SUB CADENA
    //SI NO COINCIDEN, AVANZA LA CADENA

    while((tolower(*cad) == tolower(*sub)) && *cad)
    {
        cad ++;
        sub ++;
    }

    return *sub == '\0';
}
int tolower (int ch) //CONVIERTE UN CARACTER MAYUSCULA A MINUSCULA
{
    if(ch >= 'A' && ch <= 'Z')
        return ch + ('a'-'A');

    return ch;
}


///EJERCICIO 2

void rotarMat180_MIO(int m[][COLUM], int filas, int colum)
{
    revertirColum(m, colum, filas);
    revertirFilas(m, filas, colum);
}

void revertirColum(int m[][COLUM], int filas, int colum)
{
    for (int i = 0; i < filas; i++)
        for (int j = 0, k = colum - 1; j < k; j++, k--)
            intercambiar(&m[j][i], &m[k][i]);
}

void revertirFilas(int m[][COLUM], int filas, int colum)
{
    for(int i = 0; i < filas; i++)
        for (int j = 0, k = colum - 1; j < k; j++, k--)
            intercambiar(&m[i][j], &m[i][k]);
}

void intercambiar(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int  mostrarMatTriangDerInf_MIO(int m[][COLUM], int filas, int colum)
{
    int  j, i, k, cantElem = 0;

    for(i = 0; i< filas; i ++)
    {
        for(j = 0; j < (i < colum ? colum - i - 1 : 0); j++)
            printf("%4s", " ");

        for(k = colum; k > (i < colum ? colum - i - 1 : 0); j++, k--)
        {
            printf("%4d", m[i][j]);
            cantElem ++;
        }

        printf("\n");
    }

    return cantElem;
}

///EJERCICIO 3

int  ordenarArchivo_MIO(const char *archEnt, const char *archSal)
{
    FILE* datos = fopen(archEnt, "rb");
    if(!datos)
    {
        puts("ERROR ABRIENDO ARCHIVO ENTRADA.");
        return ERROR_ARCH_ENT;
    }

    char* auxiliar;
    char cadArchivo[TAM_CAD], cadPila[TAM_PILA];
    int cmp; ///VARIABLE PARA PODER COMPARAR. SI DA POSITIVO, LA CADENA DE TEXTO ES MAYOR QUE LA DE PILA PRINCIPAL. SI ES NEGATIVO, LA CADENA DE TEXTO ES MENOR QUE LA DE PILA PRINCIPAL.

    tPila pPal, pAux; ///PROCEDO A ORDENAR CON 2 PILAS. UNA PRINCIPAL (DONDE ESTARAN TODOS LOS ELEMENTOS ORDENADOS EN EL ESTADO FINAL), Y UNA AUXILIAR PARA PODER APILAR Y DESAPILAR.

    crearPila_MIO(&pPal);
    crearPila_MIO(&pAux);

    while(fgets(cadArchivo, TAM_CAD, datos))
    {
        if(pilaVacia_MIO(&pPal))///SE CUMPLE, UNICAMENTE, LA PRIMERA VEZ.
            ponerEnPila_MIO(&pPal,cadArchivo,TAM_CAD);
        else
        {
            verTope_MIO(&pPal, cadPila, TAM_CAD);
            cmp = comparador(cadArchivo, cadPila); ///UTILIZO ESTA FUNCION PARA PODER COMPARAR EL TAMAÑO DE LAS CADENAS.

        ///SIGNIFICA QUE POSEEN LA MISMA CANTIDAD DE PALABRAS. Y LA PALABRA MAS LARGA, EL MISMO TAMAÑO.

                if(cmp > 0)///LA CADENA DEL ARCHIVO LEIDO ES MAYOR QUE EL TOPE DE LA PILA.
                {
                    while(!pilaVacia_MIO(&pPal) && (comparador(cadArchivo, cadPila) > 0))
                    {
                        sacarDePila_MIO(&pPal, cadPila, TAM_CAD);
                        ponerEnPila_MIO(&pAux, cadPila, TAM_CAD);
                        verTope_MIO(&pPal, cadPila, TAM_CAD);
                    }

                }
                else ///LA CADENAD DEL ARCHIVO LEIDO ES MENOR QUE EL TOPE DE LA PILA.
                {
                     ///SI LA PILA AUXILIAR ESTA VACIA, APILO DIRECTAMENTE EN LA PILA PRINCIPAL. SI NO, DEBO SACAR DE LA PILA AUXILIAR HASTA QUE SEA MENOR QUE LA CADENA DEL ARCHIVO.
                     ///LA PILA AUXILIAR NO ESTA VACIA. ASI QUE DEBO DESAPILAR PILA AUXILIAR HASTA QUE EL TOPE DE LA PILA AUXILIAR SEA MENOR QUE LA CADENA DEL ARCHIVO.

                    verTope_MIO(&pAux, cadPila, TAM_CAD);
                    while(!pilaVacia_MIO(&pAux) && (comparador(cadArchivo, cadPila)) < 0)
                    {
                        sacarDePila_MIO(&pAux, cadPila, TAM_CAD);
                        ponerEnPila_MIO(&pPal, cadPila, TAM_CAD);
                        verTope_MIO(&pAux, cadPila, TAM_CAD);
                    }
                }

            ponerEnPila_MIO(&pPal, cadArchivo, TAM_CAD);
        }
    }

    while(!pilaVacia_MIO(&pAux)) ///QUITO LOS ELEMENTOS RESTANTES DE LA PILA AUXILIAR. LOS APILO EN LA PILA PRINCIPAL.
    {
        sacarDePila_MIO(&pAux, cadPila, TAM_CAD);
        ponerEnPila_MIO(&pPal, cadPila, TAM_CAD);
    }

     FILE* nuevo = fopen(archSal, "wb");
    if(!nuevo)
    {
            while(!pilaVacia_MIO(&pPal))
    {
        sacarDePila_MIO(&pPal, cadArchivo, TAM_CAD);

        if(!strchr(cadArchivo, '\n'))
        {
            auxiliar = strchr(cadArchivo, '\0');
            *auxiliar = '\r'; ///EN WINDOWS 7, EL FIN DE LINEA SE ESCRIBE CON DOS CARACTERES ("\r" seguido de "\n").
            *(auxiliar + 1) = '\n';///REEMPLAZO EL FIN DE CADENA POR EL SALTO DE LINEA.
            *(auxiliar + 2) = '\0'; ///AGREGO EL FIN DE CADENA, LUEGO DEL SALTO DE LINEA.
        }

        printf("%s", cadArchivo);
    }
        return ERROR_ARCH_SAL;
    }

    while(!pilaVacia_MIO(&pPal))
    {
        sacarDePila_MIO(&pPal, cadArchivo, TAM_CAD);

        if(!strchr(cadArchivo, '\n'))
        {
            auxiliar = strchr(cadArchivo, '\0');
            *auxiliar = '\r'; ///EN WINDOWS 7, EL FIN DE LINEA SE ESCRIBE CON DOS CARACTERES ("\r" seguido de "\n").
            *(auxiliar + 1) = '\n';///REEMPLAZO EL FIN DE CADENA POR EL SALTO DE LINEA.
            *(auxiliar + 2) = '\0'; ///AGREGO EL FIN DE CADENA, LUEGO DEL SALTO DE LINEA.
        }

        fputs(cadArchivo, nuevo);
    }

    fclose(datos);
    fclose(nuevo);

    return 0;
}

int contPal(const char* cad) ///CUENTA PALABRAS
{
    int cont = 0, flagPal = 0;
    while(*cad)
    {
        if(isAlpha(*cad))
        {
            if(!flagPal)
            {
                flagPal = 1; ///Flag en 1, para que marque que empieza a contar la primera letra de la palabra
                cont ++;
            }
        }

        else
            if(flagPal)
            flagPal = 0;

        cad ++;
    }

    return cont;
}

int contPalabra(const char* cad) ///CUENTA CARACTERES DE DOS PALABRAS. GUARDA LA CANTIDAD DE LA 1RA EN UNA VARIABLE, CONSIDERADA MAXIMA, Y SE LA COMPARA CON LA LONGITUD DE LA PROXIMA PALABRA.
{
  int palabraMax = 0, cont = 0, flagPal = 0;
  while(*cad)
  {
    if(isAlpha(*cad))
    {
        cont ++;
        flagPal = 1; ///Flag en 1, para que marque que empieza a contar la primera letra de la palabra
    }
    else
        if(flagPal)
        {
            palabraMax = cont > palabraMax ? cont : palabraMax; ///Si la siguiente palabra es mayor que la anterior, se guarda como la mas larga. Y así, sucesivamente.
            cont = 0;
            flagPal = 0; ///Flag en 0, para que marque que sale de la palabra
        }

    cad ++;
  }

  return palabraMax;
}

int comparador(const char* cad1, const char* cad2)
{
    int res;

    res = contPal(cad1) - contPal(cad2);
    if(!res)
        res = contPalabra(cad1) - contPalabra(cad2);

    return res; ///Devuelve 0 si  son iguales. Positivo si cad1 > cad2 y negativo si cad2 > cad1
}

int isAlpha(char ch)
{
    return (ch>='A' && ch<='Z') || (ch>='a' && ch<='z');
}

void crearPila_MIO(tPila *p)
{
    p->tope = TAM_PILA;
}

int  ponerEnPila_MIO(tPila *p, const void *d, unsigned cantBytes)
{
    if(p->tope < cantBytes + sizeof(unsigned))
        return FALSO;

    p->tope -= cantBytes;
    memcpy(p->pila + p->tope, d, cantBytes);
    p->tope -= sizeof(unsigned);
    memcpy(p->pila + p->tope, &cantBytes, sizeof(unsigned));

    return VERDADERO;
}

int  verTope_MIO(const tPila *p, void *d, unsigned cantBytes)
{
    unsigned tamInfo;

    if(p->tope == TAM_PILA)
        return FALSO;

    memcpy(&tamInfo, p->pila + p->tope, sizeof(unsigned));
    memcpy(d, p->pila + p->tope + sizeof(unsigned), MINIMO(cantBytes, tamInfo));

    return VERDADERO;
}

int  pilaVacia_MIO(const tPila *p)
{
     return p->tope == TAM_PILA;
}

int  sacarDePila_MIO(tPila *p, void *d, unsigned cantBytes)
{
    unsigned tamInfo;

    if(p->tope == TAM_PILA)
        return FALSO;

    memcpy(&tamInfo, p->pila + p->tope, sizeof(unsigned));
    p->tope += sizeof(unsigned);
    memcpy(d, p->pila + p->tope, MINIMO(cantBytes, tamInfo));
    p->tope += tamInfo;

    return VERDADERO;
}


/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
