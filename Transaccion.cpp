#include<iostream>

using namespace std;

#include "Transaccion.h"
#include "Producto.h"
#include "ArchivoProducto.h"
#include "Pantalla.h"
#include "ArchivoTransaccion.h"

Transaccion::Transaccion(){
}

Transaccion::Transaccion(int idOperacion, int idProducto, int cantidad, float precio, char tipo, int idMesa){
    _idTransaccion = generarCodigoTransaccion();
    _idOperacionAsociada = idOperacion;
    _idProducto = idProducto;
    _cantidad = cantidad;
    _precio = precio;
    if(setTipo(tipo)) cout<<"Tipo de transaccion [compra o venta] INDEFINIDO"<<endl;
    _estado = 2; // 0 - cerrada / 1 - Borrador / 2 - Confirmada
    _idMesa= idMesa;
}

int Transaccion::getIdProducto(){
    return _idProducto;
}

int Transaccion::getCantidad(){
    return _cantidad;
}

int Transaccion::getIdOperacionAsociada(){
    return _idOperacionAsociada;
}


float Transaccion::getPrecio(){
    return _precio;
}

int Transaccion::getIdMesa(){
    return _idMesa;
}

int Transaccion::getEstado(){
    return _estado;
}

void Transaccion::setIdProducto(int IdProducto){
    _idOperacionAsociada=IdProducto;

}

void Transaccion::setCantidad(int cantidad){
    _cantidad=cantidad;
}

void Transaccion::setPrecio(int precio){
    _precio=precio;
}

void Transaccion::setEstado(int estado){
    _estado = estado;
}


int Transaccion::setTipo(char tipo){
    if((tipo='v') || (tipo='V')){
        _esVenta = true;
        _esCompra = false;
        return 0;
    }
    else if((tipo='c') || (tipo='C')){
        _esVenta = false;
        _esCompra = true;
        return 0;
    }
    else{
        _esVenta = false;
        _esCompra = false;
        return 1;
    }
}


bool Transaccion::esVenta(){
    return esVenta();
}


void Transaccion::confirmarTransaccion(){
    _estado = 2;
}

int Transaccion::generarCodigoTransaccion(){

    ArchivoTransaccion archivoTransaccion("transaccion.dat");

    return archivoTransaccion.cantidadTransacciones()+1;
}


void Transaccion::mostrar(){
    Producto producto;
    ArchivoProducto archivoProducto("productos.dat");

    cout<<_idTransaccion;
    cout<<"\t\t"<<_idOperacionAsociada;
    cout<<"\t"<<_idProducto;
    producto = archivoProducto.buscarPorCodigo(_idProducto);
    cout<<"\t\t"<<producto.getNombreProducto();
    cout<<"\t\t\t"<<_cantidad;
    cout<<"\t"<<_precio;
    cout<<"\t"<<_estado<<endl;
}

float Transaccion::cerrarMesa(int mesa){

    Transaccion transaccion;
    ArchivoTransaccion archivoTransaccion("transaccion.dat");

    Pantalla pantalla;

    float total=0;

    for (int x=0; x<archivoTransaccion.cantidadTransacciones();x++){ //RECORRE ARCHIVO TRANSACCIONES

        transaccion=archivoTransaccion.leerDeDisco(x);

        if(transaccion.getIdMesa() == mesa && transaccion.getEstado()!=0) //FILTRAMOS LAS VENTAS QUE COINCIDEN CON EL N° DE MESA INGRESADO
        {
            total+=transaccion.getPrecio();//ANTES DE CERRAR MESA DE ESA TRANSACCIÓN ACUMULA EL IMPORTE
            transaccion.setEstado(0); //CAMBIAMOS EL ESTADO PARA CERRAR MESA
            if(archivoTransaccion.sobreEscribirRegistro(x, transaccion)==0)//SOBREESCRIBO LA TRANSACCIÓN CON EL ESTADO SETEADO
            {


            }


        }
    }
    pantalla.dimensiones (4,13);
    return total;
}
