#include <iomanip>
#include <fstream>
#include <armadillo>
#include <iostream>
#include <math.h>     // exp()

using namespace std;
using namespace arma;
void fillIn (double x, double *y,int n);

ofstream ofile;
// Main program only, no other functions
int main() {

    ofstream myfile;

    int i, j, n;
    double h, btemp;
    ofile.open("C:\\Users\\richard\\Documents\\Fys441501b\\text.txt");
    cout << "Read in number of mesh points" << endl;
    cin >> n;
    h = 1.0/( (double) n+1);

    double *a;
    double *b;
    double *c;
    double *f;

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

    // write results to the output file
    for(i = 1; i <= n; i++){
        ofile << setiosflags(ios::showpoint | ios::uppercase);
        ofile << setw(15) << setprecision(8) << i*h;
        ofile << setw(15) << setprecision(8) << y[i-1];
        ofile << setw(15) << setprecision(8) << 1.0 -(1.0 - exp(-10))*(i*h)-exp(-10*i*h) <<endl;
    }
    ofile.close();
}
//

void fillIn (double x, double *y,int n){
    for(int i = 0; i <= n -1 ; i++) {
     y[i] = x;
    }
  return;
}
