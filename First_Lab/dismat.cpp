#include <iostream>
#include <cmath>

using namespace std;

double formula(double k1, double k2, double a0, double a1, int index) {

    double a = 1;
    double b = -k1;
    double c = -k2;

    double d = pow(b, 2) - 4*a*c;

    double x1, x2, l1, l2, rez;

    //Cramer
    
    if (d == 0) {
        x1 = x2 = (-b) / (2*a);

        l1 = a0;
        l2 = (a1 - a0 * x1) / x2;

        rez = l1 * pow(x1, index) + l2 * index * pow(x2, index);
    } else {
        x1 = (-b - sqrt(d)) / (2*a);
        x2 = (-b + sqrt(d)) / (2*a);

        l1 = (a0 * x2 - a1) / (x2 - x1);
        l2 = (a1 - a0 * x1) / (x2 - x1);

        rez = l1 * pow(x1, index) + l2 * pow(x2, index);
    }

    return rez;
}
/*
double recursive(double k1, double k2, double a0, double a1, int index) {
    if (index == 0) {
        return a0;
    } else if (index == 1) {
        return a1;
    } else {
        return k1 * recursive(k1, k2, a0, a1, index - 1) +
               k2 * recursive(k1, k2, a0, a1, index - 2);
    }
}
 
double dynamic(double k1, double k2, double a0, double a1, int index) {
    double arr[index + 1];
    arr[0] = a0;
    arr[1] = a1;
    for (int i = 2; i <= index; ++i) {
        arr[i] = k1 * arr[i-1] + k2 * arr[i-2];
    }
    return arr[index];
}
*/

double recursive(double k1, double k2, double a0, double a1, int trazeni_index, int brojac) {
    if (trazeni_index == brojac) {
        return k1 * a1 + k2 * a0;
    } else {
        return recursive(k1, k2, a1, k1 * a1 + k2 * a0, trazeni_index, brojac + 1);
    }
}

int main() {

    double k1, k2, a0, a1;
    int trazeni_index;

    cout << "Unesite prvi koeficijent λ_1 rekurzivne relacije: ";
    cin >> k1;
    cout << "Unesite drugi koeficijent λ_2 rekurzivne relacije: ";
    cin >> k2;
    cout << "Unesite vrijednost nultog clana niza a_0: ";
    cin >> a0;
    cout << "Unesite vrijednost prvog clana niza a_1: ";
    cin >> a1;
    cout << "Unesite redni broj n trazenog clana niza: ";
    cin >> trazeni_index;

    cout << "Vrijednost n-tog clana niza pomocu formule: " << formula(k1, k2, a0, a1, trazeni_index) << endl;
    cout << "Vrijednost n-tog clana niza iz rekurzije: " << recursive(k1, k2, a0, a1, trazeni_index, 2) << endl;

    return 0;
}