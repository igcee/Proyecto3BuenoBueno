#define _HAS_STD_BYTE 0
// ^ esto es para el error de C2872
#pragma once

#include <string>
#include <msclr/marshal_cppstd.h> // esto se ocupa para convertir texto de lo q sea q lo deja el winforms a string normalito
#include "Proyecto3/crud_paises.h" // con solo include crud_paises.h no lo encuentra (por alguna puta razon)
#include "Proyecto3/crud_citas.h"
#include "Proyecto3/crud_ciudades.h"
#include "Proyecto3/crud_diagnostico.h"
#include "Proyecto3/crud_especialidades.h"
#include "Proyecto3/crud_habitaciones.h"
#include "Proyecto3/crud_hospitalizaciones.h"
#include "Proyecto3/crud_medicos.h"
#include "Proyecto3/crud_pacientes.h"
#include "Proyecto3/crud_tratamientos.h"
// 
// NOTA: lo de crear la ventana con los botones va al puro final, pq sino manda error por no conocer chunches

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;




// PAIS -------------------------------------------------------------------------------------------------------------
	public ref class FormInsertarPais : public System::Windows::Forms::Form {
	private:
		TextBox^ txtCodPais;
		TextBox^ txtNombre; // guardar input de la ventana
		ArbolPais* arbolPaises;

	public:
		FormInsertarPais(ArbolPais* arbol) {
			arbolPaises = arbol;

			this->Text = L"Insertar Pais";
			this->Size = System::Drawing::Size(300, 250);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// cosas y cajita para input de codpais
			Label^ lblCod = gcnew Label();
			lblCod->Text = L"Codigo: ";
			lblCod->Location = System::Drawing::Point(30, 30);
			txtCodPais = gcnew TextBox();
			txtCodPais->Location = System::Drawing::Point(30, 50);

			// mismo para nombre
			Label^ lblNom = gcnew Label();
			lblNom->Text = L"Nombre del Pais:";
			lblNom->Location = System::Drawing::Point(30, 90);
			txtNombre = gcnew TextBox();
			txtNombre->Location = System::Drawing::Point(30, 110);

			// salri
			Button^ btnGuardar = gcnew Button();
			btnGuardar->Text = L"Guardar insercion";
			btnGuardar->Location = System::Drawing::Point(90, 160);
			btnGuardar->Click += gcnew System::EventHandler(this, &FormInsertarPais::Guardar_Click); // chunche evento

			this->Controls->Add(lblCod);
			this->Controls->Add(txtCodPais);
			this->Controls->Add(lblNom);
			this->Controls->Add(txtNombre);
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
			bool guardado = arbolPaises->InsertaNodo(codPaisint, nombrestr);

			if (guardado == true) {
				// exito y cierra ventana si bien guardado
				MessageBox::Show(L"Pais guardado con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				// sino no, y no cierra ventana para q se pueda corregir x usuario
				MessageBox::Show(L"Error: Ya existe un pais registrado con ese codigo.", L"Codigo Duplicado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};

// CIUDAD -------------------------------------------------------------------------------------------------------------
	public ref class FormInsertarCiudad : public System::Windows::Forms::Form {
	private:
		TextBox^ txtCodPais;
		TextBox^ txtCodCiudad;
		TextBox^ txtNombre;
		ArbolPais* arbolPaises; //validar pais
		ArbolCiudad* arbolCiudades;

	public:
		FormInsertarCiudad(ArbolPais* arbolP, ArbolCiudad* arbolC) {
			arbolPaises = arbolP;
			arbolCiudades = arbolC;

			this->Text = L"Insertar Ciudad";
			this->Size = System::Drawing::Size(300, 320);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// codpais
			Label^ lblCodPais = gcnew Label();
			lblCodPais->Text = L"Codigo del Pais:";
			lblCodPais->Location = System::Drawing::Point(30, 30);
			txtCodPais = gcnew TextBox();
			txtCodPais->Location = System::Drawing::Point(30, 50);

			// codciudad
			Label^ lblCodCiudad = gcnew Label();
			lblCodCiudad->Text = L"Codigo de la Ciudad:";
			lblCodCiudad->Location = System::Drawing::Point(30, 90);
			txtCodCiudad = gcnew TextBox();
			txtCodCiudad->Location = System::Drawing::Point(30, 110);

			// nombre
			Label^ lblNom = gcnew Label();
			lblNom->Text = L"Nombre de la Ciudad:";
			lblNom->Location = System::Drawing::Point(30, 150);
			txtNombre = gcnew TextBox();
			txtNombre->Location = System::Drawing::Point(30, 170);

	
			// salir
			Button^ btnGuardar = gcnew Button();
			btnGuardar->Text = L"Guardar insercion";
			btnGuardar->Location = System::Drawing::Point(90, 220);
			btnGuardar->Click += gcnew System::EventHandler(this, &FormInsertarCiudad::Guardar_Click);

			this->Controls->Add(lblCodPais); 
			this->Controls->Add(txtCodPais);

			this->Controls->Add(lblCodCiudad); 
			this->Controls->Add(txtCodCiudad);

			this->Controls->Add(lblNom); 
			this->Controls->Add(txtNombre);

			this->Controls->Add(btnGuardar);
		}

	private:
		// vacios
		System::Void Guardar_Click(System::Object^ sender, System::EventArgs^ e) {
			if (txtCodPais->Text == "" or txtCodCiudad->Text == "" or txtNombre->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string codPaisstr = msclr::interop::marshal_as<string>(txtCodPais->Text);
			string codCiudadstr = msclr::interop::marshal_as<string>(txtCodCiudad->Text);
			string nombrestr = msclr::interop::marshal_as<string>(txtNombre->Text);
			int codPaisint = stoi(codPaisstr);
			int codCiudadint = stoi(codCiudadstr);
			

			// codpais no existe
			if (arbolPaises->Buscarvalor(codPaisint) == nullptr) {
				MessageBox::Show(L"Error: Ese codigo de pais no existe", L"Pais no encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			bool guardado = arbolCiudades->InsertaNodo(codPaisint, codCiudadint, nombrestr);

			if (guardado == true) {
				MessageBox::Show(L"Ciudad guardada con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else { // repe
				MessageBox::Show(L"Error: Ya existe una ciudad registrada con ese codigo.", L"Codigo Duplicado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};



// ESPECIALIDAD -------------------------------------------------------------------------------------------------------------
	public ref class FormInsertarEspecialidad : public System::Windows::Forms::Form {
	private:
		TextBox^ txtIdEsp;
		TextBox^ txtNombre;
		TextBox^ txtDesc;
		ArbolEspecialidad* arbolEspecialidades;

	public:
		FormInsertarEspecialidad(ArbolEspecialidad* arbol) {
			arbolEspecialidades = arbol;

			this->Text = L"Insertar Especialidad";
			this->Size = System::Drawing::Size(340, 320);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// id
			Label^ lblId = gcnew Label();
			lblId->Text = L"Id de Especialidad:";
			lblId->Location = System::Drawing::Point(30, 30);
			txtIdEsp = gcnew TextBox();
			txtIdEsp->Location = System::Drawing::Point(30, 50);

			// nombre
			Label^ lblNom = gcnew Label();
			lblNom->Text = L"Nombre Especialidad:";
			lblNom->Location = System::Drawing::Point(30, 90);
			txtNombre = gcnew TextBox();
			txtNombre->Location = System::Drawing::Point(30, 110);

			// descripcion
			Label^ lblDesc = gcnew Label();
			lblDesc->Text = L"Descripcion:";
			lblDesc->Location = System::Drawing::Point(30, 150);
			txtDesc = gcnew TextBox();
			txtDesc->Location = System::Drawing::Point(30, 170);

			// salir
			Button^ btnGuardar = gcnew Button();
			btnGuardar->Text = L"Guardar insercion";
			btnGuardar->Location = System::Drawing::Point(100, 220);
			btnGuardar->Click += gcnew System::EventHandler(this, &FormInsertarEspecialidad::Guardar_Click);

			this->Controls->Add(lblId); 
			this->Controls->Add(txtIdEsp);
			this->Controls->Add(lblNom); 
			this->Controls->Add(txtNombre);
			this->Controls->Add(lblDesc); 
			this->Controls->Add(txtDesc);
			this->Controls->Add(btnGuardar);
		}

	private:
		System::Void Guardar_Click(System::Object^ sender, System::EventArgs^ e) {
			// vacios
			if (txtIdEsp->Text == "" or txtNombre->Text == "" or txtDesc->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string idespstr = msclr::interop::marshal_as<string>(txtIdEsp->Text);
			string nombrestr = msclr::interop::marshal_as<string>(txtNombre->Text);
			string descstr = msclr::interop::marshal_as<string>(txtDesc->Text);
			int idespint = stoi(idespstr);

			bool guardado = arbolEspecialidades->InsertaNodo(idespint, nombrestr, descstr);

			if (guardado == true) {
				MessageBox::Show(L"Especialidad guardada con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else { // repe
				MessageBox::Show(L"Error: Ya existe una especialidad con ese ID.", L"ID Duplicado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};

// TRATAMIENTO -------------------------------------------------------------------------------------------------------------
	public ref class FormInsertarTratamiento : public System::Windows::Forms::Form {
	private:
		TextBox^ txtIdTrata;
		TextBox^ txtNombre;
		TextBox^ txtDesc;
		TextBox^ txtCosto;
		ArbolTratamiento* arbolTrata;

	public:
		FormInsertarTratamiento(ArbolTratamiento* arbol) {
			arbolTrata = arbol;

			this->Text = L"Insertar Tratamiento";
			this->Size = System::Drawing::Size(360, 340);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// id
			Label^ lblId = gcnew Label();
			lblId->Text = L"Id de Tratamiento:";
			lblId->Location = System::Drawing::Point(30, 30);
			txtIdTrata = gcnew TextBox();
			txtIdTrata->Location = System::Drawing::Point(30, 50);

			// nombre
			Label^ lblNom = gcnew Label();
			lblNom->Text = L"Nombre Tratamiento:";
			lblNom->Location = System::Drawing::Point(30, 90);
			txtNombre = gcnew TextBox();
			txtNombre->Location = System::Drawing::Point(30, 110);

			// descripcion
			Label^ lblDesc = gcnew Label();
			lblDesc->Text = L"Descripcion:";
			lblDesc->Location = System::Drawing::Point(30, 150);
			txtDesc = gcnew TextBox();
			txtDesc->Location = System::Drawing::Point(30, 170);

			// costo
			Label^ lblCosto = gcnew Label();
			lblCosto->Text = L"Costo:";
			lblCosto->Location = System::Drawing::Point(30, 210);
			txtCosto = gcnew TextBox();
			txtCosto->Location = System::Drawing::Point(30, 230);

			// salir
			Button^ btnGuardar = gcnew Button();
			btnGuardar->Text = L"Guardar insercion";
			btnGuardar->Location = System::Drawing::Point(100, 260);
			btnGuardar->Click += gcnew System::EventHandler(this, &FormInsertarTratamiento::Guardar_Click);

			this->Controls->Add(lblId);
			this->Controls->Add(txtIdTrata);
			this->Controls->Add(lblNom);
			this->Controls->Add(txtNombre);
			this->Controls->Add(lblDesc);
			this->Controls->Add(txtDesc);
			this->Controls->Add(lblCosto);
			this->Controls->Add(txtCosto);
			this->Controls->Add(btnGuardar);
		}

	private:
		System::Void Guardar_Click(System::Object^ sender, System::EventArgs^ e) {
			// vacios
			if (txtIdTrata->Text == "" or txtNombre->Text == "" or txtDesc->Text == "" or txtCosto->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string idtratastr = msclr::interop::marshal_as<string>(txtIdTrata->Text);
			string nombrestr = msclr::interop::marshal_as<string>(txtNombre->Text);
			string descstr = msclr::interop::marshal_as<string>(txtDesc->Text);
			string costostr = msclr::interop::marshal_as<string>(txtCosto->Text);
			int idtrataint = stoi(idtratastr);
			double costodouble = stod(costostr);

			bool guardado = arbolTrata->InsertaNodo(idtrataint, nombrestr, descstr, costodouble);

			if (guardado == true) {
				MessageBox::Show(L"Tratamiento guardado con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else { // repe
				MessageBox::Show(L"Error: Ya existe un tratamiento con ese ID.", L"ID Duplicado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};




// DIAGNOSTICO -------------------------------------------------------------------------------------------------------------
	public ref class FormInsertarDiagnostico : public System::Windows::Forms::Form {
	private:
		TextBox^ txtIdDiag;
		TextBox^ txtNombre;
		TextBox^ txtDesc;
		ArbolDiagnostico* arbolDiag;

	public:
		FormInsertarDiagnostico(ArbolDiagnostico* arbol) {
			arbolDiag = arbol;

			this->Text = L"Insertar Diagnostico";
			this->Size = System::Drawing::Size(340, 320);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// id
			Label^ lblId = gcnew Label();
			lblId->Text = L"Id de Diagnostico:";
			lblId->Location = System::Drawing::Point(30, 30);
			txtIdDiag = gcnew TextBox();
			txtIdDiag->Location = System::Drawing::Point(30, 50);

			// nombre
			Label^ lblNom = gcnew Label();
			lblNom->Text = L"Nombre Diagnostico:";
			lblNom->Location = System::Drawing::Point(30, 90);
			txtNombre = gcnew TextBox();
			txtNombre->Location = System::Drawing::Point(30, 110);

			// descripcion
			Label^ lblDesc = gcnew Label();
			lblDesc->Text = L"Descripcion:";
			lblDesc->Location = System::Drawing::Point(30, 150);
			txtDesc = gcnew TextBox();
			txtDesc->Location = System::Drawing::Point(30, 170);

			// salir
			Button^ btnGuardar = gcnew Button();
			btnGuardar->Text = L"Guardar insercion";
			btnGuardar->Location = System::Drawing::Point(100, 220);
			btnGuardar->Click += gcnew System::EventHandler(this, &FormInsertarDiagnostico::Guardar_Click);

			this->Controls->Add(lblId);
			this->Controls->Add(txtIdDiag);
			this->Controls->Add(lblNom);
			this->Controls->Add(txtNombre);
			this->Controls->Add(lblDesc);
			this->Controls->Add(txtDesc);
			this->Controls->Add(btnGuardar);
		}

	private:
		System::Void Guardar_Click(System::Object^ sender, System::EventArgs^ e) {
			// vacios
			if (txtIdDiag->Text == "" or txtNombre->Text == "" or txtDesc->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string iddiagstr = msclr::interop::marshal_as<string>(txtIdDiag->Text);
			string nombrestr = msclr::interop::marshal_as<string>(txtNombre->Text);
			string descstr = msclr::interop::marshal_as<string>(txtDesc->Text);
			//int iddiagint = stoi(iddiagstr);

			bool guardado = arbolDiag->InsertaNodo(iddiagstr, nombrestr, descstr);

			if (guardado == true) {
				MessageBox::Show(L"Diagnostico guardado con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else { // repe
				MessageBox::Show(L"Error: Ya existe un diagnostico con ese ID.", L"ID Duplicado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};


// ventana con los botones ----------------------------------------------------------------------------------------

	public ref class FormInsertar : public System::Windows::Forms::Form
		// ventana insertar
		// tiene botones de los 10 chunches, que cada uno abre su propia ventana
	{
	private:
		ArbolPais* arbolilloPaises;
		ArbolCiudad* arbolilloCiudades;
		ArbolEspecialidad* arbolilloEsp;
		ArbolCitas* arbolilloCitas;
		ArbolHabitaciones* arbolilloHab;
		ArbolHospitalizaciones* arbolilloHosp;
		ArbolMedicos* arbolilloMed;
		ArbolPacientes* arbolilloPac;
		ArbolTratamiento* arbolilloTrata;
		ArbolDiagnostico* arbolilloDiag;

	public:
		FormInsertar(ArbolPais* arbolP, ArbolCiudad* arbolC, ArbolEspecialidad* arbolE, ArbolCitas* arbolCi, ArbolHabitaciones* arbolHa, ArbolHospitalizaciones* arbolHo, ArbolMedicos* arbolM, ArbolPacientes* arbolPac, ArbolTratamiento* arbolT, ArbolDiagnostico* arbolD) {
			arbolilloPaises = arbolP;
			arbolilloCiudades = arbolC;
			arbolilloEsp = arbolE;
			arbolilloCitas = arbolCi;
			arbolilloHab = arbolHa;
			arbolilloHosp = arbolHo;
			arbolilloMed = arbolM;
			arbolilloPac = arbolPac;
			arbolilloTrata = arbolT;
			arbolilloDiag = arbolD;



			this->Text = L"Insertar Registro";
			this->Size = System::Drawing::Size(400, 400);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false; // maximaze quita la opcion de darle a pantalla completa (el cuadradito q esta a la par de la X para cerrar la ventana)

			// dos columnas (la laptop no dejaba mover la ventana si era una sola lista vertical, pero eso es cosa mia no del codigo ni del visual (creo))
			Button^ btnPaises = gcnew Button();
			btnPaises->Text = L"1. Paises";
			btnPaises->Location = System::Drawing::Point(30, 30);
			btnPaises->Size = System::Drawing::Size(150, 40);
			Button^ btnCiudades = gcnew Button();
			btnCiudades->Text = L"2. Ciudades";
			btnCiudades->Location = System::Drawing::Point(30, 90);
			btnCiudades->Size = System::Drawing::Size(150, 40);
			Button^ btnPacientes = gcnew Button();
			btnPacientes->Text = L"3. Pacientes";
			btnPacientes->Location = System::Drawing::Point(30, 150);
			btnPacientes->Size = System::Drawing::Size(150, 40);
			Button^ btnMedicos = gcnew Button();
			btnMedicos->Text = L"4. Medicos";
			btnMedicos->Location = System::Drawing::Point(30, 210);
			btnMedicos->Size = System::Drawing::Size(150, 40);
			Button^ btnEspecialidades = gcnew Button();
			btnEspecialidades->Text = L"5. Especialidades";
			btnEspecialidades->Location = System::Drawing::Point(30, 270);
			btnEspecialidades->Size = System::Drawing::Size(150, 40);

			Button^ btnCitas = gcnew Button();
			btnCitas->Text = L"6. Citas";
			btnCitas->Location = System::Drawing::Point(200, 30);
			btnCitas->Size = System::Drawing::Size(150, 40);
			Button^ btnHabitaciones = gcnew Button();
			btnHabitaciones->Text = L"7. Habitaciones";
			btnHabitaciones->Location = System::Drawing::Point(200, 90);
			btnHabitaciones->Size = System::Drawing::Size(150, 40);
			Button^ btnHospitalizaciones = gcnew Button();
			btnHospitalizaciones->Text = L"8. Hospitalizaciones";
			btnHospitalizaciones->Location = System::Drawing::Point(200, 150);
			btnHospitalizaciones->Size = System::Drawing::Size(150, 40);
			Button^ btnDiagnosticos = gcnew Button();
			btnDiagnosticos->Text = L"9. Diagnosticos";
			btnDiagnosticos->Location = System::Drawing::Point(200, 210);
			btnDiagnosticos->Size = System::Drawing::Size(150, 40);
			Button^ btnTratamientos = gcnew Button();
			btnTratamientos->Text = L"10. Tratamientos";
			btnTratamientos->Location = System::Drawing::Point(200, 270);
			btnTratamientos->Size = System::Drawing::Size(150, 40);

			btnPaises->Click += gcnew System::EventHandler(this, &FormInsertar::Paises_Click);
			btnCiudades->Click += gcnew System::EventHandler(this, &FormInsertar::Ciudades_Click);
			btnEspecialidades->Click += gcnew System::EventHandler(this, &FormInsertar::Especialidades_Click);
			btnTratamientos->Click += gcnew System::EventHandler(this, &FormInsertar::Tratamientos_Click);
			btnDiagnosticos->Click += gcnew System::EventHandler(this, &FormInsertar::Diagnosticos_Click);

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
		
		// eventos botones
		System::Void Paises_Click(System::Object^ sender, System::EventArgs^ e) {
			FormInsertarPais^ ventanaPais = gcnew FormInsertarPais(arbolilloPaises);
			ventanaPais->ShowDialog();
		}

		System::Void Ciudades_Click(System::Object^ sender, System::EventArgs^ e) {
			FormInsertarCiudad^ ventanaCiudad = gcnew FormInsertarCiudad(arbolilloPaises, arbolilloCiudades);
			ventanaCiudad->ShowDialog();
		}

		System::Void Especialidades_Click(System::Object^ sender, System::EventArgs^ e) {
			FormInsertarEspecialidad^ ventanaEspecialidad = gcnew FormInsertarEspecialidad(arbolilloEsp);
			ventanaEspecialidad->ShowDialog();
		}

		System::Void Tratamientos_Click(System::Object^ sender, System::EventArgs^ e) {
			FormInsertarTratamiento^ ventanaTratamiento = gcnew FormInsertarTratamiento(arbolilloTrata);
			ventanaTratamiento->ShowDialog();
		}

		System::Void Diagnosticos_Click(System::Object^ sender, System::EventArgs^ e) {
			FormInsertarDiagnostico^ ventanaDiagnostico = gcnew FormInsertarDiagnostico(arbolilloDiag);
			ventanaDiagnostico->ShowDialog();
		}
	};
}