#define XSCREEN 78
#define YSCREEN 24
#include <iostream>
using namespace std;
#include "ArchivoEmpleado.h"
#include "Pantalla.h"
#include "colors.h"

ArchivoEmpleado::ArchivoEmpleado(const char* Nombre){
    strcpy(_Nombre, Nombre);
}

int ArchivoEmpleado::grabarEnDisco(Empleado empleado){
    Pantalla pantalla;
    FILE *p;
    p=fopen(_Nombre, "ab");

    if(p==NULL){
       cout << RED;
       pantalla.dimensiones(15,15);
       cout << "El archivo de - Empleados - no se pudo abrir." << endl;
       pantalla.dimensiones(15,16);
       cout << "Comuniquese con el area de sistemas" << endl;
       pantalla.dimensiones(15,20);
       cout << BLUE;
       system("pause");

      return -1;
    }
    int grabo=fwrite(&empleado, sizeof(Empleado),1, p);
    fclose(p);
    return grabo;
}



Empleado  ArchivoEmpleado:: leerDeDisco(int pos){
    Pantalla pantalla;
    Empleado empleado;
    FILE *p;
    p=fopen(_Nombre,"rb");
    if(p==NULL){
       cout << RED;
       pantalla.dimensiones(15,15);
       cout << "El archivo de -Empleados - no se pudo abrir." << endl;
       pantalla.dimensiones(15,16);
       cout << "Comuniquese con el area de sistemas" << endl;
       pantalla.dimensiones(15,20);
       cout << BLUE;
       system("pause");
       exit(20);

    }
    fseek(p, sizeof(Empleado)*pos,0);
    fread(&empleado, sizeof empleado, 1, p);

    fclose(p);
    return empleado;
}



int  ArchivoEmpleado:: cantidadEnArchivo(){
    Empleado empleado;


    FILE* p = fopen("empleados.dat", "rb");
    if (p == NULL) {
        return 0;
    }
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Empleado);
    fclose(p);
    return cant;
}


bool ArchivoEmpleado:: validarIDEmpleado(int idEmpleado){
    Pantalla pantalla;
    Empleado empleado;
    FILE *pArchivo;

    int posicion=0;

    bool encontrado=false;

	pArchivo=fopen(_Nombre,"rb");

	if(pArchivo==NULL){
       cout << RED;
       pantalla.dimensiones(15,15);
       cout << "El archivo de -Empleados - no se pudo abrir." << endl;
       pantalla.dimensiones(15,16);
       cout << "Comuniquese con el area de sistemas" << endl;
       pantalla.dimensiones(15,20);
       cout << BLUE;
       system("pause");
	}

    while(fread(&empleado, sizeof empleado, 1,pArchivo)==1){

        if(empleado.getIdEmpleado()== idEmpleado && empleado.getEstado()==true){
            fclose(pArchivo);
            encontrado=true;
            return encontrado; //retorna el número de registro
        }

        posicion++; //incrementa la posición por leer el archivo
    }

    fclose(pArchivo);
    return encontrado;

}

