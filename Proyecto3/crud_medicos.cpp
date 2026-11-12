//es arbol B, y el archivo es Medicos.csv
//campos: Idmedico;Nombre;Telefono;Correo;Idespecialidad
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "crud_medicos.h"
#include "crud_especialidades.h" //validar q la especialidad existe
#include "crud_citas.h"            //para la cascada borrar citas


//Constructor
ArbolMedicos::ArbolMedicos()
{
    raiz = nullptr;
}

//Destructor
ArbolMedicos::~ArbolMedicos()
{
    destruirArbol(raiz);
}

//Metodos privados

bool ArbolMedicos::BuscarNodo(pPagMed actual, int id, int& k)
{
    //busca el id dentro de UNA pagina ,devuelve true si esta, y en k queda la posicion
    //si no esta, k es la rama por la q hay q bajar (0 si es menor q todas las claves)
    if (id < actual->claves[1].idMedico) {
        k = 0;
        return false;
    }
    k = actual->cuenta;
    while (id < actual->claves[k].idMedico && k > 1) {
        k--;
    }
    return id == actual->claves[k].idMedico;
}

void ArbolMedicos::MeterHoja(pPagMed actual, NodoMedico cl, pPagMed rd, int k)
{
    //mete la clave cl (y su rama derecha rd) en la posicion k+1 de la pagina, corriendo las demas a la derecha
    //se llama solo cuando la pagina tiene espacio
    for (int i = actual->cuenta; i >= k + 1; i--) {
        actual->claves[i + 1] = actual->claves[i];
        actual->ramas[i + 1] = actual->ramas[i];
    }
    actual->claves[k + 1] = cl;
    actual->ramas[k + 1] = rd;
    actual->cuenta++;
}

void ArbolMedicos::DividirNodo(pPagMed actual, NodoMedico cl, pPagMed rd, int k, NodoMedico& mediana, pPagMed& nuevo)
{
    //la pagina esta llena (4 claves) y hay q meter una mas: se parte en 2 y la clave del medio sube
    //posMdna es la posicion de la clave q va a subir, depende de donde cae la clave nueva
    int posMdna;
    if (k <= MINMED) {
        posMdna = MINMED;
    }
    else {
        posMdna = MINMED + 1;
    }

    nuevo = new PaginaMedico();

    //lo q esta a la derecha de la mediana se pasa a la pagina nueva
    for (int i = posMdna + 1; i <= MAXMED; i++) {
        nuevo->claves[i - posMdna] = actual->claves[i];
        nuevo->ramas[i - posMdna] = actual->ramas[i];
    }
    nuevo->cuenta = MAXMED - posMdna;
    actual->cuenta = posMdna;

    //se mete la clave nueva en la pagina q le toca
    if (k <= MINMED) {
        MeterHoja(actual, cl, rd, k);
    }
    else {
        MeterHoja(nuevo, cl, rd, k - posMdna);
    }

    //la clave del final de la pagina izquierda es la mediana, esa sube
    mediana = actual->claves[actual->cuenta];
    nuevo->ramas[0] = actual->ramas[actual->cuenta];
    actual->cuenta--;
}

void ArbolMedicos::Empujar(pPagMed actual, NodoMedico cl, bool& subeArriba, NodoMedico& mediana, pPagMed& nuevo)
{
    if (actual == nullptr) {
        //se llego a un lugar vacio: la clave "sube" para q la meta el nivel de arriba
        subeArriba = true;
        mediana = cl;
        nuevo = nullptr;
    }
    else {
        int k;
        bool esta = BuscarNodo(actual, cl.idMedico, k);

        if (esta) {
            //repetido aca no deberia llegar porq antes se revisa con Buscarvalor
            subeArriba = false;
            return;
        }

        Empujar(actual->ramas[k], cl, subeArriba, mediana, nuevo);

        if (subeArriba) {
            if (actual->cuenta < MAXMED) {
                //hay espacio en la pagina, se mete y listo
                subeArriba = false;
                MeterHoja(actual, mediana, nuevo, k);
            }
            else {
                //pagina llena, se divide y sigue subiendo la mediana
                subeArriba = true;
                DividirNodo(actual, mediana, nuevo, k, mediana, nuevo);
            }
        }
    }
}

