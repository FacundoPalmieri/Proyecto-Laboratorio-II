using namespace std;
#include "rlutil.h"
#include "colors.h"
#include "Pantalla.h"
#include "Menu.h"
#include "Producto.h"
#include "Venta.h"
#include "Empleado.h"
#include "ArchivoEmpleado.h"
#include "ArchivoVenta.h"
#include "ArchivoProducto.h"
#include "ArchivoTransaccion.h"


void  Menu::menuIdVendedor(){


    int IntentosUsuario = 3;
    do{
        Pantalla pantalla;
        Empleado empleado;
        ArchivoEmpleado archivoEmpleado("empleados.dat");

        int idEmpleado=-1, posEmpleado=-1;
        char password[20] = {};

        pantalla.estiloMenu();


        pantalla.cursor (25,6);  cout<<"INGRESO AL SISTEMA";
        pantalla.cursor (20,7);  cout<<"--------------------------------";
        pantalla.cursor (22,10); cout<<"INGRESE SU ID DE VENDEDOR: ";
        cin>>idEmpleado;

        for(int x=0; x<archivoEmpleado.cantidadEnArchivo();x++){
            empleado = archivoEmpleado.leerDeDisco(x);

            if(empleado.getIdEmpleado()==idEmpleado&&empleado.getEstado()==true){
               posEmpleado = x; //  almacenar la posición del empleado encontrado antes de que posEmpleado sea incrementada nuevamente
               pantalla.cursor (22,11); cout<<"- ("<<empleado.getApellido()<<", "<<empleado.getNombre()<<")"; // - PSW:"<<empleadoAux.getPassword();
            }
        }

        if(posEmpleado!=-1){
            empleado=archivoEmpleado.leerDeDisco(posEmpleado);
            int IntentosClave = 3;

            for(int i = 0; i<3; i++){
                pantalla.cursor (22,13); cout<< BLUE <<"INGRESE SU CLAVE: ";
                cin>>password;
                IntentosClave --;

                if(strcmp(empleado.getPassword(),password)==0){
                  menuPrincipal(empleado.getIdEmpleado()); // Si coinciden las contraseñas ingresa al método menuPrincipal, pasando como parametros el ID)
                }
                else{
                    pantalla.cursor (26,16); cout<< RED <<" CLAVE INCORRECTA" << endl;
                    if(IntentosClave == 0){
                        pantalla.cursor (18,18);cout << " Ups, Ha alcanzado el limite de intentos " << endl;
                        pantalla.cursor (2,19);cout << " Comuniquese con el area de sistemas para solicitar un blanqueo de clave. " << endl;
                        cout << BLUE;
                        pantalla.cursor (1,23); system("pause");
                        FinalizarPrograma();
                    }
                    pantalla.cursor (22,17); cout<< RED <<" - Le quedan " << IntentosClave << " intentos - " << endl;
                    cout << BLUE;
                    pantalla.cursor (1,23); system("pause");
                    pantalla.cursor (26,16); cout << "                                       " << endl; // Limpia la menu en la parte posterior al ingreso de clave
                    pantalla.cursor (22,17); cout << "                                       " << endl;
                    pantalla.cursor (1,23);  cout << "                                       " <<endl;
                    pantalla.cursor (38,13); cout << "                                       " <<endl;

                }

            }
        }
        else{
            pantalla.cursor (24,13); cout<< RED <<"USUARIO NO ENCONTRADO ";
            IntentosUsuario--;
            if(IntentosUsuario == 0){
                pantalla.cursor (18,18);cout << " Ha alcanzado el limite de intentos " << endl;
                cout << BLUE;
                pantalla.cursor (1,23); system("pause");
                FinalizarPrograma();
            }
            pantalla.cursor (22,17); cout<< RED <<" - Le quedan " << IntentosUsuario << " intentos - " << endl;
            cout << BLUE;
            pantalla.cursor (1,23); system("pause");
        }


    }while(IntentosUsuario>0);

}

