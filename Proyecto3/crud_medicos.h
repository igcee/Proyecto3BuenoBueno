#ifndef CRUD_MEDICOS_H
#define CRUD_MEDICOS_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "crud_especialidades.h" //para validar q la especialidad exista
#include "reportes.h"
// Arbol B

const int MAXMED = 4;
const int MINMED = 2;

class NodoMedico { //es el dato (la clave) q se guarda dentro de las paginas
public:
    int idMedico;
    string nombre;
    string telefono;
    string correo;
    int idEspecialidad;


    NodoMedico() {
        idMedico = 0;
        idEspecialidad = 0;
    }
    NodoMedico(int id, string nom, string tel, string cor, int idesp) {
        idMedico = id;
        nombre = nom;
        telefono = tel;
        correo = cor;
        idEspecialidad = idesp;
    }
    friend class ArbolMedicos;
    friend class reportes;
};
typedef NodoMedico* pMedico;

class PaginaMedico { //es el nodo del arbol B
    int cuenta;
    NodoMedico claves[MAXMED + 1];
    PaginaMedico* ramas[MAXMED + 1];

public:
    PaginaMedico() {
        cuenta = 0;
        for (int i = 0; i <= MAXMED; i++) {
            ramas[i] = nullptr;
        }
    }
    friend class ArbolMedicos;
    friend class reportes;
};
typedef PaginaMedico* pPagMed;

class ArbolCitas;

class ArbolMedicos {
    friend class reportes;
private:
    pPagMed raiz;

    void Insertar(NodoMedico cl);
    void Empujar(pPagMed actual, NodoMedico cl, bool& subeArriba, NodoMedico& mediana, pPagMed& nuevo);
    bool BuscarNodo(pPagMed actual, int id, int& k);
    void MeterHoja(pPagMed actual, NodoMedico cl, pPagMed rd, int k);
    void DividirNodo(pPagMed actual, NodoMedico cl, pPagMed rd, int k, NodoMedico& mediana, pPagMed& nuevo);
    pMedico Buscarvalor(pPagMed r, int id);
    void destruirArbol(pPagMed r);

    //eliminar (arbol B)
    void EliminarRegistro(pPagMed actual, int id, bool& encontrado);
    void Quitar(pPagMed actual, int k);
    void Sucesor(pPagMed actual, int k);
    void Restablecer(pPagMed actual, int k);
    void MoverDerecha(pPagMed actual, int k);
    void MoverIzquierda(pPagMed actual, int k);
    void Combina(pPagMed actual, int k);
    pMedico BuscarPorEspecialidad(pPagMed r, int idesp);

public:
    ArbolMedicos();
    ~ArbolMedicos();

    bool InsertaNodo(int id, string nom, string tel, string cor, int idesp);
    pMedico Buscarvalor(int id); //lo usa Hospitalizaciones (y Citas) para validar que el medico exista

    void InsertarMedico(int id, string nombre, string telefono, string correo, int idesp, ArbolEspecialidad& esp);
    void leerArchivo(const char* nombreArchivo, ArbolEspecialidad& esp);
    void BuscarMostrar(int idesp, int id, ArbolEspecialidad& esp);
    void ModificarMedico(int idesp, int id, string telefono, string correo, ArbolEspecialidad& esp);
    //Medicos necesita validar q la especialidad exista, se pasa como parametro x referencia
    void InordenReportesMedicos(pPagMed r, reportes& rep, int anchos[]);
    void InordenReportesMedicosPorEspecialidad(pPagMed r, reportes& rep, int anchos[], int idespfiltro);

    //eliminar
    bool EliminaNodo(int id);
    void EliminarMedico(int id, ArbolCitas& citas);
    int EliminarMedicosDeEspecialidad(int idesp, ArbolCitas& citas); //para cuando se elimine una especialidad
};
#endif