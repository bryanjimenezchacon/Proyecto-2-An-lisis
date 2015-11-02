#include <iostream>
#include <mpi.h>
#include <string>

using namespace std;
int matriz[1001][801];
    const int NW_LIMIT = 8;// Limite procesos
    string h1 = "CTCATCAACGCAGCTAAAGTTCAGATCCTTCTCCAGCGCTAAGGTCATTGTTACGCAAGCCTTACGAACGGTGACCGGCTGTTGACACGACCGTCACCCTCAAATTATAGGCGCACACTAACACCGGCCAGGTTAGTAAAGGGGTAGCTTATCATGAATTACGCTGCTGATCTTACAATAAGACTGGTTTTATAGCCTCCAGAGCCTGACTGGCACTAAGCGGAGCTGCCCTCTCGTCAACTGGTACCTACATAAACCATGCAACCCTACGGGGTGAATGTGACTAATAAATGCTTCTTACGTCGAAGTTTTGGCAGATCCACGGAGTTTTTTATTAAAGTAATTTTCGCTGTCATGTACCTACGAACTTAATATCGGAGGAGAATTCGAACCGCTTTGCGTAACCTTGTATACGGGACGACTATTGTCATTGCTCTCAAATGGTGACGGGTCGAAGAATCAGTGCCTGCCGACTCATTGGGGTCGTGCTTTTAATCTCAAGCACCACACGCTCGAACATGTACCCTGTGGGAGGCGAAATTGTGTTAATGGGGGCGTATGAATATATCTACTTAGCTGAGGTACGATCGCAAGAGTCGTCCAAGTAATAGGGCCTAGTCCAAGGTTGAAATCCCAGGGGGACTTACTTAGCCGTCTTGGCCCGGTCGCGCGGACCTAAATATGCTCGATGCAAGAAACTCGGAAGTTATCACAAAAACAATGTTTTGGAGAGCATAATGCCGTGTTGCGCGTGGTTGCAACGATCAAAGAGATTTAGGAATAGCGTTTTAAAGTATGAC";
    string h2 = "GGTGAGGCTTGCGATATAAATTTTAAGGCGTAGAGAGGCCCGCACTCATTAGGTTCTTTAGCCTGCCCCCTCAGGCCACCCTTATTAGGAGGGTGGTGAAATACGGAAATGATACAATGTGTCCTAAGACATAACCAAGACATGTAGGTCCTTGAGATTCAAATCCGATCGCGGGACGACTATCATCAGGTAGAGCCCACAGAGTCGTCGGAAGCTGGTGAGTGCAAGGTGAAAGTGGTTCGACAGTTGTCGGTTTATTAGGCTGGGATAAACTTGCCACGATGATTAGTCAATGCTCACGGTCTCCAGTAGAGTTTTTGCTGTTGCTAATATATTCATAGTGAGAAGCCCTATGAACATGTGTGACTGTGTCGAGCCAATGTGACAGAATGAGTGAGAATAGGTACACATCCGTTCCCAAATATTTCACCTTAACCTACGTAAAATCTAGACTCTCAGGTGGCGACTTGAGATGTTACCTATGCTTTCGTTTCTCGACAACGGGCGTGGGACCAAATATAAACTGGGTCGTACATAATTTCAACACTACCGAGATTGTTGTATATCATAGCCGAGCAATCCATTGTCGACTAACAGCGAGGTAATTCTGAGATCTCCGTCTATGAATTGATTTGGAAACATCTTGGGTAATAAGAACCCATAAGACTTCTCAGCCTGGTCAAGATAGCAATGGTTCAAAGCGACCCACTCAGATACGATTGATGATAATGCACGCCCATTGCATAGGGCACATGGCTCTATCTTCTTCTCGCATGCAGCCACAAGAAATTTATCATATTTTGTTATGGCATGGTATGAGACTATCGGGTGGGCTGGGAATGACACGATCTTTATCCCTCCTGCCGGTTCTTGACACCTATTCCGGAGGCCATCTAATCCAGTCACCGGGGGAGGGCCTTAGCCCTCGCTGGGCCATTGGTTCGGCTCATATAAAGCATCGTTGGTCGCAACGGACGGGACGCGCTGGACGCATAACTGT";
    int filas = 5;
    int columnas = 8;

    int columnasPorProceso = columnas/NW_LIMIT;
    int Match;
    int Delete;
    int Insert;
    bool banderaCrearMatriz =  true;
    int bandera;
    int contador_nw = 0; 
 void prepararMatriz(){
    banderaCrearMatriz = false;
 		cout << " entre a preparar matiz " << endl;
     // Inicializa la matriz en 0
    for(int i = 0; i <= filas; i++){

            for(int j = 0; j <= columnas; j++){
                        matriz[i][j] = 0;
        }
    }

    
	//Crea la primera fila y columna
    for(int j = 0; j <= filas; j++){
        matriz[j][0] = j;
        //cout << j << " ";
    }
    for(int i = 0; i <= columnas; i++){
        matriz[0][i] = i;
        //cout << i << endl;
    }

    // for(int i = 0; i <= filas; i++){// Imprime la MATRIZ
    //         //cout << "h1: "<<h1[i] << " " ;
    //         //cout << endl << "h2: " << h2[i] << endl;
    //     for(int j = 0; j <= columnas; j++){
    //     			cout << matriz[i][j];
    //     			cout << " ";        
    //     		} 
    //     cout << endl;

    // }
}


int main()
{



  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  // Find out rank, size
  MPI_Status stat;
  int proceso;
  MPI_Comm_rank(MPI_COMM_WORLD, &proceso);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  //cout << " size:" << world_size<< endl;
  //cout << " rank:" << proceso<< endl;
    if (proceso != 0) { cout << endl<< " Proceso " << proceso << endl;
    }
    else {cout << "soy 0  : "<< endl;}
    

// if (banderaCrearMatriz == true){ banderaCrearMatriz = false;prepararMatriz();}
//          MPI_Recv(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

//             cout << "Entre al proceso 1";
          for(int i = 1; i <= filas; i++){
                int columnaInicio = (columnasPorProceso*contador) + 1;
                for(int j = (columnaInicio); j < columnaInicio + columnasPorProceso; j++){


                         //cout << "------------------------------------" << endl;
                    if(h1[j - 1] != h2[i - 1]){
                        cout << h1[j - 1]<< h2[i - 1]<<endl;
                        cout << "diferentes"<< endl;
                        bandera = 1;
                    }else {
                        cout << "IGUALES"<< endl;
                        bandera = 0;
                        //cout << h1[i - 1]<< h2[j-1]<<endl;
                        //cout << "IGUALES"<< endl;
                        }
                    Match = matriz[i-1][j-1] + bandera;
                    //cout << "M: " << Match << endl;
                    Delete = matriz[i - 1][j] + 1;
                    //cout << "D " <<Delete << endl;
                    Insert = matriz[i][j-1] + 1;
                    //cout << "I " << Insert << endl;
                    matriz[i][j] = min(min(Match, Insert), Delete);
                    //cout << "min : " << matriz[i][j] << endl;
                }

        cout << endl;
            }  
        contador++;
        MPI_Send(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);


      












MPI_Finalize();
return 0;
}