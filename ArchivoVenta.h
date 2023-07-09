#ifndef ARCHIVOVENTA_H
#define ARCHIVOVENTA_H
#include <cstring>
using namespace std;

#include "Venta.h"


class ArchivoVenta

{
    private:
        char _Nombre[50];

    public:
        ArchivoVenta(const char* Nombre);

        int grabarEnDisco(Venta venta);
        Venta leerDeDisco(int pos);
        int cantidadVentas();

        void MensajeError();
};


#endif // ARCHIVOVENTA_H
