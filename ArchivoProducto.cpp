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


    if (p == nullptr) return 0;

    fseek(p, 0, SEEK_END);

    int cantidad = ftell(p) / sizeof(Producto);

    fclose(p);

    return cantidad;
}

void ArchivoProducto::modificarRegistro(){

    system("cls");

    Pantalla pantalla;
    char Confirmacion, Nombre[50];
    int idProducto, posicion;
    float precio;

    pantalla.dimensiones(30,2); cout<<"DELTAPOINT RESTO";
    pantalla.dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
    pantalla.dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO

    //BUSCAR N° DE REGISTRO
    pantalla.dimensiones(2,5);
    cout<<"Ingrese ID del producto a modificar: ";
    cin>>idProducto;
    pantalla.dimensiones (2,7); cout<<"------------------";

    Producto producto;
    producto=buscarPorCodigo(idProducto);
    posicion=posicionRegistro(idProducto);

    if (producto.getIdProducto()!= -1){

        pantalla.dimensiones(2,9);
        cout<<"PRODUCTO A MODIFICAR: "<<endl;

        leerDeDisco(posicion);
        producto.mostrar();
        pantalla.dimensiones(2,14);
        cout<<"ESTA SEGURO/A DE CONTINUAR: (S/N): ";
        cin>>Confirmacion;
        pantalla.dimensiones (2,15); cout<<"------------------";
        cout<<endl<<endl;
        if(Confirmacion=='S' || Confirmacion=='s'){

            //CAMBIAR DATOS
            pantalla.dimensiones(1,18);
            cout<<" INGRESE NOMBRE DEL PRODUCTO: ";
            producto.cargarCadenas(Nombre, 49);
            producto.setNombreProducto(Nombre);
            pantalla.dibujarCuadro(0,0,79,24);
            pantalla.dimensiones(1,20);
            cout<<" INGRESE PRECIO DE VENTA ($): ";
            cin>>precio;
            producto.setPrecioProducto(precio);

            //SOBREESCRIBIR EL REGISTRO

            if (sobreEscribirRegistro(producto, posicion)==1){
                pantalla.dimensiones(2,22);
                cout<<"DATO MODIFICADO."<<endl<<endl;
                pantalla.dimensiones(2,23);
                system("pause");
            }
            else{
                pantalla.dimensiones(2,22);
                cout<<"ERROR AL MODIFICAR REGISTRO."<<endl<<endl;
                pantalla.dimensiones(2,23);
                system("pause");
            }
        }
        else{
           pantalla.dimensiones(2,18);
            system("pause");
        }
    }
    else{
       pantalla.dimensiones (2,9);
        cout<<"No existe un producto con ese ID"<<endl;
       pantalla.dimensiones (2,11);
        system("pause");
    }
}

void ArchivoProducto::bajaProducto(){

    //buscar
    int idProducto, posicion=0;
    Pantalla pantalla;

   pantalla.dimensiones(2,9);
    cout<<"INGRESE EL ID DEL PRODUCTO A ELIMINAR: ";
    cin>>idProducto;
    cout<<endl;


    Producto producto;
    producto=buscarPorCodigo(idProducto);
    posicion=posicionRegistro(idProducto);

    if(producto.getIdProducto() == -1){
        pantalla.dimensiones(2,11);
        cout<<"NO EXISTE ESE ID DE PRODUCTO"<<endl<<endl;
        pantalla.dimensiones (2,13); cout<<"------------------";
        pantalla.dimensiones (2,15);
        system("pause");
    }

    producto=leerDeDisco(posicion);

    char Confirmacion;
    pantalla.dimensiones(2,10);
    cout<<"ESTA ACCION DARA DE BAJA EL SIGUIENTE PRODUCTO: "<<endl<<endl;
    pantalla.dimensiones(2,12);
    producto.mostrar();
    pantalla.dimensiones(2,16);
    cout<<"ESTA SEGURO/A DE CONTINUAR: (S/N): ";
    cin>>Confirmacion;
    pantalla.dimensiones (2,17); cout<<"------------------";

    if(Confirmacion=='S' || Confirmacion=='s'){
        //cambiar estado
        producto.setEstado(false);

        //sobreescribir el registro es guardar
        if(sobreEscribirRegistro(producto, posicion)==1){
            cout<<endl<<endl;
            pantalla.dimensiones(2,18);
            cout<<"PRODUCTO DADO DE BAJA."<<endl<<endl;
            pantalla.dimensiones(3,20);
            system("pause");
        }
        else{
            cout<<endl<<endl;
            pantalla.dimensiones(2,18);
            cout<<"ERROR AL ELIMINAR PRODUCTO."<<endl<<endl;
            pantalla.dimensiones(3,20);
            system("pause");
        }

    }
    else{
       pantalla.dimensiones(3,20);
        system("pause");
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
            if(producto.getIdProducto()==idProducto){
            productoEncontrado=true;
            return producto;
		}
    }

    if (productoEncontrado==false){
        producto.setIdProducto(-1);
        producto.setPrecioProducto(0);
        pantalla.dimensiones(2,16);
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
		return -2; //si no encuentra el archivo nos devuelve un número de id inválido
	}

    while(fread(&producto, sizeof producto, 1,pArchivo)==1){

        if(producto.getIdProducto()== idProducto && producto.getEstado()==true){
            fclose(pArchivo);
            return posicion; //muestra el número de archivo
        }

        posicion++; //incrementa la posición por leer el archivo
    }

    fclose(pArchivo);
    return -1; //retorna -1 cuando ya no hay archivos
}

void ArchivoProducto::MensajeError(){
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
    exit(20);
}

