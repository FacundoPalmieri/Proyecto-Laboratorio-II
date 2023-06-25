#include <iostream>
#include<stdlib.h>
#include<cstring>
using namespace std;

#include "Producto.h"
#include "Menu.h"



Producto buscarPorCodigo(int codigo){

    Producto producto;

    int pos = 0;
	while(producto.leerDeDisco(pos++)>0){
		if(producto.getIdProducto()==codigo){
            return producto;
		}
	}
	producto.setIdProducto(-1);
	producto.setPrecioProducto(0);
	producto.setNombreProducto("PRODUCTO NO ENCONTRADO");
	return producto;
}

/// - - - - - - - PRODUCTOS::METODOS - - - - - - - -

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
    int CantidadRegistros = 0;
    cout<<"INGRESE ID DE PRODUCTO: ";
    cin>>_idProducto;
    CantidadRegistros = producto.cantidadEnArchivo();
    for(int x = 0; x < CantidadRegistros; x++){
        producto.leerDeDisco(x);
        if(producto.getEstado() == true && _idProducto == producto.getIdProducto()){
          cout << "\033[31m El producto ya existe. \033[0m";
          return;
        }

    }
    pantalla.dibujarCuadro(0,0,79,24);
    pantalla.gotoxy(1,13);
    cout<<" INGRESE NOMBRE DEL PRODUCTO: ";
    cargarCadenas(_nombreProducto, 49);
    pantalla.dibujarCuadro(0,0,79,24);
    pantalla.gotoxy(1,14);
    cout<<" INGRESE PRECIO DE VENTA ($): ";
    cin>>_precioProducto;
}

void Producto::mostrar()
{
    Pantalla pantalla;

    if(_estado==true){
        pantalla.gotoxy(2,11);
        cout<<"ID DE PRODUCTO: "<<_idProducto<<endl;
        pantalla.gotoxy(2,12);
        cout<<"NOMBRE DEL PRODUCTO: "<<_nombreProducto<<endl;
        pantalla.gotoxy(2,13);
        cout<<"PRECIO: $"<<_precioProducto<<endl;
    }
}

void Producto::grabarEnDisco(Producto producto){
    FILE *pFile;
    pFile=fopen("productos.dat", "ab");
    if(pFile==NULL) {cout<<"NO SE PUDO ABRIR EL ARCHIVO.";}
    fwrite(&producto, sizeof(Producto),1, pFile);
    fclose(pFile);
}

int Producto::leerDeDisco(int pos){
    FILE *pFile;
    pFile=fopen("productos.dat","rb");
    if(pFile==NULL) return -1;
    fseek(pFile,pos*sizeof(Producto), SEEK_SET);
    int lecturas = fread(this, sizeof(Producto), 1, pFile);
    fclose(pFile);
    return lecturas;
}

int Producto::cantidadEnArchivo(){
    FILE* pFile;
    int cantidad = 0;
    pFile = fopen("productos.dat", "rb");
    if (pFile == nullptr) return -1;
    fseek(pFile, 0, SEEK_END);
    cantidad = ftell(pFile) / sizeof(Producto);
    fclose(pFile);
    return cantidad;
}

