#ifndef CRUD_PAISES_H
#define CRUD_PAISES_H

// es _H, no .H
// ademas de que por convencion de noseque el header va en mayus
// la parte del funcionamiento de los metodos va en el de crud_paises.cpp

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "reportes.h"


class ArbolCiudad;
class ArbolPacientes;
class ArbolCitas;
class ArbolHospitalizaciones;

class NodoPais {
public:
	int codPais;
	string nombre;
	NodoPais* Hizq;
	NodoPais* Hder;



	NodoPais(int cod, string nom) {
		codPais = cod;
		nombre = nom;
		Hizq = nullptr;
		Hder = nullptr;
	}
	friend class ArbolPais;
    friend class reportes;
    
};
typedef NodoPais* pPais;

class ArbolPais { // todo esto lo pegue directo de ABBusqueda.cpp y ABBusqueda.h, solo q le cambie nombres y puse codPais y nombre
// tambien le quite algunos metodos q no ibamos a ocupar y q pedian los chunches de pila/cola q me da pereza volver a copiar y pegar
friend class reportes; // para paises en reportes
private:
    pPais raiz;

    // Metodos auxiliares privados
    pPais InsertaBinario(pPais raiz, int cod, string nom, bool& insertado);
    pPais Buscarvalor(pPais raiz, int cod);
    pPais EliminarBinario(pPais raiz, int cod, bool& eliminado);
    void destruirArbol(pPais raiz);

public:
    ArbolPais();
    ~ArbolPais();

    bool InsertaNodo(int cod, string nom);
    bool EliminaNodo(int cod);
    pPais Buscarvalor(int cod);

    void InsertarPais(int cod, string nom);
    void leerArchivo(const char* nombreArchivo);
    void BuscarMostrar(int cod);
    void ModificarPais(int cod, string nuevoNom);
    void InordenReportesPais(pPais raiz, reportes& rep, int anchos[]);
    void EliminarPais(int cod, ArbolCiudad& ciudades, ArbolPacientes& pacientes, ArbolCitas& citas, ArbolHospitalizaciones& hosp);
    pPais encontrarMin(pPais raiz); // este se ocupaba para las elim
};
#endif