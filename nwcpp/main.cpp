#include <iostream>
#include <string>
using namespace std;

int main()
{
    string h1 = "CTCATCAACGCAGCTAAAGTTCAGATCCTTCTCCAGCGCTAAGGTCATTGTTACGCAAGCCTTACGAACGGTGACCGGCTGTTGACACGACCGTCACCCTCAAATTATAGGCGCACACTAACACCGGCCAGGTTAGTAAAGGGGTAGCTTATCATGAATTACGCTGCTGATCTTACAATAAGACTGGTTTTATAGCCTCCAGAGCCTGACTGGCACTAAGCGGAGCTGCCCTCTCGTCAACTGGTACCTACATAAACCATGCAACCCTACGGGGTGAATGTGACTAATAAATGCTTCTTACGTCGAAGTTTTGGCAGATCCACGGAGTTTTTTATTAAAGTAATTTTCGCTGTCATGTACCTACGAACTTAATATCGGAGGAGAATTCGAACCGCTTTGCGTAACCTTGTATACGGGACGACTATTGTCATTGCTCTCAAATGGTGACGGGTCGAAGAATCAGTGCCTGCCGACTCATTGGGGTCGTGCTTTTAATCTCAAGCACCACACGCTCGAACATGTACCCTGTGGGAGGCGAAATTGTGTTAATGGGGGCGTATGAATATATCTACTTAGCTGAGGTACGATCGCAAGAGTCGTCCAAGTAATAGGGCCTAGTCCAAGGTTGAAATCCCAGGGGGACTTACTTAGCCGTCTTGGCCCGGTCGCGCGGACCTAAATATGCTCGATGCAAGAAACTCGGAAGTTATCACAAAAACAATGTTTTGGAGAGCATAATGCCGTGTTGCGCGTGGTTGCAACGATCAAAGAGATTTAGGAATAGCGTTTTAAAGTATGAC";
    string h2 = "GGTGAGGCTTGCGATATAAATTTTAAGGCGTAGAGAGGCCCGCACTCATTAGGTTCTTTAGCCTGCCCCCTCAGGCCACCCTTATTAGGAGGGTGGTGAAATACGGAAATGATACAATGTGTCCTAAGACATAACCAAGACATGTAGGTCCTTGAGATTCAAATCCGATCGCGGGACGACTATCATCAGGTAGAGCCCACAGAGTCGTCGGAAGCTGGTGAGTGCAAGGTGAAAGTGGTTCGACAGTTGTCGGTTTATTAGGCTGGGATAAACTTGCCACGATGATTAGTCAATGCTCACGGTCTCCAGTAGAGTTTTTGCTGTTGCTAATATATTCATAGTGAGAAGCCCTATGAACATGTGTGACTGTGTCGAGCCAATGTGACAGAATGAGTGAGAATAGGTACACATCCGTTCCCAAATATTTCACCTTAACCTACGTAAAATCTAGACTCTCAGGTGGCGACTTGAGATGTTACCTATGCTTTCGTTTCTCGACAACGGGCGTGGGACCAAATATAAACTGGGTCGTACATAATTTCAACACTACCGAGATTGTTGTATATCATAGCCGAGCAATCCATTGTCGACTAACAGCGAGGTAATTCTGAGATCTCCGTCTATGAATTGATTTGGAAACATCTTGGGTAATAAGAACCCATAAGACTTCTCAGCCTGGTCAAGATAGCAATGGTTCAAAGCGACCCACTCAGATACGATTGATGATAATGCACGCCCATTGCATAGGGCACATGGCTCTATCTTCTTCTCGCATGCAGCCACAAGAAATTTATCATATTTTGTTATGGCATGGTATGAGACTATCGGGTGGGCTGGGAATGACACGATCTTTATCCCTCCTGCCGGTTCTTGACACCTATTCCGGAGGCCATCTAATCCAGTCACCGGGGGAGGGCCTTAGCCCTCGCTGGGCCATTGGTTCGGCTCATATAAAGCATCGTTGGTCGCAACGGACGGGACGCGCTGGACGCATAACTGT";
    int division = 4;
    int l1 = 3;
    int l2 = 4;
    int matriz[4][5];// Crea la matriz
    int Match;
    int Delete;
    int Insert;
    int bandera;

    // Inicializa los valores

    for(int i = 0; i <= l1; i++){
            for(int j = 0; j <= l2; j++){
                        matriz[i][j] = 0;
        }
    }

    for(int j = 0; j <= l2; j++){
        matriz[0][j] = j;
        cout << j << " ";
    }
    for(int i = 0; i <= l1; i++){
        matriz[i][0] = i;
        cout << i << endl;
    }
    cout <<endl;
        for(int i = 0; i <= l1; i++){
            //cout << "h1: "<<h1[i] << " " ;
            //cout << endl << "h2: " << h2[i] << endl;
        for(int j = 0; j <= l2; j++){
            cout << matriz[i][j];
            cout << " ";
        }
        cout << endl;
    }
    // Evalua casos
    cout << endl << "fin :" ;
    for(int i = 1; i <= l1; i++){
        cout << "------------------------------------" << endl;
        for(int j = 1; j <= l2; j++){
            cout << "------------------------------------" << endl;
            if(h1[i - 1] != h2[j - 1]){
                cout << h1[i - 1]<< h2[j-1]<<endl;
                cout << "diferentes"<< endl;
                bandera = 1;
            }else {
                bandera = 0;
                cout << h1[i - 1]<< h2[j-1]<<endl;
                cout << "IGUALES"<< endl;}
            Match = matriz[i-1][j-1] + bandera;
            cout << "M: " << Match << endl;
            Delete = matriz[i - 1][j] + 1;
            cout << "D " <<Delete << endl;
            Insert = matriz[i][j - 1] + 1;
            cout << "I " << Insert << endl;
            matriz[i][j] = min(min(Match, Insert), Delete);
            cout << "min : " << matriz[i][j] << endl;

        }
    }

//    for(int i = 0; i <= 3; i++){
//        cout << "h1: "<<h1[i] << " " ;
//    }
//
//    for(int i = 0; i <= 3; i++){
//    cout << endl << "h2: " << h2[i] << endl;
//    }

    for(int i = 0; i <= l1; i++){
            //cout << "h1: "<<h1[i] << " " ;
            //cout << endl << "h2: " << h2[i] << endl;
        for(int j = 0; j <= l2; j++){
            cout << matriz[i][j];
            cout << " ";
        }
        cout << endl;
    }


    return 0;
}
