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

    int cargar();
    void mostrar();

    void cargarCadenas(char *pal, int tam);

};



#endif // PRODUCTO_H
