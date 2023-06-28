#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <list>
#include "rlutil.h"
#include "colors.h"
#include <limits>


#define XSCREEN 78
#define YSCREEN 24

using namespace std;
using namespace rlutil;

#include "Menu.h"
#include "Producto.h"
#include "Venta.h"
#include "Empleado.h"

Pantalla::Pantalla()
{

}




// Función PAUSA.
void pause() {
    cout<< BLUE;
    cout << "Presiona Enter para continuar...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //limpia buffer
    cin.get();
}

//FUNCION GOTOXY
void Pantalla::gotoxy(int x,int y)
{
    HANDLE hcon; //controlador (handle) de la salida estándar de la consola
    hcon = GetStdHandle(STD_OUTPUT_HANDLE); //utiliza la función GetStdHandle para obtener el controlador (handle) de la salida estándar de la consola, devolviendo el controlador de la consola que se utiliza para la salida estándar.
    COORD dwPos; //se crea una estructura de tipo COORD llamada dwPos para almacenar las coordenadas x e y proporcionadas
    dwPos.X = x; //Se asignan los valores de x e y a las propiedades X e Y de la estructura dwPos respectivamente.
    dwPos.Y= y; //Se asignan los valores de x e y a las propiedades X e Y de la estructura dwPos respectivamente.
    SetConsoleCursorPosition(hcon,dwPos); //utiliza la función SetConsoleCursorPosition para establecer la posición del cursor en la pantalla de la consola.
}

//FUNCION QUE DIBUJA EL CUADRO
void Pantalla::dibujarCuadro(int x1,int y1,int x2,int y2)
{
    int i;

    for (i=x1; i<x2; i++)
    {
        gotoxy(i,y1);
        printf("\304"); //linea horizontal superior
        gotoxy(i,y2);
        printf("\304"); //linea horizontal inferior
    }

    for (i=y1; i<y2; i++)
    {
        gotoxy(x1,i);
        printf("\263"); //linea vertical izquierda
        gotoxy(x2,i);
        printf("\263"); //linea vertical derecha
    }

    gotoxy(x1,y1);
    printf("\332");
    gotoxy(x1,y2);
    printf("\300");
    gotoxy(x2,y1);
    printf("\277");
    gotoxy(x2,y2);
    printf("\331");
}

void Pantalla::dibujarCuadroDoble(int x1,int y1,int x2,int y2, int y3){
    int i;

    for (i=x1; i<x2; i++)
    {
        gotoxy(i,y1);
        printf("\304"); //linea horizontal superior
        gotoxy(i,y2);
        printf("\304"); //linea horizontal intermedia
        gotoxy(i,y3);
        printf("\304"); //linea horizontal inferior

    }

    for (i=y1; i<y3; i++)
    {
        gotoxy(x1,i);
        printf("\263"); //linea vertical izquierda
        gotoxy(x2,i);
        printf("\263"); //linea vertical derecha
    }

    gotoxy(x1,y1);
    printf("\332");
    gotoxy(x1,y3);
    printf("\300");
    gotoxy(x2,y1);
    printf("\277");
    gotoxy(x2,y3);
    printf("\331");
}

