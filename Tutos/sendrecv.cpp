#include <mpi.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <stdlib.h>
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
 void imprimirMatriz(){
    cout << endl;
    for(int i = 0; i <= filas; i++){// Imprime la MATRIZ
            //cout << "h1: "<<h1[i] << " " ;
            //cout << endl << "h2: " << h2[i] << endl;
        for(int j = 0; j <= columnas; j++){
             cout << matriz[i][j];
             cout << " ";        
           } 
        cout << endl;

    }

 }
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

}
int main(int argc, char *argv[]) {

int numtasks, rank, dest, source, rc, count, tag=1;  
char inmsg, outmsg='x';
MPI_Status Stat;

MPI::Init(argc, argv);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

if (rank == 0) {
  prepararMatriz();

  dest = 1;
  source = 7;
  rc = MPI_Send(&(matriz[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, dest, tag, MPI_COMM_WORLD);
  

  } 

else if ( rank == 1){
  dest = 2;
  source = 0;
  rc = MPI_Recv(&(matriz[0][0]),  ((filas + 1) * (columnas + 1)), MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
  rc = MPI_Send(&(matriz[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, dest, tag, MPI_COMM_WORLD);
  //imprimirMatriz();
  }

  else if ( rank == 2){
  dest = 3;
  source = 1;
  //matriz[2][3] = 7;
  rc = MPI_Recv(&(matriz[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
  rc = MPI_Send(&(matriz[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, dest, tag, MPI_COMM_WORLD);
  }
  else if ( rank == 3){
  dest = 4;
  source = 2;
  rc = MPI_Recv(&(matriz[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
  rc = MPI_Send(&(matriz[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, dest, tag, MPI_COMM_WORLD);
  }
    else if ( rank == 4){
  dest = 5;
  source = 3;
  rc = MPI_Recv(&(matriz[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT,source, tag, MPI_COMM_WORLD, &Stat);
  rc = MPI_Send(&(matriz[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, dest, tag, MPI_COMM_WORLD);
  }
    else if ( rank == 5){
  dest = 6;
  source = 4;
  rc = MPI_Recv(&(matriz[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT,source, tag, MPI_COMM_WORLD, &Stat);
  rc = MPI_Send(&(matriz[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT,dest, tag, MPI_COMM_WORLD);
  }
    else if ( rank == 6){
  dest = 7;
  source = 5;
  rc = MPI_Recv(&(matriz[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
  rc = MPI_Send(&(matriz[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, dest, tag, MPI_COMM_WORLD);
  }
    else if ( rank == 7){
  dest = 0;
  source = 6;
  rc = MPI_Recv(&(matriz[0][0]), ((filas + 1) * (columnas + 1)),MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
  imprimirMatriz();
  }

rc = MPI_Get_count(&Stat, MPI_INT, &count);
printf("Tarea %d: Recibio %d quien sabe que de la tarea %d con la etiqueta %d \n",
       rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);



MPI_Finalize();
}
