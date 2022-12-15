/* some prompts and other information removed */

#include<iostream>
#include<cstring>

using namespace std;

// provided encryption matrix:
int A[4][4]={{14,12,26,15},
             { 8, 0, 7, 8},
             { 6,13,20, 7},
             { 7,18,25, 8}}; // initialized, available globally

void dotProduct(int At[4][4],int P[4][4],int C[4][4]){
    for(int i=0;i<4;i++){ // i = row for A & C
        for(int j=0;j<4;j++){ // j = column for P & C
            for(int k=0;k<4;k++){ // k = column for A & row for P
                // C index position equals sum(all values in A[row i] * all values in P[column j])
                C[i][j]+=At[i][k]*P[k][j];
            }
        }
    }
}

template<size_t N> // dynamic template function based on number of columns
void dotProduct(int P[4][N],int C[4][N]){ // compute [A][P]=[C]
    // where N is the number of columns in P and C
    int i=0,j=0,k=0,limit=N*4*4; // init indices and set iteration limit based on N
    while(limit){
        C[i][j]+=A[i][k]*P[k][j];
        // k++ moves A right, P down
        // j++ moves C right, P right
        // i++ moves C down, A down
        k++;
        if(k==4) j++,k=0; // C[i][j] complete, increment P column, C column, reset k
        if(j==N) i++,j=0; // C row complete, increment C row, A row, reset j
        limit--;
    }
}

void findMultiplicative(int C[4][4]){
    for(int i=0;i<4;i++){ // 4 iterations
        for(int j=0;j<4;j++){ // 4 iterations
            int k=1; // index for finding multiplicative, temporary int container
            while(k<27){ // 26 iterations
                if((A[i][j]*k)%27==C[i][j]){
                    C[i][j]=k; // update with value of k that qualifies
                    break;
                }
                k++; // increment k
            }
        }
    }
}

string encode(string input){
/*  element order for a matrix in this function is [row][column] (think: [y][x])
    encryption matrix:
    A = 14 12 26 15
         8  0  7  8
         6 13 20  7
         7 18 25  8  */
    int i=0, // index
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
    // int C[4][4];
    memset(C,0,sizeof(C));
    // dotProduct(P,C); // call dotProduct function ([A]*[P]=[C])
    int limit=columns*4*4; // set iteration limit based on columns
    i=0,j=0,k=0; // reset indices
    while(limit){ // dotProduct function moved to inside encode to allow dynamic column size
        C[i][j]+=A[i][k]*P[k][j];
        // k++ moves A right, P down
        // j++ moves C right, P right
        // i++ moves C down, A down
        k++;
        if(k==4) j++,k=0; // C[i][j] complete, increment P column, C column, reset k
        if(j==columns) i++,j=0; // C row complete, increment C row, A row, reset j
        limit--;
    }
    j=0; // reset row index
    k=0; // reset column index
    string result; // create string to populate with encoded characters
    for(i=0;i<columns*4;i++){
        // all values of C must be checked with modulo 27
        // if %27 is 0 append space to result string
        if(C[j][k]%27==0) result.push_back(' ');
        // else append C modulo 27, plus 64 (to get ASCII character value)
        else result.push_back((C[j][k]%27)+64); 
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
        for(j=0;j<4;j++){
            printf("%*i ",2,P[i][j]); // pad width of printed values
        }
        cout << endl;
    }
    cout << "\narray C:\n"; // header
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            printf("%*i ",2,C[i][j]%27); // pad width of values modulo 27
        }
        cout << endl;
    }
    cout << "\nencoded string:\n"; // header
    return result; // return encoded string
}

string decode(string &input){
 /* must find values of some number, i, where the encryption key values times i,
    modulo 27 equals the input string's corresponding matrix
    encryption matrix:
    A = 14 12 26 15
         8  0  7  8
         6 13 20  7
         7 18 25  8  */
    int P[4][4], // P matrix
        j=0, // row index
        k=0, // column index
        l=input.length(); // get length of input string
    memset(P,0,sizeof(P)); // initialize P to 0's
    for(int i=0;i<16;i++){ // 16 iterations
        if(input[i]==' ') P[j][k]=0; // if char is a space, matrix entry is 0
        // if index less than input string length, matrix entry is ASCII character value minus 64
        else if(i<l) P[j][k]=input[i];
        j++; // increment row index
        if(j==4){ // if row index increments to 4
            j=0; // reset row index to 0
            k++; // increment column index
        }
    }
    findMultiplicative(P);
    int C[4][4]; // C matrix
    memset(C,0,sizeof(C)); // initialize C to 0's
    dotProduct(P,A,C); // call dotProduct function ([P]*[A]=[C])
    j=0; // reset row index
    k=0; // reset column index
    string result; // create string to populate with encoded characters
    for(int i=0;i<16;i++){ // 16 iterations
        // all values of C must be checked with modulo 27
        // if %27 is 0 append space to result string
        if(C[j][k]%27==0) result.push_back(' ');
        // else append C modulo 27, plus 64 (to get ASCII character value)
        else result.push_back((C[j][k]%27)+64); 
        j++; // increment row index
        if(j==4){ // if row index increments to 4
            j=0; // reset row index to 0
            k++; // increment column index
        }
    }
    // test print array contents
    cout << "input string:\n" << input << endl;
    cout << "\narray P:\n"; // header
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            printf("%*i ",2,P[i][j]); // pad width of printed values
        }
        cout << endl;
    }
    cout << "\narray C:\n"; // header
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            printf("%*i ",2,C[i][j]%27); // pad width of values modulo 27
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