void Menu::menuPrincipal(int idVendedor)
{
    Pantalla pantalla;
    do
    {
        pantalla.estiloMenu();

        pantalla.cursor (2,6); cout<<"MENU PRINCIPAL";
        pantalla.cursor (2,7); cout<<"------------------";
        pantalla.cursor (2,10); cout<<"INGRESE UNA OPCION: ";

        pantalla.cursor (2,13); cout<<"1 - MENU VENTA ";
        pantalla.cursor (2,14); cout<<"2 - MENU CONSULTA ";
        pantalla.cursor (2,15); cout<<"3 - MENU AJUSTES ";
        pantalla.cursor (2,16); cout<<"4 - CERRAR SESION DE USUARIO ";
        pantalla.cursor (2,17); cout<<"0 - SALIR DEL PROGRAMA ";

        pantalla.cursor (2,19); cout<<"->: ";
        cin>>_opcion;

        switch (_opcion)
        {
        case '1':
            menuVenta(idVendedor);
            break;
        case '2':
            menuConsulta(idVendedor);
            break;
        case '3':
            menuAjuste(idVendedor);
            break;
        case '4':
            menuIdVendedor();
            break;
        case '0':
            FinalizarPrograma();
            break;

        default:
            OpcionIncorrecta();
            break;

        }

    }
    while(_opcion!=0);
}

void  Menu::menuVenta(int idVendedor)
{
    Pantalla pantalla;

    do{
        pantalla.estiloMenu();

        pantalla.cursor (2,6); cout<<"MENU VENTA";
        pantalla.cursor (2,7); cout<<"------------------";
        pantalla.cursor (2,10); cout<<"INGRESE UNA OPCION: ";

        pantalla.cursor (2,13); cout<<"1 - ATENDER CLIENTE: ";
        pantalla.cursor (2,14); cout<<"2 - CONSUMO DE MESA: ";
        pantalla.cursor (2,15); cout<<"3 - VOLVER AL MENU PRINCIPAL: ";
        pantalla.cursor (2,16); cout<<"0 - SALIR DEL PROGRAMA: ";

        pantalla.cursor (2,18); cout<<"->: ";
        cin>>_opcion;

        switch (_opcion)
        {
        case '1':
            menuPedido(idVendedor);
            break;
        case '2':
            menuConsumoMesa(idVendedor);
            break;

        case '3':
            menuPrincipal(idVendedor);
            break;
        case '0':
            FinalizarPrograma();
            break;

        default:
            OpcionIncorrecta();
            break;
        }

    }while(_opcion!=0);

}

void  Menu::menuConsulta(int idVendedor)
{
    Pantalla pantalla;

    do{
        pantalla.estiloMenu();

        pantalla.cursor (2,6); cout<<"MENU CONSULTA";
        pantalla.cursor (2,7); cout<<"------------------";
        pantalla.cursor (2,10); cout<<"INGRESE UNA OPCION ";

        pantalla.cursor (2,13); cout<<"1 - LISTADOS ";
        pantalla.cursor (2,14); cout<<"2 - CONSULTA DE VENTAS ";
        pantalla.cursor (2,15); cout<<"3 - VOLVER AL MENU PRINCIPAL ";
        pantalla.cursor (2,16); cout<<"0 - SALIR DEL PROGRAMA ";

        pantalla.cursor (2,19);
        cout<<"->: ";
        cin>>_opcion;
        switch (_opcion)
        {
        case '1':
            menuListados(idVendedor);
            break;
        case '2':
            menuConsultasDeVentas(idVendedor);
            break;
        case '3':
            menuPrincipal(idVendedor);
            break;
        case '0':
            FinalizarPrograma();
            break;

        default:
           OpcionIncorrecta();
            break;
        }



    }while(_opcion!=0);
}

