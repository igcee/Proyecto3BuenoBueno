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
	public ref class FormBuscarPais : public System::Windows::Forms::Form {
	private:
		TextBox^ txtCodPais;
		TextBox^ txtNombre; // Busqueda input de la ventana
		ArbolPais* arbolPaises;

	public:
		FormBuscarPais(ArbolPais* arbol) {
			arbolPaises = arbol;

			this->Text = L"Buscar Pais";
			this->Size = System::Drawing::Size(300, 200);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// cosas y cajita para input de codpais
			Label^ lblCod = gcnew Label();
			lblCod->Text = L"Codigo de pais a buscar: ";
			lblCod->Location = System::Drawing::Point(30, 30);
			lblCod->AutoSize = true;
			txtCodPais = gcnew TextBox();
			txtCodPais->Location = System::Drawing::Point(30, 50);

			// salri
			Button^ btnBusqueda = gcnew Button();
			btnBusqueda->Text = L"Busqueda";
			btnBusqueda->Location = System::Drawing::Point(90, 100);
			btnBusqueda->Click += gcnew System::EventHandler(this, &FormBuscarPais::Busqueda_Click); // chunche evento

			this->Controls->Add(lblCod);
			this->Controls->Add(txtCodPais);
			this->Controls->Add(btnBusqueda);
		}

	private:
		System::Void Busqueda_Click(System::Object^ sender, System::EventArgs^ e) {
			// manda error x si vacios
			if (txtCodPais->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			// convierte lo de input de ventana a str
			string codPaisstr = msclr::interop::marshal_as<string>(txtCodPais->Text);
			int codPaisint = stoi(codPaisstr);

			pPais nodo = arbolPaises->Buscarvalor(codPaisint);

			if (nodo != nullptr) { // buscarvalor manda nullptr si no encuentra, osea si != nullptr entonces se encontro
				String^ nombrePais = gcnew String(nodo->nombre.c_str()); // al reves de lo de marshal, pasa de string normal a string del chunche del winforms
				String^ resultado = L"--- Pais Encontrado ---\n\n" + L"Codigo: " + nodo->codPais + L"\n" + L"Nombre: " + nombrePais;
				// ^ lo puse como un string con los saltos de linea para q sea mas facilillo de manejar aca abajo

				MessageBox::Show(resultado, L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();// muestra datos y cierra ventana
			}
			else {
				// no esta
				MessageBox::Show(L"No se encontro ningun pais con el codigo " + codPaisint, L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};

	// CIUDAD -------------------------------------------------------------------------------------------------------------
	public ref class FormBuscarCiudad : public System::Windows::Forms::Form {
	private:
		TextBox^ txtCodPais;
		TextBox^ txtCodCiudad;
		ArbolPais* arbolPaises;
		ArbolCiudad* arbolCiudades;

	public:
		FormBuscarCiudad(ArbolPais* arbolP, ArbolCiudad* arbolC) {
			arbolPaises = arbolP;
			arbolCiudades = arbolC;

			this->Text = L"Buscar Ciudad";
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

			// codc
			Label^ lblCodCiudad = gcnew Label();
			lblCodCiudad->Text = L"Codigo de Ciudad:";
			lblCodCiudad->Location = System::Drawing::Point(30, 90);
			lblCodCiudad->AutoSize = true;
			txtCodCiudad = gcnew TextBox();
			txtCodCiudad->Location = System::Drawing::Point(30, 110);

			Button^ btnBusqueda = gcnew Button();
			btnBusqueda->Text = L"Busqueda";
			btnBusqueda->Location = System::Drawing::Point(90, 160);
			btnBusqueda->Click += gcnew System::EventHandler(this, &FormBuscarCiudad::Busqueda_Click);

			this->Controls->Add(lblCodPais);
			this->Controls->Add(txtCodPais);
			this->Controls->Add(lblCodCiudad);
			this->Controls->Add(txtCodCiudad);
			this->Controls->Add(btnBusqueda);
		}

	private:
		System::Void Busqueda_Click(System::Object^ sender, System::EventArgs^ e) {
			if (txtCodPais->Text == "" or txtCodCiudad->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string codPaisstr = msclr::interop::marshal_as<string>(txtCodPais->Text);
			string codCiudadstr = msclr::interop::marshal_as<string>(txtCodCiudad->Text);
			int codPaisint = stoi(codPaisstr);
			int codCiudadint = stoi(codCiudadstr);

			// pasi hay
			if (arbolPaises->Buscarvalor(codPaisint) == nullptr) {
				MessageBox::Show(L"No existe ningun pais con el codigo " + codPaisint, L"Pais no encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			// ciudad en ese pais
			pCiudad nodo = arbolCiudades->Buscarvalor(codPaisint, codCiudadint);

			if (nodo != nullptr) {
				String^ nombreCiu = gcnew String(nodo->nombre.c_str());
				String^ resultado = L"--- Ciudad Encontrada ---\n\n" + L"Codigo Pais: " + nodo->codPais + L"\n" + L"Codigo Ciudad: " + nodo->codCiudad + L"\n" + L"Nombre: " + nombreCiu;
				MessageBox::Show(resultado, L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				MessageBox::Show(L"No se encontro ninguna ciudad con el codigo " + codCiudadint + L" en el pais " + codPaisint, L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};



// DIAGNOSTICO -------------------------------------------------------------------------------------------------------------
	public ref class FormBuscarDiagnostico : public System::Windows::Forms::Form {
	private:
		TextBox^ txtIdDiag;
		ArbolDiagnostico* arbolDiag;

	public:
		FormBuscarDiagnostico(ArbolDiagnostico* arbol) {
			arbolDiag = arbol;

			this->Text = L"Buscar Diagnostico";
			this->Size = System::Drawing::Size(300, 200);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// iddiag
			Label^ lblId = gcnew Label();
			lblId->Text = L"Id Diagnostico (ej. D001):";
			lblId->Location = System::Drawing::Point(30, 30);
			lblId->AutoSize = true;
			txtIdDiag = gcnew TextBox();
			txtIdDiag->Location = System::Drawing::Point(30, 50);

			Button^ btnBusqueda = gcnew Button();
			btnBusqueda->Text = L"Busqueda";
			btnBusqueda->Location = System::Drawing::Point(90, 100);
			btnBusqueda->Click += gcnew System::EventHandler(this, &FormBuscarDiagnostico::Busqueda_Click);

			this->Controls->Add(lblId);
			this->Controls->Add(txtIdDiag);
			this->Controls->Add(btnBusqueda);
		}

	private:
		System::Void Busqueda_Click(System::Object^ sender, System::EventArgs^ e) {
			if (txtIdDiag->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string iddiagstr = msclr::interop::marshal_as<string>(txtIdDiag->Text);
			pDiag nodo = arbolDiag->Buscarvalor(iddiagstr);

			if (nodo != nullptr) {
				String^ idDiag = gcnew String(nodo->idDiagnostico.c_str());
				String^ nombreDiag = gcnew String(nodo->nombre.c_str());
				String^ descDiag = gcnew String(nodo->descripcion.c_str());

				String^ resultado = L"--- Diagnostico Encontrado ---\n\n" + L"ID: " + idDiag + L"\n" + L"Nombre: " + nombreDiag + L"\n" + L"Descripcion: " + descDiag;
				MessageBox::Show(resultado, L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				String^ msjError = gcnew String(iddiagstr.c_str());
				MessageBox::Show(L"No se encontro ningun diagnostico con el ID " + msjError, L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};

// TRATAMIENTO -------------------------------------------------------------------------------------------------------------
	public ref class FormBuscarTratamiento : public System::Windows::Forms::Form {
	private:
		TextBox^ txtIdTrata;
		ArbolTratamiento* arbolTrata;

	public:
		FormBuscarTratamiento(ArbolTratamiento* arbol) {
			arbolTrata = arbol;

			this->Text = L"Buscar Tratamiento";
			this->Size = System::Drawing::Size(300, 200);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// id trata
			Label^ lblId = gcnew Label();
			lblId->Text = L"Id de Tratamiento a buscar:";
			lblId->Location = System::Drawing::Point(30, 30);
			lblId->AutoSize = true;
			txtIdTrata = gcnew TextBox();
			txtIdTrata->Location = System::Drawing::Point(30, 50);

			Button^ btnBusqueda = gcnew Button();
			btnBusqueda->Text = L"Busqueda";
			btnBusqueda->Location = System::Drawing::Point(90, 100);
			btnBusqueda->Click += gcnew System::EventHandler(this, &FormBuscarTratamiento::Busqueda_Click);

			this->Controls->Add(lblId);
			this->Controls->Add(txtIdTrata);
			this->Controls->Add(btnBusqueda);
		}

	private:
		System::Void Busqueda_Click(System::Object^ sender, System::EventArgs^ e) {
			if (txtIdTrata->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string idtratastr = msclr::interop::marshal_as<string>(txtIdTrata->Text);
			int idtrataint = stoi(idtratastr);

			pTrata nodo = arbolTrata->Buscarvalor(idtrataint);

			if (nodo != nullptr) {
				String^ nombreTrata = gcnew String(nodo->nombre.c_str());
				String^ descTrata = gcnew String(nodo->descripcion.c_str());

				String^ resultado = L"--- Tratamiento Encontrado ---\n\n" + L"ID: " + nodo->idTratamiento + L"\n" + L"Nombre: " + nombreTrata + L"\n" + L"Descripcion: " + descTrata + L"\n" + L"Costo: " + nodo->costo;

				MessageBox::Show(resultado, L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				MessageBox::Show(L"No se encontro ningun tratamiento con el ID " + idtrataint, L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};




// DIAGNOSTICO -------------------------------------------------------------------------------------------------------------
	public ref class FormBuscarEspecialidad : public System::Windows::Forms::Form {
	private:
		TextBox^ txtIdEsp;
		ArbolEspecialidad* arbolEspecialidades;

	public:
		FormBuscarEspecialidad(ArbolEspecialidad* arbol) {
			arbolEspecialidades = arbol;

			this->Text = L"Buscar Especialidad";
			this->Size = System::Drawing::Size(300, 200);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// idesp
			Label^ lblId = gcnew Label();
			lblId->Text = L"Id de Especialidad a buscar:";
			lblId->Location = System::Drawing::Point(30, 30);
			lblId->AutoSize = true;
			txtIdEsp = gcnew TextBox();
			txtIdEsp->Location = System::Drawing::Point(30, 50);

			Button^ btnBusqueda = gcnew Button();
			btnBusqueda->Text = L"Busqueda";
			btnBusqueda->Location = System::Drawing::Point(90, 100);
			btnBusqueda->Click += gcnew System::EventHandler(this, &FormBuscarEspecialidad::Busqueda_Click);

			this->Controls->Add(lblId);
			this->Controls->Add(txtIdEsp);
			this->Controls->Add(btnBusqueda);
		}

	private:
		System::Void Busqueda_Click(System::Object^ sender, System::EventArgs^ e) {
			if (txtIdEsp->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string idespstr = msclr::interop::marshal_as<string>(txtIdEsp->Text);
			int idespint = stoi(idespstr);

			pEsp nodo = arbolEspecialidades->Buscarvalor(idespint);

			if (nodo != nullptr) {
				String^ nombreEsp = gcnew String(nodo->nombre.c_str());
				String^ descEsp = gcnew String(nodo->descripcion.c_str());

				String^ resultado = L"--- Especialidad Encontrada ---\n\n" + L"ID: " + nodo->idEspecialidad + L"\n" + L"Nombre: " + nombreEsp + L"\n" + L"Descripcion: " + descEsp;
				MessageBox::Show(resultado, L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				MessageBox::Show(L"No se encontro ninguna especialidad con el ID " + idespint, L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};



// PACIENTE -------------------------------------------------------------------------------------------------------------
	public ref class FormBuscarPaciente : public System::Windows::Forms::Form {
	private:
		TextBox^ txtCodPais;
		TextBox^ txtCodCiudad;
		TextBox^ txtIdPac;
		ArbolPais* arbolPaises;
		ArbolCiudad* arbolCiudades;
		ArbolPacientes* arbolPacientes;

	public:
		FormBuscarPaciente(ArbolPais* arbolP, ArbolCiudad* arbolC, ArbolPacientes* arbolPac) {
			arbolPaises = arbolP;
			arbolCiudades = arbolC;
			arbolPacientes = arbolPac;

			this->Text = L"Buscar Paciente";
			this->Size = System::Drawing::Size(300, 320);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// codp
			Label^ lblCodPais = gcnew Label();
			lblCodPais->Text = L"Codigo de Pais:";
			lblCodPais->Location = System::Drawing::Point(30, 30);
			lblCodPais->AutoSize = true;
			txtCodPais = gcnew TextBox();
			txtCodPais->Location = System::Drawing::Point(30, 50);

			// codc
			Label^ lblCodCiudad = gcnew Label();
			lblCodCiudad->Text = L"Codigo de Ciudad:";
			lblCodCiudad->Location = System::Drawing::Point(30, 90);
			lblCodCiudad->AutoSize = true;
			txtCodCiudad = gcnew TextBox();
			txtCodCiudad->Location = System::Drawing::Point(30, 110);

			// odpac
			Label^ lblId = gcnew Label();
			lblId->Text = L"Id de Paciente a buscar:";
			lblId->Location = System::Drawing::Point(30, 150);
			lblId->AutoSize = true;
			txtIdPac = gcnew TextBox();
			txtIdPac->Location = System::Drawing::Point(30, 170);

			Button^ btnBusqueda = gcnew Button();
			btnBusqueda->Text = L"Busqueda";
			btnBusqueda->Location = System::Drawing::Point(90, 220);
			btnBusqueda->Click += gcnew System::EventHandler(this, &FormBuscarPaciente::Busqueda_Click);

			this->Controls->Add(lblCodPais);
			this->Controls->Add(txtCodPais);
			this->Controls->Add(lblCodCiudad);
			this->Controls->Add(txtCodCiudad);
			this->Controls->Add(lblId);
			this->Controls->Add(txtIdPac);
			this->Controls->Add(btnBusqueda);
		}

	private:
		System::Void Busqueda_Click(System::Object^ sender, System::EventArgs^ e) {
			if (txtCodPais->Text == "" or txtCodCiudad->Text == "" or txtIdPac->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			int codPaisint = stoi(msclr::interop::marshal_as<string>(txtCodPais->Text));
			int codCiudadint = stoi(msclr::interop::marshal_as<string>(txtCodCiudad->Text));
			int idpacint = stoi(msclr::interop::marshal_as<string>(txtIdPac->Text));

			// codc hay
			if (arbolCiudades->Buscarvalor(codPaisint, codCiudadint) == nullptr) {
				MessageBox::Show(L"No existe ninguna ciudad con el codigo " + codCiudadint + L" en el pais " + codPaisint, L"Ciudad no encontrada", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			pPaciente nodo = arbolPacientes->Buscarvalor(idpacint);

			if (nodo != nullptr) {
				String^ nombrePac = gcnew String(nodo->nombre.c_str());
				String^ fechaPac = gcnew String(nodo->fechaNacimiento.c_str());
				String^ telPac = gcnew String(nodo->telefono.c_str());
				String^ correoPac = gcnew String(nodo->correo.c_str());
				String^ resultado = L"--- Paciente Encontrado ---\n\n" + L"ID: " + nodo->idPaciente + L"\n" + L"Nombre: " + nombrePac + L"\n" + L"Fecha Nacimiento: " + fechaPac + L"\n" + L"Telefono: " + telPac + L"\n" + L"Cod Pais: " + nodo->codPais + L"\n" + L"Cod Ciudad: " + nodo->codCiudad + L"\n" + L"Correo: " + correoPac;
				MessageBox::Show(resultado, L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				MessageBox::Show(L"No se encontro ningun paciente con el ID " + idpacint, L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};

// MEDICO -------------------------------------------------------------------------------------------------------------
	public ref class FormBuscarMedico : public System::Windows::Forms::Form {
	private:
		TextBox^ txtIdEsp;
		TextBox^ txtIdMed;
		ArbolEspecialidad* arbolEspecialidades;
		ArbolMedicos* arbolMedicos;

	public:
		FormBuscarMedico(ArbolEspecialidad* arbolEsp, ArbolMedicos* arbolMed) {
			arbolEspecialidades = arbolEsp;
			arbolMedicos = arbolMed;

			this->Text = L"Buscar Medico";
			this->Size = System::Drawing::Size(300, 260);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// idesp
			Label^ lblIdEsp = gcnew Label();
			lblIdEsp->Text = L"Id de Especialidad:";
			lblIdEsp->Location = System::Drawing::Point(30, 30);
			lblIdEsp->AutoSize = true;
			txtIdEsp = gcnew TextBox();
			txtIdEsp->Location = System::Drawing::Point(30, 50);

			// idmed
			Label^ lblId = gcnew Label();
			lblId->Text = L"Id de Medico a buscar:";
			lblId->Location = System::Drawing::Point(30, 90);
			lblId->AutoSize = true;
			txtIdMed = gcnew TextBox();
			txtIdMed->Location = System::Drawing::Point(30, 110);

			Button^ btnBusqueda = gcnew Button();
			btnBusqueda->Text = L"Busqueda";
			btnBusqueda->Location = System::Drawing::Point(90, 160);
			btnBusqueda->Click += gcnew System::EventHandler(this, &FormBuscarMedico::Busqueda_Click);

			this->Controls->Add(lblIdEsp);
			this->Controls->Add(txtIdEsp);
			this->Controls->Add(lblId);
			this->Controls->Add(txtIdMed);
			this->Controls->Add(btnBusqueda);
		}

	private:
		System::Void Busqueda_Click(System::Object^ sender, System::EventArgs^ e) {
			if (txtIdEsp->Text == "" or txtIdMed->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			int idespint = stoi(msclr::interop::marshal_as<string>(txtIdEsp->Text));
			int idmedicoint = stoi(msclr::interop::marshal_as<string>(txtIdMed->Text));

			// idesp hay
			if (arbolEspecialidades->Buscarvalor(idespint) == nullptr) {
				MessageBox::Show(L"No existe ninguna especialidad con el codigo " + idespint, L"Especialidad no encontrada", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			pMedico nodo = arbolMedicos->Buscarvalor(idmedicoint);

			if (nodo != nullptr) {

				String^ nombreMed = gcnew String(nodo->nombre.c_str());
				String^ telMed = gcnew String(nodo->telefono.c_str());
				String^ correoMed = gcnew String(nodo->correo.c_str());
				String^ resultado = L"--- Medico Encontrado ---\n\n" + L"ID: " + nodo->idMedico + L"\n" + L"Nombre: " + nombreMed + L"\n" + L"Telefono: " + telMed + L"\n" + L"Correo: " + correoMed + L"\n" + L"ID Especialidad: " + nodo->idEspecialidad;
				MessageBox::Show(resultado, L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				MessageBox::Show(L"No se encontro ningun medico con el ID " + idmedicoint, L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};

// HABITACION -------------------------------------------------------------------------------------------------------------
	public ref class FormBuscarHabitacion : public System::Windows::Forms::Form {
	private:
		TextBox^ txtIdHab;
		ArbolHabitaciones* arbolHabitaciones;

	public:
		FormBuscarHabitacion(ArbolHabitaciones* arbol) {
			arbolHabitaciones = arbol;

			this->Text = L"Buscar Habitacion";
			this->Size = System::Drawing::Size(300, 200);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// idhab
			Label^ lblId = gcnew Label();
			lblId->Text = L"Id de Habitacion a buscar:";
			lblId->Location = System::Drawing::Point(30, 30);
			lblId->AutoSize = true;
			txtIdHab = gcnew TextBox();
			txtIdHab->Location = System::Drawing::Point(30, 50);

			Button^ btnBusqueda = gcnew Button();
			btnBusqueda->Text = L"Busqueda";
			btnBusqueda->Location = System::Drawing::Point(90, 100);
			btnBusqueda->Click += gcnew System::EventHandler(this, &FormBuscarHabitacion::Busqueda_Click);

			this->Controls->Add(lblId);
			this->Controls->Add(txtIdHab);
			this->Controls->Add(btnBusqueda);
		}

	private:
		System::Void Busqueda_Click(System::Object^ sender, System::EventArgs^ e) {
			if (txtIdHab->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string idhabstr = msclr::interop::marshal_as<string>(txtIdHab->Text);
			int idhabint = stoi(idhabstr);

			pHab nodo = arbolHabitaciones->Buscarvalor(idhabint);

			if (nodo != nullptr) {
				String^ pisoHab = gcnew String(nodo->piso.c_str());

				// todo estos chunches es para poner tipo y estado bonito
				String^ tipoHab;
				if (nodo->tipo == 1) {
					tipoHab = L"Individual";
				}
				else if (nodo->tipo == 2) {
					tipoHab = L"Compartida";
				}
				else {
					tipoHab = L"UCI";
				}
				String^ estadoHab;
				if (nodo->estado == 0) {
					estadoHab = L"Disponible";
				}
				else {
					estadoHab = L"Ocupada"; // tecnicamente cualquier chunche saldria como ocupada, pero me da pereza cambiarlo
				}

				String^ resultado = L"--- Habitacion Encontrada ---\n\n" + L"ID: " + nodo->idHabitacion + L"\n" + L"Numero: " + nodo->numero + L"\n" + L"Piso: " + pisoHab + L"\n" + L"Tipo: " + tipoHab + L"\n" + L"Estado: " + estadoHab;
				MessageBox::Show(resultado, L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				MessageBox::Show(L"No se encontro ninguna habitacion con el ID " + idhabint, L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};



// HOSPITALIZACIONES -------------------------------------------------------------------------------------------------------------
	public ref class FormBuscarHospitalizacion : public System::Windows::Forms::Form {
	private:
		TextBox^ txtIdPac;
		TextBox^ txtIdHab;
		TextBox^ txtIdHosp;
		ArbolPacientes* arbolPac;
		ArbolHabitaciones* arbolHab;
		ArbolMedicos* arbolMed;
		ArbolHospitalizaciones* arbolHosp;

	public:
		FormBuscarHospitalizacion(ArbolPacientes* aPac, ArbolHabitaciones* aHab, ArbolMedicos* aMed, ArbolHospitalizaciones* aHosp) {
			arbolPac = aPac;
			arbolHab = aHab;
			arbolMed = aMed;
			arbolHosp = aHosp;

			this->Text = L"Buscar Hospitalizacion";
			this->Size = System::Drawing::Size(300, 320);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// idpac
			Label^ lblIdPac = gcnew Label();
			lblIdPac->Text = L"Id del Paciente:";
			lblIdPac->Location = System::Drawing::Point(30, 30);
			lblIdPac->AutoSize = true;
			txtIdPac = gcnew TextBox();
			txtIdPac->Location = System::Drawing::Point(30, 50);

			// idhab
			Label^ lblIdHab = gcnew Label();
			lblIdHab->Text = L"Id de la Habitacion:";
			lblIdHab->Location = System::Drawing::Point(30, 90);
			lblIdHab->AutoSize = true;
			txtIdHab = gcnew TextBox();
			txtIdHab->Location = System::Drawing::Point(30, 110);

			// idhops
			Label^ lblId = gcnew Label();
			lblId->Text = L"Id de Hosp a buscar:";
			lblId->Location = System::Drawing::Point(30, 150);
			lblId->AutoSize = true;
			txtIdHosp = gcnew TextBox();
			txtIdHosp->Location = System::Drawing::Point(30, 170);

			Button^ btnBusqueda = gcnew Button();
			btnBusqueda->Text = L"Busqueda";
			btnBusqueda->Location = System::Drawing::Point(90, 220);
			btnBusqueda->Click += gcnew System::EventHandler(this, &FormBuscarHospitalizacion::Busqueda_Click);

			this->Controls->Add(lblIdPac); this->Controls->Add(txtIdPac);
			this->Controls->Add(lblIdHab); this->Controls->Add(txtIdHab);
			this->Controls->Add(lblId); this->Controls->Add(txtIdHosp);
			this->Controls->Add(btnBusqueda);
		}

	private:
		System::Void Busqueda_Click(System::Object^ sender, System::EventArgs^ e) {
			if (txtIdPac->Text == "" or txtIdHab->Text == "" or txtIdHosp->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			int idpacint = stoi(msclr::interop::marshal_as<string>(txtIdPac->Text));
			int idhabint = stoi(msclr::interop::marshal_as<string>(txtIdHab->Text));
			int idhospint = stoi(msclr::interop::marshal_as<string>(txtIdHosp->Text));

			// idpac hay
			if (arbolPac->Buscarvalor(idpacint) == nullptr) {
				MessageBox::Show(L"No existe ningun paciente con el ID " + idpacint, L"Paciente no encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			// idhab hay
			if (arbolHab->Buscarvalor(idhabint) == nullptr) {
				MessageBox::Show(L"No existe ninguna habitacion con el ID " + idhabint, L"Habitacion no encontrada", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			pHosp nodo = arbolHosp->Buscarvalor(idhospint);

			if (nodo != nullptr) {

				String^ fIngreso = gcnew String(nodo->fechaIngreso.c_str());
				String^ fSalida = gcnew String(nodo->fechaSalida.c_str());
				String^ motivo = gcnew String(nodo->motivo.c_str());
				String^ resultado = L"--- Hospitalizacion Encontrada ---\n\n" + L"ID Hosp: " + nodo->idHospitalizacion + L"\n" + L"ID Paciente: " + nodo->idPaciente + L"\n" + L"ID Habitacion: " + nodo->idHabitacion + L"\n" + L"ID Medico: " + nodo->idMedico + L"\n" + L"Ingreso: " + fIngreso + L"\n" + L"Salida: " + fSalida + L"\n" + L"Motivo: " + motivo;

				MessageBox::Show(resultado, L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				MessageBox::Show(L"No se encontro ninguna hospitalizacion con el ID " + idhospint, L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};


// CITA -------------------------------------------------------------------------------------------------------------
	public ref class FormBuscarCita : public System::Windows::Forms::Form {
	private:
		TextBox^ txtIdPac;
		TextBox^ txtIdMed;
		TextBox^ txtIdCita;
		ArbolPacientes* arbolPac;
		ArbolMedicos* arbolMed;
		ArbolEspecialidad* arbolEsp;
		ArbolCitas* arbolCitas;

	public:
		FormBuscarCita(ArbolPacientes* aPac, ArbolMedicos* aMed, ArbolEspecialidad* aEsp, ArbolCitas* aCita) {
			arbolPac = aPac;
			arbolMed = aMed;
			arbolEsp = aEsp;
			arbolCitas = aCita;

			this->Text = L"Buscar Cita";
			this->Size = System::Drawing::Size(300, 320);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			//idpac
			Label^ lblIdPac = gcnew Label();
			lblIdPac->Text = L"Id del Paciente:";
			lblIdPac->Location = System::Drawing::Point(30, 30);
			lblIdPac->AutoSize = true;
			txtIdPac = gcnew TextBox();
			txtIdPac->Location = System::Drawing::Point(30, 50);

			// idmed
			Label^ lblIdMed = gcnew Label();
			lblIdMed->Text = L"Id del Medico:";
			lblIdMed->Location = System::Drawing::Point(30, 90);
			lblIdMed->AutoSize = true;
			txtIdMed = gcnew TextBox();
			txtIdMed->Location = System::Drawing::Point(30, 110);

			// idcita
			Label^ lblIdCita = gcnew Label();
			lblIdCita->Text = L"Id de Cita a buscar:";
			lblIdCita->Location = System::Drawing::Point(30, 150);
			lblIdCita->AutoSize = true;
			txtIdCita = gcnew TextBox();
			txtIdCita->Location = System::Drawing::Point(30, 170);

			Button^ btnBusqueda = gcnew Button();
			btnBusqueda->Text = L"Busqueda";
			btnBusqueda->Location = System::Drawing::Point(90, 220);
			btnBusqueda->Click += gcnew System::EventHandler(this, &FormBuscarCita::Busqueda_Click);

			this->Controls->Add(lblIdPac); 
			this->Controls->Add(txtIdPac);
			this->Controls->Add(lblIdMed); 
			this->Controls->Add(txtIdMed);
			this->Controls->Add(lblIdCita); 
			this->Controls->Add(txtIdCita);
			this->Controls->Add(btnBusqueda);
		}

	private:
		System::Void Busqueda_Click(System::Object^ sender, System::EventArgs^ e) {
			if (txtIdPac->Text == "" or txtIdMed->Text == "" or txtIdCita->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			int idpacint = stoi(msclr::interop::marshal_as<string>(txtIdPac->Text));
			int idmedint = stoi(msclr::interop::marshal_as<string>(txtIdMed->Text));
			int idcitaint = stoi(msclr::interop::marshal_as<string>(txtIdCita->Text));

			// idpac hay
			if (arbolPac->Buscarvalor(idpacint) == nullptr) {
				MessageBox::Show(L"No existe ningun paciente con el ID " + idpacint, L"Paciente no encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			// idmed hay
			if (arbolMed->Buscarvalor(idmedint) == nullptr) {
				MessageBox::Show(L"No existe ningun medico con el ID " + idmedint, L"Medico no encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			pCita nodo = arbolCitas->Buscarvalor(idcitaint);

			if (nodo != nullptr) {
				String^ fechaCita = gcnew String(nodo->fecha.c_str());
				String^ horaCita = gcnew String(nodo->hora.c_str());
				String^ motivoCita = gcnew String(nodo->motivo.c_str());

				// lo mismo q habitaciones
				String^ estadoCita;
				if (nodo->estado == 0) {
					estadoCita = L"Pendiente";
				}
				else {
					estadoCita = L"Confirmada";
				}

				String^ resultado = L"--- Cita Encontrada ---\n\n" + L"ID Cita: " + nodo->idCita + L"\n" + L"ID Paciente: " + nodo->idPaciente + L"\n" + L"ID Medico: " + nodo->idMedico + L"\n" + L"ID Especialidad: " + nodo->idEspecialidad + L"\n" + L"Fecha: " + fechaCita + L"\n" + L"Hora: " + horaCita + L"\n" + L"Motivo: " + motivoCita + L"\n" + L"Estado: " + estadoCita;

				MessageBox::Show(resultado, L"Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else {
				MessageBox::Show(L"No se encontro ninguna cita con el ID " + idcitaint, L"No Encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};


// ventana con los botones ----------------------------------------------------------------------------------------
	public ref class FormBuscar : public System::Windows::Forms::Form
		// ventana Buscar
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
		FormBuscar(ArbolPais* arbolP, ArbolCiudad* arbolC, ArbolEspecialidad* arbolE, ArbolCitas* arbolCi, ArbolHabitaciones* arbolHa, ArbolHospitalizaciones* arbolHo, ArbolMedicos* arbolM, ArbolPacientes* arbolPac, ArbolTratamiento* arbolT, ArbolDiagnostico* arbolD) {
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

			this->Text = L"Buscar Registro";
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

			btnPaises->Click += gcnew System::EventHandler(this, &FormBuscar::Paises_Click);
			btnCiudades->Click += gcnew System::EventHandler(this, &FormBuscar::Ciudades_Click);
			btnEspecialidades->Click += gcnew System::EventHandler(this, &FormBuscar::Especialidades_Click);
			btnTratamientos->Click += gcnew System::EventHandler(this, &FormBuscar::Tratamientos_Click);
			btnDiagnosticos->Click += gcnew System::EventHandler(this, &FormBuscar::Diagnosticos_Click);
			btnPacientes->Click += gcnew System::EventHandler(this, &FormBuscar::Pacientes_Click);
			btnMedicos->Click += gcnew System::EventHandler(this, &FormBuscar::Medicos_Click);
			btnHabitaciones->Click += gcnew System::EventHandler(this, &FormBuscar::Habitaciones_Click);
			btnHospitalizaciones->Click += gcnew System::EventHandler(this, &FormBuscar::Hospitalizaciones_Click);
			btnCitas->Click += gcnew System::EventHandler(this, &FormBuscar::Citas_Click);

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
		System::Void Paises_Click(System::Object^ sender, System::EventArgs^ e) {
			FormBuscarPais^ ventanaPais = gcnew FormBuscarPais(arbolilloPaises);
			ventanaPais->ShowDialog();
		}

		System::Void Ciudades_Click(System::Object^ sender, System::EventArgs^ e) {
			FormBuscarCiudad^ ventanaCiudad = gcnew FormBuscarCiudad(arbolilloPaises, arbolilloCiudades);
			ventanaCiudad->ShowDialog();
		}

		System::Void Especialidades_Click(System::Object^ sender, System::EventArgs^ e) {
			FormBuscarEspecialidad^ ventanaEspecialidad = gcnew FormBuscarEspecialidad(arbolilloEsp);
			ventanaEspecialidad->ShowDialog();
		}

		System::Void Tratamientos_Click(System::Object^ sender, System::EventArgs^ e) {
			FormBuscarTratamiento^ ventanaTratamiento = gcnew FormBuscarTratamiento(arbolilloTrata);
			ventanaTratamiento->ShowDialog();
		}

		System::Void Diagnosticos_Click(System::Object^ sender, System::EventArgs^ e) {
			FormBuscarDiagnostico^ ventanaDiagnostico = gcnew FormBuscarDiagnostico(arbolilloDiag);
			ventanaDiagnostico->ShowDialog();
		}

		System::Void Pacientes_Click(System::Object^ sender, System::EventArgs^ e) {
			FormBuscarPaciente^ ventanaPaciente = gcnew FormBuscarPaciente(arbolilloPaises, arbolilloCiudades, arbolilloPac);
			ventanaPaciente->ShowDialog();
		}

		System::Void Medicos_Click(System::Object^ sender, System::EventArgs^ e) {
			FormBuscarMedico^ ventanaMedico = gcnew FormBuscarMedico(arbolilloEsp, arbolilloMed);
			ventanaMedico->ShowDialog();
		}

		System::Void Habitaciones_Click(System::Object^ sender, System::EventArgs^ e) {
			FormBuscarHabitacion^ ventanaHabitacion = gcnew FormBuscarHabitacion(arbolilloHab);
			ventanaHabitacion->ShowDialog();
		}

		System::Void Hospitalizaciones_Click(System::Object^ sender, System::EventArgs^ e) {
			FormBuscarHospitalizacion^ ventanaHosp = gcnew FormBuscarHospitalizacion(arbolilloPac, arbolilloHab, arbolilloMed, arbolilloHosp);
			ventanaHosp->ShowDialog();
		}

		System::Void Citas_Click(System::Object^ sender, System::EventArgs^ e) {
			FormBuscarCita^ ventanaCita = gcnew FormBuscarCita(arbolilloPac, arbolilloMed, arbolilloEsp, arbolilloCitas);
			ventanaCita->ShowDialog();
		}
	};
}
