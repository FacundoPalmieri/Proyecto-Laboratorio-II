#ifndef PRODUCTO_H
#define PRODUCTO_H


class Producto
{
 private:
    int _idProducto;
    char _nombreProducto[50];
    float _precioProducto;
    bool _estado;

public:
    Producto();

    int getIdProducto();
    const char* getNombreProducto();
    float getPrecioProducto();
    bool getEstado();


    void setIdProducto(int IDproducto);
    void setNombreProducto(const char* nombreProducto);
    void setPrecioProducto(float precioProducto);
    void setEstado(bool estado);

    void cargar();
    void mostrar();

    void grabarEnDisco(Producto producto);
    int leerDeDisco(int pos);
    int cantidadEnArchivo();
    int buscarDato(int idProducto);
    void modificarRegistro();
    int bajaProducto();
    int sobreEscribirRegistro(Producto producto, int posicion);
    void cargarCadenas(char *pal, int tam);

};

Producto buscarPorCodigo(int codigo);

#endif // PRODUCTO_H
