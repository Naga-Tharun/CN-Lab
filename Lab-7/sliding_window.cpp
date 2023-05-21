// sliding window protocol
#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <time.h>
using namespace std;


int main(){
    int n;
    cout << "Enter number of frames: ";
    cin >> n;
    
    int window_size;
    cout << "Enter window size: ";
    cin >> window_size;

    srand(time(0));
    int max_wait = 3;

    vector<int> frames(n);
    for(int i=0; i<n; i++){
        frames[i] = i;
    }

    vector<int> sent(n);
    vector<int> receive(n);

    int left = 0;
    int right = window_size-1;
    int ans = 0;
    int i = 0;
    cout << "\nTransmission order: ";
    while(i < n){
        right = min(n, right);
        for(int j=left; j<=right; j++){
            if(sent[j] != 1){
                sent[j] = 1;
                ans++;
            }
            cout << j << ' ';
        }

        int x = rand()%5;

        if(x < max_wait){
            receive[i] = 1;
            i++;

            left++;
            right++;
        }
        else{
            for(int j = left; j<max(i, right); j++){
                sent[j] = 0;
            }
            left = i;
            right = left + window_size-1;
        }

    }
    cout << endl;
    cout << "Recieved order: ";
    for(int i=0; i<n; i++){
        cout << i << ' ';
    }
    cout << "\n\nNumber of transmissions happened: " << ans << "\n";
    cout << "All the data packets are transmitted\n";

}