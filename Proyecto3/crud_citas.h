#ifndef CRUD_CITAS_H
#define CRUD_CITAS_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "crud_medicos.h"
#include "crud_pacientes.h"
#include "reportes.h"


class NodoCita {
public:
    int idCita;
    int idPaciente;
    int idMedico;
    int idEspecialidad;
    string fecha;
    string hora;
    string motivo;
    int estado;
    int FB;
    NodoCita* Hizq;
    NodoCita* Hder;


    NodoCita(int idc, int idp, int idm, int idesp, string fch, string hra, string mtivo, int est) {
        idCita = idc;
        idPaciente = idp;
        idMedico = idm;
        idEspecialidad = idesp;
        fecha = fch;
        hora = hra;
        motivo = mtivo;
        estado = est;
        FB = 0;
        Hizq = nullptr;
        Hder = nullptr;
    }
    friend class ArbolCitas;
    friend class reportes;
};

typedef NodoCita* pCita;

class ArbolCitas {
    friend class reportes;
private:
    pCita raiz;


    void InsertarBalanceado(pCita& r, bool& Hh, int idc, int idp, int idm, int idesp, string fch, string hra, string mtivo, int est);
    void RotacionSimpleIzquierda(pCita& n, pCita& n1);
    void RotacionSimpleDerecha(pCita& n, pCita& n1);
    void RotacionDobleIzquierda(pCita& n, pCita& n1);
    void RotacionDobleDerecha(pCita& n, pCita& n1);
    pCita Buscarvalor(pCita r, int id);
    void LiberarMemoria(pCita r);

    //eliminar AVL
    void BorrarBalanceado(pCita& r, bool& Hh, int id);
    void Borrar(pCita& aux1, pCita& otro1, bool& Hh);
    void Equilibrar1(pCita& n, bool& Hh);
    void Equilibrar2(pCita& n, bool& Hh);
    pCita BuscarPorPaciente(pCita r, int idp);
    pCita BuscarPorMedico(pCita r, int idm);

public:

    ArbolCitas();
    ~ArbolCitas();

    bool InsertaNodo(int idc, int idp, int idm, int idesp, string fch, string hra, string mtivo, int est);
    pCita Buscarvalor(int id);

    void InsertarCita(int idc, int idp, int idm, int idesp, string fch, string hra, string mtivo, int est, ArbolPacientes& pacientes, ArbolMedicos& medicos);
    void leerArchivo(const char* nombreArchivo, ArbolPacientes& pacientes, ArbolMedicos& medicos);
    void BuscarMostrar(int idp, int idm, int id, ArbolPacientes& pacientes, ArbolMedicos& medicos);
    void ModificarCita(int idp, int idm, int idc, string motivo, int estado, ArbolPacientes& pacientes, ArbolMedicos& medicos);
    void InordenReportesCitasPorPaciente(pCita r, reportes& rep, int anchos[], int IdPacFiltro);
    void InordenReportesCitasPorMedico(pCita r, reportes& rep, int anchos[], int idMedFiltro);
    void InordenReportesCitasPorEspecialidad(pCita r, reportes& rep, int anchos[], int idEspFiltro);
    void InordenReportesCitasPorFecha(pCita r, reportes& rep, int anchos[], string fecha);

    //eliminar
    bool EliminaNodo(int id);
    void EliminarCita(int idp, int idm, int idc, ArbolPacientes& pacientes, ArbolMedicos& medicos);
    int EliminarCitasDePaciente(int idp); //cuando se elimine un paciente
    int EliminarCitasDeMedico(int idm);   //cuando se elimine un medico
};


#endif
