#pragma once
#include <string>
#include <msclr/marshal_cppstd.h> // esto se ocupa para convertir texto de lo q sea q lo deja el winforms a string normalito
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
	

	// estos chunches deberian de ir en archivos aparte (pq sino se ocuparian como CUARENTA clases para todo, lo hago asi por mientras )
	public ref class FormInsertarPais : public System::Windows::Forms::Form {
	private:
		TextBox^ txtCodPais;
		TextBox^ txtNombre; // guardar input de la ventana
		ArbolPais* arbolPaises;

	public:
		FormInsertarPais(ArbolPais* arbol) {
			arbolPaises = arbol;

			this->Text = L"Insertar País";
			this->Size = System::Drawing::Size(300, 250);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// cosas y cajita para input de codpais
			Label^ lblCod = gcnew Label(); 
			lblCod->Text = L"Código: "; 
			lblCod->Location = System::Drawing::Point(30, 30); 
			txtCodPais = gcnew TextBox(); 
			txtCodPais->Location = System::Drawing::Point(30, 50);

			// mismo para nombre
			Label^ lblNom = gcnew Label(); 
			lblNom->Text = L"Nombre del País:"; 
			lblNom->Location = System::Drawing::Point(30, 90); 
			txtNombre = gcnew TextBox(); 
			txtNombre->Location = System::Drawing::Point(30, 110); txtNombre->Width = 200;

			// salri
			Button^ btnGuardar = gcnew Button(); 
			btnGuardar->Text = L"Guardar insercion"; 
			btnGuardar->Location = System::Drawing::Point(90, 160);
			btnGuardar->Click += gcnew System::EventHandler(this, &FormInsertarPais::Guardar_Click); // chunche evento

			this->Controls->Add(lblCod); this->Controls->Add(txtCodPais);
			this->Controls->Add(lblNom); this->Controls->Add(txtNombre);
			this->Controls->Add(btnGuardar);
		}

	private:
		System::Void Guardar_Click(System::Object^ sender, System::EventArgs^ e) {
			// manda error x si vacios
			if (txtCodPais->Text == "" or txtNombre->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			// convierte lo de input de ventana a str
			string codPaisstr = msclr::interop::marshal_as<string>(txtCodPais->Text);
			string nombrestr = msclr::interop::marshal_as<string>(txtNombre->Text);
			int codPaisint = stoi(codPaisstr);
			arbolPaises->InsertarPais(codPaisint, nombrestr);

			MessageBox::Show(L"País guardado", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
			this->Close(); // Cierra la ventana tras guardar
		}
	};
	public ref class FormInsertar : public System::Windows::Forms::Form
	{
	private:
		ArbolPais* arbol;
	public:
		FormInsertar(ArbolPais* arbolRecibido) {
			arbol = arbolRecibido;
			this->Text = L"Insertar Registro";
			this->Size = System::Drawing::Size(400, 400);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;


			// lo meti en dos columnas diferentes por ahora, pq por alguna razon me estaba dando problemillas al tenerlo todo en una sola listilla vertical (se me estaba saliendo de la ventana de la compu y no me dejaba moverla para arriba, creo que es cosa de mi laptop, no del codigo, pq me ha estado dando problemas para chunches de otros cursos, asi q por ahora lo dejo asi)
			Button^ btnPaises = gcnew Button(); btnPaises->Text = L"1. Países"; btnPaises->Location = System::Drawing::Point(30, 30); btnPaises->Size = System::Drawing::Size(150, 40);
			Button^ btnCiudades = gcnew Button(); btnCiudades->Text = L"2. Ciudades"; btnCiudades->Location = System::Drawing::Point(30, 90); btnCiudades->Size = System::Drawing::Size(150, 40);
			Button^ btnPacientes = gcnew Button(); btnPacientes->Text = L"3. Pacientes"; btnPacientes->Location = System::Drawing::Point(30, 150); btnPacientes->Size = System::Drawing::Size(150, 40);
			Button^ btnMedicos = gcnew Button(); btnMedicos->Text = L"4. Médicos"; btnMedicos->Location = System::Drawing::Point(30, 210); btnMedicos->Size = System::Drawing::Size(150, 40);
			Button^ btnEspecialidades = gcnew Button(); btnEspecialidades->Text = L"5. Especialidades"; btnEspecialidades->Location = System::Drawing::Point(30, 270); btnEspecialidades->Size = System::Drawing::Size(150, 40);

			Button^ btnCitas = gcnew Button(); btnCitas->Text = L"6. Citas"; btnCitas->Location = System::Drawing::Point(200, 30); btnCitas->Size = System::Drawing::Size(150, 40);
			Button^ btnHabitaciones = gcnew Button(); btnHabitaciones->Text = L"7. Habitaciones"; btnHabitaciones->Location = System::Drawing::Point(200, 90); btnHabitaciones->Size = System::Drawing::Size(150, 40);
			Button^ btnHospitalizaciones = gcnew Button(); btnHospitalizaciones->Text = L"8. Hospitalizaciones"; btnHospitalizaciones->Location = System::Drawing::Point(200, 150); btnHospitalizaciones->Size = System::Drawing::Size(150, 40);
			Button^ btnDiagnosticos = gcnew Button(); btnDiagnosticos->Text = L"9. Diagnósticos"; btnDiagnosticos->Location = System::Drawing::Point(200, 210); btnDiagnosticos->Size = System::Drawing::Size(150, 40);
			Button^ btnTratamientos = gcnew Button(); btnTratamientos->Text = L"10. Tratamientos"; btnTratamientos->Location = System::Drawing::Point(200, 270); btnTratamientos->Size = System::Drawing::Size(150, 40);

			btnPaises->Click += gcnew System::EventHandler(this, &FormInsertar::Paises_Click);

			this->Controls->Add(btnPaises); 
			this->Controls->Add(btnCiudades); 
			this->Controls->Add(btnPacientes);
			this->Controls->Add(btnMedicos); 
			this->Controls->Add(btnEspecialidades); 
			this->Controls->Add(btnCitas);
			this->Controls->Add(btnHabitaciones); 
			this->Controls->Add(btnHospitalizaciones); 
			this->Controls->Add(btnDiagnosticos);
			this->Controls->Add(btnTratamientos);
		}
		System::Void Paises_Click(System::Object^ sender, System::EventArgs^ e) {
			FormInsertarPais^ ventanaPais = gcnew FormInsertarPais(arbol);
			ventanaPais->ShowDialog();
		}
	};

	public ref class FormMantenimiento : public System::Windows::Forms::Form
	{
	private:
		ArbolPais* arbol;
	public:
		FormMantenimiento(ArbolPais* arbolRecibido) {
			arbol = arbolRecibido;
			this->Text = L"Mantenimiento de Base de Datos";
			this->Size = System::Drawing::Size(300, 350);
			this->StartPosition = FormStartPosition::CenterParent; // sale en centro
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;// ni me acuerdo, pero salia en tutoria y me da pereza revisarlo again
			this->MaximizeBox = false;


			Button^ btnInsertar = gcnew Button();
			btnInsertar->Text = L"1. Insertar";
			btnInsertar->Location = System::Drawing::Point(50, 30);
			btnInsertar->Size = System::Drawing::Size(180, 40);
			btnInsertar->Click += gcnew System::EventHandler(this, &FormMantenimiento::Insertar_Click); // para q sirva x ahora

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

		// cosas acciones
		// testear insertar para tneer de base x ahora
		System::Void Insertar_Click(System::Object^ sender, System::EventArgs^ e) {
			FormInsertar^ ventanaInsertar = gcnew FormInsertar(arbol);
			ventanaInsertar->ShowDialog();
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
	FormMantenimiento^ ventana = gcnew FormMantenimiento(arbolPaises);
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