void  Menu::menuListados(int idVendedor)
{
 do{
        Pantalla pantalla;

        pantalla.estiloMenu();

        pantalla.cursor (2,6); cout << "MENU LISTADOS";
        pantalla.cursor (2,7); cout << "------------------";
        pantalla.cursor (2,10); cout << "INGRESE UNA OPCION: ";

        pantalla.cursor (2,13); cout << "1 - PRODUCTOS ";
        pantalla.cursor (2,14); cout << "2 - EMPLEADOS ";
        pantalla.cursor (2,15); cout << "3 - VOLVER AL MENU ANTERIOR ";
        pantalla.cursor (2,16); cout << "0 - SALIR DEL PROGRAMA ";

        pantalla.cursor (2,19); cout << "->: ";
        cin >> _opcion;

        switch (_opcion)
        {
            case '1':
                vistaListadoProductos(idVendedor);
                break;
            case '2':
                vistaListadoEmpleados(idVendedor);
                break;
            case '3':
                menuConsulta(idVendedor);
                break;
            case '0':
                FinalizarPrograma();

            default:
                OpcionIncorrecta();
                break;
        }


    }while(_opcion!=0);
}

void Menu::vistaListadoProductos(int idVendedor) {
    Pantalla pantalla;
    Producto producto;
    ArchivoProducto archivoProducto("productos.dat");
    int renglon, maximo = 0;

    archivoProducto.Ordenar();

    pantalla.estiloMenu();

    pantalla.cursor(2, 6);
    cout << "LISTA DE PRODUCTOS:";
    pantalla.cursor(2, 7);
    cout << "--------------------";

    renglon = 8;

    maximo = archivoProducto.cantidadEnArchivo();
    pantalla.cursor(5, renglon); cout <<"ID";
    pantalla.cursor(13, renglon);cout << "PRODUCTO";
    pantalla.cursor(36, renglon);cout << "PRECIO UNITARIO";
    renglon++;
    renglon++;

    for (int i = 0; i < maximo; i++) {
        producto=archivoProducto.leerDeDisco(i);

        if (producto.getEstado() == true) {

            pantalla.cursor(5, renglon);
            cout << producto.getIdProducto();
            pantalla.cursor(13, renglon);
            cout << producto.getNombreProducto();
            pantalla.cursor(36, renglon);
            cout << "$" << producto.getPrecioProducto();
            renglon++;
        }
    }

    pantalla.cursor(2, 23);
    cout << system("pause");
}




void Menu::vistaListadoEmpleados(int idVendedor)
{
    Pantalla pantalla;
    Empleado empleado;
    ArchivoEmpleado archivoEmpleado("empleados.dat");
    int renglon=8, maximo=0;

    pantalla.estiloMenu();

    archivoEmpleado.Ordenar();

    pantalla.cursor (2,6); cout<<"LISTA DE EMPLEADOS:";
    pantalla.cursor (2,7); cout<<"--------------------";

    maximo = archivoEmpleado.cantidadEnArchivo();

    pantalla.cursor (5,renglon);  cout<<"ID";
    pantalla.cursor (13,renglon); cout<<" APELLIDO Y NOMBRE";
    pantalla.cursor (39,renglon); cout<<" DNI";
    renglon++;
    renglon++;
    for (int i = 0; i < maximo; i++) {
        empleado=archivoEmpleado.leerDeDisco(i);

        if (empleado.getEstado() == true) {
            pantalla.cursor (5,renglon); cout<<empleado.getIdEmpleado();
            pantalla.cursor (14,renglon); cout<<empleado.getApellido()<<", "<<empleado.getNombre();
            pantalla.cursor (40,renglon); cout<<empleado.getDNI();
            renglon++;
        }

    }

    pantalla.cursor (2,23); cout<< system("pause");

}

