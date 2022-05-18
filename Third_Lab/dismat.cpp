#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool provjera(vector<vector<int>> graf, int vrh, vector<int> boje, int boja, int n) {

    for (int i = 0; i < n; i++)
        if (graf[vrh][i] && boja == boje[i])
            return false;
            
    return true;
}

bool bojanjeR(vector<vector<int>> graf, int vrh, int k, vector<int> boje, int n) {

    if (vrh == n)
        return true;

    for (int boja = 1; boja < k + 1; boja++) {
        if (provjera(graf, vrh, boje, boja, n)) {
            boje[vrh] = boja;
            if (bojanjeR(graf, vrh + 1, k, boje, n))
                return true;
            boje[vrh] = 0;
        }
    }

    return false;
}

bool bojanje(vector<vector<int>> graf, int k, int n) {

    vector<int> boje(n, 0);

    if (!bojanjeR(graf, 0, k, boje, n))
        return false;

    return true;
}

int main() {

    string ime_dat;

    cout << "Molimo upisite naziv datoteke: ";
    cin >> ime_dat;
    ifstream datoteka(ime_dat);

    int v, s;

    datoteka >> v >> s;

    vector<int> S;
    int pom;

    for (int i = 0; i < s; ++i) {
        datoteka >> pom;
        S.push_back(pom);
    }
    
    datoteka.close();

    vector<vector<int>> graf;  

    for (int i = 0; i < v; ++i) {
        vector<int> pom(v, 0);
        for (int j = 0; j < v; ++j)
            for (int k = 0; k < s; ++k)
                if (S[k] == abs(i-j) && i != j) 
                    pom[j] = 1;
        graf.push_back(pom);
    }

    /*
    for (int i = 0; i < v; ++i) {
        cout << "[";
        for (int j = 0; j < v; ++j)
            cout << graf[i][j] << ((j != v - 1) ? " " : "");
        cout << "]" << endl;
    }
    */

    for(int i = 1; i < v + 1; i++)
        if(bojanje(graf, i, v)) {
            cout << "Kromatski broj zadanog grafa je " << i << endl;
            break;
        }
}