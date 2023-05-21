// stop and wait protocol
#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <time.h>
using namespace std;


void print_stop_and_wait_protocol(vector<vector<int>> table, int max_wait){
    int range = 5;

    cout << "Frame_No Data Waiting_Time (Sec) Acknowledgement Resend\n";

    for(int i=0; i<table.size(); i++){
        cout << table[i][0] << "\t" << table[i][1] << "\t";
        int wait_time = rand()%range;
        sleep(min(wait_time, max_wait));
        if(wait_time > max_wait){
            for(int j=0; j<=max_wait; j++){
                cout << j << ", ";
            }
            cout << "\t\tNo\tResend\n";
            i--;
        }
        else{
            for(int j=0; j<=wait_time; j++){
                cout << j << ", ";
            }
            if(wait_time <= max_wait/2){
                cout << "\t";
            }
            cout << "\t\tYes\tNo\n";
        }
    }
}


int main(){
    int n;
    cout << "Enter the number of frames to be transmitted: ";
    cin >> n;

    srand(time(0));
    int max_wait = 3;
    int data_range = 100;

    vector<vector<int>> table;

    for(int i=0; i<n; i++){
        vector<int> row_data(2);
        row_data[0] = i+1;
        row_data[1] = rand()%data_range;
        table.push_back(row_data);
    }

    print_stop_and_wait_protocol(table, max_wait);
    cout << "All the data packets are transmitted\n";

    return 0;
}