#ifndef FECHA_H
#define FECHA_H

class Fecha
{
private:
    int _dia;
    int _mes;
    int _anio;

public:
    Fecha();
    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);
    int getDia();
    int getMes();
    int getAnio();

    void cargarFecha();
    void mostrarFecha();
};

#endif // FECHA_H
