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

int Empleado::getPassword(){
    return _password;
}

void Empleado::setPassword(int newPassword){
    _password = newPassword;
}

void Empleado::cargarEmpleado(){
    Pantalla pantalla;
    ArchivoEmpleado archivoEmpleado("empleados.dat");

    int password1, password2; //[10], password2[10];

    cout<<"INGRESE ID DEL EMPLEADO: ";
    cin>>_idEmpleado;

    if (archivoEmpleado.validarIDEmpleado(_idEmpleado)==false){
        pantalla.dimensiones (2,13);
        cout<<"INGRESE EL NOMBRE DEL EMPLEADO: ";
        cargarCadenas(_nombre,11);
        pantalla.dimensiones (2,14);
        cout<<"INGRESE EL APELLIDO DEL EMPLEADO: ";
        cargarCadenas(_apellido,19);
        pantalla.dimensiones (2,15);
        cout<<"INGRESE PASSWORD: ";
        cin>>password1;
        pantalla.dimensiones (2,16);
        cout<<"VUELVA A INGRESAR EL PASSWORD: ";
        cin>>password2;
        if(password1==password2){//strcmp(password1, password2))
            //cargarCadenas(_password, 9);
            _password = password1;
            pantalla.dimensiones (2,18);
            cout<<"ALTA DE USUARIO CORRECTA!";
            pantalla.dimensiones (2,19);
            system("pause");
        }
        else{
           pantalla.dimensiones (2,18);
           cout<<RED<<"LAS PASSWORD INGRESADAS NO COINCIDEN";
           pantalla.dimensiones (2,19);
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
    }
}

void Empleado::mostrar(){
    if (_estado==true){
        Pantalla pantalla;
       pantalla.dimensiones (2,9);
        cout<<"ID DEL EMPLEADO: "<<_idEmpleado;
       pantalla.dimensiones (2,10);
        cout<<"NOMBRE: "<<_nombre;
       pantalla.dimensiones (2,11);
        cout<<"APELLIDO: "<<_apellido;
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

