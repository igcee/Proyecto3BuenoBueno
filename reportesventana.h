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
}
