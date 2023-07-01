#include<iostream>

using namespace std;

#include "Transaccion.h"
#include "Producto.h"

Transaccion::Transaccion(){
}

Transaccion::Transaccion(int idOperacion, int idProducto, int cantidad, float precio, char tipo, int idMesa){
    _idTransaccion = generarCodigoTransaccion() + _contador;
    _idOperacionAsociada = idOperacion;
    _idProducto = idProducto;
    _cantidad = cantidad;
    _precio = precio;
    if(setTipo(tipo)) cout<<"Tipo de transaccion [compra o venta] INDEFINIDO"<<endl;
    _estado = 1;
    _idMesa= idMesa;

    _contador++;
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

int Transaccion::grabarEnDisco(){
    FILE *p;
    p=fopen("transaccion.dat", "ab");
    if(p==NULL) return -1;
    int grabo=fwrite(this, sizeof(Transaccion), 1, p);
    fclose(p);
    return grabo;
}

int Transaccion::grabarEnDiscoPorPosicion(int posicion){
	FILE *p;
	p = fopen("transaccion.dat", "rb+");
	if(p==NULL) return false;
	fseek(p, sizeof(Transaccion)*posicion, 0);
	int escribio = fwrite(this, sizeof(Transaccion), 1, 0);
	fclose(p);
	return escribio;
}

int Transaccion::leerDeDisco(int pos){
    FILE *p;
    p=fopen("transaccion.dat","rb");
    if(p==NULL) return -1;
    fseek(p,pos * sizeof(Transaccion), SEEK_SET);
    int leyo = fread(this, sizeof(Transaccion), 1, p);
    fclose(p);
    return leyo;
}


int Transaccion::generarCodigoTransaccion(){
  return cantidadTransacciones() + 1;
}

int Transaccion::getLastIdTransaction(){
    FILE *p;
    p=fopen("transaccion.dat","rb+");
    if(p==NULL) return 0;
    fseek(p,sizeof(Transaccion), SEEK_END);
    int lecturas = fread(this,sizeof(Transaccion), 1, p);
    fclose(p);
    return lecturas;
}

int Transaccion::cantidadTransacciones(){
    FILE* pFile;
    int cantidad = 0;
    pFile = fopen("transaccion.dat", "rb");
    if (pFile == nullptr) return 0;
    fseek(pFile, 0, SEEK_END);
    cantidad = ftell(pFile) / sizeof(Transaccion);
    fclose(pFile);
    return cantidad;
}


void Transaccion::mostrar(){
    Producto productoAux;

    cout<<_idTransaccion;
    cout<<"\t\t"<<_idOperacionAsociada;
    cout<<"\t"<<_idProducto;
    productoAux = buscarPorCodigo(_idProducto);
    cout<<"\t\t"<<productoAux.getNombreProducto();
    cout<<"\t\t\t"<<_cantidad;
    cout<<"\t"<<_precio;
    cout<<"\t"<<_estado<<endl;
}
