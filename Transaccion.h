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
    int _estado;    // 0 - cerrada / 1 - Borrador / 2 - Confirmada
    int _contador;
    int _idMesa;

public:
    Transaccion();
    Transaccion(int idOperacion, int idProducto, int cantidad, float precio, int idMesa);

    int getIdTransaccion();
    int getIdProducto();
    int getCantidad();
    int getIdOperacionAsociada();
    float getPrecio();
    int getIdMesa();
    int getEstado();
    void setIdProducto(int IdProducto);
    void setCantidad(int cantidad);
    void setPrecio(int precio);
    void setEstado(int estado);


    bool esVenta();
    void confirmarTransaccion();

    int generarCodigoTransaccion();
    float cerrarMesa(int mesa);

    void mostrar();

};

#endif // TRANSACCION_H_INCLUDED
