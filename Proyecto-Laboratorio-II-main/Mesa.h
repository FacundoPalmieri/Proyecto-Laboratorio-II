#ifndef MESA_H_INCLUDED
#define MESA_H_INCLUDED

class Mesa{
private:
    int _idMesa;
    bool _disponibilidad;       // 0- esta ocupada  /  1- esta disponible
    bool _estado;

public:
    Mesa();
    int getIdMesa();
    bool getDisponibilidad();
    bool getEstado();

    void setDisponibilidad(bool disp);
    void setEstado(bool estado);

    bool cargar();
    bool mostrar();

    int ocupar();

    int grabarEnDisco();
    int grabarEnDiscoEnPosicion(int pos);
    int leerDeDisco(int pos);
};

#endif // MESA_H_INCLUDED
