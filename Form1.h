#define _HAS_STD_BYTE 0
// ^ esto es para el error de C2872
#pragma once
#include <string>
#include "Proyecto3/crud_paises.h" 
#include "mantenimiento.h"

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
			ConstruirInterfaz(); // temp? veo dsps
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
		Panel^ barraSuperior;
		Panel^ barraInferior;
		Label^ lblEstado;
		Button^ btnMantenimiento;
		Button^ btnReportes;
		Button^ btnAcercaDe;
		//chunches de hora
		Label^ lblHora;
		System::Windows::Forms::Timer^ reloj;
		Label^ lblFecha;
			
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
			// 
			// Form1
			// 
			this->Size = System::Drawing::Size(1280, 720);// resu en X / Y
			this->Text = L"Sistema de Gestion Hospitalaria - Hospital San Rafael"; // este si nombre de ventana
			this->BackColor = System::Drawing::Color::FromArgb(0, 69, 153); // color fondo



		}
#pragma endregion

// x cualquier cosa, esto seguro lo quito dsps y lo dejo limpio
void ConstruirInterfaz() {
	ConstruirBarraSuperior();
	ConstruirReloj();
	ConstruirBarraInferior();
}

Button^ CrearBotonBarra(String^ texto, int x) {
	// esto crea un boton, con un texto y posicion x
	// no se ocupa posicion y, ya que como es solo para los de la barra (lo q era antes menu strip), todos van en la misma cord y
	Button^ b = gcnew Button();
	b->Text = texto;
	b->Size = System::Drawing::Size(140, 32);
	b->Location = System::Drawing::Point(x, 6);
	b->FlatStyle = FlatStyle::Flat;
	b->BackColor = Color::White;
	return b;
	}

void ConstruirBarraSuperior() {
	// panel pegado de arriba q hace de "barra de menu"
	barraSuperior = gcnew Panel();
	barraSuperior->Dock = DockStyle::Top; // DockStyle top pega el panel a la parte de arriba, y se estira automaticamente dependiendo del ancho
	barraSuperior->Height = 44;
	barraSuperior->BackColor = Color::FromArgb(221, 235, 247);


	// aca se hacen dentro de este panel 3 botones, con nombre y cord X, ademas les mete el chunche de eventhandler para q sirvan
	btnMantenimiento = CrearBotonBarra(L"Mantenimiento", 10);
	btnMantenimiento->Click += gcnew EventHandler(this, &Form1::Mantenimiento_Click);

	btnReportes = CrearBotonBarra(L"Reportes", 160);
	btnReportes->Click += gcnew EventHandler(this, &Form1::Reportes_Click);

	btnAcercaDe = CrearBotonBarra(L"Acerca de", 310);
	btnAcercaDe->Click += gcnew EventHandler(this, &Form1::AcercaDe_Click);

	barraSuperior->Controls->Add(btnMantenimiento);
	barraSuperior->Controls->Add(btnReportes);
	barraSuperior->Controls->Add(btnAcercaDe);

	this->Controls->Add(barraSuperior);
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
void ConstruirReloj() {
	// esto es para hacer el relog
	lblHora = gcnew Label();
	lblHora->Dock = DockStyle::Right;
	lblHora->Width = 160;
	lblHora->TextAlign = ContentAlignment::MiddleCenter;
	lblHora->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0f, FontStyle::Bold);
	lblHora->ForeColor = Color::FromArgb(0, 40, 100);
	barraSuperior->Controls->Add(lblHora);

	// y este de hora
	lblFecha = gcnew Label();
	lblFecha->Dock = DockStyle::Right;
	lblFecha->Width = 120;
	lblFecha->TextAlign = ContentAlignment::MiddleCenter;
	lblFecha->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0f, FontStyle::Bold);
	lblFecha->ForeColor = Color::FromArgb(0, 40, 100);
	barraSuperior->Controls->Add(lblFecha);
	lblFecha->BringToFront(); // esto hace q fecha quede a izq de hora

	// actualiza cada 1000 ms
	reloj = gcnew System::Windows::Forms::Timer();
	reloj->Interval = 1000;
	reloj->Tick += gcnew EventHandler(this, &Form1::Reloj_Tick);

	ActualizarHora();
	reloj->Start();
}

void ActualizarHora() {
	lblHora->Text = DateTime::Now.ToString(L"hh:mm:ss tt");
	lblFecha->Text = DateTime::Now.ToString(L"dd'/'MM'/'yyyy");
}

System::Void Reloj_Tick(System::Object^ sender, System::EventArgs^ e) {
	ActualizarHora();
}

// chunches eventos

System::Void Mantenimiento_Click(System::Object^ sender, System::EventArgs^ e) {
	FormMantenimiento^ ventana = gcnew FormMantenimiento(arbolilloPais, arbolilloCiudad, arbolilloHab, arbolilloHosp, arbolilloPac, arbolilloMed, arbolilloTrata, arbolilloDiag, arbolilloEsp, arbolilloCita);
	ventana->ShowDialog(); // espera q cierre
}

System::Void Reportes_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show(L"Reportes: no hay aun :P", L"Informacion", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

System::Void AcercaDe_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show(L"Las consecuencias de la inclusion de la salsa lizano a los tamales", L"Acerca de", MessageBoxButtons::OK, MessageBoxIcon::Information);
}





// esto viene de default con el winforms, y se lo toco se jode todo.
// aka mejor dejarlo ahi tranquilo
	private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}