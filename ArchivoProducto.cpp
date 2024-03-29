#include <iostream>
#include <cstring>
#include "colors.h"
using namespace std;
#include "ArchivoProducto.h"
#include "Producto.h"
#include "Menu.h"
#include "Pantalla.h"


ArchivoProducto::ArchivoProducto(const char* Nombre)
{
    strcpy(_Nombre, Nombre);
    FILE *p = fopen(_Nombre, "ab");


    if(p==NULL){
      MensajeError();

    }
}


void ArchivoProducto::grabarEnDisco(Producto producto){
    FILE *p;

    p=fopen(_Nombre, "ab");

    if(p==NULL){
       MensajeError();
    }


    fwrite(&producto, sizeof(Producto),1, p);

    fclose(p);
}

Producto ArchivoProducto::leerDeDisco(int pos){
    Producto producto;

    FILE *p;
    p=fopen(_Nombre,"rb");

    if(p==NULL){
       MensajeError();
    }

    fseek(p,pos*sizeof(Producto), 0);
    fread(&producto, sizeof(Producto), 1, p);
    fclose(p);
    return producto;
}

int ArchivoProducto::cantidadEnArchivo(){
    Producto producto;

    FILE* p=fopen(_Nombre, "rb");


    if (p == nullptr){
        MensajeError();
    }
    fseek(p, 0, SEEK_END);

    int cantidad = ftell(p) / sizeof(Producto);

    fclose(p);

    return cantidad;
}

void ArchivoProducto::modificarRegistro(){

    system("cls");

    Pantalla pantalla;
    Producto producto;
    char Confirmacion, Nombre[50];
    int idProducto, posicion;
    float precio;

    pantalla.cursor(30,2); cout<<"DELTAPOINT RESTO";
    pantalla.dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
    pantalla.dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
    pantalla.cursor (2,5);  cout<<"MENU AJUSTE - MODIFICAR PRODUCTO";
    pantalla.cursor (2,6);  cout<<"----------------------------------";
    pantalla.cursor (2,23); cout <<"ingrese 0(cero) para volver al menu anterior";

    //BUSCAR N� DE REGISTRO
    pantalla.cursor(2,7);
    cout<<"Ingrese ID del producto a modificar: ";
    cin>>idProducto;
    pantalla.cursor (2,8);
    if(idProducto == 0){
       pantalla.cursor (2,23); cout <<"                                                       ";
        return;
    }
    else{
        producto=buscarPorCodigo(idProducto);
        posicion=posicionRegistro(idProducto);

        if (producto.getIdProducto()!= -1){

            leerDeDisco(posicion);
            producto.mostrar();
            pantalla.cursor(2,23);cout <<"                                               ";
            do{
                pantalla.cursor (2,23);
                cout<<"ESTA SEGURO/A DE CONTINUAR: (S/N):";
                cin>>Confirmacion;
                if(Confirmacion=='S' || Confirmacion=='s'){
                    system ("cls");
                    pantalla.cursor(30,2); cout<<"DELTAPOINT RESTO";
                    pantalla.dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
                    pantalla.dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
                    pantalla.cursor (2,6); cout<<"MENU AJUSTE - MODIFICAR PRODUCTO";
                    pantalla.cursor (2,7); cout<<"--------------------------------";
                    pantalla.cursor (2,8);
                    pantalla.cursor (2,16);
                    cout<<endl<<endl;

                    //CAMBIAR DATOS
                    pantalla.cursor(1,10);
                    cout<<" INGRESE EL NUEVO NOMBRE DEL PRODUCTO: ";
                    producto.cargarCadenas(Nombre, 49);
                    producto.setNombreProducto(Nombre);
                    pantalla.dibujarCuadro(0,0,79,24);
                    pantalla.cursor(1,11);
                    cout<<" INGRESE EL NUEVO PRECIO DE VENTA ($): ";
                    cin>>precio;
                    producto.setPrecioProducto(precio);

                    //SOBREESCRIBIR EL REGISTRO

                    if (sobreEscribirRegistro(producto, posicion)==1){
                        pantalla.cursor(2,22);
                        cout << GREEN;
                        cout<<"DATO MODIFICADO."<<endl<<endl;
                        cout << BLUE;
                        pantalla.cursor(2,23);
                        system("pause");
                        return;

                    }
                    else{
                        pantalla.cursor(2,22);
                        cout << RED;
                        cout<<"ERROR AL MODIFICAR REGISTRO."<<endl<<endl;
                        cout << BLUE;
                        pantalla.cursor(2,23);
                        system("pause");
                        return;

                    }
                }
                else{
                    if(Confirmacion=='N' || Confirmacion=='n'){
                        pantalla.cursor(2,23);
                        system("pause");
                        return;
                    }
                    else{
                       cout << RED;
                        pantalla.cursor (2,22); cout << "Opcion Incorrecta";
                        cout << BLUE;
                        pantalla.cursor(2,23);
                        system("pause");
                        pantalla.cursor (2,22); cout << "                       ";
                        pantalla.cursor (2,23); cout << "                                                ";
                    }
                }
            }while(Confirmacion!= 'S' || Confirmacion != 's' || Confirmacion != 'N' || Confirmacion != 'n');
        }
        else{
            pantalla.cursor (2,9);
            cout << RED;
            cout<<"No existe un producto con ese ID"<<endl;
            cout << BLUE;
            pantalla.cursor (2,23);
            system("pause");
        }
    }
}

