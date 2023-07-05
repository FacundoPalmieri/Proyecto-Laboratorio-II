#ifndef ARCHIVOEMPLEADO_H
#define ARCHIVOEMPLEADO_H
using namespace std;
#include <cstring>
#include "Empleado.h"


class ArchivoEmpleado{
    private:
        char _Nombre[50];

    public:
        ArchivoEmpleado(const char* Nombre);

        int grabarEnDisco(Empleado empleado);
        int leerDeDisco(int pos);
        int cantidadEnArchivo();
        bool validarIDEmpleado(int idEmpleado);
        int buscarDato(int idEmpleado);
        void modificarRegistro();
        int bajaEmpleado();
        int sobreEscribirRegistro(Empleado empleado, int posicion);

};

#endif // ARCHIVOEMPLEADO_H
