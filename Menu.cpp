#define XSCREEN 78
#define YSCREEN 24

using namespace std;
#include "rlutil.h"
#include "colors.h"
#include "Pantalla.h"
#include "Menu.h"
#include "Producto.h"
#include "Venta.h"
#include "Empleado.h"
#include "ArchivoEmpleado.h"

void Menu::FinalizarPrograma(){
    system("cls");
    Pantalla pantalla;

    pantalla.dibujarCuadro(0,0,79,24);
    pantalla.dibujarCuadro(1,1,(XSCREEN-1),3); //SE DIBUJA EL CUADRO DEL TITULO
    pantalla.dimensiones(30,2); cout<<"DELTAPOINT RESTO";
    pantalla.dimensiones(17,5);
    cout << " Gracias por utilizar nuestro programa :)" << endl << endl << endl << endl << endl ;
    exit(0);
}


void Menu:: OpcionIncorrecta(){
    Pantalla pantalla;

    cout << RED;
    pantalla.dimensiones (2,22);cout << "Opcion Incorrecta " << endl;
    cout << BLUE;
    pantalla.dimensiones (2,23); system("pause");

}


int Menu::menuIdVendedor(){


    int IntentosUsuario = 3;
    do{
        Pantalla pantalla;
        Empleado empleadoAux;
        ArchivoEmpleado archivoEmpleado("empleados.dat");
        int idEmpleado=-1, pos, posAux;
        int password=-1;

        pantalla.estiloMenu();

        pantalla.dimensiones (25,6);  cout<<"INGRESO AL SISTEMA";
        pantalla.dimensiones (20,7);  cout<<"--------------------------------";
        pantalla.dimensiones (22,10); cout<<"INGRESE SU ID DE VENDEDOR: ";
        cin>>idEmpleado;

        pos=0;
        posAux=-1;
        while(pos < archivoEmpleado.cantidadEnArchivo()){// Lee y aumenta la posici�n. Ingresa siempre que sea mayor a 0
            empleadoAux = archivoEmpleado.leerDeDisco(pos);
            pos++;
            if(empleadoAux.getIdEmpleado()==idEmpleado&&empleadoAux.getEstado()==true){
                posAux = pos-1; //  almacenar la posici�n del empleado encontrado antes de que pos sea incrementada nuevamente
               pantalla.dimensiones (22,11); cout<<"- ("<<empleadoAux.getApellido()<<", "<<empleadoAux.getNombre()<<")"; // - PSW:"<<empleadoAux.getPassword();
            }
        }

        if(posAux!=-1){
            archivoEmpleado.leerDeDisco(posAux);
            int IntentosClave = 3;

            for(int i = 0; i<3; i++){
                pantalla.dimensiones (2,12); cout<<"                                     ";
                pantalla.dimensiones (22,13); cout<< BLUE <<"INGRESE SU CLAVE: ";
                cin>>password;
                IntentosClave --;
                //cout<<"psw ingresado: "<<password<<", psw encontrado: "<<empleadoAux.getPassword();
                if(empleadoAux.getPassword()==password){
                  menuPrincipal(empleadoAux.getIdEmpleado()); // Si coinciden las contrase�as ingresa al m�todo menuPrincipal, pasando como parametros el ID)


                }
                else{
                    pantalla.dimensiones (26,16); cout<< RED <<" CLAVE INCORRECTA" << endl;
                    if(IntentosClave == 0){
                        pantalla.dimensiones (18,18);cout << " Ha alcanzado el limite de intentos " << endl;
                        cout << BLUE;
                        pantalla.dimensiones (1,23); system("pause");
                        FinalizarPrograma();
                    }
                    pantalla.dimensiones (22,17); cout<< RED <<" - Le quedan " << IntentosClave << " intentos - " << endl;
                    cout << BLUE;
                    pantalla.dimensiones (1,23); system("pause");
                    pantalla.dimensiones (26,16); cout << "                                       " << endl; // Limpia la menu en la parte posterior al ingreso de clave
                    pantalla.dimensiones (22,17); cout << "                                       " << endl;
                    pantalla.dimensiones (1,23);  cout << "                                       " <<endl;
                    pantalla.dimensiones (40,13); cout << "                                       " <<endl;

                }

            }
        }
        else{
            pantalla.dimensiones (24,13); cout<< RED <<"USUARIO NO ENCONTRADO ";
            IntentosUsuario--;
            if(IntentosUsuario == 0){
                pantalla.dimensiones (18,18);cout << " Ha alcanzado el limite de intentos " << endl;
                cout << BLUE;
                pantalla.dimensiones (1,23); system("pause");
                FinalizarPrograma();
            }
            pantalla.dimensiones (22,17); cout<< RED <<" - Le quedan " << IntentosUsuario << " intentos - " << endl;
            cout << BLUE;
            pantalla.dimensiones (1,23); system("pause");
        }


    }while(IntentosUsuario>0);
   return 0;
}

