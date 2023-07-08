#include<iostream>


using namespace std;

#include"Mesa.h"

Mesa::Mesa(){
    _idMesa = -1;
    _disponibilidad = true;
    _status = true;
}

int Mesa::getIdMesa(){
    return _idMesa;
}

bool Mesa::getDisponibilidad(){
    return _disponibilidad;
}

bool Mesa::getEstado(){
    return _estado;
}

void Mesa::setDisponibilidad(bool disp){
    _disponibilidad = disp;
}

void Mesa::setEstado(bool estado){
    _estado = estado;
}

bool Mesa::cargar(){
    Mesa mesaAux;
    int idAux, pos;
    cout<<"INGRESE NUMERO DE MESA: ";
    cin>>idAux;
    pos=0;
    while(mesaAux.leerDeDisco(pos++)){
        if(mesaAux.getIdMesa()==idAux){
            cout<<"EL NUMERO DE MESA INDICADO YA EXISTE, INDIQUE OTRO NUMERO"<<endl;
            return false;
        }
        _idMesa = idAux;
        return true;
    }
    return false;
}

bool Mesa::mostrar(){
    cout<<"\nNUMERO DE MESA: "<<_idMesa;
    cout<<"\nESTA DISPONIBLE: ";
    if(_disponibilidad) cout<<"SI";
    else cout<<"NO";


}

int Mesa::ocupar(){         //compruba existencia y disponibilidad

    Mesa mesaAux;
    int pos=0;
    while(mesaAux.leerDeDisco(pos)){
        if(mesaAux.getIdMesa()==this->getIdMesa()){
            if(mesaAux.getDisponibilidad()==1)      // si esta disponible
                mesaAux.setDisponibilidad(0);        // ocuparla
                mesaAux.grabarEnDiscoEnPosicion(pos);
                return 1;
            if(mesaAux.getDisponibilidad()==1){
                return 0;
            }
        }
        pos++;
    }
    return -1;
}

int Mesa::grabarEnDisco(){
        FILE *p;
        p=fopen("mesas.dat", "ab+");
        if(p==NULL) return -1;
        int grabo=fwrite(this, sizeof(Mesa),1, p);
        fclose(p);
        return grabo;
}

int Mesa::grabarEnDiscoEnPosicion(int pos){
	FILE *p1;
	p1 = fopen("mesas.dat", "rb+");
	if(p1==NULL) return false;
	fseek(p1, sizeof(Mesa)*pos, 0);
	int escribio = fwrite(p1, sizeof(Mesa), 1, 0);
	fclose(p1);
	return escribio;
}

int Mesa::leerDeDisco(int pos){
    FILE *p;
    p=fopen("mesas.dat","rb");
    if(p==NULL) return -1;
    fseek(p,pos*sizeof(Mesa), SEEK_SET);
    int lecturas = fread(this, sizeof(Mesa), 1, p);
    fclose(p);
    return lecturas;
}

