#include "colors.h"
#include <iostream>
#include <cstring>

#include "Empleado.h"
#include "Pantalla.h"
using namespace std;

Empleado::Empleado()
{
    //ctor
}

void Empleado::setIdEmpleado(int idEmpleado){
    _idEmpleado = idEmpleado;
}

int Empleado::getIdEmpleado(){
    return _idEmpleado;
}

void Empleado::setNombre(const char* name){
    strcpy(_nombre, name);
}

const char* Empleado::getNombre(){
    return _nombre;
}

void Empleado::setApellido(const char* lastName){
    strcpy(_apellido, lastName);
}

const char* Empleado::getApellido(){
    return _apellido;
}

void Empleado::setEstado(bool estado){
    _estado = estado;
}

bool Empleado::getEstado(){
    return _estado;
}

int Empleado::getPassword(){
    return _password;
}

void Empleado::setPassword(int newPassword){
    _password = newPassword;
}

void Empleado::cargarEmpleado(){
    Pantalla pantalla;

    int password1, password2; //[10], password2[10];

    cout<<"INGRESE ID DEL EMPLEADO: ";
    cin>>_idEmpleado;

    if (validarIDEmpleado(_idEmpleado)==false){
        pantalla.gotoxy (2,13);
        cout<<"INGRESE EL NOMBRE DEL EMPLEADO: ";
        cargarCadenas(_nombre,11);
        pantalla.gotoxy (2,14);
        cout<<"INGRESE EL APELLIDO DEL EMPLEADO: ";
        cargarCadenas(_apellido,19);
        pantalla.gotoxy (2,15);
        cout<<"INGRESE PASSWORD: ";
        cin>>password1;
        pantalla.gotoxy (2,16);
        cout<<"VUELVA A INGRESAR EL PASSWORD: ";
        cin>>password2;
        if(password1==password2){//strcmp(password1, password2))
            //cargarCadenas(_password, 9);
            _password = password1;
            pantalla.gotoxy (2,18);
            cout<<"ALTA DE USUARIO CORRECTA!";
            pantalla.gotoxy (2,19);
            system("pause");
        }
        else{
           pantalla.gotoxy (2,18);
           cout<<RED<<"LAS PASSWORD INGRESADAS NO COINCIDEN";
           pantalla.gotoxy (2,19);
           cout << BLUE;
           system("pause");
        }
    }
    else{
       pantalla.gotoxy (2,13);
        cout<<RED<<"ID DE EMPLEADO YA EXISTENTE";
        pantalla.gotoxy (2,15);
        cout << BLUE;
        system("pause");
    }
}

void Empleado::mostrar(){
    if (_estado==true){
        Pantalla pantalla;
       pantalla.gotoxy (2,9);
        cout<<"ID DEL EMPLEADO: "<<_idEmpleado;
       pantalla.gotoxy (2,10);
        cout<<"NOMBRE: "<<_nombre;
       pantalla.gotoxy (2,11);
        cout<<"APELLIDO: "<<_apellido;
    }
}

int Empleado::grabarEnDisco(){
    FILE *p;
    p=fopen("empleados.dat", "ab");
    if(p==NULL) return -1;
    int grabo=fwrite(this, sizeof(Empleado),1, p);
    fclose(p);
    return grabo;
}

int Empleado::leerDeDisco(int pos){
    FILE *p;
    p=fopen("empleados.dat","rb");
    if(p==NULL) return -1;
    fseek(p, pos*sizeof(Empleado), SEEK_SET);
    int leyo = fread(this, sizeof(Empleado), 1, p);
    fclose(p);
    return leyo;
}

int Empleado::cantidadEnArchivo(){
    FILE* p;
    int cantidad = 0;
    p = fopen("empleados.dat", "rb");
    if (p == nullptr) return -1;
    fseek(p, 0, SEEK_END);
    cantidad = ftell(p) / sizeof(Empleado);
    fclose(p);
    return cantidad;
}