void ArchivoProducto::bajaProducto(){

    //buscar
    int idProducto, posicion=0;
    Pantalla pantalla;
    Producto producto;


    pantalla.cursor (2,6); cout<<"MENU AJUSTE - ELIMINAR PRODUCTO";
    pantalla.cursor (2,7); cout<<"-------------------------------";
    pantalla.cursor (2,23); cout <<"ingrese 0(cero) para volver al menu anterior";
    pantalla.cursor(2,9);
    cout<<"INGRESE EL ID DEL PRODUCTO A ELIMINAR: ";
    cin>>idProducto;
    cout<<endl;
    //Volver al menu anterior
    if(idProducto == 0){
       pantalla.cursor (2,23); cout <<"                                                       "; // Limpia la leyenda "ingrese cero para volver
        return;
    }
    else{
        producto=buscarPorCodigo(idProducto);
        posicion=posicionRegistro(idProducto);

        if(producto.getIdProducto() == -1){
            pantalla.cursor(2,11);
            cout << RED;
            cout<<"No existe ID producto"<<endl<<endl;
            cout << BLUE;
            pantalla.cursor (2,23);
            system("pause");
            return;
        }

        producto=leerDeDisco(posicion);

        char Confirmacion;
        pantalla.cursor(2,10);
        cout<<"ESTA ACCION DARA DE BAJA EL SIGUIENTE PRODUCTO: ";
        producto.mostrar();
        pantalla.cursor(2,23);
        do{
            cout<<"ESTA SEGURO/A DE CONTINUAR: (S/N): ";
            cin>>Confirmacion;
            pantalla.cursor (2,17);
            if(Confirmacion=='S' || Confirmacion=='s'){
                producto.setEstado(false);
                //sobreescribir el registro es guardar
                if(sobreEscribirRegistro(producto, posicion)==1){
                    cout<<endl<<endl;
                    pantalla.cursor(2,18);
                    cout << GREEN;
                    cout<<"PRODUCTO DADO DE BAJA."<<endl<<endl;
                    cout << BLUE;
                    pantalla.cursor(2,23);
                    system("pause");
                    return;
                }
                else{
                    cout<<endl<<endl;
                    pantalla.cursor(2,18);
                    cout<<"ERROR AL ELIMINAR PRODUCTO."<<endl<<endl;
                    pantalla.cursor(3,20);
                    system("pause");
                    return;
                }

            }
            else{
                if(Confirmacion=='N' || Confirmacion=='n'){
                    pantalla.cursor(2,23);
                    system("pause");
                    return;
                }
                else{
                    cout << RED;
                    pantalla.cursor (2,22); cout << "Opcion Incorrecta";
                    cout << BLUE;
                    pantalla.cursor(2,23);
                    system("pause");
                    pantalla.cursor (2,22); cout << "                       ";
                    pantalla.cursor (2,23); cout << "                                                ";
                }
            }

        }while(Confirmacion!= 'S' || Confirmacion != 's' || Confirmacion != 'N' || Confirmacion != 'n');
    }
}

int ArchivoProducto::sobreEscribirRegistro(Producto producto, int posicion){

    FILE *p;

	p=fopen(_Nombre,"rb+");

	if(p==NULL){
		return -1;
	}

    fseek(p, posicion*sizeof (Producto), 0); //usamos fseek para llegar al registro que necesito pisar con la
    int valor=fwrite(&producto, sizeof producto, 1,p); //sobre escribo
    fclose(p);

    return valor;
}


Producto ArchivoProducto::buscarPorCodigo(int idProducto){

    Producto producto;
    Pantalla pantalla;
    bool productoEncontrado=false;

    for (int x=0; x<cantidadEnArchivo();x++){
        producto=leerDeDisco(x);
            if(producto.getIdProducto()==idProducto && producto.getEstado() == true){
            productoEncontrado=true;
            return producto;
		}
    }

    if (productoEncontrado==false){
        producto.setIdProducto(-1);
        producto.setPrecioProducto(0);
        pantalla.cursor(2,16);
        producto.setNombreProducto("PRODUCTO NO ENCONTRADO");
        return producto;
    }

    return producto;
}


int ArchivoProducto::posicionRegistro(int idProducto){

    Producto producto;
    FILE *pArchivo;

    int posicion=0;

	pArchivo=fopen(_Nombre,"rb");

	if(pArchivo==NULL){
		return -2; //si no encuentra el archivo nos devuelve un n�mero de id inv�lido
	}

    while(fread(&producto, sizeof producto, 1,pArchivo)==1){

        if(producto.getIdProducto()== idProducto && producto.getEstado()==true){
            fclose(pArchivo);
            return posicion; //muestra el n�mero de archivo
        }

        posicion++; //incrementa la posici�n por leer el archivo
    }

    fclose(pArchivo);
    return -1; //retorna -1 cuando ya no hay archivos
}

void ArchivoProducto::Ordenar(){
    Producto producto, productoAuxiliar, productoSiguiente;
    ArchivoProducto archivoProducto("productos.dat");
    int maximo = 0;

    maximo = archivoProducto.cantidadEnArchivo();

    for (int x=0; x<maximo; x++){
        for (int i=0; i<maximo-1; i++){
            producto=archivoProducto.leerDeDisco(i);
            productoSiguiente=archivoProducto.leerDeDisco(i+1);

            if (producto.getIdProducto()>productoSiguiente.getIdProducto()){
                productoAuxiliar=productoSiguiente;

                archivoProducto.sobreEscribirRegistro(producto, i+1);

                archivoProducto.sobreEscribirRegistro(productoAuxiliar, i);
            }
        }
    }



}

void ArchivoProducto::MensajeError(){
    Pantalla pantalla;
    system ("cls");
    pantalla.cursor (4,5);
    pantalla.estiloMenu();

    cout << RED;
    pantalla.cursor(15,15);
    cout << "El archivo de - Ventas - no se pudo abrir." << endl;
    pantalla.cursor(15,16);
    cout << "Comuniquese con el area de sistemas" << endl;
    pantalla.cursor(15,20);
    cout << BLUE;
    exit(20);
}

