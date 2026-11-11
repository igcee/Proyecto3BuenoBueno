#define _HAS_STD_BYTE 0
// ^ esto es para el error de C2872
#pragma once
#include <string>
#include "Proyecto3/crud_paises.h" 
//#include "mantenimiento.h"
#include "insertar.h"
#include "buscar.h"
#include "modificar.h"
#include "iconos.h"
#include "consolabuenobueno.h"
#include "eliminar.h"

namespace CppCLRWinFormsProject {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// Summary for Form1
	/// </summary>
	

	// estos chunches deberian de ir en archivos aparte (pq sino se ocuparian como CUARENTA clases para todo, lo hago asi por mientras )
	// ^ ya los corri

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			arbolilloPais = new ArbolPais();
			arbolilloCiudad = new ArbolCiudad();
			arbolilloEsp = new ArbolEspecialidad();
			arbolilloHab = new ArbolHabitaciones();
			arbolilloHosp = new ArbolHospitalizaciones();
			arbolilloCita = new ArbolCitas();
			arbolilloTrata = new ArbolTratamiento();
			arbolilloDiag = new ArbolDiagnostico();
			arbolilloPac = new ArbolPacientes();
			arbolilloMed = new ArbolMedicos();

			// archivos

			consolabuena = gcnew Consola();
			ConstruirInterfaz(); // temp? veo dsps
			CapturaSalida cap;
			arbolilloPais->leerArchivo("Proyecto3/Paises.csv");
			arbolilloCiudad->leerArchivo("Proyecto3/Ciudades.csv", *arbolilloPais);
			arbolilloPac->leerArchivo("Proyecto3/Pacientes.csv", *arbolilloCiudad);
			arbolilloEsp->leerArchivo("Proyecto3/Especialidades.csv");
			arbolilloMed->leerArchivo("Proyecto3/Medicos.csv", *arbolilloEsp);
			arbolilloHab->leerArchivo("Proyecto3/Habitaciones.csv");
			arbolilloCita->leerArchivo("Proyecto3/Citas.csv", *arbolilloPac, *arbolilloMed);
			arbolilloHosp->leerArchivo("Proyecto3/Hospitalizaciones.csv", *arbolilloPac, *arbolilloHab, *arbolilloMed);
			arbolilloDiag->leerArchivo("Proyecto3/Diagnostico.csv");
			arbolilloTrata->leerArchivo("Proyecto3/Tratamiento.csv");
			consolabuena->Escribir(aNet(cap.Terminar()));
			//
			//TODO: Add the constructor code here
			//
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
		//Panel^ barraSuperior;
		Panel^ barraInferior;
		Label^ lblEstado;
		//Button^ btnMantenimiento;
		//Button^ btnReportes;
		//Button^ btnAcercaDe;
		//chunches de hora
		//Label^ lblHora;
		System::Windows::Forms::Timer^ reloj;
		RichTextBox^ consola;
		Consola^ consolabuena;

		//Label^ lblFecha;

		MenuStrip^ menuBarraTest;
		ToolStripLabel^ lblFechaHora;
		//RichTextBox^ consola;
		//ConsolaBuf* bufConsola;
		//std::streambuf* coutOriginal;
			
		// arboles 
		ArbolPais* arbolilloPais;
		ArbolCiudad* arbolilloCiudad;
		ArbolEspecialidad* arbolilloEsp;
		ArbolCitas* arbolilloCita;
		ArbolHabitaciones* arbolilloHab;
		ArbolHospitalizaciones* arbolilloHosp;
		ArbolMedicos* arbolilloMed;
		ArbolPacientes* arbolilloPac;
		ArbolTratamiento* arbolilloTrata;
		ArbolDiagnostico* arbolilloDiag;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// Form1
			// 
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(69)),
				static_cast<System::Int32>(static_cast<System::Byte>(153)));
			this->ClientSize = System::Drawing::Size(1262, 673);
			this->Name = L"Form1";
			this->Text = L"Sistema de Gestion Hospitalaria - Hospital San Rafael";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load_1);
			this->ResumeLayout(false);

		}
