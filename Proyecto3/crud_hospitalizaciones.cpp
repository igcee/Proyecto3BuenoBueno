#include <pch.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "crud_hospitalizaciones.h"

ArbolHospitalizaciones::ArbolHospitalizaciones() {
    raiz = nullptr;
}

ArbolHospitalizaciones::~ArbolHospitalizaciones() {
    LiberarMemoria(raiz);
}


void ArbolHospitalizaciones::InsertarRN(pHosp nuevo) {
    //insercion normal de arbol binario de busqueda -sin balancear todavia
    // entes de llamar esto ya se reviso q el id no exista, entonces aca no hay iguales
    pHosp actual = raiz;
    pHosp papa = nullptr;

    while (actual != nullptr) {
        papa = actual;
        if (nuevo->idHospitalizacion < actual->idHospitalizacion)
            actual = actual->Hizq;
        else
            actual = actual->Hder;
    }

    nuevo->padre = papa;

    if (papa == nullptr) {
        raiz = nuevo;
    }
    else if (nuevo->idHospitalizacion < papa->idHospitalizacion) {
        papa->Hizq = nuevo;
    }
    else {
        papa->Hder = nuevo;
    }
}

void ArbolHospitalizaciones::ArreglaInsercion(pHosp nodo) {
    //mientras el padre sea rojo hay 2 rojos seguidos, o sea q se rompe una regla
    while (nodo != raiz and nodo->padre != nullptr and nodo->padre->color == true) {
        pHosp papa = nodo->padre;
        pHosp abuelo = papa->padre;

        if (abuelo == nullptr) break; //el padre es la raiz (y la raiz es negra, no deberia pasar)

        pHosp tio;
        bool papaEsIzquierdo;

        if (abuelo->Hizq == papa) {
            papaEsIzquierdo = true;
            tio = abuelo->Hder;
        }
        else {
            papaEsIzquierdo = false;
            tio = abuelo->Hizq;
        }

        if (tio != nullptr and tio->color == true) {
            //Caso 1: tio rojo -> solo se recolorea y se sigue subiendo con el abuelo
            papa->color = false;
            tio->color = false;
            abuelo->color = true;
            nodo = abuelo;
        }
        else {
            // tio negro (o null) -> hay que rotar
            if (papaEsIzquierdo) {
                if (nodo == papa->Hder) {
                    //Caso 2:nodo es hijo derecho -> rotar izq en el padre para volverlo caso 3
                    nodo = papa;
                    RotIzquierda(nodo);
                    papa = nodo->padre;
                    abuelo = papa->padre;
                }
                //Caso 3: rotar derecha en el abuelo
                papa->color = false;
                abuelo->color = true;
                RotDerecha(abuelo);
            }
            else {
                if (nodo == papa->Hizq) {
                    //Caso 2 espejo
                    nodo = papa;
                    RotDerecha(nodo);
                    papa = nodo->padre;
                    abuelo = papa->padre;
                }
                // Caso 3 espejo: rotar izquierda en el abuelo
                papa->color = false;
                abuelo->color = true;
                RotIzquierda(abuelo);
            }
            break;
        }
    }
    raiz->color = false; //la raiz siempre negra
}

void ArbolHospitalizaciones::RotIzquierda(pHosp nodo) {
    pHosp hijoDer = nodo->Hder;
    nodo->Hder = hijoDer->Hizq;

    if (hijoDer->Hizq != nullptr)
        hijoDer->Hizq->padre = nodo;

    hijoDer->padre = nodo->padre;

    if (nodo->padre == nullptr)
        raiz = hijoDer;
    else if (nodo == nodo->padre->Hizq)
        nodo->padre->Hizq = hijoDer;
    else
        nodo->padre->Hder = hijoDer;

    hijoDer->Hizq = nodo;
    nodo->padre = hijoDer;
}

void ArbolHospitalizaciones::RotDerecha(pHosp nodo) {
    pHosp hijoIzq = nodo->Hizq;
    nodo->Hizq = hijoIzq->Hder;

    if (hijoIzq->Hder != nullptr)
        hijoIzq->Hder->padre = nodo;

    hijoIzq->padre = nodo->padre;

    if (nodo->padre == nullptr)
        raiz = hijoIzq;
    else if (nodo == nodo->padre->Hder)
        nodo->padre->Hder = hijoIzq;
    else
        nodo->padre->Hizq = hijoIzq;

    hijoIzq->Hder = nodo;
    nodo->padre = hijoIzq;
}

