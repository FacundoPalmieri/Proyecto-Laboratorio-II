#ifndef ARCHIVOTRANSACCION_H
#define ARCHIVOTRANSACCION_H
using namespace std;
#include <cstring>
#include "Transaccion.h"

class ArchivoTransaccion{
    private:
        char _Nombre[50];

    public:
        ArchivoTransaccion(const char* Nombre);

        int grabarEnDisco(Transaccion transaccion);
        int grabarEnDiscoPorPosicion(int posicion, Transaccion transaccion);
        Transaccion leerDeDisco(int pos);
        int cantidadTransacciones();

        void MensajeError();
};

#endif // ARCHIVOTRANSACCION_H
