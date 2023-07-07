#include <iostream>
#include <cstring>
using namespace std;

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

void Producto::cargar()
{
    Producto producto;
    Pantalla pantalla;

    ArchivoProducto archivoProducto("productos.dat");


    int CantidadRegistros = archivoProducto.cantidadEnArchivo();

    cout<<"INGRESE ID DE PRODUCTO: ";
    cin>>_idProducto;


    for(int x = 0; x < CantidadRegistros; x++){
        producto=archivoProducto.leerDeDisco(x);

        if(producto.getEstado() == true && _idProducto == producto.getIdProducto()){
           pantalla.dimensiones(1,13);
            cout << "El producto ya existe.";
            return;
        }
    }
    pantalla.dibujarCuadro(0,0,79,24);
    pantalla.dimensiones(1,13);
    cout<<" INGRESE NOMBRE DEL PRODUCTO: ";
    cargarCadenas(_nombreProducto, 49);
    pantalla.dibujarCuadro(0,0,79,24);
    pantalla.dimensiones(1,14);
    cout<<" INGRESE PRECIO DE VENTA ($): ";
    cin>>_precioProducto;
    pantalla.dimensiones(1,15);
    cout<<" PRODUCTO AGREGADO.";
}

void Producto::mostrar()
{
    Pantalla pantalla;

    if(_estado==true){
       pantalla.dimensiones(2,11);
        cout<<"ID DE PRODUCTO: "<<_idProducto<<endl;
       pantalla.dimensiones(2,12);
        cout<<"NOMBRE DEL PRODUCTO: "<<_nombreProducto<<endl;
       pantalla.dimensiones(2,13);
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


