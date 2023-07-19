#define XSCREEN 78
#define YSCREEN 24
#include <iostream>
#include "colors.h"
using namespace std;
#include "ArchivoEmpleado.h"
#include "Pantalla.h"



ArchivoEmpleado::ArchivoEmpleado(const char* Nombre){
    strcpy(_Nombre, Nombre);
    FILE *p = fopen(_Nombre, "ab");


    if(p==NULL){
      MensajeError();

    }
}

int ArchivoEmpleado::grabarEnDisco(Empleado empleado){
    FILE *p;
    p=fopen(_Nombre, "ab");

    if(p==NULL){
     MensajeError();
    }
    int grabo=fwrite(&empleado, sizeof(Empleado),1, p);
    fclose(p);
    return grabo;
}



Empleado  ArchivoEmpleado:: leerDeDisco(int pos){
    Empleado empleado;

    FILE *p;
    p=fopen(_Nombre,"rb");
    if(p==NULL){
      MensajeError();

    }
    fseek(p, sizeof(Empleado)*pos,0);
    fread(&empleado, sizeof empleado, 1, p);

    fclose(p);
    return empleado;
}



int  ArchivoEmpleado:: cantidadEnArchivo(){

    FILE* p = fopen(_Nombre, "rb");
    if (p == NULL) {
        MensajeError();
    }
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Empleado);
    fclose(p);
    return cant;
}


bool ArchivoEmpleado:: validarIDEmpleado(int idEmpleado){
    Empleado empleado;
    FILE *pArchivo;

    int posicion=0;

    bool encontrado=false;

	pArchivo=fopen(_Nombre,"rb");

	if(pArchivo==NULL){
       MensajeError();
	}

    while(fread(&empleado, sizeof empleado, 1,pArchivo)==1){

        if(empleado.getIdEmpleado()== idEmpleado && empleado.getEstado()==true){
            fclose(pArchivo);
            encontrado=true;
            return encontrado; //retorna true
        }

        posicion++; //incrementa la posición por leer el archivo
    }

    fclose(pArchivo);
    return encontrado;

}

int ArchivoEmpleado:: buscarDato(int idEmpleado){
    Empleado empleado;
    FILE *pArchivo;

    int posicion=0;

	pArchivo=fopen(_Nombre,"rb");

	if(pArchivo==NULL){
       MensajeError();
	}

    while(fread(&empleado, sizeof empleado, 1,pArchivo)==1){

        if(empleado.getIdEmpleado()== idEmpleado && empleado.getEstado()==true){
            fclose(pArchivo);
            return posicion; //retorna el número de registro
        }

        posicion++; //incrementa la posición por leer el archivo
    }

    fclose(pArchivo);
    return -1; //retorna -1 cuando ya no hay archivos
}




