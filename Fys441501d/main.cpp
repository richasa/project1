#include <iomanip>
#include <fstream>
#include <armadillo>
#include <iostream>
#include <math.h>     // exp()
#include <time.h>


using namespace std;
using namespace arma;
void fillIn (double x, double *y,int n);
int tridiagonal(int n);
int lu(int n);

ofstream ofile;
// Main program only, no other functions
int main() {

    double luTime = 0;
    double tridiagonalTime = 0;

    clock_t start , finish ;// declare start and final time
    cout << setw(5) << setprecision(8) << "n";
    cout << setw(15) << setprecision(8) << "lu Time";
    cout<< setw(20) << setprecision(8) << "tridiagonal Time" <<endl;

for (int z = 10; z <= 100000; z= z*10){

    //time for lu
    start = clock () ;
    lu(z);
    finish = clock () ;
    luTime = ((double)finish-(double)start)/ CLOCKS_PER_SEC;

    //time for tridiagonal;
    start = clock () ;
    tridiagonal(z);
    finish = clock () ;
    tridiagonalTime = ((double)finish-(double)start)/ CLOCKS_PER_SEC;


    cout << setw(5) << setprecision(8) << z*10;
    cout << setw(10) << setprecision(8) << luTime;
    cout<< setw(15) << setprecision(8) << tridiagonalTime <<endl;

}
}
//

void fillIn (double x, double *y,int n){
    for(int i = 0; i <= n -1 ; i++) {
     y[i] = x;
    }
  return;
}

//lu matrix solver
int lu (int n){

    double h = 1.0/( (double) n+1);

    //def matrix A;
    mat A = mat(n,n);
    for(int x = 0; x < n; x++) {
        for(int y = 0; y < n; y++) {
            if (x==y){
                A(x,y) = 2;
             }else if ((x+1 == y)||(x-1 == y) ){
                A(x,y) = -1;
            }else{
                A(x,y) = 0;
            }
        }
    }

    //check we have write matix
    for(int x = 0; x <= n; x++) {
        for(int y = 0; y < n; y++) {
    //        cout<<A(x,y)<<"     ";
            }
     //   cout<<endl;
        }

    vec b = vec(n);

    for(int i = 0; i < n; i++){
        // Explicit expression for f, could code as separate function
        b(i) = h*h*(100.0)*exp(-10*i*h);
    }

    vec x = solve(A, b);
    //cout<<x<<endl;

  return 0;
}


//tridiagonal solver
int tridiagonal(int n){
    int i, j;
    double h, btemp;


    h = 1.0/( (double) n+1);

    double *a;
    double *b;
    double *c;
    double *f;
    double error = 0;
    double u = 0;

    //making arrays
    a = new double[n-1];
    b = new double [n-1];
    c = new double [n-1];
    f = new double [n-1];

    double y [n-1];
    double temp [n-1];
    double hh = h*h; // to avoid extra flops in the for loop;

    // set up the matrix defined by three arrays, diagonal, upper and lower diagonal band
    fillIn (-1.0, a, n);
    fillIn (-1.0, c, n);
    fillIn (2.0, b, n);

    // Then define the value of the right hand side f (multiplied by h*h)
    for(i = 0; i <= n-1; i++){
        // Explicit expression for f, could code as separate function
        f[i] = hh*(100.0)*exp(-10*i*h);
    }
    // solve the tridiagonal system, first forward substitution
    btemp = b[0];
    for(i = 1; i <= n - 1; i++) {
        temp[i] = c[i-1] / btemp;
        btemp = b[i] - a[i] * temp[i];
        y[i] = (f[i] - a[i] * y[i-1]) / btemp;
    }
    // then backward substitution, the solution is in y()
    for(i = n-2; i >= 0; i--) {

        y[i] -= temp[i+1] * y[i+1];
    }
  return 0;
}

