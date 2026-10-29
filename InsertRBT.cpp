#include <iostream>
#include <fstream>
#include <cstring>
#define R 1
#define B 0

using namespace std;

template <typename H> class Nodo{
	private:
		Nodo<H> *left, *right, *father;
		H key;
		int color;
		
		public:
			 
			Nodo(){}
			
			Nodo(H val){
				left = right = father = nullptr;
				key = val;
				color = R;
			}
			
			H getKey()const{ return key;}
			Nodo<H>* getLeft()const{ return left;}
			Nodo<H>* getRight()const{ return right;}
			Nodo<H>* getFather()const{ return father;}
			int getColor()const{ return color;}
			
			void setFather(Nodo<H> *f){ this->father = f;}
			void setRight(Nodo<H> *r){ this->right = r;}
			void setLeft(Nodo<H> *l){ this->left = l;}
			void setKey(H val){ this->key = val;}
			void setColor(int c){this->color = c;}
			
};


template <typename H> class RBT{
	private:
		Nodo<H> *root;
		int size;
		
		Nodo<H>* search(H val){
			Nodo<H> *iter = this->root;
			while(iter != nullptr){
				if( val < iter->getKey()) iter = iter->getLeft();
				else iter = iter->getRight();
			}
			return iter;
		}
		
		
		void _preorder(ofstream& out, Nodo<H> *tmp){
			//if(!tmp) return;
			if(tmp){
				out << "(" << tmp->getKey() <<" "<< this->whichColor(tmp->getColor()) <<") ";
				_preorder(out, tmp->getLeft());
				_preorder(out, tmp->getRight());
			}
		}
		
		
		void _postorder(ofstream& out, Nodo<H> *tmp){
			if(tmp){
				_postorder(out, tmp->getLeft());
				_postorder(out, tmp->getRight());
				out << "(" << tmp->getKey() <<" "<< this->whichColor(tmp->getColor()) <<") ";
			}
		}
		
		
		void _inorder(ofstream& out, Nodo<H> *tmp){
			if(tmp){
				_inorder(out, tmp->getLeft());
				out << "(" << tmp->getKey() <<" "<< this->whichColor(tmp->getColor()) <<") ";
				_inorder(out, tmp->getRight());
			}
		}
		
		
		Nodo<H>* minimum(Nodo<H>* tmp){
			Nodo<H> *min = tmp;
			if(!min){
				return nullptr;
			}
			while(min->getLeft()){
				min = min->getLeft();
			}
			return min;
		}
		
		
		Nodo<H>* maximum(Nodo<H>* tmp){
			Nodo<H> *max = tmp;
			if(max == nullptr){
				return nullptr;
			}   
			while(max->getRight()){
				max = max->getRight();
			}
			return max;
		}
		
		
		Nodo<H>* successore(Nodo<H>* current){
			if(!current){
				return nullptr;
			}
			if(current->getRight()){
				return minimum(current->getRight());
			}
			Nodo<H> *parent = current->getFather();
			while(parent != nullptr && current->getKey() > parent->getKey()){
				parent = parent->getFather();
			}
			return parent;
		}
		
		
		Nodo<H>* predecessore(Nodo<H>* current){
			if(!current){
				return nullptr;
			}
			if(current->getLeft()){
				return maximum(current->getLeft());
			}
			Nodo<H> *parent = current->getFather();
			while(parent != nullptr && current->getKey() < parent->getKey()){
				parent = parent->getFather();
			}
			return parent;
		}
		
		
		void insertOnTop(Nodo<H>* x, Nodo<H>* child){
			//devo inserire il nodo y al posto del padre di x	 
			if(x->getFather() != nullptr){
				
				if(isLeftChild(x)){
					x->getFather()->setLeft(child);
				}
				else
					x->getFather()->setRight(child);
			}
			else root = child;
			child->setFather(x->getFather());
			x->setFather(child);
		}
		
		
		int isLeftChild(Nodo<H>* ptr){
			return ptr == ptr->getFather()->getLeft();
		}
		
		 
		void leftRotate(Nodo<H>* x){
			if(x != nullptr){
				Nodo<H> *y = x->getRight();
				insertOnTop(x, y);
				x->setRight(y->getLeft());
				if(y->getLeft() != nullptr){
					y->getLeft()->setFather(x);
				}
				y->setLeft(x);
			}
		}
		
		
		void rightRotate(Nodo<H>* x){
			if(x != nullptr){
				Nodo<H> *y = x->getLeft();
				insertOnTop(x, y);
				x->setLeft(y->getRight());
				if(y->getRight() != nullptr){
					y->getRight()->setFather(x);
				}
				y->setRight(x);
			}
		}
		
		
		Nodo<H>* getUncle(Nodo<H> *ptr){
			Nodo<H> *u = nullptr;
			if(ptr->getFather() == nullptr || ptr->getFather()->getFather() == nullptr)
				return nullptr;
			if(isLeftChild(ptr->getFather())){

				if(ptr->getFather()->getFather()->getRight() != nullptr){
					u = ptr->getFather()->getFather()->getRight();
				}
			}
			else{
				if(ptr->getFather()->getFather()->getLeft() != nullptr);
					u = ptr->getFather()->getFather()->getLeft();	
				}
			return u;
		}
		
		
		Nodo<H>* getSibling(Nodo<H> *ptr){
			Nodo<H> *s = nullptr;
			if(ptr->getFather() == nullptr){
				return nullptr;
			}
			if(isLeftChild(ptr))
				s = ptr->getFather()->getRight();
			else s = ptr->getFather()->getLeft();
			return s;
		}
		
		
		void swapColorsRBT(Nodo<H> *x, Nodo<H> *y){
			int col = x->getColor();
			x->setColor(y->getColor());
			y->setColor(col);
		}
		
		
		void swapKeys(Nodo<H> *x, Nodo<H> *y){
			H aux = x->getKey();
			x->setKey(y->getKey());	
			y->setKey(aux);
		}
		
		
		void _insertRbFixUp(Nodo<H> *ptr){
			
			if(ptr == this->root){
				ptr->setColor(B);
				return;	
			}
			
			Nodo<H> *parent = ptr->getFather();
			Nodo<H> *uncle = this->getUncle(ptr);
			Nodo<H> *grandparent = parent->getFather();
			
			if(parent != nullptr && parent->getColor() == R){
				
				if(uncle != nullptr && uncle->getColor() == R){
					parent->setColor(B);
					uncle->setColor(B);
					grandparent->setColor(R);
					_insertRbFixUp(grandparent);
				}
				else{
					
					if(isLeftChild(parent)){
						
						if(isLeftChild(ptr)){
							swapColorsRBT(parent, grandparent);
						}
						else{
							leftRotate(parent);
							swapColorsRBT(ptr, grandparent);				
						}
						rightRotate(grandparent);
					}
					else{
						
						if(isLeftChild(ptr)){
							rightRotate(parent);
							swapColorsRBT(ptr, grandparent);
						}
						else{
							swapColorsRBT(parent, grandparent);
						}
						leftRotate(grandparent);
					}
				}
			}
			
			if(parent != nullptr && parent->getColor() == B)
				return;
		}
		
		
		void deleteRbFixUp(Nodo<H> *ptr);
		
		
		public:
			
			RBT(){
				size = 0; 
				root = nullptr;
			}
			

				void insertRBT(H x){
				Nodo<H> *iter = root;	
				Nodo<H> *p = nullptr;
				while(iter != nullptr){
					p = iter;
					if( x >= iter->getKey())
						iter = iter->getRight();
					else iter = iter->getLeft();
				}
				//alloco un nuovo nodo
				Nodo<H> *nuovo = new Nodo<H>(x);
				nuovo->setFather(p);
				
				if(p == nullptr){
					root = nuovo;
				}
		 		else if( x < p->getKey()){
					p->setLeft(nuovo);
				}
				else{
					p->setRight(nuovo);
				}
				
				_insertRbFixUp(nuovo);
				this->size++;
			}
			
			
			/*
				[x] 	LIFO  extract order x, y ,z, A, B, C 
				[y]
				[z]
				[A]
				[B]
				[C]
			*/
			
			
			char whichColor(int col){
				if(col) return 'R';
			 return 'B';
			}
			
			
			void printPreOrder(ofstream& out){
				//use a Stack data structure
				_preorder(out, root);
			} 
			
			
			void printPostOrder(ofstream& out){
				//utilizzo una coda e parto da minimo
				//da qui vado prima a sx, poi a dx e poi rad
				_postorder(out, root);
			}
			
			void printInOrder(ofstream& out){
				
				_inorder(out, root);
			}
			
			int Size()const{ return this->size;}
			Nodo<H>* getRoot()const{ return root;}
			
			void cancRBT(H key);
			
};

