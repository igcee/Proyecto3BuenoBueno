#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "crud_citas.h"
#include "crud_pacientes.h"
#include "crud_medicos.h"

ArbolCitas::ArbolCitas() {
    raiz = nullptr;
}

ArbolCitas::~ArbolCitas() {
    LiberarMemoria(raiz);
}

bool ArbolCitas::InsertaNodo(int idc, int idp, int idm, int idesp, string fch, string hra, string mtivo, int est)
{
    if (Buscarvalor(raiz, idc) != nullptr)// ignora repetidos
        return false;

    bool Hh = false;// Hh = el arbol crecio de altura
    InsertarBalanceado(raiz, Hh, idc, idp, idm, idesp, fch, hra, mtivo, est);
    return true;
}

pCita ArbolCitas::Buscarvalor(int idc)
{
    return Buscarvalor(raiz, idc);
}

pCita ArbolCitas::Buscarvalor(pCita r, int id)
{
    if (r == nullptr) { // nada
        return nullptr;
    }
    else if (id == r->idCita) { // ya encontro
        return r;
    }
    else if (id < r->idCita) {
        return Buscarvalor(r->Hizq, id);
    }
    else {
        return Buscarvalor(r->Hder, id);
    }
}

void ArbolCitas::LiberarMemoria(pCita r)
{
    if (r == nullptr) return;
    LiberarMemoria(r->Hizq);
    LiberarMemoria(r->Hder);
    delete r;
}