bool Empleado::validarIDEmpleado(int idEmpleado){

    Pantalla pantalla;

    Empleado empleado;
    FILE *pArchivo;

    int posicion=0;

    bool encontrado=false;

	pArchivo=fopen("empleados.dat","rb");

	if(pArchivo==NULL){
       pantalla.gotoxy (2,7);
       cout<<"NO SE PUDO VERIFICAR EL ARCHIVO DE EMPLEADOS. "<<endl;
       pantalla.gotoxy (2,9);
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


int Empleado::buscarDato(int idEmpleado){

    Empleado empleado;
    FILE *pArchivo;

    int posicion=0;

	pArchivo=fopen("empleados.dat","rb");

	if(pArchivo==NULL){
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


void Empleado::modificarRegistro(){
    system("cls");

    Pantalla pantalla;
    char Confirmacion;
    int idEmpleado, posicion;

   pantalla.gotoxy(30,2); cout<<"DELTAPOINT RESTO";
    pantalla.dibujarCuadro(0,0,78,24); //SE DIBUJA EL CUADRO PRINCIPAL
    pantalla.dibujarCuadro(1,1,77,3); //SE DIBUJA EL CUADRO DEL TITULO

    //BUSCAR N° DE REGISTRO
   pantalla.gotoxy(2,5);
    cout<<"Ingrese ID del empleado a modificar: ";
    cin>>idEmpleado;
   pantalla.gotoxy (2,6);
    cout<<"------------------";

    posicion=buscarDato(idEmpleado);

    if (posicion!= -1){
        //LEER EL REGISTRO, Y GUARDARLO EN UN REGISTRO AUXILIAR
        Empleado empleado;
        empleado.leerDeDisco(posicion);

       pantalla.gotoxy(2,7);
        cout<<"EMPLEADO A MODIFICAR: "<<endl;

        empleado.mostrar();
        pantalla.gotoxy(2,13);
        cout<<"ESTA SEGURO/A DE CONTINUAR: (S/N): ";
        cin>>Confirmacion;
        pantalla.gotoxy (2,15);
        cout<<"------------------";
        cout<<endl<<endl;
        if(Confirmacion=='S' || Confirmacion=='s'){

            //CAMBIAR DATOS
            pantalla.gotoxy(1,17);
            cout<<" INGRESE NOMBRE DEL EMPLEADO: ";
            cargarCadenas(_nombre, 11);
            empleado.setNombre(_nombre);
            pantalla.gotoxy(1,18);
            cout<<" INGRESE APELLIDO DEL EMPLEADO: ";
            cargarCadenas(_apellido, 19);
            empleado.setApellido(_apellido);
            pantalla.gotoxy(1,19);
            cout<<" INGRESE PASSWORD: ";
            cin>>_password;
            empleado.setPassword(_password);
            _estado=true;

            //SOBREESCRIBIR EL REGISTRO

            sobreEscribirRegistro(empleado, posicion);
            pantalla.gotoxy(2,21);
            cout<<"REGISTRO EMPLEADO MODIFICADO."<<endl<<endl;
            pantalla.gotoxy(2,22);
            system("pause");

        }
        else{
            pantalla.gotoxy (2,16);
            pantalla.gotoxy(2,18);
            system("pause");
        }
    }
    else{
        pantalla.gotoxy (2,7);
        cout<<"ID DE EMPLEADO INEXISTENTE"<<endl;
        pantalla.gotoxy (2,9);
        system("pause");
    }
}


int Empleado::bajaEmpleado(){

    ///buscar
    int idEmpleado, posicion=0;
    Pantalla pantalla;

   pantalla.gotoxy(2,7);
    cout<<"INGRESE EL ID DEL EMPLEADO A ELIMINAR: ";
    cin>>idEmpleado;
    cout<<endl;

    posicion=buscarDato(idEmpleado);
    if(posicion== -1){
        pantalla.gotoxy(2,11);
        cout<<"ID DE EMPLEADO INEXISTENTE"<<endl<<endl;
        pantalla.gotoxy (2,15);
        system("pause");
        return -1;
    }

    //leer
    Empleado empleado;
    empleado.leerDeDisco(posicion);

    char Confirmacion;
    pantalla.gotoxy(2,8);
    cout<<"ESTA ACCION DARA DE BAJA EL SIGUIENTE EMPLEADO: "<<endl<<endl;
    empleado.mostrar();
    pantalla.gotoxy(2,13);
    cout<<"ESTA SEGURO/A DE CONTINUAR: (S/N): ";
    cin>>Confirmacion;
    pantalla.gotoxy (2,14);
    cout<<"------------------";

    if(Confirmacion=='S' || Confirmacion=='s'){
        //cambiar estado
        empleado.setEstado(false);

        //sobreescribir el registro es guardar
        sobreEscribirRegistro(empleado, posicion);

        cout<<endl<<endl;
        pantalla.gotoxy(2,17);
        cout<<"EMPLEADO DADO DE BAJA."<<endl<<endl;
        pantalla.gotoxy(2,18);
        system("pause");
    }
    else{
        pantalla.gotoxy(2,17);
        system("pause");
    }
    return 1;

}


int Empleado::sobreEscribirRegistro(Empleado empleado, int posicion){

    FILE *pArchivo;

	pArchivo=fopen("empleados.dat","rb+");

	if(pArchivo==NULL){
		return -1;
	}

    fseek(pArchivo, posicion*sizeof (empleado), 0); //usamos fseek para llegar al registro que necesito pisar con la
    int valor=fwrite(&empleado, sizeof empleado, 1,pArchivo); //sobre escribo
    fclose(pArchivo);

    return valor;
}


void Empleado::cargarCadenas(char *pal, int tam){
    int i;
    fflush(stdin);
    for(i=0; i<tam; i++)
    {
        pal[i]=cin.get();
        if(pal[i]=='\n') break;
    }
    pal[i]='\0';
    fflush(stdin);
}