int Producto::buscarDato(int idProducto){

    Producto producto;
    FILE *pArchivo;

    int posicion=0;

	pArchivo=fopen("productos.dat","rb");

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

void Producto::modificarRegistro(){
    system("cls");

    Pantalla pantalla;
    char Confirmacion;
    int idProducto, posicion;

    pantalla.gotoxy(30,2); cout<<"DELTAPOINT RESTO";
    pantalla.dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
    pantalla.dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO

    //BUSCAR N° DE REGISTRO
    pantalla.gotoxy(2,5);
    cout<<"Ingrese ID del producto a modificar: ";
    cin>>idProducto;
    pantalla.gotoxy (2,7); cout<<"------------------";

    posicion=buscarDato(idProducto);

    if (posicion== -1){
        cout<<"No existe un producto con ese ID"<<endl;
    }

    //LEER EL REGISTRO, Y GUARDARLO EN UN REGISTRO AUXILIAR
    Producto producto;
    producto.leerDeDisco(posicion);

    pantalla.gotoxy(2,9);
    cout<<"PRODUCTO A MODIFICAR: "<<endl;

    producto.mostrar();
    pantalla.gotoxy(2,14);
    cout<<"ESTA SEGURO/A DE CONTINUAR: (S/N): ";
    cin>>Confirmacion;
    pantalla.gotoxy (2,15); cout<<"------------------";
    cout<<endl<<endl;
    if(Confirmacion=='S' || Confirmacion=='s'){

        //CAMBIAR DATOS
        pantalla.gotoxy(1,18);
        cout<<" INGRESE NOMBRE DEL PRODUCTO: ";
        cargarCadenas(_nombreProducto, 49);
        producto.setNombreProducto(_nombreProducto);
        pantalla.dibujarCuadro(0,0,79,24);
        pantalla.gotoxy(1,20);
        cout<<" INGRESE PRECIO DE VENTA ($): ";
        cin>>_precioProducto;
        producto.setPrecioProducto(_precioProducto);

        //SOBREESCRIBIR EL REGISTRO

        sobreEscribirRegistro(producto, posicion);
        pantalla.gotoxy(2,22);
        cout<<"DATO MODIFICADO."<<endl<<endl;
        pantalla.gotoxy(2,23);
        system("pause");
    }
    else{
        pantalla.gotoxy (2,16); cout<<"------------------";
        pantalla.gotoxy(2,18);
        system("pause");
    }
}

int Producto::bajaProducto(){

    ///buscar
    int idProducto, posicion=0;
    Pantalla pantalla;

    pantalla.gotoxy(2,9);
    cout<<"INGRESE EL ID DEL PRODUCTO A ELIMINAR: ";
    cin>>idProducto;
    cout<<endl;

    posicion=buscarDato(idProducto);
    if(posicion== -1){
        pantalla.gotoxy(2,11);
        cout<<"NO EXISTE ESE ID DE PRODUCTO"<<endl<<endl;
        pantalla.gotoxy (2,13); cout<<"------------------";
        pantalla.gotoxy (2,15);
        system("pause");
        return -1;
    }

    //leer
    Producto producto;
    producto.leerDeDisco(posicion);

    char Confirmacion;
    pantalla.gotoxy(2,10);
    cout<<"ESTA ACCION DARA DE BAJA EL SIGUIENTE PRODUCTO: "<<endl<<endl;
    pantalla.gotoxy(2,12);
    producto.mostrar();
    pantalla.gotoxy(2,16);
    cout<<"ESTA SEGURO/A DE CONTINUAR: (S/N): ";
    cin>>Confirmacion;
    pantalla.gotoxy (2,17); cout<<"------------------";

    if(Confirmacion=='S' || Confirmacion=='s'){
        //cambiar estado
        producto.setEstado(false);

        //sobreescribir el registro es guardar
        sobreEscribirRegistro(producto, posicion);

        cout<<endl<<endl;
        pantalla.gotoxy(2,18);
        cout<<"PRODUCTO DADO DE BAJA."<<endl<<endl;
        pantalla.gotoxy(3,20);
        system("pause");
    }
    else{
        pantalla.gotoxy(3,20);
        system("pause");
    }
    return 1;

}

int Producto::sobreEscribirRegistro(Producto producto, int posicion){

    FILE *pArchivo;

	pArchivo=fopen("productos.dat","rb+");

	if(pArchivo==NULL){
		return -1;
	}

    fseek(pArchivo, posicion*sizeof (Producto), 0); //usamos fseek para llegar al registro que necesito pisar con la
    int valor=fwrite(&producto, sizeof producto, 1,pArchivo); //sobre escribo
    fclose(pArchivo);

    return valor;
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