int ArchivoEmpleado:: buscarDato(int idEmpleado){
    Pantalla pantalla;
    Empleado empleado;
    FILE *pArchivo;

    int posicion=0;

	pArchivo=fopen("empleados.dat","rb");

	if(pArchivo==NULL){
       cout << RED;
       pantalla.dimensiones(15,15);
       cout << "El archivo de -Empleados - no se pudo abrir." << endl;
       pantalla.dimensiones(15,16);
       cout << "Comuniquese con el area de sistemas" << endl;
       pantalla.dimensiones(15,20);
       cout << BLUE;
       system("pause");

		return -2; //si no encuentra el archivo nos devuelve un número de id inválido
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
    int idEmpleado = 0, posicion = 0, password = 0;
    char Nombre[30], Apellido[30];

    pantalla.dimensiones(30,2); cout<<"DELTAPOINT RESTO";
    pantalla.dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
    pantalla.dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO

    //BUSCAR N° DE REGISTRO
    pantalla.dimensiones(2,5);
    cout<<"Ingrese ID del empleado a modificar: ";
    cin>>idEmpleado;
    pantalla.dimensiones (2,6);
    cout<<"------------------";

    posicion=buscarDato(idEmpleado);

    if (posicion!= -1){
        //LEER EL REGISTRO, Y GUARDARLO EN UN REGISTRO AUXILIAR
        Empleado empleado;
        archivoEmpleado.leerDeDisco(posicion);

        pantalla.dimensiones(2,7);
        cout<<"EMPLEADO A MODIFICAR: "<<endl;

        empleado.mostrar();
        pantalla.dimensiones(2,13);
        cout<<"ESTA SEGURO/A DE CONTINUAR: (S/N): ";
        cin>>Confirmacion;
        pantalla.dimensiones (2,15);
        cout<<"------------------";
        cout<<endl<<endl;
        if(Confirmacion=='S' || Confirmacion=='s'){

            //CAMBIAR DATOS
            pantalla.dimensiones(1,17);
            cout<<" INGRESE NOMBRE DEL EMPLEADO: ";
            empleado.cargarCadenas(Nombre, 11);
            empleado.setNombre(Nombre);
            pantalla.dimensiones(1,18);
            cout<<" INGRESE APELLIDO DEL EMPLEADO: ";
            empleado.cargarCadenas(Apellido, 19);
            empleado.setApellido(Apellido);
            pantalla.dimensiones(1,19);
            cout<<" INGRESE PASSWORD: ";
            cin>>password;
            empleado.setPassword(password);
            empleado.setEstado(true);

            //SOBREESCRIBIR EL REGISTRO

            sobreEscribirRegistro(empleado, posicion);
            pantalla.dimensiones(2,21);
            cout<<"REGISTRO EMPLEADO MODIFICADO."<<endl<<endl;
            pantalla.dimensiones(2,22);
            system("pause");

        }
        else{
            pantalla.dimensiones (2,16);
            pantalla.dimensiones(2,18);
            system("pause");
        }
    }
    else{
        pantalla.dimensiones (2,7);
        cout<<"ID DE EMPLEADO INEXISTENTE"<<endl;
        pantalla.dimensiones (2,9);
        system("pause");
    }
}



int  ArchivoEmpleado:: bajaEmpleado(){
    ArchivoEmpleado archivoEmpleado("empleados.dat");
    int idEmpleado, posicion=0;
    Pantalla pantalla;

    pantalla.dimensiones(2,7);
    cout<<"INGRESE EL ID DEL EMPLEADO A ELIMINAR: ";
    cin>>idEmpleado;
    cout<<endl;

    posicion=buscarDato(idEmpleado);
    if(posicion== -1){
        pantalla.dimensiones(2,11);
        cout<<"ID DE EMPLEADO INEXISTENTE"<<endl<<endl;
        pantalla.dimensiones (2,15);
        system("pause");
        return -1;
    }

    //leer
    Empleado empleado;
    archivoEmpleado.leerDeDisco(posicion);

    char Confirmacion;
    pantalla.dimensiones(2,8);
    cout<<"ESTA ACCION DARA DE BAJA EL SIGUIENTE EMPLEADO: "<<endl<<endl;
    empleado.mostrar();
    pantalla.dimensiones(2,13);
    cout<<"ESTA SEGURO/A DE CONTINUAR: (S/N): ";
    cin>>Confirmacion;
    pantalla.dimensiones (2,14);
    cout<<"------------------";

    if(Confirmacion=='S' || Confirmacion=='s'){
        //cambiar estado
        empleado.setEstado(false);

        //sobreescribir el registro es guardar
        sobreEscribirRegistro(empleado, posicion);

        cout<<endl<<endl;
        pantalla.dimensiones(2,17);
        cout<<"EMPLEADO DADO DE BAJA."<<endl<<endl;
        pantalla.dimensiones(2,18);
        system("pause");
    }
    else{
        pantalla.dimensiones(2,17);
        system("pause");
    }
    return 1;

}


int  ArchivoEmpleado:: sobreEscribirRegistro(Empleado empleado, int posicion){
    FILE *pArchivo;

	pArchivo=fopen(_Nombre,"rb+");

	if(pArchivo==NULL){
		return -1;
	}

    fseek(pArchivo, posicion*sizeof (empleado), 0); //usamos fseek para llegar al registro que necesito pisar con la
    int valor=fwrite(&empleado, sizeof empleado, 1,pArchivo); //sobre escribo
    fclose(pArchivo);

    return valor;
}


