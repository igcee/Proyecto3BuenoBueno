// campos: IdTratamiento;Nombre;Descripcion;Costo
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "crud_tratamientos.h"

//constructor
ArbolTratamiento::ArbolTratamiento()
{
    raiz = nullptr;
}

//destructor
ArbolTratamiento::~ArbolTratamiento()
{
    LiberarMemoria(raiz);
}

//metodos privados

void ArbolTratamiento::InsertarRN(pTrata nuevo)
{
    //insercion normal de arbol binario de busqueda -sin balancear todavia
    // entes de llamar esto ya se reviso q el id no exista, entonces aca no hay iguales
    pTrata actual = raiz;
    pTrata papa = nullptr;

    while (actual != nullptr) {
        papa = actual;
        if (nuevo->idTratamiento < actual->idTratamiento)
            actual = actual->Hizq;
        else
            actual = actual->Hder;
    }

    nuevo->padre = papa;

    if (papa == nullptr) {
        raiz = nuevo;
    }
    else if (nuevo->idTratamiento < papa->idTratamiento) {
        papa->Hizq = nuevo;
    }
    else {
        papa->Hder = nuevo;
    }
}

void ArbolTratamiento::ArreglaInsercion(pTrata nodo)
{
    //mientras el padre sea rojo hay 2 rojos seguidos, o sea q se rompe una regla

    while (nodo != raiz and nodo->padre != nullptr and nodo->padre->color == true) {
        pTrata papa = nodo->padre;
        pTrata abuelo = papa->padre;

        if (abuelo == nullptr) break; //el padre es la raiz (y la raiz es negra, no deberia pasar)

        pTrata tio;
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

void ArbolTratamiento::RotIzquierda(pTrata nodo)
{
    pTrata hijoDer = nodo->Hder;
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

void ArbolTratamiento::RotDerecha(pTrata nodo)
{
    pTrata hijoIzq = nodo->Hizq;
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

pTrata ArbolTratamiento::Buscarvalor(pTrata r, int id)
{
    if (r == nullptr) {
        return nullptr;
    }

    if (id == r->idTratamiento) {
        return r;
    }
    else if (id < r->idTratamiento) {
        return Buscarvalor(r->Hizq, id);
    }
    else {
        return Buscarvalor(r->Hder, id);
    }
}

void ArbolTratamiento::LiberarMemoria(pTrata r)
{
    if (r == nullptr) return;
    LiberarMemoria(r->Hizq);
    LiberarMemoria(r->Hder);
    delete r;
}

// Metodos publicos

bool ArbolTratamiento::InsertaNodo(int id, string nom, string desc, double cost)
{
    if (Buscarvalor(raiz, id) != nullptr) {
        return false; //ya existe, no se crea el nodo
    }

    pTrata nuevo = new NodoTrata(id, nom, desc, cost);
    InsertarRN(nuevo);
    ArreglaInsercion(nuevo);
    return true;
}

pTrata ArbolTratamiento::Buscarvalor(int id)
{
    return Buscarvalor(raiz, id);
}

void ArbolTratamiento::InsertarTratamiento(int id, string nom, string desc, double cost)
{
    if (InsertaNodo(id, nom, desc, cost)) {
        cout << "Tratamiento de nombre: " << nom << " con codigo: " << id << " insertado correctamente" << endl;
    }
    else {
        cout << "No se pudo insertar el tratamiento ya que ya existe un tratamiento de codigo: " << id << endl;
    }
}

void ArbolTratamiento::leerArchivo(const char* nombreArchivo)
{
    cout << "------------------ chunches tratamientos" << endl;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open() == false) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string idtrata, nombre, descripcion, costo;
    string filaencabezado;

    getline(archivo, filaencabezado); //el encabezado no se borra del archivo

    while (getline(archivo, idtrata, ';')) {
        getline(archivo, nombre, ';');
        getline(archivo, descripcion, ';');
        getline(archivo, costo); //el ultimo campo de la fila no lleva delimitnte
        int idtrataint = stoi(idtrata);
        double costodouble = stod(costo);
        InsertarTratamiento(idtrataint, nombre, descripcion, costodouble);
    }
    archivo.close();
}

void ArbolTratamiento::BuscarMostrar(int id)
{
    pTrata nodoesta = Buscarvalor(id);

    if (nodoesta != nullptr) {
        cout << "Tratamiento encontrado" << endl;
        cout << "Id de tratamiento: " << nodoesta->idTratamiento << endl;
        cout << "Nombre: " << nodoesta->nombre << endl;
        cout << "Descripcion: " << nodoesta->descripcion << endl;
        cout << "Costo: " << nodoesta->costo << endl;
    }
    else {
        cout << "No existe ningun tratamiento de codigo: " << id << endl;
    }
}

void ArbolTratamiento::ModificarTratamiento(int id, string nuevoNombre, string nuevaDesc, double nuevoCosto) {
    pTrata nodoesta = Buscarvalor(id);
    if (nodoesta == nullptr) {
        cout << "No existe ningun tratamiento de codigo: " << id << endl;
    }
    else {
        nodoesta->nombre = nuevoNombre;
        nodoesta->descripcion = nuevaDesc;
        nodoesta->costo = nuevoCosto;
        cout << "Tratamiento de codigo " << id << " modificado, ahora es: " << nodoesta->nombre << " | " << nodoesta->descripcion << " | costo " << nodoesta->costo << endl;
        // le puse esas | en el cout pq sino se hacia un desmadre

    }
}

void ArbolTratamiento::InordenReportesTrata(pTrata r, reportes& rep, int anchos[]) {
    if (r == nullptr) {
        return;
    }
    InordenReportesTrata(r->Hizq, rep, anchos);
    string textos[] = { to_string(r->idTratamiento), r->nombre, r->descripcion, to_string(r->costo) };
    rep.escribirFilaDinamica(4, textos, anchos);
    InordenReportesTrata(r->Hder, rep, anchos);
}

// chunches eliminar --------------------------------------------------------------------------------------
bool ArbolTratamiento::EliminaNodo(int idtrata) {
    pTrata nodo = Buscarvalor(raiz, idtrata);
    if (nodo == nullptr) { //no esta
        return false;
    }

    EliminarTrata(nodo);
    return true;
}


void ArbolTratamiento::EliminarTrata(pTrata idtrata)
{
    pTrata y = idtrata;
    pTrata x;
    pTrata xPadre = nullptr;
    bool yOriginalColor = y->color;

    if (idtrata->Hizq == nullptr)
    {
        x = idtrata->Hder;
        xPadre = idtrata->padre;
        Sustitucion(idtrata, idtrata->Hder);
    }
    else
        if (idtrata->Hder == nullptr)
        {
            x = idtrata->Hizq;
            xPadre = idtrata->padre;
            Sustitucion(idtrata, idtrata->Hizq);
        }
        else
        {
            y = Minimo(idtrata->Hder);
            yOriginalColor = y->color;
            x = y->Hder;
            xPadre = y->padre;

            if (y->padre == idtrata)
            {
                xPadre = y;
                if (x != nullptr)
                    x->padre = y;
            }
            else
            {
                Sustitucion(y, y->Hder);
                y->Hder = idtrata->Hder;
                if (y->Hder != nullptr)
                    y->Hder->padre = y;
            }

            Sustitucion(idtrata, y);
            y->Hizq = idtrata->Hizq;
            if (y->Hizq != nullptr)
                y->Hizq->padre = y;
            y->color = idtrata->color;
        }

    delete idtrata;

    if (!yOriginalColor)
    {
        // Si x es nullptr, crea nodo temp
        if (x == nullptr)
        {
            pTrata centinela = new NodoTrata(0, "","",0.0); // esto lo acmbie de lo de la profe pq para el nodo sin nada no sirve con solo NodoHosp(0)\
                        // si o si tenia q contener "algo" para todos los valores q tiene el nodo para hosp, sino se jodia
                        // lo cambie aca para trata
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


void ArbolTratamiento::Sustitucion(pTrata idtrata1, pTrata idtrata2) {
    if (idtrata1->padre == nullptr)
    {
        raiz = idtrata2;
    }
    else
        if (idtrata1 == idtrata1->padre->Hizq)
        {
            idtrata1->padre->Hizq = idtrata2;
        }
        else
        {
            idtrata1->padre->Hder = idtrata2;
        }

    if (idtrata2 != nullptr)
    {
        idtrata2->padre = idtrata1->padre;
    }
}

pTrata ArbolTratamiento::Minimo(pTrata nodo) {
    while (nodo->Hizq != nullptr)
    {
        nodo = nodo->Hizq;
    }
    return nodo;
}


void ArbolTratamiento::ArreglaEliminacion(pTrata x)
{
    while (x != raiz and x->color == false)
    {
        if (x->padre == nullptr)
            break;

        if (x == x->padre->Hizq)
        {
            pTrata w = x->padre->Hder;

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
            pTrata w = x->padre->Hizq;

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


void ArbolTratamiento::EliminarTratamiento(int id) {
    if (EliminaNodo(id) == true) {
        cout << "Tratamiento de id: " << id << " eliminado correctamente" << endl;
    }
    else {
        cout << "No se pudo eliminar el tratamiento de id: " << id << " porque no existe" << endl;
    }
}