void ArbolMedicos::Insertar(NodoMedico cl)
{
    bool subeArriba;
    NodoMedico mediana;
    pPagMed nuevo;

    Empujar(raiz, cl, subeArriba, mediana, nuevo);

    if (subeArriba) {
        //se dividio hasta la raiz: se crea una raiz nueva y el arbol crece un nivel
        pPagMed p = new PaginaMedico();
        p->cuenta = 1;
        p->claves[1] = mediana;
        p->ramas[0] = raiz;
        p->ramas[1] = nuevo;
        raiz = p;
    }
}

pMedico ArbolMedicos::Buscarvalor(pPagMed r, int id)
{
    if (r == nullptr) {
        return nullptr;
    }

    int k;
    if (BuscarNodo(r, id, k)) {
        return &(r->claves[k]);
    }
    return Buscarvalor(r->ramas[k], id);
}

void ArbolMedicos::destruirArbol(pPagMed r)
{
    if (r == nullptr) return;
    for (int i = 0; i <= r->cuenta; i++) {
        destruirArbol(r->ramas[i]);
    }
    delete r;
}

//Metodos publicos

bool ArbolMedicos::InsertaNodo(int id, string nom, string tel, string cor, int idesp)
{
    if (Buscarvalor(raiz, id) != nullptr) {
        return false; //ya existe
    }
    Insertar(NodoMedico(id, nom, tel, cor, idesp));
    return true;
}

pMedico ArbolMedicos::Buscarvalor(int id)
{
    return Buscarvalor(raiz, id);
}

void ArbolMedicos::InsertarMedico(int id, string nombre, string telefono, string correo, int idesp, ArbolEspecialidad& esp)
{
    if (esp.Buscarvalor(idesp) == nullptr) { //antes q nada hay q ver q la especialidad exista USANDO METODO DE crud_especialidades
        cout << "No existe ninguna especialidad de codigo: " << idesp << endl;
    }
    else if (InsertaNodo(id, nombre, telefono, correo, idesp)) {
        cout << "Medico de nombre: " << nombre << " con id: " << id << " insertado correctamente" << endl;
    }
    else {
        cout << "No se pudo insertar el medico ya que ya existe un medico de id: " << id << endl;
    }
}

void ArbolMedicos::leerArchivo(const char* nombreArchivo, ArbolEspecialidad& esp)
{
    cout << "------------------ chunches medicos" << endl;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open() == false) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string idmedico, nombre, telefono, correo, idesp;
    string filaencabezado;

    getline(archivo, filaencabezado); //el encabezado no se borra del archivo, solo se salta al leer

    while (getline(archivo, idmedico, ';')) {
        getline(archivo, nombre, ';');
        getline(archivo, telefono, ';');
        getline(archivo, correo, ';');
        getline(archivo, idesp); //el ultimo campo de la fila no lleva delimitante
        int idint = stoi(idmedico);
        int idespint = stoi(idesp);
        InsertarMedico(idint, nombre, telefono, correo, idespint, esp);
    }
    archivo.close();
}

void ArbolMedicos::BuscarMostrar(int idesp, int id, ArbolEspecialidad& esp)
{
    if (esp.Buscarvalor(idesp) == nullptr) { //primero se valida q la especialidad exista
        cout << "No existe ninguna especialidad de codigo: " << idesp << endl;
        return;
    }

    pMedico nodoesta = Buscarvalor(id);

    if (nodoesta == nullptr) {
        cout << "No existe ningun medico de id: " << id << endl;
    }
    else if (nodoesta->idEspecialidad != idesp) { //el medico tiene q ser de ESA especialidad
        cout << "El medico de id: " << id << " existe, pero no pertenece a esa especialidad" << endl;
    }
    else {
        cout << "Medico encontrado" << endl;
        cout << "Id de medico: " << nodoesta->idMedico << endl;
        cout << "Nombre: " << nodoesta->nombre << endl;
        cout << "Telefono: " << nodoesta->telefono << endl;
        cout << "Correo: " << nodoesta->correo << endl;
        cout << "Id de especialidad: " << nodoesta->idEspecialidad << endl;
    }
}

