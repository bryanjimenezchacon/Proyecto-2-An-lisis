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
    int filas = 1000;
    int columnas = 800;

    int columnasPorProceso = columnas/NW_LIMIT;
    int Match;
    int Delete;
    int Insert;
    bool banderaCrearMatriz =  true;
    int bandera;
    int contador_nw = 0; 

 int **alloc_2d_int(int rows, int cols){
    int *data = (int *)malloc(rows*cols*sizeof(int));
    int **array = (int **)malloc(rows*sizeof(int*));
    for (int i = 0; i <rows; i++){
      array[i] = &(data[cols*i]);
    }
    return array;
}
int **A = alloc_2d_int((filas + 1), (columnas + 1));//Crea la matriz vacia

 void prepararMatriz(){
    banderaCrearMatriz = false; 
  //Crea la primera fila y columna
    for(int j = 0; j <= filas; j++){
        A[j][0] = j;
        //cout << j << " ";
    }
    for(int i = 0; i <= columnas; i++){
        A[0][i] = i;
        //cout << i << endl;
    }

}
 void imprimirMatriz(){
    cout << endl;
    for(int i = 0; i <= filas; i++){// Imprime la MATRIZ
            //cout << "h1: "<<h1[i] << " " ;
            //cout << endl << "h2: " << h2[i] << endl;
        for(int j = 0; j <= columnas; j++){
             cout << (A[i][j]);
             cout << " ";        
           } 
        cout << endl;

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
  //imprimirMatriz();
  dest = 1;
  source = 7;

  for (int i = 1; i <= filas; i++){
    int columnaInicio = (columnasPorProceso*rank) + 1;
    for (int j = columnaInicio; j < (columnaInicio + columnasPorProceso); j++){
      if (h1[i-1] != h2[j-1]){
        bandera = 1;
      }
      else { bandera = 0; }
      Match = A[i-1][j-1] + bandera;
      //cout << "M: " << Match << endl;
      Delete = A[i - 1][j] + 1;
      //cout << "D " <<Delete << endl;
      Insert = A[i][j-1] + 1;
      //cout << "I " << Insert << endl;
      A[i][j] = min(min(Match, Insert), Delete);


    }
  }
  //imprimirMatriz();
  rc = MPI_Send(&(A[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, dest, tag, MPI_COMM_WORLD);


  } 

else if ( rank == 1){
  dest = 2;
  source = 0;
  rc = MPI_Recv(&(A[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, source, tag, MPI_COMM_WORLD, &Stat); 
    for (int i = 1; i <= filas; i++){
    int columnaInicio = (columnasPorProceso*rank) + 1;
    for (int j = columnaInicio; j < (columnaInicio + columnasPorProceso); j++){
      if (h1[i-1] != h2[j-1]){
        bandera = 1;
      }
      else { bandera = 0; }
      Match = A[i-1][j-1] + bandera;
      //cout << "M: " << Match << endl;
      Delete = A[i - 1][j] + 1;
      //cout << "D " <<Delete << endl;
      Insert = A[i][j-1] + 1;
      //cout << "I " << Insert << endl;
      A[i][j] = min(min(Match, Insert), Delete);


    }
  }
  //imprimirMatriz();
  rc = MPI_Send(&(A[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, dest, tag, MPI_COMM_WORLD);
  }

  else if ( rank == 2){
  dest = 3;
  source = 1;
  rc = MPI_Recv(&(A[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
  for (int i = 1; i <= filas; i++){
    int columnaInicio = (columnasPorProceso*rank) + 1;
    for (int j = columnaInicio; j < (columnaInicio + columnasPorProceso); j++){
      if (h1[i-1] != h2[j-1]){
        bandera = 1;
      }
      else { bandera = 0; }
      Match = A[i-1][j-1] + bandera;
      //cout << "M: " << Match << endl;
      Delete = A[i - 1][j] + 1;
      //cout << "D " <<Delete << endl;
      Insert = A[i][j-1] + 1;
      //cout << "I " << Insert << endl;
      A[i][j] = min(min(Match, Insert), Delete);


    }
  }
  //imprimirMatriz();
  rc = MPI_Send(&(A[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, dest, tag, MPI_COMM_WORLD);
  }
  else if ( rank == 3){
  dest = 4;
  source = 2;
  rc = MPI_Recv(&(A[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
  for (int i = 1; i <= filas; i++){
    int columnaInicio = (columnasPorProceso*rank) + 1;
    for (int j = columnaInicio; j < (columnaInicio + columnasPorProceso); j++){
      if (h1[i-1] != h2[j-1]){
        bandera = 1;
      }
      else { bandera = 0; }
      Match = A[i-1][j-1] + bandera;
      //cout << "M: " << Match << endl;
      Delete = A[i - 1][j] + 1;
      //cout << "D " <<Delete << endl;
      Insert = A[i][j-1] + 1;
      //cout << "I " << Insert << endl;
      A[i][j] = min(min(Match, Insert), Delete);


    }
  }
  //imprimirMatriz();
  rc = MPI_Send(&(A[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, dest, tag, MPI_COMM_WORLD);
  }
    else if ( rank == 4){
  dest = 5;
  source = 3;
  rc = MPI_Recv(&(A[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
  for (int i = 1; i <= filas; i++){
    int columnaInicio = (columnasPorProceso*rank) + 1;
    for (int j = columnaInicio; j < (columnaInicio + columnasPorProceso); j++){
      if (h1[i-1] != h2[j-1]){
        bandera = 1;
      }
      else { bandera = 0; }
      Match = A[i-1][j-1] + bandera;
      //cout << "M: " << Match << endl;
      Delete = A[i - 1][j] + 1;
      //cout << "D " <<Delete << endl;
      Insert = A[i][j-1] + 1;
      //cout << "I " << Insert << endl;
      A[i][j] = min(min(Match, Insert), Delete);


    }
  }
  //imprimirMatriz();
  rc = MPI_Send(&(A[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, dest, tag, MPI_COMM_WORLD);
  }
    else if ( rank == 5){
  dest = 6;
  source = 4;
  rc = MPI_Recv(&(A[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
  for (int i = 1; i <= filas; i++){
    int columnaInicio = (columnasPorProceso*rank) + 1;
    for (int j = columnaInicio; j < (columnaInicio + columnasPorProceso); j++){
      if (h1[i-1] != h2[j-1]){
        bandera = 1;
      }
      else { bandera = 0; }
      Match = A[i-1][j-1] + bandera;
      //cout << "M: " << Match << endl;
      Delete = A[i - 1][j] + 1;
      //cout << "D " <<Delete << endl;
      Insert = A[i][j-1] + 1;
      //cout << "I " << Insert << endl;
      A[i][j] = min(min(Match, Insert), Delete);


    }
  }
  //imprimirMatriz();
  rc = MPI_Send(&(A[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, dest, tag, MPI_COMM_WORLD);
  }
    else if ( rank == 6){
  dest = 7;
  source = 5;
  rc = MPI_Recv(&(A[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
  for (int i = 1; i <= filas; i++){
    int columnaInicio = (columnasPorProceso*rank) + 1;
    for (int j = columnaInicio; j < (columnaInicio + columnasPorProceso); j++){
      if (h1[i-1] != h2[j-1]){
        bandera = 1;
      }
      else { bandera = 0; }
      Match = A[i-1][j-1] + bandera;
      //cout << "M: " << Match << endl;
      Delete = A[i - 1][j] + 1;
      //cout << "D " <<Delete << endl;
      Insert = A[i][j-1] + 1;
      //cout << "I " << Insert << endl;
      A[i][j] = min(min(Match, Insert), Delete);


    }
  }
  //imprimirMatriz();
  rc = MPI_Send(&(A[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, dest, tag, MPI_COMM_WORLD);
  }
    else if ( rank == 7){
  dest = 0;
  source = 6;
  rc = MPI_Recv(&(A[0][0]), ((filas + 1) * (columnas + 1)), MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
  for (int i = 1; i <= filas; i++){
    int columnaInicio = (columnasPorProceso*rank) + 1;
    for (int j = columnaInicio; j < (columnaInicio + columnasPorProceso); j++){
      if (h1[i-1] != h2[j-1]){
        bandera = 1;
      }
      else { bandera = 0; }
      Match = A[i-1][j-1] + bandera;
      //cout << "M: " << Match << endl;
      Delete = A[i - 1][j] + 1;
      //cout << "D " <<Delete << endl;
      Insert = A[i][j-1] + 1;
      //cout << "I " << Insert << endl;
      A[i][j] = min(min(Match, Insert), Delete);


    }
  }
  //imprimirMatriz();
  }

rc = MPI_Get_count(&Stat, MPI_INT, &count);
printf("Tarea %d: Recibio %d quien sabe que de la tarea %d con la etiqueta %d \n",
       rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);



MPI_Finalize();

}
