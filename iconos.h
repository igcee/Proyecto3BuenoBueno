#pragma once

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class BotonIcono : public System::Windows::Forms::Button
	{
	public:

		// agarra texto que muestra icono, posiciones x/y de donde se dibuja y color de fondo (mas tarde lo cambio para poder meterle una imagen)
		BotonIcono(String^ nombre, int x, int y, Color fondo) {
			this->Text = nombre;
			this->Location = System::Drawing::Point(x, y);
			this->Size = System::Drawing::Size(140, 110);
			this->BackColor = fondo;
			this->ForeColor = Color::FromArgb(0, 40, 100);
			this->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0f, FontStyle::Bold);
			this->TextAlign = ContentAlignment::BottomCenter;
			this->Cursor = Cursors::Hand;

			// esto es para el color del borde, para q no se vea tan feo
			this->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->FlatAppearance->BorderSize = 2;
			this->FlatAppearance->BorderColor = Color::FromArgb(0, 0, 0);

			//imagen del icono que busca iconos/<nombreminuscula>.png o .jpg
			Image^ img = CargarImagen(nombre->ToLower(), 64);
			if (img != nullptr) {
				this->Image = img;
				this->ImageAlign = ContentAlignment::TopCenter;
				this->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
				this->Padding = System::Windows::Forms::Padding(0, 6, 0, 4);
			}

			this->Click += gcnew EventHandler(this, &BotonIcono::Icono_Click);
		}

	private:

		//si no encuentra la imagen devuelve nullptr y el boton se queda solo con texto (no se cae el chunche)
		static Image^ CargarImagen(String^ archivo, int lado) {
			array<String^>^ extensiones = gcnew array<String^>{ L".png", L".jpg", L".jpeg", L".bmp" };
			for each(String ^ ext in extensiones) {
				String^ ruta = Path::Combine(L"iconos", archivo + ext);
				if (File::Exists(ruta)) {
					try {
						//se lee a memoria pq Image::FromFile deja el archivo bloqueado
						MemoryStream^ ms = gcnew MemoryStream(File::ReadAllBytes(ruta));
						Image^ original = Image::FromStream(ms);
						return gcnew Bitmap(original, System::Drawing::Size(lado, lado));
					}
					catch (Exception^) {
						return nullptr;
					}
				}
			}
			return nullptr;
		}

		System::Void Icono_Click(System::Object^ sender, System::EventArgs^ e) {
			MessageBox::Show(L"Como la revolucion industrial inspiro a la obra Cuentos de mi tia Panchita", L"Informacion",MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	};
}