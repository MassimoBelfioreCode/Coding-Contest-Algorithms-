#include <iostream>

using namespace std;

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
		
		int getN()const{ return n;}
		Nodo* getFront()const{ return this->front;}
		
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
		
		
		//metodo trovato a casa Romelu
		void destroyLinkedList(){
			while(front != nullptr){
				Nodo* tmp = this->front;
				front = front->next;
				n--;
				//return tmp;	
			}
		}
		
};


int main(){
	
	LinkedList *l = new LinkedList();
	l->insertInFront(4);
	l->insertInFront(9);
	l->print();
	cout <<"Key 4 Address: " << l->search(4) << endl;
	cout << "Dimension: " << l->getN() <<endl;
	l->destroyLinkedList();
	l->print();
	cout <<"Dimension: "<< l->getN()<<endl;
	
	return 0;
}