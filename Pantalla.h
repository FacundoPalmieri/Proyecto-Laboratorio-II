#ifndef PANTALLA_H
#define PANTALLA_H


class Pantalla
{
    public:
    void dibujarCuadro(int x1,int y1,int x2,int y2);
    void dibujarCuadroDoble(int x1,int y1,int x2,int y2, int y3);
    void gotoxy(int x,int y);
};

#endif // PANTALLA_H
