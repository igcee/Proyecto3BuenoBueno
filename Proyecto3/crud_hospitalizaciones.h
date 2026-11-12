#ifndef CRUD_HOSPITALIZACIONES_H
#define CRUD_HOSPITALIZACIONES_H

#include <iostream>
#include <fstream>
#include <string>
#include "crud_pacientes.h"
#include "crud_habitaciones.h"
#include "crud_medicos.h"

using namespace std;
#include "reportes.h"

class NodoHosp {
public:
    int idHospitalizacion;
    int idPaciente;
    int idHabitacion;
    int idMedico;
    string fechaIngreso;
    string fechaSalida;
    string motivo;
    bool color;
    NodoHosp* padre;
    NodoHosp* Hizq;
    NodoHosp* Hder;


    NodoHosp(int idHosp, int idPac, int idHab, int idMed, string fIngreso, string fSalida, string mot) {
        idHospitalizacion = idHosp;
        idPaciente = idPac;
        idHabitacion = idHab;
        idMedico = idMed;
        fechaIngreso = fIngreso;
        fechaSalida = fSalida;
        motivo = mot;
        color = true;
        padre = nullptr;
        Hizq = nullptr;
        Hder = nullptr;
    }
    friend class ArbolHospitalizaciones;
    friend class ArbolHabitaciones;
    //friend class ArbolMedicos
};
typedef NodoHosp* pHosp;

class ArbolHospitalizaciones {
    friend class reportes;
    //friend class ArbolMedico
private:
    pHosp raiz;

    void InsertarRN(pHosp nuevo);
    void ArreglaInsercion(pHosp nodo);
    void RotIzquierda(pHosp x);
    void RotDerecha(pHosp x);
    pHosp Buscarvalor(pHosp r, int id);
    void LiberarMemoria(pHosp r);
    void EliminarHosp(pHosp idhosp);
    void Sustitucion(pHosp idhosp1, pHosp idhosp2);
    pHosp Minimo(pHosp raiz);
    void ArreglaEliminacion(pHosp x);

public:
    ArbolHospitalizaciones();
    ~ArbolHospitalizaciones();

    bool InsertaNodo(int idHosp, int idPac, int idHab, int idMed, string ingreso, string salida, string mot);
    pHosp Buscarvalor(int id);

    void InsertarHospitalizacion(int idHosp, int idPac, int idHab, int idMed, string fIngreso, string fSalida, string mot, ArbolPacientes& pacientes, ArbolHabitaciones& habitaciones, ArbolMedicos& medicos);
    void leerArchivo(const char* nombreArchivo, ArbolPacientes& pacientes, ArbolHabitaciones& habitaciones, ArbolMedicos& medicos);
    void BuscarMostrar(int idPac, int idHab, int idHosp, ArbolPacientes& pacientes, ArbolHabitaciones& habitaciones);
    void ModificarHosp(int idPac, int idHab, int idHosp, string nuevoMotivo, ArbolPacientes& pacientes, ArbolHabitaciones& habitaciones);
    void InordenReportesHosp(pHosp r, reportes& rep, int anchos[]);
    void InordenReportesHospDeMedico(pHosp r, reportes& rep, int anchos[], int IdMedico);

    bool EliminaNodo(int id);
    void EliminarHospitalizacion(int idPac, int idHab, int idHosp, ArbolPacientes& pacientes, ArbolHabitaciones& habitaciones);

    // ese es para cascada, de q borrar habitacion tambien borra hosp
    void EliminarHospPorHab(pHosp nodo, int idHab);
};

#endif