void ArchivoEmpleado:: modificarRegistro(){
    system("cls");

    Pantalla pantalla;
    ArchivoEmpleado archivoEmpleado("empleados.dat");
    char Confirmacion;
    int idEmpleado = 0, posicion = 0, dni = 0;
    char Nombre[30], Apellido[30], password1[20],password2[20];


    pantalla.dimensiones(30,2); cout<<"DELTAPOINT RESTO";
    pantalla.dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
    pantalla.dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
    pantalla.dimensiones (2,6); cout<<"MENU AJUSTE - MODIFICAR EMPLEADO";
    pantalla.dimensiones (2,7); cout<<"----------------------------------";
    pantalla.dimensiones (2,23); cout <<"ingrese 0(cero) para volver al menu anterior";
    pantalla.dimensiones(2,8);
    cout<<"Ingrese ID del empleado a modificar: ";
    cin>>idEmpleado;
    if(idEmpleado == 0){
       pantalla.dimensiones (2,23); cout <<"                                                       "; // Limpia la leyenda "ingrese cero para volver
        return ;
    }
    else{
        pantalla.dimensiones (2,12);
        pantalla.dimensiones (2,23); cout <<"                                                       "; // Limpia la leyenda "ingrese cero para volver

        posicion=buscarDato(idEmpleado);

        if (posicion!= -1){
            //LEER EL REGISTRO, Y GUARDARLO EN UN REGISTRO AUXILIAR
            Empleado empleado;
            empleado=archivoEmpleado.leerDeDisco(posicion);

            pantalla.dimensiones(2,13);
            cout<<"EMPLEADO A MODIFICAR: "<<endl;
            pantalla.dimensiones(5,14);
            empleado.mostrar(1);
            do{
                pantalla.dimensiones(2,23);
                cout<<"ESTA SEGURO/A DE CONTINUAR (S/N): ";
                cin>>Confirmacion;

                if(Confirmacion =='S' || Confirmacion =='s'){

                    system ("cls");
                    pantalla.dimensiones(30,2); cout<<"DELTAPOINT RESTO";
                    pantalla.dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
                    pantalla.dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO
                    pantalla.dimensiones (2,6); cout<<"MENU AJUSTE - MODIFICAR EMPLEADO";
                    pantalla.dimensiones (2,7); cout<<"--------------------------------";

                    //CAMBIAR DATOS
                    pantalla.dimensiones(2,10);
                    cout<<"INGRESE EL NUEVO NOMBRE DEL EMPLEADO  : ";
                    empleado.cargarCadenas(Nombre, 11);
                    empleado.setNombre(Nombre);
                    pantalla.dimensiones(2,11);
                    cout<<"INGRESE EL NUEVO APELLIDO DEL EMPLEADO: ";
                    empleado.cargarCadenas(Apellido, 19);
                    empleado.setApellido(Apellido);
                    pantalla.dimensiones(2,12);
                    cout<<"INGRESE EL DNI                        : ";
                    cin >>dni;
                    empleado.setDNI(dni);
                    pantalla.dimensiones(2,13);
                    cout<<"INGRESE EL NUEVO PASSWORD             : ";
                    cin>>password1;
                    pantalla.dimensiones (2,14);
                    cout<<"VUELVA A INGRESAR EL PASSWORD         : ";
                    cin>>password2;
                    cin.ignore();
                    if(strcmp(password1, password2)==0){//strcmp(password1, password2))
                        empleado.setPassword(password1);
                        empleado.setEstado(true);
                    }

                    //SOBREESCRIBIR EL REGISTRO

                    if (sobreEscribirRegistro(empleado, posicion)==1){

                        pantalla.dimensiones(2,19);
                        cout << GREEN;
                        cout<<"REGISTRO EMPLEADO MODIFICADO."<<endl<<endl;
                        cout << BLUE;
                        pantalla.dimensiones(2,23);
                        system("pause");
                        return;
                    }
                    else{
                        pantalla.dimensiones(2,22);
                        cout << RED;
                        cout<<"ERROR AL MODIFICAR REGISTRO."<<endl<<endl;
                        pantalla.dimensiones(2,23);
                        cout << BLUE;
                        system("pause");
                        return;
                    }

                }
                else{
                    if(Confirmacion=='N' || Confirmacion=='n'){
                        pantalla.dimensiones(2,23);
                        system("pause");
                        return;
                    }
                    else{
                        cout << RED;
                        pantalla.dimensiones (2,22); cout << "Opcion Incorrecta";
                        cout << BLUE;
                        pantalla.dimensiones(2,23);
                        system("pause");
                        pantalla.dimensiones (2,22); cout << "                       ";
                        pantalla.dimensiones (2,23); cout << "                                                ";

                    }
                }
            }while(Confirmacion!= 'S' || Confirmacion != 's' || Confirmacion != 'N' || Confirmacion != 'n');
        }
        else{
            pantalla.dimensiones (2,9);
            cout << RED;
            cout<<"ID DE EMPLEADO INEXISTENTE"<<endl;
            cout << BLUE;
            pantalla.dimensiones (2,10);
            system("pause");
        }
    }
}