int Menu::menuPrincipal(int idVendedor)
{
    Pantalla pantalla;
    do
    {
        pantalla.estiloMenu();

        pantalla.dimensiones (2,6); cout<<"MENU PRINCIPAL";
        pantalla.dimensiones (2,7); cout<<"------------------";
        pantalla.dimensiones (2,10); cout<<"INGRESE UNA OPCION: ";

        pantalla.dimensiones (2,13); cout<<"1 - MENU VENTA ";
        pantalla.dimensiones (2,14); cout<<"2 - MENU CONSULTA ";
        pantalla.dimensiones (2,15); cout<<"3 - MENU AJUSTES ";
        pantalla.dimensiones (2,16); cout<<"4 - CERRAR SESION DE USUARIO ";
        pantalla.dimensiones (2,17); cout<<"0 - SALIR DEL PROGRAMA ";

        pantalla.dimensiones (2,19); cout<<"->: ";
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
            FinalizarPrograma();
            break;

        default:
            OpcionIncorrecta();
            break;

        }

    }
    while(_opcion!=0);
    return 0;
}

int Menu::menuVenta(int idVendedor)
{
    Pantalla pantalla;

    do{
        pantalla.estiloMenu();

        pantalla.dimensiones (2,6); cout<<"MENU VENTA";
        pantalla.dimensiones (2,7); cout<<"------------------";
        pantalla.dimensiones (2,10); cout<<"INGRESE UNA OPCION: ";

        pantalla.dimensiones (2,13); cout<<"1 - ATENDER CLIENTE: ";
        pantalla.dimensiones (2,14); cout<<"2 - CONSUMO DE MESA: ";
        pantalla.dimensiones (2,15); cout<<"3 - CERRAR MESA: ";
        pantalla.dimensiones (2,16); cout<<"4 - VOLVER AL MENU PRINCIPAL: ";
        pantalla.dimensiones (2,17); cout<<"0 - SALIR DEL PROGRAMA: ";

        pantalla.dimensiones (2,19); cout<<"->: ";
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
            cerrarMesa();
            break;
        case 4:
            menuPrincipal(idVendedor);
            break;
        case 0:
            FinalizarPrograma();
            break;

        default:
            OpcionIncorrecta();
            break;
        }

    }while(_opcion!=0);

    return 0;

}

int Menu::menuConsulta(int idVendedor)
{
    Pantalla pantalla;

    do{
        pantalla.estiloMenu();

        pantalla.dimensiones (2,6); cout<<"MENU CONSULTA";
        pantalla.dimensiones (2,7); cout<<"------------------";
        pantalla.dimensiones (2,10); cout<<"INGRESE UNA OPCION: ";

        pantalla.dimensiones (2,13); cout<<"1 - LISTADOS: ";
        pantalla.dimensiones (2,14); cout<<"2 - CONSULTA DE VENTAS: ";
        pantalla.dimensiones (2,15); cout<<"3 - VOLVER AL MENU PRINCIPAL: ";
        pantalla.dimensiones (2,16); cout<<"0 - SALIR DEL PROGRAMA: ";

        pantalla.dimensiones (2,19);
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
            FinalizarPrograma();
            break;

        default:
           OpcionIncorrecta();
            break;
        }



    }while(_opcion!=0);
    return 0;
}

