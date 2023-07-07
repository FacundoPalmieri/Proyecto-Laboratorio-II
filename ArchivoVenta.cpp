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
}

int ArchivoVenta::grabarEnDisco(Venta venta){
    Pantalla pantalla;

    FILE *p = fopen(_Nombre, "ab");


    if(p==NULL){
    cout << RED;
    pantalla.dimensiones(15,15);
    cout << "El archivo de - Ventas - no se pudo abrir." << endl;
    pantalla.dimensiones(15,16);
    cout << "Comuniquese con el area de sistemas" << endl;
    pantalla.dimensiones(15,20);
    cout << BLUE;
    system("pause");

    return -1;

    }
    int grabo=fwrite(&venta, sizeof(Venta),1, p);
    fclose(p);
    return grabo;
}

Venta ArchivoVenta::leerDeDisco(int pos){
    Pantalla pantalla;
    Venta venta;

    FILE *p;
    p=fopen("venta.dat","rb");
    if(p==NULL){
        cout << RED;
        pantalla.dimensiones(15,15);
        cout << "El archivo de - Ventas - no se pudo abrir." << endl;
    }

    fseek(p, sizeof(Venta)*pos, SEEK_SET);
    fread(&venta, sizeof venta, 1, p);


    fclose(p);

    return venta;

}


int ArchivoVenta::cantidadVentas(){
    FILE* pFile;
    int cantidad = 0;
    pFile = fopen("venta.dat", "rb");
    if (pFile == nullptr) {
        return 0;
    }
    fseek(pFile, 0, SEEK_END);
    cantidad = ftell(pFile) / sizeof(Venta);
    fclose(pFile);
    return cantidad;
}
