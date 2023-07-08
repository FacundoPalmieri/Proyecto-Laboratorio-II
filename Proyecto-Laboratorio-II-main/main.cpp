#include "iostream"

using namespace std;
#include "Menu.h"
#define XSCREEN 78

#include "ArchivoTransaccion.h"
#include "ArchivoProducto.h"
#include "Transaccion.h"
#include "Producto.h"

int main(){

    Menu menu;

    menu.menuIdVendedor();


/*
    Producto producto;
    ArchivoProducto archivoProducto("productos.dat");

    for(int x=0; x<archivoProducto.cantidadEnArchivo(); x++){
        producto=archivoProducto.leerDeDisco(x);
        if (producto.getEstado()==true){
            cout<<"ID: "<<producto.getIdProducto()<<endl;
            cout<<"NOMBRE: "<<producto.getPrecioProducto()<<endl;
            cout<<"PRECIO: "<<producto.getNombreProducto()<<endl;
            cout<<"--------------------------"<<endl;
        }
    }

    int maximo=0;
    Producto producto;
    ArchivoProducto archivoProducto("productos.dat");

    cout<<"CANTIDAD EN ARCHIVO PRODUCTO: "<<archivoProducto.cantidadEnArchivo()<<endl;

    for (int x = 0; x < archivoProducto.cantidadEnArchivo(); x++) {
        producto = archivoProducto.leerDeDisco(x);
        if (producto.getIdProducto() > maximo && producto.getEstado()==true) {
            maximo = producto.getIdProducto();
        }
    }

    cout<<"EL INDICE MAXIMO PARA EL VECTOR: "<<maximo<<endl;

    int* VecIdProductos = new int[maximo];

    if (VecIdProductos != nullptr) {

        // Inicializar el arreglo con valores inválidos
        for (int i = 0; i <maximo; i++) {
            VecIdProductos[i] = 0;
        }

        // Asignar al vector el ID de cada producto, ya ordenado
        for (int i = 0; i < archivoProducto.cantidadEnArchivo(); i++) {
            producto = archivoProducto.leerDeDisco(i);
            VecIdProductos[producto.getIdProducto()-1] = producto.getIdProducto();
        }

        for (int x = 0; x < maximo; x++) {

            for (int i = 0; i < archivoProducto.cantidadEnArchivo(); i++) {
                producto = archivoProducto.leerDeDisco(i);

                if (producto.getIdProducto() == VecIdProductos[x] && producto.getEstado() == true) {


                    cout << producto.getIdProducto()<<endl;

                    cout << producto.getNombreProducto()<<endl;

                    cout << "$" << producto.getPrecioProducto()<<endl;

                }
            }
        }

        delete[] VecIdProductos;
    } else {
    cout << "NO SE PUDO ASIGNAR MEMORIA" << endl;
    }
*/
    return 0;
}
