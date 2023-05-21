#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> pii;

vector< vector<int> > dijkstra(const vector< vector<int> >& adjacency_matrix){
    int n = adjacency_matrix.size();
    vector< vector<int> > forwarding_tables(n, vector<int>(n, -1));

    for(int src=0; src<n; src++){
        vector<int> dist(n, INT_MAX);
        vector<int> prev(n, -1);
        priority_queue< pii, vector<pii>, greater<pii> > pq;

        dist[src] = 0;
        pq.push({0, src});

        while(!pq.empty()){
            int u = pq.top().second;
            pq.pop();

            for(int v=0; v<n; v++){
                if(adjacency_matrix[u][v] > 0){
                    int alt = dist[u] + adjacency_matrix[u][v];
                    if(alt < dist[v]){
                        dist[v] = alt;
                        prev[v] = u;
                        pq.push({dist[v], v});
                    }
                }
            }
        }

        for(int dest=0; dest<n; dest++){
            if(src == dest){
                continue;
            } 
            int next_hop = dest;
            
            while(prev[next_hop] != src){
                next_hop = prev[next_hop];
            }
            forwarding_tables[src][dest] = next_hop;
        }
    }

    return forwarding_tables;
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

    vector< vector<int> > forwarding_tables = dijkstra(graph);

    for(int i=0; i<forwarding_tables.size(); i++){
        cout << "Forwarding table for node " << i << ":\n";
        cout << "Destination\tNext hop\n";
        for(int j=0; j<forwarding_tables[i].size(); j++){
            if(i != j){
                cout << j << "\t\t" << forwarding_tables[i][j] << '\n';
            }
        }
        cout << endl;
    }

    return 0;
}