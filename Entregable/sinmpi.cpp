
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;
int matriz[1001][801];
int main( int argc, char* argv[])
{
    string archivo1 = argv[1];
    string archivo2 = argv[2];
    string line;
    string line2;
    string hilerafilas;
    string hileracolumnas;
    cout << archivo1<< endl;
    cout << archivo2<< endl;

    ifstream file1;
    file1.open(archivo1.c_str());
    while (getline(file1, line2)){

        hilerafilas = line2;

    }
    file1.close();

    ifstream file2;
    file2.open(archivo2.c_str());
    while (getline(file2, line)){

        hileracolumnas = line;

    }
    file2.close();

    int division = 4;
    cout << "Cant columnas: " << hileracolumnas.length();
    cout << endl;
    cout << "Cant filas: " << hilerafilas.length() << endl;
    int columnas = hileracolumnas.length() + 1;
    int filas = hilerafilas.length() + 1;
    int Match;
    int Delete;
    int Insert;
    int bandera;

    // Inicializa los valores
    for(int i = 0; i <= filas; i++){
            for(int j = 0; j <= columnas; j++){
                        matriz[i][j] = 0;
        }
    }

    for(int j = 0; j <= columnas; j++){
        matriz[0][j] = j;
        //cout << j << " ";
    }
    for(int i = 0; i <= filas; i++){
        matriz[i][0] = i;
        //cout << i << endl;
    }

    // Evalua casos
    for(int i = 1; i <= filas; i++){
        //cout << "------------------------------------" << endl;
        for(int j = 1; j <= columnas; j++){
            //cout << "------------------------------------" << endl;
            if(hilerafilas[i - 1] != hileracolumnas[j - 1]){
                //cout << hilerafilas[i - 1]<< hileracolumnas[j-1]<<endl;
                //cout << "diferentes"<< endl;
                bandera = 1;
            }else {
                bandera = 0;
                //cout << hilerafilas[i - 1]<< hileracolumnas[j-1]<<endl;
                //cout << "IGUALES"<< endl;
                }
            Match = matriz[i-1][j-1] + bandera;
            //cout << "M: " << Match << endl;
            Delete = matriz[i - 1][j] + 1;
            //cout << "D " <<Delete << endl;
            Insert = matriz[i][j - 1] + 1;
            //cout << "I " << Insert << endl;
            matriz[i][j] = min(min(Match, Insert), Delete);
            
        }
    }

/* Para imprimir la matriz
    for(int i = 0; i <= filas; i++){
            //cout << "hilerafilas: "<<hilerafilas[i] << " " ;
            //cout << endl << "hileracolumnas: " << hileracolumnas[i] << endl;
        for(int j = 0; j <= columnas; j++){
            cout << matriz[i][j];
            cout << " ";
        }
        cout << endl;
    }
*/
    cout << "El resultado minimo de comparar h1 con h2 es " << matriz[filas][columnas] << endl;
    return 0;
}