pHosp ArbolHospitalizaciones::Buscarvalor(pHosp r, int id) {
    if (r == nullptr) return nullptr;
    if (id == r->idHospitalizacion) return r;
    else if (id < r->idHospitalizacion) return Buscarvalor(r->Hizq, id);
    else return Buscarvalor(r->Hder, id);
}

void ArbolHospitalizaciones::LiberarMemoria(pHosp r) {
    if (r == nullptr) return;
    LiberarMemoria(r->Hizq);
    LiberarMemoria(r->Hder);
    delete r;
}


bool ArbolHospitalizaciones::InsertaNodo(int idHosp, int idPac, int idHab, int idMed, string fIngreso, string fSalida, string mot) {
    if (Buscarvalor(raiz, idHosp) != nullptr) {
        return false; //ya existe, no se crea el nodo
    }
    pHosp nuevo = new NodoHosp(idHosp, idPac, idHab, idMed, fIngreso, fSalida, mot);
    InsertarRN(nuevo);
    ArreglaInsercion(nuevo);
    return true;
}

pHosp ArbolHospitalizaciones::Buscarvalor(int id) {
    return Buscarvalor(raiz, id);
}

void ArbolHospitalizaciones::InsertarHospitalizacion(int idHosp, int idPac, int idHab, int idMed, string fIngreso, string fSalida, string mot, ArbolPacientes& pacientes, ArbolHabitaciones& habitaciones, ArbolMedicos& medicos) {
    if (pacientes.Buscarvalor(idPac) == nullptr) {
        cout << "Error: El paciente con ID " << idPac << " no existe." << endl;
        return;
    }
    if (habitaciones.Buscarvalor(idHab) == nullptr) {
        cout << "Error: La habitacion con ID " << idHab << " no existe." << endl;
        return;
    }
    if (medicos.Buscarvalor(idMed) == nullptr) {
        cout << "Error: El medico con ID " << idMed << " no existe." << endl;
        return;
    }

    if (InsertaNodo(idHosp, idPac, idHab, idMed, fIngreso, fSalida, mot)) {
        cout << "Hospitalizacion ID: " << idHosp << " insertada correctamente." << endl;
    }
    else {
        cout << "Error: Ya existe una hospitalizacion con el ID " << idHosp << "." << endl;
    }
}

void ArbolHospitalizaciones::leerArchivo(const char* nombreArchivo, ArbolPacientes& pacientes, ArbolHabitaciones& habitaciones, ArbolMedicos& medicos) {
    cout << "------------------ chunches hospitalizaciones" << endl;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open() == false) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string idHosp, idPac, idHab, idMed, fIngreso, fSalida, motivo;
    string filaencabezado;
    getline(archivo, filaencabezado);

    while (getline(archivo, idHosp, ';')) {
        getline(archivo, idPac, ';');
        getline(archivo, idHab, ';');
        getline(archivo, idMed, ';');
        getline(archivo, fIngreso, ';');
        getline(archivo, fSalida, ';');
        getline(archivo, motivo);

        InsertarHospitalizacion(stoi(idHosp), stoi(idPac), stoi(idHab), stoi(idMed), fIngreso, fSalida, motivo, pacientes, habitaciones, medicos);
    }
    archivo.close();
}