#pragma endregion

// x cualquier cosa, esto seguro lo quito dsps y lo dejo limpio
void ConstruirInterfaz() {
	ConstruirMenu();
	ConstruirReloj();
	ConstruirConsola();
	ConstruirBarraInferior();
	ConstruirIconos();
}





void ConstruirBarraInferior() {
	barraInferior = gcnew Panel();
	barraInferior->Dock = DockStyle::Bottom;
	barraInferior->Height = 30;
	barraInferior->BackColor = Color::FromArgb(221, 235, 247);

	lblEstado = gcnew Label();
	lblEstado->Dock = DockStyle::Fill;
	lblEstado->TextAlign = ContentAlignment::MiddleLeft;
	lblEstado->Padding = System::Windows::Forms::Padding(10, 0, 0, 0);
	lblEstado->ForeColor = Color::FromArgb(0, 40, 100);
	lblEstado->Text = L"Usuario: Administrador   |   Sistema de Gestion Hospitalaria";

	barraInferior->Controls->Add(lblEstado);
	this->Controls->Add(barraInferior);
}


// crea un elemento de menu de txt y evento
// lo hice asi para no tener q andar repitiendo tanto codigo para 
// cada uno de los 10 modulos pq me daba MUCHISIMA pereza escribir tanto
ToolStripMenuItem^ CrearItem(String^ texto, EventHandler^ evento) {
	ToolStripMenuItem^ item = gcnew ToolStripMenuItem(texto);
	item->Click += evento;
	return item;
}

// los botones de los 10 modulos para el menu de barra
// lo q hace menuAccion->DropDownItems->Add es agregar nuevo elemento a la lista esa q se despliega del menu de barra
// para es el menu, osea para estos seria el de mantenimiento 
// y el evento, osea el click
void AgregarEntidades(ToolStripMenuItem^ menuAccion, EventHandler^ evento) {
	menuAccion->DropDownItems->Add(CrearItem(L"Paises", evento));
	menuAccion->DropDownItems->Add(CrearItem(L"Ciudades", evento));
	menuAccion->DropDownItems->Add(CrearItem(L"Pacientes", evento));
	menuAccion->DropDownItems->Add(CrearItem(L"Medicos", evento));
	menuAccion->DropDownItems->Add(CrearItem(L"Especialidades", evento));
	menuAccion->DropDownItems->Add(CrearItem(L"Citas", evento));
	menuAccion->DropDownItems->Add(CrearItem(L"Habitaciones", evento));
	menuAccion->DropDownItems->Add(CrearItem(L"Hospitalizaciones", evento));
	menuAccion->DropDownItems->Add(CrearItem(L"Diagnosticos", evento));
	menuAccion->DropDownItems->Add(CrearItem(L"Tratamientos", evento));
}

