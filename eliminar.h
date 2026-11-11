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

	public:
		FormEliminarPais(ArbolPais* arbol, Consola^ consola) {
			arbolPaises = arbol;
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
			arbolPaises->EliminarPais(codPaisint); // elimina de vrdd
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

	public:
		FormEliminarCiudad(ArbolPais* arbolP, ArbolCiudad* arbolC, Consola^ consola) {
			arbolPaises = arbolP;
			arbolCiudades = arbolC;
			consolaCiudad = consola;

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
			arbolCiudades->EliminarCiudad(codPaisint, codCiudadint, *arbolPaises);
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

	public:
		FormEliminarEspecialidad(ArbolEspecialidad* arbol, Consola^ consola) {
			arbolEsp = arbol;
			consolaEsp = consola;

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
			arbolEsp->EliminarEspecialidad(idespint);
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