void ArbolHospitalizaciones::BuscarMostrar(int idPac, int idHab, int idHosp, ArbolPacientes& pacientes, ArbolHabitaciones& habitaciones) {
    if (pacientes.Buscarvalor(idPac) == nullptr) {
        cout << "Error: El paciente " << idPac << " no existe." << endl;
        return;
    }
    if (habitaciones.Buscarvalor(idHab) == nullptr) {
        cout << "Error: La habitacion " << idHab << " no existe." << endl;
        return;
    }

    pHosp nodoesta = Buscarvalor(idHosp);
    if (nodoesta != nullptr) {
        if (nodoesta->idPaciente != idPac || nodoesta->idHabitacion != idHab) {
            cout << "La hospitalizacion " << idHosp << " existe, pero NO pertenece al paciente " << idPac << " o a la habitacion " << idHab << "." << endl;
            return;
        }
        cout << "==== Hospitalizacion Encontrada ====" << endl;
        cout << "ID Hosp: " << nodoesta->idHospitalizacion << endl;
        cout << "Paciente ID: " << nodoesta->idPaciente << endl;
        cout << "Habitacion ID: " << nodoesta->idHabitacion << endl;
        cout << "Medico ID: " << nodoesta->idMedico << endl;
        cout << "Ingreso: " << nodoesta->fechaIngreso << endl;
        cout << "Salida: " << nodoesta->fechaSalida << endl;
        cout << "Motivo: " << nodoesta->motivo << endl;
    }
    else {
        cout << "No existe ninguna hospitalizacion de codigo: " << idHosp << endl;
    }
}

void ArbolHospitalizaciones::ModificarHosp(int idPac, int idHab, int idHosp, string nuevoMotivo, ArbolPacientes& pacientes, ArbolHabitaciones& habitaciones) {
    if (pacientes.Buscarvalor(idPac) == nullptr) {
        cout << "Error: El paciente " << idPac << " no existe." << endl;
        return;
    }
    if (habitaciones.Buscarvalor(idHab) == nullptr) {
        cout << "Error: La habitacion " << idHab << " no existe." << endl;
        return;
    }

    pHosp nodoesta = Buscarvalor(idHosp);
    if (nodoesta == nullptr) {
        cout << "No existe ninguna hospitalizacion de codigo: " << idHosp << endl;
    }
    else {
        if (nodoesta->idPaciente != idPac or nodoesta->idHabitacion != idHab) {
            cout << "La hospitalizacion " << idHosp << " existe, pero NO pertenece al paciente " << idPac << " o a la habitacion " << idHab << endl;
            return;
        }

        cout << "Hospitalizacion " << idHosp << " modificada, motivo anterior era:"<< nodoesta->motivo<< " , ahora es:" << nuevoMotivo << endl;
        nodoesta->motivo = nuevoMotivo;
    }
}

void ArbolHospitalizaciones::InordenReportesHosp(pHosp r, reportes& rep, int anchos[]) {
    if (r == nullptr) {
        return;
    }
    InordenReportesHosp(r->Hizq, rep, anchos);
    string textos[] = { to_string(r->idHospitalizacion), to_string(r->idPaciente), to_string(r->idHabitacion), to_string(r->idMedico), r->fechaIngreso, r->fechaSalida, r->motivo };
    rep.escribirFilaDinamica(7, textos, anchos);
    InordenReportesHosp(r->Hder, rep, anchos);

}

void ArbolHospitalizaciones::InordenReportesHospDeMedico(pHosp r, reportes& rep, int anchos[], int MedicoFiltro) {
    if (r == nullptr) {
        return;
    }
    InordenReportesHospDeMedico(r->Hizq, rep, anchos, MedicoFiltro);
    if (r->idMedico == MedicoFiltro) {
        string textos[] = { to_string(r->idMedico), to_string(r->idPaciente), to_string(r->idHabitacion), to_string(r->idHospitalizacion), r->fechaIngreso, r->fechaSalida, r->motivo };
        rep.escribirFilaDinamica(7, textos, anchos);
    }
    InordenReportesHospDeMedico(r->Hder, rep, anchos, MedicoFiltro);

}

// chunches eliminar --------------------------------------------------------------------------------------
bool ArbolHospitalizaciones::EliminaNodo(int idhosp) {
    pHosp nodo = Buscarvalor(raiz, idhosp);
    if (nodo == nullptr) { //no esta
        return false;
    }
   
    EliminarHosp(nodo);
    return true;
}