void
 Menu::menuConsultasDeVentas(int idVendedor)
{
    Pantalla pantalla;
    do{
        pantalla.estiloMenu();

        pantalla.cursor (2,6); cout<<"MENU CONSULTA DE VENTAS";
        pantalla.cursor (2,7); cout<<"------------------";
        pantalla.cursor (2,10); cout<<"INGRESE UNA OPCION: ";

        pantalla.cursor (2,13); cout<<"1 - VENTAS TOTALES POR MES ";
        pantalla.cursor (2,14); cout<<"2 - VENTAS POR EMPLEADO ";
        pantalla.cursor (2,15); cout<<"3 - VENTAS POR PRODUCTO ";
        pantalla.cursor (2,16); cout<<"4 - VOLVER AL MENU ANTERIOR ";
        pantalla.cursor (2,17); cout<<"0 - SALIR DEL PROGRAMA ";

        pantalla.cursor (2,19); cout<<"->: ";
        cin>>_opcion;
        switch (_opcion)
        {
        case '1':
            vistaVentasPorMes(idVendedor);
            break;
        case '2':
            vistaVentasPorEmpleado(idVendedor);
            break;
        case '3':
            vistaVentasPorProducto(idVendedor);
            break;
        case '4':
            menuConsulta(idVendedor);
            break;
        case '0':
            FinalizarPrograma();
            break;

        default:
           OpcionIncorrecta();
           break;
        }

    }while(_opcion!=0);
}

void Menu::vistaVentasPorMes(int idVendedor)
{

    Pantalla pantalla;
    Venta venta;
    ArchivoVenta archivoVenta("ventas.dat");

    float consumoTotal=0;
    int Anioregistro=0;

    pantalla.estiloMenu();

    pantalla.cursor (2,4); cout<<"VENTAS POR MES:";
    pantalla.cursor (2,5); cout<<"--------------------";

    int cantidad = archivoVenta.cantidadVentas();
    int renglonMes=9;
    char Opcion;

    pantalla.cursor (2,7); cout<<"REGISTRO 2023: ";

    for(int mes=1; mes<13; mes++){
        pantalla.cursor (2,renglonMes++); cout<<"MES: "<<mes;
        consumoTotal = 0;

        for(int indice=0; indice<cantidad; indice++){
            venta=archivoVenta.leerDeDisco(indice);

            if(venta.getFecha().getAnio()==2023 && venta.getFecha().getMes()== mes){
                consumoTotal += venta.getConsumoTotal();

            }
        }
        pantalla.cursor (20,renglonMes-1); cout<<"$ "<<consumoTotal;

    }

    pantalla.cursor (2,23); cout << "1- Registros previos / 2 - Volver :";
    pantalla.cursor (38,23);cin >> Opcion;

    switch(Opcion)
    {
    case '1':
        system("cls");

        renglonMes=6;
        consumoTotal=0;

        pantalla.estiloMenu();
        pantalla.cursor (2,4); cout<<"INGRESE PERIODO ANUAL A CONSULTAR: ";
        cin>>Anioregistro;
        pantalla.cursor (2,5); cout<<"--------------------";

        for(int mes=1; mes<13; mes++){
            pantalla.cursor (2,renglonMes++); cout<<"MES: "<<mes;
            consumoTotal = 0;

            for(int indice=0; indice<cantidad; indice++){
                venta=archivoVenta.leerDeDisco(indice);

                if(venta.getFecha().getAnio()==Anioregistro && venta.getFecha().getMes()==mes){
                    consumoTotal += venta.getConsumoTotal();
                }
            }

            pantalla.cursor (20,renglonMes-1); cout<<"$ "<<consumoTotal;
        }
        pantalla.cursor (2,23); system("pause");

        break;

    case '2':
        menuConsultasDeVentas(idVendedor);
        break;

    default:
       OpcionIncorrecta();
       break;

    }

}

