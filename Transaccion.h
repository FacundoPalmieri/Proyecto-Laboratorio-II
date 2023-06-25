#ifndef TRANSACCION_H_INCLUDED
#define TRANSACCION_H_INCLUDED

class Transaccion
{
private:
    int _idTransaccion;
    int _idOperacionAsociada;
    int _idProducto;
    int _cantidad;
    float _precio;
    bool _esCompra;
    bool _esVenta;
    int _estado;    // 0 - cancelada / 1 - Borrador / 2 - Confirmada
    int _contador;

public:
    Transaccion();
    Transaccion(int idOperacion, int idProducto, int cantidad, float precio, char tipo);

    int getIdProducto();
    int getCantidad();
    float getPrecio();

    int grabarEnDisco();
    int grabarEnDiscoPorPosicion(int posicion);
    int leerDeDisco(int pos);

    int generarCodigoTransaccion();
    int getLastIdTransaction();
    int cantidadTransacciones();

    void confirmarTransaccion();

    int getIdOperacionAsociada();
    bool esVenta();

    void setEstado(int estado);

    int setTipo(char tipo);

    void mostrar();

};

#endif // TRANSACCION_H_INCLUDED