void ArbolHospitalizaciones::EliminarHosp(pHosp idhosp)
{
    pHosp y = idhosp;
    pHosp x;
    pHosp xPadre = nullptr;
    bool yOriginalColor = y->color;

    if (idhosp->Hizq == nullptr)
    {
        x = idhosp->Hder;
        xPadre = idhosp->padre;
        Sustitucion(idhosp, idhosp->Hder);
    }
    else
        if (idhosp->Hder == nullptr)
        {
            x = idhosp->Hizq;
            xPadre = idhosp->padre;
            Sustitucion(idhosp, idhosp->Hizq);
        }
        else
        {
            y = Minimo(idhosp->Hder);
            yOriginalColor = y->color;
            x = y->Hder;
            xPadre = y->padre;

            if (y->padre == idhosp)
            {
                xPadre = y;
                if (x != nullptr)
                    x->padre = y;
            }
            else
            {
                Sustitucion(y, y->Hder);
                y->Hder = idhosp->Hder;
                if (y->Hder != nullptr)
                    y->Hder->padre = y;
            }

            Sustitucion(idhosp, y);
            y->Hizq = idhosp->Hizq;
            if (y->Hizq != nullptr)
                y->Hizq->padre = y;
            y->color = idhosp->color;
        }

    delete idhosp;

    if (!yOriginalColor)
    {
        // Si x es nullptr, crea nodo temp
        if (x == nullptr)
        {
            pHosp centinela = new NodoHosp(0, 0, 0, 0, "", "", ""); // esto lo acmbie de lo de la profe pq para el nodo sin nada no sirve con solo NodoHosp(0)\
            // si o si tenia q contener "algo" para todos los valores q tiene el nodo para hosp, sino se jodia
            centinela->color = false;
            centinela->padre = xPadre;
            centinela->Hizq = nullptr;
            centinela->Hder = nullptr;

            // Conectar el centinela al padre
            if (xPadre != nullptr)
            {
                if (xPadre->Hizq == nullptr)
                    xPadre->Hizq = centinela;
                else
                    xPadre->Hder = centinela;
            }

            ArreglaEliminacion(centinela);

            // Desconectar y eliminar el centinela
            if (xPadre != nullptr)
            {
                if (xPadre->Hizq == centinela)
                    xPadre->Hizq = nullptr;
                if (xPadre->Hder == centinela)
                    xPadre->Hder = nullptr;
            }

            delete centinela;
        }
        else
        {
            ArreglaEliminacion(x);
        }
    }
}


void ArbolHospitalizaciones::Sustitucion(pHosp idhosp1, pHosp idhosp2) {
    if (idhosp1->padre == nullptr)
    {
        raiz = idhosp2;
    }
    else
        if (idhosp1 == idhosp1->padre->Hizq)
        {
            idhosp1->padre->Hizq = idhosp2;
        }
        else
        {
            idhosp1->padre->Hder = idhosp2;
        }

    if (idhosp2 != nullptr)
    {
        idhosp2->padre = idhosp1->padre;
    }
}

pHosp ArbolHospitalizaciones::Minimo(pHosp nodo) {
    while (nodo->Hizq != nullptr)
    {
        nodo = nodo->Hizq;
    }
    return nodo;
}


void ArbolHospitalizaciones::ArreglaEliminacion(pHosp x)
{
    while (x != raiz and x->color == false)
    {
        if (x->padre == nullptr)
            break;

        if (x == x->padre->Hizq)
        {
            pHosp w = x->padre->Hder;

            // hermano es rojo
            if (w != nullptr and w->color == true)
            {
                w->color = false;
                x->padre->color = true;
                RotIzquierda(x->padre);
                w = x->padre->Hder;
            }

            if (w == nullptr)
            {
                x = x->padre;
                continue;
            }

            //  hermano es negro y ambos hijos del hermano son negros
            if ((w->Hizq == nullptr or w->Hizq->color == false) and (w->Hder == nullptr or w->Hder->color == false))
            {
                w->color = true;
                x = x->padre;
            }
            else
            {
                //  hermano negro, hijo der del hermano es negro, hijo izq es rojo
                if (w->Hder == nullptr or w->Hder->color == false)
                {
                    if (w->Hizq != nullptr)
                        w->Hizq->color = false;
                    w->color = true;
                    RotDerecha(w);
                    w = x->padre->Hder;
                }

                // Caso 4: hermano es negro, hijo derecho del hermano es rojo
                if (w != nullptr)
                {
                    w->color = x->padre->color;
                    x->padre->color = false;
                    if (w->Hder != nullptr)
                        w->Hder->color = false;
                    RotIzquierda(x->padre);
                }
                x = raiz;
            }
        }
        else
        {
            // Casos simetricos (x es hijo derecho)
            pHosp w = x->padre->Hizq;

            // Caso 1 simetrico
            if (w != nullptr and w->color == true)
            {
                w->color = false;
                x->padre->color = true;
                RotDerecha(x->padre);
                w = x->padre->Hizq;
            }

            if (w == nullptr)
            {
                x = x->padre;
                continue;
            }

            // Caso 2 simetrico
            if ((w->Hder == nullptr or w->Hder->color == false) and (w->Hizq == nullptr or w->Hizq->color == false))
            {
                w->color = true;
                x = x->padre;
            }
            else {
                // simetrico
                if (w->Hizq == nullptr or w->Hizq->color == false)
                {
                    if (w->Hder != nullptr)
                        w->Hder->color = false;
                    w->color = true;
                    RotIzquierda(w);
                    w = x->padre->Hizq;
                }

                // simetrico
                if (w != nullptr)
                {
                    w->color = x->padre->color;
                    x->padre->color = false;
                    if (w->Hizq != nullptr)
                        w->Hizq->color = false;
                    RotDerecha(x->padre);
                }
                x = raiz;
            }
        }
    }

    if (x != nullptr)
        x->color = false;
}



