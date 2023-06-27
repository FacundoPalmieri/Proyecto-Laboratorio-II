#include <iostream>
#include <list>


using namespace std;

#include "Venta.h"
#include "Producto.h"
#include "Empleado.h"
#include "Mesa.h"

list<Transaccion> _listaProductosVenta;
list<Transaccion>::iterator it;

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

Venta::~Venta(){

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
    int idMesaAux;
    cout<<"INGRESE NUMERO DE MESA: "<<endl;
    cin>>idMesaAux;

}

void Venta::mostrarVenta()
{
    Empleado empleado;

    cout<<"\nID DE VENTA: "<<_IdVenta<<endl;
    cout<<"FECHA: "; _fecha.mostrarFecha(); cout<<endl;
    cout<<"CONSUMO TOTAL: $"<<_consumoTotal<<endl;
    cout<<"NUMERO DE MESA: "<<_idMesa<<endl;
    cout<<"ESTADO: "<<_estado<<endl;
    cout<<"\nID. TRASN | COD. OP | COD. PRODUCTO | \tPRODUCTO\t | CANTIDAD | PRECIO | ESTADO"<<endl;
    for(Transaccion elem: _listaProductosVenta) elem.mostrar();

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

    Transaccion transaccionAux;
    int pos=0;

    while(transaccionAux.leerDeDisco(pos)){
        if(transaccionAux.esVenta()==true){
            if(transaccionAux.getIdOperacionAsociada() == getIDventa()){
                transaccionAux.confirmarTransaccion();
                transaccionAux.mostrar();
                transaccionAux.grabarEnDiscoPorPosicion(pos);
            }
        }
        pos++;
    }
    _estado = 2;                                        //seteo como confirmado el estado de la venta en general

    return true;
}

int Venta::grabarEnDisco(){
    for(Transaccion elem: _listaProductosVenta){        //graba cada elemento de la lista como una Transaccion en el archivo
        elem.grabarEnDisco();
    }
    FILE *p;
    p=fopen("venta.dat", "ab");
    if(p==NULL) return -1;
    int grabo=fwrite(this, sizeof(Venta),1, p);
    fclose(p);
    return grabo;
}

int Venta::leerDeDisco(int pos){
    FILE *p;
    p=fopen("venta.dat","rb");
    if(p==NULL) return -1;
    fseek(p,pos * sizeof(Venta), SEEK_SET);
    int leyo = fread(this, sizeof(Venta), 1, p);
    fclose(p);

    _listaProductosVenta.clear();

    Transaccion transaccionAux;
    int cantidad = transaccionAux.cantidadTransacciones();
    for(int i=0; i<cantidad; i++){
        transaccionAux.leerDeDisco(i);
        _listaProductosVenta.push_back(transaccionAux);
    }
    return leyo;
}

int Venta::generarCodigoVenta(){
  return cantidadVentas() + 1;
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

int Venta::cantidadVentas(){
    FILE* pFile;
    int cantidad = 0;
    pFile = fopen("venta.dat", "rb");
    if (pFile == nullptr) {
        return 0;
    }
    fseek(pFile, 0, SEEK_END);
    cantidad = ftell(pFile) / sizeof(Venta);
    fclose(pFile);
    return cantidad;
}

int Venta::agregarProductoALaVenta(int idProducto, int cantidad){
    Producto productoAux;

    productoAux = buscarPorCodigo(idProducto);

    Transaccion transaccionAux(getIDventa(), idProducto, cantidad, productoAux.getPrecioProducto(),'V');


   _listaProductosVenta.push_back(transaccionAux);

    _consumoTotal+=(productoAux.getPrecioProducto() * cantidad);


    return 0;
}
