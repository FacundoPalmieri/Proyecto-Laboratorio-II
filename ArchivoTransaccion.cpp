#include <iostream>
#include "colors.h"
using namespace std;
#include "ArchivoTransaccion.h"
#include "Pantalla.h"


ArchivoTransaccion::ArchivoTransaccion(const char* Nombre){
    strcpy(_Nombre, Nombre);
    FILE *p = fopen(_Nombre, "ab");


    if(p==NULL){
      MensajeError();

    }
}


int ArchivoTransaccion::grabarEnDisco(Transaccion transaccion){

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


void ArchivoTransaccion :: MensajeError(){
    Pantalla pantalla;
    system ("cls");
    pantalla.cursor (4,5);
    pantalla.estiloMenu();
    cout << RED;
    pantalla.cursor(15,15);
    cout << "El archivo de - Transaccion - no se pudo abrir. ESTOY EN M�TODO GRABAR EN DISCO DE TRANSACCION" << endl; //BORRAR COMENTARIO!!!
    pantalla.cursor(15,16);
    cout << "Comuniquese con el area de sistemas" << endl;
    pantalla.cursor(15,20);
    cout << BLUE;
    system("pause");
    exit(20);
}
