#ifndef MENU_H
#define MENU_H


class Menu
{
public:


    //PROTOTIPOS DE LAS FUNCIONES

    int menuIdVendedor();
    int menuPrincipal(int idVendedor);
    int menuVenta(int idVendedor);
    int menuConsulta(int idVendedor);
    int menuListados(int idVendedor);
    void vistaListadoProductos(int idVendedor);
    void vistaListadoEmpleados(int idVendedor);
    int menuConsultasDeVentas(int idVendedor);
    void vistaVentasPorMes(int idVendedor);
    void vistaVentasPorEmpleado(int idVendedor);
    void vistaVentasPorProducto(int idVendedor);
    int menuAjuste(int idVendedor);
    void vender(int idVendedor);
    int menuPedido(int idVendedor);
    void menuConsumoMesa(int idVendedor);
    void cerrarMesa();


    void FinalizarPrograma();
    void OpcionIncorrecta();
    void marcoPantallaMenu();

private:
    int _opcion;
};

#endif // MENU_H
