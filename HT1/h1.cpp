#include <iostream>
#include <fstream>
#include <cstdio>
#include "stdlib.h"
#include <ctime>
#include <cstdlib>
#include <string>
#include <string.h>
#include <sys/stat.h>

using namespace std;

int puntero = 0;
int countp = 0;

typedef struct{
    int Tipo;
    int Id;
    char CUI[15];
    char Nombre[25];
    char Curso[25];
} Objeto;

void crear_archivo(int tamanio, char dim);
void mostrar_struct(Objeto ejm);
void obtener_puntero();
void count_obj_puntero(Objeto ejm);

void crear_archivo(int tamanio, char dim){
    struct stat buffer;
    if ( !stat( "HT1.dsk" , &buffer ) ){
        return ;
    }

    int size_file = 0;
    if ( dim == 'K' || dim == 'k' ) {
        size_file = tamanio;
    }else if( dim == 'M' || dim == 'm' ){
        size_file = tamanio * 1024;
    }else if( dim == 'G' || dim == 'g'){
        size_file = tamanio * 1024 * 1024;
    }
    
    char bloque[1024];
    for ( int i = 0; i < 1024; i++ ){
        bloque[i] = '\0';
    }
    int limite = 0;
    FILE * archivo_binario;
    archivo_binario = fopen("HT1.dsk", "w");

    while( limite != size_file ){
        fwrite(&bloque, 1024, 1, archivo_binario);
        limite++;
    }
    fclose(archivo_binario);
}

void mostrar_struct(Objeto ejm){
    if(ejm.Id != 0 && ejm.CUI != "" && ejm.Nombre != "" && ejm.Curso != ""){
        cout << "ID: ";
        cout << ejm.Id;
        cout << ", CUI: ";
        cout << ejm.CUI;
        cout << ", Nombre: ";
        cout << ejm.Nombre;
        cout << ", Curso: ";
        cout << ejm.Curso << endl;
    }
}

void obtener_puntero(){
    FILE *archivo_binario;
    Objeto ejm;
    archivo_binario = fopen("HT1.dsk", "rb+");
    while (!feof(archivo_binario)){
        fseek(archivo_binario,countp*sizeof(Objeto), SEEK_SET);
        fread(&ejm, sizeof(ejm), 1, archivo_binario);
        count_obj_puntero(ejm);
        countp++;
    }
    countp = 0;
    fclose(archivo_binario);
}

void count_obj_puntero(Objeto ejm){
    if(ejm.Id != 0 && ejm.CUI != "" && ejm.Nombre != "" && ejm.Curso != ""){
        puntero ++;
    }
}

