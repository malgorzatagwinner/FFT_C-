#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>

using namespace std;


vector <complex<double>> FFT(vector<complex<double>> *a, complex<double> w){
    int n = (*a).size();
    if(n == 1){
        return *a;
    }
    complex<double> w_2(1,0);
    vector<complex<double>> a1;
    vector<complex<double>> a2;
    for(int i = 0; i<n; i++){
        if(i%2 ==0){
            a1.push_back((*a)[i]);
        }
        else{
            a2.push_back((*a)[i]);
        }
    }

    vector<complex<double>> y1 = FFT(&a1, w*w);
    vector<complex<double>> y2 = FFT(&a2, w*w);
    vector<complex<double>> y;
    y.resize(n);
    for(int i=0; i<n/2; i++){
        y[i] = y1[i] + w_2*y2[i];
        y[(n/2)+i] = y1[i] - w_2*y2[i];
        w_2 = w* w_2;
    }
    return y;
}

vector <int> count(vector <complex<double>> a, vector <complex<double>> b){
    int asize = a.size();
    int bsize = b.size();

    int number = a.size() + b.size();
    for(int i =number;i<2*number; i++){
        if((i != 0) && ((i & (i - 1)) == 0)){
            number = i;
            break;
        }
    }
    for(int i=a.size(); i<number; i++){
        a.push_back(0);
    }
    for(int i=b.size(); i<number; i++){
        b.push_back(0);
    }
   double alpha = 2* M_PI /number;
   complex<double> w = complex<double>(cos(alpha), sin(alpha));
   complex<double> one(1.0, 0);
   complex<double > w1 = one/w;

   vector <complex<double>> A = FFT(&a, w);
   vector <complex<double>> B = FFT(&b, w);
   vector<complex<double >> C(number);

    for(int i=0; i<number; i++){
         C[i] = A[i] * B[i];

    }

   vector<int> c(number);

    vector<complex<double>>tmp = FFT(&C, w1);

    for(int i=0; i<number; i++){
        c[i] = round((1/double(number))*tmp[i].real());
    }
    return c;

}


int main() {
    ofstream plik;
    plik.open("Fourier.txt");
    vector<complex<double>> a;
    vector<complex<double>> b;
    int x;
    for(int i=0; i<5000; i++){
        cin>> x;
        a.push_back(x);
    }
    for(int i=0; i<5000; i++){
        cin>>x;
        b.push_back(x);
    }

    clock_t start;
    double duration;
    start = clock();
    vector<int> c = count(a,b);
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

    for(int i=0; i<c.size(); i++){
        cout << c[i] << endl;
        plik << c[i] << endl;

    }
    cout<<"czas mnozenia: "<< duration/100000 <<endl;
}
