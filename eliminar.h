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
	public ref class FormEliminarPais : public System::Windows::Forms::Form {
	private:
		TextBox^ txtCodPais;
		ArbolPais* arbolPaises;
		Consola^ consolaPais;
		ArbolCiudad* arbolCiudades;
		ArbolPacientes* arbolPac;
		ArbolCitas* arbolCita;
		ArbolHospitalizaciones* arbolHosp;

	public:
		FormEliminarPais(ArbolPais* arbol, ArbolCiudad* ciudades, ArbolPacientes* pacientes, ArbolCitas* citas, ArbolHospitalizaciones* hosp, Consola^ consola) {
			arbolPaises = arbol;
			arbolCiudades = ciudades;
			arbolPac = pacientes;
			arbolCita = citas;
			arbolHosp = hosp;
			consolaPais = consola;

			this->Text = L"Eliminar Pais";
			this->Size = System::Drawing::Size(300, 200);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// cosas y cajita para input de codpais
			Label^ lblCod = gcnew Label();
			lblCod->Text = L"Codigo de pais a Eliminar: ";
			lblCod->Location = System::Drawing::Point(30, 30);
			lblCod->AutoSize = true;
			txtCodPais = gcnew TextBox();
			txtCodPais->Location = System::Drawing::Point(30, 50);

			// salri
			Button^ btnEliminar = gcnew Button();
			btnEliminar->Text = L"Eliminar";
			btnEliminar->Location = System::Drawing::Point(90, 100);
			btnEliminar->Click += gcnew System::EventHandler(this, &FormEliminarPais::Eliminar_Click); // chunche evento

			this->Controls->Add(lblCod);
			this->Controls->Add(txtCodPais);
			this->Controls->Add(btnEliminar);
		}

	private:
		System::Void Eliminar_Click(System::Object^ sender, System::EventArgs^ e) {
			// manda error x si vacios
			if (txtCodPais->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			// convierte lo de input de ventana a str
			string codPaisstr = msclr::interop::marshal_as<string>(txtCodPais->Text);
			int codPaisint = stoi(codPaisstr);
			/*
			CapturaSalida cap;
			arbolPaises->EliminarPais(codPaisint);
			String^ mensajeConsola = aNet(cap.Terminar());
			consolaPais->Escribir(mensajeConsola);

			bool eliminado = arbolPaises->EliminaNodo(codPaisint);
			if (eliminado == true) {
				MessageBox::Show(L"Pais eliminado con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				MessageBox::Show(L"No se encontro ningun pais con el codigo " + codPaisint, L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			*/



			// lo q tenia aca arriba fallaba pq estaba se estaban haciendo 2 borrados, en arbolPaises->EliminarPais(codPaisint); y luego en bool eliminado = arbolPaises->EliminaNodo(codPaisint);
			// eso estaba haciendo q si se borrara de verdad, si se mostrara en consola el mensaje de borrado como deberia ser, PERO la ventana dijera "codigo no existe"
			// por culpa, justamente, de esos 2 borrados. Aca abajo hice q usara buscarvalor para saber si mandar el msg de "codigo no existe" o "eliminado exitosamente"
			// eso quita el problema ese

			bool existe = (arbolPaises->Buscarvalor(codPaisint) != nullptr); // esto es para lo de mostrar mensaje de eliminado O de codpais no existe
			
			CapturaSalida cap;
			if (existe == true) {
				arbolCiudades->EliminarCiudadesDePais(codPaisint, *arbolPac, *arbolCita, *arbolHosp);// quita ciudades
			}
			arbolPaises->EliminarPais(codPaisint, *arbolCiudades, *arbolPac, *arbolCita, *arbolHosp); // dsps pais
			String^ mensajeConsola = aNet(cap.Terminar());
			consolaPais->Escribir(mensajeConsola);
			

			if (existe == true) {
				MessageBox::Show(L"Pais eliminado con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				MessageBox::Show(L"No se encontro ningun pais con el codigo " + codPaisint, L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}

		}
	};
	

// CIUDAD -------------------------------------------------------------------------------
	public ref class FormEliminarCiudad : public System::Windows::Forms::Form {
	private:
		TextBox^ txtCodPais;
		TextBox^ txtCodCiudad;
		ArbolPais* arbolPaises;
		ArbolCiudad* arbolCiudades;
		Consola^ consolaCiudad;

		ArbolHospitalizaciones* arbolHosp;
		ArbolPacientes* arbolPac;
		ArbolCitas* arbolCita;

	public:
		FormEliminarCiudad(ArbolPais* arbolP, ArbolCiudad* arbolC, ArbolPacientes* arbolPaci, ArbolCitas* arbolCi, ArbolHospitalizaciones* arbolHo, Consola^ consola) {
			arbolPaises = arbolP;
			arbolCiudades = arbolC;
			consolaCiudad = consola;
			arbolHosp = arbolHo;
			arbolPac = arbolPaci;
			arbolCita = arbolCi;

			this->Text = L"Eliminar Ciudad";
			this->Size = System::Drawing::Size(300, 260);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// codp
			Label^ lblCodPais = gcnew Label();
			lblCodPais->Text = L"Codigo de Pais:";
			lblCodPais->Location = System::Drawing::Point(30, 30);
			lblCodPais->AutoSize = true;
			txtCodPais = gcnew TextBox();
			txtCodPais->Location = System::Drawing::Point(30, 50);

			//codc
			Label^ lblCodCiudad = gcnew Label();
			lblCodCiudad->Text = L"Codigo de Ciudad a Eliminar:";
			lblCodCiudad->Location = System::Drawing::Point(30, 90);
			lblCodCiudad->AutoSize = true;
			txtCodCiudad = gcnew TextBox();
			txtCodCiudad->Location = System::Drawing::Point(30, 110);

			Button^ btnEliminar = gcnew Button();
			btnEliminar->Text = L"Eliminar";
			btnEliminar->Location = System::Drawing::Point(90, 160);
			btnEliminar->Click += gcnew System::EventHandler(this, &FormEliminarCiudad::Eliminar_Click);

			this->Controls->Add(lblCodPais);
			this->Controls->Add(txtCodPais);
			this->Controls->Add(lblCodCiudad);
			this->Controls->Add(txtCodCiudad);
			this->Controls->Add(btnEliminar);
		}

	private:
		System::Void Eliminar_Click(System::Object^ sender, System::EventArgs^ e) {
			if (txtCodPais->Text == "" or txtCodCiudad->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string codPaisstr = msclr::interop::marshal_as<string>(txtCodPais->Text);
			string codCiudadstr = msclr::interop::marshal_as<string>(txtCodCiudad->Text);
			int codPaisint = stoi(codPaisstr);
			int codCiudadint = stoi(codCiudadstr);

			// pais hay
			if (arbolPaises->Buscarvalor(codPaisint) == nullptr) {
				MessageBox::Show(L"No existe ningun pais con el codigo " + codPaisint, L"Pais no encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			bool existe = (arbolCiudades->Buscarvalor(codPaisint, codCiudadint) != nullptr);

			CapturaSalida cap;
			arbolCiudades->EliminarCiudad(codPaisint, codCiudadint, *arbolPaises, *arbolPac, *arbolCita, *arbolHosp);
			String^ mensajeConsola = aNet(cap.Terminar());
			consolaCiudad->Escribir(mensajeConsola);

			if (existe == true) {
				MessageBox::Show(L"Ciudad eliminada con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				MessageBox::Show(L"No se encontro ninguna ciudad con el codigo " + codCiudadint + L" en el pais " + codPaisint, L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}

			/*
			if (eliminado == true) {
				MessageBox::Show(L"Ciudad eliminada con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				MessageBox::Show(L"No se encontro ninguna ciudad con el codigo " + codCiudadint + L" en el pais " + codPaisint, L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			*/
		}
	};

// ESPECIALIDADES -------------------------------------------------------------------------------------------
	public ref class FormEliminarEspecialidad : public System::Windows::Forms::Form {
	private:
		TextBox^ txtCodEsp;
		ArbolEspecialidad* arbolEsp;
		Consola^ consolaEsp;
		ArbolMedicos* arbolMed;
		ArbolCitas* arbolCita;

	public:
		FormEliminarEspecialidad(ArbolEspecialidad* arbol, ArbolMedicos* medicos, ArbolCitas* citas, Consola^ consola) {
			arbolEsp = arbol;
			consolaEsp = consola;
			arbolMed = medicos;
			arbolCita = citas;

			this->Text = L"Eliminar Especialidad";
			this->Size = System::Drawing::Size(300, 200);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			Label^ lblCod = gcnew Label();
			lblCod->Text = L"Codigo de Especialidad a Eliminar: ";
			lblCod->Location = System::Drawing::Point(30, 30);
			lblCod->AutoSize = true;

			txtCodEsp = gcnew TextBox();
			txtCodEsp->Location = System::Drawing::Point(30, 50);

			Button^ btnEliminar = gcnew Button();
			btnEliminar->Text = L"Eliminar";
			btnEliminar->Location = System::Drawing::Point(90, 100);
			btnEliminar->Click += gcnew System::EventHandler(this, &FormEliminarEspecialidad::Eliminar_Click);

			this->Controls->Add(lblCod);
			this->Controls->Add(txtCodEsp);
			this->Controls->Add(btnEliminar);
		}

	private:
		System::Void Eliminar_Click(System::Object^ sender, System::EventArgs^ e) {
			if (txtCodEsp->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string idespstr = msclr::interop::marshal_as<string>(txtCodEsp->Text);
			int idespint = stoi(idespstr);

			bool existe = (arbolEsp->Buscarvalor(idespint) != nullptr);

			CapturaSalida cap;
			arbolEsp->EliminarEspecialidad(idespint, *arbolMed, *arbolCita);
			String^ mensajeConsola = aNet(cap.Terminar());
			consolaEsp->Escribir(mensajeConsola);

			if (existe == true) {
				MessageBox::Show(L"Especialidad eliminada con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				MessageBox::Show(L"No se encontro ninguna especialidad con el codigo " + idespint, L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};

// DIAGNOSTICO -------------------------------------------------------------------------------------------
	public ref class FormEliminarDiagnostico : public System::Windows::Forms::Form {
	private:
		TextBox^ txtCodDiag;
		ArbolDiagnostico* arbolDiag;
		Consola^ consolaDiag;

	public:
		FormEliminarDiagnostico(ArbolDiagnostico* arbol, Consola^ consola) {
			arbolDiag = arbol;
			consolaDiag = consola;

			this->Text = L"Eliminar Diagnostico";
			this->Size = System::Drawing::Size(300, 200);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			Label^ lblCod = gcnew Label();
			lblCod->Text = L"Codigo de Diagnostico a Eliminar: ";
			lblCod->Location = System::Drawing::Point(30, 30);
			lblCod->AutoSize = true;

			txtCodDiag = gcnew TextBox();
			txtCodDiag->Location = System::Drawing::Point(30, 50);

			Button^ btnEliminar = gcnew Button();
			btnEliminar->Text = L"Eliminar";
			btnEliminar->Location = System::Drawing::Point(90, 100);
			btnEliminar->Click += gcnew System::EventHandler(this, &FormEliminarDiagnostico::Eliminar_Click);

			this->Controls->Add(lblCod);
			this->Controls->Add(txtCodDiag);
			this->Controls->Add(btnEliminar);
		}

	private:
		System::Void Eliminar_Click(System::Object^ sender, System::EventArgs^ e) {
			if (txtCodDiag->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string idDiagstr = msclr::interop::marshal_as<string>(txtCodDiag->Text);
			//int idDiagint = stoi(idDiagstr);

			bool existe = (arbolDiag->Buscarvalor(idDiagstr) != nullptr);

			CapturaSalida cap;
			arbolDiag->EliminarDiagnostico(idDiagstr);
			String^ mensajeConsola = aNet(cap.Terminar());
			consolaDiag->Escribir(mensajeConsola);

			if (existe == true) {
				MessageBox::Show(L"Diagnostico eliminado con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				MessageBox::Show(L"No se encontro ningun diagnostico con el codigo " + txtCodDiag->Text, L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
				//^ si lo dejaba en idDIagstr en lugar de txtCodDiag->Text me salia el error de no acceptable conversion
				// pq si se puede manejar los txtos de cli q empiezan con L y ints, pero no con strings
			}
		}
	};

// Hospitalizacion -------------------------------------------------------------------------------------------
	public ref class FormEliminarHospitalizacion : public System::Windows::Forms::Form {
	private:
		TextBox^ txtCodHosp;
		TextBox^ txtCodPac;
		TextBox^ txtCodHab;
		ArbolHospitalizaciones* arbolHosp;
		ArbolPacientes* arbolPac;
		ArbolHabitaciones* arbolHab;
		Consola^ consolaHosp;

	public:
		FormEliminarHospitalizacion(ArbolHospitalizaciones* arbol, ArbolPacientes* pacientes, ArbolHabitaciones* habitaciones, Consola^ consola) {
			arbolHosp = arbol;
			arbolPac = pacientes;
			arbolHab = habitaciones;
			consolaHosp = consola;

			this->Text = L"Eliminar Hospitalizacion";
			this->Size = System::Drawing::Size(300, 320);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// idhosp
			Label^ lblCodHosp = gcnew Label();
			lblCodHosp->Text = L"Codigo de Hospitalizacion a Eliminar: ";
			lblCodHosp->Location = System::Drawing::Point(30, 20);
			lblCodHosp->AutoSize = true;
			txtCodHosp = gcnew TextBox();
			txtCodHosp->Location = System::Drawing::Point(30, 40);
			
			// idpac
			Label^ lblCodPac = gcnew Label();
			lblCodPac->Text = L"Codigo de Paciente:";
			lblCodPac->Location = System::Drawing::Point(30, 80);
			lblCodPac->AutoSize = true;
			txtCodPac = gcnew TextBox();
			txtCodPac->Location = System::Drawing::Point(30, 100);

			// idhab
			Label^ lblCodHab = gcnew Label();
			lblCodHab->Text = L"Codigo de Habitacion:";
			lblCodHab->Location = System::Drawing::Point(30, 140);
			lblCodHab->AutoSize = true;
			txtCodHab = gcnew TextBox();
			txtCodHab->Location = System::Drawing::Point(30, 160);

			/*
			txtCodHosp = gcnew TextBox();
			txtCodHosp->Location = System::Drawing::Point(30, 50);
			*/

			Button^ btnEliminar = gcnew Button();
			btnEliminar->Text = L"Eliminar";
			btnEliminar->Location = System::Drawing::Point(90, 210);
			btnEliminar->Click += gcnew System::EventHandler(this, &FormEliminarHospitalizacion::Eliminar_Click);

			this->Controls->Add(lblCodHosp);
			this->Controls->Add(txtCodHosp);
			this->Controls->Add(lblCodPac);
			this->Controls->Add(txtCodPac);
			this->Controls->Add(lblCodHab);
			this->Controls->Add(txtCodHab);
			this->Controls->Add(btnEliminar);
		}

	private:
		System::Void Eliminar_Click(System::Object^ sender, System::EventArgs^ e) {
			if (txtCodHosp->Text == "" or txtCodPac->Text == "" or txtCodHab->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string idHospstr = msclr::interop::marshal_as<string>(txtCodHosp->Text);
			string idPacstr = msclr::interop::marshal_as<string>(txtCodPac->Text);
			string idHabstr = msclr::interop::marshal_as<string>(txtCodHab->Text);
			int idHospint = stoi(idHospstr);
			int idPacint = stoi(idPacstr);
			int idHabint = stoi(idHabstr);

			//bool existe = (arbolHosp->Buscarvalor(idHospint) != nullptr);
			bool PizzaHut = false;
			pHosp NovilloAlegre = arbolHosp->Buscarvalor(idHospint);
			if (NovilloAlegre != nullptr and NovilloAlegre->idPaciente == idPacint and NovilloAlegre->idHabitacion == idHabint) {
				PizzaHut = true;
			}

			CapturaSalida cap;
			arbolHosp->EliminarHospitalizacion(idPacint, idHabint, idHospint, *arbolPac, *arbolHab); // ocupa ref a los arboles para lo de verificar idpac y idhab
			String^ mensajeConsola = aNet(cap.Terminar());
			consolaHosp->Escribir(mensajeConsola);

			if (PizzaHut == true) {
				MessageBox::Show(L"Hospitalizacion eliminada con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				MessageBox::Show(mensajeConsola, L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
				// ^ aca puse como mensaje "mensajeConsola", pq hay un monton de mensajes que podrian terminar saliendo aca (mal pac, mal hab, mal hosp...)
				// entonces mas facil solo puse q saque lo mismo q iba a mostrarse en la consola

			}
		}
	};

// TRATAMIENTO -------------------------------------------------------------------------------------------
	public ref class FormEliminarTratamiento : public System::Windows::Forms::Form {
	private:
		TextBox^ txtIdTratamiento;
		ArbolTratamiento* arbolTrata;
		Consola^ consolaTrata;

	public:
		FormEliminarTratamiento(ArbolTratamiento* arbol, Consola^ consola) {
			arbolTrata = arbol;
			consolaTrata = consola;

			this->Text = L"Eliminar Tratamiento";
			this->Size = System::Drawing::Size(300, 200);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// idtrata
			Label^ lblCod = gcnew Label();
			lblCod->Text = L"Codigo de Tratamiento a Eliminar: ";
			lblCod->Location = System::Drawing::Point(30, 30);
			lblCod->AutoSize = true;

			txtIdTratamiento = gcnew TextBox();
			txtIdTratamiento->Location = System::Drawing::Point(30, 50);

			Button^ btnEliminar = gcnew Button();
			btnEliminar->Text = L"Eliminar";
			btnEliminar->Location = System::Drawing::Point(90, 100);
			btnEliminar->Click += gcnew System::EventHandler(this, &FormEliminarTratamiento::Eliminar_Click);

			this->Controls->Add(lblCod);
			this->Controls->Add(txtIdTratamiento);
			this->Controls->Add(btnEliminar);
		}

	private:
		System::Void Eliminar_Click(System::Object^ sender, System::EventArgs^ e) {
			if (txtIdTratamiento->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string idTratastr = msclr::interop::marshal_as<string>(txtIdTratamiento->Text);
			//string idPacstr = msclr::interop::marshal_as<string>(txtCodPac->Text);
			//string idHabstr = msclr::interop::marshal_as<string>(txtCodHab->Text);
			int idTrataint = stoi(idTratastr);
			//int idPacint = stoi(idPacstr);
			//int idHabint = stoi(idHabstr);

			/*
			//bool existe = (arbolHosp->Buscarvalor(idHospint) != nullptr);
			bool PizzaHut = false;
			pHosp NovilloAlegre = arbolHosp->Buscarvalor(idHospint);
			if (NovilloAlegre != nullptr and NovilloAlegre->idPaciente == idPacint and NovilloAlegre->idHabitacion == idHabint) {
				PizzaHut = true;
			}
			*/
			bool existe = (arbolTrata->Buscarvalor(idTrataint) != nullptr);

			CapturaSalida cap;
			arbolTrata->EliminarTratamiento(idTrataint);
			String^ mensajeConsola = aNet(cap.Terminar());
			consolaTrata->Escribir(mensajeConsola);
			/*
			if (PizzaHut == true) {
				MessageBox::Show(L"Hospitalizacion eliminada con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				MessageBox::Show(mensajeConsola, L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
				// ^ aca puse como mensaje "mensajeConsola", pq hay un monton de mensajes que podrian terminar saliendo aca (mal pac, mal hab, mal hosp...)
				// entonces mas facil solo puse q saque lo mismo q iba a mostrarse en la consola

			}
			*/

			if (existe == true) {
				MessageBox::Show(L"Tratamiento eliminado con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				MessageBox::Show(mensajeConsola, L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
				// ^ en realidad ya no ocuparia lo de mensajeConsola, pq solo hay 1 salida posible (q no encuentra idTrata)
				// pero en realidad lo dejo asi pq es mucho mas sencillo, lastima q no se me ocurrio al principio de las elim -_-

			}


		}
	};








// CITAS (AVL) -----------------------------------------------------------------------------------------------------------------------
	public ref class FormEliminarCita : public System::Windows::Forms::Form {
	private:
		TextBox^ txtIdPac;
		TextBox^ txtIdMed;
		TextBox^ txtIdCita;
		ArbolPacientes* arbolPac;
		ArbolMedicos* arbolMed;
		ArbolCitas* arbolCita;
		Consola^ consolaCita;

	public:
		FormEliminarCita(ArbolPacientes* pacientes, ArbolMedicos* medicos, ArbolCitas* citas, Consola^ consola) {
			arbolPac = pacientes;
			arbolMed = medicos;
			arbolCita = citas;
			consolaCita = consola;

			this->Text = L"Eliminar Cita";
			this->Size = System::Drawing::Size(320, 290);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			Label^ lblPac = gcnew Label();
			lblPac->Text = L"Id del Paciente: ";
			lblPac->Location = System::Drawing::Point(30, 20);
			lblPac->AutoSize = true;
			txtIdPac = gcnew TextBox();
			txtIdPac->Location = System::Drawing::Point(30, 40);

			Label^ lblMed = gcnew Label();
			lblMed->Text = L"Id del Medico: ";
			lblMed->Location = System::Drawing::Point(30, 75);
			lblMed->AutoSize = true;
			txtIdMed = gcnew TextBox();
			txtIdMed->Location = System::Drawing::Point(30, 95);

			Label^ lblCita = gcnew Label();
			lblCita->Text = L"Id de la Cita a Eliminar: ";
			lblCita->Location = System::Drawing::Point(30, 130);
			lblCita->AutoSize = true;
			txtIdCita = gcnew TextBox();
			txtIdCita->Location = System::Drawing::Point(30, 150);

			Button^ btnEliminar = gcnew Button();
			btnEliminar->Text = L"Eliminar";
			btnEliminar->Location = System::Drawing::Point(100, 195);
			btnEliminar->Click += gcnew System::EventHandler(this, &FormEliminarCita::Eliminar_Click);

			this->Controls->Add(lblPac);
			this->Controls->Add(txtIdPac);
			this->Controls->Add(lblMed);
			this->Controls->Add(txtIdMed);
			this->Controls->Add(lblCita);
			this->Controls->Add(txtIdCita);
			this->Controls->Add(btnEliminar);
		}

	private:
		System::Void Eliminar_Click(System::Object^ sender, System::EventArgs^ e) {
			int idp, idm, idc;
			// TryParse devuelve false si no es un numero
			if (!Int32::TryParse(txtIdPac->Text, idp) || !Int32::TryParse(txtIdMed->Text, idm) || !Int32::TryParse(txtIdCita->Text, idc)) {
				MessageBox::Show(L"Por favor llene todos los campos con numeros.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			bool existiaAntes = (arbolCita->Buscarvalor(idc) != nullptr);

			CapturaSalida cap;
			arbolCita->EliminarCita(idp, idm, idc, *arbolPac, *arbolMed);
			String^ mensajeConsola = aNet(cap.Terminar());
			consolaCita->Escribir(mensajeConsola);

			bool existeDespues = (arbolCita->Buscarvalor(idc) != nullptr);

			if (existiaAntes == true && existeDespues == false) {
				MessageBox::Show(L"Cita eliminada con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				// el mensaje q dio el CRUD dice por que no se pudo (no existe, no hace juego)
				MessageBox::Show(mensajeConsola, L"No se pudo eliminar", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};

//HABITACIONES (AVL) -------------------------------------------------------------------------------------------------------------
	public ref class FormEliminarHabitacion : public System::Windows::Forms::Form {
	private:
		TextBox^ txtIdHab;
		ArbolHabitaciones* arbolHab;
		ArbolHospitalizaciones* arbolHosp; //cascada
		Consola^ consolaHab;

	public:
		FormEliminarHabitacion(ArbolHabitaciones* habitaciones, ArbolHospitalizaciones* hosp, Consola^ consola) {
			arbolHab = habitaciones;
			arbolHosp = hosp;
			consolaHab = consola;

			this->Text = L"Eliminar Habitacion";
			this->Size = System::Drawing::Size(300, 200);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			Label^ lblCod = gcnew Label();
			lblCod->Text = L"Id de Habitacion a Eliminar: ";
			lblCod->Location = System::Drawing::Point(30, 30);
			lblCod->AutoSize = true;

			txtIdHab = gcnew TextBox();
			txtIdHab->Location = System::Drawing::Point(30, 50);

			Button^ btnEliminar = gcnew Button();
			btnEliminar->Text = L"Eliminar";
			btnEliminar->Location = System::Drawing::Point(90, 100);
			btnEliminar->Click += gcnew System::EventHandler(this, &FormEliminarHabitacion::Eliminar_Click);

			this->Controls->Add(lblCod);
			this->Controls->Add(txtIdHab);
			this->Controls->Add(btnEliminar);
		}

	private:
		System::Void Eliminar_Click(System::Object^ sender, System::EventArgs^ e) {
			int idh;
			if (!Int32::TryParse(txtIdHab->Text, idh)) {
				MessageBox::Show(L"Por favor escriba un id valido (numero).", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			bool existe = (arbolHab->Buscarvalor(idh) != nullptr);

			CapturaSalida cap;
			if (existe == true) {
				//arbolHosp->EliminarHospDeHabitacion(idh); //cascadaprimero sus hospitalizaciones
			}
			arbolHab->EliminarHab(idh, *arbolHosp);
			String^ mensajeConsola = aNet(cap.Terminar());
			consolaHab->Escribir(mensajeConsola);

			if (existe == true) {
				MessageBox::Show(L"Habitacion eliminada con exito.", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				MessageBox::Show(L"No se encontro ninguna habitacion con el id " + idh.ToString(), L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};

//PACIENTES -------------------------------------------------------------------------------------------------------------------
	public ref class FormEliminarPaciente : public System::Windows::Forms::Form {
	private:
		TextBox^ txtIdPac;
		ArbolPacientes* arbolPac;
		ArbolCitas* arbolCita;
		ArbolHospitalizaciones* arbolHosp;
		Consola^ consolaPac;

	public:
		FormEliminarPaciente(ArbolPacientes* pacientes, ArbolCitas* citas, ArbolHospitalizaciones* hosp, Consola^ consola) {
			arbolPac = pacientes;
			arbolCita = citas;
			arbolHosp = hosp;
			consolaPac = consola;

			this->Text = L"Eliminar Paciente";
			this->Size = System::Drawing::Size(300, 200);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			Label^ lblId = gcnew Label();
			lblId->Text = L"Id del Paciente a Eliminar: ";
			lblId->Location = System::Drawing::Point(30, 30);
			lblId->AutoSize = true;

			txtIdPac = gcnew TextBox();
			txtIdPac->Location = System::Drawing::Point(30, 50);

			Button^ btnEliminar = gcnew Button();
			btnEliminar->Text = L"Eliminar";
			btnEliminar->Location = System::Drawing::Point(90, 100);
			btnEliminar->Click += gcnew System::EventHandler(this, &FormEliminarPaciente::Eliminar_Click);

			this->Controls->Add(lblId);
			this->Controls->Add(txtIdPac);
			this->Controls->Add(btnEliminar);
		}

	private:
		System::Void Eliminar_Click(System::Object^ sender, System::EventArgs^ e) {
			int idp;
			if (!Int32::TryParse(txtIdPac->Text, idp)) {
				MessageBox::Show(L"Por favor escriba un id valido (numero).", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			if (arbolPac->Buscarvalor(idp) == nullptr) {
				MessageBox::Show(L"No se encontro ningun paciente con el id " + idp.ToString(), L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			//se avisa de la cascada antes de borrar
			System::Windows::Forms::DialogResult resp = MessageBox::Show(L"Se eliminara el paciente " + idp.ToString() + L" junto con TODAS sus citas y hospitalizaciones.\nDesea continuar?", L"Confirmar", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
			if (resp != System::Windows::Forms::DialogResult::Yes) {
				return;
			}

			CapturaSalida cap;
			arbolPac->EliminarPaciente(idp, *arbolCita, *arbolHosp);
			String^ mensajeConsola = aNet(cap.Terminar());
			consolaPac->Escribir(mensajeConsola);

			MessageBox::Show(L"Paciente eliminado con exito", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
			this->Close();
		}
	};

//MEDICOS ---------------------------------------------------------------------------------------------------------------------------
	public ref class FormEliminarMedico : public System::Windows::Forms::Form {
	private:
		TextBox^ txtIdMed;
		ArbolMedicos* arbolMed;
		ArbolCitas* arbolCita;
		Consola^ consolaMed;

	public:
		FormEliminarMedico(ArbolMedicos* medicos, ArbolCitas* citas, Consola^ consola) {
			arbolMed = medicos;
			arbolCita = citas;
			consolaMed = consola;

			this->Text = L"Eliminar Medico";
			this->Size = System::Drawing::Size(300, 200);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			Label^ lblId = gcnew Label();
			lblId->Text = L"Id del Medico a Eliminar: ";
			lblId->Location = System::Drawing::Point(30, 30);
			lblId->AutoSize = true;

			txtIdMed = gcnew TextBox();
			txtIdMed->Location = System::Drawing::Point(30, 50);

			Button^ btnEliminar = gcnew Button();
			btnEliminar->Text = L"Eliminar";
			btnEliminar->Location = System::Drawing::Point(90, 100);
			btnEliminar->Click += gcnew System::EventHandler(this, &FormEliminarMedico::Eliminar_Click);

			this->Controls->Add(lblId);
			this->Controls->Add(txtIdMed);
			this->Controls->Add(btnEliminar);
		}

	private:
		System::Void Eliminar_Click(System::Object^ sender, System::EventArgs^ e) {
			int idm;
			if (!Int32::TryParse(txtIdMed->Text, idm)) {
				MessageBox::Show(L"Por favor escriba un id valido (numero).", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			if (arbolMed->Buscarvalor(idm) == nullptr) {
				MessageBox::Show(L"No se encontro ningun medico con el id " + idm.ToString(), L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			System::Windows::Forms::DialogResult resp = MessageBox::Show(L"Se eliminara el medico " + idm.ToString() + L" junto con TODAS sus citas.\nDesea continuar?", L"Confirmar", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
			if (resp != System::Windows::Forms::DialogResult::Yes) {
				return;
			}

			CapturaSalida cap;
			arbolMed->EliminarMedico(idm, *arbolCita);
			String^ mensajeConsola = aNet(cap.Terminar());
			consolaMed->Escribir(mensajeConsola);

			MessageBox::Show(L"Medico eliminado con exito", L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
			this->Close();
		}
	};
/*
	// ventana con los botones ----------------------------------------------------------------------------------------
	public ref class FormEliminar : public System::Windows::Forms::Form
		// ventana Eliminar
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
		FormEliminar(ArbolPais* arbolP, ArbolCiudad* arbolC, ArbolEspecialidad* arbolE, ArbolCitas* arbolCi, ArbolHabitaciones* arbolHa, ArbolHospitalizaciones* arbolHo, ArbolMedicos* arbolM, ArbolPacientes* arbolPac, ArbolTratamiento* arbolT, ArbolDiagnostico* arbolD) {
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

			this->Text = L"Eliminar Registro";
			this->Size = System::Drawing::Size(400, 400);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false; // maximaze quita la opcion de darle a pantalla completa

			// col1
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

			// col2
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

			btnPaises->Click += gcnew System::EventHandler(this, &FormEliminar::Paises_Click);
			btnCiudades->Click += gcnew System::EventHandler(this, &FormEliminar::Ciudades_Click);
			btnEspecialidades->Click += gcnew System::EventHandler(this, &FormEliminar::Especialidades_Click);
			btnTratamientos->Click += gcnew System::EventHandler(this, &FormEliminar::Tratamientos_Click);
			btnDiagnosticos->Click += gcnew System::EventHandler(this, &FormEliminar::Diagnosticos_Click);
			btnPacientes->Click += gcnew System::EventHandler(this, &FormEliminar::Pacientes_Click);
			btnMedicos->Click += gcnew System::EventHandler(this, &FormEliminar::Medicos_Click);
			btnHabitaciones->Click += gcnew System::EventHandler(this, &FormEliminar::Habitaciones_Click);
			btnHospitalizaciones->Click += gcnew System::EventHandler(this, &FormEliminar::Hospitalizaciones_Click);
			btnCitas->Click += gcnew System::EventHandler(this, &FormEliminar::Citas_Click);

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

	private:
		// chunches click
		Void Paises_Click(Object^ sender, EventArgs^ e) {
			FormEliminarPais^ ventanaPais = gcnew FormEliminarPais(arbolilloPaises);
			ventanaPais->ShowDialog();
		}

		System::Void Ciudades_Click(System::Object^ sender, System::EventArgs^ e) {
			FormEliminarCiudad^ ventanaCiudad = gcnew FormEliminarCiudad(arbolilloPaises, arbolilloCiudades);
			ventanaCiudad->ShowDialog();
		}
		
		System::Void Especialidades_Click(System::Object^ sender, System::EventArgs^ e) {
			FormEliminarEspecialidad^ ventanaEspecialidad = gcnew FormEliminarEspecialidad(arbolilloEsp);
			ventanaEspecialidad->ShowDialog();
		}

		System::Void Tratamientos_Click(System::Object^ sender, System::EventArgs^ e) {
			FormEliminarTratamiento^ ventanaTratamiento = gcnew FormEliminarTratamiento(arbolilloTrata);
			ventanaTratamiento->ShowDialog();
		}

		System::Void Diagnosticos_Click(System::Object^ sender, System::EventArgs^ e) {
			FormEliminarDiagnostico^ ventanaDiagnostico = gcnew FormEliminarDiagnostico(arbolilloDiag);
			ventanaDiagnostico->ShowDialog();
		}

		System::Void Pacientes_Click(System::Object^ sender, System::EventArgs^ e) {
			FormEliminarPaciente^ ventanaPaciente = gcnew FormEliminarPaciente(arbolilloPaises, arbolilloCiudades, arbolilloPac);
			ventanaPaciente->ShowDialog();
		}

		System::Void Medicos_Click(System::Object^ sender, System::EventArgs^ e) {
			FormEliminarMedico^ ventanaMedico = gcnew FormEliminarMedico(arbolilloEsp, arbolilloMed);
			ventanaMedico->ShowDialog();
		}

		System::Void Habitaciones_Click(System::Object^ sender, System::EventArgs^ e) {
			FormEliminarHabitacion^ ventanaHabitacion = gcnew FormEliminarHabitacion(arbolilloHab);
			ventanaHabitacion->ShowDialog();
		}

		System::Void Hospitalizaciones_Click(System::Object^ sender, System::EventArgs^ e) {
			FormEliminarHospitalizacion^ ventanaHosp = gcnew FormEliminarHospitalizacion(arbolilloPac, arbolilloHab, arbolilloMed, arbolilloHosp);
			ventanaHosp->ShowDialog();
		}

		System::Void Citas_Click(System::Object^ sender, System::EventArgs^ e) {
			FormEliminarCita^ ventanaCita = gcnew FormEliminarCita(arbolilloPac, arbolilloMed, arbolilloEsp, arbolilloCitas);
			ventanaCita->ShowDialog();
		}
	};
	*/
}