int Menu::menuListados(int idVendedor)
{
 do{
        Pantalla pantalla;
        Empleado empleadoAux;
        Producto productoAux;

        pantalla.estiloMenu();

        pantalla.dimensiones (2,6); cout << "MENU LISTADOS";
        pantalla.dimensiones (2,7); cout << "------------------";
        pantalla.dimensiones (2,10); cout << "INGRESE UNA OPCION: ";

        pantalla.dimensiones (2,13); cout << "1 - PRODUCTOS ";
        pantalla.dimensiones (2,14); cout << "2 - EMPLEADOS ";
        pantalla.dimensiones (2,15); cout << "3 - VOLVER AL MENU PRINCIPAL ";
        pantalla.dimensiones (2,16); cout << "0 - SALIR DEL PROGRAMA ";

        pantalla.dimensiones (2,19); cout << "->: ";
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
                FinalizarPrograma();

            default:
                OpcionIncorrecta();
                break;
        }


    }while(_opcion!=0);
    return 0;
}

void Menu::vistaListadoProductos(int idVendedor) {
    Pantalla pantalla;
    Empleado empleadoAux;
    Producto productoAux;
    int renglon, maximo;

    pantalla.estiloMenu();

    pantalla.dimensiones(2, 6);
    cout << "LISTA DE PRODUCTOS:";
    pantalla.dimensiones(2, 7);
    cout << "--------------------";

    renglon = 8;
    maximo = 0;

    int* VecIdProductos = nullptr;

    for (int x = 0; x < productoAux.cantidadEnArchivo(); x++) {
        productoAux.leerDeDisco(x);
        if (productoAux.getIdProducto() > maximo) {
            maximo = productoAux.getIdProducto();
        }
    }

    VecIdProductos = new int[maximo];

    if (VecIdProductos != nullptr) {

        // ASIGNAR AL VECTOR EL ID DE CADA PRODUCTO, YA ORDENADO
        for (int i = 0; i < productoAux.cantidadEnArchivo(); i++) {
            productoAux.leerDeDisco(i);
            VecIdProductos[productoAux.getIdProducto()] = productoAux.getIdProducto();
        }

        for (int x = 0; x <= maximo; x++) {

            for (int i = 0; i < productoAux.cantidadEnArchivo(); i++) {
                productoAux.leerDeDisco(i);

                if (productoAux.getIdProducto() == VecIdProductos[x] && productoAux.getEstado() == true) {

                    pantalla.dimensiones(5, renglon);
                    cout << productoAux.getIdProducto();
                    pantalla.dimensiones(14, renglon);
                    cout << productoAux.getNombreProducto();
                    pantalla.dimensiones(60, renglon);
                    cout << "$" << productoAux.getPrecioProducto();
                    renglon++;
                }
            }
        }
    }
    else {
        cout << "NO SE PUDO ASIGNAR MEMORIA" << endl;
    }

    delete[] VecIdProductos;

    pantalla.dimensiones(2, 20);
    cout << system("pause");
}


