#ifndef MENU_H
#define MENU_H


class Pantalla
{
public:
    Pantalla();

    //PROTOTIPOS DE LAS FUNCIONES
    void dibujarCuadro(int x1,int y1,int x2,int y2);
    void dibujarCuadroDoble(int x1,int y1,int x2,int y2, int y3);
    void gotoxy(int x,int y);
    int menuIdVendedor();
    int menuPrincipal(int idVendedor);
    int menuVenta(int idVendedor);
    int menuConsulta(int idVendedor);
    int menuListados(int idVendedor);
    int vistaListadoProductos(int idVendedor);
    int vistaListadoEmpleados(int idVendedor);
    int menuConsultasDeVentas(int idVendedor);
    int vistaVentasPorMes(int idVendedor);
    int vistaVentasPorEmpleado(int idVendedor);
    int vistaVentasPorProducto(int idVendedor);
    int menuAjuste(int idVendedor);
    void vender(int idVendedor);
    int menuPedido(int idVendedor);
    int menuConsumoMesa(int idVendedor);

private:
    int _opcion;
};

#endif // MENU_H
