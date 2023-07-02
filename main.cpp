#include "iostream"

using namespace std;
#include "Menu.h"
#include "Pantalla.h"
#define XSCREEN 78
int main(){

    Pantalla pantalla;
    Menu menu;

    int Programa = menu.menuIdVendedor();
    system("cls");
    if(Programa == 0){
        pantalla.dibujarCuadro(0,0,79,24);
        pantalla.dibujarCuadro(1,1,(XSCREEN-1),3); //SE DIBUJA EL CUADRO DEL TITULO
        pantalla.gotoxy(30,2); cout<<"DELTAPOINT RESTO";
        pantalla.gotoxy(17,5);
        cout << " Gracias por utilizar nuestro programa :)" << endl << endl << endl << endl << endl ;
    }
    return 0;
}