void Menu::vistaListadoEmpleados(int idVendedor)
{
    Pantalla pantalla;
    Empleado empleadoAux;
    ArchivoEmpleado archivoEmpleado("empleados.dat");
    int renglon, maximo;

    pantalla.estiloMenu();

    pantalla.dimensiones (2,6); cout<<"LISTA DE EMPLEADOS:";
    pantalla.dimensiones (2,7); cout<<"--------------------";

    renglon = 8;
    maximo=0;

    int* VecIdEmpleados = nullptr;

    for (int x = 0; x < archivoEmpleado.cantidadEnArchivo(); x++) {
        archivoEmpleado.leerDeDisco(x);
        if (empleadoAux.getIdEmpleado() > maximo) {
            maximo = empleadoAux.getIdEmpleado();
        }
    }

    VecIdEmpleados = new int[maximo]; // Incrementar en 1 el tama�o del arreglo

    if (VecIdEmpleados != nullptr) {

        // ASIGNAR AL VECTOR EL ID DE CADA EMPLEADO, YA ORDENADO
        for (int i = 0; i < archivoEmpleado.cantidadEnArchivo(); i++) {
            archivoEmpleado.leerDeDisco(i);
            VecIdEmpleados[empleadoAux.getIdEmpleado()] = empleadoAux.getIdEmpleado();
        }

        for (int x = 0; x <= maximo; x++) {

            for (int i = 0; i < archivoEmpleado.cantidadEnArchivo(); i++) {
                archivoEmpleado.leerDeDisco(i);

                if (empleadoAux.getIdEmpleado() == VecIdEmpleados[x] && empleadoAux.getEstado() == true) {

                    pantalla.dimensiones (5,renglon); cout<<empleadoAux.getIdEmpleado();
                    pantalla.dimensiones (14,renglon); cout<<empleadoAux.getApellido()<<", "<<empleadoAux.getNombre();
                    pantalla.dimensiones (45,renglon); cout<<empleadoAux.getPassword();
                    renglon++;
                }
            }
        }
    }
    else {
        cout << "NO SE PUDO ASIGNAR MEMORIA" << endl;
    }

    delete[] VecIdEmpleados;

    pantalla.dimensiones (2,20); cout<< system("pause");

}

int Menu::menuConsultasDeVentas(int idVendedor)
{
    Pantalla pantalla;
    do{
        pantalla.estiloMenu();

        pantalla.dimensiones (2,6); cout<<"MENU CONSULTA DE VENTAS";
        pantalla.dimensiones (2,7); cout<<"------------------";
        pantalla.dimensiones (2,10); cout<<"INGRESE UNA OPCION: ";

        pantalla.dimensiones (2,13); cout<<"1 - VENTAS TOTALES POR MES ";
        pantalla.dimensiones (2,14); cout<<"2 - VENTAS POR EMPLEADO ";
        pantalla.dimensiones (2,15); cout<<"3 - VENTAS POR PRODUCTO ";
        pantalla.dimensiones (2,16); cout<<"4 - VOLVER AL MENU ANTERIOR ";
        pantalla.dimensiones (2,17); cout<<"0 - SALIR DEL PROGRAMA ";

        pantalla.dimensiones (2,19); cout<<"->: ";
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
            FinalizarPrograma();
            break;

        default:
           OpcionIncorrecta();
           break;
        }

    }while(_opcion!=0);
    return 0;
}

void Menu::vistaVentasPorMes(int idVendedor)
{
    Pantalla pantalla;
    Venta ventaAux;
    float consumoTotal;

    pantalla.estiloMenu();

    pantalla.dimensiones (2,4); cout<<"VENTAS POR MES:";
    pantalla.dimensiones (2,5); cout<<"--------------------";

    int cantidad = ventaAux.cantidadVentas();

    for(int anio=2020; anio<2026; anio++){
        pantalla.dimensiones ((anio-2017)*9-8,7); cout<<anio;
        for(int mes=1; mes<13; mes++){
            pantalla.dimensiones (2,mes+7); cout<<"MES "<<mes;

            for(int indice=0; indice<cantidad; indice++){
                ventaAux.leerDeDisco(indice);
                if(ventaAux.getFecha().getAnio()==anio){
                    if(ventaAux.getFecha().getMes()==mes){
                        consumoTotal += ventaAux.getConsumoTotal();
                        pantalla.dimensiones ((anio-2017)*9-10,mes+7); cout<<consumoTotal<<"|";
                    }
                    else{
                        pantalla.dimensiones ((anio-2017)*9-8,mes+7); cout<<" - - |";
                    }
                }
                else{
                    pantalla.dimensiones ((anio-2017)*9-8,mes+7); cout<<" - - |";
                }
            }
        }
    }


    pantalla.dimensiones (2,22); cout<< system ("pause");

}

