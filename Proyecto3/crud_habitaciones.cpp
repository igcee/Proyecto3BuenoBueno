#include <pch.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "crud_habitaciones.h"


// Constructor
ArbolHabitaciones::ArbolHabitaciones()
{
    raiz = nullptr;
}

// Destructor
ArbolHabitaciones::~ArbolHabitaciones()
{
    LiberarMemoria(raiz);
}

bool ArbolHabitaciones::InsertaNodo(int id, int num, string pis, int tip, int est)
{
    if (Buscarvalor(raiz, id) != nullptr)// ignora repetidos
        return false;

    bool Hh = false;// Hh = el arbol crecio de altura
    InsertarBalanceado(raiz, Hh, id, num, pis, tip, est);
    return true;
}

pHab ArbolHabitaciones::Buscarvalor(int id)
{
    return Buscarvalor(raiz, id);
}

void ArbolHabitaciones::InordenR()
{
    if (raiz == nullptr)
        cout << "No hay habitaciones" << endl;
    else
        InordenR(raiz);
}

void ArbolHabitaciones::InsertarHabitacion(int id, int num, string pis, int tip, int est)
{
    if (InsertaNodo(id, num, pis, tip, est))
        cout << "Habitacion de id: " << id << " de numero: " << num << " de piso: " << pis << " de tipo: " << tip <<  " de estado: " << est << " insertada correctamente" << endl;
    else
        cout << "No se pudo insertar la habitacion porque el id: " << id << " ya existe" << endl;
}

void ArbolHabitaciones::leerArchivo(const char* nombreArchivo)
{
    cout << "------------------ chunches habitaciones" << endl;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open() == false) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string id, numero, piso, tipo, estado;
    string filaencabezado;
    int idint;
    int numint;
    int tipoint;
    int estadoint;

    getline(archivo, filaencabezado);

    while (getline(archivo, id, ';')){
        getline(archivo, numero, ';');
        getline(archivo, piso, ';');
        getline(archivo, tipo, ';');
        getline(archivo, estado);
        idint = stoi(id);
        numint = stoi(numero);
        tipoint = stoi(tipo);
        estadoint = stoi(estado);
        InsertarHabitacion(idint, numint, piso, tipoint, estadoint);
    }
    archivo.close();
}

void ArbolHabitaciones::BuscarMostrar(int id)
{
    pHab nodoesta = Buscarvalor(id);
    if (nodoesta != nullptr) {
        cout << "Habitacion encontrada" << endl;
        MostrarNodo(nodoesta);
    }
    else {
        cout << "No existe una habitacion de id: " << id << endl;
    }
}

void ArbolHabitaciones::MostrarNodo(pHab n){
    cout << "Id: " << n->idHabitacion << endl;
    cout << "Numero: " << n->numero << endl;
    cout << "Piso: " << n->piso << endl;
    if (n->tipo == 1){
        cout << "Tipo: Individual" << endl;
    }
    else if (n->tipo == 2){
        cout << "Tipo: Compartida" << endl;
    }
    else{
        cout << "Tipo: UCI" << endl;
    }

    if (n->estado == 0){
        cout << "Estado: Disponible" << endl;
    }
    else{
        cout << "Estado: Ocupada" << endl;
    }
}

pHab ArbolHabitaciones::Buscarvalor(pHab r, int id)
{
    if (r == nullptr){ // nada
        return nullptr;
    }
    else if (id == r->idHabitacion){ // ya encontro
        return r;
    }
    else if (id < r->idHabitacion){
        return Buscarvalor(r->Hizq, id);
    }
    else
        return Buscarvalor(r->Hder, id);
}

void ArbolHabitaciones::InordenR(pHab r)
{
    if (r == nullptr) return;
    InordenR(r->Hizq);
    MostrarNodo(r);
    cout << endl;
    InordenR(r->Hder);
}

void ArbolHabitaciones::LiberarMemoria(pHab r)
{
    if (r == nullptr) return;
    LiberarMemoria(r->Hizq);
    LiberarMemoria(r->Hder);
    delete r;
}


