#include <iostream>

using namespace std;

template <typename H> class Nodo{
	private:	
		Nodo<H> *next;
		
		public:
			H key;
			
			Nodo(H val){
				key = val;
				next = nullptr;
			}
			
			Nodo<H>* getNext()const{ return next;}
			void setNext(Nodo<H> *nx){ next = nx;}
	
};


template <typename H> class LinkedList{
	private:
		
		Nodo<H> *head;
		int size;
		
		public:
			
			LinkedList(){
				head = nullptr;
				size = 0;
			}
			
			int getSize()const{ return size;}
			Nodo<H>* getHead()const{ return this->head;}
			
			void insert(H x){
				Nodo<H> *nuovo = new Nodo<H>(x);
				nuovo->setNext(head);
				head = nuovo;
				this->size++;
			}
			
			Nodo<H>* ricerca(H val){
				Nodo<H> *current = this->head;
				while(current != nullptr){
					if(current->key == val) return current;
					else current = current->getNext();
				}
				return nullptr;
			}
			
			void cancellazione(H val){
				Nodo<H> *prev = nullptr;
				Nodo<H> *current = nullptr;
				if(head == nullptr){
					cout<<"lista vuota , impossibile rimuovere elementi"<<endl;
				}
				else if(this->head->key == val){
					prev = this->head;
					this->head = this->head->getNext();
					delete prev; 
					size--;	
				}
				else{
					prev = this->head;
					current = this->head->getNext();
					while(current != nullptr && current->key != val){
						prev = prev->getNext(); //oppure prev = current
						current = current->getNext();
					}
					
					if(current != nullptr){
						prev->setNext(current->getNext());
						delete current;
						size--;
					}
					else cout<<"elemento non nella lista" <<endl;
				}
			}
			
			
			void print(){
				Nodo<H> *i = this->head;
				while(i != nullptr){
					cout << i->key <<"-->";
					i = i->getNext();
				}
				cout <<"NIL" <<endl;
			}
			
};


template <typename H> class HashTable{
	private:
		
		LinkedList<H> *arr;		//implementazione con concatenamento
		int m;                  //numero di slots
		int count;
		
		public:

			HashTable(int length){
				count = 0;
				m = length;
				arr = new LinkedList<H>[m];	
			}
			
			int getM()const{ return m;}
			int getCount(){ return count;}
			LinkedList<H>* getArr(){ return arr;}
			
			//utilizzo metodo della divisione
			int hashFunction(H key)const{ return (key % this->m);}
			
			//inserimento
			HashTable<H>& hashInsert(H val){
				int index = hashFunction(val);
				arr[index].insert(val);
				count++;
				return *this;
			}
			
			//ricerca
			Nodo<H>* ricerca(H _key){
				int idx = hashFunction(_key);
				if(arr[idx].ricerca(_key) != nullptr) return arr[idx].ricerca(_key);
				else return nullptr;
			}
			
			//cancellazione
			void hashDelete(H _key){
				int idx = hashFunction(_key);
				Nodo<H> *tmp = arr[idx].ricerca(_key);
				if(tmp == nullptr){
					return;
				}
				arr[idx].cancellazione(tmp->key);
				this->count--;
			}
			
			//stampa
			void printHashTable(){
				for (int i = 0; i < this->getM(); i++){
					cout << "arr[" << i <<"]-->";
					arr[i].print();
				}	
				cout << endl;
			}
			
						
};


int main(){
	
	HashTable<int> *h = new HashTable<int>(15);
	h->hashInsert(12).hashInsert(32).hashInsert(21).hashInsert(1).hashInsert(9).hashInsert(40).hashInsert(25).hashInsert(36);
	h->printHashTable();
	cout <<"numero di elementi nella tavola Hash: "<< h->getCount() <<"\n";
	cout <<"elemento trovato o non trovato?: " << h->ricerca(21) << endl << endl;
	h->hashDelete(40);
	//h->hashDelete(1);
	h->printHashTable();
	cout <<"elemento trovato o non trovato?: " << h->ricerca(40) << endl;
	cout <<"elemento trovato o non trovato?: " << h->ricerca(1) << endl;
	cout <<"elemento trovato o non trovato?: " << h->ricerca(23) << endl;
	cout <<"elemento trovato o non trovato?: " << h->ricerca(25) << endl;
	cout <<"numero di elementi nella tavola Hash: " <<h->getCount() <<"\n\n";
	
	return 0;
}