void Menu::vistaVentasPorEmpleado(int idVendedor)
{
    Pantalla pantalla;
    Venta ventaAux;
    Empleado empleadoAux;
    ArchivoEmpleado archivoEmpleado("empleados.dat");
    int pos1, pos2, renglon = 8;
    float consumoTotal;

    pantalla.estiloMenu();

    pantalla.dimensiones (2,4); cout<<"VENTAS POR EMPLEADO:";
    pantalla.dimensiones (2,5); cout<<"--------------------";

    for(int id=0; id<10; id++){

        consumoTotal=0;
        pos1=0;
        while(pos1< archivoEmpleado.cantidadEnArchivo()){
            empleadoAux = archivoEmpleado.leerDeDisco(pos1);
            pos1++;
            if(empleadoAux.getIdEmpleado()==id&&empleadoAux.getEstado()==true){
                pantalla.dimensiones(2,renglon); cout<<empleadoAux.getNombre()<<" "<<empleadoAux.getApellido();
                pos2=0;
                while(ventaAux.leerDeDisco(pos2++)>0){
                    if(ventaAux.getIdVendedor()==id){
                        consumoTotal+=ventaAux.getConsumoTotal();
                    }
                }
                pantalla.dimensiones(25,renglon); cout<<"$ "<<consumoTotal;
                renglon++;
            }
        }
    }

    pantalla.dimensiones (2,15); cout << system("pause");

}

void Menu::vistaVentasPorProducto(int idVendedor)
{
    Pantalla pantalla;
    Transaccion transaccionAux;
    Producto productoAux;
    int pos1, pos2, renglon = 8, id;
    float consumoTotal;

    pantalla.estiloMenu();

    pantalla.dimensiones (2,4); cout<<"VENTAS POR PRODUCTO:";
    pantalla.dimensiones (2,5); cout<<"--------------------";

    pos1=0;
    while(productoAux.leerDeDisco(pos1++)>0){
        consumoTotal=0;
        id = productoAux.getIdProducto();

        if (productoAux.getEstado()==true){
            pantalla.dimensiones(2,renglon); cout<<productoAux.getNombreProducto();
            pos2=0;
            while(transaccionAux.leerDeDisco(pos2++)>0){
                if(transaccionAux.getIdProducto()==id){
                    consumoTotal+=(transaccionAux.getPrecio()*transaccionAux.getCantidad());
                }
            }
            pantalla.dimensiones(35,renglon); cout<<"$ "<<consumoTotal;
            renglon++;
        }
    }

    pantalla.dimensiones (2,22); cout << system("pause");
}

