#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector< vector<int> > distance_vector_routing(int n, vector< vector<int> > graph){

    vector<int> dist(n);
    vector<int> via(n);
    for(int source=0; source<n; source++){

        for (int i=0; i<n; i++) {
            dist[i] = graph[source][i];
            if (dist[i] != INT_MAX) {
                via[i] = source;
            }
        }

        for(int k=0; k<n; k++){
            for(int i=0; i<n; i++){
                for(int j=0; j<n; j++){
                    if(graph[i][k] != INT_MAX && graph[k][j] != INT_MAX && graph[i][j] > graph[i][k] + graph[k][j]){
                        graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                        via[j] = k;
                    }
                }
            }
        }
    }

    for(int i=0; i<n; i++){
        graph[i][i] = 0;
    }

    return graph;
}

int main(){
    int n;
    cout << "Enter the number of nodes or routers in the network: ";
    cin >> n;

    vector< vector<int> > graph(n, vector<int>(n, 0));
    cout << "Enter the weight or cost matrix: " << endl;

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> graph[i][j];
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(graph[i][j] == 0){
                graph[i][j] = INT_MAX;
            }
        }
    }

    vector< vector<int> > dvr_costs = distance_vector_routing(n, graph);

    for(int i=0; i<n; i++){
        cout << "\nFinal routing path for router " << i+1 << ":\n";
        for(int j=0; j<n; j++){
            if(dvr_costs[i][j] == INT_MAX){
                cout << "router " << i+1 << " via " << j+1 << " Distance INFINITY";
            }
            else{
                cout << "router " << i+1 << " via " << j+1 << " Distance " << dvr_costs[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
    
    return 0;
}