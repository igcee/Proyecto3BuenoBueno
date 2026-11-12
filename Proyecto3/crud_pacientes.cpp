//archivo de pacientes.
//es arbol B, y el archivo es Pacientes.csv
//campos: Idpaciente;Nombre;Fechanacimiento;Telefono;CodPais;CodCiudad;Correo
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "crud_pacientes.h"
#include "crud_ciudades.h" //validar q la ciudad existe
#include "reportes.h"
#include "crud_citas.h"            //para la cascada borrar citas
#include "crud_hospitalizaciones.h" //para la cascada borrar hospitalizaciones

//Constructor
ArbolPacientes::ArbolPacientes()
{
    raiz = nullptr;
}

//Destructor
ArbolPacientes::~ArbolPacientes()
{
    destruirArbol(raiz);
}

//Metodos privados

bool ArbolPacientes::BuscarNodo(pPagPac actual, int id, int& k)
{
    //busca el id dentro de UNA pagina. devuelve true si esta, y en k queda la posicion
    //si no esta, k es la rama por la q hay q bajar (0 si es menor q todas las claves)
    if (id < actual->claves[1].idPaciente) {
        k = 0;
        return false;
    }
    k = actual->cuenta;
    while (id < actual->claves[k].idPaciente && k > 1) {
        k--;
    }
    return id == actual->claves[k].idPaciente;
}

void ArbolPacientes::MeterHoja(pPagPac actual, NodoPaciente cl, pPagPac rd, int k)
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

