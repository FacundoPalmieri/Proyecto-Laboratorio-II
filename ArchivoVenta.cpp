#define XSCREEN 78
#define YSCREEN 24
#include <iostream>
using namespace std;
#include "ArchivoVenta.h"
#include "Pantalla.h"
#include "colors.h"
#include "Venta.h"



ArchivoVenta::ArchivoVenta(const char* Nombre){
    strcpy(_Nombre, Nombre);
    FILE *p = fopen(_Nombre, "ab");


    if(p==NULL){
      MensajeError();

    }


}

int ArchivoVenta::grabarEnDisco(Venta venta){

    FILE *p = fopen(_Nombre, "ab");


    if(p==NULL){
      MensajeError();

    }
    int grabo=fwrite(&venta, sizeof(Venta),1, p);
    fclose(p);
    return grabo;
}

Venta ArchivoVenta::leerDeDisco(int pos){

    Venta venta;

    FILE *p;
    p=fopen(_Nombre,"rb");
    if(p==NULL){
        MensajeError();
    }

    fseek(p, sizeof(Venta)*pos, SEEK_SET);
    fread(&venta, sizeof venta, 1, p);


    fclose(p);

    return venta;

}


int ArchivoVenta::cantidadVentas(){
    FILE* pFile;
    int cantidad = 0;
    pFile = fopen(_Nombre, "rb");
    if (pFile == nullptr) {
        MensajeError();
    }
    fseek(pFile, 0, SEEK_END);
    cantidad = ftell(pFile) / sizeof(Venta);
    fclose(pFile);
    return cantidad;
}
void ArchivoVenta:: MensajeError(){
    Pantalla pantalla;
    system ("cls");
    pantalla.dimensiones (4,5);
    pantalla.estiloMenu();
    cout << RED;
    pantalla.dimensiones(15,15);
    cout << "El archivo de - Ventas - no se pudo abrir." << endl;
    pantalla.dimensiones(15,16);
    cout << "Comuniquese con el area de sistemas" << endl;
    pantalla.dimensiones(15,20);
    cout << BLUE;
    system("pause");

    exit(20);


}
