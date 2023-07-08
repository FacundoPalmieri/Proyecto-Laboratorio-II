#include <iostream>

using namespace std;

#include "Venta.h"
#include "Producto.h"
#include "Empleado.h"
#include "Mesa.h"
#include "ArchivoVenta.h"
#include "ArchivoProducto.h"
#include "ArchivoTransaccion.h"


Venta::Venta(){
    _IdVenta = generarCodigoVenta();
    _consumoTotal = 0;
    _idVendedor = -1;
    _idMesa = -1;
    _estado = 1;        // se crea en estado BORRADOR

}

Venta::Venta(int vendedor, int mesa)
{
    _IdVenta = generarCodigoVenta();
    _consumoTotal = 0;
    _idVendedor = vendedor;
    _idMesa = mesa;
    _estado = 1;        // se crea en estado BORRADOR
}

int Venta::getIDventa()
{
    return _IdVenta;
}

int Venta::getIdMesa(){
    return _idMesa;
}

float Venta::getConsumoTotal()
{
    return _consumoTotal;
}

Fecha Venta::getFecha(){
    return _fecha;
}

int Venta::getIdVendedor(){
    return _idVendedor;
}

void Venta::cargarVenta()
{
    int idMesa;
    cout<<"INGRESE NUMERO DE MESA: "<<endl;
    cin>>idMesa;

}

void Venta::mostrar()
{
    cout<<"\n ID DE VENTA: "<<_IdVenta<<endl;
    cout<<"FECHA: "; _fecha.mostrarFecha(); cout<<endl;
    cout<<"CONSUMO TOTAL: $"<<_consumoTotal<<endl;
    cout<<"NUMERO DE MESA: "<<_idMesa<<endl;
    cout<<"ESTADO: "<<_estado<<endl;
}

void Venta::setVendedor(int idVendedor){
    _idVendedor = idVendedor;
}

void Venta::setMesa(int mesa){
    _idMesa = mesa;
}

void Venta::setConsumoTotal(float total){
    _consumoTotal = total;
}

bool Venta::confirmarVenta(){

    ArchivoTransaccion archivoTransaccion("transaccion.dat");
    Transaccion transaccion;

    for(int x=0; x<archivoTransaccion.cantidadTransacciones();x++){
        transaccion=archivoTransaccion.leerDeDisco(x);

        if(transaccion.esVenta()==true){
            if(transaccion.getIdOperacionAsociada() == getIDventa()){
                transaccion.confirmarTransaccion();
                transaccion.mostrar();
                archivoTransaccion.grabarEnDiscoPorPosicion(x, transaccion);
            }
        }
    }
    _estado = 2;     //seteo como confirmado el estado de la venta en general

    return true;
}


int Venta::generarCodigoVenta(){
    ArchivoVenta archivoVenta("venta.dat");
    int cantidadVentas=archivoVenta.cantidadVentas();
    return cantidadVentas;
}

int Venta::getLastIdVenta(){
    FILE *p;
    p=fopen("venta.dat","rb+");
    if(p==NULL) return 0;
    fseek(p, sizeof(Venta), SEEK_END);
    int lecturas = fread(this, sizeof(Venta), 1, p);
    fclose(p);
    return lecturas;
}


int Venta::agregarProductoALaVenta(int idProducto, int cantidad){

    Producto producto; //SE UTILIZA PARA BUSCAR EL ID DEL PRODUCTO QUE RECIBIMOS POR PARÁMETRO
    ArchivoProducto archivoProducto("productos.dat");
    producto = archivoProducto.buscarPorCodigo(idProducto);

    ArchivoTransaccion archivoTransaccion("transaccion.dat");

    if(producto.getIdProducto() != -1){
        //CREAMOS UNA TRANSACCION AUX, POR PARÁMETROS, CON LOS DATOS DE LA VENTA Y EL PRODUCTO
        Transaccion transaccion(getIDventa(), idProducto, cantidad, producto.getPrecioProducto(),'V', _idMesa);

        //GRABAMOS EN ARCHIVO TRANSACCIÓN

        archivoTransaccion.grabarEnDisco(transaccion);

        //SUMAMOS EL IMPORTE TOTAL

        _consumoTotal+=(producto.getPrecioProducto() * cantidad);

        return 0;
    }
    else{
        return -1;
    }
}
