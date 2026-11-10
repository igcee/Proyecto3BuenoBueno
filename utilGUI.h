#define _HAS_STD_BYTE 0
// ^esto es pa el error de C2872
#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <msclr/marshal_cppstd.h>

// PARTE NATIVA

class CapturaSalida {
private:
	std::ostringstream buffer;
	std::streambuf* anterior;
	bool activa;

public:
	CapturaSalida() {
		anterior = std::cout.rdbuf(buffer.rdbuf());
		activa = true;
	}

	std::string Terminar() {
		if (activa) {
			std::cout.rdbuf(anterior);
			activa = false;
			std::cout << buffer.str();
		}
		return buffer.str();
	}

	~CapturaSalida() { // por si se olvida llamar Terminar, q el cout no se quede roto
		if (activa) {
			std::cout.rdbuf(anterior);
		}
	}
};

// pasar de texto de ventana a string normalito y al reves
inline std::string aStd(System::String^ s) {
	return msclr::interop::marshal_as<std::string>(s);
}

inline System::String^ aNet(const std::string& s) {
	return msclr::interop::marshal_as<System::String^>(s);
}

// PARTE DE VENTANAS

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	// funciones sueltas para validar lo q escribe el usuario
	public ref class GuiUtil abstract sealed {
	public:
		// true si la cajita esta vacia (o solo espacios)
		static bool Vacio(TextBox^ t) {
			return String::IsNullOrWhiteSpace(t->Text);
		}

		// intenta pasar la cajita a int. Si el usuario escribio letras devuelve false (en vez de tirar excepcion y cerrar todo)
		static bool LeerEntero(TextBox^ t, int% valor) {
			return Int32::TryParse(t->Text->Trim(), valor);
		}

		// igual pero para decimales- acepta 1500.50 y 1500,50
		static bool LeerDecimal(TextBox^ t, double% valor) {
			String^ s = t->Text->Trim()->Replace(L',', L'.');
			return Double::TryParse(s, System::Globalization::NumberStyles::Float, System::Globalization::CultureInfo::InvariantCulture, valor);
		}

		static void Aviso(String^ mensaje) {
			MessageBox::Show(mensaje, L"Atencion", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}

		static void MostrarError(String^ mensaje, String^ titulo) {
			MessageBox::Show(mensaje, titulo, MessageBoxButtons::OK, MessageBoxIcon::Error);
		}

		// recibe lo q imprimio el metodo Modificar del arbol y lo muestra. Todos los mensajes de exito
		// de los Modificar dicen "modificad..." (modificado/modificada), los de error no.
		// Devuelve true si se modifico, para saber si cerrar la ventana
		static bool MostrarResultadoModificar(String^ texto) {
			String^ t = texto->Trim();
			if (t->Contains(L"modificad")) {
				MessageBox::Show(t, L"Modificacion exitosa", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return true;
			}
			if (t->Length == 0) {
				t = L"No se pudo realizar la modificacion.";
			}
			MessageBox::Show(t, L"No se pudo modificar", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return false;
		}
	};

	// Ventana base para insertar y modificar. En vez de poner a mano la posicion de cada etiqueta y
	// cajita, se llama AgregarTexto / AgregarLista / etc. y ella las va acomodando una debajo de otra.
	// Si hay muchos campos pasa a una segunda columna (pq no da para ventanas muy altas).
	public ref class FormCampos : public System::Windows::Forms::Form {
	protected:
		int posX; // columna actual
		int posY; // altura del siguiente campo
		int maxY; // lo mas abajo q ha llegado alguna columna

		FormCampos(String^ titulo) {
			this->Text = titulo;
			this->StartPosition = FormStartPosition::CenterParent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			posX = 30;
			posY = 20;
			maxY = 20;
		}

		// si el siguiente campo ya no cabe en la columna, se pasa a otra
		void RevisarEspacio(int altoNecesario) {
			if (posY + altoNecesario > 400) {
				posX += 310;
				posY = 20;
			}
		}

		void PonerEtiqueta(String^ texto) {
			RevisarEspacio(60);
			Label^ lbl = gcnew Label();
			lbl->Text = texto;
			lbl->AutoSize = true;
			lbl->Location = System::Drawing::Point(posX, posY);
			this->Controls->Add(lbl);
			posY += 20;
		}

		void TerminarCampo(int alto) {
			posY += alto;
			if (posY > maxY) {
				maxY = posY;
			}
		}

		TextBox^ AgregarTexto(String^ etiqueta) {
			PonerEtiqueta(etiqueta);
			TextBox^ txt = gcnew TextBox();
			txt->Location = System::Drawing::Point(posX, posY);
			txt->Width = 260;
			this->Controls->Add(txt);
			TerminarCampo(40);
			return txt;
		}

		// lista desplegable (solo deja escoger, no escribir)
		ComboBox^ AgregarLista(String^ etiqueta, cli::array<String^>^ opciones) {
			PonerEtiqueta(etiqueta);
			ComboBox^ cmb = gcnew ComboBox();
			cmb->DropDownStyle = ComboBoxStyle::DropDownList;
			for each (String ^ opcion in opciones) {
				cmb->Items->Add(opcion);
			}
			cmb->SelectedIndex = 0;
			cmb->Location = System::Drawing::Point(posX, posY);
			cmb->Width = 260;
			this->Controls->Add(cmb);
			TerminarCampo(40);
			return cmb;
		}

		// calendario para escoger fecha
		DateTimePicker^ AgregarFecha(String^ etiqueta) {
			PonerEtiqueta(etiqueta);
			DateTimePicker^ dtp = gcnew DateTimePicker();
			dtp->Format = DateTimePickerFormat::Custom;
			dtp->CustomFormat = L"d/M/yyyy";
			dtp->Location = System::Drawing::Point(posX, posY);
			dtp->Width = 260;
			this->Controls->Add(dtp);
			TerminarCampo(40);
			return dtp;
		}

		CheckBox^ AgregarCheck(String^ texto) {
			RevisarEspacio(30);
			CheckBox^ chk = gcnew CheckBox();
			chk->Text = texto;
			chk->AutoSize = true;
			chk->Location = System::Drawing::Point(posX, posY);
			this->Controls->Add(chk);
			TerminarCampo(30);
			return chk;
		}

		// el boton va al final y ajusta el tamano de la ventana a lo q se agrego
		Button^ AgregarBoton(String^ texto, System::EventHandler^ evento) {
			Button^ btn = gcnew Button();
			btn->Text = texto;
			btn->Size = System::Drawing::Size(160, 32);
			btn->Location = System::Drawing::Point(posX + 50, posY + 5);
			btn->Click += evento;
			this->Controls->Add(btn);
			this->AcceptButton = btn; // con Enter tambien guarda

			int alto = posY + 45;
			if (maxY > alto) {
				alto = maxY;
			}
			this->ClientSize = System::Drawing::Size(posX + 320, alto + 20);
			return btn;
		}

		// fecha escogida a texto d/m/aaaa
		static String^ FechaATexto(DateTimePicker^ dtp) {
			return dtp->Value.ToString(L"d'/'M'/'yyyy", System::Globalization::CultureInfo::InvariantCulture);
		}
	};
}