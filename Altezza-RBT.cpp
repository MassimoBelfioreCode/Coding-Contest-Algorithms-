#include <iostream>
#include <fstream>
#include <string>
#define RED 1
#define BLACK 0

//ALBERI ROSSO-NERI, SONO ALBERI BINARI AUTOBILANCIATI

using namespace std;

template <typename H> class Nodo{
	private:
		
		Nodo<H>* left;
		Nodo<H>* right;
		Nodo<H>* father;
		H key;
		int color;
		
		public:	
					
			Nodo(H val){
				left = nullptr;
				right =	nullptr;
				father = nullptr;
				key = val;
				color = RED;
			}
			
			Nodo<H>* getLeft()const{ return left;}
			Nodo<H>* getRight()const{ return right;}
			Nodo<H>* getFather()const{ return father;}
			H getKey()const{ return key;}
			int getColor()const{ return color;}
			
			void setLeft(Nodo<H>* l){ this->left = l;}
			void setRight(Nodo<H>* r){ this->right = r;}
			void setFather(Nodo<H>* f){ this->father = f;}
			void setKey(H val){ this->key = val;}
			void setColor(int c){ this->color = c;}
			
};


template <typename H> class RBT{
	private:
		Nodo<H> *root;
		int size;		//numero di elementi contenuti
		
		
		Nodo<H>* search(H val){
			Nodo<H> *iter = this->root;
			while(iter != nullptr){
				if(val > iter->getKey()) iter = iter->getRight();
				else iter = iter->getLeft();
			}
			return iter;
		}
		
		
		Nodo<H>* minimo(Nodo<H>* ptr){
			Nodo<H> *tmp = ptr;
			if(!tmp){
				return nullptr;
			}
			while(tmp->getLeft()){
				tmp = tmp->getLeft();
			}
			return tmp;
		}
		
		
		Nodo<H>* massimo(Nodo<H>* ptr){
			Nodo<H> *tmp = ptr;
			if(!tmp){
				return nullptr;
			}
			while(tmp->getRight()){
				tmp = tmp->getRight();
			}
			return tmp;
		}
		
		
		void _preorder(ofstream& out, Nodo<H>* tmp){
			if(tmp!=nullptr){
				out << tmp->getKey() <<" ";
				_preorder(out, tmp->getLeft());
				_preorder(out, tmp->getRight());
			}
			out << endl;
		}
		
		
		void _inorder(ofstream& out, Nodo<H>* tmp){
			if(tmp!=nullptr){
				_inorder(out, tmp->getLeft());
				out << tmp->getKey() <<" ";
				_inorder(out, tmp->getRight());
			}
			out << endl; 
		}
		
		
		void _postorder(ofstream& out, Nodo<H>* tmp){
			if(tmp!=nullptr){
				_postorder(out, tmp->getLeft());
				_postorder(out, tmp->getRight());
				out << tmp->getKey() <<" ";
			}
			out << endl;
		}
		
		
		void insertRbFixUp(Nodo<H> *ptr){
				
				if(ptr == this->root){
					ptr->setColor(BLACK);
					return;
				}
				Nodo<H> *parent = ptr->getFather();
				Nodo<H> *grandparent = parent->getFather();
				Nodo<H> *uncle = getUncle(ptr);
				if(parent != nullptr && parent->getColor() == RED){
					//caso 1
					if(uncle != nullptr && uncle->getColor() == RED){
						parent->setColor(BLACK);
						uncle->setColor(BLACK);
						grandparent->setColor(RED);
						insertRbFixUp(grandparent);
					}
					else{
						
					   	if(isLeftChild(parent)){
							if(isLeftChild(ptr))
								swapColors(parent, grandparent);
							else{
								leftRotate(parent);
								swapColors(ptr, grandparent);
							}
							rightRotate(grandparent);
						}
						else{
							
							if(isLeftChild(ptr)){
								rightRotate(parent);
								swapColors(ptr, grandparent);
							}
							else{
								swapColors(parent, grandparent);
							}
								leftRotate(grandparent);
						}
					}
				}
				if(parent != nullptr && parent->getColor() == BLACK)
					return;
				// if parent->getColor() == BLACK exit
			}
		
		
		public:
			
			RBT(){
				root = nullptr;
				size = 0;
			}
			
			Nodo<H>* getRoot()const{ return root;}
			int getSize()const{ return size;}
			void setRoot(Nodo<H> *r){this->root = r;}
			void preorder(ofstream& out){ _preorder(out, root);}
			void inorder(ofstream& out){ _inorder(out, root);}
			void postorder(ofstream& out){ _postorder(out, root);}
			
			
			Nodo<H>* successore(Nodo<H>* tmp){
				if(!tmp){
					return nullptr;
				}	
				if(tmp->getRight()){
					return minimo(tmp->getRight());
				}
				Nodo<H> *p = tmp->getFather();
				while(p != nullptr && tmp->getKey() > p->getKey()){
					p = p->getFather();
				}
				return p;
			}
			
			
			Nodo<H>* predecessore(Nodo<H>* tmp){
				if(!tmp){
					return nullptr;
				}	
				if(tmp->getLeft()){
					return massimo(tmp->getLeft());
				}
				Nodo<H> *p = tmp->getFather();
				while(p != nullptr && tmp->getKey() < p->getKey()){
					p = p->getFather();
				}
				return p;
			}
			
			
			int isLeftChild(Nodo<H> *tmp){
				
				return tmp == tmp->getFather()->getLeft(); 
			}
			
			
			//nodo x e nodo y
			void leftRotate(Nodo<H> *x){
				if(x!=nullptr){
					Nodo<H> *y = x->getRight();
					insertNodeTop(x, y);
					x->setRight(y->getLeft());
					if(y->getLeft() != nullptr){
						y->getLeft()->setFather(x);	
					}
					y->setLeft(x);	
				}	
			}
			
			
			void rightRotate(Nodo<H> *x){
				Nodo<H> *y = x->getLeft();
				insertNodeTop(x, y);
				x->setLeft(y->getRight());
				if(y->getRight() != nullptr){
					y->getRight()->setFather(x);	
				}
				y->setRight(x);
			}
			
			
			void insertNodeTop(Nodo<H> *x, Nodo<H> *child){
				if(x->getFather()!=nullptr){
					if(isLeftChild(x)){
						x->getFather()->setLeft(child);
					}
					else x->getFather()->setRight(child);
				}
				else root = child;
				child->setFather(x->getFather());
				x->setFather(child);
			}
			
			
			Nodo<H>* getUncle(Nodo<H> *ptr){
				Nodo<H> *u = nullptr;
				if(ptr->getFather() == nullptr || ptr->getFather()->getFather() == nullptr)
					return nullptr;
				if(isLeftChild(ptr->getFather())){
					if(ptr->getFather()->getFather()->getRight() != nullptr)
						u = ptr->getFather()->getFather()->getRight();
				}
				else{
					if(ptr->getFather()->getFather()->getLeft() != nullptr)
						u = ptr->getFather()->getFather()->getLeft();
				}
				return u;
			}
			
			
			void swapColors(Nodo<H> *c1, Nodo<H> *c2){
				int col = c1->getColor();
				c1->setColor(c2->getColor());
				c2->setColor(col);
			}
			
			
			//metodo per inserire un nodo
			void insertRBT(H val){
				Nodo<H> *current = this->root;
				Nodo<H> *p = nullptr;

				while(current != nullptr){
					p = current;
					if(val >= current->getKey()){
						current = current->getRight();
					}
					else current = current->getLeft();
				}
				Nodo<H> *nuovo = new Nodo<H>(val);
				nuovo->setFather(p);
				if(p == nullptr){
					root = nuovo;
				}
				else if(val > p->getKey()){
					p->setRight(nuovo); 
				}
				else p->setLeft(nuovo);
				this->size++;
				insertRbFixUp(nuovo);
			}
			
			
			//fare il metodo ricorsivo
			int altezzaRBT(Nodo<H>* ptr){
    			if(ptr == NULL)
        		return 0;
    			int sx = altezzaRBT(ptr->getLeft());
    			int dx = altezzaRBT(ptr->getRight());

    			return 1 + max(sx, dx);
			}
			
			int getAltezza(){
				return altezzaRBT(this->root);
			}

};


int main(){
	
	ifstream in("input.txt");
	ofstream out("output.txt");
	
	for(int task = 0; task < 100; task++){
		
		string tipo;
		in >> tipo;
		int N; 
		in >> N;
			
			if(tipo == "int"){
				RBT<int> *bt = new RBT<int>();
				for(int k = 0; k < N; k++){
					int var; 
					in >> var;
					bt->insertRBT(var);
				}	
				out << bt->getAltezza() <<endl;
				delete bt;
			}
			else if (tipo == "double"){
				RBT<double> *bt = new RBT<double>();
				for(int k = 0; k < N; k++){
					double var; 
					in >> var;
					bt->insertRBT(var);
				}	
				out << bt->getAltezza() <<endl;
				delete bt;
			}
		}
	
	return 0;
}