int main() {
    crear_archivo( 100 , 'k');
    obtener_puntero();
    
    string opcion = "", opcionsub = "";
    string id = "", cui = "", nombre = "", curso = "";
    int eleccion = 0, cont = 0;
    char dim = 0;
    FILE *archivo_binario;
    Objeto obj, aux;

    while( eleccion != 4 ){
        cout << "------------------------------------------" << endl;
        //cout << "------------------------------------------" << endl;
        cout << "      Selecciona una opcion:              " << endl << endl;
        cout << "      1. Ingreso de Profesor              " << endl;
        cout << "      2. Ingreso de Estudiante            " << endl;
        cout << "      3. Ver Registros                    " << endl;
        cout << "      4. Salir                            " << endl;
        //cout << "------------------------------------------" << endl;
        cout << "Ingrese una Opcion:";
        getline(cin, opcion);
        eleccion = atoi( opcion.c_str() );

        switch( eleccion ){
            case 1:
                cout << "-----------------------------------------" << endl;
                cout << "         Ingreso de Profesor             " << endl;
                //cout << "-----------------------------------------" << endl;
                cout << "Ingrese ID: ";
                getline(cin, id);
                cout << "Ingrese CUI: ";
                getline(cin, cui);
                cout << "Ingrese Nombre: ";
                getline(cin, nombre);
                cout << "Ingrese Curso: ";
                getline(cin, curso);
                
                archivo_binario = fopen("HT1.dsk", "rb+");

                obj.Tipo = 0;
                obj.Id = atoi(id.c_str());
                strcpy( obj.CUI , cui.c_str() );
                strcpy( obj.Nombre , nombre.c_str() );
                strcpy( obj.Curso , curso.c_str() );

                fseek( archivo_binario,sizeof(Objeto) * puntero,  SEEK_SET );
                fwrite( &obj, sizeof(obj) , 1, archivo_binario);
                id = ""; cui = ""; nombre = ""; curso = "";
                puntero = puntero + sizeof(Objeto);
                fclose(archivo_binario);
                break;

            case 2:

                cout << "-----------------------------------------" << endl;
                cout << "         Ingreso de Estudiante           " << endl;
                //cout << "-----------------------------------------" << endl;
                cout << "Ingrese ID: ";
                getline(cin, id);
                cout << "Ingrese CUI: ";
                getline(cin, cui);
                cout << "Ingrese Nombre: ";
                getline(cin, nombre);
                cout << "Ingrese Carnet: ";
                getline(cin, curso);
                
                archivo_binario = fopen("HT1.dsk", "rb+");

                obj.Tipo = 1;
                obj.Id = atoi(id.c_str());
                strcpy( obj.CUI , cui.c_str() );
                strcpy( obj.Nombre , nombre.c_str() );
                strcpy( obj.Curso , curso.c_str() );

                fseek( archivo_binario,sizeof(Objeto) * puntero,  SEEK_SET );
                fwrite( &obj, sizeof(obj) , 1, archivo_binario);
                id = ""; cui = ""; nombre = ""; curso = "";
                puntero = puntero + sizeof(Objeto);
                fclose(archivo_binario);
                break;

            case 3:
                cout << "-----------------------------------------" << endl;
                cout << "  Ver todos los registros en el archivo  " << endl << endl;
                //cout << "-----------------------------------------" << endl;
                archivo_binario = fopen("HT1.dsk", "rb+");

                //cout << "-----------------------------------------" << endl;
                cout << "               PROFESORES:               " << endl;
                while (!feof(archivo_binario)){
                    fseek(archivo_binario,cont*sizeof(Objeto), SEEK_SET);
                    fread(&obj, sizeof(obj), 1, archivo_binario);
                    
                    if(obj.Id != 0 && obj.CUI != "" && obj.Nombre != "" && obj.Curso != ""){
                        if ( obj.Tipo == 0 ){
                            cout << "ID: ";
                            cout << obj.Id;
                            cout << ", CUI: ";
                            cout << obj.CUI;
                            cout << ", Nombre: ";
                            cout << obj.Nombre;
                            cout << ", Curso: ";
                            cout << obj.Curso << endl;   
                        }
                    }
                    cont++;
                }
                cont = 0;
                fclose(archivo_binario);

                archivo_binario = fopen("HT1.dsk", "rb+");
                //cout << "-----------------------------------------" << endl;
                cout << endl;
                cout << "               ESTUDIANTES:               " << endl ;
                while (!feof(archivo_binario)){
                    fseek(archivo_binario,cont*sizeof(Objeto), SEEK_SET);
                    fread(&obj, sizeof(obj), 1, archivo_binario);
                    
                    if(obj.Id != 0 && obj.CUI != "" && obj.Nombre != "" && obj.Curso != ""){
                        if ( obj.Tipo == 1 ){
                            cout << "ID: ";
                            cout << obj.Id;
                            cout << ", CUI: ";
                            cout << obj.CUI;
                            cout << ", Nombre: ";
                            cout << obj.Nombre;
                            cout << ", Carnet: ";
                            cout << obj.Curso << endl;   
                        }
                    }
                    cont++;
                }
                cont = 0;
                fclose(archivo_binario);
                break;
        }
    }
    return 0;
}