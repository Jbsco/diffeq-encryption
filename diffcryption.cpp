/* some prompts and other information removed */

#include<iostream>
#include<cstring>

using namespace std;

// provided encryption matrix:
int A[4][4]={{14,12,26,15},
             { 8, 0, 7, 8},
             { 6,13,20, 7},
             { 7,18,25, 8}}; // initialized, available globally
int Ai[4][4]={{-18,19,18,-1},
              {24,-1,-2,5},
              {-25,2,3,5},
              {23,-24,-24,2}}; // congruent multiplicative inverse of A, to be initialized in decode function

string encode(string input){
/*  element order for a matrix in this function is [row][column] (think: [y][x])
    encryption matrix:
    A = 14 12 26 15
         8  0  7  8
         6 13 20  7
         7 18 25  8  */
    int i=0, // iteration index
        j=0, // row index
        k=0, // column index
        l=input.length(); // get length of input string
    int columns=l/4; // dynamic matrix size based on input string length
    if(l%4) columns++; // add for leftover length
    int P[4][columns]; // P matrix
    memset(P,0,sizeof(P)); // initialize to 0
    for(i=0;i<columns*4;i++){
        if(input[i]==' '); // if input is a space, leave as 0
        // if index less than input string length, matrix entry is ASCII character value minus 64
        else if(i<l) P[j][k]=input[i]-64;
        j++; // increment row index
        if(j==4){ // if row index increments to 4
            j=0; // reset row index to 0
            k++; // increment column index
        }
    }
    int C[4][columns]; // C matrix
    memset(C,0,sizeof(C)); // initialize to 0
    int limit=columns*4*4; // set iteration limit based on columns
    i=0,j=0,k=0; // reset indices
    // dotProduct function, allows dynamic column size
    while(limit){
        C[i][j]+=A[i][k]*P[k][j];
        // k++ moves A right, P down
        // j++ moves C right, P right
        // i++ moves C down, A down
        k++;
        if(k==4) C[i][j]%=27,j++,k=0; // C[i][j] complete, mod 27, increment P column, C column, reset k
        if(j==columns) i++,j=0; // C row complete, increment C row, A row, reset j
        limit--;
    }
    j=0; // reset row index
    k=0; // reset column index
    string result; // create string to populate with encoded characters
    for(i=0;i<columns*4;i++){
        // all values of C must be checked with modulo 27
        // if %27 is 0 append space to result string
        if(C[j][k]==0) result.push_back(' ');
        // else append C modulo 27, plus 64 (to get ASCII character value)
        else result.push_back(C[j][k]+64); 
        j++; // increment row index
        if(j==4){ // if row index increments to 4
            j=0; // reset row index to 0
            k++; // increment column index
        }
    }
    // test print array contents
    cout << "input string:\n" << input << endl;
    cout << "\narray P:\n"; // header
    for(i=0;i<4;i++){
        for(j=0;j<columns;j++){
            printf("%*i ",2,P[i][j]); // pad width of printed values
        }
        cout << endl;
    }
    cout << "\narray C:\n"; // header
    for(i=0;i<4;i++){
        for(j=0;j<columns;j++){
            printf("%*i ",2,C[i][j]); // pad width of values
        }
        cout << endl;
    }
    cout << "\nencoded string:\n"; // header
    return result; // return encoded string
}

string decode(string &input){
 /* must find values of some number, i, where the encryption key values times i,
    modulo 27 equals the input string's corresponding matrix
    decryption matrix:
    Ai = 14 12 26 15
          8  0  7  8
          6 13 20  7
          7 18 25  8  */
    int i=0, // iteration index
        j=0, // row index
        k=0, // column index
        l=input.length(); // get length of input string
    int columns=l/4; // dynamic matrix size based on input string length
    if(l%4) columns++; // add for leftover length
    int P[4][columns]; // P matrix
    memset(P,0,sizeof(P)); // initialize to 0
    for(i=0;i<columns*4;i++){
        if(input[i]==' '); // if input is a space, leave as 0
        // if index less than input string length, matrix entry is ASCII character value minus 64
        else if(i<l) P[j][k]=input[i]-64;
        j++; // increment row index
        if(j==4){ // if row index increments to 4
            j=0; // reset row index to 0
            k++; // increment column index
        }
    }
    /*// find congruent multiplicative inverse of [A] - this is the decryption matrix
    for(i=0;i<4;i++){
        for(j=0;j<columns;j++){
            k=1; // index for finding multiplicative, temporary int container
            while(k<27){ // 26 iterations
                if((4*k)%27==A[i][j]){
                    Ai[i][j]=k; // update [Ai] with value
                    break; // exit loop
                }
                k++; // increment k
            }
        }
    }*/
    // need to undo dotProduct operation, find [C] for [Ai][C]=[P]
    int C[4][columns]; // C matrix
    memset(C,0,sizeof(C)); // initialize to 0
    int limit=columns*4*4; // set iteration limit based on columns
    i=0,j=0,k=0; // reset indices
    // dotProduct function, allows dynamic column size
    while(limit){
        C[i][j]+=Ai[i][k]*P[k][j];
        // k++ moves A right, P down
        // j++ moves C right, P right
        // i++ moves C down, Ai down
        k++;
        if(k==4) C[i][j]%=27,j++,k=0; // C[i][j] complete, mod 27, increment P column, C column, reset k
        if(j==columns) i++,j=0; // C row complete, increment C row, Ai row, reset j
        limit--;
    }
    j=0; // reset row index
    k=0; // reset column index
    string result; // create string to populate with encoded characters
    for(i=0;i<columns*4;i++){
        // all values of C must be checked with modulo 27
        // if %27 is 0 append space to result string
        if(C[j][k]==0) result.push_back(' ');
        // else append C modulo 27, plus 64 (to get ASCII character value)
        else result.push_back((C[j][k])+64); 
        j++; // increment row index
        if(j==4){ // if row index increments to 4
            j=0; // reset row index to 0
            k++; // increment column index
        }
    }
    // test print array contents
    cout << "input string:\n" << input << endl;
    cout << "\narray P:\n"; // header
    for(i=0;i<4;i++){
        for(j=0;j<columns;j++){
            printf("%*i ",2,P[i][j]); // pad width of printed values
        }
        cout << endl;
    }
    cout << "\narray Ai:\n"; // header
    for(i=0;i<4;i++){
        for(j=0;j<columns;j++){
            printf("%*i ",2,Ai[i][j]); // pad width of values modulo 27
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