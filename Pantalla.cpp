#include "Pantalla.h"
#include "Menu.h"
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include "rlutil.h"
#define XSCREEN 78
#define YSCREEN 24
using namespace std;
//FUNCION pantalla.gotoxy
void Pantalla::gotoxy(int x,int y)
{
    HANDLE hcon; //controlador (handle) de la salida estándar de la consola
    hcon = GetStdHandle(STD_OUTPUT_HANDLE); //utiliza la función GetStdHandle para obtener el controlador (handle) de la salida estándar de la consola, devolviendo el controlador de la consola que se utiliza para la salida estándar.
    COORD dwPos; //se crea una estructura de tipo COORD llamada dwPos para almacenar las coordenadas x e y proporcionadas
    dwPos.X = x; //Se asignan los valores de x e y a las propiedades X e Y de la estructura dwPos respectivamente.
    dwPos.Y= y; //Se asignan los valores de x e y a las propiedades X e Y de la estructura dwPos respectivamente.
    SetConsoleCursorPosition(hcon,dwPos); //utiliza la función SetConsoleCursorPosition para establecer la posición del cursor en la menu de la consola.
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

void Pantalla::estiloMenu(){
    system("cls");
    Pantalla pantalla;
    system("mode con: cols=80 lines=25"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
    system("COLOR 71"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS
    dibujarCuadro(0,0,XSCREEN,YSCREEN); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1,(XSCREEN-1),3); //SE DIBUJA EL CUADRO DEL TITULO
    gotoxy(30,2); cout<<"DELTAPOINT RESTO";
}

