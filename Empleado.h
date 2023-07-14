#ifndef EMPLEADO_H
#define EMPLEADO_H


class Empleado
{
    private:
        int _idEmpleado;
        char _nombre[12];
        char _apellido[20];
        int _dni;
        char _password[20];
        bool _estado;

    public:
        Empleado();

        void setIdEmpleado(int idEmpleado);
        int getIdEmpleado();

        void setNombre(const char* name);
        const char* getNombre();

        void setApellido(const char* lastName);
        const char* getApellido();

        void setEstado(bool estado);
        bool getEstado();

        const char* getPassword();
        void setPassword(const char* newPassword);

        void setDNI(int DNI);
        int getDNI();

        int cargarEmpleado();
        void mostrar(int posicion);

        void cargarCadenas(char *pal, int tam);

};

#endif // EMPLEADO_H

