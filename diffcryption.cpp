/* some prompts and other information removed */

#include<iostream>
#include<cstring>

using namespace std;

string encode(string &input){
    int A[4][4]={{14,12,26,15},
                 { 8, 0, 7, 8},
                 { 6,13,20, 7},
                 { 7,18,25, 8}}; // encryption matrix
    int i=0, // iteration index
        j=0, // row index
        k=0, // column index
        l=input.length(); // get length of input string
    int columns=l/4; // dynamic column amount based on input string length
    if(l%4) columns++; // add for leftover length
    int P[4][columns]; // P matrix
    memset(P,0,sizeof(P)); // initialize to 0
    for(i=0;i<columns*4;i++){
        if(input[i]==' '); // if input character is a space, leave as 0 
        else if(i<l){ // if current index less than input string length:
            if(islower(input[i])) P[j][k]=input[i]-96; // allows encoding lower-case characters, ASCII value minus 96
            else P[j][k]=input[i]-64; // upper case, ASCII value minus 64
        }
        j++; // increment row index
        if(j==4){ // if row index increments to 4:
            j=0; // reset row index to 0
            k++; // increment column index
        }
    }
    int C[4][columns]; // C matrix
    memset(C,0,sizeof(C)); // initialize to 0
    int limit=columns*4*4; // set iteration limit based on columns
    i=0,j=0,k=0; // reset indices
    while(limit){ // dotProduct, find [C] for [A][P]=[C]
        C[i][j]+=A[i][k]*P[k][j]; // accumulate C[i][j] while moving through A rows and P columns
        k++; // k++ moves A right, P down
        if(k==4) C[i][j]%=27,j++,k=0; // C[i][j] complete, mod 27, j++ moves C & P right, reset k
        if(j==columns) i++,j=0; // C row complete, i++ moves C & A down, reset j
        limit--; // decrement limit count
    }
    j=0; // reset row index
    k=0; // reset column index
    string result; // create string to populate with encoded characters
    for(i=0;i<columns*4;i++){
        if(!C[j][k]) result.push_back(' '); // if C[j][k] is 0 append space to result string
        else result.push_back(C[j][k]+64); // else append C modulo 27, plus 64 (to get ASCII character value)
        j++; // increment row index
        if(j==4){ // if row index increments to 4
            j=0; // reset row index to 0
            k++; // increment column index
        }
    }
    cout << "\narray P:\n"; // header
    for(i=0;i<4;i++){
        for(j=0;j<columns;j++){
            printf("%*i ",2,P[i][j]); // pad width of printed values
        }
        cout << endl;
    }
    cout << "\nencryption matrix:\n"; // header
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            printf("%*i ",2,A[i][j]); // pad width of printed values
        }
        cout << endl;
    }
    cout << "\narray C:\n"; // header
    for(i=0;i<4;i++){
        for(j=0;j<columns;j++){
            printf("%*i ",2,C[i][j]); // pad width of printed values
        }
        cout << endl;
    }
    cout << "\nencoded string:\n"; // header
    return result; // return encoded string
}

string decode(string &input){
    int A[4][4]={{ 9,19,18,26},
                 {24,26,25, 5},
                 { 2, 2, 3,22},
                 {23, 3, 3, 2}}; // decryption matrix
    int i=0, // iteration index
        j=0, // row index
        k=0, // column index
        l=input.length(); // get length of input string
    int columns=l/4; // dynamic column amount based on input string length
    if(l%4) columns++; // add for leftover length
    int P[4][columns]; // P matrix
    memset(P,0,sizeof(P)); // initialize to 0
    for(i=0;i<columns*4;i++){
        if(input[i]==' '); // if input is a space, leave as 0
        else if(i<l){ // if current index less than input string length:
            if(islower(input[i])) P[j][k]=input[i]-96; // allows encoding lower-case characters, ASCII value minus 96
            else P[j][k]=input[i]-64; // upper case, ASCII value minus 64
        }
        j++; // increment row index
        if(j==4){ // if row index increments to 4:
            j=0; // reset row index to 0
            k++; // increment column index
        }
    }
    int C[4][columns]; // C matrix
    memset(C,0,sizeof(C)); // initialize to 0
    int limit=columns*4*4; // set iteration limit based on columns
    i=0,j=0,k=0; // reset indices
    while(limit){ // dotProduct, find [C] for [A][P]=[C]
        C[i][j]+=A[i][k]*P[k][j]; // accumulate C[i][j] while moving through A rows and P columns
        k++; // k++ moves A right, P down
        if(k==4) C[i][j]%=27,j++,k=0; // C[i][j] complete, mod 27, j++ moves C & P right, reset k
        if(j==columns) i++,j=0; // C row complete, i++ moves C & A down, reset j
        limit--; // decrement limit count
    }
    j=0; // reset row index
    k=0; // reset column index
    string result; // create string to populate with encoded characters
    for(i=0;i<columns*4;i++){
        if(!C[j][k]) result.push_back(' '); // if C[j][k] is 0 append space to result string
        else result.push_back(C[j][k]+64); // else append C modulo 27, plus 64 (to get ASCII character value)
        j++; // increment row index
        if(j==4){ // if row index increments to 4
            j=0; // reset row index to 0
            k++; // increment column index
        }
    }
    cout << "\narray P:\n"; // header
    for(i=0;i<4;i++){
        for(j=0;j<columns;j++){
            printf("%*i ",2,P[i][j]); // pad width of printed values
        }
        cout << endl;
    }
    cout << "\ndecryption matrix:\n"; // header
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            printf("%*i ",2,A[i][j]); // pad width of printed values
        }
        cout << endl;
    }
    cout << "\narray C:\n"; // header
    for(i=0;i<4;i++){
        for(j=0;j<columns;j++){
            printf("%*i ",2,C[i][j]); // pad width of printed values
        }
        cout << endl;
    }
    cout << "\ndecoded string:\n"; // header
    return result; // return encoded string
}

int main(){
    string in;
    while(1){
        cout << "\ninput string to encode:\n";
        getline(cin,in);
        cout << encode(in) << endl;
        cout << "\ninput string to decode:\n";
        getline(cin,in);
        cout << decode(in) << endl;
    }
    return 0;
}
/*

IXBWSZBCRYCCZEVB
NHFGL MRZGTYOHGH

1234567890
abcdefghij
1234567890
klmnopqrst
123456
uvwxyz

*/