void ArbolMedicos::ModificarMedico(int idesp, int id, string telefono, string correo, ArbolEspecialidad& esp)
{
    if (esp.Buscarvalor(idesp) == nullptr) {
        cout << "No existe ninguna especialidad de codigo: " << idesp << endl;
        return;
    }

    pMedico nodoesta = Buscarvalor(id);

    if (nodoesta == nullptr) {
        cout << "No existe ningun medico de id: " << id << endl;
    }
    else if (nodoesta->idEspecialidad != idesp) {
        cout << "El medico de id: " << id << " existe, pero no pertenece a esa especialidad" << endl;
    }
    else {
        nodoesta->telefono = telefono;
        nodoesta->correo = correo;
        cout << "Medico de id: " << id << " modificado correctamente" << endl;
    }
}

void ArbolMedicos::InordenReportesMedicos(pPagMed r, reportes& rep, int anchos[]) {
    if (r == nullptr) {
        return;
    }
    InordenReportesMedicos(r->ramas[0], rep, anchos); // no se podia hacer r->Hizq/Hder x ser diferente
    for (int i = 1; i <= r->cuenta;i++) { // < solo se jodia
        //string textos[] = { to_string(r->idMedico), r->nombre, r->telefono, r->correo, to_string(r->idEspecialidad) };
        string textos[] = { to_string(r->claves[i].idMedico), r->claves[i].nombre, r->claves[i].telefono, r->claves[i].correo,to_string(r->claves[i].idEspecialidad) };
        rep.escribirFilaDinamica(5, textos, anchos);
        InordenReportesMedicos(r->ramas[i], rep, anchos); // estas dos ultimas lineas si van dentro del for, sino no se actualiza el [i]
    }

}

void ArbolMedicos::InordenReportesMedicosPorEspecialidad(pPagMed r, reportes& rep, int anchos[], int IdEspFiltro) {
    if (r == nullptr) {
        return;
    }
    InordenReportesMedicosPorEspecialidad(r->ramas[0], rep, anchos, IdEspFiltro); // no se podia hacer r->Hizq/Hder x ser diferente
    for (int i = 1; i <= r->cuenta;i++) { // < solo se jodia
        if (r->claves[i].idEspecialidad == IdEspFiltro) {
            //string textos[] = { to_string(r->idMedico), r->nombre, r->telefono, r->correo, to_string(r->idEspecialidad) };
            string textos[] = { to_string(r->claves[i].idMedico), r->claves[i].nombre, r->claves[i].telefono, r->claves[i].correo,to_string(r->claves[i].idEspecialidad)};
            rep.escribirFilaDinamica(5, textos, anchos);
        }
        InordenReportesMedicosPorEspecialidad(r->ramas[i], rep, anchos, IdEspFiltro); // estas dos ultimas lineas si van dentro del for, sino no se actualiza el [i]
    }
}

//ELIMINAR (ARBOL B)
void ArbolMedicos::Quitar(pPagMed actual, int k)
{
    for (int j = k + 1; j <= actual->cuenta; j++) {
        actual->claves[j - 1] = actual->claves[j];
        actual->ramas[j - 1] = actual->ramas[j];
    }
    actual->cuenta--;
}

void ArbolMedicos::Sucesor(pPagMed actual, int k)
{
    pPagMed q = actual->ramas[k];
    while (q->ramas[0] != nullptr) {
        q = q->ramas[0];
    }
    actual->claves[k] = q->claves[1]; //se copian todos los datos del sucesor
}

void ArbolMedicos::MoverDerecha(pPagMed actual, int k)
{
    pPagMed problema = actual->ramas[k];
    pPagMed izquierdo = actual->ramas[k - 1];

    for (int j = problema->cuenta; j >= 1; j--) {
        problema->claves[j + 1] = problema->claves[j];
        problema->ramas[j + 1] = problema->ramas[j];
    }
    problema->cuenta++;
    problema->ramas[1] = problema->ramas[0];

    problema->claves[1] = actual->claves[k];                
    actual->claves[k] = izquierdo->claves[izquierdo->cuenta];
    problema->ramas[0] = izquierdo->ramas[izquierdo->cuenta];
    izquierdo->cuenta--;
}

void ArbolMedicos::MoverIzquierda(pPagMed actual, int k)
{
    pPagMed problema = actual->ramas[k - 1];
    pPagMed derecho = actual->ramas[k];

    problema->cuenta++;
    problema->claves[problema->cuenta] = actual->claves[k];
    problema->ramas[problema->cuenta] = derecho->ramas[0];

    actual->claves[k] = derecho->claves[1];                
    derecho->ramas[0] = derecho->ramas[1];
    derecho->cuenta--;

    for (int j = 1; j <= derecho->cuenta; j++) {        
        derecho->claves[j] = derecho->claves[j + 1];
        derecho->ramas[j] = derecho->ramas[j + 1];
    }
}

