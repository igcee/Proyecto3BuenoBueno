#pragma once
#include "Proyecto3/crud_paises.h" // con solo include crud_paises.h no lo encuentra (por alguna puta razon)
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
	public ref class FormMantenimiento : public System::Windows::Forms::Form
	{
	public:
		FormMantenimiento() {
			
			this->Text = L"Mantenimiento de Base de Datos";
			this->Size = System::Drawing::Size(300, 350);
			this->StartPosition = FormStartPosition::CenterParent; // sale en centro
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;// ni me acuerdo, pero salia en tutoria y me da pereza revisarlo again
			this->MaximizeBox = false;


			Button^ btnInsertar = gcnew Button();
			btnInsertar->Text = L"1. Insertar";
			btnInsertar->Location = System::Drawing::Point(50, 30);
			btnInsertar->Size = System::Drawing::Size(180, 40);

			Button^ btnBuscar = gcnew Button();
			btnBuscar->Text = L"2. Buscar";
			btnBuscar->Location = System::Drawing::Point(50, 90);
			btnBuscar->Size = System::Drawing::Size(180, 40);

			Button^ btnModificar = gcnew Button();
			btnModificar->Text = L"3. Modificar";
			btnModificar->Location = System::Drawing::Point(50, 150);
			btnModificar->Size = System::Drawing::Size(180, 40);

			Button^ btnEliminar = gcnew Button();
			btnEliminar->Text = L"4. Eliminar";
			btnEliminar->Location = System::Drawing::Point(50, 210);
			btnEliminar->Size = System::Drawing::Size(180, 40);

			// Agregar botoness
			this->Controls->Add(btnInsertar);
			this->Controls->Add(btnBuscar);
			this->Controls->Add(btnModificar);
			this->Controls->Add(btnEliminar);
		}
	};
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			arbolPaises = new ArbolPais();
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
		Button^ btnMantenimiento;
		Button^ btnReportes;
		Button^ btnAcercaDe;

		// arboles 
		ArbolPais* arbolPaises;


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



// chunches eventos

System::Void Mantenimiento_Click(System::Object^ sender, System::EventArgs^ e) {
	FormMantenimiento^ ventana = gcnew FormMantenimiento();
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