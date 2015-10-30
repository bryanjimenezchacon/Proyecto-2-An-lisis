#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;
int matriz[801][1001];

int main() {
    const int NW_LIMIT = 8;
    string h1 = "CTCATCAACGCAGCTAAAGTTCAGATCCTTCTCCAGCGCTAAGGTCATTGTTACGCAAGCCTTACGAACGGTGACCGGCTGTTGACACGACCGTCACCCTCAAATTATAGGCGCACACTAACACCGGCCAGGTTAGTAAAGGGGTAGCTTATCATGAATTACGCTGCTGATCTTACAATAAGACTGGTTTTATAGCCTCCAGAGCCTGACTGGCACTAAGCGGAGCTGCCCTCTCGTCAACTGGTACCTACATAAACCATGCAACCCTACGGGGTGAATGTGACTAATAAATGCTTCTTACGTCGAAGTTTTGGCAGATCCACGGAGTTTTTTATTAAAGTAATTTTCGCTGTCATGTACCTACGAACTTAATATCGGAGGAGAATTCGAACCGCTTTGCGTAACCTTGTATACGGGACGACTATTGTCATTGCTCTCAAATGGTGACGGGTCGAAGAATCAGTGCCTGCCGACTCATTGGGGTCGTGCTTTTAATCTCAAGCACCACACGCTCGAACATGTACCCTGTGGGAGGCGAAATTGTGTTAATGGGGGCGTATGAATATATCTACTTAGCTGAGGTACGATCGCAAGAGTCGTCCAAGTAATAGGGCCTAGTCCAAGGTTGAAATCCCAGGGGGACTTACTTAGCCGTCTTGGCCCGGTCGCGCGGACCTAAATATGCTCGATGCAAGAAACTCGGAAGTTATCACAAAAACAATGTTTTGGAGAGCATAATGCCGTGTTGCGCGTGGTTGCAACGATCAAAGAGATTTAGGAATAGCGTTTTAAAGTATGAC";
    string h2 = "GGTGAGGCTTGCGATATAAATTTTAAGGCGTAGAGAGGCCCGCACTCATTAGGTTCTTTAGCCTGCCCCCTCAGGCCACCCTTATTAGGAGGGTGGTGAAATACGGAAATGATACAATGTGTCCTAAGACATAACCAAGACATGTAGGTCCTTGAGATTCAAATCCGATCGCGGGACGACTATCATCAGGTAGAGCCCACAGAGTCGTCGGAAGCTGGTGAGTGCAAGGTGAAAGTGGTTCGACAGTTGTCGGTTTATTAGGCTGGGATAAACTTGCCACGATGATTAGTCAATGCTCACGGTCTCCAGTAGAGTTTTTGCTGTTGCTAATATATTCATAGTGAGAAGCCCTATGAACATGTGTGACTGTGTCGAGCCAATGTGACAGAATGAGTGAGAATAGGTACACATCCGTTCCCAAATATTTCACCTTAACCTACGTAAAATCTAGACTCTCAGGTGGCGACTTGAGATGTTACCTATGCTTTCGTTTCTCGACAACGGGCGTGGGACCAAATATAAACTGGGTCGTACATAATTTCAACACTACCGAGATTGTTGTATATCATAGCCGAGCAATCCATTGTCGACTAACAGCGAGGTAATTCTGAGATCTCCGTCTATGAATTGATTTGGAAACATCTTGGGTAATAAGAACCCATAAGACTTCTCAGCCTGGTCAAGATAGCAATGGTTCAAAGCGACCCACTCAGATACGATTGATGATAATGCACGCCCATTGCATAGGGCACATGGCTCTATCTTCTTCTCGCATGCAGCCACAAGAAATTTATCATATTTTGTTATGGCATGGTATGAGACTATCGGGTGGGCTGGGAATGACACGATCTTTATCCCTCCTGCCGGTTCTTGACACCTATTCCGGAGGCCATCTAATCCAGTCACCGGGGGAGGGCCTTAGCCCTCGCTGGGCCATTGGTTCGGCTCATATAAAGCATCGTTGGTCGCAACGGACGGGACGCGCTGGACGCATAACTGT";
    int l1 = 800;
    int l2 = 1000;
    cout << "Largo l1: " << l1;
    cout << endl;
    cout << "Largo l2: " << l2;
    int Match;
    int Delete;
    int Insert;
    int bandera;
    cout << "Largo h1: " << h1.length();
    cout << endl;
    cout << "Largo h2: " << h2.length();
     // Inicializa la matriz en 0
    for(int i = 0; i <= l1; i++){
            for(int j = 0; j <= l2; j++){
                        matriz[i][j] = 0;
        }
    }
	//Crea la primera fila y columna
    for(int j = 0; j <= l2; j++){
        matriz[0][j] = j;
        //cout << j << " ";
    }
    for(int i = 0; i <= l1; i++){
        matriz[i][0] = i;
        //cout << i << endl;
    }

  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  // Find out rank, size
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int contador_nw = 0;
  int partner_rank = (world_rank + 1);
  while (contador_nw < NW_LIMIT) {

	  if (contador_nw == 0){
		  for(int i = 0; i <= l1; i++){
				for(int j = 0; j <= contador_nw; j++){
					cout << matriz[i][contador_nw];
						 //cout << "------------------------------------" << endl;
					if(h1[i - 1] != h2[contador_nw]){
						//cout << h1[i - 1]<< h2[j-1]<<endl;
						//cout << "diferentes"<< endl;
						bandera = 1;
					}else {
						bandera = 0;
						//cout << h1[i - 1]<< h2[j-1]<<endl;
						//cout << "IGUALES"<< endl;
						}
					Match = matriz[i-1][contador_nw] + bandera;
					//cout << "M: " << Match << endl;
					Delete = matriz[i - 1][contador_nw + 1] + 1;
					//cout << "D " <<Delete << endl;
					Insert = matriz[i][contador_nw] + 1;
					//cout << "I " << Insert << endl;
					matriz[i][contador_nw] = min(min(Match, Insert), Delete);
					cout << "min : " << matriz[i][contador_nw] << endl;
				}
        cout << endl;
			}
		contador_nw ++;
		 MPI_Send(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);

	  }
	  if (contador_nw == 1){
		  MPI_Recv(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		  for(int i = 0; i <= l1; i++){
				for(int j = 0; j <= contador_nw; j++){
					cout << matriz[i][contador_nw];
						 //cout << "------------------------------------" << endl;
					if(h1[i - 1] != h2[contador_nw]){
						//cout << h1[i - 1]<< h2[j-1]<<endl;
						//cout << "diferentes"<< endl;
						bandera = 1;
					}else {
						bandera = 0;
						//cout << h1[i - 1]<< h2[j-1]<<endl;
						//cout << "IGUALES"<< endl;
						}
					Match = matriz[i-1][contador_nw] + bandera;
					//cout << "M: " << Match << endl;
					Delete = matriz[i - 1][contador_nw + 1] + 1;
					//cout << "D " <<Delete << endl;
					Insert = matriz[i][contador_nw] + 1;
					//cout << "I " << Insert << endl;
					matriz[i][contador_nw] = min(min(Match, Insert), Delete);
					cout << "min : " << matriz[i][contador_nw] << endl;
				}
        cout << endl;
			}
		contador_nw ++;
		 MPI_Send(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);

	  }
	  if (contador_nw == 2){
		  MPI_Recv(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		  for(int i = 0; i <= l1; i++){
				for(int j = 0; j <= contador_nw; j++){
					cout << matriz[i][contador_nw];
						 //cout << "------------------------------------" << endl;
					if(h1[i - 1] != h2[contador_nw]){
						//cout << h1[i - 1]<< h2[j-1]<<endl;
						//cout << "diferentes"<< endl;
						bandera = 1;
					}else {
						bandera = 0;
						//cout << h1[i - 1]<< h2[j-1]<<endl;
						//cout << "IGUALES"<< endl;
						}
					Match = matriz[i-1][contador_nw] + bandera;
					//cout << "M: " << Match << endl;
					Delete = matriz[i - 1][contador_nw + 1] + 1;
					//cout << "D " <<Delete << endl;
					Insert = matriz[i][contador_nw] + 1;
					//cout << "I " << Insert << endl;
					matriz[i][contador_nw] = min(min(Match, Insert), Delete);
					cout << "min : " << matriz[i][contador_nw] << endl;
				}
        cout << endl;
			}
		contador_nw ++;
		 MPI_Send(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);


	  }
	  if (contador_nw == 3){
		  MPI_Recv(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		  for(int i = 0; i <= l1; i++){
				for(int j = 0; j <= contador_nw; j++){
					cout << matriz[i][contador_nw];
						 //cout << "------------------------------------" << endl;
					if(h1[i - 1] != h2[contador_nw]){
						//cout << h1[i - 1]<< h2[j-1]<<endl;
						//cout << "diferentes"<< endl;
						bandera = 1;
					}else {
						bandera = 0;
						//cout << h1[i - 1]<< h2[j-1]<<endl;
						//cout << "IGUALES"<< endl;
						}
					Match = matriz[i-1][contador_nw] + bandera;
					//cout << "M: " << Match << endl;
					Delete = matriz[i - 1][contador_nw + 1] + 1;
					//cout << "D " <<Delete << endl;
					Insert = matriz[i][contador_nw] + 1;
					//cout << "I " << Insert << endl;
					matriz[i][contador_nw] = min(min(Match, Insert), Delete);
					cout << "min : " << matriz[i][contador_nw] << endl;
				}
        cout << endl;
			}
		contador_nw ++;
		 MPI_Send(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);


	  }
	  if (contador_nw == 4){
		  MPI_Recv(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		  for(int i = 0; i <= l1; i++){
				for(int j = 0; j <= contador_nw; j++){
					cout << matriz[i][contador_nw];
						 //cout << "------------------------------------" << endl;
					if(h1[i - 1] != h2[contador_nw]){
						//cout << h1[i - 1]<< h2[j-1]<<endl;
						//cout << "diferentes"<< endl;
						bandera = 1;
					}else {
						bandera = 0;
						//cout << h1[i - 1]<< h2[j-1]<<endl;
						//cout << "IGUALES"<< endl;
						}
					Match = matriz[i-1][contador_nw] + bandera;
					//cout << "M: " << Match << endl;
					Delete = matriz[i - 1][contador_nw + 1] + 1;
					//cout << "D " <<Delete << endl;
					Insert = matriz[i][contador_nw] + 1;
					//cout << "I " << Insert << endl;
					matriz[i][contador_nw] = min(min(Match, Insert), Delete);
					cout << "min : " << matriz[i][contador_nw] << endl;
				}
        cout << endl;
			}
		contador_nw ++;
		 MPI_Send(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);


	  }
	  if (contador_nw == 5){
		  MPI_Recv(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		  for(int i = 0; i <= l1; i++){
				for(int j = 0; j <= contador_nw; j++){
					cout << matriz[i][contador_nw];
						 //cout << "------------------------------------" << endl;
					if(h1[i - 1] != h2[contador_nw]){
						//cout << h1[i - 1]<< h2[j-1]<<endl;
						//cout << "diferentes"<< endl;
						bandera = 1;
					}else {
						bandera = 0;
						//cout << h1[i - 1]<< h2[j-1]<<endl;
						//cout << "IGUALES"<< endl;
						}
					Match = matriz[i-1][contador_nw] + bandera;
					//cout << "M: " << Match << endl;
					Delete = matriz[i - 1][contador_nw + 1] + 1;
					//cout << "D " <<Delete << endl;
					Insert = matriz[i][contador_nw] + 1;
					//cout << "I " << Insert << endl;
					matriz[i][contador_nw] = min(min(Match, Insert), Delete);
					cout << "min : " << matriz[i][contador_nw] << endl;
				}
        cout << endl;
			}
		contador_nw ++;
		 MPI_Send(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);


	  }
	  if (contador_nw == 6){
		  MPI_Recv(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		  for(int i = 0; i <= l1; i++){
				for(int j = 0; j <= contador_nw; j++){
					cout << matriz[i][contador_nw];
						 //cout << "------------------------------------" << endl;
					if(h1[i - 1] != h2[contador_nw]){
						//cout << h1[i - 1]<< h2[j-1]<<endl;
						//cout << "diferentes"<< endl;
						bandera = 1;
					}else {
						bandera = 0;
						//cout << h1[i - 1]<< h2[j-1]<<endl;
						//cout << "IGUALES"<< endl;
						}
					Match = matriz[i-1][contador_nw] + bandera;
					//cout << "M: " << Match << endl;
					Delete = matriz[i - 1][contador_nw + 1] + 1;
					//cout << "D " <<Delete << endl;
					Insert = matriz[i][contador_nw] + 1;
					//cout << "I " << Insert << endl;
					matriz[i][contador_nw] = min(min(Match, Insert), Delete);
					cout << "min : " << matriz[i][contador_nw] << endl;
				}
        cout << endl;
			}
		contador_nw ++;
		 MPI_Send(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);


	  }
	  if (contador_nw == 7){
		  MPI_Recv(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		  for(int i = 0; i <= l1; i++){
				for(int j = 0; j <= contador_nw; j++){
					cout << matriz[i][contador_nw];
						 //cout << "------------------------------------" << endl;
					if(h1[i - 1] != h2[contador_nw]){
						//cout << h1[i - 1]<< h2[j-1]<<endl;
						//cout << "diferentes"<< endl;
						bandera = 1;
					}else {
						bandera = 0;
						//cout << h1[i - 1]<< h2[j-1]<<endl;
						//cout << "IGUALES"<< endl;
						}
					Match = matriz[i-1][contador_nw] + bandera;
					//cout << "M: " << Match << endl;
					Delete = matriz[i - 1][contador_nw + 1] + 1;
					//cout << "D " <<Delete << endl;
					Insert = matriz[i][contador_nw] + 1;
					//cout << "I " << Insert << endl;
					matriz[i][contador_nw] = min(min(Match, Insert), Delete);
					cout << "min : " << matriz[i][contador_nw] << endl;
				}
        cout << endl;
			}
		contador_nw ++;
		 MPI_Send(&matriz, 801801, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);


	  }
	}
MPI_Finalize();


return 0;

}
