#include <iostream>
#include <vector>
#include <math.h>
#include <bitset>
#include <climits>
using namespace std;

int find_n_r(int n){
    int r = 0;
    while(pow(2, r) < n+r+1){
        r++;
    }

    return r;
}

vector<string> convert_to_binary(int n){

    vector<string> binary_index(n);
    for(int i=1; i<=n; i++){
        int x = (int)(log2(i));
        string n_bin = bitset<64>(i).to_string().substr(64-x-1);
        binary_index[i-1] = n_bin;
    }

    return binary_index;
}

vector<int> encode(vector<int> data, int n, int nr){
    vector<int> encoded_data(n+nr);
    int tn = n+nr;
    vector<int> parity_index(nr);
    for(int i=0; i<nr; i++){
        parity_index[i] = pow(2, i)-1;
        encoded_data[parity_index[i]] = INT_MIN;
    }

    int j=0;
    for(int i=0; i<n; i++){
        while(encoded_data[j] == INT_MIN){
            j++;
        }
        encoded_data[j] = data[i];
        j++;
    }

    vector<string> binary_index = convert_to_binary(tn);

    for(int i=0; i<nr; i++){
        int count_1 = 0;
        for(int j=0; j<tn; j++){
            if(binary_index[j].size() < i){
                continue;
            }
            int x = binary_index[j].size();
            string t = binary_index[j];
            if(encoded_data[j] == 1 && t[x-i-1] == '1'){
                count_1++;
            }
        }
        if(count_1%2 == 0){
            encoded_data[parity_index[i]] = 0;
        }
        else{
            encoded_data[parity_index[i]] = 1;
        }
    }

    return encoded_data;
}

vector<int> find_parity(vector<int> data, int nr){
    vector<string> binary_index = convert_to_binary(data.size());
    int tn = data.size();

    vector<int> parity;

    for(int i=0; i<nr; i++){
        int count_1 = 0;
        for(int j=0; j<tn; j++){
            if(binary_index[j].size() < i){
                continue;
            }
            int x = binary_index[j].size();
            string t = binary_index[j];
            if(data[j] == 1 && t[x-i-1] == '1'){
                count_1++;
            }
        }
        if(count_1%2 == 0){
            parity.push_back(0);
        }
        else{
            parity.push_back(1);
        }
    }

    return parity;
}


int main(){
    int n;
    cout << "Enter the number of bits in the input data: ";
    cin >> n;

    vector<int> input_data(n);
    string input = "";
    cout << "Enter the data: ";
    cin >> input;

    for(int i=0; i<n; i++){
        input_data[i] = input[i]-'0';
    }

    int nr = find_n_r(n);
    int tn = n+nr;

    vector<int> encoded_data = encode(input_data, n, nr);

    cout << "Transmitted data (Encoded data or hamming code): ";
    for(int i=0; i<tn; i++){
        cout << encoded_data[i];
    }
    cout << endl;

    vector<int> output_data;
    string output = "";
    cout << "Enter the received data: ";
    cin >> output;

    for(int i=0; i<output.size(); i++){
        output_data.push_back(output[i]-'0');
    }

    vector<int> parity_output = find_parity(output_data, nr);

    string binary_index = "";
    for(int i=0; i<parity_output.size(); i++){
        binary_index +=  to_string(parity_output[i]);
    }

    int i=0;
    while(i < binary_index.size() && binary_index[i] != '1'){
        i++;
    }
    binary_index = binary_index.substr(i);

    if(binary_index.size() == 0){
        cout << "No errors in the received data" << endl;
        return 0;
    }

    int index = 0;
    for(int i=binary_index.size()-1; i>=0; i--){
        if(binary_index[i] == '1'){
            index += pow(2, binary_index.size()-1-i);
        }
    }
    cout << "Error detected at bit position " << index << endl;
    
    return 0;
}