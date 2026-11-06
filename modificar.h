#define _HAS_STD_BYTE 0
// ^ esto es para el error de C2872
#pragma once
#include <string>
#include "utilGUI.h"
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

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	// PAIS (se modifica el nombre)
	public ref class FormModificarPais : public FormCampos {
	private:
		TextBox^ txtCod;
		TextBox^ txtNombre;
		ArbolPais* arbolPais;

	public:
		FormModificarPais(ArbolPais* arbol) : FormCampos(L"Modificar Pais") {
			arbolPais = arbol;

			txtCod = AgregarTexto(L"Codigo del Pais:");
			txtNombre = AgregarTexto(L"Nuevo nombre:");
			AgregarBoton(L"Guardar modificacion", gcnew System::EventHandler(this, &FormModificarPais::Guardar_Click));
		}

	private:
		System::Void Guardar_Click(System::Object^ sender, System::EventArgs^ e) {
			int cod = 0;
			if (GuiUtil::Vacio(txtNombre) || !GuiUtil::LeerEntero(txtCod, cod)) {
				GuiUtil::Aviso(L"Por favor llene todos los campos (el codigo debe ser un numero).");
				return;
			}

			CapturaSalida cap; // atrapa lo q imprime el arbol
			arbolPais->ModificarPais(cod, aStd(txtNombre->Text));
			if (GuiUtil::MostrarResultadoModificar(aNet(cap.Terminar()))) {
				this->Close();
			}
		}
	};

	// CIUDAD (se modifica el nombre)
	public ref class FormModificarCiudad : public FormCampos {
	private:
		TextBox^ txtCodPais;
		TextBox^ txtCodCiudad;
		TextBox^ txtNombre;
		ArbolPais* arbolPais; // ModificarCiudad valida el pais con este
		ArbolCiudad* arbolCiudad;

	public:
		FormModificarCiudad(ArbolPais* arbolP, ArbolCiudad* arbolC) : FormCampos(L"Modificar Ciudad") {
			arbolPais = arbolP;
			arbolCiudad = arbolC;

			txtCodPais = AgregarTexto(L"Codigo del Pais:");
			txtCodCiudad = AgregarTexto(L"Codigo de la Ciudad:");
			txtNombre = AgregarTexto(L"Nuevo nombre:");
			AgregarBoton(L"Guardar modificacion", gcnew System::EventHandler(this, &FormModificarCiudad::Guardar_Click));
		}

	private:
		System::Void Guardar_Click(System::Object^ sender, System::EventArgs^ e) {
			int codp = 0;
			int codc = 0;
			if (GuiUtil::Vacio(txtNombre) || !GuiUtil::LeerEntero(txtCodPais, codp) || !GuiUtil::LeerEntero(txtCodCiudad, codc)) {
				GuiUtil::Aviso(L"Por favor llene todos los campos (los codigos deben ser numeros).");
				return;
			}

			CapturaSalida cap;
			arbolCiudad->ModificarCiudad(codp, codc, aStd(txtNombre->Text), *arbolPais);
			if (GuiUtil::MostrarResultadoModificar(aNet(cap.Terminar()))) {
				this->Close();
			}
		}
	};

	// PACIENTE (se modifican telefono y correo)
	public ref class FormModificarPaciente : public FormCampos {
	private:
		TextBox^ txtCodPais;
		TextBox^ txtCodCiudad;
		TextBox^ txtId;
		TextBox^ txtTel;
		TextBox^ txtCorreo;
		ArbolCiudad* arbolCiudad; // valida q la ciudad exista
		ArbolPacientes* arbolPac;

	public:
		FormModificarPaciente(ArbolCiudad* arbolC, ArbolPacientes* arbolP) : FormCampos(L"Modificar Paciente") {
			arbolCiudad = arbolC;
			arbolPac = arbolP;

			txtCodPais = AgregarTexto(L"Codigo del Pais del paciente:");
			txtCodCiudad = AgregarTexto(L"Codigo de la Ciudad del paciente:");
			txtId = AgregarTexto(L"Id de Paciente:");
			txtTel = AgregarTexto(L"Nuevo telefono:");
			txtCorreo = AgregarTexto(L"Nuevo correo:");
			AgregarBoton(L"Guardar modificacion", gcnew System::EventHandler(this, &FormModificarPaciente::Guardar_Click));
		}

	private:
		System::Void Guardar_Click(System::Object^ sender, System::EventArgs^ e) {
			int codp = 0;
			int codc = 0;
			int id = 0;
			if (GuiUtil::Vacio(txtTel) || GuiUtil::Vacio(txtCorreo) || !GuiUtil::LeerEntero(txtCodPais, codp) || !GuiUtil::LeerEntero(txtCodCiudad, codc) || !GuiUtil::LeerEntero(txtId, id)) {
				GuiUtil::Aviso(L"Por favor llene todos los campos (los codigos e ids deben ser numeros).");
				return;
			}

			CapturaSalida cap;
			arbolPac->ModificarPaciente(codp, codc, id, aStd(txtTel->Text), aStd(txtCorreo->Text), *arbolCiudad);
			if (GuiUtil::MostrarResultadoModificar(aNet(cap.Terminar()))) {
				this->Close();
			}
		}
	};

	// MEDICO (se modifican telefono y correo)
	public ref class FormModificarMedico : public FormCampos {
	private:
		TextBox^ txtIdEsp;
		TextBox^ txtId;
		TextBox^ txtTel;
		TextBox^ txtCorreo;
		ArbolEspecialidad* arbolEsp; // valida q la especialidad exista
		ArbolMedicos* arbolMed;

	public:
		FormModificarMedico(ArbolEspecialidad* arbolE, ArbolMedicos* arbolM) : FormCampos(L"Modificar Medico") {
			arbolEsp = arbolE;
			arbolMed = arbolM;

			txtIdEsp = AgregarTexto(L"Id de la Especialidad del medico:");
			txtId = AgregarTexto(L"Id de Medico:");
			txtTel = AgregarTexto(L"Nuevo telefono:");
			txtCorreo = AgregarTexto(L"Nuevo correo:");
			AgregarBoton(L"Guardar modificacion", gcnew System::EventHandler(this, &FormModificarMedico::Guardar_Click));
		}

	private:
		System::Void Guardar_Click(System::Object^ sender, System::EventArgs^ e) {
			int idesp = 0;
			int id = 0;
			if (GuiUtil::Vacio(txtTel) || GuiUtil::Vacio(txtCorreo) || !GuiUtil::LeerEntero(txtIdEsp, idesp) || !GuiUtil::LeerEntero(txtId, id)) {
				GuiUtil::Aviso(L"Por favor llene todos los campos (los ids deben ser numeros).");
				return;
			}

			CapturaSalida cap;
			arbolMed->ModificarMedico(idesp, id, aStd(txtTel->Text), aStd(txtCorreo->Text), *arbolEsp);
			if (GuiUtil::MostrarResultadoModificar(aNet(cap.Terminar()))) {
				this->Close();
			}
		}
	};

	// ESPECIALIDAD (se modifica la descripcion)
	public ref class FormModificarEspecialidad : public FormCampos {
	private:
		TextBox^ txtId;
		TextBox^ txtDesc;
		ArbolEspecialidad* arbolEsp;

	public:
		FormModificarEspecialidad(ArbolEspecialidad* arbol) : FormCampos(L"Modificar Especialidad") {
			arbolEsp = arbol;

			txtId = AgregarTexto(L"Id de Especialidad:");
			txtDesc = AgregarTexto(L"Nueva descripcion:");
			AgregarBoton(L"Guardar modificacion", gcnew System::EventHandler(this, &FormModificarEspecialidad::Guardar_Click));
		}

	private:
		System::Void Guardar_Click(System::Object^ sender, System::EventArgs^ e) {
			int id = 0;
			if (GuiUtil::Vacio(txtDesc) || !GuiUtil::LeerEntero(txtId, id)) {
				GuiUtil::Aviso(L"Por favor llene todos los campos (el id debe ser un numero).");
				return;
			}

			CapturaSalida cap;
			arbolEsp->ModificarEspecialidad(id, aStd(txtDesc->Text));
			if (GuiUtil::MostrarResultadoModificar(aNet(cap.Terminar()))) {
				this->Close();
			}
		}
	};

	// CITA (se modifican motivo y estado)
	public ref class FormModificarCita : public FormCampos {
	private:
		TextBox^ txtIdPac;
		TextBox^ txtIdMed;
		TextBox^ txtIdCita;
		TextBox^ txtMotivo;
		ComboBox^ cmbEstado;
		ArbolPacientes* arbolPac; // ModificarCita valida paciente y medico con estos
		ArbolMedicos* arbolMed;
		ArbolCitas* arbolCitas;

	public:
		FormModificarCita(ArbolPacientes* arbolP, ArbolMedicos* arbolM, ArbolCitas* arbolC) : FormCampos(L"Modificar Cita") {
			arbolPac = arbolP;
			arbolMed = arbolM;
			arbolCitas = arbolC;

			txtIdPac = AgregarTexto(L"Id de Paciente de la cita:");
			txtIdMed = AgregarTexto(L"Id de Medico de la cita:");
			txtIdCita = AgregarTexto(L"Id de Cita:");
			txtMotivo = AgregarTexto(L"Nuevo motivo:");
			cmbEstado = AgregarLista(L"Nuevo estado:", gcnew cli::array<String^>{ L"0 - Pendiente", L"1 - Confirmada" });
			AgregarBoton(L"Guardar modificacion", gcnew System::EventHandler(this, &FormModificarCita::Guardar_Click));
		}

	private:
		System::Void Guardar_Click(System::Object^ sender, System::EventArgs^ e) {
			int idpac = 0;
			int idmed = 0;
			int idcita = 0;
			if (GuiUtil::Vacio(txtMotivo) || !GuiUtil::LeerEntero(txtIdPac, idpac) || !GuiUtil::LeerEntero(txtIdMed, idmed) || !GuiUtil::LeerEntero(txtIdCita, idcita)) {
				GuiUtil::Aviso(L"Por favor llene todos los campos (los ids deben ser numeros).");
				return;
			}

			int estado = cmbEstado->SelectedIndex;

			CapturaSalida cap;
			arbolCitas->ModificarCita(idpac, idmed, idcita, aStd(txtMotivo->Text), estado, *arbolPac, *arbolMed);
			if (GuiUtil::MostrarResultadoModificar(aNet(cap.Terminar()))) {
				this->Close();
			}
		}
	};

	// HABITACION (se modifica el estado) 
	public ref class FormModificarHabitacion : public FormCampos {
	private:
		TextBox^ txtId;
		ComboBox^ cmbEstado;
		ArbolHabitaciones* arbolHab;

	public:
		FormModificarHabitacion(ArbolHabitaciones* arbol) : FormCampos(L"Modificar Habitacion") {
			arbolHab = arbol;

			txtId = AgregarTexto(L"Id de Habitacion:");
			cmbEstado = AgregarLista(L"Nuevo estado:", gcnew cli::array<String^>{ L"0 - Disponible", L"1 - Ocupada" });
			AgregarBoton(L"Guardar modificacion", gcnew System::EventHandler(this, &FormModificarHabitacion::Guardar_Click));
		}

	private:
		System::Void Guardar_Click(System::Object^ sender, System::EventArgs^ e) {
			int id = 0;
			if (!GuiUtil::LeerEntero(txtId, id)) {
				GuiUtil::Aviso(L"Por favor escriba el id de la habitacion (debe ser un numero).");
				return;
			}

			int estado = cmbEstado->SelectedIndex;

			CapturaSalida cap;
			arbolHab->ModificarHab(id, estado);
			if (GuiUtil::MostrarResultadoModificar(aNet(cap.Terminar()))) {
				this->Close();
			}
		}
	};

	// HOSPITALIZACION (se modifica el motivo)
	public ref class FormModificarHospitalizacion : public FormCampos {
	private:
		TextBox^ txtIdPac;
		TextBox^ txtIdHab;
		TextBox^ txtIdHosp;
		TextBox^ txtMotivo;
		ArbolPacientes* arbolPac; // ModificarHosp valida paciente y habitacion con estos
		ArbolHabitaciones* arbolHab;
		ArbolHospitalizaciones* arbolHosp;

	public:
		FormModificarHospitalizacion(ArbolPacientes* arbolP, ArbolHabitaciones* arbolHa, ArbolHospitalizaciones* arbolHo) : FormCampos(L"Modificar Hospitalizacion") {
			arbolPac = arbolP;
			arbolHab = arbolHa;
			arbolHosp = arbolHo;

			txtIdPac = AgregarTexto(L"Id de Paciente:");
			txtIdHab = AgregarTexto(L"Id de Habitacion:");
			txtIdHosp = AgregarTexto(L"Id de Hospitalizacion:");
			txtMotivo = AgregarTexto(L"Nuevo motivo:");
			AgregarBoton(L"Guardar modificacion", gcnew System::EventHandler(this, &FormModificarHospitalizacion::Guardar_Click));
		}

	private:
		System::Void Guardar_Click(System::Object^ sender, System::EventArgs^ e) {
			int idpac = 0;
			int idhab = 0;
			int idhosp = 0;
			if (GuiUtil::Vacio(txtMotivo) || !GuiUtil::LeerEntero(txtIdPac, idpac) || !GuiUtil::LeerEntero(txtIdHab, idhab) || !GuiUtil::LeerEntero(txtIdHosp, idhosp)) {
				GuiUtil::Aviso(L"Por favor llene todos los campos (los ids deben ser numeros).");
				return;
			}

			CapturaSalida cap;
			arbolHosp->ModificarHosp(idpac, idhab, idhosp, aStd(txtMotivo->Text), *arbolPac, *arbolHab);
			if (GuiUtil::MostrarResultadoModificar(aNet(cap.Terminar()))) {
				this->Close();
			}
		}
	};

	// DIAGNOSTICO (se modifica la descripcion; el id es texto, tipo D001)
	public ref class FormModificarDiagnostico : public FormCampos {
	private:
		TextBox^ txtId;
		TextBox^ txtDesc;
		ArbolDiagnostico* arbolDiag;

	public:
		FormModificarDiagnostico(ArbolDiagnostico* arbol) : FormCampos(L"Modificar Diagnostico") {
			arbolDiag = arbol;

			txtId = AgregarTexto(L"Id de Diagnostico (ejemplo: D001):");
			txtDesc = AgregarTexto(L"Nueva descripcion:");
			AgregarBoton(L"Guardar modificacion", gcnew System::EventHandler(this, &FormModificarDiagnostico::Guardar_Click));
		}

	private:
		System::Void Guardar_Click(System::Object^ sender, System::EventArgs^ e) {
			// el id de diagnostico es string, entonces aca no se pasa a numero
			if (GuiUtil::Vacio(txtId) || GuiUtil::Vacio(txtDesc)) {
				GuiUtil::Aviso(L"Por favor llene todos los campos.");
				return;
			}

			CapturaSalida cap;
			arbolDiag->ModificarDiag(aStd(txtId->Text->Trim()), aStd(txtDesc->Text));
			if (GuiUtil::MostrarResultadoModificar(aNet(cap.Terminar()))) {
				this->Close();
			}
		}
	};

	// TRATAMIENTO (se modifican nombre, descripcion y costo) 
	public ref class FormModificarTratamiento : public FormCampos {
	private:
		TextBox^ txtId;
		TextBox^ txtNombre;
		TextBox^ txtDesc;
		TextBox^ txtCosto;
		ArbolTratamiento* arbolTrata;

	public:
		FormModificarTratamiento(ArbolTratamiento* arbol) : FormCampos(L"Modificar Tratamiento") {
			arbolTrata = arbol;

			txtId = AgregarTexto(L"Id de Tratamiento:");
			txtNombre = AgregarTexto(L"Nuevo nombre:");
			txtDesc = AgregarTexto(L"Nueva descripcion:");
			txtCosto = AgregarTexto(L"Nuevo costo:");
			AgregarBoton(L"Guardar modificacion", gcnew System::EventHandler(this, &FormModificarTratamiento::Guardar_Click));
		}

	private:
		System::Void Guardar_Click(System::Object^ sender, System::EventArgs^ e) {
			int id = 0;
			double costo = 0;
			if (GuiUtil::Vacio(txtNombre) || GuiUtil::Vacio(txtDesc) || !GuiUtil::LeerEntero(txtId, id) || !GuiUtil::LeerDecimal(txtCosto, costo)) {
				GuiUtil::Aviso(L"Por favor llene todos los campos (el id y el costo deben ser numeros).");
				return;
			}
			if (costo < 0) {
				GuiUtil::Aviso(L"El costo no puede ser negativo.");
				return;
			}

			CapturaSalida cap;
			arbolTrata->ModificarTratamiento(id, aStd(txtNombre->Text), aStd(txtDesc->Text), costo);
			if (GuiUtil::MostrarResultadoModificar(aNet(cap.Terminar()))) {
				this->Close();
			}
		}
	};

	// ventana con los botones 

	public ref class FormModificar : public System::Windows::Forms::Form
		// ventana modificar: 10 botones, cada uno abre la ventana de su arbol
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
		// los parametros van en el mismo orden q en FormInsertar
		FormModificar(ArbolPais* arbolP, ArbolCiudad* arbolC, ArbolEspecialidad* arbolE, ArbolCitas* arbolCi, ArbolHabitaciones* arbolHa, ArbolHospitalizaciones* arbolHo, ArbolMedicos* arbolM, ArbolPacientes* arbolPac, ArbolTratamiento* arbolT, ArbolDiagnostico* arbolD) {
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

			this->Text = L"Modificar Registro";
			this->Size = System::Drawing::Size(400, 400);
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;

			cli::array<String^>^ nombres = gcnew cli::array<String^>{L"1. Paises", L"2. Ciudades", L"3. Pacientes", L"4. Medicos", L"5. Especialidades",L"6. Citas", L"7. Habitaciones", L"8. Hospitalizaciones", L"9. Diagnosticos", L"10. Tratamientos" };

			// 10 botones en dos columnas. Todos usan el mismo evento y se distinguen por el Tag (1 a 10)
			for (int i = 0; i < 10; i++) {
				Button^ btn = gcnew Button();
				btn->Text = nombres[i];
				btn->Tag = i + 1;
				btn->Size = System::Drawing::Size(150, 40);
				if (i < 5) {
					btn->Location = System::Drawing::Point(30, 30 + i * 60);
				}
				else {
					btn->Location = System::Drawing::Point(200, 30 + (i - 5) * 60);
				}
				btn->Click += gcnew System::EventHandler(this, &FormModificar::Abrir_Click);
				this->Controls->Add(btn);
			}
		}

	private:
		System::Void Abrir_Click(System::Object^ sender, System::EventArgs^ e) {
			Button^ boton = safe_cast<Button^>(sender);
			int opcion = safe_cast<int>(boton->Tag);

			Form^ ventana = nullptr;

			switch (opcion) {
			case 1:
				ventana = gcnew FormModificarPais(arbolilloPaises);
				break;
			case 2:
				ventana = gcnew FormModificarCiudad(arbolilloPaises, arbolilloCiudades);
				break;
			case 3:
				ventana = gcnew FormModificarPaciente(arbolilloCiudades, arbolilloPac);
				break;
			case 4:
				ventana = gcnew FormModificarMedico(arbolilloEsp, arbolilloMed);
				break;
			case 5:
				ventana = gcnew FormModificarEspecialidad(arbolilloEsp);
				break;
			case 6:
				ventana = gcnew FormModificarCita(arbolilloPac, arbolilloMed, arbolilloCitas);
				break;
			case 7:
				ventana = gcnew FormModificarHabitacion(arbolilloHab);
				break;
			case 8:
				ventana = gcnew FormModificarHospitalizacion(arbolilloPac, arbolilloHab, arbolilloHosp);
				break;
			case 9:
				ventana = gcnew FormModificarDiagnostico(arbolilloDiag);
				break;
			case 10:
				ventana = gcnew FormModificarTratamiento(arbolilloTrata);
				break;
			}

			if (ventana != nullptr) {
				ventana->ShowDialog();
			}
		}
	};
}