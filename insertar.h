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
			lblCodPais->AutoSize = true;
			txtCodPais = gcnew TextBox();
			txtCodPais->Location = System::Drawing::Point(30, 50);

			// codciudad
			Label^ lblCodCiudad = gcnew Label();
			lblCodCiudad->Text = L"Codigo de la Ciudad:";
			lblCodCiudad->Location = System::Drawing::Point(30, 90);
			lblCodCiudad->AutoSize = true;
			txtCodCiudad = gcnew TextBox();
			txtCodCiudad->Location = System::Drawing::Point(30, 110);

			// nombre
			Label^ lblNom = gcnew Label();
			lblNom->Text = L"Nombre de la Ciudad:";
			lblNom->Location = System::Drawing::Point(30, 150);
			lblNom->AutoSize = true;
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
			lblId->AutoSize = true;
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
			lblId->AutoSize = true;
			txtIdTrata = gcnew TextBox();
			txtIdTrata->Location = System::Drawing::Point(30, 50);

			// nombre
			Label^ lblNom = gcnew Label();
			lblNom->Text = L"Nombre Tratamiento:";
			lblNom->Location = System::Drawing::Point(30, 90);
			lblNom->AutoSize = true;
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
			lblId->AutoSize = true;
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



// PACIENTE -------------------------------------------------------------------------------------------------------------
	public ref class FormInsertarPaciente : public System::Windows::Forms::Form {
	private:
		TextBox^ txtIdPac;
		TextBox^ txtNombre;
		TextBox^ txtFecha;
		TextBox^ txtTel;
		TextBox^ txtCodPais;
		TextBox^ txtCodCiudad;
		TextBox^ txtCorreo;
		ArbolPais* arbolPaises;
		ArbolCiudad* arbolCiudades;
		ArbolPacientes* arbolPacientes;

	public:
		FormInsertarPaciente(ArbolPais* arbolP, ArbolCiudad* arbolC, ArbolPacientes* arbolPac) {
			arbolPaises = arbolP;
			arbolCiudades = arbolC;
			arbolPacientes = arbolPac;

			this->Text = L"Insertar Paciente";
			this->Size = System::Drawing::Size(340, 500);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// id
			Label^ lblId = gcnew Label();
			lblId->Text = L"Id de Paciente:";
			lblId->Location = System::Drawing::Point(30, 20);
			lblId->AutoSize = true;
			txtIdPac = gcnew TextBox();
			txtIdPac->Location = System::Drawing::Point(30, 40);

			// nombre
			Label^ lblNom = gcnew Label();
			lblNom->Text = L"Nombre:";
			lblNom->Location = System::Drawing::Point(30, 70);
			txtNombre = gcnew TextBox();
			txtNombre->Location = System::Drawing::Point(30, 90);

			// fecha
			Label^ lblFecha = gcnew Label();
			lblFecha->Text = L"Fecha de Nac. (ej. 15-05-1990):";
			lblFecha->Location = System::Drawing::Point(30, 120);
			lblFecha->AutoSize = true;
			txtFecha = gcnew TextBox();
			txtFecha->Location = System::Drawing::Point(30, 140);

			// telefono
			Label^ lblTel = gcnew Label();
			lblTel->Text = L"Telefono:";
			lblTel->Location = System::Drawing::Point(30, 170);
			lblTel->AutoSize = true;
			txtTel = gcnew TextBox();
			txtTel->Location = System::Drawing::Point(30, 190);

			// codpais
			Label^ lblCodPais = gcnew Label();
			lblCodPais->Text = L"Codigo de Pais:";
			lblCodPais->Location = System::Drawing::Point(30, 220);
			txtCodPais = gcnew TextBox();
			txtCodPais->Location = System::Drawing::Point(30, 240);

			// codciudad
			Label^ lblCodCiudad = gcnew Label();
			lblCodCiudad->Text = L"Codigo de Ciudad:";
			lblCodCiudad->Location = System::Drawing::Point(30, 270);
			txtCodCiudad = gcnew TextBox();
			txtCodCiudad->Location = System::Drawing::Point(30, 290);

			// correo
			Label^ lblCorreo = gcnew Label();
			lblCorreo->Text = L"Correo Electronico:";
			lblCorreo->Location = System::Drawing::Point(30, 320);
			txtCorreo = gcnew TextBox();
			txtCorreo->Location = System::Drawing::Point(30, 340);

			// salir
			Button^ btnGuardar = gcnew Button();
			btnGuardar->Text = L"Guardar insercion";
			btnGuardar->Location = System::Drawing::Point(100, 390);
			btnGuardar->Click += gcnew System::EventHandler(this, &FormInsertarPaciente::Guardar_Click);

			this->Controls->Add(lblId); 
			this->Controls->Add(txtIdPac);
			this->Controls->Add(lblNom); 
			this->Controls->Add(txtNombre);
			this->Controls->Add(lblFecha); 
			this->Controls->Add(txtFecha);
			this->Controls->Add(lblTel); 
			this->Controls->Add(txtTel);
			this->Controls->Add(lblCodPais); 
			this->Controls->Add(txtCodPais);
			this->Controls->Add(lblCodCiudad); 
			this->Controls->Add(txtCodCiudad);
			this->Controls->Add(lblCorreo); 
			this->Controls->Add(txtCorreo);
			this->Controls->Add(btnGuardar);
		}

	private:
		System::Void Guardar_Click(System::Object^ sender, System::EventArgs^ e) {
			// vacios
			if (txtIdPac->Text == "" or txtNombre->Text == "" or txtFecha->Text == "" or txtTel->Text == "" or txtCodPais->Text == "" or txtCodCiudad->Text == "" or txtCorreo->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string idpacstr = msclr::interop::marshal_as<string>(txtIdPac->Text);
			string nombrestr = msclr::interop::marshal_as<string>(txtNombre->Text);
			string fechastr = msclr::interop::marshal_as<string>(txtFecha->Text);
			string telefonostr = msclr::interop::marshal_as<string>(txtTel->Text);
			string codPaisstr = msclr::interop::marshal_as<string>(txtCodPais->Text);
			string codCiudadstr = msclr::interop::marshal_as<string>(txtCodCiudad->Text);
			string correostr = msclr::interop::marshal_as<string>(txtCorreo->Text);

			int idpacint = stoi(idpacstr);
			int codPaisint = stoi(codPaisstr);
			int codCiudadint = stoi(codCiudadstr);


			if (arbolCiudades->Buscarvalor(codPaisint, codCiudadint) == nullptr) {
				MessageBox::Show(L"Error: Esa ciudad no existe en el pais del codigo indicado.", L"Ciudad no encontrada", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			bool guardado = arbolPacientes->InsertaNodo(idpacint, nombrestr, fechastr, telefonostr, codPaisint, codCiudadint, correostr);

			if (guardado == true) {
				MessageBox::Show(L"Paciente guardado con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else { // repe
				MessageBox::Show(L"Error: Ya existe un paciente con ese ID.", L"ID Duplicado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};

// MEDICO -------------------------------------------------------------------------------------------------------------
	public ref class FormInsertarMedico : public System::Windows::Forms::Form {
	private:
		TextBox^ txtIdMed;
		TextBox^ txtNombre;
		TextBox^ txtTel;
		TextBox^ txtCorreo;
		TextBox^ txtIdEsp;
		ArbolEspecialidad* arbolEspecialidades;
		ArbolMedicos* arbolMedicos;

	public:
		FormInsertarMedico(ArbolEspecialidad* arbolEsp, ArbolMedicos* arbolMed) {
			arbolEspecialidades = arbolEsp;
			arbolMedicos = arbolMed;

			this->Text = L"Insertar Medico";
			this->Size = System::Drawing::Size(340, 400);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// id
			Label^ lblId = gcnew Label();
			lblId->Text = L"Id de Medico:";
			lblId->Location = System::Drawing::Point(30, 20);
			lblId->AutoSize = true;
			txtIdMed = gcnew TextBox();
			txtIdMed->Location = System::Drawing::Point(30, 40);

			// nombre
			Label^ lblNom = gcnew Label();
			lblNom->Text = L"Nombre :";
			lblNom->Location = System::Drawing::Point(30, 70);
			txtNombre = gcnew TextBox();
			txtNombre->Location = System::Drawing::Point(30, 90);

			// telefono
			Label^ lblTel = gcnew Label();
			lblTel->Text = L"Telefono:";
			lblTel->Location = System::Drawing::Point(30, 120);
			txtTel = gcnew TextBox();
			txtTel->Location = System::Drawing::Point(30, 140);

			// correo
			Label^ lblCorreo = gcnew Label();
			lblCorreo->Text = L"Correo Electronico:";
			lblCorreo->Location = System::Drawing::Point(30, 170);
			lblCorreo->AutoSize = true;
			txtCorreo = gcnew TextBox();
			txtCorreo->Location = System::Drawing::Point(30, 190);

			// idespecialidad
			Label^ lblIdEsp = gcnew Label();
			lblIdEsp->Text = L"Id de Especialidad:";
			lblIdEsp->Location = System::Drawing::Point(30, 220);
			lblIdEsp->AutoSize = true;
			txtIdEsp = gcnew TextBox();
			txtIdEsp->Location = System::Drawing::Point(30, 240);

			// salir
			Button^ btnGuardar = gcnew Button();
			btnGuardar->Text = L"Guardar insercion";
			btnGuardar->Location = System::Drawing::Point(100, 290);
			btnGuardar->Size = System::Drawing::Size(120, 30);
			btnGuardar->Click += gcnew System::EventHandler(this, &FormInsertarMedico::Guardar_Click);

			this->Controls->Add(lblId); 
			this->Controls->Add(txtIdMed);
			this->Controls->Add(lblNom); 
			this->Controls->Add(txtNombre);
			this->Controls->Add(lblTel); 
			this->Controls->Add(txtTel);
			this->Controls->Add(lblCorreo); 
			this->Controls->Add(txtCorreo);
			this->Controls->Add(lblIdEsp); 
			this->Controls->Add(txtIdEsp);
			this->Controls->Add(btnGuardar);
		}

	private:
		System::Void Guardar_Click(System::Object^ sender, System::EventArgs^ e) {
			// vacios
			if (txtIdMed->Text == "" or txtNombre->Text == "" or txtTel->Text == "" or txtCorreo->Text == "" or txtIdEsp->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string idmedicostr = msclr::interop::marshal_as<string>(txtIdMed->Text);
			string nombrestr = msclr::interop::marshal_as<string>(txtNombre->Text);
			string telefonostr = msclr::interop::marshal_as<string>(txtTel->Text);
			string correostr = msclr::interop::marshal_as<string>(txtCorreo->Text);
			string idespstr = msclr::interop::marshal_as<string>(txtIdEsp->Text);

			int idmedicoint = stoi(idmedicostr);
			int idespint = stoi(idespstr);

			// idesp hay
			if (arbolEspecialidades->Buscarvalor(idespint) == nullptr) {
				MessageBox::Show(L"Error: Ese ID de especialidad no existe.", L"Especialidad no encontrada", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			bool guardado = arbolMedicos->InsertaNodo(idmedicoint, nombrestr, telefonostr, correostr, idespint);

			if (guardado == true) {
				MessageBox::Show(L"Medico guardado con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else { // repe
				MessageBox::Show(L"Error: Ya existe un medico con ese ID.", L"ID Duplicado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};

// HABITACION -------------------------------------------------------------------------------------------------------------
	public ref class FormInsertarHabitacion : public System::Windows::Forms::Form {
	private:
		TextBox^ txtIdHab;
		TextBox^ txtNumero;
		TextBox^ txtPiso;
		TextBox^ txtTipo; // recordatorio q tipo es 1/2/3
		TextBox^ txtEstado; // y estado 0/1
		ArbolHabitaciones* arbolHabitaciones;

	public:
		FormInsertarHabitacion(ArbolHabitaciones* arbol) {
			arbolHabitaciones = arbol;

			this->Text = L"Insertar Habitacion";
			this->Size = System::Drawing::Size(340, 400);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// id
			Label^ lblId = gcnew Label();
			lblId->Text = L"Id de Habitacion:";
			lblId->Location = System::Drawing::Point(30, 20);
			lblId->AutoSize = true;
			txtIdHab = gcnew TextBox();
			txtIdHab->Location = System::Drawing::Point(30, 40);

			// numero
			Label^ lblNum = gcnew Label();
			lblNum->Text = L"Numero:";
			lblNum->Location = System::Drawing::Point(30, 70);
			txtNumero = gcnew TextBox();
			txtNumero->Location = System::Drawing::Point(30, 90);

			// piso
			Label^ lblPiso = gcnew Label();
			lblPiso->Text = L"Piso:";
			lblPiso->Location = System::Drawing::Point(30, 120);
			txtPiso = gcnew TextBox();
			txtPiso->Location = System::Drawing::Point(30, 140);

			// tipo
			Label^ lblTipo = gcnew Label();
			lblTipo->Text = L"Tipo (1 Indiv, 2 Comp, 3 UCI):";
			lblTipo->Location = System::Drawing::Point(30, 170);
			lblTipo->AutoSize = true;
			txtTipo = gcnew TextBox();
			txtTipo->Location = System::Drawing::Point(30, 190);

			// estado
			Label^ lblEstado = gcnew Label();
			lblEstado->Text = L"Estado (0 Disp, 1 Ocupada):";
			lblEstado->Location = System::Drawing::Point(30, 220);
			lblEstado->AutoSize = true;
			txtEstado = gcnew TextBox();
			txtEstado->Location = System::Drawing::Point(30, 240);

			// salir
			Button^ btnGuardar = gcnew Button();
			btnGuardar->Text = L"Guardar insercion";
			btnGuardar->Location = System::Drawing::Point(100, 290);
			btnGuardar->Size = System::Drawing::Size(120, 30);
			btnGuardar->Click += gcnew System::EventHandler(this, &FormInsertarHabitacion::Guardar_Click);

			this->Controls->Add(lblId); 
			this->Controls->Add(txtIdHab);
			this->Controls->Add(lblNum); 
			this->Controls->Add(txtNumero);
			this->Controls->Add(lblPiso); 
			this->Controls->Add(txtPiso);
			this->Controls->Add(lblTipo); 
			this->Controls->Add(txtTipo);
			this->Controls->Add(lblEstado); 
			this->Controls->Add(txtEstado);
			this->Controls->Add(btnGuardar);
		}

	private:
		System::Void Guardar_Click(System::Object^ sender, System::EventArgs^ e) {
			// vacios
			if (txtIdHab->Text == "" or txtNumero->Text == "" or txtPiso->Text == "" or txtTipo->Text == "" or txtEstado->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string idhabstr = msclr::interop::marshal_as<string>(txtIdHab->Text);
			string numstr = msclr::interop::marshal_as<string>(txtNumero->Text);
			string pisostr = msclr::interop::marshal_as<string>(txtPiso->Text);
			string tipostr = msclr::interop::marshal_as<string>(txtTipo->Text);
			string estadostr = msclr::interop::marshal_as<string>(txtEstado->Text);

			int idhabint = stoi(idhabstr);
			int numint = stoi(numstr);
			//int pisoint = stoi(pisostr);
			int tipoint = stoi(tipostr);
			int estadoint = stoi(estadostr);

			bool guardado = arbolHabitaciones->InsertaNodo(idhabint, numint, pisostr, tipoint, estadoint);

			if (guardado == true) {
				MessageBox::Show(L"Habitacion guardada con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else { // repe
				MessageBox::Show(L"Error: Ya existe una habitacion con ese ID.", L"ID Duplicado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};



// HOSPITALIZACIONES -------------------------------------------------------------------------------------------------------------
	public ref class FormInsertarHospitalizacion : public System::Windows::Forms::Form {
	private:
		TextBox^ txtIdHosp;
		TextBox^ txtIdPac;
		TextBox^ txtIdHab;
		TextBox^ txtIdMed;
		TextBox^ txtFechaIn;
		TextBox^ txtFechaOut;
		TextBox^ txtMotivo;
		ArbolPacientes* arbolPac;
		ArbolHabitaciones* arbolHab;
		ArbolMedicos* arbolMed;
		ArbolHospitalizaciones* arbolHosp;

	public:
		FormInsertarHospitalizacion(ArbolPacientes* aPac, ArbolHabitaciones* aHab, ArbolMedicos* aMed, ArbolHospitalizaciones* aHosp) {
			arbolPac = aPac;
			arbolHab = aHab;
			arbolMed = aMed;
			arbolHosp = aHosp;

			this->Text = L"Insertar Hospitalizacion";
			this->Size = System::Drawing::Size(340, 500);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// id hospitalizacion
			Label^ lblId = gcnew Label();
			lblId->Text = L"Id de Hosp:"; // me fije q cuando el texto es muy grande, las palabras se cortan ("Id de Hospitalizacion:" se mostraba como "Id de"). Se deberia de resolver haciendo mas largo el label pero eso lo hago luego, pq habria que cambiar varias cosillas a todos los tamanos de lo de insertar y ahorita me da pereza
			lblId->Location = System::Drawing::Point(30, 20);
			txtIdHosp = gcnew TextBox();
			txtIdHosp->Location = System::Drawing::Point(30, 40);

			// id paciente
			Label^ lblIdPac = gcnew Label();
			lblIdPac->Text = L"Id del Paciente:";
			lblIdPac->Location = System::Drawing::Point(30, 70);
			txtIdPac = gcnew TextBox();
			txtIdPac->Location = System::Drawing::Point(30, 90);

			// id habitacion
			Label^ lblIdHab = gcnew Label();
			lblIdHab->Text = L"Id de la Habitacion:";
			lblIdHab->Location = System::Drawing::Point(30, 120);
			txtIdHab = gcnew TextBox();
			txtIdHab->Location = System::Drawing::Point(30, 140);

			// id medico
			Label^ lblIdMed = gcnew Label();
			lblIdMed->Text = L"Id del Medico:";
			lblIdMed->Location = System::Drawing::Point(30, 170);
			txtIdMed = gcnew TextBox();
			txtIdMed->Location = System::Drawing::Point(30, 190);

			// ingreso
			Label^ lblFechaIn = gcnew Label();
			lblFechaIn->Text = L"Fecha Ingreso (dd/mm/aa):";
			lblFechaIn->Location = System::Drawing::Point(30, 220);
			lblFechaIn->AutoSize = true;
			txtFechaIn = gcnew TextBox();
			txtFechaIn->Location = System::Drawing::Point(30, 240);

			// salida
			Label^ lblFechaOut = gcnew Label();
			lblFechaOut->Text = L"Fecha Salida (dd/mm/aa, 0000 para no indicar):";
			lblFechaOut->Location = System::Drawing::Point(30, 270);
			lblFechaOut->AutoSize = true;
			txtFechaOut = gcnew TextBox();
			txtFechaOut->Location = System::Drawing::Point(30, 290);

			// motivo
			Label^ lblMotivo = gcnew Label();
			lblMotivo->Text = L"Motivo:";
			lblMotivo->Location = System::Drawing::Point(30, 320);
			txtMotivo = gcnew TextBox();
			txtMotivo->Location = System::Drawing::Point(30, 340);

			// salir
			Button^ btnGuardar = gcnew Button();
			btnGuardar->Text = L"Guardar insercion";
			btnGuardar->Location = System::Drawing::Point(100, 390);
			btnGuardar->Size = System::Drawing::Size(120, 30);
			btnGuardar->Click += gcnew System::EventHandler(this, &FormInsertarHospitalizacion::Guardar_Click);

			this->Controls->Add(lblId); 
			this->Controls->Add(txtIdHosp);
			this->Controls->Add(lblIdPac); 
			this->Controls->Add(txtIdPac);
			this->Controls->Add(lblIdHab); 
			this->Controls->Add(txtIdHab);
			this->Controls->Add(lblIdMed); 
			this->Controls->Add(txtIdMed);
			this->Controls->Add(lblFechaIn); 
			this->Controls->Add(txtFechaIn);
			this->Controls->Add(lblFechaOut); 
			this->Controls->Add(txtFechaOut);
			this->Controls->Add(lblMotivo); 
			this->Controls->Add(txtMotivo);
			this->Controls->Add(btnGuardar);
		}

	private:
		System::Void Guardar_Click(System::Object^ sender, System::EventArgs^ e) {
			// vacios
			if (txtIdHosp->Text == "" or txtIdPac->Text == "" or txtIdHab->Text == "" or txtIdMed->Text == "" or txtFechaIn->Text == "" or txtFechaOut->Text == "" or txtMotivo->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string idhospstr = msclr::interop::marshal_as<string>(txtIdHosp->Text);
			string idpacstr = msclr::interop::marshal_as<string>(txtIdPac->Text);
			string idhabstr = msclr::interop::marshal_as<string>(txtIdHab->Text);
			string idmedstr = msclr::interop::marshal_as<string>(txtIdMed->Text);
			string fechainstr = msclr::interop::marshal_as<string>(txtFechaIn->Text);
			string fechaoutstr = msclr::interop::marshal_as<string>(txtFechaOut->Text);
			string motivostr = msclr::interop::marshal_as<string>(txtMotivo->Text);

			int idhospint = stoi(idhospstr);
			int idpacint = stoi(idpacstr);
			int idhabint = stoi(idhabstr);
			int idmedint = stoi(idmedstr);

			// validar paciente
			if (arbolPac->Buscarvalor(idpacint) == nullptr) {
				MessageBox::Show(L"Error: Ese ID de paciente no existe.", L"Paciente no encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			// validar habitacion
			if (arbolHab->Buscarvalor(idhabint) == nullptr) {
				MessageBox::Show(L"Error: Ese ID de habitacion no existe.", L"Habitacion no encontrada", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			// validar medico
			if (arbolMed->Buscarvalor(idmedint) == nullptr) {
				MessageBox::Show(L"Error: Ese ID de medico no existe.", L"Medico no encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			bool guardado = arbolHosp->InsertaNodo(idhospint, idpacint, idhabint, idmedint, fechainstr, fechaoutstr, motivostr);

			if (guardado == true) {
				MessageBox::Show(L"Hospitalizacion guardada con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else { // repe
				MessageBox::Show(L"Error: Ya existe una hospitalizacion con ese ID.", L"ID Duplicado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};


// CITA -------------------------------------------------------------------------------------------------------------
	public ref class FormInsertarCita : public System::Windows::Forms::Form {
	private:
		TextBox^ txtIdCita;
		TextBox^ txtIdPac;
		TextBox^ txtIdMed;
		TextBox^ txtIdEsp;
		TextBox^ txtFecha;
		TextBox^ txtHora;
		TextBox^ txtMotivo;
		TextBox^ txtEstado; // recordatorio estado aca tambien es 0/1
		ArbolPacientes* arbolPac;
		ArbolMedicos* arbolMed;
		ArbolEspecialidad* arbolEsp;
		ArbolCitas* arbolCitas;

	public:
		FormInsertarCita(ArbolPacientes* aPac, ArbolMedicos* aMed, ArbolEspecialidad* aEsp, ArbolCitas* aCita) {
			arbolPac = aPac;
			arbolMed = aMed;
			arbolEsp = aEsp;
			arbolCitas = aCita;

			this->Text = L"Insertar Cita";
			this->Size = System::Drawing::Size(340, 550);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// id cita
			Label^ lblIdCita = gcnew Label();
			lblIdCita->Text = L"Id de Cita:";
			lblIdCita->Location = System::Drawing::Point(30, 20);
			txtIdCita = gcnew TextBox();
			txtIdCita->Location = System::Drawing::Point(30, 40);

			// id paciente
			Label^ lblIdPac = gcnew Label();
			lblIdPac->Text = L"Id de Paciente:";
			lblIdPac->Location = System::Drawing::Point(30, 70);
			txtIdPac = gcnew TextBox();
			txtIdPac->Location = System::Drawing::Point(30, 90);

			// id medico
			Label^ lblIdMed = gcnew Label();
			lblIdMed->Text = L"Id de Medico:";
			lblIdMed->Location = System::Drawing::Point(30, 120);
			txtIdMed = gcnew TextBox();
			txtIdMed->Location = System::Drawing::Point(30, 140);

			// id especialidad
			Label^ lblIdEsp = gcnew Label();
			lblIdEsp->Text = L"Id de Especialidad:";
			lblIdEsp->Location = System::Drawing::Point(30, 170);
			txtIdEsp = gcnew TextBox();
			txtIdEsp->Location = System::Drawing::Point(30, 190);

			// fecha
			Label^ lblFecha = gcnew Label();
			lblFecha->Text = L"Fecha (dd/mm/aa):";
			lblFecha->Location = System::Drawing::Point(30, 220);
			lblFecha->AutoSize = true;
			txtFecha = gcnew TextBox();
			txtFecha->Location = System::Drawing::Point(30, 240);

			// hora
			Label^ lblHora = gcnew Label();
			lblHora->Text = L"Hora (ej. 09:30, lapsos de 15min):";
			lblHora->Location = System::Drawing::Point(30, 270);
			lblHora->AutoSize = true;
			txtHora = gcnew TextBox();
			txtHora->Location = System::Drawing::Point(30, 290);

			// motivo
			Label^ lblMotivo = gcnew Label();
			lblMotivo->Text = L"Motivo:";
			lblMotivo->Location = System::Drawing::Point(30, 320);
			txtMotivo = gcnew TextBox();
			txtMotivo->Location = System::Drawing::Point(30, 340);

			// estado
			Label^ lblEstado = gcnew Label();
			lblEstado->Text = L"Estado (0 Pendiente, 1 Confirmada):";
			lblEstado->Location = System::Drawing::Point(30, 370);
			lblEstado->AutoSize = true;
			txtEstado = gcnew TextBox();
			txtEstado->Location = System::Drawing::Point(30, 390);

			// salir
			Button^ btnGuardar = gcnew Button();
			btnGuardar->Text = L"Guardar insercion";
			btnGuardar->Location = System::Drawing::Point(100, 440);
			btnGuardar->Size = System::Drawing::Size(120, 30);
			btnGuardar->Click += gcnew System::EventHandler(this, &FormInsertarCita::Guardar_Click);

			this->Controls->Add(lblIdCita); 
			this->Controls->Add(txtIdCita);
			this->Controls->Add(lblIdPac); 
			this->Controls->Add(txtIdPac);
			this->Controls->Add(lblIdMed); 
			this->Controls->Add(txtIdMed);
			this->Controls->Add(lblIdEsp); 
			this->Controls->Add(txtIdEsp);
			this->Controls->Add(lblFecha); 
			this->Controls->Add(txtFecha);
			this->Controls->Add(lblHora); 
			this->Controls->Add(txtHora);
			this->Controls->Add(lblMotivo); 
			this->Controls->Add(txtMotivo);
			this->Controls->Add(lblEstado); 
			this->Controls->Add(txtEstado);
			this->Controls->Add(btnGuardar);
		}

	private:
		System::Void Guardar_Click(System::Object^ sender, System::EventArgs^ e) {
			// vacios
			if (txtIdCita->Text == "" or txtIdPac->Text == "" or txtIdMed->Text == "" or txtIdEsp->Text == "" or txtFecha->Text == "" or txtHora->Text == "" or txtMotivo->Text == "" or txtEstado->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string idcitastr = msclr::interop::marshal_as<string>(txtIdCita->Text);
			string idpacstr = msclr::interop::marshal_as<string>(txtIdPac->Text);
			string idmedstr = msclr::interop::marshal_as<string>(txtIdMed->Text);
			string idespstr = msclr::interop::marshal_as<string>(txtIdEsp->Text);
			string fechastr = msclr::interop::marshal_as<string>(txtFecha->Text);
			string horastr = msclr::interop::marshal_as<string>(txtHora->Text);
			string motivostr = msclr::interop::marshal_as<string>(txtMotivo->Text);
			string estadostr = msclr::interop::marshal_as<string>(txtEstado->Text);

			int idcitaint = stoi(idcitastr);
			int idpacint = stoi(idpacstr);
			int idmedint = stoi(idmedstr);
			int idespint = stoi(idespstr);
			int estadoint = stoi(estadostr);

			// validar paciente
			if (arbolPac->Buscarvalor(idpacint) == nullptr) {
				MessageBox::Show(L"Error: Ese ID de paciente no existe.", L"Paciente no encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			// validar medico
			if (arbolMed->Buscarvalor(idmedint) == nullptr) {
				MessageBox::Show(L"Error: Ese ID de medico no existe.", L"Medico no encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			// validar especialidad
			if (arbolEsp->Buscarvalor(idespint) == nullptr) {
				MessageBox::Show(L"Error: Ese ID de especialidad no existe.", L"Especialidad no encontrada", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			bool guardado = arbolCitas->InsertaNodo(idcitaint, idpacint, idmedint, idespint, fechastr, horastr, motivostr, estadoint);

			if (guardado == true) {
				MessageBox::Show(L"Cita guardada con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else { // repe
				MessageBox::Show(L"Error: Ya existe una cita con ese ID.", L"ID Duplicado", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
			btnPacientes->Click += gcnew System::EventHandler(this, &FormInsertar::Pacientes_Click);
			btnMedicos->Click += gcnew System::EventHandler(this, &FormInsertar::Medicos_Click);
			btnHabitaciones->Click += gcnew System::EventHandler(this, &FormInsertar::Habitaciones_Click);
			btnHospitalizaciones->Click += gcnew System::EventHandler(this, &FormInsertar::Hospitalizaciones_Click);
			btnCitas->Click += gcnew System::EventHandler(this, &FormInsertar::Citas_Click);

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

		System::Void Pacientes_Click(System::Object^ sender, System::EventArgs^ e) {
			FormInsertarPaciente^ ventanaPaciente = gcnew FormInsertarPaciente(arbolilloPaises, arbolilloCiudades, arbolilloPac);
			ventanaPaciente->ShowDialog();
		}

		System::Void Medicos_Click(System::Object^ sender, System::EventArgs^ e) {
			FormInsertarMedico^ ventanaMedico = gcnew FormInsertarMedico(arbolilloEsp, arbolilloMed);
			ventanaMedico->ShowDialog();
		}

		System::Void Habitaciones_Click(System::Object^ sender, System::EventArgs^ e) {
			FormInsertarHabitacion^ ventanaHabitacion = gcnew FormInsertarHabitacion(arbolilloHab);
			ventanaHabitacion->ShowDialog();
		}

		System::Void Hospitalizaciones_Click(System::Object^ sender, System::EventArgs^ e) {
			FormInsertarHospitalizacion^ ventanaHosp = gcnew FormInsertarHospitalizacion(arbolilloPac, arbolilloHab, arbolilloMed, arbolilloHosp);
			ventanaHosp->ShowDialog();
		}

		System::Void Citas_Click(System::Object^ sender, System::EventArgs^ e) {
			FormInsertarCita^ ventanaCita = gcnew FormInsertarCita(arbolilloPac, arbolilloMed, arbolilloEsp, arbolilloCitas);
			ventanaCita->ShowDialog();
		}
	};
}