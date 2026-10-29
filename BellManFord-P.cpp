#include <iostream>
#include <fstream>

using namespace std;


class Arco{
public:

    int s;
    int d;
    int w;

    Arco(int _s, int _d, int _w): s(_s), d(_d), w(_w){}

};


template <typename H> class Graph{
private:

    int size;
    int n;
    int m;

    Arco** arr;

    public:

        Graph(int nov){
            size = 1000;
            n = nov;
            m = 0;
            arr = new Arco*[size];
            for(int i = 0; i < size; i++){
                arr[i] = nullptr;
            }
        }

        ~Graph(){
            for(int i = 0; i < n; i++){
                arr[i] = nullptr;
            }
            delete [] arr;
        }


        void addEdge(int x, int y, int w){
            arr[m] = new Arco(x, y , w);
            m++;
        }


        void BellManFord(int source, int dest, int k, ofstream& out){
            int distances[size];

            for(int i = 0; i < n; i++){
                distances[i] = INT32_MAX;
            }

            distances[source] = 0;
            for(int i = 1; i < k+1; i++){
                for(int j = 0; j < m; j++){
                    if(arr[j] != nullptr){
                        int u = arr[j]->s;
                        int v = arr[j]->d;
                        int w = arr[j]->w;

                        if(distances[u] != INT32_MAX && distances[u] + w < distances[v])
                            distances[v] = distances[u] + w;
                    }
                }
            }

            if(distances[dest] != INT32_MAX)
                out << distances[dest] << endl;
            else
                out << "inf." << endl;

        }


};


int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");


    for(int t = 0; t < 100; t++){
        int N; in >> N;
        int M; in >> M;
        int K; in >> K;

        Graph<int> *g = new Graph<int>(N);

        for(int i = 0; i < M; i++){
            char parentesis;
            in >> parentesis;
            int u; in >> u;
            int v; in >> v;
            int w; in >> w;
            in >> parentesis;
            g->addEdge(u, v, w);
        }
        int v1; in >> v1;
        int v2; in >> v2;
        g->BellManFord(v1, v2, K, out);
        delete g;
    }

    return 0;
}