void ArbolCitas::InsertarBalanceado(pCita& r, bool& Hh, int idc, int idp, int idm, int idesp, string fcha, string hra, string mtivo, int est)
{
    pCita n1;
    if (r == nullptr)
    {
        r = new NodoCita(idc, idp, idm, idesp, fcha, hra, mtivo, est);

        Hh = true;
    }
    else
    {
        if (idc < r->idCita)
        {
            InsertarBalanceado(r->Hizq, Hh, idc, idp, idm, idesp, fcha, hra, mtivo, est);
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
            if (idc > r->idCita)
            {
                InsertarBalanceado(r->Hder, Hh, idc, idp, idm, idesp, fcha, hra, mtivo, est);
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

void ArbolCitas::RotacionDobleIzquierda(pCita& n, pCita& n1)
{
    pCita n2;
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

void ArbolCitas::RotacionDobleDerecha(pCita& n, pCita& n1)
{
    pCita n2;
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

void ArbolCitas::RotacionSimpleDerecha(pCita& n, pCita& n1)
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

void ArbolCitas::RotacionSimpleIzquierda(pCita& n, pCita& n1)
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

void ArbolCitas::InsertarCita(int idc, int idp, int idm, int idesp, string fch, string hra, string mtivo, int est, ArbolPacientes& pacientes, ArbolMedicos& medicos)
{
    if (pacientes.Buscarvalor(idp) == nullptr) {
        cout << " No existe ningun paciente de id: " << idp << endl;
    }

    else if (medicos.Buscarvalor(idm) == nullptr) {
        cout << " No existe ningun medico de id: " << idm << endl;
    }

    else {
        if (InsertaNodo(idc, idp, idm, idesp, fch, hra, mtivo, est)) {
            cout << "Cita de id: " << idc << " de id paciente: " << idp << " de id medico: " << idm << " de id especialidad: " << idesp << " de fecha: " << fch << " de motivo: " << mtivo << " de estado: " << est << " insertada correctamente" << endl;
        }
        else {
            cout << "No se pudo insertar la cita porque el id: " << idc << " ya existe" << endl;
        }
    }
}

void ArbolCitas::leerArchivo(const char* nombreArchivo, ArbolPacientes& pacientes, ArbolMedicos& medicos)
{
    cout << "------------------ chunches citas" << endl;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open() == false) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string idc, idp, idm, idesp, fcha, hra, mtivo, est;
    string filaencabezado;
    int idcint;
    int idpint;
    int idmint;
    int idespint;
    int estadoint;

    getline(archivo, filaencabezado);

    while (getline(archivo, idc, ';')) {
        getline(archivo, idp, ';');
        getline(archivo, idm, ';');
        getline(archivo, idesp, ';');
        getline(archivo, fcha, ';');
        getline(archivo, hra, ';');
        getline(archivo, mtivo, ';');
        getline(archivo, est);
        idcint = stoi(idc);
        idpint = stoi(idp);
        idmint = stoi(idm);
        idespint = stoi(idesp);
        estadoint = stoi(est);
        InsertarCita(idcint, idpint, idmint, idespint, fcha, hra, mtivo, estadoint, pacientes, medicos);
    }
    archivo.close();
}

void ArbolCitas::BuscarMostrar(int idp, int idm, int id, ArbolPacientes& pacientes, ArbolMedicos& medicos)
{

    if (pacientes.Buscarvalor(idp) == nullptr) {
        cout << " No existe ningun paciente de id: " << idp << endl;
    }
    else if (medicos.Buscarvalor(idm) == nullptr) {
        cout << " No existe ningun medico de id: " << idm << endl;
    }

    else {
        pCita nodoesta = Buscarvalor(id);
        if (nodoesta != nullptr) {
            cout << "Cita encontrada" << endl;
            cout << "Id de cita: " << nodoesta->idCita << endl;
            cout << "Id de paciente: " << nodoesta->idPaciente << endl;
            cout << "Id de medico: " << nodoesta->idMedico << endl;
            cout << "Id de especialidad: " << nodoesta->idEspecialidad << endl;
            cout << "Fecha: " << nodoesta->fecha << endl;
            cout << "Hora: " << nodoesta->hora << endl;
            cout << "Motivo: " << nodoesta->motivo << endl;
            cout << "Estado: " << nodoesta->estado << endl;
        }
        else {
            cout << "No existe una cita de id: " << id << endl;
        }


    }


}



void ArbolCitas::ModificarCita(int idp, int idm, int idc, string motivo, int est, ArbolPacientes& pacientes, ArbolMedicos& medicos) {

    if (pacientes.Buscarvalor(idp) == nullptr) {
        cout << " No existe ningun paciente de id: " << idp << endl;
    }
    else if (medicos.Buscarvalor(idm) == nullptr) {
        cout << " No existe ningun medico de id: " << idm << endl;
    }
    else {
        pCita nodoesta = Buscarvalor(idc);
        if (nodoesta == nullptr) { // si id no existe mandar error
            cout << "No se pudo realizar esa modificacion ya que la cita de id " << idc << " no existe" << endl;

        }
        else {

            cout << "Cita de id " << idc << " modificada, su nuevo motivo es: "<< motivo<< " y su nuevo estado: "<< est << endl;
            nodoesta->motivo = motivo;
            nodoesta->estado = est;
        }



    }

}


void ArbolCitas::InordenReportesCitasPorPaciente(pCita r, reportes& rep, int anchos[], int IdPacFiltro) {
    if (r == nullptr) {
        return;
    }
    InordenReportesCitasPorPaciente(r->Hizq,rep,anchos,IdPacFiltro);
    if (r->idPaciente == IdPacFiltro) {
        string textos[] = { to_string(r->idCita), to_string(r->idPaciente), to_string(r->idMedico),to_string(r->idEspecialidad), r->fecha,r->hora,r->motivo,to_string(r->estado)};
        rep.escribirFilaDinamica(8, textos, anchos);
    }
    InordenReportesCitasPorPaciente(r->Hder, rep, anchos, IdPacFiltro);
}

void ArbolCitas::InordenReportesCitasPorMedico(pCita r, reportes& rep, int anchos[], int IdMedFiltro) {
    if (r == nullptr) {
        return;
    }
    InordenReportesCitasPorMedico(r->Hizq, rep, anchos, IdMedFiltro);
    if (r->idMedico == IdMedFiltro) {
        string textos[] = { to_string(r->idCita), to_string(r->idPaciente), to_string(r->idMedico),to_string(r->idEspecialidad), r->fecha,r->hora,r->motivo,to_string(r->estado) };
        rep.escribirFilaDinamica(8, textos, anchos);
    }
    InordenReportesCitasPorMedico(r->Hder, rep, anchos, IdMedFiltro);
}

void ArbolCitas::InordenReportesCitasPorEspecialidad(pCita r, reportes& rep, int anchos[], int idEspFiltro) {
    if (r == nullptr) {
        return;
    }
    InordenReportesCitasPorEspecialidad(r->Hizq, rep, anchos, idEspFiltro);
    if (r->idEspecialidad == idEspFiltro) {
        string textos[] = { to_string(r->idCita), to_string(r->idPaciente), to_string(r->idMedico),to_string(r->idEspecialidad), r->fecha,r->hora,r->motivo,to_string(r->estado) };
        rep.escribirFilaDinamica(8, textos, anchos);
    }
    InordenReportesCitasPorEspecialidad(r->Hder, rep, anchos, idEspFiltro);
}

void ArbolCitas::InordenReportesCitasPorFecha(pCita r, reportes& rep, int anchos[], string fechafiltro) {
    if (r == nullptr) {
        return;
    }
    InordenReportesCitasPorFecha(r->Hizq, rep, anchos, fechafiltro);
    if (r->fecha == fechafiltro) {
        string textos[] = { to_string(r->idCita), to_string(r->idPaciente), to_string(r->idMedico),to_string(r->idEspecialidad), r->fecha,r->hora,r->motivo,to_string(r->estado) };
        rep.escribirFilaDinamica(8, textos, anchos);
    }
    InordenReportesCitasPorFecha(r->Hder, rep, anchos, fechafiltro);
}

//ELIMINAR AVL

void ArbolCitas::Equilibrar1(pCita& n, bool& Hh)
{
    pCita n1;
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

void ArbolCitas::Equilibrar2(pCita& n, bool& Hh)
{
    pCita n1;
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

void ArbolCitas::Borrar(pCita& aux1, pCita& otro1, bool& Hh)
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
        otro1->idCita = aux1->idCita;
        otro1->idPaciente = aux1->idPaciente;
        otro1->idMedico = aux1->idMedico;
        otro1->idEspecialidad = aux1->idEspecialidad;
        otro1->fecha = aux1->fecha;
        otro1->hora = aux1->hora;
        otro1->motivo = aux1->motivo;
        otro1->estado = aux1->estado;

        otro1 = aux1;        //ahora el q se va a hacer delete es este nodo
        aux1 = aux1->Hizq;   //su hijo izq sube a su lugar
        Hh = true;
    }
}

void ArbolCitas::BorrarBalanceado(pCita& r, bool& Hh, int id)
{
    pCita otro;
    if (r == nullptr) {
        return;
    }

    if (id < r->idCita)
    {
        BorrarBalanceado(r->Hizq, Hh, id);
        if (Hh) {
            Equilibrar1(r, Hh);
        }
    }
    else if (id > r->idCita)
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
        else {// tiene 2 hijos
            Borrar(otro->Hizq, otro, Hh);
            if (Hh) {
                Equilibrar1(r, Hh);
            }
        }
        delete otro;
    }
}

bool ArbolCitas::EliminaNodo(int id)
{
    if (Buscarvalor(raiz, id) == nullptr) {
        return false;
    }
    bool Hh = false;
    BorrarBalanceado(raiz, Hh, id);
    return true;
}

void ArbolCitas::EliminarCita(int idp, int idm, int idc, ArbolPacientes& pacientes, ArbolMedicos& medicos)
{
    pCita nodoesta = Buscarvalor(idc);

    if (nodoesta == nullptr) {
        cout << "No se pudo eliminar la cita porque no existe una cita de id: " << idc << endl;
    }
    else if (pacientes.Buscarvalor(idp) == nullptr) {
        cout << " No existe ningun paciente de id: " << idp << endl;
    }
    else if (medicos.Buscarvalor(idm) == nullptr) {
        cout << " No existe ningun medico de id: " << idm << endl;
    }
    else if (nodoesta->idPaciente != idp || nodoesta->idMedico != idm) {
        cout << "No se pudo eliminar: la cita de id " << idc << " no es del paciente " << idp << " con el medico " << idm << endl;
    }
    else {
        EliminaNodo(idc);
        cout << "Cita de id: " << idc << " eliminada correctamente" << endl;
    }
}

//recorre el arbol y devuelve la primera cita q encuentre de ese paciente
pCita ArbolCitas::BuscarPorPaciente(pCita r, int idp)
{
    if (r == nullptr) {
        return nullptr;
    }
    if (r->idPaciente == idp) {
        return r;
    }
    pCita encontrado = BuscarPorPaciente(r->Hizq, idp);
    if (encontrado != nullptr) {
        return encontrado;
    }
    return BuscarPorPaciente(r->Hder, idp);
}

pCita ArbolCitas::BuscarPorMedico(pCita r, int idm)
{
    if (r == nullptr) {
        return nullptr;
    }
    if (r->idMedico == idm) {
        return r;
    }
    pCita encontrado = BuscarPorMedico(r->Hizq, idm);
    if (encontrado != nullptr) {
        return encontrado;
    }
    return BuscarPorMedico(r->Hder, idm);
}

int ArbolCitas::EliminarCitasDePaciente(int idp)
{
    int cantidad = 0;
    pCita cita = BuscarPorPaciente(raiz, idp);
    while (cita != nullptr) {
        int idc = cita->idCita; //se guarda el id antes de borrar
        EliminaNodo(idc);
        cout << "Cita de id: " << idc << " del paciente " << idp << " eliminada" << endl;
        cantidad++;
        cita = BuscarPorPaciente(raiz, idp);
    }
    return cantidad;
}

int ArbolCitas::EliminarCitasDeMedico(int idm)
{
    int cantidad = 0;
    pCita cita = BuscarPorMedico(raiz, idm);
    while (cita != nullptr) {
        int idc = cita->idCita;
        EliminaNodo(idc);
        cout << "Cita de id: " << idc << " del medico " << idm << " eliminada" << endl;
        cantidad++;
        cita = BuscarPorMedico(raiz, idm);
    }
    return cantidad;
}