//GALAXY TREE , Nodo<H> *groot, Each Node is a Galaxy and each Galaxy has Planets information and sometimes Satellars

int main(){
	
	ifstream in;
	in.open("input.txt");
	ofstream out;
	out.open("output.txt");
	
	for(int i = 0; i < 100; i++){
		string tipo;
		in >> tipo;
		int N;
		in >> N;
		string visita;
		in >> visita;
		
		if(tipo == "int"){
			RBT<int> *bt = new RBT<int>();
			for(int j = 0; j < N; j++){
				int val;
				in >> val;
				bt->insertRBT(val);
			}
			
			if(visita == "inorder"){
				bt->printInOrder(out);
			}
			else if(visita == "preorder"){
				bt->printPreOrder(out);
			}
			else if(visita == "postorder"){
				bt->printPostOrder(out);
			}
			delete bt;
		}
		else{
			
			RBT<double> *bt = new RBT<double>();
			for(int j = 0; j < N; j++){
				double val;
				in >> val;
				bt->insertRBT(val);
			}
			
			if(visita == "inorder"){
				bt->printInOrder(out);
			}
			else if(visita == "preorder"){
				bt->printPreOrder(out);
			}
			else if(visita == "postorder"){
				bt->printPostOrder(out);
			}
			delete bt;	
		}
		out << endl;
	}
	
	in.close();
	out.close();
	
	return 0;
	
}
