#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cmath>

//Lagrange polynomial calculation

using namespace std;

double fund_poly(int n, int i, double *mesh, double x) {
	double y = 1;
	for(int j = 0; j < n; j++) {
		if(j != i) y *= (x - mesh[j]) / (mesh[i] - mesh[j]);
	}
	return y;
}

double Lag(int n, double *mesh, double *vals, double x) {
	double y = 0;
	for(int i = 0; i < n; i++) {
		y += vals[i] * fund_poly(n, i, mesh, x);
	}
	return y;
}

double runge(double x) {
	return 1. / (25 * x * x + 1); 	
}

double modul(double x) {
    return fabs(x);
}

int main(int argc, char**argv) {
	int n; //numbr of nodes
	double *mesh, *vals; //nodes and values

        if(argc <= 3) {
            return -1;
        }
	ifstream fin;

        fin.open(argv[1]);
        int select_fun = atoi(argv[2]);

	//read the file
	
	fin >> n;

	mesh = (double *)malloc(n * sizeof(double));
	vals = (double *)malloc(n * sizeof(double));
	

	cout <<"Reading data  n = " << n <<"\n";
	for(int i = 0; i < n; i++) {
		fin >> mesh[i];
		fin >> vals[i];
	} 
	
	//we are happy because we've read
	
	//now it's time to build a graph
	//
	ofstream fout;
        fout.open(argv[3]);
	fout << n << "\n";

	double y_est, y_tr;
	double x = mesh[0];

	double step;
        const int k = 4;
	fout << "# x_i      y_i      L_i      |y_i - L_i| \n";

	cout << "Performing calculations\n";
        for(int i = 1; i < n; i++) {
                x = mesh[i-1];
                step = (mesh[i] - mesh[i-1]) / k;
                for(int j = 0; j < k; j++) {
			//cout<<"j = "<<j<<"\n";
			y_est = Lag(n, mesh, vals, x);
                        if (select_fun == 0) {
                            y_tr = runge(x);
                        } else {

                            y_tr = modul(x);
                        }
                        fout.precision(16);
                        fout.width(21);
                        fout << x << " ";

                        fout.precision(16);
                        fout.width(21);
                        fout << y_est << " " ;

                        fout.precision(16);
                        fout.width(21);
                        fout << y_tr << " " ;

                        fout.precision(16);
                        fout.width(21);
                        fout << y_est - y_tr<<"\n";
			x+=step;

		}
		
	}

        //i = n - 1
        x = mesh[n-1];
        y_est = Lag(n, mesh, vals, x);
        if (select_fun == 0) {
            y_tr = runge(x);
        } else {

            y_tr = modul(x);
        }
        fout.precision(16);
        fout.width(21);
        fout << x << " ";

        fout.precision(16);
        fout.width(21);
        fout << y_est << " " ;

        fout.precision(16);
        fout.width(21);
        fout << y_tr << " " ;

        fout.precision(16);
        fout.width(21);
        fout << y_est - y_tr<<"\n";


	fout.close();
	free(mesh);
	free(vals);
	return 0;
}
	