void ArbolHabitaciones::InsertarBalanceado(pHab& r, bool& Hh, int id, int num, string pis, int tip, int est)
{
    pHab n1;
    if (r == nullptr)
    {
        r = new NodoHab(id, num, pis, tip, est);

        Hh = true;
    }
    else
    {
        if (id < r->idHabitacion)
        {
            InsertarBalanceado(r->Hizq, Hh, id, num, pis, tip, est);
            if (Hh)
            {
                switch (r->FB)
                {
                case 1:
                    r->FB = 0;
                    Hh = false;
                    break;
                case 0:
                    r->FB = -1;
                    break;
                case -1:
                    n1 = r->Hizq;
                    if (n1->FB == -1)
                    {
                        RotacionSimpleIzquierda(r, n1);
                    }
                    else
                    {
                        RotacionDobleIzquierda(r, n1);
                    }
                    Hh = false;
                    break;
                }
            }
        }
        else
            if (id > r->idHabitacion)
            {
                InsertarBalanceado(r->Hder, Hh, id, num, pis, tip, est);
                if (Hh)
                {
                    switch (r->FB)
                    {
                    case -1:
                        r->FB = 0;
                        Hh = false;
                        break;
                    case 0:
                        r->FB = 1;
                        break;
                    case 1:
                        n1 = r->Hder;
                        if (n1->FB == 1)
                        {
                            RotacionSimpleDerecha(r, n1);
                        }
                        else
                        {
                            RotacionDobleDerecha(r, n1);
                        }
                        Hh = false;
                        break;
                    }
                }
            }
    }
}

void ArbolHabitaciones::RotacionDobleIzquierda(pHab& n, pHab& n1)
{
    pHab n2;
    n2 = n1->Hder;
    n->Hizq = n2->Hder;
    n2->Hder = n;
    n1->Hder = n2->Hizq;
    n2->Hizq = n1;
    if (n2->FB == 1)
    {
        n1->FB = -1;
    }
    else
    {
        n1->FB = 0;
    }
    if (n2->FB == -1)
    {
        n->FB = 1;
    }
    else
    {
        n->FB = 0;
    }
    n2->FB = 0;
    n = n2;
}

void ArbolHabitaciones::RotacionDobleDerecha(pHab& n, pHab& n1)
{
    pHab n2;
    n2 = n1->Hizq;
    n->Hder = n2->Hizq;
    n2->Hizq = n;
    n1->Hizq = n2->Hder;
    n2->Hder = n1;
    if (n2->FB == 1)
    {
        n->FB = -1;
    }
    else
    {
        n->FB = 0;
    }
    if (n2->FB == -1)
    {
        n1->FB = 1;
    }
    else
    {
        n1->FB = 0;
    }
    n2->FB = 0;
    n = n2;
}

void ArbolHabitaciones::RotacionSimpleDerecha(pHab& n, pHab& n1)
{
    n->Hder = n1->Hizq;
    n1->Hizq = n;
    if (n1->FB == 1)
    {
        n->FB = 0;
        n1->FB = 0;
    }
    else
    {
        n->FB = 1;
        n1->FB = -1;
    }
    n = n1;
}

void ArbolHabitaciones::RotacionSimpleIzquierda(pHab& n, pHab& n1)
{
    n->Hizq = n1->Hder;
    n1->Hder = n;
    if (n1->FB == -1)
    {
        n->FB = 0;
        n1->FB = 0;
    }
    else
    {
        n->FB = -1;
        n1->FB = 1;
    }
    n = n1;
}


void ArbolHabitaciones::ModificarHab(int id, int nuevoEst) {
    pHab nodoesta = Buscarvalor(id);
    if (nodoesta == nullptr) { // si id no existe mandar error
        cout << "No se pudo realizar esa modificacion ya que la habitacion de id " << id << " no existe" << endl;

    }
    else {
       
        if (nuevoEst == 0) {
            if (nodoesta->estado == 0) {
                cout << "Habitacion de id " << id << " modificado, antes estaba en estado Disponible, ahora esta en estado Disponible" << endl;
            }
            else {
                cout << "Habitacion de id " << id << " modificado, antes estaba en estado Ocupada, ahora esta en estado Disponible" << endl;
            }
           
            
        }
        else {
            if (nodoesta->estado == 0) {
                cout << "Habitacion de id " << id << " modificado, antes estaba en estado Disponible, ahora esta en estado Ocupada" << endl;
             }
            else {
                cout << "Habitacion de id " << id << " modificado, antes estaba en estado Ocupada, ahora esta en estado Ocupada" << endl;
            }
            // la vrdd es q para los otros modulos con msjes de modificacion es mejor solo poner el 0 y 1 en lugar de Ocupada/Disponible, mucha pereza escribir tnato
        }

        nodoesta->estado = nuevoEst;
    }

}

