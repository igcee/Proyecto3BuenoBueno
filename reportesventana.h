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



}