int Menu::menuAjuste(int idVendedor)
{
    do{
        Pantalla pantalla;
        Producto productoAux;
        Empleado empleadoAux;
        ArchivoEmpleado archivoEmpleado("empleados.dat");
        int opcion;

        pantalla.estiloMenu();

        pantalla.dimensiones (2,6); cout<<"MENU AJUSTE";
        pantalla.dimensiones (2,7); cout<<"------------------";
        pantalla.dimensiones (2,9); cout<<"INGRESE UNA OPCION: ";

        pantalla.dimensiones (2,11); cout<<"1 - CARGAR PRODUCTO ";
        pantalla.dimensiones (2,12); cout<<"2 - MODIFICAR PRODUCTO ";
        pantalla.dimensiones (2,13); cout<<"3 - DAR DE BAJA PRODUCTO ";
        pantalla.dimensiones (2,14); cout<<"4 - CARGAR EMPLEADO ";
        pantalla.dimensiones (2,15); cout<<"5 - MODIFICAR EMPLEADO ";
        pantalla.dimensiones (2,16); cout<<"6 - DAR DE BAJA EMPLEADO ";
        pantalla.dimensiones (2,17); cout<<"7 - VOLVER AL MENU PRINCIPAL ";
        pantalla.dimensiones (2,18); cout<<"0 - SALIR DEL PROGRAMA ";

        pantalla.dimensiones (2,20); cout<<"->: ";
        cin>>opcion;

        switch (opcion)
        {
        case 1:
            pantalla.estiloMenu();
            pantalla.dimensiones (2,6); cout<<"MENU AJUSTE - CARGAR PRODUCTO";
            pantalla.dimensiones (2,7); cout<<"------------------";
            pantalla.dimensiones (2,9);
            productoAux.cargar();
            pantalla.dimensiones (2,15);
            productoAux.grabarEnDisco(productoAux);
            pantalla.dimensiones (2,16);
            system("pause");
            menuAjuste(idVendedor);
            break;
        case 2:
            pantalla.estiloMenu();
            pantalla.dimensiones (2,6); cout<<"MENU AJUSTE - MODIFICAR PRODUCTO";
            pantalla.dimensiones (2,7); cout<<"------------------";
            pantalla.dimensiones (2,12);
            productoAux.modificarRegistro();
            menuAjuste(idVendedor);
            break;

        case 3:
            pantalla.estiloMenu();
            pantalla.dimensiones (2,6); cout<<"MENU AJUSTE - ELIMINAR PRODUCTO";
            pantalla.dimensiones (2,7); cout<<"------------------";
            pantalla.dimensiones (2,12);
            productoAux.bajaProducto();
            menuAjuste(idVendedor);
            break;
        case 4:
            pantalla.estiloMenu();
            pantalla.dimensiones (2,6); cout<<"MENU AJUSTE - CARGAR EMPLEADO";
            pantalla.dimensiones (2,7); cout<<"------------------";
            pantalla.dimensiones (2,12);
            empleadoAux.cargarEmpleado();
            archivoEmpleado.grabarEnDisco(empleadoAux);
            menuAjuste(idVendedor);
            break;
        case 5:
            pantalla.estiloMenu();
            pantalla.dimensiones (2,6); cout<<"MENU AJUSTE - MODIFICAR EMPLEADO";
            pantalla.dimensiones (2,7); cout<<"------------------";
            pantalla.dimensiones (2,8);
            archivoEmpleado.modificarRegistro();
            menuAjuste(idVendedor);
            break;
        case 6:
            pantalla.estiloMenu();
            pantalla.dimensiones (2,5); cout<<"MENU AJUSTE - BAJA DE EMPLEADO";
            pantalla.dimensiones (2,6); cout<<"------------------";
            archivoEmpleado.bajaEmpleado();
            menuAjuste(idVendedor);
            break;
        case 7:
            menuPrincipal(idVendedor);
            break;
        case 0:
            FinalizarPrograma();
            break;

        default:
            OpcionIncorrecta();
            break;
        }

    }while(_opcion!=0);
    return 0;

}

