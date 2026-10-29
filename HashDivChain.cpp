#include <iostream>
#include <fstream>
#include <list>
#include <string>

using namespace std;

//la funzione hash h(K) calcola a partire dalla chiave k l'indice nella struttura dati associato alla chiave(valore hash) tramite cui
//si accede alla chiave stessa.
/*creare una struttura dati tabella hash organizzata mediante il concatenamento per risolvere le collisioni e progettare la funzione
 hash con il metodo della divisione , cioè h(k) = k mod m con m numero primo possibilmente
*/ 

template <typename H > class HashTable{
	private:
	
		int m; //numero di slots
		list<H> *arr;
		int size; //contatore di elementi inseriti
					
		public:
			
			HashTable(int dim){
				size = 0;
				m = dim;
				arr = new list<H>[m];
			}
			
			int getM()const{ return m;}
			int getSize()const{ return this->size;}
			
			int hashFunction(int key)const{ return (key % this->m);} //calcola il bucket 
			
			//x è la chiave
			HashTable<H>* insert(H x){
				int tmp = hashFunction(x);
				arr[tmp].push_front(x);
				size++;
				return this;
			}
				
				
			void printHashTable(){
				for (int i = 0; i < this->getM(); i++){
					cout << i;
					for (auto x : arr[i])
						cout << " --> [" << x <<"]";
						//cout <<"\tkey Stored:"<< arr[i].size();
						cout << endl;
				}
			}
				
			void stampaSize(ofstream& out){
				for (int h = 0; h < this->getM(); h++){
					out << arr[h].size() <<" ";
				}
				out << endl;
			}
			
}; 

//restituendo un puntatore alla struttura dati si possono fare gli inserimenti in cascata, es ins(8).ins(23).ins(15) ecc 

int main(int argc, char *argv[]){
	
	/*
	HashTable<double> *h = new HashTable<double>(11);
	h->insert(23);
	h->insert(31);
	h->insert(4);
	h->insert(11);
	h->insert(56);
	h->insert(47);
	h->insert(9);
	h->insert(2);
	h->insert(13);
	h->insert(86);
	h->insert(65);
	
	
	h->printHashTable();
	cout << endl;
	h->stampaSize();
	*/
	
	ifstream in("input.txt");
	ofstream out("output.txt");
	
	
	
	for(int i = 0; i < 100; i++){
		
		// HashTable<int> *ht = new HashTable<int>(M)
		//array di M bucket(posizioni) dove ogni bucket punta ad una lista
		// N = 5        1, 3 , 53, 12, 17
		//tipo = int
		//int tmp; in >> tmp;
		//ins
		string tipo; 
		in >> tipo;
		int M; in >> M; //numero di bucket
		int N; in >> N; //numero di chiavi da inserire 
		//N compreso tra 100 e 200 , qui < 100
		//N sempre minore di 100
		 
		if(tipo == "int"){
			HashTable<int> *ht = new HashTable<int>(M);
			for(int j = 0; j < N; j++){

					int var; 
					in >> var;
					ht->insert(var);
				}
				ht->stampaSize(out);
				delete ht;
			}
			else if(tipo == "bool"){
				
				HashTable<bool> *ht = new HashTable<bool>(M);
				for(int j = 0; j < N; j++){
					bool var;
					in >> var;
					ht->insert(var);
				}
				ht->stampaSize(out);
				delete ht;
			}	
			else if(tipo == "double"){

				HashTable<double> *ht = new HashTable<double>(M);
				for(int j = 0; j < N; j++){
					double var;
					in >> var;
					ht->insert(var);
				}
				ht->stampaSize(out);
				delete ht;
			}
			else if(tipo == "char"){
				HashTable<char> *ht = new HashTable<char>(M);
				for(int j = 0; j < N; j++){
					char var;
					in >> var;
					ht->insert(var);
				}
				ht->stampaSize(out);
				delete ht;
			}
		}
	
	
	in.close();
	out.close();
	
	return 0;

}