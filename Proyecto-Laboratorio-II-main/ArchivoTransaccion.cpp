#define XSCREEN 78
#define YSCREEN 24
#include <iostream>
#include "colors.h"
using namespace std;
#include "ArchivoTransaccion.h"
#include "Pantalla.h"


void ArchivoTransaccion :: MensajeError(){
    Pantalla pantalla;
    system ("cls");
    pantalla.dimensiones (4,5);
    pantalla.estiloMenu();
    cout << RED;
    pantalla.dimensiones(15,15);
    cout << "El archivo de - Transaccion - no se pudo abrir. ESTOY EN MÉTODO GRABAR EN DISCO DE TRANSACCION" << endl; //BORRAR COMENTARIO!!!
    pantalla.dimensiones(15,16);
    cout << "Comuniquese con el area de sistemas" << endl;
    pantalla.dimensiones(15,20);
    cout << BLUE;
    system("pause");
    exit(20);
}

ArchivoTransaccion::ArchivoTransaccion(const char* Nombre){
    strcpy(_Nombre, Nombre);
    FILE *p = fopen(_Nombre, "ab");


    if(p==NULL){
      MensajeError();

    }
}


int ArchivoTransaccion::grabarEnDisco(Transaccion transaccion){
    Pantalla pantalla;

    FILE *p;
    p=fopen(_Nombre, "ab");

    if(p==NULL){
       MensajeError();
    }

    int grabo=fwrite(&transaccion, sizeof(Transaccion), 1, p);
    fclose(p);
    return grabo;
}



int ArchivoTransaccion::grabarEnDiscoPorPosicion(int posicion, Transaccion transaccion){
    Pantalla pantalla;

	FILE *p;
	p = fopen(_Nombre, "rb+");
	if(p==NULL){
       MensajeError();
	}
	fseek(p, sizeof(Transaccion)*posicion, 0);
	int escribio = fwrite(&transaccion, sizeof(Transaccion), 1, p);
	fclose(p);
	return escribio;
}



Transaccion ArchivoTransaccion::leerDeDisco(int pos){
    Pantalla pantalla;
    Transaccion transaccion;

    FILE *p;
    p=fopen(_Nombre,"rb");
    if(p==NULL){
       MensajeError();

    }
    fseek(p,pos * sizeof(Transaccion), SEEK_SET);
    fread(&transaccion, sizeof(Transaccion), 1, p);
    fclose(p);
    return transaccion;
}


int ArchivoTransaccion::getLastIdTransaction(){
    Pantalla pantalla;
    Transaccion transaccion;
    FILE *p;
    p=fopen(_Nombre,"rb+");
    if(p==NULL){
       MensajeError();
    }
    fseek(p,sizeof(Transaccion), SEEK_END);
    int lecturas = fread(&transaccion,sizeof(Transaccion), 1, p);
    fclose(p);
    return lecturas;
}


int ArchivoTransaccion::cantidadTransacciones(){

    FILE* p = fopen(_Nombre, "rb");
    if (p == NULL) {
        MensajeError();
    }
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Transaccion);
    fclose(p);
    return cant;
}

int  ArchivoTransaccion::sobreEscribirRegistro(int posicion, Transaccion transaccion){
    Pantalla pantalla;

    FILE* p;
    p = fopen(_Nombre, "rb+");
    if (p == NULL) {
      MensajeError();
    }
    fseek(p, sizeof transaccion*posicion,0);

    // Escribe los datos modificados de vuelta al archivo
    int grabo = fwrite(&transaccion, sizeof(Transaccion), 1, p);
    fclose(p);
    return grabo;
}
