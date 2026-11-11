#include <pch.h>
//archivo de diagnosticos
//es arbol AA, y el archivo es Diagnostico.csv
//campos: IdDiagnostico;Nombre;Descripcion

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "crud_diagnostico.h"

//constructor
ArbolDiagnostico::ArbolDiagnostico()
{
    raiz = nullptr;
}

//destructor
ArbolDiagnostico::~ArbolDiagnostico()
{
    destruirArbol(raiz);
}

//metodos privados

void ArbolDiagnostico::Skew(pDiag& r)
{
    if (r == nullptr || r->Hizq == nullptr) return;

    if (r->Hizq->nivel == r->nivel) {
        pDiag izq = r->Hizq;
        r->Hizq = izq->Hder;
        izq->Hder = r;
        r = izq; //el hijo izq sube y pasa a ser la nueva raiz de este subarbol
    }
}

void ArbolDiagnostico::Split(pDiag& r)
{
    if (r == nullptr || r->Hder == nullptr || r->Hder->Hder == nullptr) return;

    if (r->nivel == r->Hder->Hder->nivel) {
        pDiag der = r->Hder;
        r->Hder = der->Hizq;
        der->Hizq = r;
        r = der;     //el hijo der sube
        r->nivel++;  //y su nivel aumenta en 1
    }
}

void ArbolDiagnostico::InsertaAA(pDiag& r, string id, string nom, string desc, bool& insertado)
{
    if (r == nullptr) {
        r = new NodoDiag(id, nom, desc);
        insertado = true;
        return;
    }

    if (id < r->idDiagnostico) {
        InsertaAA(r->Hizq, id, nom, desc, insertado);
    }
    else if (id > r->idDiagnostico) {
        InsertaAA(r->Hder, id, nom, desc, insertado);
    }
    else {
        return; //ya existe, insertado se queda en false y no hay nada q rebalancear
    }

    //de regreso de la recursion se arregla el balance, siempre en orden
    Skew(r);
    Split(r);
}

pDiag ArbolDiagnostico::Buscarvalor(pDiag r, string id)
{
    if (r == nullptr) {
        return nullptr;
    }

    if (id == r->idDiagnostico) {
        return r;
    }
    else if (id < r->idDiagnostico) {
        return Buscarvalor(r->Hizq, id);
    }
    else {
        return Buscarvalor(r->Hder, id);
    }
}

void ArbolDiagnostico::destruirArbol(pDiag r)
{
    if (r == nullptr) return;
    destruirArbol(r->Hizq);
    destruirArbol(r->Hder);
    delete r;
}

//metodos publicos

bool ArbolDiagnostico::InsertaNodo(string id, string nom, string desc)
{
    bool insertado = false;
    InsertaAA(raiz, id, nom, desc, insertado);
    return insertado;
}

pDiag ArbolDiagnostico::Buscarvalor(string id)
{
    return Buscarvalor(raiz, id);
}

void ArbolDiagnostico::InsertarDiagnostico(string id, string nom, string desc)
{
    if (InsertaNodo(id, nom, desc)) {
        cout << "Diagnostico de nombre: " << nom << " con codigo: " << id << " insertado correctamente" << endl;
    }
    else {
        cout << "No se pudo insertar el diagnostico ya que ya existe un diagnostico de codigo: " << id << endl;
    }
}

void ArbolDiagnostico::leerArchivo(const char* nombreArchivo)
{
    cout << "------------------ chunches diagnosticos" << endl;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open() == false) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string iddiag, nombre, descripcion;
    string filaencabezado;

    getline(archivo, filaencabezado); //el encabezado no se borra del archivo

    while (getline(archivo, iddiag, ';')) {
        getline(archivo, nombre, ';');
        getline(archivo, descripcion); //ultimo campo de la fila no lleva delimitante
        //int iddiagint = stoi(iddiag);
        InsertarDiagnostico(iddiag, nombre, descripcion);
    }
    archivo.close();
}

void ArbolDiagnostico::BuscarMostrar(string id)
{
    pDiag nodoesta = Buscarvalor(id);

    if (nodoesta != nullptr) {
        cout << "Diagnostico encontrado" << endl;
        cout << "Id de diagnostico: " << nodoesta->idDiagnostico << endl;
        cout << "Nombre: " << nodoesta->nombre << endl;
        cout << "Descripcion: " << nodoesta->descripcion << endl;
    }
    else {
        cout << "No existe ningun diagnostico de codigo: " << id << endl;
    }
}

void ArbolDiagnostico::ModificarDiag(string id, string nuevaDesc) {
    pDiag nodoesta = Buscarvalor(id);
    if (nodoesta == nullptr) {
        cout << "No se pudo realizar esa modificacion ya que el diagnostico de id " << id << " no existe" << endl;
    }
    else {
        cout << "Diagnostico de id " << id << " modificado, su nueva descripcion es: " << nuevaDesc << endl;
        nodoesta->descripcion = nuevaDesc;
    }
}

