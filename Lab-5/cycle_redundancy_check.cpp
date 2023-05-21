#include <iostream>
#include <vector>
using namespace std;

vector<int> xor2(vector<int> a, vector<int> b){
    vector<int> ans(a.size(), 0);
    for(int i=0; i<a.size(); i++){
        if(a[i] != b[i]){
            ans[i] = 1;
        }
    }

    return ans;
}

vector<int> modulo_2_division(vector<int> M, vector<int> P){
    int nP = P.size();
    int nM = M.size();

    // R = M/P
    vector<int> R(nP, 0);
    for(int j=0; j<nP; j++){
        R[j] = M[j];   
    }

    for(int i=nP; i<=nM; i++){
        int c = 0;
        for(int j=0; j<R.size(); j++){
            if(R[j] == 1){
                c++;
            }
        }
        if(c == 0){
            break;
        }

        if(R[0] == 0){
            vector<int> t(nP-1, 0);
            R = xor2(R, t);
        }
        else{
            R = xor2(R, P);
        }

        vector<int>::iterator it;
        it = R.begin();
        if(*it == 0){
            R.erase(it);
            if(i != nM){
                R.push_back(M[i]);
            }
        }
    }

    return R;
}

vector<int> CRC(vector<int> M, vector<int> P, int nM, int nP){
    int n = nP-1;
    // M = M*2^n
    for(int i=0; i<n; i++){
        M.push_back(0);
    }
    vector<int> R = modulo_2_division(M, P);

    return R;
}

int main(){
    int nM, nP;
    cout << "Enter the number of bits in input data: ";
    cin >> nM;
    cout << "Enter the number of bits in the polynomial generator (divisor): ";
    cin >> nP;

    vector<int> M(nM), P(nP);
    string sM, sP;
    cout << "Enter the data: ";
    cin >> sM;
    cout << "Enter the divisor: ";
    cin >> sP;

    for(int i=0; i<nM; i++){
        M[i] = sM[i]-'0';
    }
    for(int i=0; i<nP; i++){
        P[i] = sP[i]-'0';
    }

    vector<int> crc_value = CRC(M, P, nM, nP);
    string crc = "";

    for(int i=0; i<crc_value.size(); i++){
        crc += to_string(crc_value[i]);
    }
    cout << "CRC value: " << crc << endl;

    string transmitted = sP + crc;
    cout << "Transmitted data: " << transmitted << endl;

    string received;
    cout << "Enter the received data: ";
    cin >> received;

    vector<int> Re(received.size());
    for(int i=0; i<Re.size(); i++){
        Re[i] = received[i]-'0';
    }

    int n = nP-1;
    // M = M*2^n
    for(int i=0; i<n; i++){
        M.push_back(0);
    }

    vector<int> check = modulo_2_division(Re, P);

    for(int i=0; i<check.size(); i++){
        if(check[i] == 1){
            cout << "Errors detected" << endl;
            return 0;
        }
    }
    cout << "No errors detected" << endl;

    return 0;
}