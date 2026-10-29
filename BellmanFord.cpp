#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

class Edge{
protected:
    int weight; 
    int s, f;
public:
    Edge(int _s, int _f, int _w): s(_s), f(_f), weight(_w){}

    int getWeight(){return weight;}
    int getS(){return s;}
    int getF(){return f;}
};

template <class H>
class Grafo{
protected:
    int size, n, m;

    Edge** M; //un array di array è una coppia di puntatori ad un tipo Edge
    H* K;  // se k[i] -> key vuol dire che i è l' id della chiave key

    int findIndex(H x){
        for(int i = 0; i < size; i++){
            if(K[i] == x)
                return i;
        }
        return -1;
    }
public:
    Grafo(){
        size = 1000;
        n = m = 0;
        M = new Edge*[size]; //genero l'array di puntatori ad archi
        //adesso che abbiamo generato l'array di puntatori ad oggetti di tipo Arco procedo che
        //ogni elemento di questo array di puntatori ad Arco deve diventare un array di oggetti di tipo Arco
        //M[i] non è altro che un puntatore ad Arco 
        for(int i = 0; i < size; i++) 
		    M[i] = NULL;
		    
        K = new H[size];

        for(int i = 0; i < size; i++)
            K[i] = -1;
    }

    ~Grafo(){
        for(int i = 0; i < m; i++)
            delete M[i];
        delete [] M;
        delete [] K;
    }
	
    void addVertex(H x){
        K[n] = x; //lo metto nella successiva posizione vuota, cioè quella di posizione n
        n++;
    }
	
    void addEdge(H x, H y, int p){
        int i = findIndex(x);
        int j = findIndex(y);

        M[m] = new Edge(i, j, p);
        m++;
    }
 	
 	
    void BellmanFord(H s, H f, ofstream &out){
        int dist[n];
        int source = findIndex(s);

        int dest = findIndex(f);
        if(dest < 0 || source < 0){
            out << "inf." << endl;
        }
        for(int i = 0; i < n; i++)
            dist[i] = INT_MAX;

        dist[source] = 0;
		
        for(int i = 1; i < n; i++){
			for(int j = 0; j < m; j++){
				if(M[j] != nullptr){
					int u = M[j]->getS();
					int v = M[j]->getF();
					int w = M[j]->getWeight();
					
					if(dist[u] != INT_MAX && dist[u] + w < dist[v])
                		dist[v] = dist[u] + w;
				}	
			}
        }
    
        for(int i = 0; i < m; i++){
            if(M[i] != NULL){
                int u = M[i]->getS();
                int v = M[i]->getF();
                int w = M[i]->getWeight();

                if(dist[u] != INT_MAX && dist[u] + w < dist[v]){
                    out << "undef." << endl;
                    return;
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
    ifstream in;
	in.open("input.txt");
    ofstream out;
	out.open("output.txt");

    for(int i = 0; i < 100; i++){
        int n, m; in >> n >> m;
        string type; in >> type;

        if(type == "int"){
            Grafo<int>* t = new Grafo<int>();

            for(int j = 0; j < n; j++){
                int val; in >> val;
                t->addVertex(val);
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

            t->BellmanFord(s,f, out);
            delete t;
        }
        else{
            Grafo<double>* t = new Grafo<double>();

            for(int j = 0; j < n; j++){
                double val; in >> val;
                t->addVertex(val);
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
            t->BellmanFord(s,f, out);
            delete t;
        }
    }
    return 0;
}