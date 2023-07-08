#define XSCREEN 78
#define YSCREEN 24
#include <iostream>
#include "colors.h"
using namespace std;
#include "ArchivoTransaccion.h"
#include "Pantalla.h"


ArchivoTransaccion::ArchivoTransaccion(const char* Nombre){
    strcpy(_Nombre, Nombre);
}


int ArchivoTransaccion::grabarEnDisco(Transaccion transaccion){
    Pantalla pantalla;

    FILE *p;
    p=fopen(_Nombre, "ab");

    if(p==NULL){
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

    int grabo=fwrite(&transaccion, sizeof(Transaccion), 1, p);
    fclose(p);
    return grabo;
}



int ArchivoTransaccion::grabarEnDiscoPorPosicion(int posicion, Transaccion transaccion){
    Pantalla pantalla;

	FILE *p;
	p = fopen(_Nombre, "rb+");
	if(p==NULL){
       cout << RED;
       pantalla.dimensiones(15,15);
       cout << "El archivo de - Transaccion - no se pudo abrir. ESTOY EN MÉTODO GRABAR EN DISCO POR POSC DE TRANSACCION" << endl; //BORRAR COMENTARIO!!!
       pantalla.dimensiones(15,16);
       cout << "Comuniquese con el area de sistemas" << endl;
       pantalla.dimensiones(15,20);
       cout << BLUE;
       system("pause");
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
       cout << RED;
       pantalla.dimensiones(15,15);
       cout << "El archivo de - Transaccion - no se pudo abrir. ESTOY EN MÉTODO LEER DE DISCO DE TRANSACCION" << endl; //BORRAR COMENTARIO!!!
       pantalla.dimensiones(15,16);
       cout << "Comuniquese con el area de sistemas" << endl;
       pantalla.dimensiones(15,20);
       cout << BLUE;
       system("pause");
       exit(20);

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
       cout << RED;
       pantalla.dimensiones(15,15);
       cout << "El archivo de - Transaccion - no se pudo abrir. ESTOY EN MÉTODO LAST ID DE TRANSACCION" << endl; //BORRAR COMENTARIO!!!
       pantalla.dimensiones(15,16);
       cout << "Comuniquese con el area de sistemas" << endl;
       pantalla.dimensiones(15,20);
       cout << BLUE;
       system("pause");

     return 0;
    }
    fseek(p,sizeof(Transaccion), SEEK_END);
    int lecturas = fread(&transaccion,sizeof(Transaccion), 1, p);
    fclose(p);
    return lecturas;
}


int ArchivoTransaccion::cantidadTransacciones(){

    FILE* p = fopen("transaccion.dat", "rb");
    if (p == NULL) {
        return 0;
    }
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Transaccion);
    fclose(p);
    return cant;
}

void ArchivoTransaccion::sobreEscribirRegistro(int posicion, Transaccion transaccion){
    Pantalla pantalla;

    FILE* p;
    p = fopen(_Nombre, "rb+");
    if (p == NULL) {
      cout << RED;
      pantalla.dimensiones(15,15);
      cout << "El archivo de - Transaccion - no se pudo abrir. ESTOY EN MÉTODO SOBREESCRIBIR DE TRANSACCION" << endl; //BORRAR COMENTARIO!!!
      pantalla.dimensiones(15,16);
      cout << "Comuniquese con el area de sistemas" << endl;
      pantalla.dimensiones(15,20);
      cout << BLUE;
      system("pause");
      exit(20);
    }
    fseek(p, sizeof transaccion*posicion,0);

    // Escribe los datos modificados de vuelta al archivo
    fwrite(&transaccion, sizeof(Transaccion), 1, p);
    fclose(p);
}