void ArbolHospitalizaciones::EliminarHospitalizacion(int idPac, int idHab, int idHosp, ArbolPacientes& pacientes, ArbolHabitaciones& habitaciones) {
    if (pacientes.Buscarvalor(idPac) == nullptr) {
        cout << "Error: El paciente de id " << idPac << " no existe." << endl;
        return;
    }
    if (habitaciones.Buscarvalor(idHab) == nullptr) {
        cout << "Error: La habitacion de id " << idHab << " no existe." << endl;
        return;
    }

    pHosp nodoesta = Buscarvalor(idHosp);
    if (nodoesta == nullptr) {
        cout << "No existe ninguna hospitalizacion de codigo: " << idHosp << endl;
    }
    else if (nodoesta->idPaciente != idPac or nodoesta->idHabitacion != idHab) {
        cout << "La hospitalizacion " << idHosp << " existe, pero NO pertenece al paciente " << idPac << " o a la habitacion " << idHab << endl;
    }
    else {
        EliminaNodo(idHosp);
        cout << "Hospitalizacion " << idHosp << " eliminada correctamente" << endl;
    }
}

//ELIMINAR EN CASCADA
pHosp ArbolHospitalizaciones::BuscarPorPaciente(pHosp r, int idPac) {
    if (r == nullptr) return nullptr;
    if (r->idPaciente == idPac) return r;
    pHosp encontrado = BuscarPorPaciente(r->Hizq, idPac);
    if (encontrado != nullptr) return encontrado;
    return BuscarPorPaciente(r->Hder, idPac);
}

pHosp ArbolHospitalizaciones::BuscarPorHabitacion(pHosp r, int idHab) {
    if (r == nullptr) return nullptr;
    if (r->idHabitacion == idHab) return r;
    pHosp encontrado = BuscarPorHabitacion(r->Hizq, idHab);
    if (encontrado != nullptr) return encontrado;
    return BuscarPorHabitacion(r->Hder, idHab);
}

//borra todas las hospitalizaciones de un paciente
int ArbolHospitalizaciones::EliminarHospDePaciente(int idPac) {
    int cantidad = 0;
    pHosp h = BuscarPorPaciente(raiz, idPac);
    while (h != nullptr) {
        int id = h->idHospitalizacion;
        EliminaNodo(id);
        cout << "Hospitalizacion " << id << " del paciente " << idPac << " eliminada" << endl;
        cantidad++;
        h = BuscarPorPaciente(raiz, idPac);
    }
    return cantidad;
}

int ArbolHospitalizaciones::EliminarHospDeHabitacion(int idHab) {
    int cantidad = 0;
    pHosp h = BuscarPorHabitacion(raiz, idHab);
    while (h != nullptr) {
        int id = h->idHospitalizacion;
        EliminaNodo(id);
        cout << "Hospitalizacion " << id << " de la habitacion " << idHab << " eliminada" << endl;
        cantidad++;
        h = BuscarPorHabitacion(raiz, idHab);
    }
    return cantidad;
}