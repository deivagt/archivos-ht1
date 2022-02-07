#include <iostream>
#include <fstream>
using namespace std;

class app {
public:
	app() {
		cout << "Hoja de trabajo 2" << endl;
		cout << "201800523 - David Alberto Avila Belisle" << endl << endl;
		this->crearArchivo();
	}

	void menuPrincipal() {

		
			string opcion;

			cout << "1. Registro estudiante\n";
			cout << "2. Registro profesor\n";
			cout << "3. Ver registros\n";
			cout << "4. salir\n";
			

			do {
				cout << "Elige una opcion: ";
				cin >> opcion;
				if (opcion == "1") {
					break;
				}
				else if (opcion == "2") {
					break;
				}
				else if (opcion  == "3") {
					break;
				}
				else if (opcion == "4") {
					break;
				}
				else if (opcion == "56") {
					this->crearArchivo();
				}
				else  {
					cout << "Opcion invalida\n";
				}
			} while (true);


		

	}


	void crearArchivo() {
		ofstream file;
		file.open("archivo.bin", ios::out | ios::app | ios::binary);
		if (file.fail())
		{
			cout << "Error al crear el fichero" << endl;
			return;
		}

		int tamanio = 5*1024; //tamanio del archivo en mb

		int temporal = 0;// valor para llenar el archivo

		this->llenarArchivo(&temporal, &file, tamanio);		
		
		cout << "escrito " << temporal<<" " << file.tellp() << endl;

		file.close();
	}

	void llenarArchivo(int* temporal,ofstream* file, int tamanio) {
		file->seekp(0, ios::beg);
		for (int i = 0; i < tamanio;i++) {
			file->write((char*)&temporal, 1024);
		}
	}
};