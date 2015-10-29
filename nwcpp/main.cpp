
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
int matriz[801][1001];
int main()
{
    string h1 = "CTCATCAACGCAGCTAAAGTTCAGATCCTTCTCCAGCGCTAAGGTCATTGTTACGCAAGCCTTACGAACGGTGACCGGCTGTTGACACGACCGTCACCCTCAAATTATAGGCGCACACTAACACCGGCCAGGTTAGTAAAGGGGTAGCTTATCATGAATTACGCTGCTGATCTTACAATAAGACTGGTTTTATAGCCTCCAGAGCCTGACTGGCACTAAGCGGAGCTGCCCTCTCGTCAACTGGTACCTACATAAACCATGCAACCCTACGGGGTGAATGTGACTAATAAATGCTTCTTACGTCGAAGTTTTGGCAGATCCACGGAGTTTTTTATTAAAGTAATTTTCGCTGTCATGTACCTACGAACTTAATATCGGAGGAGAATTCGAACCGCTTTGCGTAACCTTGTATACGGGACGACTATTGTCATTGCTCTCAAATGGTGACGGGTCGAAGAATCAGTGCCTGCCGACTCATTGGGGTCGTGCTTTTAATCTCAAGCACCACACGCTCGAACATGTACCCTGTGGGAGGCGAAATTGTGTTAATGGGGGCGTATGAATATATCTACTTAGCTGAGGTACGATCGCAAGAGTCGTCCAAGTAATAGGGCCTAGTCCAAGGTTGAAATCCCAGGGGGACTTACTTAGCCGTCTTGGCCCGGTCGCGCGGACCTAAATATGCTCGATGCAAGAAACTCGGAAGTTATCACAAAAACAATGTTTTGGAGAGCATAATGCCGTGTTGCGCGTGGTTGCAACGATCAAAGAGATTTAGGAATAGCGTTTTAAAGTATGAC";
    string h2 = "GGTGAGGCTTGCGATATAAATTTTAAGGCGTAGAGAGGCCCGCACTCATTAGGTTCTTTAGCCTGCCCCCTCAGGCCACCCTTATTAGGAGGGTGGTGAAATACGGAAATGATACAATGTGTCCTAAGACATAACCAAGACATGTAGGTCCTTGAGATTCAAATCCGATCGCGGGACGACTATCATCAGGTAGAGCCCACAGAGTCGTCGGAAGCTGGTGAGTGCAAGGTGAAAGTGGTTCGACAGTTGTCGGTTTATTAGGCTGGGATAAACTTGCCACGATGATTAGTCAATGCTCACGGTCTCCAGTAGAGTTTTTGCTGTTGCTAATATATTCATAGTGAGAAGCCCTATGAACATGTGTGACTGTGTCGAGCCAATGTGACAGAATGAGTGAGAATAGGTACACATCCGTTCCCAAATATTTCACCTTAACCTACGTAAAATCTAGACTCTCAGGTGGCGACTTGAGATGTTACCTATGCTTTCGTTTCTCGACAACGGGCGTGGGACCAAATATAAACTGGGTCGTACATAATTTCAACACTACCGAGATTGTTGTATATCATAGCCGAGCAATCCATTGTCGACTAACAGCGAGGTAATTCTGAGATCTCCGTCTATGAATTGATTTGGAAACATCTTGGGTAATAAGAACCCATAAGACTTCTCAGCCTGGTCAAGATAGCAATGGTTCAAAGCGACCCACTCAGATACGATTGATGATAATGCACGCCCATTGCATAGGGCACATGGCTCTATCTTCTTCTCGCATGCAGCCACAAGAAATTTATCATATTTTGTTATGGCATGGTATGAGACTATCGGGTGGGCTGGGAATGACACGATCTTTATCCCTCCTGCCGGTTCTTGACACCTATTCCGGAGGCCATCTAATCCAGTCACCGGGGGAGGGCCTTAGCCCTCGCTGGGCCATTGGTTCGGCTCATATAAAGCATCGTTGGTCGCAACGGACGGGACGCGCTGGACGCATAACTGT";
    int division = 4;
    int l1 = 8;
    int l2 = 11;
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
    // Inicializa los valores
    for(int i = 0; i <= l1; i++){
            for(int j = 0; j <= l2; j++){
                        matriz[i][j] = 0;
        }
    }

    for(int j = 0; j <= l2; j++){
        matriz[0][j] = j;
        //cout << j << " ";
    }
    for(int i = 0; i <= l1; i++){
        matriz[i][0] = i;
        //cout << i << endl;
    }
    //cout <<endl;
        for(int i = 0; i <= l1; i++){
            ////cout << "h1: "<<h1[i] << " " ;
            ////cout << endl << "h2: " << h2[i] << endl;
        for(int j = 0; j <= l2; j++){
            //cout << matriz[i][j];
            //cout << " ";
        }
        //cout << endl;
    }
    // Evalua casos
    cout << endl << "fin :" ;
    for(int i = 1; i <= l1; i++){
        //cout << "------------------------------------" << endl;
        for(int j = 1; j <= l2; j++){
            //cout << "------------------------------------" << endl;
            if(h1[i - 1] != h2[j - 1]){
                //cout << h1[i - 1]<< h2[j-1]<<endl;
                //cout << "diferentes"<< endl;
                bandera = 1;
            }else {
                bandera = 0;
                //cout << h1[i - 1]<< h2[j-1]<<endl;
                //cout << "IGUALES"<< endl;
                }
            Match = matriz[i-1][j-1] + bandera;
            //cout << "M: " << Match << endl;
            Delete = matriz[i - 1][j] + 1;
            //cout << "D " <<Delete << endl;
            Insert = matriz[i][j - 1] + 1;
            //cout << "I " << Insert << endl;
            matriz[i][j] = min(min(Match, Insert), Delete);
            cout << "min : " << matriz[i][j] << endl;

        }
    }

//    for(int i = 0; i <= 3; i++){
//        //cout << "h1: "<<h1[i] << " " ;
//    }
//
//    for(int i = 0; i <= 3; i++){
//    //cout << endl << "h2: " << h2[i] << endl;
//    }

    for(int i = 0; i <= l1; i++){
            //cout << "h1: "<<h1[i] << " " ;
            //cout << endl << "h2: " << h2[i] << endl;
        for(int j = 0; j <= l2; j++){
            cout << matriz[i][3];
            cout << " ";
        }
        cout << endl;
    }

    return 0;
}

