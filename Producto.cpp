#include <iostream>
#include <cstring>
using namespace std;
#include "colors.h"
#include "Producto.h"
#include "Menu.h"
#include "Pantalla.h"
#include "ArchivoProducto.h"


Producto::Producto()
{
}

int Producto::getIdProducto()
{
    return _idProducto;
}

const char* Producto::getNombreProducto()
{
    return _nombreProducto;
}

float Producto::getPrecioProducto()
{
    return _precioProducto;
}

bool Producto::getEstado()
{
    return _estado;

}

void Producto::setIdProducto(int idProducto)
{
    _idProducto=idProducto;
}

void Producto::setNombreProducto(const char* nombreProducto)
{
    strcpy(_nombreProducto, nombreProducto);
}

void Producto::setPrecioProducto(float precioProducto)
{
    _precioProducto=precioProducto;
}


void Producto::setEstado(bool estado)
{
    _estado = estado;

}

int Producto::cargar()
{
    Producto producto;
    Pantalla pantalla;

    ArchivoProducto archivoProducto("productos.dat");
    int CantidadRegistros = archivoProducto.cantidadEnArchivo();


    pantalla.cursor(30,2); cout<<"DELTAPOINT RESTO";


    pantalla.cursor (2,6);  cout<<"MENU AJUSTE - CARGAR PRODUCTO";
    pantalla.cursor (2,7);  cout<<"-----------------------------";
    pantalla.cursor (2,23); cout <<"ingrese 0(cero) para volver al menu anterior";

    pantalla.cursor (2,8);
    cout<<"INGRESE ID DE PRODUCTO: ";
    cin>>_idProducto;


    if(_idProducto == 0){
       pantalla.cursor (2,23); cout <<"                                                       "; // Limpia la leyenda "ingrese cero para volver
        return -1;
    }
    else{

        for(int x = 0; x < CantidadRegistros; x++){
            producto=archivoProducto.leerDeDisco(x);

            if(producto.getEstado() == true && _idProducto == producto.getIdProducto()){
               pantalla.cursor(2,13);
               cout << RED;
               cout << " El producto ya existe.";
               pantalla.cursor (2,23); cout <<"                                                       "; // Limpia la leyenda "ingrese cero para volver
               cout << BLUE;
               return -1;
            }
        }

        pantalla.dibujarCuadro(0,0,79,24);
        pantalla.cursor(1,9);
        cout<<" INGRESE NOMBRE DEL PRODUCTO: ";
        cargarCadenas(_nombreProducto, 49);
        pantalla.dibujarCuadro(0,0,79,24);
        pantalla.cursor(1,10);
        cout<<" INGRESE PRECIO DE VENTA ($): ";
        cin>>_precioProducto;
        pantalla.cursor(1,14);
        cout << GREEN;
        cout<<" PRODUCTO AGREGADO.";
        cout << BLUE;
        pantalla.cursor (2,23); cout <<"                                                       "; // Limpia la leyenda "ingrese cero para volver
        _estado = true;
        return 0;
    }
}

void Producto::mostrar()
{
    Pantalla pantalla;

    if(_estado==true){
        pantalla.cursor(2,12);
        cout<<"ID DE PRODUCTO: "<<_idProducto<<endl;
        pantalla.cursor(2,13);
        cout<<"NOMBRE DEL PRODUCTO: "<<_nombreProducto<<endl;
        pantalla.cursor(2,14);
        cout<<"PRECIO: $"<<_precioProducto<<endl;
    }
}


void Producto::cargarCadenas(char *pal, int tam){
    int i;
    fflush(stdin);
    for(i=0; i<tam; i++)
    {
        pal[i]=cin.get();
        if(pal[i]=='\n') break;
    }
    pal[i]='\0';
    fflush(stdin);
}


