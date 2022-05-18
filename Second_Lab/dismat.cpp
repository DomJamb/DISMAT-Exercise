#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    int n, a, b;
    cout << "Unesite redom, odvojene razmakom, parametre n, a i b: ";
    cin >> n >> a >> b;
    int arr[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                arr[i][j] = 0;
            }
            if (i < j) {
                arr[i][j] = (a * (i + 1) + b * (j + 1)) * (a * (i + 1) + b * (j + 1)) + 1;
            }
            if (i > j) {
                arr[i][j] = arr[j][i];
            }
        }
    }

    /*Greedy v1

    int min1 = INT32_MAX;
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        bool visited[n];
        for (int j = 0; j < n; ++j) {
            visited[j] = false;
        }
        int cnt = 0;
        int k = i;
        while (cnt < n - 1) {
            int min = INT32_MAX;
            int min_ind = 0;
            visited[k] = true;
            for (int j = 0; j < n; ++j) {
                if (arr[k][j] < min && arr[k][j] != 0 && !visited[j]) {
                    min = arr[k][j];
                    min_ind = j;
                }
            }
            sum += min;
            k = min_ind;
            visited[k] = true;          
            cnt++;
        }
        sum += arr[k][i]; 
        if (sum < min1) {
            min1 = sum;
        }
    }
    */

    /*Greedy v2

    int min1 = 0;
    bool visited[n];

    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }

    int prviVrh;
    int drugiVrh;
    int minBrid = INT32_MAX;

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (arr[i][j] < minBrid && arr[i][j] != 0) {
                minBrid = arr[i][j];
                prviVrh = i;
                drugiVrh = j;
            }
        }
    }

    visited[prviVrh] = true;
    visited[drugiVrh] = true;
    min1 += arr[prviVrh][drugiVrh];

    int minPrvi = INT32_MAX;
    int minDrugi = INT32_MAX;

    for (int i = 0; i < n; ++i) {
        if (arr[prviVrh][i] != 0 && i != drugiVrh && arr[prviVrh][i] < minPrvi) {
            minPrvi = arr[prviVrh][i];
        }
    }

    for (int i = 0; i < n; ++i) {
        if (arr[drugiVrh][i] != 0 && i != prviVrh && arr[drugiVrh][i] < minDrugi) {
            minDrugi = arr[drugiVrh][i];
        }
    }

    int pocetniVrh;
    int zavrsniVrh;
    
    if (minPrvi < minDrugi) {
        pocetniVrh = prviVrh;
        zavrsniVrh = drugiVrh;
    } else {
        pocetniVrh = drugiVrh;
        zavrsniVrh = prviVrh;
    }

    int i = pocetniVrh;
    int cnt = 0;
    while (cnt < n - 2) {
        int min = INT32_MAX;
        int min_ind = 0;
        for (int j = 0; j < n; ++j) {
            if (arr[i][j] < min && arr[i][j] != 0 && !visited[j]) {
                min = arr[i][j];
                min_ind = j;
            }
        }
        min1 += min;
        i = min_ind;
        visited[i] = true;          
        cnt++;
    }
    min1 += arr[i][zavrsniVrh];
    */

    //Greedy v3

    int min1 = 0;
    bool visited[n];

    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }

    int prviVrh;
    int drugiVrh;
    int minBrid = INT32_MAX;

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (arr[i][j] < minBrid && arr[i][j] != 0) {
                minBrid = arr[i][j];
                prviVrh = i;
                drugiVrh = j;
            }
        }
    }

    visited[prviVrh] = true;
    visited[drugiVrh] = true;
    min1 += arr[prviVrh][drugiVrh];

    int cnt = 0;
    do {
        int minPrvi = INT32_MAX;
        int minPrviInd;
        int minDrugi = INT32_MAX;
        int minDrugiInd;

        for (int i = 0; i < n; ++i) {
            if (arr[prviVrh][i] != 0 && !visited[i] && arr[prviVrh][i] < minPrvi) {
                minPrvi = arr[prviVrh][i];
                minPrviInd = i;
            }
        }

        for (int i = 0; i < n; ++i) {
            if (arr[drugiVrh][i] != 0 && !visited[i] && arr[drugiVrh][i] < minDrugi) {
                minDrugi = arr[drugiVrh][i];
                minDrugiInd = i;
            }
        }      
    
        if (minPrvi < minDrugi) {
            prviVrh = minPrviInd;
            min1 += minPrvi;
            visited[prviVrh] = true;
        } else {
            drugiVrh = minDrugiInd;
            min1 += minDrugi;
            visited[drugiVrh] = true;   
        }
        cnt++;
    } while (cnt < n -2);

    min1 += arr[prviVrh][drugiVrh];

    //Bruteforce
    
    int vrhovi[n];
    for (int i = 0; i < n; ++i) {
        vrhovi[i] = i + 1;
    } 

    int min2 = INT32_MAX;
    do {
        int sum = 0;
        int j;
        for (j = 0; j < n - 1; ++j) {
            sum += arr[vrhovi[j]-1][vrhovi[j+1]-1];
        }
        sum += arr[vrhovi[j]-1][vrhovi[0]-1];
        if (sum < min2) {
            min2 = sum;
        }
    } while(next_permutation(vrhovi + 1, vrhovi + n));


    cout << "Pohlepni algoritam nalazi ciklus duljine " << min1 << endl;
    cout << "Iscrpni algoritam nalazi ciklus duljine " << min2 << endl;
    if (min1 == min2) {
        cout << "Pohlepni algoritam na ovom grafu daje optimalno rjesenje! " << endl;
    } else {
        cout << "Pohlepni algoritam na ovom grafu ne daje optimalno rjesenje! " << endl;
    }
}