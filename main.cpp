#include "iostream"

using namespace std;
#include "Menu.h"
#define XSCREEN 78

#include "ArchivoEmpleado.h"
#include "Empleado.h"
#include "ArchivoProducto.h"
#include "Producto.h"

int main(){
    Menu menu;
    ArchivoEmpleado archivoEmpleado("empleados.dat");
    Empleado empleado;
    ArchivoProducto archivoProducto("productos.dat");
    Producto producto;

    //empleado.cargarEmpleado();
    //archivoEmpleado.grabarEnDisco(empleado);

    //producto = archivoProducto.leerDeDisco(0);
    //producto.mostrar();
    menu.menuIdVendedor();

    return 0;
}
