#include <iostream>
#include <vector>
using namespace std;

vector<int> bit_destuffing(vector<int> input, int n){
    vector<int> output;

    int count = 0;
    for(int i=0; i<n; i++){
        if(input[i] == 1){
            count++;
        }
        if(input[i] == 0){
            count = 0;
        }

        output.push_back(input[i]);

        if(count == 5){
            i++;
            count = 0;
        }
    }

    return output;
}

int main(){
    int n;
    vector<int> input;

    cin >> n;
    for(int i=0; i<n; i++){
        int x;
        cin >> x;
        input.push_back(x);
    }

    vector<int> output = bit_destuffing(input, n);

    for(int i=0; i<output.size(); i++){
        cout << output[i];
    }
    cout << endl;

    return 0;
}