#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class app {
public:

    struct control{
        int64_t espacioDisponible;
    };

    struct profesor{
        int64_t id_profesor;
        char cui [13];
        char nombre[25];
        char curso [25];
        int64_t apuntador;

    };

    struct estudiante{
        int64_t id_estudiante;
        char cui [13];
        char nombre [25];
        char curso [25];
        int64_t apuntador;
    };

	app() {
		cout << "Hoja de trabajo 2" << endl;
		cout << "201800523 - David Alberto Avila Belisle" << endl << endl;
		//this->crearArchivo();
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
				else if (opcion == "5") {
					this->crearArchivo();
				}
				else  {
					cout << "Opcion invalida\n";
				}
			} while (true);




	}


	void crearArchivo() {
		FILE* file;
		try{
		file = fopen("archivo.bin", "wb+");
		}catch(exception e){
            cout << "error"<<endl;
            return;
		}



		int tamanio = 5*1024*1024; //tamanio del archivo en mb

		int temporal = 0;// valor para llenar el archivo

		fseek(file, 0, SEEK_SET);

        for (int i = 0; i < tamanio;i++) {
            this->escribirArchivo((char*)&temporal, file,  1);
		}


		cout << "escrito " << temporal<<" " << ftell(file) << endl;

		//Variable para el control de los espacios
        struct control miControl;
        miControl.espacioDisponible = 1;

        //Variable para iniciar el archivo
        struct estudiante primerEstudiante;
        int64_t id = 201800523;
        string cui ="3358868681901";
        string nombre = "David Avila";
        string curso = "archivos";

        primerEstudiante.id_estudiante = id;
        strcpy(primerEstudiante.cui,cui.c_str());
        strcpy(primerEstudiante.nombre,nombre.c_str());
        strcpy(primerEstudiante.curso,curso.c_str());
        primerEstudiante.apuntador = 26;

        //proceso de escribir el primer dato

		fseek(file, 0, SEEK_SET);//posicionarme al inicio del archivo

		this->escribirArchivo((char*)&miControl, file,  sizeof(control));

		//mover puntero al siguiente espacio disponible
		fseek(file, sizeof(miControl), SEEK_SET);

		char* buffer = new char[sizeof(primerEstudiante)];

        memcpy(buffer, &primerEstudiante, sizeof(struct estudiante));


		this->escribirArchivo(buffer, file,  sizeof(struct estudiante));

        fclose(file);

        file = fopen("archivo.bin", "rb+");
        fseek(file, sizeof(miControl), SEEK_SET);
        struct estudiante est;

        this->leer((char*)&est,file,sizeof(struct estudiante));
        cout<< "lectura: "<<est.id_estudiante<<endl;



	}

	void escribirArchivo(char* temporal,FILE* file,  int bytes) {
        try{
            fwrite(temporal,bytes, 1,file);
        }catch(exception e){
            cout << "error al escribir" <<endl;
        }

	}

	void leer(char* temporal,FILE* file,  int bytes) {
        try{
            fread(temporal,bytes, 1,file);
        }catch(exception e){
            cout << "error al escribir" <<endl;
        }

	}
};