void ArbolMedicos::Combina(pPagMed actual, int k)
{
    pPagMed derecho = actual->ramas[k];
    pPagMed izquierdo = actual->ramas[k - 1];

    izquierdo->cuenta++;
    izquierdo->claves[izquierdo->cuenta] = actual->claves[k];
    izquierdo->ramas[izquierdo->cuenta] = derecho->ramas[0];

    for (int j = 1; j <= derecho->cuenta; j++) {    
        izquierdo->cuenta++;
        izquierdo->claves[izquierdo->cuenta] = derecho->claves[j];
        izquierdo->ramas[izquierdo->cuenta] = derecho->ramas[j];
    }

    for (int j = k; j <= actual->cuenta - 1; j++) {      
        actual->claves[j] = actual->claves[j + 1];
        actual->ramas[j] = actual->ramas[j + 1];
    }
    actual->cuenta--;

    delete derecho;
}

void ArbolMedicos::Restablecer(pPagMed actual, int k)
{
    if (k > 0) { 
        if (actual->ramas[k - 1]->cuenta > MINMED) {
            MoverDerecha(actual, k);
        }
        else {
            Combina(actual, k);
        }
    }
    else { 
        if (actual->ramas[1]->cuenta > MINMED) {
            MoverIzquierda(actual, 1);
        }
        else {
            Combina(actual, 1);
        }
    }
}

void ArbolMedicos::EliminarRegistro(pPagMed actual, int id, bool& encontrado)
{
    if (actual == nullptr) {
        encontrado = false; 
        return;
    }

    int k;
    encontrado = BuscarNodo(actual, id, k);
    if (encontrado) {
        if (actual->ramas[k - 1] == nullptr) { 
            Quitar(actual, k);
        }
        else { 
            Sucesor(actual, k);
            EliminarRegistro(actual->ramas[k], actual->claves[k].idMedico, encontrado);
        }
    }
    else {
        EliminarRegistro(actual->ramas[k], id, encontrado);
    }

    if (actual->ramas[k] != nullptr) {
        if (actual->ramas[k]->cuenta < MINMED) {
            Restablecer(actual, k);
        }
    }
}

bool ArbolMedicos::EliminaNodo(int id)
{
    bool encontrado;
    EliminarRegistro(raiz, id, encontrado);

    if (encontrado && raiz->cuenta == 0) {
        pPagMed vieja = raiz;
        raiz = raiz->ramas[0];
        delete vieja;
    }
    return encontrado;
}

//ELIMINAR EN CASCADA
void ArbolMedicos::EliminarMedico(int id, ArbolCitas& citas)
{
    if (Buscarvalor(id) == nullptr) {
        cout << "No se pudo eliminar el medico porque no existe un medico de id: " << id << endl;
        return;
    }

    int cantCitas = citas.EliminarCitasDeMedico(id);

    EliminaNodo(id);
    cout << "Medico de id: " << id << " eliminado correctamente (se eliminaron " << cantCitas << " citas)" << endl;
}

pMedico ArbolMedicos::BuscarPorEspecialidad(pPagMed r, int idesp)
{
    if (r == nullptr) {
        return nullptr;
    }
    for (int i = 1; i <= r->cuenta; i++) {
        if (r->claves[i].idEspecialidad == idesp) {
            return &(r->claves[i]);
        }
    }
    for (int i = 0; i <= r->cuenta; i++) {
        pMedico encontrado = BuscarPorEspecialidad(r->ramas[i], idesp);
        if (encontrado != nullptr) {
            return encontrado;
        }
    }
    return nullptr;
}

int ArbolMedicos::EliminarMedicosDeEspecialidad(int idesp, ArbolCitas& citas)
{
    int cantidad = 0;
    pMedico med = BuscarPorEspecialidad(raiz, idesp);
    while (med != nullptr) {
        int id = med->idMedico;
        EliminarMedico(id, citas);
        cantidad++;
        med = BuscarPorEspecialidad(raiz, idesp);
    }
    return cantidad;
}