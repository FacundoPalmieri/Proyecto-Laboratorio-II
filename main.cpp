#include "iostream"

using namespace std;
#include "Menu.h"
#define XSCREEN 78

#include "ArchivoProducto.h"
#include "Producto.h"

int main(){
    Menu menu;
    menu.menuIdVendedor();

    ArchivoProducto archivoProducto("productos.dat");
    Producto producto;


    cout<<"cantidad en archivo: "<<archivoProducto.cantidadEnArchivo();

    return 0;
}
