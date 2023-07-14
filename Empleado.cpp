#include "colors.h"
#include <iostream>
#include <cstring>
#include "ArchivoEmpleado.h"
#include "Empleado.h"
#include "Pantalla.h"
using namespace std;

Empleado::Empleado()
{
    //ctor
}

void Empleado::setIdEmpleado(int idEmpleado){
    _idEmpleado = idEmpleado;
}

int Empleado::getIdEmpleado(){
    return _idEmpleado;
}

void Empleado::setNombre(const char* name){
    strcpy(_nombre, name);
}

const char* Empleado::getNombre(){
    return _nombre;
}

void Empleado::setApellido(const char* lastName){
    strcpy(_apellido, lastName);
}

const char* Empleado::getApellido(){
    return _apellido;
}

void Empleado::setEstado(bool estado){
    _estado = estado;
}

bool Empleado::getEstado(){
    return _estado;
}

const char* Empleado::getPassword(){
    return _password;
}

void Empleado::setPassword(const char* newPassword){
    strcpy(_password, newPassword);
}

void Empleado::setDNI(int DNI){
    _dni = DNI;
}

int Empleado:: getDNI(){
    return _dni;
}

int Empleado::cargarEmpleado(){
    Pantalla pantalla;
    ArchivoEmpleado archivoEmpleado("empleados.dat");
    char password1[20], password2[20]; //[10], password2[10];

    pantalla.dimensiones (2,8);
    cout<<"INGRESE ID DEL EMPLEADO          : ";
    cin>>_idEmpleado;

    if (archivoEmpleado.validarIDEmpleado(_idEmpleado)==false){
        pantalla.dimensiones (2,9);
        cout<<"INGRESE EL NOMBRE DEL EMPLEADO   : ";
        cargarCadenas(_nombre,11);
        pantalla.dimensiones (2,10);
        cout<<"INGRESE EL APELLIDO DEL EMPLEADO : ";
        cargarCadenas(_apellido,19);
        pantalla.dimensiones (2,11);
        cout<<"INGRESE EL DNI                   : ";
        cin >>_dni;
        pantalla.dimensiones (2,12);
        cout<<"INGRESE EL PASSWORD              : ";
        cargarCadenas(password1,19);
        pantalla.dimensiones (2,13);
        cout<<"VUELVA A INGRESAR EL PASSWORD    : ";
        cargarCadenas(password2,19);
        if(strcmp(password1, password2)==0){//strcmp(password1, password2))
            strcpy(_password, password1);
            pantalla.dimensiones (2,19);
            cout << GREEN;
            cout<<"ALTA DE USUARIO CORRECTA!";
            cout << BLUE;
            _estado = true;
            pantalla.dimensiones (2,20);
            system("pause");
        }
        else{
           pantalla.dimensiones (2,19);
           cout<<RED<<"LAS PASSWORD INGRESADAS NO COINCIDEN";
           pantalla.dimensiones (2,20);
           cout << BLUE;
           system("pause");
        }
    }
    else{
        pantalla.dimensiones (2,13);
        cout<<RED<<"ID DE EMPLEADO YA EXISTENTE";
        pantalla.dimensiones (2,15);
        cout << BLUE;
        system("pause");
        return -1;
    }
}

void Empleado::mostrar(int posicion){
    Pantalla pantalla;

    if (_estado==true){
        if(posicion ==1){
            pantalla.dimensiones(2,13);
            cout<<"ID DEL EMPLEADO  : "<<_idEmpleado << endl;
            pantalla.dimensiones(2,14);
            cout<<"NOMBRE           : "<<_nombre << endl;
            pantalla.dimensiones(2,15);
            cout<<"APELLIDO         : "<<_apellido << endl;
            pantalla.dimensiones(2,16);
            cout<<"DNI              : "<<_dni << endl;
        }
        else{
            pantalla.dimensiones(2,10);
            cout<<"ID DEL EMPLEADO  : "<<_idEmpleado << endl;
            pantalla.dimensiones(2,11);
            cout<<"NOMBRE           : "<<_nombre << endl;
            pantalla.dimensiones(2,12);
            cout<<"APELLIDO         : "<<_apellido << endl;
            pantalla.dimensiones(2,13);
            cout<<"DNI              : "<<_dni << endl;

        }
    }
}

void Empleado::cargarCadenas(char *pal, int tam){
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

