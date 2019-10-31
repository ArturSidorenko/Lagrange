#include<iostream>
#include<fstream>
#include<string>
#include<fstream>
#include<cmath>

using namespace std;
typedef double(*s_func)(double);
typedef double(*mesh_)(int,int);
// Runghe frunction calculation
//
double func(double x);

double func(double x) {
	return 1. / (25 * x * x + 1);
}

double mesh_cheb(int n, int i) ;
double mesh_cheb(int n, int i) {
    return cos(M_PI * (-1 + 2*(n-i)) / (2*n) );
}

double unif_mesh(int n, int i);
double unif_mesh(int n, int i) {
    return i*(1.+1.) / (n-1) - 1;
}

double runge(double x);
double runge(double x) {
    return 1/(25*x*x+1);
}

double modul(double x);
double modul(double x) {
    return fabs(x);
}

void fill(int n, string fname, s_func func, mesh_ m) {
    ofstream f;
    f.open(fname);

        // write the number of nodes
    f << n << "\n";
    double x;
        //uniform mesh
    for(int i = 0; i < n; i++) {
        x = m(n, i);
        f.precision(17);
        f.width(22);
        f << x <<" "<<func(x)<<"\n";
    }

    f.close();
}

int main() {
        int n = 50;
        fill(n,"ru.dat", runge, unif_mesh);
        fill(n,"rc.dat", runge, mesh_cheb);

        fill(n,"mu.dat", modul, unif_mesh);
        fill(n,"mc.dat", modul, mesh_cheb);
	

    return 0;
}
