#ifndef ARCHIVOPRODUCTO_H
#define ARCHIVOPRODUCTO_H

#include "Producto.h"

class ArchivoProducto
{
    private:
        char _Nombre[50];

    public:
        ArchivoProducto(const char* Nombre);

        void grabarEnDisco(Producto producto);
        Producto leerDeDisco(int pos);
        int cantidadEnArchivo();
        void modificarRegistro();
        int sobreEscribirRegistro(Producto producto, int posicion);
        void bajaProducto();
        int posicionRegistro(int idProducto);
        Producto buscarPorCodigo(int idProducto);
        void Ordenar();

        void MensajeError();

};

#endif // ARCHIVOPRODUCTO_H
