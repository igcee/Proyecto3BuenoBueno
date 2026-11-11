#pragma once

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class Consola {
	private:
		RichTextBox^ caja;

	public:
		RichTextBox^ Crear() {
			caja = gcnew RichTextBox();
			caja->Dock = DockStyle::Bottom;
			caja->Height = 200;
			caja->ReadOnly = true;
			caja->BackColor = Color::FromArgb(5, 79, 156);
			caja->ForeColor = Color::FromArgb(120, 255, 120);
			caja->Font = gcnew System::Drawing::Font(L"Consolas", 10.0f);
			caja->BorderStyle = System::Windows::Forms::BorderStyle::None;
			caja->ScrollBars = RichTextBoxScrollBars::Vertical;
			caja->TabStop = false;
			return caja;
		}


void Escribir(String^ texto) {
	if (caja == nullptr) {
		return;
	}
	caja->AppendText(texto);
	if (caja->IsHandleCreated) {
		caja->ScrollToCaret();
		}
}

void Linea(String^ texto) {
	Escribir(texto + L"\n");
}

void IrAlFinal() {
	if (caja == nullptr) {
		return;
	}
	else {
		caja->SelectionStart = caja->TextLength;
		caja->ScrollToCaret();
	}

}
};
}
