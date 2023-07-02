#include "Pantalla.h"
#include "Menu.h"
#include <stdio.h>
#include <windows.h>

//FUNCION pantalla.gotoxy
void Pantalla::gotoxy(int x,int y)
{
    HANDLE hcon; //controlador (handle) de la salida est�ndar de la consola
    hcon = GetStdHandle(STD_OUTPUT_HANDLE); //utiliza la funci�n GetStdHandle para obtener el controlador (handle) de la salida est�ndar de la consola, devolviendo el controlador de la consola que se utiliza para la salida est�ndar.
    COORD dwPos; //se crea una estructura de tipo COORD llamada dwPos para almacenar las coordenadas x e y proporcionadas
    dwPos.X = x; //Se asignan los valores de x e y a las propiedades X e Y de la estructura dwPos respectivamente.
    dwPos.Y= y; //Se asignan los valores de x e y a las propiedades X e Y de la estructura dwPos respectivamente.
    SetConsoleCursorPosition(hcon,dwPos); //utiliza la funci�n SetConsoleCursorPosition para establecer la posici�n del cursor en la menu de la consola.
}

//FUNCION QUE DIBUJA EL CUADRO
void Pantalla::dibujarCuadro(int x1,int y1,int x2,int y2)
{
    int i;

    for (i=x1; i<x2; i++)
    {
        gotoxy(i,y1);
        printf("\304"); //linea horizontal superior
        gotoxy(i,y2);
        printf("\304"); //linea horizontal inferior
    }

    for (i=y1; i<y2; i++)
    {
        gotoxy(x1,i);
        printf("\263"); //linea vertical izquierda
        gotoxy(x2,i);
        printf("\263"); //linea vertical derecha
    }

    gotoxy(x1,y1);
    printf("\332");
    gotoxy(x1,y2);
    printf("\300");
    gotoxy(x2,y1);
    printf("\277");
    gotoxy(x2,y2);
    printf("\331");
}

void Pantalla::dibujarCuadroDoble(int x1,int y1,int x2,int y2, int y3){
    int i;

    for (i=x1; i<x2; i++)
    {
        gotoxy(i,y1);
        printf("\304"); //linea horizontal superior
        gotoxy(i,y2);
        printf("\304"); //linea horizontal intermedia
        gotoxy(i,y3);
        printf("\304"); //linea horizontal inferior

    }

    for (i=y1; i<y3; i++)
    {
        gotoxy(x1,i);
        printf("\263"); //linea vertical izquierda
        gotoxy(x2,i);
        printf("\263"); //linea vertical derecha
    }

    gotoxy(x1,y1);
    printf("\332");
    gotoxy(x1,y3);
    printf("\300");
    gotoxy(x2,y1);
    printf("\277");
    gotoxy(x2,y3);
    printf("\331");
}