// crea lo de los reportes en el menu
// en realidad me di cuenta de q no ocupaba hacer esto en funcion aparte
// pq igual el codigo de hacer los botones de los reportes se ocupa solo 1 vez
// no como los botones de las 10 entidades q si se repiten como 4 veces
// pero lo dejo asi pq ya para que si ya lo hice
void AgregarReportes(ToolStripMenuItem^ menuReportes) {
	EventHandler^ evento = gcnew EventHandler(this, &Form1::Reporte_Click);
	menuReportes->DropDownItems->Add(CrearItem(L"Paises", evento));
	menuReportes->DropDownItems->Add(CrearItem(L"Ciudades de un pais", evento));
	menuReportes->DropDownItems->Add(CrearItem(L"Pacientes", evento));
	menuReportes->DropDownItems->Add(CrearItem(L"Especialidades", evento));
	menuReportes->DropDownItems->Add(CrearItem(L"Habitaciones disponibles (Estado=0)", evento));
	menuReportes->DropDownItems->Add(CrearItem(L"Habitaciones ocupadas (Estado=1)", evento));
	menuReportes->DropDownItems->Add(CrearItem(L"Hospitalizaciones", evento));
	menuReportes->DropDownItems->Add(CrearItem(L"Hospitalizacion de un medico", evento));
	menuReportes->DropDownItems->Add(CrearItem(L"Medicos", evento));
	menuReportes->DropDownItems->Add(CrearItem(L"Medicos de una especialidad", evento));
	menuReportes->DropDownItems->Add(CrearItem(L"Citas por fecha", evento));
	menuReportes->DropDownItems->Add(CrearItem(L"Citas por especialidad", evento));
	menuReportes->DropDownItems->Add(CrearItem(L"Citas de un medico", evento));
	menuReportes->DropDownItems->Add(CrearItem(L"Pacientes de un pais", evento));
	menuReportes->DropDownItems->Add(CrearItem(L"Pacientes de una ciudad", evento));
	menuReportes->DropDownItems->Add(CrearItem(L"Citas de un paciente", evento));
	menuReportes->DropDownItems->Add(CrearItem(L"Diagnosticos", evento));
	menuReportes->DropDownItems->Add(CrearItem(L"Tratamientos", evento));
}

void ConstruirMenu() {
	menuBarraTest = gcnew MenuStrip();
	menuBarraTest->BackColor = Color::FromArgb(221, 235, 247);

	// mete en la pestana de mantenimiento los botones de crud
	ToolStripMenuItem^ menuMantenimiento = gcnew ToolStripMenuItem(L"Mantenimiento");

	ToolStripMenuItem^ menuInsertar = gcnew ToolStripMenuItem(L"Insertar");
	AgregarEntidades(menuInsertar, gcnew EventHandler(this, &Form1::Insertar_Click));

	ToolStripMenuItem^ menuModificar = gcnew ToolStripMenuItem(L"Modificar");
	AgregarEntidades(menuModificar, gcnew EventHandler(this, &Form1::Modificar_Click));

	ToolStripMenuItem^ menuBuscar = gcnew ToolStripMenuItem(L"Buscar");
	AgregarEntidades(menuBuscar, gcnew EventHandler(this, &Form1::Buscar_Click));

	ToolStripMenuItem^ menuEliminar = gcnew ToolStripMenuItem(L"Eliminar");
	AgregarEntidades(menuEliminar, gcnew EventHandler(this, &Form1::Eliminar_Click));

	menuMantenimiento->DropDownItems->Add(menuInsertar);
	menuMantenimiento->DropDownItems->Add(menuModificar);
	menuMantenimiento->DropDownItems->Add(menuBuscar);
	menuMantenimiento->DropDownItems->Add(menuEliminar);

	// y aca lo mismo pero con los reportes
	ToolStripMenuItem^ menuReportes = gcnew ToolStripMenuItem(L"Reportes");
	AgregarReportes(menuReportes);

	// Acerca de
	ToolStripMenuItem^ menuAcercaDe = gcnew ToolStripMenuItem(L"Acerca de");
	menuAcercaDe->Click += gcnew EventHandler(this, &Form1::AcercaDe_Click);

	menuBarraTest->Items->Add(menuMantenimiento);
	menuBarraTest->Items->Add(menuReportes);
	menuBarraTest->Items->Add(menuAcercaDe);

	this->MainMenuStrip = menuBarraTest;
	this->Controls->Add(menuBarraTest);
}