void ArbolHabitaciones::InordenReportesHab(pHab r, reportes& rep, int anchos[], int estado) {
    if (r == nullptr) {
        return;
    }
    InordenReportesHab(r->Hizq, rep, anchos, estado);
    if (r->estado == estado) {
        string tipo = "Individual";
        if (r->tipo == 2) {
            tipo = "Compartida";
        }
        else if (r->tipo == 3) {
            tipo = "UCI";
        }
        string est = "Disponible";
        if (r->estado == 1) {
            est = "Ocupada";
        }
        string textos[] = { to_string(r->idHabitacion), to_string(r->numero), r->piso, tipo, est };
        rep.escribirFilaDinamica(5, textos, anchos);
    }
    InordenReportesHab(r->Hder, rep, anchos, estado);
}

//ELIMINAR AVL
// se llama cuando el subarbol IZQUIERDO de n se hizo mas bajo
void ArbolHabitaciones::Equilibrar1(pHab& n, bool& Hh)
{
    pHab n1;
    switch (n->FB)
    {
    case -1: //estaba cargado a la izq, ahora queda parejo (y la altura bajo)
        n->FB = 0;
        break;
    case 0: //estaba parejo, ahora queda cargado a la der (la altura NO cambia)
        n->FB = 1;
        Hh = false;
        break;
    case 1: //ya estaba cargado a la der, ahora queda desbalanceado: hay q rotar
        n1 = n->Hder;
        if (n1->FB >= 0)
        {
            if (n1->FB == 0) { //en este caso despues de rotar la altura no cambia
                Hh = false;
            }
            RotacionSimpleDerecha(n, n1);
        }
        else
        {
            RotacionDobleDerecha(n, n1);
        }
        break;
    }
}

//se llama cuando el subarbol DERECHO de n se hizo mas bajo (es el espejo de Equilibrar1)
void ArbolHabitaciones::Equilibrar2(pHab& n, bool& Hh)
{
    pHab n1;
    switch (n->FB)
    {
    case 1:
        n->FB = 0;
        break;
    case 0:
        n->FB = -1;
        Hh = false;
        break;
    case -1:
        n1 = n->Hizq;
        if (n1->FB <= 0)
        {
            if (n1->FB == 0) {
                Hh = false;
            }
            RotacionSimpleIzquierda(n, n1);
        }
        else
        {
            RotacionDobleIzquierda(n, n1);
        }
        break;
    }
}

void ArbolHabitaciones::Borrar(pHab& aux1, pHab& otro1, bool& Hh)
{
    if (aux1->Hder != nullptr)
    {
        Borrar(aux1->Hder, otro1, Hh);
        if (Hh) {
            Equilibrar2(aux1, Hh);
        }
    }
    else
    {
        //se copian los datos (no los hijos ni el FB)
        otro1->idHabitacion = aux1->idHabitacion;
        otro1->numero = aux1->numero;
        otro1->piso = aux1->piso;
        otro1->tipo = aux1->tipo;
        otro1->estado = aux1->estado;

        otro1 = aux1;        //ahora el q se va a hacer delete es este nodo
        aux1 = aux1->Hizq;   //su hijo izq sube a su lugar
        Hh = true;
    }
}

void ArbolHabitaciones::BorrarBalanceado(pHab& r, bool& Hh, int id)
{
    pHab otro;
    if (r == nullptr) {
        return;
    }

    if (id < r->idHabitacion)
    {
        BorrarBalanceado(r->Hizq, Hh, id);
        if (Hh) {
            Equilibrar1(r, Hh);
        }
    }
    else if (id > r->idHabitacion)
    {
        BorrarBalanceado(r->Hder, Hh, id);
        if (Hh) {
            Equilibrar2(r, Hh);
        }
    }
    else //lo encontro
    {
        otro = r;
        if (otro->Hder == nullptr) { //solo tiene hijo izq (o ninguno)
            r = otro->Hizq;
            Hh = true;
        }
        else if (otro->Hizq == nullptr) { //solo tiene hijo der
            r = otro->Hder;
            Hh = true;
        }
        else { //tiene 2 hijos
            Borrar(otro->Hizq, otro, Hh);
            if (Hh) {
                Equilibrar1(r, Hh);
            }
        }
        delete otro;
    }
}

bool ArbolHabitaciones::EliminaNodo(int id)
{
    if (Buscarvalor(raiz, id) == nullptr) {
        return false;
    }
    bool Hh = false;
    BorrarBalanceado(raiz, Hh, id);
    return true;
}

// Se indica el IdHabitacion, si existe se elimina la habitacion
void ArbolHabitaciones::EliminarHab(int id)
{
    if (EliminaNodo(id) == true) {
        cout << "Habitacion de id: " << id << " eliminada correctamente" << endl;
    }
    else {
        cout << "No se pudo eliminar la habitacion de id: " << id << " porque no existe" << endl;
    }
}