int Menu::menuPedido(int idVendedor)
{
    do{
        Pantalla pantalla;
        Venta venta;
        Producto producto;
        int opcion, renglon = 8, codigoProducto = 0, cantidadProducto = 0, mesaAux = -1;
        float subtotal = 0;

        system("cls");
        system("mode con: cols=100 lines=26"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
        system("COLOR 71"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS
        pantalla.dibujarCuadro(0,0,98,25); //SE DIBUJA EL CUADRO PRINCIPAL
        pantalla.dibujarCuadro(1,1,97,3); //SE DIBUJA EL CUADRO DEL TITULO
        pantalla.dimensiones(39,2); cout<<"DELTAPOINT RESTO";

        pantalla.dibujarCuadroDoble(2,4,96,6,23);

        pantalla.dibujarCuadroDoble(2,4,96,6,23);
        pantalla.dimensiones (4,5); cout<<"MESA: ";
        cin>> mesaAux;
        venta.setMesa(mesaAux);
        venta.setVendedor(idVendedor);

        pantalla.dimensiones (3,renglon-1); cout<<"CODIGO";
        pantalla.dimensiones (18,renglon-1);cout<<"NOMBRE PRODUCTO";
        pantalla.dimensiones (50,renglon-1);cout<<"CANTIDAD";
        pantalla.dimensiones (66,renglon-1);cout<<"PRECIO";
        pantalla.dimensiones (82,renglon-1);cout<<"SUBTOTAL";
        pantalla.dimensiones (3,24); cout<<"0 - FIN DE CARGA DE PRODUCTOS";

        pantalla.dimensiones (3,renglon);
        cin>>codigoProducto;
        pantalla.dimensiones (80,22); cout<<"TOTAL: ";

        while(codigoProducto>0)
        {
            producto = buscarPorCodigo(codigoProducto);
            pantalla.dimensiones (15,renglon); cout<<producto.getNombreProducto();
            if(producto.getIdProducto()!=-1)
            {
                pantalla.dimensiones (54,renglon);
                cin>>cantidadProducto;

                pantalla.dimensiones (66,renglon); cout<<"$"<<producto.getPrecioProducto();
                subtotal = cantidadProducto * producto.getPrecioProducto();
                pantalla.dimensiones (82,renglon); cout<<"$"<<subtotal;

                if(venta.agregarProductoALaVenta(codigoProducto,cantidadProducto) != -1){//GRABAMOS EN ARCHIVO TRANSACCI�N
                    pantalla.dimensiones (87,22); cout<<"$"<<venta.getConsumoTotal(); //EN EL M�TODO ANTERIOR SE SUM� EL IMPORTE

                    renglon++;
                }
                else{
                    cout << RED;
                    pantalla.dimensiones (3,renglon+1);cout << "No se pudo cargar la venta. " ;
                    cout << BLUE;
                    renglon++;
                    renglon++;

                }
            }
            else{
                renglon++; // SI no encontr� el producto se baja un renglon y pida un nuevo codigo de prod
            }

            pantalla.dimensiones (3,renglon);
            cin>>codigoProducto;
        }
        pantalla.dimensiones (4,renglon+1); cout<<" - - - FIN DE CARGA DE PRODUCTOS - - - ";

        do{
            pantalla.dimensiones (3,24) ;  cout <<"1 - CONFIRMAR                ";
            pantalla.dimensiones (25,24);  cout <<"2 - SALIR / MENU PRINCIPAL";
            pantalla.dimensiones (4,22) ;  cout <<"INGRESE UNA OPCION: ";
            cin>>opcion;
            switch (opcion)
            {
            case 1:
                venta.grabarEnDisco(); ////GRABAMOS EN ARCHIVO VENTA
                pantalla.dimensiones (4,22); cout<<"VENTA REGISTRADA                        ";
                pantalla.dimensiones (35,24); cout << "                                                      " << endl;
                pantalla.dimensiones (3,24); system("pause");
                menuVenta(idVendedor);
                break;

            case 2:
                menuPrincipal(idVendedor);
                break;

            default:
                cout << RED;
                pantalla.dimensiones (4,22);  cout << "Opcion Incorrecta                                      " << endl;
                cout << BLUE;
                pantalla.dimensiones (35,24); cout << "                                                      " << endl;
                pantalla.dimensiones (3,24);  system("pause");
                pantalla.dimensiones (4,22);  cout << "                                                     " << endl;
                pantalla.dimensiones (25,24); cout << "                                                     " << endl;
                pantalla.dimensiones (4,22);  cout  <<"INGRESE UNA OPCION: ";
                break;
            }

        }while (opcion != 1 || opcion != 2);


    }while(_opcion!=0);
    return 0;
}

void Menu::menuConsumoMesa(int idVendedor)
{
    system("cls");
    Pantalla pantalla;
    Venta venta;
    Transaccion transaccion;
    Producto producto;

    int pos1=0, pos2=0;

    int renglon = 8, mesaAux = -1;
    float total = 0, subtotal = 0;

    system("cls");
    system("mode con: cols=100 lines=26"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
    system("COLOR 71"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS
    pantalla.dibujarCuadro(0,0,98,25); //SE DIBUJA EL CUADRO PRINCIPAL
    pantalla.dibujarCuadro(1,1,97,3); //SE DIBUJA EL CUADRO DEL TITULO
    pantalla.dimensiones(39,2); cout<<"DELTAPOINT RESTO";

    pantalla.dibujarCuadroDoble(2,4,96,6,23);

    pantalla.dimensiones (4,5); cout<<"MESA: ";
    cin>> mesaAux;

    pantalla.dimensiones (3,renglon-1);  cout<<"CODIGO";
    pantalla.dimensiones (18,renglon-1); cout<<"NOMBRE PRODUCTO";
    pantalla.dimensiones (50,renglon-1); cout<<"CANTIDAD";
    pantalla.dimensiones (66,renglon-1); cout<<"PRECIO";
    pantalla.dimensiones (82,renglon-1); cout<<"SUBTOTAL";
    pantalla.dimensiones (80,22);        cout<<"TOTAL: ";

    while(venta.leerDeDisco(pos1++)>0) //RECORRE ARCHIVO VENTAS
    {
        venta.getIdMesa(); //POR VUELTA TOMAMOS EL ID

        if(venta.getIdMesa() == mesaAux) //FILTRAMOS LAS VENTAS QUE COINCIDEN CON EL N� DE MESA INGRESADO
        {
            while(transaccion.leerDeDisco(pos2++)) //RECORREMOS ARCHIVO TRANSACCI�N
            {
                if(transaccion.getIdMesa() == venta.getIdMesa()&&transaccion.getEstado()==2) //FILTRA SI COINCIDE VENTA Y TRANSACCI�N EN EL ID MESA
                {
                    pantalla.dimensiones (4,renglon); cout<<transaccion.getIdProducto();
                    producto = buscarPorCodigo(transaccion.getIdProducto());
                    pantalla.dimensiones (19,renglon); cout<<producto.getNombreProducto();
                    pantalla.dimensiones (54,renglon); cout<<transaccion.getCantidad();
                    pantalla.dimensiones (66,renglon); cout<<"$"<<transaccion.getPrecio();
                    subtotal = transaccion.getCantidad() * transaccion.getPrecio();
                    pantalla.dimensiones (82,renglon); cout<<"$"<<subtotal;
                    total+= subtotal;
                    venta.setConsumoTotal(total);
                    pantalla.dimensiones (87,22);  cout<<"$"<<total;

                    renglon++;
                }
            }
        }
    }

    pantalla.dimensiones (3,24); system ("pause") ;

}


void Menu::cerrarMesa(){

    Pantalla pantalla;
    Transaccion transaccion;

    int mesaAux = -1, posicion=0;
    float total=0;

    system("cls");
    system("mode con: cols=100 lines=26"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
    system("COLOR 71"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS
    pantalla.dibujarCuadro(0,0,98,25); //SE DIBUJA EL CUADRO PRINCIPAL
    pantalla.dibujarCuadro(1,1,97,3); //SE DIBUJA EL CUADRO DEL TITULO
    pantalla.dimensiones(39,2); cout<<"DELTAPOINT RESTO";

    pantalla.dibujarCuadroDoble(2,4,96,6,23);

    pantalla.dimensiones (4,5); cout<<"MESA: ";
    cin>> mesaAux;


    while(transaccion.leerDeDisco(posicion)>0) //RECORRE ARCHIVO VENTAS
    {
        transaccion.getIdMesa(); //POR VUELTA TOMAMOS EL ID

        if(transaccion.getIdMesa() == mesaAux) //FILTRAMOS LAS VENTAS QUE COINCIDEN CON EL N� DE MESA INGRESADO
        {
            total+=transaccion.getPrecio();
            transaccion.cerrarMesa(mesaAux);
        }
        posicion++;
    }

    pantalla.dimensiones (4,8);
    cout<<"MESA CERRADA."<<endl;

    pantalla.dimensiones (80,22); cout<<"TOTAL: "<<total;
    pantalla.dimensiones (2,24); cout<< system("pause") ;
}