void Menu::vistaVentasPorEmpleado(int idVendedor)
{
    Pantalla pantalla;
    Venta venta;
    Empleado empleado;
    ArchivoEmpleado archivoEmpleado("empleados.dat");
    ArchivoVenta archivoVenta("ventas.dat");

    int renglon = 8;
    float consumoTotal=0;

    pantalla.estiloMenu();

    pantalla.cursor (2,4); cout<<"VENTAS POR EMPLEADO:";
    pantalla.cursor (2,5); cout<<"--------------------";

    for(int id=0; id<archivoEmpleado.cantidadEnArchivo(); id++){

        empleado = archivoEmpleado.leerDeDisco(id);
        consumoTotal=0;

        if(empleado.getEstado()==true){

            pantalla.cursor(2,renglon);
            cout<<empleado.getNombre()<<" "<<empleado.getApellido();

            for (int x=0; x<archivoVenta.cantidadVentas();x++){
                venta=archivoVenta.leerDeDisco(x);

                if(venta.getIdVendedor()==empleado.getIdEmpleado()){
                    consumoTotal+=venta.getConsumoTotal();
                }

            }

            pantalla.cursor(25,renglon); cout<<"$ "<<consumoTotal;
            renglon++;
        }

    }

    pantalla.cursor (2,23); cout << system("pause");

}

void Menu::vistaVentasPorProducto(int idVendedor)
{
    Pantalla pantalla;
    Transaccion transaccion;
    Producto producto;
    ArchivoProducto archivoProducto("productos.dat");
    ArchivoTransaccion archivoTransaccion("transacciones.dat");

    int renglon = 8;
    float consumoTotal;

    pantalla.estiloMenu();

    pantalla.cursor (2,4); cout<<"VENTAS POR PRODUCTO:";
    pantalla.cursor (2,5); cout<<"--------------------";

    for (int x=0; x<archivoProducto.cantidadEnArchivo();x++){
        consumoTotal=0;
        producto=archivoProducto.leerDeDisco(x);

        if (producto.getEstado()==true){
            pantalla.cursor(2,renglon); cout<<producto.getNombreProducto();

            for (int x=0; x<archivoTransaccion.cantidadTransacciones();x++){
                transaccion=archivoTransaccion.leerDeDisco(x);

                if(transaccion.getIdProducto()==producto.getIdProducto()){
                    consumoTotal+=(transaccion.getPrecio()*transaccion.getCantidad());
                }
            }
            pantalla.cursor(35,renglon); cout<<"$ "<<consumoTotal;
            renglon++;
        }
    }

    pantalla.cursor (2,22); cout << system("pause");
}

void Menu::menuAjuste(int idVendedor)
{
    do{
        Pantalla pantalla;
        Producto producto;
        Empleado empleado;
        ArchivoEmpleado archivoEmpleado("empleados.dat");
        ArchivoProducto archivoProducto("productos.dat");
        char opcion;

        pantalla.estiloMenu();

        pantalla.cursor (2,6); cout<<"MENU AJUSTE";
        pantalla.cursor (2,7); cout<<"------------------";
        pantalla.cursor (2,9); cout<<"INGRESE UNA OPCION: ";

        pantalla.cursor (2,11); cout<<"1 - CARGAR PRODUCTO ";
        pantalla.cursor (2,12); cout<<"2 - MODIFICAR PRODUCTO ";
        pantalla.cursor (2,13); cout<<"3 - DAR DE BAJA PRODUCTO ";
        pantalla.cursor (2,14); cout<<"4 - CARGAR EMPLEADO ";
        pantalla.cursor (2,15); cout<<"5 - MODIFICAR EMPLEADO ";
        pantalla.cursor (2,16); cout<<"6 - DAR DE BAJA EMPLEADO ";
        pantalla.cursor (2,17); cout<<"7 - VOLVER AL MENU PRINCIPAL ";
        pantalla.cursor (2,18); cout<<"0 - SALIR DEL PROGRAMA ";

        pantalla.cursor (2,20); cout<<"->: ";
        cin>>opcion;

        switch (opcion)
        {
        case '1':
            pantalla.estiloMenu();
            pantalla.cursor (2,9);
            if(producto.cargar()!= -1){
                pantalla.cursor (2,15);
                archivoProducto.grabarEnDisco(producto);
            }
            pantalla.cursor (2,23);
            system("pause");
            menuAjuste(idVendedor);
            break;
        case '2':
            pantalla.estiloMenu();
            pantalla.cursor (2,12);
            archivoProducto.modificarRegistro();
            menuAjuste(idVendedor);
            break;

        case '3':
            pantalla.estiloMenu();
            pantalla.cursor (2,12);
            archivoProducto.bajaProducto();
            menuAjuste(idVendedor);
            break;
        case '4':
            pantalla.estiloMenu();
            pantalla.cursor (2,12);
            if(empleado.cargarEmpleado()!= -1){
                if(archivoEmpleado.grabarEnDisco(empleado)==0){
                    archivoEmpleado.MensajeError();
                }
            }
            menuAjuste(idVendedor);
            break;
        case '5':
            pantalla.estiloMenu();
            archivoEmpleado.modificarRegistro();
            menuAjuste(idVendedor);
            break;
        case '6':
            pantalla.estiloMenu();
            archivoEmpleado.bajaEmpleado();
            menuAjuste(idVendedor);
            break;
        case '7':
            menuPrincipal(idVendedor);
            break;
        case '0':
            FinalizarPrograma();
            break;

        default:
            OpcionIncorrecta();
            break;
        }

    }while(_opcion!=0);

}

