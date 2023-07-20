#include "Pantalla.h"
#include "rlutil.h"
using namespace std;

//Metodo pantalla.dimensiones
void Pantalla::cursor(int x,int y)
{
    HANDLE hcon; //controlador (handle) de la salida estándar de la consola
    hcon = GetStdHandle(STD_OUTPUT_HANDLE); //utiliza la función GetStdHandle para obtener el controlador (handle) de la salida estándar de la consola, devolviendo el controlador de la consola que se utiliza para la salida estándar.
    COORD dwPos; //se crea una estructura de tipo COORD llamada dwPos para almacenar las coordenadas x e y proporcionadas
    dwPos.X = x; //Se asignan los valores de x e y a las propiedades X e Y de la estructura dwPos respectivamente.
    dwPos.Y= y; //Se asignan los valores de x e y a las propiedades X e Y de la estructura dwPos respectivamente.
    SetConsoleCursorPosition(hcon,dwPos); //utiliza la función SetConsoleCursorPosition para establecer la posición del cursor en la menu de la consola.
}

//Metodo QUE DIBUJA EL CUADRO
void Pantalla::dibujarCuadro(int x1,int y1,int x2,int y2)
{
    int i;

    for (i=x1; i<x2; i++)
    {
        cursor(i,y1);
        printf("\304"); //linea horizontal superior
        cursor(i,y2);
        printf("\304"); //linea horizontal inferior
    }

    for (i=y1; i<y2; i++)
    {
        cursor(x1,i);
        printf("\263"); //linea vertical izquierda
        cursor(x2,i);
        printf("\263"); //linea vertical derecha
    }

    cursor(x1,y1);
    printf("\332");
    cursor(x1,y2);
    printf("\300");
    cursor(x2,y1);
    printf("\277");
    cursor(x2,y2);
    printf("\331");
}


void Pantalla::dibujarCuadroDoble(int x1,int y1,int x2,int y2, int y3){
    int i;

    for (i=x1; i<x2; i++)
    {
        cursor(i,y1);
        printf("\304"); //linea horizontal superior
        cursor(i,y2);
        printf("\304"); //linea horizontal intermedia
        cursor(i,y3);
        printf("\304"); //linea horizontal inferior

    }

    for (i=y1; i<y3; i++)
    {
        cursor(x1,i);
        printf("\263"); //linea vertical izquierda
        cursor(x2,i);
        printf("\263"); //linea vertical derecha
    }

    cursor(x1,y1);
    printf("\332");
    cursor(x1,y3);
    printf("\300");
    cursor(x2,y1);
    printf("\277");
    cursor(x2,y3);
    printf("\331");
}

void Pantalla::estiloMenu(){
    system("cls");
    system("mode con: cols=80 lines=25"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
    system("COLOR 71"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS
    dibujarCuadro(0,0, 79,24); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1, 78,3); //SE DIBUJA EL CUADRO DEL TITULO
    cursor(30,2); cout<<"DELTAPOINT RESTO";
}

