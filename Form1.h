#pragma once

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			ConstruirInterfaz();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
		MenuStrip^ menuPrincipal;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font; // chunches de escalado para otros monitores y yo q se
			this->ClientSize = System::Drawing::Size(1280, 720);// resu en X / Y
			this->Name = L"Form1"; // nombre variable, no de nombre de ventana
			this->Text = L"Sistema de Gestion Hospitalaria - Hospital San Rafael"; // este si nombre de ventana
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->BackColor = System::Drawing::Color::FromArgb(0, 69, 153); // color fondo

		}
#pragma endregion




		void ConstruirMenu() {
			menuPrincipal = gcnew MenuStrip();
			array<String^>^ acciones = gcnew array<String^>{L"Insercion", L"Eliminacion", L"Modificacion", L"Consultas (Busquedas)" };
			array<String^>^ entidades = gcnew array<String^>{L"Paises", L"Ciudades", L"Pacientes", L"Medicos", L"Especialidades", L"Citas", L"Habitaciones", L"Hospitalizaciones", L"Diagnosticos", L"Tratamientos" };
			ToolStripMenuItem^ mMantenimiento = gcnew ToolStripMenuItem(L"Mantenimiento");

			for (int i = 0; i < acciones->Length; i++) {
				// insertar / modificar / eliminar / buscar
				ToolStripMenuItem^ mAccion = gcnew ToolStripMenuItem(acciones[i]);

				for (int j = 0; j < entidades->Length; j++) {
					// paises / ciudades / pacientes / ...
					ToolStripMenuItem^ mEntidad = gcnew ToolStripMenuItem(entidades[j]);
					mEntidad->Tag = acciones[i] + L" - " + entidades[j];   // para saber cual se toco
					mEntidad->Click += gcnew EventHandler(this, &Form1::Opcion_Click);
					mAccion->DropDownItems->Add(mEntidad);
				}

				mMantenimiento->DropDownItems->Add(mAccion);
			}

			menuPrincipal->Items->Add(mMantenimiento);

			this->MainMenuStrip = menuPrincipal;
			this->Controls->Add(menuPrincipal);
		}

		System::Void Opcion_Click(System::Object^ sender, System::EventArgs^ e) {
			// esto es solo temporal, pq luego no me acuerdo q servia y q no :P
			ToolStripMenuItem^ item = safe_cast<ToolStripMenuItem^>(sender);
			MessageBox::Show(item->Tag->ToString() + L": aun no implementado.", L"Informacion",
				MessageBoxButtons::OK, MessageBoxIcon::Information);
		}

		void ConstruirInterfaz() {
			ConstruirMenu();
		}

		System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
		}
	};
}

