#include<iostream>
#include<cstring>
using namespace std;

string encodeDecode(string &input,bool decrypt){
    int A[4][4]={{14,12,26,15},{8,0,7,8},{6,13,20,7},{7,18,25,8}}; // encryption matrix
    if(decrypt){ // if decrypt flag is set:
        int D[4][4]={{9,19,18,26},{24,26,25,5},{2,2,3,22},{23,3,3,2}}; // initialize decryption matrix
        memcpy(&A,&D,sizeof(D)); // copy contents of decryption matrix into [A]
    } int i=0,j=0,k=0,l=input.length(),columns=l/4; // iteration, row, column indices, length, columns of input
    if(l%4) columns++; // add for leftover length
    int P[4][columns]; // P matrix
    memset(P,0,sizeof(P)); // initialize to 0
    for(i=0;i<columns*4;i++){
        if(i<l&&input[i]!=' '){ // if current index less than input string length:
            if(islower(input[i])) P[j][k]=input[i]-96; // allows encoding lower-case characters, ASCII value minus 96
            else P[j][k]=input[i]-64; // upper case, ASCII value minus 64
        } j++; // increment row index
        if(j==4) j=0,k++; // if row index increments to 4: reset row index to 0, increment column index
    } int C[4][columns]; // C matrix
    memset(C,0,sizeof(C)); // initialize to 0
    int limit=columns*4*4; // set iteration limit based on columns
    i=0,j=0,k=0; // reset indices
    while(limit){ // dotProduct, find [C] for [A][P]=[C]
        C[i][j]+=A[i][k]*P[k][j]; // accumulate C[i][j] while moving through A rows and P columns
        k++; // k++ moves A right, P down
        if(k==4) C[i][j]%=27,j++,k=0; // C[i][j] complete, mod 27, j++ moves C & P right, reset k
        if(j==columns) i++,j=0; // C row complete, i++ moves C & A down, reset j
        limit--; // decrement limit count
    } j=0,k=0; // reset row and column indices
    string result; // create string to populate with encoded characters
    for(i=0;i<columns*4;i++){
        if(!C[j][k]) result.push_back(' '); // if C[j][k] is 0 append space to result string
        else result.push_back(C[j][k]+64); // else append C, plus 64 (to get ASCII character value)
        j++; // increment row index
        if(j==4) j=0,k++; // if row index increments to 4: reset row index to 0, increment column index
    } return result; // return encoded string
}

int main(){
    string in;
    while(1){
        cout << "\ninput string to encode:\n";
        getline(cin,in);
        cout << "\nencoded string:\n" << encodeDecode(in,0) << endl;
        cout << "\ninput string to decode:\n";
        getline(cin,in);
        cout << "\ndecoded string:\n" << encodeDecode(in,1) << endl;
    } return 0;
}