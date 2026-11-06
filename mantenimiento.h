#define _HAS_STD_BYTE 0
// ^ esto es para el error de C2872
#pragma once

#include "Proyecto3/crud_paises.h"
#include "Proyecto3/crud_citas.h"
#include "Proyecto3/crud_ciudades.h"
#include "Proyecto3/crud_diagnostico.h"
#include "Proyecto3/crud_especialidades.h"
#include "Proyecto3/crud_habitaciones.h"
#include "Proyecto3/crud_hospitalizaciones.h"
#include "Proyecto3/crud_medicos.h"
#include "Proyecto3/crud_pacientes.h"
#include "Proyecto3/crud_tratamientos.h"
#include "insertar.h"
#include "modificar.h"
//#include "buscar.h"
//#include "eliminar.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	// vebtana de mantenimiento con botones insertar, buscar, eliminar, modificar
	public ref class FormMantenimiento : public System::Windows::Forms::Form
	{
	private:
		ArbolPais* arbolilloPais;
		ArbolCiudad* arbolilloCiudad;
		ArbolEspecialidad* arbolilloEsp;
		ArbolCitas* arbolilloCitas;
		ArbolHabitaciones* arbolilloHab;
		ArbolHospitalizaciones* arbolilloHosp;
		ArbolMedicos* arbolilloMed;
		ArbolPacientes* arbolilloPac;
		ArbolTratamiento* arbolilloTrata;
		ArbolDiagnostico* arbolilloDiag;
	public:
		FormMantenimiento(ArbolPais* arbolP, ArbolCiudad* arbolC, ArbolHabitaciones* arbolHa, ArbolHospitalizaciones* arbolHo, ArbolPacientes* arbolPac, ArbolMedicos* arbolM, ArbolTratamiento* arbolT, ArbolDiagnostico* arbolD, ArbolEspecialidad* arbolE, ArbolCitas* arbolCi) {
			arbolilloPais = arbolP;
			arbolilloCiudad = arbolC;
			arbolilloHab = arbolHa;
			arbolilloHosp = arbolHo;
			arbolilloPac = arbolPac;
			arbolilloMed = arbolM;
			arbolilloTrata = arbolT;
			arbolilloDiag = arbolD;
			arbolilloEsp = arbolE;
			arbolilloCitas = arbolCi;

			this->Text = L"Mantenimiento de Base de Datos";
			this->Size = System::Drawing::Size(300, 350);
			this->StartPosition = FormStartPosition::CenterParent; // sale en centro
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;

			// crear los 2 botones
			Button^ btnInsertar = gcnew Button();
			btnInsertar->Text = L"1. Insertar";
			btnInsertar->Location = System::Drawing::Point(50, 30);
			btnInsertar->Size = System::Drawing::Size(180, 40);
			btnInsertar->Click += gcnew System::EventHandler(this, &FormMantenimiento::Insertar_Click);

			Button^ btnModificar = gcnew Button();
			btnModificar->Text = L"2. Modificar";
			btnModificar->Location = System::Drawing::Point(50, 90);
			btnModificar->Size = System::Drawing::Size(180, 40);
			btnModificar->Click += gcnew System::EventHandler(this, &FormMantenimiento::Modificar_Click);

			this->Controls->Add(btnInsertar);
			this->Controls->Add(btnModificar);
		}

		System::Void Insertar_Click(System::Object^ sender, System::EventArgs^ e) {
			FormInsertar^ ventanaInsertar = gcnew FormInsertar(arbolilloPais, arbolilloCiudad, arbolilloEsp, arbolilloCitas, arbolilloHab, arbolilloHosp, arbolilloMed, arbolilloPac, arbolilloTrata, arbolilloDiag);
			ventanaInsertar->ShowDialog();
		}
		System::Void Modificar_Click(System::Object^ sender, System::EventArgs^ e) {
			FormModificar^ ventanaModificar = gcnew FormModificar(arbolilloPais, arbolilloCiudad, arbolilloEsp, arbolilloCitas, arbolilloHab, arbolilloHosp, arbolilloMed, arbolilloPac, arbolilloTrata, arbolilloDiag);
			ventanaModificar->ShowDialog();
		}
	};
}