void Insertar_Click(System::Object^ sender, System::EventArgs^ e) {
	ToolStripMenuItem^ item = (ToolStripMenuItem^)sender;
	String^ entidad = item->Text; //txt del menu (osea paises/ciudad...etc)

	if (entidad == L"Paises") {
		FormInsertarPais^ ventana = gcnew FormInsertarPais(arbolilloPais);
		ventana->ShowDialog();
	}
	else if (entidad == L"Ciudades") {
		FormInsertarCiudad^ ventana = gcnew FormInsertarCiudad(arbolilloPais, arbolilloCiudad);
		ventana->ShowDialog();
	}
	else if (entidad == L"Pacientes") {
		FormInsertarPaciente^ ventana = gcnew FormInsertarPaciente(arbolilloPais, arbolilloCiudad, arbolilloPac);
		ventana->ShowDialog();
	}
	else if (entidad == L"Medicos") {
		FormInsertarMedico^ ventana = gcnew FormInsertarMedico(arbolilloEsp, arbolilloMed);
		ventana->ShowDialog();
	}
	else if (entidad == L"Especialidades") {
		FormInsertarEspecialidad^ ventana = gcnew FormInsertarEspecialidad(arbolilloEsp);
		ventana->ShowDialog();
	}
	else if (entidad == L"Citas") {
		FormInsertarCita^ ventana = gcnew FormInsertarCita(arbolilloPac, arbolilloMed, arbolilloEsp, arbolilloCita);
		ventana->ShowDialog();
	}
	else if (entidad == L"Habitaciones") {
		FormInsertarHabitacion^ ventana = gcnew FormInsertarHabitacion(arbolilloHab);
		ventana->ShowDialog();
	}
	else if (entidad == L"Hospitalizaciones") {
		FormInsertarHospitalizacion^ ventana = gcnew FormInsertarHospitalizacion(arbolilloPac, arbolilloHab, arbolilloMed, arbolilloHosp);
		ventana->ShowDialog();
	}
	else if (entidad == L"Diagnosticos") {
		FormInsertarDiagnostico^ ventana = gcnew FormInsertarDiagnostico(arbolilloDiag);
		ventana->ShowDialog();
	}
	else if (entidad == L"Tratamientos") {
		FormInsertarTratamiento^ ventana = gcnew FormInsertarTratamiento(arbolilloTrata);
		ventana->ShowDialog();
	}
	else { // no deberia de pasar, pero lo dejo por cualquier cosa a futuro
		MessageBox::Show(L"camaronDormido", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

// los de modificar, busca y eliminar los hice iguales q al de aca arriba de insertar, solo q le cambie la llamada (obviamente)
void Modificar_Click(System::Object^ sender, System::EventArgs^ e) {
	ToolStripMenuItem^ item = (ToolStripMenuItem^)sender;
	String^ entidad = item->Text;

	if (entidad == L"Paises") {
		FormModificarPais^ ventana = gcnew FormModificarPais(arbolilloPais);
		ventana->ShowDialog();
	}
	else if (entidad == L"Ciudades") {
		FormModificarCiudad^ ventana = gcnew FormModificarCiudad(arbolilloPais, arbolilloCiudad);
		ventana->ShowDialog();
	}
	else if (entidad == L"Pacientes") {
		FormModificarPaciente^ ventana = gcnew FormModificarPaciente(arbolilloCiudad, arbolilloPac);
		ventana->ShowDialog();
	}
	else if (entidad == L"Medicos") {
		FormModificarMedico^ ventana = gcnew FormModificarMedico(arbolilloEsp, arbolilloMed);
		ventana->ShowDialog();
	}
	else if (entidad == L"Especialidades") {
		FormModificarEspecialidad^ ventana = gcnew FormModificarEspecialidad(arbolilloEsp);
		ventana->ShowDialog();
	}
	else if (entidad == L"Citas") {
		FormModificarCita^ ventana = gcnew FormModificarCita(arbolilloPac, arbolilloMed, arbolilloCita);
		ventana->ShowDialog();
	}
	else if (entidad == L"Habitaciones") {
		FormModificarHabitacion^ ventana = gcnew FormModificarHabitacion(arbolilloHab);
		ventana->ShowDialog();
	}
	else if (entidad == L"Hospitalizaciones") {
		FormModificarHospitalizacion^ ventana = gcnew FormModificarHospitalizacion(arbolilloPac, arbolilloHab, arbolilloHosp);
		ventana->ShowDialog();
	}
	else if (entidad == L"Diagnosticos") {
		FormModificarDiagnostico^ ventana = gcnew FormModificarDiagnostico(arbolilloDiag);
		ventana->ShowDialog();
	}
	else if (entidad == L"Tratamientos") {
		FormModificarTratamiento^ ventana = gcnew FormModificarTratamiento(arbolilloTrata);
		ventana->ShowDialog();
	}
	else {
		MessageBox::Show(L"madrugadorAlQueDiosNoAyudo", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

void Buscar_Click(System::Object^ sender, System::EventArgs^ e) {
	ToolStripMenuItem^ item = (ToolStripMenuItem^)sender;
	String^ entidad = item->Text;

	if (entidad == L"Paises") {
		FormBuscarPais^ ventana = gcnew FormBuscarPais(arbolilloPais);
		ventana->ShowDialog();
	}
	else if (entidad == L"Ciudades") {
		FormBuscarCiudad^ ventana = gcnew FormBuscarCiudad(arbolilloPais, arbolilloCiudad);
		ventana->ShowDialog();
	}
	else if (entidad == L"Pacientes") {
		FormBuscarPaciente^ ventana = gcnew FormBuscarPaciente(arbolilloPais, arbolilloCiudad, arbolilloPac);
		ventana->ShowDialog();
	}
	else if (entidad == L"Medicos") {
		FormBuscarMedico^ ventana = gcnew FormBuscarMedico(arbolilloEsp, arbolilloMed);
		ventana->ShowDialog();
	}
	else if (entidad == L"Especialidades") {
		FormBuscarEspecialidad^ ventana = gcnew FormBuscarEspecialidad(arbolilloEsp);
		ventana->ShowDialog();
	}
	else if (entidad == L"Citas") {
		FormBuscarCita^ ventana = gcnew FormBuscarCita(arbolilloPac, arbolilloMed, arbolilloEsp, arbolilloCita);
		ventana->ShowDialog();
	}
	else if (entidad == L"Habitaciones") {
		FormBuscarHabitacion^ ventana = gcnew FormBuscarHabitacion(arbolilloHab);
		ventana->ShowDialog();
	}
	else if (entidad == L"Hospitalizaciones") {
		FormBuscarHospitalizacion^ ventana = gcnew FormBuscarHospitalizacion(arbolilloPac, arbolilloHab, arbolilloMed, arbolilloHosp);
		ventana->ShowDialog();
	}
	else if (entidad == L"Diagnosticos") {
		FormBuscarDiagnostico^ ventana = gcnew FormBuscarDiagnostico(arbolilloDiag);
		ventana->ShowDialog();
	}
	else if (entidad == L"Tratamientos") {
		FormBuscarTratamiento^ ventana = gcnew FormBuscarTratamiento(arbolilloTrata);
		ventana->ShowDialog();
	}
	else {
		MessageBox::Show(L"kashdashjda", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

void Eliminar_Click(System::Object^ sender, System::EventArgs^ e) {
	ToolStripMenuItem^ item = (ToolStripMenuItem^)sender;
	String^ entidad = item->Text;

	if (entidad == L"Paises") {
		FormEliminarPais^ ventana = gcnew FormEliminarPais(arbolilloPais, consolabuena);
		ventana->ShowDialog();
	}
	else if (entidad == L"Ciudades") {
		FormEliminarCiudad^ ventana = gcnew FormEliminarCiudad(arbolilloPais, arbolilloCiudad, consolabuena);
		ventana->ShowDialog();
	}
	/*
	else if (entidad == L"Pacientes") {
		FormEliminarPaciente^ ventana = gcnew FormEliminarPaciente(arbolilloPais, arbolilloCiudad, arbolilloPac);
		ventana->ShowDialog();
	}
	else if (entidad == L"Medicos") {
		FormEliminarMedico^ ventana = gcnew FormEliminarMedico(arbolilloEsp, arbolilloMed);
		ventana->ShowDialog();
	}
	*/
	else if (entidad == L"Especialidades") {
		FormEliminarEspecialidad^ ventana = gcnew FormEliminarEspecialidad(arbolilloEsp, consolabuena);
		ventana->ShowDialog();
	}
	/*
	else if (entidad == L"Citas") {
		FormEliminarCita^ ventana = gcnew FormEliminarCita(arbolilloPac, arbolilloMed, arbolilloEsp, arbolilloCita);
		ventana->ShowDialog();
	}
	else if (entidad == L"Habitaciones") {
		FormEliminarHabitacion^ ventana = gcnew FormEliminarHabitacion(arbolilloHab);
		ventana->ShowDialog();
	}
	else if (entidad == L"Hospitalizaciones") {
		FormEliminarHospitalizacion^ ventana = gcnew FormEliminarHospitalizacion(arbolilloPac, arbolilloHab, arbolilloMed, arbolilloHosp);
		ventana->ShowDialog();
	}
	else if (entidad == L"Diagnosticos") {
		FormEliminarDiagnostico^ ventana = gcnew FormEliminarDiagnostico(arbolilloDiag);
		ventana->ShowDialog();
	}
	else if (entidad == L"Tratamientos") {
		FormEliminarTratamiento^ ventana = gcnew FormEliminarTratamiento(arbolilloTrata);
		ventana->ShowDialog();
	}
	*/
	else {
		MessageBox::Show(L"kashdasasdashjda", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}



void ConstruirReloj() {
	// fecha y hora a la derecha del menu
	lblFechaHora = gcnew ToolStripLabel();
	lblFechaHora->Alignment = ToolStripItemAlignment::Right;
	lblFechaHora->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0f, FontStyle::Bold);
	lblFechaHora->ForeColor = Color::FromArgb(0, 40, 100);
	menuBarraTest->Items->Add(lblFechaHora);

	// actualiza cada 1000 ms
	reloj = gcnew System::Windows::Forms::Timer();
	reloj->Interval = 1000;
	reloj->Tick += gcnew EventHandler(this, &Form1::Reloj_Tick);

	DateTime ahora = DateTime::Now;
	lblFechaHora->Text = ahora.ToString(L"dd'/'MM'/'yyyy") + L"     " + ahora.ToString(L"hh:mm:ss tt");
	reloj->Start();
}


void Reloj_Tick(System::Object^ sender, System::EventArgs^ e) {
	DateTime ahora = DateTime::Now;
}


void ConstruirIconos() {
	Color fondo = Color::FromArgb(200, 200, 200); //temporal, luego lo cambio para meterle una imagen


	// lo de las posiciones tambien es temporal, luego veo como acomodarlos bien bonito

	// fila 1
	this->Controls->Add(gcnew BotonIcono(L"Paises", 20, 70, fondo));
	this->Controls->Add(gcnew BotonIcono(L"Ciudades", 180, 70, fondo));
	this->Controls->Add(gcnew BotonIcono(L"Pacientes", 340, 70, fondo));
	this->Controls->Add(gcnew BotonIcono(L"Medicos", 500, 70, fondo));
	this->Controls->Add(gcnew BotonIcono(L"Especialidades", 660, 70, fondo));

	// fila 2 
	this->Controls->Add(gcnew BotonIcono(L"Citas", 20, 200, fondo));
	this->Controls->Add(gcnew BotonIcono(L"Habitaciones", 180, 200, fondo));
	this->Controls->Add(gcnew BotonIcono(L"Hospitalizaciones", 340, 200, fondo));
	this->Controls->Add(gcnew BotonIcono(L"Diagnosticos", 500, 200, fondo));
	this->Controls->Add(gcnew BotonIcono(L"Tratamientos", 660, 200, fondo));

	//a cada icono le pone el evento de clic (la cosa recorre los controles de la ventana y agarra solo los BotonIcono)
	for each(Control ^ c in this->Controls) {
		BotonIcono^ icono = dynamic_cast<BotonIcono^>(c);
		if (icono != nullptr) {
			icono->Click += gcnew EventHandler(this, &Form1::Icono_Click);
		}
	}
}

//al darle clic a un icono sale un menuito con las 4 acciones de esa entidad
void Icono_Click(System::Object^ sender, System::EventArgs^ e) {
	Button^ icono = (Button^)sender;
	String^ entidad = icono->Text; //"Pacientes", "Medicos", etc

	System::Windows::Forms::ContextMenuStrip^ menuIcono = gcnew System::Windows::Forms::ContextMenuStrip();
	EventHandler^ evento = gcnew EventHandler(this, &Form1::AccionIcono_Click);
	//CrearItem es el mismo q usa el menu de arriba.en el Tag se guarda de q entidad es
	ToolStripMenuItem^ opInsertar = CrearItem(L"Insertar", evento);
	opInsertar->Tag = entidad;
	ToolStripMenuItem^ opBuscar = CrearItem(L"Buscar", evento);
	opBuscar->Tag = entidad;
	ToolStripMenuItem^ opModificar = CrearItem(L"Modificar", evento);
	opModificar->Tag = entidad;
	ToolStripMenuItem^ opEliminar = CrearItem(L"Eliminar", evento);
	opEliminar->Tag = entidad;

	menuIcono->Items->Add(opInsertar);
	menuIcono->Items->Add(opBuscar);
	menuIcono->Items->Add(opModificar);
	menuIcono->Items->Add(opEliminar);

	menuIcono->Show(icono, System::Drawing::Point(0, icono->Height)); // sale justo debajo del icono
}

//reutiliza los mismos eventos del menu de arriba. Esos eventos leen el Text del item para saber
//la entidad, entonces se crea un item con el nombre de la entidad y se les pasa
void AccionIcono_Click(System::Object^ sender, System::EventArgs^ e) {
	ToolStripMenuItem^ opcion = (ToolStripMenuItem^)sender;
	ToolStripMenuItem^ itemEntidad = gcnew ToolStripMenuItem((String^)opcion->Tag);

	if (opcion->Text == L"Insertar") {
		Insertar_Click(itemEntidad, e);
	}
	else if (opcion->Text == L"Buscar") {
		Buscar_Click(itemEntidad, e);
	}
	else if (opcion->Text == L"Modificar") {
		Modificar_Click(itemEntidad, e);
	}
	else if (opcion->Text == L"Eliminar") {
		Eliminar_Click(itemEntidad, e);
	}
}




// estas cosas son temporales de la consola, q me gustaria pulir mejor


void ConstruirConsola() {
	consola =consolabuena->Crear();
	this->Controls->Add(consola);

	// para q  al abrirse la ventana, la consola baje hasta lo ultimo escrito
	this->Shown += gcnew EventHandler(this, &Form1::Form1_Shown);
}

void Form1_Shown(System::Object^ sender, System::EventArgs^ e) {
	consolabuena->IrAlFinal();
}


// chunches eventos
/*
System::Void Mantenimiento_Click(System::Object^ sender, System::EventArgs^ e) {
	FormMantenimiento^ ventana = gcnew FormMantenimiento(arbolilloPais, arbolilloCiudad, arbolilloHab, arbolilloHosp, arbolilloPac, arbolilloMed, arbolilloTrata, arbolilloDiag, arbolilloEsp, arbolilloCita);
	ventana->ShowDialog(); // espera q cierre
}

System::Void Reportes_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show(L"Reportes: no hay aun :P", L"Informacion", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
*/

void AcercaDe_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show(L"Las consecuencias de la inclusion de la salsa lizano a los tamales", L"Acerca de", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

void Reporte_Click(System::Object^ sender, System::EventArgs^ e) {
	ToolStripMenuItem^ item = (ToolStripMenuItem^)(sender);
	MessageBox::Show(L"Generando reporte de: " + item->Text, L"Reportes", MessageBoxButtons::OK, MessageBoxIcon::Information);
}



// esto viene de default con el winforms, y se lo toco se jode todo.
// aka mejor dejarlo ahi tranquilo
	private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Form1_Load_1(System::Object^ sender, System::EventArgs^ e) {
	}
};
}