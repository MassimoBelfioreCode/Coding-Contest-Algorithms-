#include <iostream>
#include <fstream>
using namespace std;

#define MAXN 20


class Nodo{
	public:
		
		int val;
		Nodo* next;
		
		Nodo(int v){
			val = v;
			next = nullptr;
		}
	
};


class LinkedList{
	
	private:
		
		Nodo *front; // head
		int n;
		
		
		/*		head----> null	
			
			head
			[ ]->
			
			front	front
			[	]<--[	]<--front
		
		*/
	public: 
	
		LinkedList(){
			n = 0;
			front = nullptr;
		}
		int getN(){ return n;}
		
		void insertInFront(int x){
			Nodo *nuovo = new Nodo(x);
			nuovo->next = front;
			front = nuovo;
			n++;
		}
		
		
		Nodo* search(int value){
			Nodo *traveler = this->front;
			if(!traveler)
				return nullptr;
			while(traveler != nullptr && traveler->val != value){
				traveler = traveler->next;
			}
			return traveler;
		}
		
		
		void print(){
			Nodo *i = this->front;
			while(i != nullptr){
				cout << i->val <<"-->";
				i = i->next;
			}
			cout <<"NIL" <<endl;
		}
		
		
		//metodo trovato a caso Romelu
		void destroyLinkedList(){
			while(front != nullptr){
				Nodo* tmp = this->front;
				front = front->next;
				n--;
				//return tmp;	
			}
		}
		
};


//rappresentazione del grafo attraverso la matrice di adiacenza
template <class T> class Graph {
private:
    bool **adj; //adj[MAXN][MAXN];
    int n, m, current;
    T** k; // k[i] -> key se i è l'id della chiave key
    
    int _search(T key) {
        for(int i=0; i<n; i++) {
            if( *k[i] == key ) return i;
        }
        return -1;
    }
    
public:
    Graph() {
        n = m = 0;
        adj = new bool*[MAXN];
        for(int i=0; i<MAXN; i++)
            adj[i] = new bool[MAXN];
        k = new T*[MAXN];
        for(int i=0; i<MAXN; i++) k[i] = NULL;
        current = 0;
    }
    
    Graph<T>& addNode(T key) {
        // inseriamo il nodo all'interno dell'array k
        k[n] = new T(key);
        n++;
        // aggiorniamo la matrice di adiacenza
        for(int i=0; i<n; i++) adj[n][i] = adj[i][n] = 0;
        return *this;
    }

    Graph<T>& cancNode(T key) {
        int i = _search(key);
        if(i<0) return *this;
        // sistemo l'array k
        k[i] = k[n-1];
        // sistemo la matrice adj
        for(int j=0; j<n; j++) {
            adj[i][j] = adj[n-1][j];
            adj[j][i] = adj[j][n-1];
        }
        n--;
        return *this;
    }

    Graph<T>& addEdge(T key1, T key2) {
        int i = _search(key1);
        int j = _search(key2);
        if(i<0 || j<0) return *this;
        adj[i][j] = 1;
        // se il grafo fosse non direzionato:
        // adj[j][i] = 1;
        m++;
        return *this;
    }

    Graph<T>& cancEdge(T key1, T key2) {
        int i = _search(key1);
        int j = _search(key2);
        if(i<0 || j<0) return *this;
        adj[i][j] = 0;
        // se il grafo fosse non direzionato:
        // adj[j][i] = 0;
        m--;
        return *this;
    }

    int sizeV() {
        return n;
    }
    
    int sizeE() {
        return m;
    }
    
    int existEdge(T key1, T key2) {
        int i = _search(key1);
        int j = _search(key2);
        if(i<0 || j<0) return 0;
        return adj[i][j];
    }
    
    int findNode(T key) {
        int i = _search(key);
        return i;
    }
    
    void adjSet(T key, ostream& out) {
        int i = _search(key);
        if(i<0) return;
        out << "{ ";
        for(int j=0; j<n; j++) {
            if(adj[i][j]==1)
                out << *k[j] << " ";
        }
        out << "}";
    }
    
    // iteratore
    void reset() {
        current = 0;
    }
    int hasNext() {
        return current<n;
    }
    T* next() {
        if(!hasNext()) return NULL;
        T* tmp = k[current];
        current++;
        return tmp;
    }
};

template <class H> ostream& operator<<(ostream& out, const Graph<H>& g) {
    Graph<H> tmp = g;
    tmp.reset();
    int id = 0;
    while(tmp.hasNext()) {
        H* e = tmp.next();
        out << "(" << id << "," << *e << ") --> ";
        id++;
        tmp.adjSet(*e, out);  
        out << endl;
    }
    return out; 
}

 
int main() {
    Graph<string> *g = new Graph<string>();
    cout << g->sizeV() << endl;
    g->addNode("Giuseppe");
    g->addNode("Carmelo");
    g->addNode("Riccardo");
    g->addNode("Vincenzo");
    g->addNode("Nicolò");
    cout << g->sizeV() << endl;
    cout << *g << endl;
    cout << g->findNode("Riccardo") << endl;
    cout << g->findNode("Aurelio") << endl;
    g->addEdge("Carmelo","Giuseppe");
    g->addEdge("Carmelo","Riccardo");
    g->addEdge("Riccardo","Vincenzo");
    g->addEdge("Vincenzo","Giuseppe");
    g->addEdge("Nicolò","Giuseppe");
    g->addEdge("Nicolò","Riccardo");
    g->addEdge("Nicolò","Vincenzo");
    cout << g->existEdge("Carmelo","Giuseppe") << endl;
    cout << g->existEdge("Carmelo","Riccardo") << endl;
    cout << *g << endl;
    //g->cancEdge("Nicolò","Riccardo");
    //cout << *g << endl;
    g->cancNode("Carmelo");
    cout << *g << endl;
}
