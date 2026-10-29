#include <iostream>
#include <graph>


/*UTILIZZO LE CODE DI MIN PRIORIT à E IL MIN HEAP E I GRAFI PER IMPLEMENTARE DIJKSTRA
indice della matrice di adiacenza 
/class Pair implementa delle copie delle chiavi (int , T)
/siccome dobbiamo fare decreaseKey per chiamarla non sull' indice della relativa posizione del min heap ma sulla chiave 
potremmo utilizzare una tabella hash per mantenere questa corrispondenza */


template <class T> class PairMinHeap<T> : public MinBinaryHeap<T>{
	private:
		
		
		
		
		
		public:
			






};

/*void Dijkstra(...................){
	....
	PairMinHeap < pair<int , T>>* = new PairMinHeap<int, T>>(V);
	.....
}