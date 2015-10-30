#include <iostream>
#include <mpi.h>
using namespace std;
int matriz[1001][801];
int main()
{
    cout << "Hello world!" << endl;
    const int NW_LIMIT = 8;// Limite procesos
    string h1 = "CTCATCAACGCAGCTAAAGTTCAGATCCTTCTCCAGCGCTAAGGTCATTGTTACGCAAGCCTTACGAACGGTGACCGGCTGTTGACACGACCGTCACCCTCAAATTATAGGCGCACACTAACACCGGCCAGGTTAGTAAAGGGGTAGCTTATCATGAATTACGCTGCTGATCTTACAATAAGACTGGTTTTATAGCCTCCAGAGCCTGACTGGCACTAAGCGGAGCTGCCCTCTCGTCAACTGGTACCTACATAAACCATGCAACCCTACGGGGTGAATGTGACTAATAAATGCTTCTTACGTCGAAGTTTTGGCAGATCCACGGAGTTTTTTATTAAAGTAATTTTCGCTGTCATGTACCTACGAACTTAATATCGGAGGAGAATTCGAACCGCTTTGCGTAACCTTGTATACGGGACGACTATTGTCATTGCTCTCAAATGGTGACGGGTCGAAGAATCAGTGCCTGCCGACTCATTGGGGTCGTGCTTTTAATCTCAAGCACCACACGCTCGAACATGTACCCTGTGGGAGGCGAAATTGTGTTAATGGGGGCGTATGAATATATCTACTTAGCTGAGGTACGATCGCAAGAGTCGTCCAAGTAATAGGGCCTAGTCCAAGGTTGAAATCCCAGGGGGACTTACTTAGCCGTCTTGGCCCGGTCGCGCGGACCTAAATATGCTCGATGCAAGAAACTCGGAAGTTATCACAAAAACAATGTTTTGGAGAGCATAATGCCGTGTTGCGCGTGGTTGCAACGATCAAAGAGATTTAGGAATAGCGTTTTAAAGTATGAC";
    string h2 = "GGTGAGGCTTGCGATATAAATTTTAAGGCGTAGAGAGGCCCGCACTCATTAGGTTCTTTAGCCTGCCCCCTCAGGCCACCCTTATTAGGAGGGTGGTGAAATACGGAAATGATACAATGTGTCCTAAGACATAACCAAGACATGTAGGTCCTTGAGATTCAAATCCGATCGCGGGACGACTATCATCAGGTAGAGCCCACAGAGTCGTCGGAAGCTGGTGAGTGCAAGGTGAAAGTGGTTCGACAGTTGTCGGTTTATTAGGCTGGGATAAACTTGCCACGATGATTAGTCAATGCTCACGGTCTCCAGTAGAGTTTTTGCTGTTGCTAATATATTCATAGTGAGAAGCCCTATGAACATGTGTGACTGTGTCGAGCCAATGTGACAGAATGAGTGAGAATAGGTACACATCCGTTCCCAAATATTTCACCTTAACCTACGTAAAATCTAGACTCTCAGGTGGCGACTTGAGATGTTACCTATGCTTTCGTTTCTCGACAACGGGCGTGGGACCAAATATAAACTGGGTCGTACATAATTTCAACACTACCGAGATTGTTGTATATCATAGCCGAGCAATCCATTGTCGACTAACAGCGAGGTAATTCTGAGATCTCCGTCTATGAATTGATTTGGAAACATCTTGGGTAATAAGAACCCATAAGACTTCTCAGCCTGGTCAAGATAGCAATGGTTCAAAGCGACCCACTCAGATACGATTGATGATAATGCACGCCCATTGCATAGGGCACATGGCTCTATCTTCTTCTCGCATGCAGCCACAAGAAATTTATCATATTTTGTTATGGCATGGTATGAGACTATCGGGTGGGCTGGGAATGACACGATCTTTATCCCTCCTGCCGGTTCTTGACACCTATTCCGGAGGCCATCTAATCCAGTCACCGGGGGAGGGCCTTAGCCCTCGCTGGGCCATTGGTTCGGCTCATATAAAGCATCGTTGGTCGCAACGGACGGGACGCGCTGGACGCATAACTGT";
    int filas = 5;
    int columnas = 8;

    int columnasPorProceso = columnas/NW_LIMIT;
    cout << "Largo filas: " << filas;
    cout << endl;
    cout << "Largo columnas: " << columnas;
    int Match;
    int Delete;
    int Insert;
    int bandera;
    cout << "Largo h1: " << h1.length();
    cout << endl;
    cout << "Largo h2: " << h2.length();
     // Inicializa la matriz en 0
    for(int i = 0; i <= filas; i++){

            for(int j = 0; j <= columnas; j++){
                        matriz[i][j] = 0;
        }
    }
    for(int i = 0; i <=filas; i++){// Imprime la MATRIZ
            //cout << "h1: "<<h1[i] << " " ;
            //cout << endl << "h2: " << h2[i] << endl;
        for(int j = 0; j <= columnas; j++){
            cout << matriz[i][j];
            cout << " ";
        }
        cout << endl;
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

    for(int i = 0; i <= filas; i++){// Imprime la MATRIZ
            //cout << "h1: "<<h1[i] << " " ;
            //cout << endl << "h2: " << h2[i] << endl;
        for(int j = 0; j <= columnas; j++){
            cout << matriz[i][j];
            cout << " ";
        }
        cout << endl;
    }



  // Initialize the MPI environment
  //MPI_Init(NULL, NULL);
  // Find out rank, size
  int world_rank;
  //MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  //MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int contador_nw = 0;
  int partner_rank = (world_rank + 1);
 while (contador_nw < NW_LIMIT) {
      cout << "NW Limit: " << NW_LIMIT << endl;
	  if (contador_nw == 0){
            cout << "Entre al proceso 1";
		  for(int i = 1; i <= filas; i++){
				for(int j = ((columnasPorProceso*contador_nw) + 1); j < ((columnasPorProceso*contador_nw) + 1 + columnasPorProceso); j++){


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
		contador_nw ++;
		cout << "Sali del proceso 1";
		 MPI_Send(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
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
	  if (contador_nw == 1){
            cout << "Entre al proceso 2";
		  MPI_Recv(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		  for(int i = 1; i <= filas; i++){
				for(int j = ((columnasPorProceso*contador_nw) + 1); j < ((columnasPorProceso*contador_nw) + 1 + columnasPorProceso); j++){


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
		contador_nw ++;
		 MPI_Send(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
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
	  if (contador_nw == 2){
		  MPI_Recv(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		 for(int i = 1; i <= filas; i++){
				for(int j = ((columnasPorProceso*contador_nw) + 1); j < ((columnasPorProceso*contador_nw) + 1 + columnasPorProceso); j++){


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
		contador_nw ++;
		 MPI_Send(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
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
	  if (contador_nw == 3){
		  MPI_Recv(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		  for(int i = 1; i <= filas; i++){
				for(int j = ((columnasPorProceso*contador_nw) + 1); j < ((columnasPorProceso*contador_nw) + 1 + columnasPorProceso); j++){


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
		contador_nw ++;
		 MPI_Send(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);


	  }
	  if (contador_nw == 4){
		  MPI_Recv(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		 for(int i = 1; i <= filas; i++){
				for(int j = ((columnasPorProceso*contador_nw) + 1); j < ((columnasPorProceso*contador_nw) + 1 + columnasPorProceso); j++){


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
		contador_nw ++;
		 MPI_Send(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);


	  }
	  if (contador_nw == 5){
		  MPI_Recv(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		 for(int i = 1; i <= filas; i++){
				for(int j = ((columnasPorProceso*contador_nw) + 1); j < ((columnasPorProceso*contador_nw) + 1 + columnasPorProceso); j++){


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
		contador_nw ++;
		 MPI_Send(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);


	  }
	  if (contador_nw == 6){
		  MPI_Recv(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		for(int i = 1; i <= filas; i++){
				for(int j = ((columnasPorProceso*contador_nw) + 1); j < ((columnasPorProceso*contador_nw) + 1 + columnasPorProceso); j++){


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
		contador_nw ++;
		 MPI_Send(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);


	  }
	  if (contador_nw == 7){
            cout << "Entre al proceso 8";
		  MPI_Recv(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		 for(int i = 1; i <= filas; i++){
				for(int j = ((columnasPorProceso*contador_nw) + 1); j < ((columnasPorProceso*contador_nw) + 1 + columnasPorProceso); j++){


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
		contador_nw ++;
		 MPI_Send(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);


	  }
	}
MPI_Finalize();
    for(int i = 0; i <= filas; i++){// Imprime la MATRIZ
            //cout << "h1: "<<h1[i] << " " ;
            //cout << endl << "h2: " << h2[i] << endl;
        for(int j = 0; j <= columnas; j++){
            cout << matriz[i][j];
            cout << " ";
        }
        cout << endl;
    }

return 0;

}
