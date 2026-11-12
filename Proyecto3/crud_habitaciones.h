#ifndef CRUD_HABITACIONES_H
#define CRUD_HABITACIONES_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "reportes.h"

class NodoHab{
public:
	int idHabitacion;
	int numero;
	string piso;
	int tipo;
	int estado;
    int FB;
	NodoHab* Hizq;
    NodoHab* Hder;


    NodoHab(int idhab, int num, string p, int t, int est) {
        idHabitacion = idhab;
        numero = num;
        piso = p;
        tipo = t;
        estado = est;
        FB = 0;
        Hizq = nullptr;
        Hder = nullptr;
    }
    friend class ArbolHabitaciones;
    friend class ArbolHospitalizaciones;
};

typedef NodoHab* pHab;

class ArbolHabitaciones {
    friend class reportes;
private:
    pHab raiz;


    void InsertarBalanceado(pHab& r, bool& Hh, int id, int num, string pis, int tip, int est);
    void RotacionSimpleIzquierda(pHab& n, pHab& n1);
    void RotacionSimpleDerecha(pHab& n, pHab& n1);
    void RotacionDobleIzquierda(pHab& n, pHab& n1);
    void RotacionDobleDerecha(pHab& n, pHab& n1);
    pHab Buscarvalor(pHab r, int id);
    void InordenR(pHab r);
    void MostrarNodo(pHab n);
    void LiberarMemoria(pHab r);

    //eliminar AVL
    void BorrarBalanceado(pHab& r, bool& Hh, int id);
    void Borrar(pHab& aux1, pHab& otro1, bool& Hh);
    void Equilibrar1(pHab& n, bool& Hh);
    void Equilibrar2(pHab& n, bool& Hh);

public:

    ArbolHabitaciones();
    ~ArbolHabitaciones();

    bool InsertaNodo(int id, int num, string pis, int tip, int est);
    pHab Buscarvalor(int id);

    void InordenR();
    void InsertarHabitacion(int id, int num, string pis, int tip, int est);
    void leerArchivo(const char* nombreArchivo);
    void BuscarMostrar(int id);
    void ModificarHab(int id, int estado);
    void InordenReportesHab(pHab r, reportes& rep, int anchos[], int est);

    //eliminar
    bool EliminaNodo(int id);
    void EliminarHab(int id);

};


#endif