int Pantalla::menuIdVendedor(){
    int IntentosUsuario = 3;
    do{
        Empleado empleadoAux;
        int idEmpleado=-1, pos, posAux;
        int password=-1;

        cls();
        system("mode con: cols=80 lines=25"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
        system("COLOR 71"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS
        dibujarCuadro(0,0,XSCREEN,YSCREEN); //SE DIBUJA EL CUADRO PRINCIPAL
        dibujarCuadro(1,1,(XSCREEN-1),3); //SE DIBUJA EL CUADRO DEL TITULO
        gotoxy(30,2); cout<<"DELTAPOINT RESTO";

        gotoxy (25,6); cout<<"INGRESO AL SISTEMA";
        gotoxy (20,7); cout<<"--------------------------------";
        gotoxy (22,10); cout<<"INGRESE SU ID DE VENDEDOR: ";
        cin>>idEmpleado;

        pos=0;
        posAux=-1;
        while(empleadoAux.leerDeDisco(pos++)>0){ // Lee y aumenta la posición. Ingresa siempre que sea mayor a 0
            if(empleadoAux.getIdEmpleado()==idEmpleado&&empleadoAux.getEstado()==true){
                posAux = pos-1; //  almacenar la posición del empleado encontrado antes de que pos sea incrementada nuevamente
                gotoxy (22,11); cout<<"- ("<<empleadoAux.getApellido()<<", "<<empleadoAux.getNombre()<<")"; // - PSW:"<<empleadoAux.getPassword();
            }
        }

        if(posAux!=-1){
            empleadoAux.leerDeDisco(posAux);
            int IntentosClave = 3;

            for(int i = 0; i<3; i++){
                gotoxy (2,12); cout<<"                                     ";
                gotoxy (22,13); cout<< BLUE <<"INGRESE SU CLAVE: ";
                cin>>password;
                IntentosClave --;
                //cout<<"psw ingresado: "<<password<<", psw encontrado: "<<empleadoAux.getPassword();
                if(empleadoAux.getPassword()==password){
                    int Retorno = menuPrincipal(empleadoAux.getIdEmpleado()); // Si coinciden las contraseñas ingresa al método menuPrincipal, pasando como parametros el ID)
                    if(Retorno == 0){
                        return 0;
                    }
                }
                else{
                    gotoxy (26,16); cout<< RED <<" CLAVE INCORRECTA" << endl;
                    if(IntentosClave == 0){
                        gotoxy (18,18);cout << " Ha alcanzado el limite de intentos " << endl;
                        gotoxy (1,23);pause();
                        return 0;
                    }
                    gotoxy (22,17); cout<< RED <<" - Le quedan " << IntentosClave << " intentos - " << endl;
                    gotoxy (1,23); pause();
                    gotoxy (26,16); cout << "                                 " << endl; // Limpia la pantalla en la parte posterior al ingreso de clave
                    gotoxy (22,17); cout << "                                 " << endl;
                    gotoxy (1,23);  cout << "                                 " <<endl;
                    gotoxy (40,13); cout << "                                 " <<endl;





                }

            }
        }
        else{
            gotoxy (24,13); cout<< RED <<"USUARIO NO ENCONTRADO ";
            IntentosUsuario--;
            if(IntentosUsuario == 0){
                gotoxy (18,18);cout << " Ha alcanzado el limite de intentos " << endl;
                gotoxy (1,23);pause();
                return 0;
            }
            gotoxy (22,17); cout<< RED <<" - Le quedan " << IntentosUsuario << " intentos - " << endl;
            gotoxy (1,23); pause();
        }


    }while(IntentosUsuario>0);
   return 0;
}

int Pantalla::menuPrincipal(int idVendedor)
{
    do
    {
        cls();
        system("mode con: cols=80 lines=25"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
        system("COLOR 71"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS
        dibujarCuadro(0,0,XSCREEN,YSCREEN); //SE DIBUJA EL CUADRO PRINCIPAL
        dibujarCuadro(1,1,(XSCREEN-1),3); //SE DIBUJA EL CUADRO DEL TITULO

        gotoxy(30,2);cout<<"DELTAPOINT RESTO";

        gotoxy (2,6); cout<<"MENU PRINCIPAL";
        gotoxy (2,7); cout<<"------------------";
        gotoxy (2,10); cout<<"INGRESE UNA OPCION: ";

        gotoxy (2,13); cout<<"1 - MODO VENTA: ";
        gotoxy (2,14); cout<<"2 - MODO CONSULTA: ";
        gotoxy (2,15); cout<<"3 - AJUSTES: ";
        gotoxy (2,16); cout<<"4 - CERRAR SESION DE USUARIO: ";
        gotoxy (2,17); cout<<"0 - SALIR DEL PROGRAMA: ";

        gotoxy (2,19); cout<<"->: ";
        cin>>_opcion;



        switch (_opcion)
        {
        case 1:
            menuVenta(idVendedor);
            break;
        case 2:
            menuConsulta(idVendedor);;
            break;
        case 3:
            menuAjuste(idVendedor);
            break;
        case 4:
            menuIdVendedor();
            break;
        case 0:
            exit(0);

            break;

        default:
            break;
        }

    }
    while(_opcion!=0);
    return 0;
}

int Pantalla::menuVenta(int idVendedor)
{
    do{
        cls();
        system("mode con: cols=80 lines=25"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
        system("COLOR 71"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS
        dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
        dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
        gotoxy(30,2);cout<<"DELTAPOINT RESTO";

        gotoxy (2,6); cout<<"MENU VENTA";
        gotoxy (2,7); cout<<"------------------";
        gotoxy (2,10); cout<<"INGRESE UNA OPCION: ";

        gotoxy (2,13); cout<<"1 - ATENDER CLIENTE: ";
        gotoxy (2,14); cout<<"2 - CONSUMO DE MESA: ";
        gotoxy (2,15); cout<<"3 - VOLVER AL MENU PRINCIPAL: ";
        gotoxy (2,16); cout<<"0 - SALIR DEL PROGRAMA: ";

        gotoxy (2,18); cout<<"->: ";
        cin>>_opcion;

        switch (_opcion)
        {
        case 1:
            menuPedido(idVendedor);
            break;
        case 2:
            menuConsumoMesa(idVendedor);
            break;
        case 3:
            menuPrincipal(idVendedor);
            break;
        case 0:
            exit(0);
            break;

        /*default:
            break;*/
        }

        gotoxy (2,22);
        cin.ignore();
        anykey();

    }while(_opcion!=0);

    return 0;

}

int Pantalla::menuConsulta(int idVendedor)
{
    do{
        cls();
        system("mode con: cols=80 lines=25"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
        system("COLOR 71"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS
        dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
        dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
        gotoxy(30,2); cout<<"DELTAPOINT RESTO";

        gotoxy (2,6); cout<<"MENU CONSULTA";
        gotoxy (2,7); cout<<"------------------";
        gotoxy (2,10); cout<<"INGRESE UNA OPCION: ";

        gotoxy (2,13); cout<<"1 - LISTADOS: ";
        gotoxy (2,14); cout<<"2 - CONSULTA DE VENTAS: ";
        gotoxy (2,15); cout<<"3 - VOLVER AL MENU PRINCIPAL: ";
        gotoxy (2,16); cout<<"0 - SALIR DEL PROGRAMA: ";

        gotoxy (2,19);
        cout<<"->: ";
        cin>>_opcion;
        switch (_opcion)
        {
        case 1:
            menuListados(idVendedor);
            break;
        case 2:
            menuConsultasDeVentas(idVendedor);
            break;
        case 3:
            menuPrincipal(idVendedor);
            break;
        case 0:
            exit(0);
            break;

        default:
            break;
        }

        gotoxy (2,22);
        cin.ignore();
        anykey();

    }while(_opcion!=0);
    return 0;
}

int Pantalla::menuListados(int idVendedor)
{
    cls();

    Empleado empleadoAux;
    Producto productoAux;

    system("mode con: cols=80 lines=25");
    system("COLOR 71");
    dibujarCuadro(0,0,78,24);
    dibujarCuadro(1,1,77,3);
    gotoxy(30,2); cout << "DELTAPOINT RESTO";

    gotoxy (2,6); cout << "MENU LISTADOS";
    gotoxy (2,7); cout << "------------------";
    gotoxy (2,10); cout << "INGRESE UNA OPCION: ";

    gotoxy (2,13); cout << "1 - PRODUCTOS: ";
    gotoxy (2,14); cout << "2 - EMPLEADOS: ";
    gotoxy (2,15); cout << "3 - VOLVER AL MENU PRINCIPAL: ";
    gotoxy (2,16); cout << "0 - SALIR DEL PROGRAMA: ";

    gotoxy (2,19); cout << "->: ";
    cin >> _opcion;

    switch (_opcion)
    {
        case 1:
            vistaListadoProductos(idVendedor);
            break;
        case 2:
            vistaListadoEmpleados(idVendedor);
            break;
        case 3:
            menuPrincipal(idVendedor);
            break;
        case 0:
            exit(0); // Salir del programa
            break;
        default:
            break;
    }

    gotoxy (2,22);
    cin.ignore();
    anykey();

    return 0;
}

int Pantalla::vistaListadoProductos(int idVendedor)
{
    do{
        cls();

        Empleado empleadoAux;
        Producto productoAux;
        int pos, renglon;

        system("mode con: cols=80 lines=25"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
        system("COLOR 71"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS
        dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
        dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
        gotoxy(30,2); cout<<"DELTAPOINT RESTO";

        gotoxy (2,6); cout<<"LISTA DE PRODUCTOS:";
        gotoxy (2,7); cout<<"--------------------";

        pos=0;
        renglon = 8;
        while(productoAux.leerDeDisco(pos++)>0){
            if(productoAux.getEstado()==true){
                gotoxy (5,renglon); cout<<productoAux.getIdProducto();
                gotoxy (14,renglon); cout<<productoAux.getNombreProducto();
                gotoxy (60,renglon); cout<<"$"<<productoAux.getPrecioProducto();
                renglon++;
            }
        }

        gotoxy (2,20); cout<<"1 - VOLVER";

        do{ // Vuelve a pedir la opción, si la misma es incorrecta.
            gotoxy (2,21); cout<<"->: ";
            cin>>_opcion;
            switch (_opcion){
                case 1:
                    menuListados(idVendedor);
                    break;

                default:
                    cout << RED;
                    gotoxy (2,22);cout << "Opcion Incorrecta " << endl;
                    gotoxy (2,23); pause();
                    gotoxy (2,21); cout<<"->:                             "; // Limpia pantalla
                    gotoxy (2,22); cout<<"                                ";
                    gotoxy (2,23); cout<<"                                ";

                    break;
            }

        }while (_opcion != 1);


        gotoxy (2,22);
        cin.ignore();
        anykey();

    }while(_opcion!=0);
    return 0;
}

int Pantalla::vistaListadoEmpleados(int idVendedor)
{
    do{
        cls();

        Empleado empleadoAux;
        int pos, renglon;

        system("mode con: cols=80 lines=25"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
        system("COLOR 71"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS
        dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
        dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
        gotoxy(30,2); cout<<"DELTAPOINT RESTO";

        gotoxy (2,6); cout<<"LISTA DE EMPLEADOS:";
        gotoxy (2,7); cout<<"--------------------";

        pos=0;
        renglon = 8;
        while(empleadoAux.leerDeDisco(pos++)>0){
            if(empleadoAux.getEstado()==true){
            gotoxy (5,renglon); cout<<empleadoAux.getIdEmpleado();
            gotoxy (14,renglon); cout<<empleadoAux.getApellido()<<", "<<empleadoAux.getNombre();
            gotoxy (45,renglon); cout<<empleadoAux.getPassword();
            renglon++;
            }
        }

        gotoxy (2,20); cout<<"1 - VOLVER";

        do{ // Vuelve a pedir la opción, si la misma es incorrecta.
            gotoxy (2,21); cout<<"->: ";
            cin>>_opcion;
            switch (_opcion){
                case 1:
                    menuListados(idVendedor);
                    break;

                default:
                    cout << RED;
                    gotoxy (2,22);cout << "Opcion Incorrecta " << endl;
                    gotoxy (2,23); pause();
                    gotoxy (2,21); cout<<"->:                             "; // Limpia pantalla
                    gotoxy (2,22); cout<<"                                ";
                    gotoxy (2,23); cout<<"                                ";

                    break;
            }

        }while (_opcion != 1);


        gotoxy (2,22);
        cin.ignore();
        anykey();

    }while(_opcion!=0);
    return 0;
}

int Pantalla::menuConsultasDeVentas(int idVendedor)
{
    do{
        cls();
        system("mode con: cols=80 lines=25"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
        system("COLOR 71"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS
        dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
        dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
        gotoxy(30,2); cout<<"DELTAPOINT RESTO";

        gotoxy (2,6); cout<<"MENU CONSULTA DE VENTAS";
        gotoxy (2,7); cout<<"------------------";
        gotoxy (2,10); cout<<"INGRESE UNA OPCION: ";

        gotoxy (2,13); cout<<"1 - VENTAS TOTALES POR MES: ";
        gotoxy (2,14); cout<<"2 - VENTAS POR EMPLEADO: ";
        gotoxy (2,15); cout<<"3 - VENTAS POR PRODUCTO: ";
        gotoxy (2,16); cout<<"4 - VOLVER AL MENU ANTERIOR: ";
        gotoxy (2,17); cout<<"0 - SALIR DEL PROGRAMA: ";

        gotoxy (2,19); cout<<"->: ";
        cin>>_opcion;
        switch (_opcion)
        {
        case 1:
            vistaVentasPorMes(idVendedor);
            break;
        case 2:
            vistaVentasPorEmpleado(idVendedor);
            break;
        case 3:
            vistaVentasPorProducto(idVendedor);
            break;
        case 4:
            menuConsulta(idVendedor);
            break;
        case 0:
            exit(0);
            break;

        default:
            break;
        }

        gotoxy (2,22);
        cin.ignore();
        anykey();

    }while(_opcion!=0);
    return 0;
}

int Pantalla::vistaVentasPorMes(int idVendedor)
{
    do{
        cls();

        Venta ventaAux;
        float consumoTotal;

        system("mode con: cols=80 lines=25"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
        system("COLOR 71"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS
        dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
        dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
        gotoxy(30,2); cout<<"DELTAPOINT RESTO";

        gotoxy (2,4); cout<<"VENTAS POR MES:";
        gotoxy (2,5); cout<<"--------------------";

        int cantidad = ventaAux.cantidadVentas();

        for(int anio=2020; anio<2026; anio++){
            gotoxy ((anio-2017)*9-8,7); cout<<anio;
            for(int mes=1; mes<13; mes++){
                gotoxy (2,mes+7); cout<<"MES "<<mes;

                for(int indice=0; indice<cantidad; indice++){
                    ventaAux.leerDeDisco(indice);
                    if(ventaAux.getFecha().getAnio()==anio){
                        if(ventaAux.getFecha().getMes()==mes){
                            consumoTotal += ventaAux.getConsumoTotal();
                            gotoxy ((anio-2017)*9-10,mes+7); cout<<consumoTotal<<"|";
                        }
                        else{
                            gotoxy ((anio-2017)*9-8,mes+7); cout<<" - - |";
                        }
                    }
                    else{
                        gotoxy ((anio-2017)*9-8,mes+7); cout<<" - - |";
                    }
                }
            }
        }


        gotoxy (2,22); cout<<"1 - VOLVER";

        gotoxy (2,23); cout<<"->: ";
        cin>>_opcion;
        switch (_opcion)
        {
        case 1:
            menuConsultasDeVentas(idVendedor);
            break;

        default:
            break;
        }

        gotoxy (2,22);
        cin.ignore();
        anykey();

    }while(_opcion!=0);
    return 0;
}

int Pantalla::vistaVentasPorEmpleado(int idVendedor)
{
    do{
        cls();

        Venta ventaAux;
        Empleado empleadoAux;
        int pos1, pos2, renglon = 8;
        float consumoTotal;

        system("mode con: cols=80 lines=25"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
        system("COLOR 71"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS
        dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
        dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
        gotoxy(30,2); cout<<"DELTAPOINT RESTO";

        gotoxy (2,4); cout<<"VENTAS POR EMPLEADO:";
        gotoxy (2,5); cout<<"--------------------";

        for(int id=0; id<10; id++){

            consumoTotal=0;
            pos1=0;
            while(empleadoAux.leerDeDisco(pos1++)>0){
                if(empleadoAux.getIdEmpleado()==id&&empleadoAux.getEstado()==true){
                    gotoxy(2,renglon); cout<<empleadoAux.getNombre()<<" "<<empleadoAux.getApellido();
                    pos2=0;
                    while(ventaAux.leerDeDisco(pos2++)>0){
                        if(ventaAux.getIdVendedor()==id){
                            consumoTotal+=ventaAux.getConsumoTotal();
                        }
                    }
                    gotoxy(25,renglon); cout<<"$ "<<consumoTotal;
                    renglon++;
                }
            }
        }

        gotoxy (2,22); cout<<"1 - VOLVER";

        gotoxy (2,23); cout<<"->: ";
        cin>>_opcion;
        switch (_opcion)
        {
        case 1:
            menuConsultasDeVentas(idVendedor);
            break;

        default:
            break;
        }

        gotoxy (2,22);
        cin.ignore();
        anykey();

    }while(_opcion!=0);
    return 0;
}

int Pantalla::vistaVentasPorProducto(int idVendedor)
{
    do{
        cls();

        Transaccion transaccionAux;
        Producto productoAux;
        int pos1, pos2, renglon = 8, id;
        float consumoTotal;

        system("mode con: cols=80 lines=25"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
        system("COLOR 71"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS
        dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
        dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
        gotoxy(30,2); cout<<"DELTAPOINT RESTO";

        gotoxy (2,4); cout<<"VENTAS POR PRODUCTO:";
        gotoxy (2,5); cout<<"--------------------";

        pos1=0;
        while(productoAux.leerDeDisco(pos1++)>0){
            consumoTotal=0;
            id = productoAux.getIdProducto();

            if (productoAux.getEstado()==true){
                gotoxy(2,renglon); cout<<productoAux.getNombreProducto();
                pos2=0;
                while(transaccionAux.leerDeDisco(pos2++)>0){
                    if(transaccionAux.getIdProducto()==id){
                        consumoTotal+=(transaccionAux.getPrecio()*transaccionAux.getCantidad());
                    }
                }
                gotoxy(35,renglon); cout<<"$ "<<consumoTotal;
                renglon++;
            }
        }

        gotoxy (2,22); cout<<"1 - VOLVER";

        gotoxy (2,23); cout<<"->: ";
        cin>>_opcion;
        switch (_opcion)
        {
        case 1:
            menuConsultasDeVentas(idVendedor);
            break;

        default:
            break;
        }

        gotoxy (2,22);
        cin.ignore();
        anykey();

    }while(_opcion!=0);
    return 0;
}

int Pantalla::menuAjuste(int idVendedor)
{
    do{
        Producto productoAux;
        Empleado empleadoAux;
        int opcion;

        cls();
        system("mode con: cols=80 lines=25"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
        system("COLOR 71"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS
        dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
        dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
        gotoxy(30,2); cout<<"DELTAPOINT RESTO";

        gotoxy (2,6); cout<<"MENU AJUSTE";
        gotoxy (2,7); cout<<"------------------";
        gotoxy (2,9); cout<<"INGRESE UNA OPCION: ";

        gotoxy (2,11); cout<<"1 - CARGAR PRODUCTO: ";
        gotoxy (2,12); cout<<"2 - MODIFICAR PRODUCTO: ";
        gotoxy (2,13); cout<<"3 - DAR DE BAJA PRODUCTO: ";
        gotoxy (2,14); cout<<"4 - CARGAR EMPLEADO: ";
        gotoxy (2,15); cout<<"5 - MODIFICAR EMPLEADO: ";
        gotoxy (2,16); cout<<"6 - DAR DE BAJA EMPLEADO: ";
        gotoxy (2,17); cout<<"7 - VOLVER AL MENU PRINCIPAL: ";
        gotoxy (2,18); cout<<"0 - SALIR DEL PROGRAMA: ";

        gotoxy (2,20); cout<<"->: ";
        cin>>opcion;

        switch (opcion)
        {
        case 1:
            cls();
            gotoxy(30,2); cout<<"DELTAPOINT RESTO";
            dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
            dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
            gotoxy (2,6); cout<<"MENU AJUSTE - CARGAR PRODUCTO";
            gotoxy (2,7); cout<<"------------------";
            gotoxy (2,9);
            productoAux.cargar();
            gotoxy (2,15);
            productoAux.grabarEnDisco(productoAux);
            gotoxy (2,16);
            system("pause");
            menuAjuste(idVendedor);
            break;
        case 2:
            cls();
            gotoxy(30,2); cout<<"DELTAPOINT RESTO";
            dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
            dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
            gotoxy (2,6); cout<<"MENU AJUSTE - MODIFICAR PRODUCTO";
            gotoxy (2,7); cout<<"------------------";
            gotoxy (2,12);
            productoAux.modificarRegistro();
            menuAjuste(idVendedor);
            break;

        case 3:
            cls();
            gotoxy(30,2); cout<<"DELTAPOINT RESTO";
            dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
            dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
            gotoxy (2,6); cout<<"MENU AJUSTE - ELIMINAR PRODUCTO";
            gotoxy (2,7); cout<<"------------------";
            gotoxy (2,12);
            productoAux.bajaProducto();
            menuAjuste(idVendedor);
            break;
        case 4:
            cls();
            dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
            dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
            gotoxy (2,6); cout<<"MENU AJUSTE - CARGAR EMPLEADO";
            gotoxy (2,7); cout<<"------------------";
            gotoxy (2,12);
            empleadoAux.cargarEmpleado();
            empleadoAux.grabarEnDisco();
            menuAjuste(idVendedor);
            break;
        case 5:
            cls();
            gotoxy(30,2); cout<<"DELTAPOINT RESTO";
            dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
            dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
            gotoxy (2,6); cout<<"MENU AJUSTE - MODIFICAR EMPLEADO";
            gotoxy (2,7); cout<<"------------------";
            gotoxy (2,8);
            empleadoAux.modificarRegistro();
            menuAjuste(idVendedor);
            break;
        case 6:
            cls();
            gotoxy(30,2); cout<<"DELTAPOINT RESTO";
            dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
            dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
            gotoxy (2,5); cout<<"MENU AJUSTE - BAJA DE EMPLEADO";
            gotoxy (2,6); cout<<"------------------";
            //gotoxy (2,12);
            empleadoAux.bajaEmpleado();
            menuAjuste(idVendedor);
            break;
        case 7:
            menuPrincipal(idVendedor);
            break;
        case 0:
            exit(0);
            break;
        }

        gotoxy (2,22);
        cin.ignore();
        anykey();

    }while(_opcion!=0);
    return 0;

}

int Pantalla::menuPedido(int idVendedor)
{
    do{
        Venta venta;
        Producto producto;
        int opcion, renglon = 8, codigoProducto = 0, cantidadProducto = 0, mesaAux = -1;
        float subtotal = 0;

        cls();
        system("mode con: cols=100 lines=26"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
        system("COLOR 71"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS
        dibujarCuadro(0,0,98,25); //SE DIBUJA EL CUADRO PRINCIPAL
        dibujarCuadro(1,1,97,3); //SE DIBUJA EL CUADRO DEL TITULO
        gotoxy(39,2); cout<<"DELTAPOINT RESTO";

        dibujarCuadroDoble(2,4,96,6,23);
        gotoxy (4,5); cout<<"MESA: ";
        cin>> mesaAux;
        venta.setMesa(mesaAux);
        venta.setVendedor(idVendedor);

        gotoxy (3,renglon-1); cout<<"CODIGO";
        gotoxy (18,renglon-1);cout<<"NOMBRE PRODUCTO";
        gotoxy (50,renglon-1);cout<<"CANTIDAD";
        gotoxy (66,renglon-1);cout<<"PRECIO";
        gotoxy (82,renglon-1);cout<<"SUBTOTAL";
        gotoxy (3,24); cout<<"0 - FIN DE CARGA DE PRODUCTOS";

        gotoxy (3,renglon);
        cin>>codigoProducto;
        gotoxy (80,22); cout<<"TOTAL: ";

        while(codigoProducto>0)
        {
            producto = buscarPorCodigo(codigoProducto);
            gotoxy (15,renglon); cout<<producto.getNombreProducto();
            if(producto.getIdProducto()!=-1)
            {
                gotoxy (54,renglon);
                cin>>cantidadProducto;

                gotoxy (66,renglon); cout<<"$"<<producto.getPrecioProducto();
                subtotal = cantidadProducto * producto.getPrecioProducto();
                gotoxy (82,renglon); cout<<"$"<<subtotal;

                venta.agregarProductoALaVenta(codigoProducto,cantidadProducto);
                gotoxy (87,22); cout<<"$"<<venta.getConsumoTotal();

                renglon++;
            }
            else{
                renglon++; //para que baje un renglon y pida un nuevo codigo de prod
            }

            gotoxy (3,renglon);
            cin>>codigoProducto;
        }
        gotoxy (4,renglon+1); cout<<" - - - FIN DE CARGA DE PRODUCTOS - - - ";
        gotoxy (3,24); cout<<"1 - CONFIRMAR                ";
        gotoxy (25,24); cout<<"2 - SALIR / MENU PRINCIPAL";
        gotoxy (4,22); cout<<"INGRESE UNA OPCION: ";
        cin>>opcion;

        switch (opcion)
        {
        case 1:
            venta.grabarEnDisco();
            gotoxy (4,22); cout<<"VENTA REGISTRADA                        ";
            gotoxy (3,24); cout<<"PRESIONE CUALQUIER TECLA PARA CONTINUAR...                               ";
            getch();
            menuPrincipal(idVendedor);
            break;

        case 2:
            menuPrincipal(idVendedor);
            break;

        default:
            gotoxy (4,22); cout<<"INGRESE UNA OPCION CORRECTA";
            break;
        }

        gotoxy (2,22);
        cin.ignore();
        anykey();

    }while(_opcion!=0);
    return 0;
}

int Pantalla::menuConsumoMesa(int idVendedor)
{
    do{
        Venta venta;
        Transaccion transaccion;
        Producto producto;

        int pos1=0, pos2=0;

        int opcion, renglon = 8, mesaAux = -1;
        float total = 0, subtotal = 0;

        cls();
        system("mode con: cols=100 lines=26"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
        system("COLOR 71"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS
        dibujarCuadro(0,0,98,25); //SE DIBUJA EL CUADRO PRINCIPAL
        dibujarCuadro(1,1,97,3); //SE DIBUJA EL CUADRO DEL TITULO
        gotoxy(39,2); cout<<"DELTAPOINT RESTO";

        dibujarCuadroDoble(2,4,96,6,23);
        gotoxy (4,5); cout<<"MESA: ";
        cin>> mesaAux;

        gotoxy (3,renglon-1); cout<<"CODIGO";
        gotoxy (18,renglon-1); cout<<"NOMBRE PRODUCTO";
        gotoxy (50,renglon-1); cout<<"CANTIDAD";
        gotoxy (66,renglon-1); cout<<"PRECIO";
        gotoxy (82,renglon-1); cout<<"SUBTOTAL";
        gotoxy (3,24); cout<<"0 - FIN DE CARGA DE PRODUCTOS";

        gotoxy (80,22); cout<<"TOTAL: ";

        while(venta.leerDeDisco(pos1++)>0)
        {
            venta.getIdMesa();
            if(venta.getIdMesa() == mesaAux)
            {
                while(transaccion.leerDeDisco(pos2++))
                {
                    if(transaccion.getIdOperacionAsociada() == venta.getIDventa())
                    {
                        gotoxy (3,renglon); cout<<transaccion.getIdProducto();
                        producto = buscarPorCodigo(transaccion.getIdProducto());
                        gotoxy (15,renglon); cout<<producto.getNombreProducto();
                        gotoxy (54,renglon); cout<<transaccion.getCantidad();
                        gotoxy (66,renglon); cout<<"$"<<transaccion.getPrecio();
                        subtotal = transaccion.getCantidad() * transaccion.getPrecio();
                        gotoxy (82,renglon); cout<<"$"<<subtotal;
                        total+= subtotal;
                        venta.setConsumoTotal(total);
                        gotoxy (87,22);  cout<<"$"<<total;

                        renglon++;
                    }
                }
            }
        }

        gotoxy (3,24); cout<<"1 - VOLVER AL MENU ANTERIOR               ";
        gotoxy (4,22); cout<<"INGRESE UNA OPCION: ";
        cin>>opcion;

        switch (opcion)
        {
        case 1:
            menuVenta(idVendedor);
        default:
            gotoxy (4,22); cout<<"INGRESE UNA OPCION CORRECTA";
            break;
        }

        gotoxy (2,22);
        cin.ignore();
        anykey();

    }while(_opcion!=0);
    return 0;
}