void Menu::menuPedido(int idVendedor)
{

    Pantalla pantalla;
    Venta venta;
    Producto producto;
    ArchivoVenta archivoVenta("ventas.dat");
    ArchivoProducto archivoProducto("productos.dat");

    char opcion;
    int renglon = 8, codigoProducto = 0, cantidadProducto = 0, mesa = -1;
    float subtotal = 0;

    system("cls");
    system("mode con: cols=100 lines=26"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
    system("COLOR 71"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS
    pantalla.dibujarCuadro(0,0,98,25); //SE DIBUJA EL CUADRO PRINCIPAL
    pantalla.dibujarCuadro(1,1,97,3); //SE DIBUJA EL CUADRO DEL TITULO
    pantalla.cursor(39,2); cout<<"DELTAPOINT RESTO";

    pantalla.dibujarCuadroDoble(2,4,96,6,23);

    pantalla.dibujarCuadroDoble(2,4,96,6,23);
    pantalla.cursor (4,5);

    cout<<"MESA: ";
    cin>> mesa;

    venta.setMesa(mesa);
    venta.setVendedor(idVendedor);

    pantalla.cursor (3,renglon-1); cout<<"CODIGO";
    pantalla.cursor (18,renglon-1);cout<<"NOMBRE PRODUCTO";
    pantalla.cursor (50,renglon-1);cout<<"CANTIDAD";
    pantalla.cursor (66,renglon-1);cout<<"PRECIO";
    pantalla.cursor (82,renglon-1);cout<<"SUBTOTAL";
    pantalla.cursor (3,24); cout<<"0 - FIN DE CARGA DE PRODUCTOS  ";

    pantalla.cursor (3,renglon);
    cin>>codigoProducto;
    pantalla.cursor (80,22); cout<<"TOTAL: ";

    while(codigoProducto>0)
    {
        producto = archivoProducto.buscarPorCodigo(codigoProducto);
        pantalla.cursor (15,renglon); cout<<producto.getNombreProducto();

        if(producto.getIdProducto()!=-1)
        {
            pantalla.cursor (54,renglon);
            cin>>cantidadProducto;

            pantalla.cursor (66,renglon); cout<<"$"<<producto.getPrecioProducto();
            subtotal = cantidadProducto * producto.getPrecioProducto();
            pantalla.cursor (82,renglon); cout<<"$"<<subtotal;

            if(venta.agregarProductoALaVenta(codigoProducto,cantidadProducto) != -1){//GRABAMOS EN ARCHIVO TRANSACCIÓN
                pantalla.cursor (87,22); cout<<"$"<<venta.getConsumoTotal(); //EN EL MÉTODO ANTERIOR SE SUMÓ EL IMPORTE

                renglon++;
            }
            else{
                cout << RED;
                pantalla.cursor (3,renglon+1);cout << "No se pudo cargar la venta. " ;
                cout << BLUE;
                renglon++;
                renglon++;

            }
        }
        else{
            renglon++; // SI no encontró el producto se baja un renglon y pida un nuevo codigo de prod
        }

        pantalla.cursor (3,renglon);
        cin>>codigoProducto;
    }
    pantalla.cursor (4,renglon+1); cout<<" - - - FIN DE CARGA DE PRODUCTOS - - - ";

    do{
        pantalla.cursor (3,24) ;  cout <<"1 - CONFIRMAR                ";
        pantalla.cursor (25,24);  cout <<"2 - SALIR / MENU PRINCIPAL";
        pantalla.cursor (4,22) ;  cout <<"INGRESE UNA OPCION: ";
        cin>>opcion;
        switch (opcion)
        {
        case '1':
            archivoVenta.grabarEnDisco(venta); ////GRABAMOS EN ARCHIVO VENTA
            cout << GREEN;
            pantalla.cursor (4,22); cout<<"VENTA REGISTRADA                        ";
            pantalla.cursor (35,24); cout << "                                                      " << endl;
            cout << BLUE;
            pantalla.cursor (3,24); system("pause");
            menuVenta(idVendedor);
            break;

        case '2':
            menuPrincipal(idVendedor);
            break;

        default:
            cout << RED;
            pantalla.cursor (4,22);  cout << "Opcion Incorrecta                                      " << endl;
            cout << BLUE;
            pantalla.cursor (35,24); cout << "                                                      " << endl;
            pantalla.cursor (3,24);  system("pause");
            pantalla.cursor (4,22);  cout << "                                                     " << endl;
            pantalla.cursor (25,24); cout << "                                                     " << endl;
            pantalla.cursor (4,22);  cout  <<"INGRESE UNA OPCION: ";
            break;
        }

    }while (opcion != 1 || opcion != 2);
}

void Menu::menuConsumoMesa(int idVendedor)
{
    system("cls");
    Pantalla pantalla;
    Transaccion transaccion;
    Producto producto;

    ArchivoProducto archivoProducto("productos.dat");
    ArchivoTransaccion archivoTransaccion("transacciones.dat");

    char Opcion;
    int renglon = 8, mesa = -1;
    float total = 0, subtotal = 0;

    system("cls");
    system("mode con: cols=100 lines=26"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
    system("COLOR 71"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS
    pantalla.dibujarCuadro(0,0,98,25); //SE DIBUJA EL CUADRO PRINCIPAL
    pantalla.dibujarCuadro(1,1,97,3); //SE DIBUJA EL CUADRO DEL TITULO
    pantalla.cursor(39,2); cout<<"DELTAPOINT RESTO";

    pantalla.dibujarCuadroDoble(2,4,96,6,23);

    pantalla.cursor (4,5); cout<<"MESA: ";
    cin>> mesa;

    pantalla.cursor (3,renglon-1);  cout<<"CODIGO";
    pantalla.cursor (18,renglon-1); cout<<"NOMBRE PRODUCTO";
    pantalla.cursor (50,renglon-1); cout<<"CANTIDAD";
    pantalla.cursor (66,renglon-1); cout<<"PRECIO";
    pantalla.cursor (82,renglon-1); cout<<"SUBTOTAL";
    pantalla.cursor (80,22);        cout<<"TOTAL: ";


    for (int x=0; x<archivoTransaccion.cantidadTransacciones();x++) //RECORREMOS ARCHIVO TRANSACCIÓN
    {
        transaccion=archivoTransaccion.leerDeDisco(x); //LEE

        if(transaccion.getIdMesa() == mesa && transaccion.getEstado()==2) //FILTRA SI COINCIDE VENTA Y TRANSACCIÓN EN EL ID MESA
        {
            pantalla.cursor (4,renglon); cout<<transaccion.getIdProducto();
            producto = archivoProducto.buscarPorCodigo(transaccion.getIdProducto());
            pantalla.cursor (19,renglon); cout<<producto.getNombreProducto();
            pantalla.cursor (54,renglon); cout<<transaccion.getCantidad();
            pantalla.cursor (66,renglon); cout<<"$"<<transaccion.getPrecio();
            subtotal = transaccion.getCantidad() * transaccion.getPrecio();
            pantalla.cursor (82,renglon); cout<<"$"<<subtotal;
            total+= subtotal;
            pantalla.cursor (87,22);  cout<<"$"<<total;

            renglon++;
        }
    }

    do{

        pantalla.cursor (3,24); cout << "1- Cerrar mesa / 2 - Volver :";
        pantalla.cursor (33,24);cin >> Opcion;
        switch(Opcion){
         case '1':
            char OpcionConfirmacion;
            do{
                pantalla.cursor (3,24); cout << " Esta seguro/a que desea cerrar la mesa? (S/N): ";
                cin >> OpcionConfirmacion;
                if(OpcionConfirmacion == 's' || OpcionConfirmacion == 'S'){
                    if(transaccion.cerrarMesa(mesa)!=0){

                        pantalla.cursor (4,24);
                        pantalla.cursor (3,24);  cout << "                                                 ";
                        cout << GREEN;
                        pantalla.cursor (3,24); cout<<"MESA CERRADA - Imprimiendo Ticket..."<<endl;
                        cout << BLUE;
                        Sleep(3000);

                        pantalla.cursor (80,22); cout<<"TOTAL: "<<total;
                        pantalla.cursor (2,24); cout<< system("pause") ;
                        break;
                    }
                    else{
                        cout << RED;
                        pantalla.cursor (4,22);  cout << "La mesa ya se encuentra cerrada " << endl;
                        cout << BLUE;
                        pantalla.cursor (15,24); cout << "                                                     " << endl;
                        pantalla.cursor (3,24); system("pause");
                        pantalla.cursor (4,22);  cout << "                                                     " << endl;
                        pantalla.cursor (25,24); cout << "                                                     " << endl;
                        break;

                    }
                }
                else{
                    if(OpcionConfirmacion == 'n' || OpcionConfirmacion == 'N'){
                        break;
                    }
                    else{
                        cout << RED;
                        pantalla.cursor (4,22);  cout << "Opcion Incorrecta                                      " << endl;
                        cout << BLUE;
                        pantalla.cursor (35,24); cout << "                                                      " << endl;
                        pantalla.cursor (3,24);  system("pause");
                        pantalla.cursor (4,22);  cout << "                                                     " << endl;
                        pantalla.cursor (25,24); cout << "                                                     " << endl;
                    }
                }

            }while(OpcionConfirmacion != 's' || OpcionConfirmacion != 'S' || OpcionConfirmacion!='n' || OpcionConfirmacion!='N');
         case '2':
            menuVenta(idVendedor);
            break;

         default:
            cout << RED;
            pantalla.cursor (4,22);  cout << "Opcion Incorrecta                                      " << endl;
            cout << BLUE;
            pantalla.cursor (35,24); cout << "                                                      " << endl;
            pantalla.cursor (3,24);  system("pause");
            pantalla.cursor (4,22);  cout << "                                                     " << endl;
            pantalla.cursor (25,24); cout << "                                                     " << endl;
        }
    }while (Opcion != 1 || Opcion !=2);


}


void Menu::FinalizarPrograma(){
    system("cls");
    Pantalla pantalla;

    pantalla.dibujarCuadro(0,0,79,24);
    pantalla.dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
    pantalla.cursor(30,2); cout<<"DELTAPOINT RESTO";
    pantalla.cursor(17,5);
    cout << " Gracias por utilizar nuestro programa \1" << endl << endl << endl << endl << endl ;
    exit(0);
}


void Menu:: OpcionIncorrecta(){
    Pantalla pantalla;

    cout << RED;
    pantalla.cursor (2,22);cout << "Opcion Incorrecta " << endl;
    cout << BLUE;
    pantalla.cursor (2,23); system("pause");

}