void ArbolPacientes::DividirNodo(pPagPac actual, NodoPaciente cl, pPagPac rd, int k, NodoPaciente& mediana, pPagPac& nuevo)
{
    //la pagina esta llena (4 claves) y hay q meter una mas: se parte en 2 y la clave del medio sube
    //posMdna es la posicion de la clave q va a subir, depende de donde cae la clave nueva
    int posMdna;
    if (k <= MINPAC) {
        posMdna = MINPAC;
    }
    else {
        posMdna = MINPAC + 1;
    }

    nuevo = new PaginaPaciente();

    //lo q esta a la derecha de la mediana se pasa a la pagina nueva
    for (int i = posMdna + 1; i <= MAXPAC; i++) {
        nuevo->claves[i - posMdna] = actual->claves[i];
        nuevo->ramas[i - posMdna] = actual->ramas[i];
    }
    nuevo->cuenta = MAXPAC - posMdna;
    actual->cuenta = posMdna;

    //se mete la clave nueva en la pagina q le toca
    if (k <= MINPAC) {
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

void ArbolPacientes::Empujar(pPagPac actual, NodoPaciente cl, bool& subeArriba, NodoPaciente& mediana, pPagPac& nuevo)
{
    if (actual == nullptr) {
        //se llego a un lugar vacio: la clave "sube" para q la meta el nivel de arriba
        subeArriba = true;
        mediana = cl;
        nuevo = nullptr;
    }
    else {
        int k;
        bool esta = BuscarNodo(actual, cl.idPaciente, k);

        if (esta) {
            //repetido aca no deberia llegar porq antes se revisa con Buscarvalor
            subeArriba = false;
            return;
        }

        Empujar(actual->ramas[k], cl, subeArriba, mediana, nuevo);

        if (subeArriba) {
            if (actual->cuenta < MAXPAC) {
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

void ArbolPacientes::Insertar(NodoPaciente cl)
{
    bool subeArriba;
    NodoPaciente mediana;
    pPagPac nuevo;

    Empujar(raiz, cl, subeArriba, mediana, nuevo);

    if (subeArriba) {
        //se dividio hasta la raiz: se crea una raiz nueva y el arbol crece un nivel
        pPagPac p = new PaginaPaciente();
        p->cuenta = 1;
        p->claves[1] = mediana;
        p->ramas[0] = raiz;
        p->ramas[1] = nuevo;
        raiz = p;
    }
}

pPaciente ArbolPacientes::Buscarvalor(pPagPac r, int id)
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

void ArbolPacientes::destruirArbol(pPagPac r)
{
    if (r == nullptr) return;
    for (int i = 0; i <= r->cuenta; i++) {
        destruirArbol(r->ramas[i]);
    }
    delete r;
}

//Metodos publicos

bool ArbolPacientes::InsertaNodo(int id, string nom, string fecha, string tel, int codp, int codc, string cor)
{
    if (Buscarvalor(raiz, id) != nullptr) {
        return false; // ya existe
    }
    Insertar(NodoPaciente(id, nom, fecha, tel, codp, codc, cor));
    return true;
}

pPaciente ArbolPacientes::Buscarvalor(int id)
{
    return Buscarvalor(raiz, id);
}

void ArbolPacientes::InsertarPaciente(int id, string nombre, string fecha, string telefono, string correo, int codpais, int codciudad, ArbolCiudad& ciudades)
{
    if (ciudades.Buscarvalor(codpais, codciudad) == nullptr) { //antes q nada hay q ver q la ciudad exista USANDO METODO DE crud_ciudades
        cout << "No existe ninguna ciudad de codigo: " << codciudad << " en el pais de codigo: " << codpais << endl;
    }
    else if (InsertaNodo(id, nombre, fecha, telefono, codpais, codciudad, correo)) {
        cout << "Paciente de nombre: " << nombre << " con id: " << id << " insertado correctamente" << endl;
    }
    else {
        cout << "No se pudo insertar el paciente ya que ya existe un paciente de id: " << id << endl;
    }
}

void ArbolPacientes::leerArchivo(const char* nombreArchivo, ArbolCiudad& ciudades)
{
    cout << "------------------ chunches pacientes" << endl;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open() == false) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string idpaciente, nombre, fecha, telefono, codpais, codciudad, correo;
    string filaencabezado;

    getline(archivo, filaencabezado); //el encabezado no se borra del archivo, solo se salta al leer

    while (getline(archivo, idpaciente, ';')) {
        getline(archivo, nombre, ';');
        getline(archivo, fecha, ';');
        getline(archivo, telefono, ';');
        getline(archivo, codpais, ';');
        getline(archivo, codciudad, ';');
        getline(archivo, correo); //el ultimo campo de la fila no lleva delimitante
        int idint = stoi(idpaciente);
        int codpaisint = stoi(codpais);
        int codciudadint = stoi(codciudad);
        //en el archivo el correo va al final, pero InsertarPaciente lo recibe antes del pais y la ciudad
        InsertarPaciente(idint, nombre, fecha, telefono, correo, codpaisint, codciudadint, ciudades);
    }
    archivo.close();
}

void ArbolPacientes::BuscarMostrar(int codpais, int codciudad, int id, ArbolCiudad& ciudades)
{
    if (ciudades.Buscarvalor(codpais, codciudad) == nullptr) { //primero se valida q la ciudad exista
        cout << "No existe ninguna ciudad de codigo: " << codciudad << " en el pais de codigo: " << codpais << endl;
        return;
    }

    pPaciente nodoesta = Buscarvalor(id);

    if (nodoesta == nullptr) {
        cout << "No existe ningun paciente de id: " << id << endl;
    }
    else if (nodoesta->codPais != codpais || nodoesta->codCiudad != codciudad) { //el paciente tiene q ser de ESA ciudad
        cout << "El paciente de id: " << id << " existe, pero no pertenece a esa ciudad" << endl;
    }
    else {
        cout << "Paciente encontrado" << endl;
        cout << "Id de paciente: " << nodoesta->idPaciente << endl;
        cout << "Nombre: " << nodoesta->nombre << endl;
        cout << "Fecha de nacimiento: " << nodoesta->fechaNacimiento << endl;
        cout << "Telefono: " << nodoesta->telefono << endl;
        cout << "Codigo de pais: " << nodoesta->codPais << endl;
        cout << "Codigo de ciudad: " << nodoesta->codCiudad << endl;
        cout << "Correo: " << nodoesta->correo << endl;
    }
}

void ArbolPacientes::ModificarPaciente(int codpais, int codciudad, int id, string telefono, string correo, ArbolCiudad& ciudades)
{
    if (ciudades.Buscarvalor(codpais, codciudad) == nullptr) {
        cout << "No existe ninguna ciudad de codigo: " << codciudad << " en el pais de codigo: " << codpais << endl;
        return;
    }

    pPaciente nodoesta = Buscarvalor(id);

    if (nodoesta == nullptr) {
        cout << "No existe ningun paciente de id: " << id << endl;
    }
    else if (nodoesta->codPais != codpais || nodoesta->codCiudad != codciudad) {
        cout << "El paciente de id: " << id << " existe, pero no pertenece a esa ciudad" << endl;
    }
    else {
        nodoesta->telefono = telefono;
        nodoesta->correo = correo;
        cout << "Paciente de id: " << id << " modificado correctamente" << endl;
    }
}

void ArbolPacientes::InordenReportesPacientes(pPagPac r, reportes& rep, int anchos[]) {
    if (r == nullptr) {
        return;
    }
    InordenReportesPacientes(r->ramas[0], rep, anchos);
    for (int i = 1; i <= r->cuenta;i++) {
        string textos[] = { to_string(r->claves[i].idPaciente), r->claves[i].nombre, r->claves[i].fechaNacimiento,  r->claves[i].telefono, to_string(r->claves[i].codPais), to_string(r->claves[i].codCiudad),r->claves[i].correo};
        rep.escribirFilaDinamica(7, textos, anchos);
        InordenReportesPacientes(r->ramas[i], rep, anchos);
    }
}

void ArbolPacientes::InordenReportesPacientesPorPais(pPagPac r, reportes& rep, int anchos[], int codPaisFiltro) {
    if (r == nullptr) {
        return;
    }
    InordenReportesPacientesPorPais(r->ramas[0], rep, anchos, codPaisFiltro);
    for (int i = 1; i <= r->cuenta;i++) {
        if (r->claves[i].codPais == codPaisFiltro) {
            string textos[] = { to_string(r->claves[i].idPaciente), r->claves[i].nombre, r->claves[i].fechaNacimiento,  r->claves[i].telefono, to_string(r->claves[i].codPais), to_string(r->claves[i].codCiudad),r->claves[i].correo };
            rep.escribirFilaDinamica(7, textos, anchos);
        }
        InordenReportesPacientesPorPais(r->ramas[i], rep, anchos, codPaisFiltro);
    }
}

void ArbolPacientes::InordenReportesPacientesPorCiudad(pPagPac r, reportes& rep, int anchos[], int codPaisFiltro,int codCiudadFiltro) {
    if (r == nullptr) {
        return;
    }
    InordenReportesPacientesPorCiudad(r->ramas[0], rep, anchos, codPaisFiltro,codCiudadFiltro);
    for (int i = 1; i <= r->cuenta;i++) {
        if (r->claves[i].codCiudad == codCiudadFiltro and r->claves[i].codPais == codPaisFiltro) {
            string textos[] = { to_string(r->claves[i].idPaciente), r->claves[i].nombre, r->claves[i].fechaNacimiento,  r->claves[i].telefono, to_string(r->claves[i].codPais), to_string(r->claves[i].codCiudad),r->claves[i].correo };
            rep.escribirFilaDinamica(7, textos, anchos);
        }
        InordenReportesPacientesPorCiudad(r->ramas[i], rep, anchos, codPaisFiltro,codCiudadFiltro);
    }
}

//ELIMINAR (ARBOL B)
void ArbolPacientes::Quitar(pPagPac actual, int k)
{
    for (int j = k + 1; j <= actual->cuenta; j++) {
        actual->claves[j - 1] = actual->claves[j];
        actual->ramas[j - 1] = actual->ramas[j];
    }
    actual->cuenta--;
}

void ArbolPacientes::Sucesor(pPagPac actual, int k)
{
    pPagPac q = actual->ramas[k];
    while (q->ramas[0] != nullptr) {
        q = q->ramas[0];
    }
    actual->claves[k] = q->claves[1]; 
}

void ArbolPacientes::MoverDerecha(pPagPac actual, int k)
{
    pPagPac problema = actual->ramas[k];
    pPagPac izquierdo = actual->ramas[k - 1];

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

void ArbolPacientes::MoverIzquierda(pPagPac actual, int k)
{
    pPagPac problema = actual->ramas[k - 1];
    pPagPac derecho = actual->ramas[k];

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

void ArbolPacientes::Combina(pPagPac actual, int k)
{
    pPagPac derecho = actual->ramas[k];
    pPagPac izquierdo = actual->ramas[k - 1];

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

void ArbolPacientes::Restablecer(pPagPac actual, int k)
{
    if (k > 0) { 
        if (actual->ramas[k - 1]->cuenta > MINPAC) {
            MoverDerecha(actual, k);
        }
        else {
            Combina(actual, k);
        }
    }
    else { 
        if (actual->ramas[1]->cuenta > MINPAC) {
            MoverIzquierda(actual, 1);
        }
        else {
            Combina(actual, 1);
        }
    }
}

void ArbolPacientes::EliminarRegistro(pPagPac actual, int id, bool& encontrado)
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
            EliminarRegistro(actual->ramas[k], actual->claves[k].idPaciente, encontrado);
        }
    }
    else {
        EliminarRegistro(actual->ramas[k], id, encontrado);
    }

    if (actual->ramas[k] != nullptr) {
        if (actual->ramas[k]->cuenta < MINPAC) {
            Restablecer(actual, k);
        }
    }
}

bool ArbolPacientes::EliminaNodo(int id)
{
    bool encontrado;
    EliminarRegistro(raiz, id, encontrado);

    if (encontrado && raiz->cuenta == 0) {
        pPagPac vieja = raiz;
        raiz = raiz->ramas[0];
        delete vieja;
    }
    return encontrado;
}

//ELIMINAR EN CASCADA

void ArbolPacientes::EliminarPaciente(int id, ArbolCitas& citas, ArbolHospitalizaciones& hosp)
{
    if (Buscarvalor(id) == nullptr) {
        cout << "No se pudo eliminar el paciente porque no existe un paciente de id: " << id << endl;
        return;
    }

    int cantCitas = citas.EliminarCitasDePaciente(id);
    int cantHosp = hosp.EliminarHospDePaciente(id);

    EliminaNodo(id);
    cout << "Paciente de id: " << id << " eliminado correctamente (se eliminaron " << cantCitas << " citas y " << cantHosp << " hospitalizaciones)" << endl;
}

pPaciente ArbolPacientes::BuscarPorCiudad(pPagPac r, int codp, int codc)
{
    if (r == nullptr) {
        return nullptr;
    }
    for (int i = 1; i <= r->cuenta; i++) {
        if (r->claves[i].codPais == codp && r->claves[i].codCiudad == codc) {
            return &(r->claves[i]);
        }
    }
    for (int i = 0; i <= r->cuenta; i++) {
        pPaciente encontrado = BuscarPorCiudad(r->ramas[i], codp, codc);
        if (encontrado != nullptr) {
            return encontrado;
        }
    }
    return nullptr;
}

int ArbolPacientes::EliminarPacientesDeCiudad(int codp, int codc, ArbolCitas& citas, ArbolHospitalizaciones& hosp)
{
    int cantidad = 0;
    pPaciente pac = BuscarPorCiudad(raiz, codp, codc);
    while (pac != nullptr) {
        int id = pac->idPaciente; 
        EliminarPaciente(id, citas, hosp);
        cantidad++;
        pac = BuscarPorCiudad(raiz, codp, codc);
    }
    return cantidad;
}