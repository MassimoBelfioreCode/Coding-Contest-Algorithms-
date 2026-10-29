#include <iostream>
#include <fstream>
#include <list>  // liste doppiamente linkate
#include <cmath>
#include <string>

using namespace std;

//matrice hash che risolve le collisioni mediante il concatenamento
//funzione hash progettata con metodo della moltiplicazione, è un' euristica
//funzione hash prende un parametro costante c = 0.61803


template <typename H> class HashTable{
	private:
		int size; // numero di elementi inseriti
		int m; // numero di celle o bucket meglio dire della tabella hash organizzata con concatenamento
		const double c = 0.61803; // rappresenta la costante A con valore 0 < A < 1
		
		list<H> *ptr;
		
		
		public:

			int getSize()const{ return size;}
			int getM()const{ return m;}
			
			list<H>* getPtr()const{ return ptr;}
			
			HashTable(int length){
				size = 0;
				m = length;
				ptr = new list<H>[m];
			}
			
			
			int hashFunction(H key){ return floor(m*(fmod(key*c ,1.0)));}
			//int hashFunction(int key){ return floor(m*((key*c-floor(key*c)));} anche questa va bene
			
			void insertKey(H key){
				int pos = hashFunction(key);
				ptr[pos].push_front(key);
				this->size++;
			}
			
			
			void counting(ofstream& out){
				for(int i = 0; i < this->getM(); i++){
					out << ptr[i].size() <<" ";
				}
				out << endl;	
			}
			
};



int main(){
		
	ifstream in("input.txt");
	ofstream out("output.txt");
	
	
	
	for(int i = 0; i < 100; i++){
		
		string tipo; 
		in >> tipo;
		int M; in >> M; //numero di bucket
		int N; in >> N; //numero di chiavi da inserire 
		
		 
		if(tipo == "int"){
			HashTable<int> *ht = new HashTable<int>(M);
			for(int j = 0; j < N; j++){

					int var; 
					in >> var;
					ht->insertKey(var);
				}
				ht->counting(out);
				delete ht;
			}
			else if(tipo == "double"){

				HashTable<double> *ht = new HashTable<double>(M);
				for(int j = 0; j < N; j++){
					double var;
					in >> var;
					ht->insertKey(var);
				}
				ht->counting(out);
				delete ht;
			}
			else if(tipo == "bool"){
				
				HashTable<bool> *ht = new HashTable<bool>(M);
				for(int j = 0; j < N; j++){
					bool var;
					in >> var;
					ht->insertKey(var);
				}
				ht->counting(out);
				delete ht;
			}	
			else if(tipo == "char"){
				HashTable<char> *ht = new HashTable<char>(M);
				for(int j = 0; j < N; j++){
					char var;
					in >> var;
					ht->insertKey(var);
				}
				ht->counting(out);
				delete ht;
			}
		}
	
	
	in.close();
	out.close();
	
	return 0;

}