int  ArchivoEmpleado:: bajaEmpleado(){
    ArchivoEmpleado archivoEmpleado("empleados.dat");
    int idEmpleado, posicion=0;
    Pantalla pantalla;


    pantalla.dimensiones (2,5); cout<<"MENU AJUSTE - BAJA DE EMPLEADO";
    pantalla.dimensiones (2,6); cout<<"-------------------------------";
    pantalla.dimensiones (2,23); cout <<"ingrese 0(cero) para volver al menu anterior";
    pantalla.dimensiones( 2,7);
    cout<<"INGRESE EL ID DEL EMPLEADO A ELIMINAR: ";
    cin>>idEmpleado;
    if(idEmpleado == 0){
       pantalla.dimensiones (2,23); cout <<"                                                       "; // Limpia la leyenda "ingrese cero para volver
        return -1;
    }
    else{
        pantalla.dimensiones (2,23); cout <<"                                                       "; // Limpia la leyenda "ingrese cero para volver
        posicion=buscarDato(idEmpleado);
        if(posicion== -1){
            pantalla.dimensiones(2,11);
           cout << RED;
            cout<<"ID DE EMPLEADO INEXISTENTE"<<endl;
            cout << BLUE;
            pantalla.dimensiones (2,23);
            system("pause");
            return -1;
        }

        //leer
        Empleado empleado;
        empleado=archivoEmpleado.leerDeDisco(posicion);

        char Confirmacion;
        pantalla.dimensiones(2,8);
        cout<<"ESTA ACCION DARA DE BAJA EL SIGUIENTE EMPLEADO: "<<endl<<endl;
        empleado.mostrar(2);
        pantalla.dimensiones(2,23);
        do{
            cout<<"ESTA SEGURO/A DE CONTINUAR: (S/N): ";
            cin>>Confirmacion;
            if(Confirmacion=='S' || Confirmacion=='s'){
                //cambiar estado
                empleado.setEstado(false);

                //sobreescribir el registro es guardar
                if (sobreEscribirRegistro(empleado, posicion)==1){
                    pantalla.dimensiones(2,17);
                    cout << GREEN;
                    cout<<"EMPLEADO DADO DE BAJA.";
                    cout << BLUE;
                    pantalla.dimensiones(2,23);
                    system("pause");
                    return 0;
                }
                else{
                    pantalla.dimensiones(2,17);
                    cout << RED;
                    cout<<"ERROR AL DAR DE BAJA EL REGISTRO."<<endl<<endl;
                    cout << BLUE;
                    pantalla.dimensiones(2,18);
                    system("pause");
                    return -1;
                }
            }
            else{
                if(Confirmacion=='N' || Confirmacion=='n'){
                    pantalla.dimensiones(2,23);
                    system("pause");
                    return 0;
                }
                else{
                    cout << RED;
                    pantalla.dimensiones (2,22); cout << "Opcion Incorrecta";
                    cout << BLUE;
                    pantalla.dimensiones(2,23);
                    system("pause");
                    pantalla.dimensiones (2,22); cout << "                       ";
                    pantalla.dimensiones (2,23); cout << "                                                ";
                }
            }
        }while(Confirmacion!= 'S' || Confirmacion != 's' || Confirmacion != 'N' || Confirmacion != 'n');
        return 1;
    }

}


int  ArchivoEmpleado:: sobreEscribirRegistro(Empleado empleado, int posicion){
    FILE *pArchivo;

	pArchivo=fopen(_Nombre,"rb+");

	if(pArchivo==NULL){
		return -1;
	}

    fseek(pArchivo, posicion*sizeof (empleado), 0); //usamos fseek para llegar al registro que necesito pisar con la
    int valor=fwrite(&empleado, sizeof empleado, 1,pArchivo); //sobreescribo
    fclose(pArchivo);

    return valor;
}

void ArchivoEmpleado::Ordenar(){
    Empleado empleado, empleadoAuxiliar, empleadoSiguiente;
    ArchivoEmpleado archivoEmpleado("empleados.dat");
    int maximo = 0;

    maximo = archivoEmpleado.cantidadEnArchivo();

    for (int x=0; x<maximo; x++){
        for (int i=0; i<maximo-1; i++){
            empleado=archivoEmpleado.leerDeDisco(i);
            empleadoSiguiente=archivoEmpleado.leerDeDisco(i+1);

            if (empleado.getIdEmpleado()> empleadoSiguiente.getIdEmpleado()){
                empleadoAuxiliar=empleadoSiguiente;

                archivoEmpleado.sobreEscribirRegistro(empleado, i+1);

                archivoEmpleado.sobreEscribirRegistro(empleadoAuxiliar, i);
            }
        }
    }



}

void ArchivoEmpleado:: MensajeError(){
    Pantalla pantalla;
    system ("cls");
    pantalla.dimensiones (4,5);
    pantalla.estiloMenu();

    cout << RED;
    pantalla.dimensiones(15,15);
    cout << "El archivo de - Empleados - no se pudo abrir." << endl;
    pantalla.dimensiones(15,16);
    cout << "Comuniquese con el area de sistemas" << endl;
    pantalla.dimensiones(15,20);
    cout << BLUE;
    system("pause");
    exit(20);
}