void ArbolDiagnostico::InordenReportesDiag(pDiag r, reportes& rep, int anchos[]) {
    if (r == nullptr) {
        return;
    }
    InordenReportesDiag(r->Hizq, rep, anchos);
    string textos[] = { r->idDiagnostico, r->nombre, r->descripcion };
    rep.escribirFilaDinamica(3, textos, anchos);
    InordenReportesDiag(r->Hder, rep, anchos);
}


// chunches eliminar ------------------------------------------------------------------------------------

bool ArbolDiagnostico::EliminaNodo(string id) {
    bool eliminado = false;
    raiz = EliminaRec(raiz, id, eliminado);
    return eliminado;
}

pDiag ArbolDiagnostico::EliminaRec(pDiag r, string id, bool& eliminado) {
    if (r == nullptr) {
        return nullptr;
    }

    if (id < r->idDiagnostico)
    {
        r->Hizq = EliminaRec(r->Hizq, id, eliminado);
    }
    else if (id > r->idDiagnostico)
    {
        r->Hder = EliminaRec(r->Hder, id, eliminado);
    }
    else {
        eliminado = true; // si se me vuelve a olvidar el eliminado = true empezare a cometer crimenes contra la humanidad -_-

        /*
        // hoja
        if (r->Hizq == nullptr and r->Hder == nullptr) {
            delete r;
            return nullptr;
        }

        // 1 hijo
        if (r->Hizq == nullptr) {
            pDiag temp = r->Hder;
            delete r;
            return temp;
        }

        else if (r->Hder == nullptr)
        {
            pDiag temp = r->Hizq;
            delete r;
            return temp;
        }
        */

        // hoja o 1 hijo'
        if (r->Hizq == nullptr) {
            pDiag temp = r->Hder;
            delete r;
            return temp;
        }
        else if (r->Hder == nullptr) {
            pDiag temp = r->Hizq;
            delete r;
            return temp;
        }
        // ^ hice aca arriba y abajo de lo de 2 hijos el mismo fix de esp, pq ambos tenian el mismo problemilla
        else {
            // 2 hijos
            pDiag sucesor = r->Hder;
            while (sucesor->Hizq != nullptr) {
                sucesor = sucesor->Hizq;
            }
            r->idDiagnostico = sucesor->idDiagnostico;
            r->nombre = sucesor->nombre;
            r->descripcion = sucesor->descripcion;
            r->Hder = EliminaRec(r->Hder, sucesor->idDiagnostico, eliminado);
        }

    }
    if (r == nullptr) {
        return nullptr;
    }


    int nivelEsperado = 1;
    if (r->Hizq != nullptr) {
        nivelEsperado = r->Hizq->nivel + 1;
    }

    if (r->Hder != nullptr and r->Hder->nivel + 1 < nivelEsperado) {
        nivelEsperado = r->Hder->nivel + 1;
    }

    if (nivelEsperado < r->nivel) {
        r->nivel = nivelEsperado;
        if (r->Hder != nullptr and r->Hder->nivel > nivelEsperado) {
            r->Hder->nivel = nivelEsperado;
        }
    }

    Skew(r);
    if (r->Hder != nullptr) {
        Skew(r->Hder);
        if (r->Hder->Hder != nullptr) {
            Skew(r->Hder->Hder);
        }
    }

    Split(r);
    if (r->Hder != nullptr) {
        Split(r->Hder);
    }

    return r;
}



        /*
        // 2 hijos
        pDiag sucesor = r->Hder;
        while (sucesor->Hizq != nullptr)
            sucesor = sucesor->Hizq;

        r->idDiagnostico = sucesor->idDiagnostico;
        r->nombre = sucesor->nombre;
        r->descripcion = sucesor->descripcion;
        r->Hder = EliminaRec(r->Hder, sucesor->idDiagnostico, eliminado);

        // ajuste
        int nivelEsperado = 1;
        if (r->Hizq != nullptr) {
            nivelEsperado = r->Hizq->nivel + 1;
        }
        if (r->Hder != nullptr and r->Hder->nivel + 1 < nivelEsperado) {
            nivelEsperado = r->Hder->nivel + 1;
        }

        if (nivelEsperado < r->nivel) {
            r->nivel = nivelEsperado;

            if (r->Hder != nullptr and r->Hder->nivel > nivelEsperado) {
                r->Hder->nivel = nivelEsperado;
            }
        }

        Skew(r);
        Split(r);

        if (r->Hder != nullptr) {
            Split(r->Hder);
        }

        if (r->Hder != nullptr and r->Hder->Hder != nullptr) {
            Split(r->Hder->Hder);
        }

        return r;
    }
}
*/
void ArbolDiagnostico::EliminarDiagnostico(string id) {
    if (EliminaNodo(id) == true) {
        cout << "Diagnostico de id: " << id << " eliminada correctamente" << endl;
    }
    else {
        cout << "No se pudo eliminar el diagnostico de id: " << id << " porque no existe" << endl;
    }
}