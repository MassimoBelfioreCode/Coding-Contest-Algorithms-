#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

class Edge{
private:
    int peso;
    int s, f;
public:
    Edge(int _s, int _f, int _p): s(_s), f(_f), peso(_p){}

    int getPeso(){return peso;}
    int getS(){return s;}
    int getF(){return f;}
};

template <class H>
class Grafo{
private:
    int len, n, m;

    Edge** M;
    H* K;

    int findIndex(H x){
        for(int i = 0; i < len; i++){
            if(K[i] == x)
                return i;
        }
        return -1;
    }
public:
    Grafo(){
        len = 1000;
        n = m = 0;
        M = new Edge*[len];
        for(int i = 0; i < len; i++)
            M[i] = NULL;

        K = new H[len];

        for(int i = 0; i < len; i++)
            K[i] = -1;
    }

    ~Grafo(){
        for(int i = 0; i < m; i++)
            delete M[i];
        delete [] M;
        delete [] K;
    }

    void addNodo(H x){
        K[n] = x;
        n++;
    }

    void addEdge(H x, H y, int p){
        int i = findIndex(x);
        int j = findIndex(y);

        M[m] = new Edge(i, j, p);
        m++;
    }

    void Dijkstra(H s, H f, ofstream &out){
        int dist[n];
        int source = findIndex(s);

        int dest = findIndex(f);
        if(dest < 0 || source < 0){
            out << "inf." << endl;
            return;
        }
        for(int i = 0; i < n; i++)
            dist[i] = INT_MAX;

        dist[source] = 0;
		H *predecessors = new H[n];
		for(int i = 0; i < n; i++){
        	predecessors[i] = -1;
		}
		
        for(int i = 1; i < n; i++){
            for(int j = 0; j < m; j++){
                if(M[j] != NULL){
                    int u = M[j]->getS();
                    int v = M[j]->getF();
                    int w = M[j]->getPeso();
                    if(dist[u] != INT_MAX && dist[u] + w < dist[v]){
                        dist[v] = dist[u] + w;
                        predecessors[v] = u;
                    }
                }
            }
        }
    	
        if(dist[dest] != INT_MAX)
            out << dist[dest] << endl;
        else
            out << "inf." << endl;
    }
};


int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        int n, m; in >> n >> m;
        string type; in >> type;

        if(type == "int"){
            Grafo<int>* t = new Grafo<int>();

            for(int j = 0; j < n; j++){
                int val; in >> val;
                t->addNodo(val);
            }
            for(int j = 0; j < m; j++){
                char tmp; in >> tmp;
                int x, y, p;
                in >> x;
                in >> y;
                in >> p;
                in >> tmp;
                t->addEdge(x, y, p);
            }

            int s, f; in >> s >> f;

            t->Dijkstra(s,f, out);
            delete t;
        }
        else{
            Grafo<double>* t = new Grafo<double>();

            for(int j = 0; j < n; j++){
                double val; in >> val;
                t->addNodo(val);
            }
            for(int j = 0; j < m; j++){
                char tmp; in >> tmp;
                double x, y;
                int p;
                in >> x;
                in >> y;
                in >> p;
                in >> tmp;
                t->addEdge(x, y, p);
            }

            double s, f; in >> s >> f;
            t->Dijkstra(s,f, out);
            delete t;
        }
    }
    
    return 0;
}