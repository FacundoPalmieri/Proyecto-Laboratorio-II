#ifndef VENTA_H
#define VENTA_H
#include "Fecha.h"
#include "Transaccion.h"


class Venta
{
private:
    int _IdVenta;
    float _consumoTotal;
    int _idVendedor;
    Fecha _fecha;
    int _idMesa;
    int _estado;    // 0 - cancelada / 1 - Borrador / 2 - Confirmada


public:
    Venta();
    Venta(int vendedor, int mesa);

    int getIDventa();
    int getIdMesa();
    float getConsumoTotal();
    Fecha getFecha();
    int getIdVendedor();

    void cargarVenta();
    void mostrar();

    void setVendedor(int idVendedor);
    void setMesa(int mesa);
    void setConsumoTotal(float total);

    bool confirmarVenta();

    int generarCodigoVenta();
    int cantidadVentas();

    int agregarProductoALaVenta(int idProducto, int cantidad);

};

#endif // VENTA_H
