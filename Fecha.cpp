#include <iostream>
#include<cstdio>
#include <stdlib.h>
#include<ctime>

using namespace std;

#include "Fecha.h"


Fecha::Fecha()
{
    time_t t;
    struct tm *f;
    time(&t);
    f=localtime(&t);
    _dia=f->tm_mday;
    _mes=f->tm_mon+1;
    _anio=f->tm_year+1900;
}

void Fecha::setDia(int dia)
{
    _dia=dia;
}
void Fecha::setMes(int mes)
{
    _mes=mes;
}
void Fecha::setAnio(int anio)
{
    _anio=anio;
}
int Fecha::getDia()
{
    return _dia;
}
int Fecha::getMes()
{
    return _mes;
}
int Fecha::getAnio()
{
    return _anio;
}

void Fecha::cargarFecha()
{
    cout<<"\nCARGAR FECHA CON EL FORMATO DD/MM/AA: "<<endl;
    cout<<"INGRESE DIA: ";
    cin>>_dia;
    cout<<"INGRESE MES: ";
    cin>>_mes;
    cout<<"INGRESE ANIO: ";
    cin>>_anio;
}

void Fecha::mostrarFecha()
{
    if (_dia < 10)
    {
        cout << "0";
    }
    cout << _dia << "/";
    if (_mes < 10)
    {
        cout << "0";
    }
    cout << _mes << "/";
    if (_anio < 10)
    {
        cout << "0";
    }
    cout <<_anio << endl;
}
