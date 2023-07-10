#ifndef MENU_H
#define MENU_H


class Menu
{
public:


    //PROTOTIPOS DE LAS FUNCIONES

    void menuIdVendedor();
    void menuPrincipal(int idVendedor);
    void menuVenta(int idVendedor);
    void menuConsulta(int idVendedor);
    void menuListados(int idVendedor);
    void vistaListadoProductos(int idVendedor);
    void vistaListadoEmpleados(int idVendedor);
    void menuConsultasDeVentas(int idVendedor);
    void vistaVentasPorMes(int idVendedor);
    void vistaVentasPorEmpleado(int idVendedor);
    void vistaVentasPorProducto(int idVendedor);
    void menuAjuste(int idVendedor);
    void vender(int idVendedor);
    void menuPedido(int idVendedor);
    void menuConsumoMesa(int idVendedor);



    void FinalizarPrograma();
    void OpcionIncorrecta();

private:
    int _opcion;
};

#endif // MENU_H
