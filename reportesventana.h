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
#include "Proyecto3/reportes.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	/*
	public ref class FormReportePais : public System::Windows::Forms::Form {

	private:
		ArbolPais* arbolilloPais;
		Consola^ consolaRep;

	public:
		FormReportePais(ArbolPais* arbolP, Consola^ consola) {
			arbolilloPais = arbolP;
			consolaRep = consola;

			this->Text = L"Generar reporte de todos los paises";
			this->Size = System::Drawing::Size(300, 200);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			Button^ btnGenerar = gcnew Button();
			btnGenerar->Text = L"Generar reporte";
			btnGenerar->Size = System::Drawing::Size(120, 30);
			btnGenerar->Location = System::Drawing::Point(80, 60);
			btnGenerar->Click += gcnew System::EventHandler(this, &FormReportePais::Generar_Click);

			this->Controls->Add(btnGenerar);
		}

	private:
		System::Void Generar_Click(System::Object^ sender, System::EventArgs^ e) {
			CapturaSalida cap;
			reportes rep;
			rep.ReporteTodosPaises(*arbolilloPais);
			String^ mensajeConsola = aNet(cap.Terminar());
			consolaRep->Escribir(mensajeConsola);

			MessageBox::Show(L"Reporte de todos los paises generado en el archivo reporte_paises.pdf", L"Reporte Generado", MessageBoxButtons::OK, MessageBoxIcon::Information);
			this->Close();
		}
	};
	*/

	public ref class FormReporteCiudadesDePais : public System::Windows::Forms::Form {

	private:
		TextBox^ txtCodPais;
		ArbolPais* arbolilloPais;
		ArbolCiudad* arbolilloCiudad;
		Consola^ consolaRep;

	public:
		FormReporteCiudadesDePais(ArbolPais* arbolP, ArbolCiudad* arbolC, Consola^ consola) {
			arbolilloPais = arbolP;
			arbolilloCiudad = arbolC;
			consolaRep = consola;

			this->Text = L"Reporte de ciudades de un pais";
			this->Size = System::Drawing::Size(300, 200);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// codpais
			Label^ lblCod = gcnew Label();
			lblCod->Text = L"Codigo de pais: ";
			lblCod->Location = System::Drawing::Point(30, 30);
			lblCod->AutoSize = true;
			txtCodPais = gcnew TextBox();
			txtCodPais->Location = System::Drawing::Point(30, 50);

			Button^ btnGenerar = gcnew Button();
			btnGenerar->Text = L"Generar reporte";
			btnGenerar->Size = System::Drawing::Size(120, 30);
			btnGenerar->Location = System::Drawing::Point(80, 100);
			btnGenerar->Click += gcnew System::EventHandler(this, &FormReporteCiudadesDePais::Generar_Click);

			this->Controls->Add(lblCod);
			this->Controls->Add(txtCodPais);
			this->Controls->Add(btnGenerar);
		}

	private:
		System::Void Generar_Click(System::Object^ sender, System::EventArgs^ e) {

			if (txtCodPais->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string codPaisstr = msclr::interop::marshal_as<string>(txtCodPais->Text);
			int codPaisint = stoi(codPaisstr);

			if (arbolilloPais->Buscarvalor(codPaisint) == nullptr) {
				MessageBox::Show(L"No existe ningun pais con el codigo " + codPaisint, L"Pais no encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			else {
				CapturaSalida cap;
				reportes rep2;
				rep2.ReporteTodasCiudadesDePais(*arbolilloCiudad, *arbolilloPais, codPaisint);
				String^ mensajeConsola = aNet(cap.Terminar());
				consolaRep->Escribir(mensajeConsola);

				MessageBox::Show(L"Reporte de ciudades del pais generado en el archivo reporte_ciudades_de_pais.pdf", L"Reporte Generado", MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}

		}
	};


	public ref class FormReporteHospDeMedico : public System::Windows::Forms::Form {

	private:
		TextBox^ txtIdMedico;
		ArbolHospitalizaciones* arbolilloHosp;
		ArbolMedicos* arbolilloMed;
		Consola^ consolaRep;

	public:
		FormReporteHospDeMedico(ArbolHospitalizaciones* arbolH, ArbolMedicos* arbolM, Consola^ consola) {
			arbolilloHosp = arbolH;
			arbolilloMed = arbolM;
			consolaRep = consola;

			this->Text = L"Reporte de hospitalizaciones de un medico";
			this->Size = System::Drawing::Size(300, 200);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			// idmed
			Label^ lblId = gcnew Label();
			lblId->Text = L"Id del medico: ";
			lblId->Location = System::Drawing::Point(30, 30);
			lblId->AutoSize = true;
			txtIdMedico = gcnew TextBox();
			txtIdMedico->Location = System::Drawing::Point(30, 50);

			Button^ btnGenerar = gcnew Button();
			btnGenerar->Text = L"Generar reporte";
			btnGenerar->Size = System::Drawing::Size(120, 30);
			btnGenerar->Location = System::Drawing::Point(80, 100);
			btnGenerar->Click += gcnew System::EventHandler(this, &FormReporteHospDeMedico::Generar_Click);

			this->Controls->Add(lblId);
			this->Controls->Add(txtIdMedico);
			this->Controls->Add(btnGenerar);
		}

	private:
		System::Void Generar_Click(System::Object^ sender, System::EventArgs^ e) {

			if (txtIdMedico->Text == "") {
				MessageBox::Show(L"Por favor llene todos los campos.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			string idMedstr = msclr::interop::marshal_as<string>(txtIdMedico->Text);
			int idMedint = stoi(idMedstr);

			if (arbolilloMed->Buscarvalor(idMedint) == nullptr) {
				MessageBox::Show(L"No existe ningun medico con el id " + idMedint, L"Medico no encontrado", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			else {
				CapturaSalida cap;
				reportes rep2;
				rep2.ReporteHospitalizacionesPorMedico(*arbolilloHosp, *arbolilloMed, idMedint);
				String^ mensajeConsola = aNet(cap.Terminar());
				consolaRep->Escribir(mensajeConsola);

			}

			MessageBox::Show(L"Reporte de hospitalizaciones del medico generado en el archivo reporte_hospitalizaciones_de_medico.pdf", L"Reporte Generado", MessageBoxButtons::OK, MessageBoxIcon::Information);
			this->Close();
		}
	};

	//REPORTES CON FILTRO una  ventana para los 7 reportes q piden un dato antes de generar PDF
	//segun tipo la ventana pide: un id, una fecha, o pais y ciudad
	public ref class FormReporteFiltro : public System::Windows::Forms::Form {

	private:
		String^ tipo;
		Label^ lblDato1;
		TextBox^ txtDato1;
		Label^ lblDato2;
		TextBox^ txtDato2;
		DateTimePicker^ dtpFecha;

		ArbolPacientes* arbolPac;
		ArbolMedicos* arbolMed;
		ArbolEspecialidad* arbolEsp;
		ArbolCitas* arbolCita;
		ArbolPais* arbolPais;
		ArbolCiudad* arbolCiudad;
		Consola^ consolaRep;

	public:
		FormReporteFiltro(String^ tipoReporte, ArbolPacientes* pacientes, ArbolMedicos* medicos, ArbolEspecialidad* especialidades,
			ArbolCitas* citas, ArbolPais* paises, ArbolCiudad* ciudades, Consola^ consola) {
			tipo = tipoReporte;
			arbolPac = pacientes;
			arbolMed = medicos;
			arbolEsp = especialidades;
			arbolCita = citas;
			arbolPais = paises;
			arbolCiudad = ciudades;
			consolaRep = consola;

			this->Text = L"Reporte: " + tipo;
			this->Size = System::Drawing::Size(320, 240);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

			//dato 1
			lblDato1 = gcnew Label();
			lblDato1->Location = System::Drawing::Point(30, 20);
			lblDato1->AutoSize = true;
			txtDato1 = gcnew TextBox();
			txtDato1->Location = System::Drawing::Point(30, 40);

			//dato 2 solo para pacientes de una ciudad
			lblDato2 = gcnew Label();
			lblDato2->Text = L"Codigo de ciudad: ";
			lblDato2->Location = System::Drawing::Point(30, 75);
			lblDato2->AutoSize = true;
			lblDato2->Visible = false;
			txtDato2 = gcnew TextBox();
			txtDato2->Location = System::Drawing::Point(30, 95);
			txtDato2->Visible = false;

			//fecha solo para citas por fecha
			dtpFecha = gcnew DateTimePicker();
			dtpFecha->Format = DateTimePickerFormat::Short;
			dtpFecha->Location = System::Drawing::Point(30, 40);
			dtpFecha->Visible = false;

			//segun el reporte se cambia el texto de la etiqueta y q se muestra
			if (tipo == L"Medicos de una especialidad" || tipo == L"Citas por especialidad") {
				lblDato1->Text = L"Id de la especialidad: ";
			}
			else if (tipo == L"Citas de un medico") {
				lblDato1->Text = L"Id del medico: ";
			}
			else if (tipo == L"Citas de un paciente") {
				lblDato1->Text = L"Id del paciente: ";
			}
			else if (tipo == L"Pacientes de un pais") {
				lblDato1->Text = L"Codigo de pais: ";
			}
			else if (tipo == L"Pacientes de una ciudad") {
				lblDato1->Text = L"Codigo de pais: ";
				lblDato2->Visible = true;
				txtDato2->Visible = true;
			}
			else if (tipo == L"Citas por fecha") {
				lblDato1->Text = L"Fecha de las citas: ";
				txtDato1->Visible = false;
				dtpFecha->Visible = true;
			}

			Button^ btnGenerar = gcnew Button();
			btnGenerar->Text = L"Generar reporte";
			btnGenerar->Size = System::Drawing::Size(120, 30);
			btnGenerar->Location = System::Drawing::Point(90, 140);
			btnGenerar->Click += gcnew System::EventHandler(this, &FormReporteFiltro::Generar_Click);

			this->Controls->Add(lblDato1);
			this->Controls->Add(txtDato1);
			this->Controls->Add(lblDato2);
			this->Controls->Add(txtDato2);
			this->Controls->Add(dtpFecha);
			this->Controls->Add(btnGenerar);
		}

	private:
		//muestra el mensaje de error y devuelve false (para escribir menos abajo)
		bool Error(String^ mensaje) {
			MessageBox::Show(mensaje, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return false;
		}

		//revisa q lo q se pidio exista en su arbol, antes de crear el reporte
		bool DatosValidos(int id1, int id2) {
			if (tipo == L"Medicos de una especialidad" || tipo == L"Citas por especialidad") {
				if (arbolEsp->Buscarvalor(id1) == nullptr) {
					return Error(L"No existe ninguna especialidad con el id " + id1.ToString());
				}
			}
			else if (tipo == L"Citas de un medico") {
				if (arbolMed->Buscarvalor(id1) == nullptr) {
					return Error(L"No existe ningun medico con el id " + id1.ToString());
				}
			}
			else if (tipo == L"Citas de un paciente") {
				if (arbolPac->Buscarvalor(id1) == nullptr) {
					return Error(L"No existe ningun paciente con el id " + id1.ToString());
				}
			}
			else if (tipo == L"Pacientes de un pais") {
				if (arbolPais->Buscarvalor(id1) == nullptr) {
					return Error(L"No existe ningun pais con el codigo " + id1.ToString());
				}
			}
			else if (tipo == L"Pacientes de una ciudad") {
				if (arbolPais->Buscarvalor(id1) == nullptr) {
					return Error(L"No existe ningun pais con el codigo " + id1.ToString());
				}
				if (arbolCiudad->Buscarvalor(id1, id2) == nullptr) {
					return Error(L"No existe la ciudad " + id2.ToString() + L" en el pais " + id1.ToString());
				}
			}
			return true;
		}

		System::Void Generar_Click(System::Object^ sender, System::EventArgs^ e) {
			int id1 = 0;
			int id2 = 0;

			//1leer los numeros
			if (tipo != L"Citas por fecha") {
				if (!Int32::TryParse(txtDato1->Text->Trim(), id1)) {
					Error(L"Por favor escriba un numero valido.");
					return;
				}
			}
			if (tipo == L"Pacientes de una ciudad") {
				if (!Int32::TryParse(txtDato2->Text->Trim(), id2)) {
					Error(L"Por favor escriba un codigo de ciudad valido.");
					return;
				}
			}

			//2revisar q exista
			if (!DatosValidos(id1, id2)) {
				return;
			}

			//3generar el PDF
			CapturaSalida cap;
			reportes rep;
			String^ archivo = L"";

			if (tipo == L"Medicos de una especialidad") {
				rep.ReporteMedicosPorEspecialidad(*arbolMed, *arbolEsp, id1);
				archivo = L"reporte_medicos_de_especialidad.pdf";
			}
			else if (tipo == L"Citas por especialidad") {
				rep.ReporteCitasPorEspecialidad(*arbolCita, *arbolEsp, id1);
				archivo = L"reporte_citas_de_especialidad.pdf";
			}
			else if (tipo == L"Citas de un medico") {
				rep.ReporteCitasPorMedico(*arbolCita, *arbolMed, id1);
				archivo = L"reporte_citas_de_medico.pdf";
			}
			else if (tipo == L"Citas de un paciente") {
				rep.ReporteCitasPorPaciente(*arbolCita, *arbolPac, id1);
				archivo = L"reporte_citas_de_paciente.pdf";
			}
			else if (tipo == L"Pacientes de un pais") {
				rep.ReportePacientesPorPais(*arbolPac, *arbolPais, id1);
				archivo = L"reporte_pacientes_de_pais.pdf";
			}
			else if (tipo == L"Pacientes de una ciudad") {
				rep.ReportePacientesPorCiudad(*arbolPac, *arbolCiudad, *arbolPais, id1, id2);
				archivo = L"reporte_pacientes_de_ciudad_de_pais.pdf";
			}
			else if (tipo == L"Citas por fecha") {
				//en el CSV las fechas estan sin cero adelante, entonces se arma igual
				DateTime f = dtpFecha->Value;
				String^ fecha = f.Day.ToString() + L"/" + f.Month.ToString() + L"/" + f.Year.ToString();
				rep.ReporteCitasPorFecha(*arbolCita, aStd(fecha));
				archivo = L"reporte_citas_de_fecha.pdf";
			}

			consolaRep->Escribir(aNet(cap.Terminar()));
			MessageBox::Show(L"Reporte generado en el archivo " + archivo, L"Reporte Generado", MessageBoxButtons::OK, MessageBoxIcon::Information);
			this->Close();
		}
	};

}
