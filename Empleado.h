#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <cstring>

#ifndef EMPLEADO_H
#define EMPLEADO_H



class Empleado
{
    private:
        int _idEmpleado;
        char _nombre[12];
        char _apellido[20];
        int _password;
        bool _estado;

    public:
        Empleado();

        void setIdEmpleado(int idEmpleado);
        int getIdEmpleado();

        void setNombre(const char* name);
        const char* getNombre();

        void setApellido(const char* lastName);
        const char* getApellido();

        void setEstado(bool estado);
        bool getEstado();

        int getPassword();
        void setPassword(int passwprd);

        void cargarEmpleado();
        void mostrarEmpleado();

        //bool valirdarPassword();NO ESTÁ IMPLEMENTADO

        int grabarEnDisco();
        int leerDeDisco(int pos);
        int cantidadEnArchivo();
        bool valirdarIDEmpleado(int idEmpleado);
        int buscarDato(int idVendedor);
        void modificarRegistro(int idVendedor);
        int bajaEmpleado();
        int sobreEscribirRegistro(Empleado empleado, int posicion);
        void cargarCadenas(char *pal, int tam);

};

#endif // EMPLEADO_H

