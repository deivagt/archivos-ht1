#include <iostream>
#include <fstream>
#include <cstring>
#include<stdio.h>
using namespace std;

class app {
public:

    struct control{
        int64_t siguiente;
    };

    struct profesor{
        int64_t id_profesor;
        char cui [13];
        char nombre[25];
        char curso [25];

    };

    struct estudiante{
        int64_t id_estudiante;
        char cui [13];
        char nombre [25];
        char carne [10];
    };

    struct metaData{
        char tipo;
    };

	app() {

		//this->crearArchivo();
	}

	void menuPrincipal() {


			string opcion;

			do {
                this->encabezado();
                cout << "1. Registro estudiante\n";
                cout << "2. Registro profesor\n";
                cout << "3. Ver registros\n";
                cout << "4. salir\n";
				cout << "Elige una opcion: ";
				cin >> opcion;
				if (opcion == "1") {
                    agregarEstudiante();
				}
				else if (opcion == "2") {
					agregarProfesor();
				}
				else if (opcion  == "3") {
					verRegistros();
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



		int tamanio = 2*1024*1024; //tamanio del archivo en mb

		int temporal = 0;// valor para llenar el archivo

		fseek(file, 0, SEEK_SET);

        for (int i = 0; i < tamanio;i++) {
            this->escribirArchivo((char*)&temporal, file,  1);
		}


		cout << "escrito " << temporal<<" " << ftell(file) << endl;

		//Variable para el control de los espacios
        struct control siguiente;
        //siguiente.siguiente = sizeof(control)+sizeof(struct metaData) +sizeof(struct estudiante);
        siguiente.siguiente = sizeof(control);
        fseek(file, 0, SEEK_SET);//posicionarme al inicio del archivo

		this->escribirArchivo((char*)&siguiente, file,  sizeof(control));
		fclose(file);

        /*//Variable de tipo
        struct metaData tipo;
        tipo.tipo = 'e';



        //Variable para iniciar el archivo
       /* struct estudiante primerEstudiante;
        int64_t id = sizeof(control)+1;//El id es la siguiente posicion disponible
        string cui ="335886868190";
        string nombre = "David Avila";
        string carne = "201800523";

        primerEstudiante.id_estudiante = id;
        strcpy(primerEstudiante.cui,cui.c_str());
        strcpy(primerEstudiante.nombre,nombre.c_str());
        strcpy(primerEstudiante.carne,carne.c_str());*/

        //proceso de escribir el primer dato



		//insertar tipo

		//this->escribirArchivo((char*)&tipo, file,  sizeof(metaData));

		//insertar estudiante

		/*char* buffer = new char[sizeof(primerEstudiante)];
        memcpy(buffer, &primerEstudiante, sizeof(struct estudiante));
		this->escribirArchivo(buffer, file,  sizeof(struct estudiante));
        */




       /* file = fopen("archivo.bin", "rb+");
        fseek(file, 0, SEEK_SET);

        struct control otro;


        this->leer((char*)&otro,file,sizeof(struct control));

        int64_t pos =otro.siguiente;
        cout << "posicion leida "<< pos<<endl;
        fseek(file, otro.siguiente-sizeof(struct estudiante), SEEK_SET);
        struct estudiante est;

        this->leer((char*)&est,file,sizeof(struct estudiante));
        cout<< "lectura: "<<est.cui<<endl;

        */
	}

	void agregarEstudiante(){
	    struct estudiante nuevoEstudiante;
	    int sigTemp = obtenerSiguiente();

	    string cui;
        string nombre;
        string carne;

        this->encabezado();
        cout << "BIENVENIDO A LA INTERFAZ DE INGRESO DE ESTUDIANTE\n";
        cout<<"Ingresa los datos del estudiante: \n";
        cout <<"Cui: ";cin>>cui;cout<<endl;
        cout <<"Nombre: ";cin>>nombre;cout<<endl;
        cout <<"Carne: ";cin>>carne;cout<<endl;

        nuevoEstudiante.id_estudiante = sigTemp+sizeof(struct metaData);
        strcpy(nuevoEstudiante.cui,cui.c_str());
        strcpy(nuevoEstudiante.nombre,nombre.c_str());
        strcpy(nuevoEstudiante.carne,carne.c_str());

        //crear tipo
        struct metaData tipo;
        tipo.tipo = 'e';

        //Insercion
        FILE* file;
	    file = fopen("archivo.bin", "rb+");
        fseek(file, sigTemp, SEEK_SET);

        //Insertar tipo

        this->escribirArchivo((char*)&tipo, file,  sizeof(metaData));

        //Insertar valor
        char* buffer = new char[sizeof(nuevoEstudiante)];
        memcpy(buffer, &nuevoEstudiante, sizeof(struct estudiante));
		this->escribirArchivo(buffer, file,  sizeof(struct estudiante));


		//Actualizar posicion siguientre
		this->actualizarSiguiente(sigTemp+sizeof(struct estudiante)+sizeof(struct metaData));

        fclose(file);

        cout<< "posicion siguiente: " <<obtenerSiguiente()<<endl;

	}

	void agregarProfesor(){
	    struct profesor nuevoProfesor;
	    int sigTemp = obtenerSiguiente();

	    string cui;
        string nombre;
        string curso;

        this->encabezado();
        cout << "BIENVENIDO A LA INTERFAZ DE INGRESO DE PROFESOR\n";
        cout<<"Ingresa los datos del profesor: \n";
        cout <<"Cui: ";cin>>cui;cout<<endl;
        cout <<"Nombre: ";cin>>nombre;cout<<endl;
        cout <<"Curso: ";cin>>curso;cout<<endl;

        nuevoProfesor.id_profesor = sigTemp+sizeof(struct metaData);
        strcpy(nuevoProfesor.cui,cui.c_str());
        strcpy(nuevoProfesor.nombre,nombre.c_str());
        strcpy(nuevoProfesor.curso,curso.c_str());

        //crear tipo
        struct metaData tipo;
        tipo.tipo = 'p';

        //Insercion
        FILE* file;
	    file = fopen("archivo.bin", "rb+");
        fseek(file, sigTemp, SEEK_SET);

        //Insertar tipo

        this->escribirArchivo((char*)&tipo, file,  sizeof(metaData));

        //Insertar valor
        char* buffer = new char[sizeof(nuevoProfesor)];
        memcpy(buffer, &nuevoProfesor, sizeof(struct profesor));
		this->escribirArchivo(buffer, file,  sizeof(struct profesor));


		//Actualizar posicion siguientre
		this->actualizarSiguiente(sigTemp+sizeof(struct profesor)+sizeof(struct metaData));

        fclose(file);

        cout<< "posicion siguiente: " <<obtenerSiguiente()<<endl;

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

	void verRegistros(){
	    this->encabezado();
	    cout<<"REGISTROS"<<endl;
        FILE* file;
	    file = fopen("archivo.bin", "rb+");
        fseek(file, sizeof(struct control), SEEK_SET);

        struct metaData tipo;
        struct estudiante est;
        struct profesor prof;
        int contador = 1;

        while(true){
            this->leer((char*)&tipo,file,sizeof(struct metaData));

            if(tipo.tipo=='e'){

                this->leer((char*)&est,file,sizeof(struct estudiante));
                cout<<contador<<") "<< "Estudiante: id: "<<  est.id_estudiante<< " Cui: " << est.cui<< " Nombre: " << est.nombre<< " Carne: " <<est.carne<< endl;


            }else if(tipo.tipo=='p'){
                this->leer((char*)&prof,file,sizeof(struct profesor));
                cout<<contador<<") "<< "Profesor: id: " << prof.id_profesor<< " Cui: " << prof.cui<< " Nombre: " << prof.nombre<< " Curso: " <<prof.curso<< endl;

            }else{
                cout<<tipo.tipo<<"\n";
                break;
            }
            contador++;
        }


        fclose(file);

        cout << "ingresa 1 para continuar...";
        string c;
        cin >>c;

	}

	int64_t obtenerSiguiente(){
	    FILE* file;
	    file = fopen("archivo.bin", "rb+");
        fseek(file, 0, SEEK_SET);

        struct control otro;

        this->leer((char*)&otro,file,sizeof(struct control));

        int64_t pos =otro.siguiente;

        fclose(file);

        return pos;
	}
	void actualizarSiguiente(int64_t nuevoValor){
	    FILE* file;
	    file = fopen("archivo.bin", "rb+");
        fseek(file, 0, SEEK_SET);
        struct control siguiente;
        siguiente.siguiente = nuevoValor;
        this->escribirArchivo((char*)&siguiente, file,  sizeof(control));
        fclose(file);

	}


	void encabezado(){
        system("clear");
		cout << "Hoja de trabajo 2" << endl;
		cout << "201800523 - David Alberto Avila Belisle" << endl << endl;
    }
};
