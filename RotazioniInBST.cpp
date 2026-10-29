#include <iostream>
#include <fstream>
#include <cstring>
#define BLACK 0
#define RED 1

//char* arr; è un puntatore ad un array di caratteri

using namespace std;

//utilizzare le struct per la classe Nodo


//un oggetto può essere indicato con una struct, cioè con un tipo di dato struttura, tipo di dato definito dal programmatore 
//dove mantengo attributi di tipo diverso dell'oggetto, detti campi, in abbondanza possono essere.
//data di acquisto : array di caratteri di dimensione 8 Es 10 12 1992 , char data_acquisto[8], char titolo[14]

template <typename H> class Nodo{
	private:
		Nodo<H> *left;
		Nodo<H> *right; 
		Nodo<H> *parent;
		H val;
		int color;
		
	public:
		Nodo(H value){
			this->val = value;
			this->left = nullptr;
			this->right = nullptr;
			this->parent = nullptr;
			color = 1;
		}
		
		Nodo<H>* getLeft()const{ return left;}
		Nodo<H>* getRight()const{ return right;}
		Nodo<H>* getParent()const{ return parent;}
		H getVal()const{ return val;}
		int getColor()const{ return color;}
		
		void setLeft(Nodo<H>* l){ this->left = l;}
		void setRight(Nodo<H>* r){ this->right = r;}
		void setParent(Nodo<H>* p){ this->parent = p;}
		void setValue(H v){ this->val = v;}
		void setColor(int c){ this->color = c;}

}; //variabili di tipo struct vanno qui dopo le graffe , es: n1, n2, n3; 
//oppure posso dichiarare le variabili scrivendo struct Nodo n1, n2, n3; in C
//le variabili di tipo struttura possono essere assegnate ad altre variabili di tipo struttura
//ES. Nodo n4 = n2;

//una variabile di tipo struttura si può inizializzare in qualunque punto del programma, anche alla definizione
// n1 = {.., .. , ..., ...,}; i valori dei campi della struct vanno nei puntini nell'ordine in cui sono stati definiti
/* struct Semaforo{
		char sopra[5];
		char centro[6];
		char sotto[5];
		int secondi;
		int numero;
	} s1 = {"Rosso", "Giallo", "Verde", 100, (...default)};
	
	si può usare sizeof sulle variabili di tipo struct : cout << "syzeof(semaforo1): " << syzeof(s1); 30 bit per esempio
	
	accesso ai campi di una variabile di tipo struttura si usa l' operatore punto, per dargli valori del suo tipo ecc... 
	ES :  <variabile struct>.campo = valore;
	s1.numero = 2;
	
	le struct si possono annidare, struct di struct, posso creare nuova struttura con solo i campi in comune delle 2 struct
	e dopodichè dichiararla come campo di tipo struct in entrambe le strutture iniziali
	struct cliente, struct impiegato , struct info
	
	struct cliente{
		int saldo;
		struct info anagrafica;
		....
	}
	
	stessa cosa nella struct impiegato, vedi libro fondamenti c++ pag 258
	
	Accesso a nome di campo anagrafica 
	Cliente c1;
	c1.anagrafica.nome = "Gerry";
	
	si possono annidare anche più di 2 struct ,si accede con operatori punto in cascata
	
	un array di clienti di tipo struct si definisce così : struct Cliente clienti[82];
	gli array di strutture sono utili per rappresentare database
	accesso ai campi es: cliente[4].saldo = 30;
	si possono inizializzare, cioè riempire gli array dando i valori ai campi fra parentesi graffe , pag 260

	si possono utilizzare le strutture anche come parametri di funzioni.
	Ecc...
*/


template <typename H> class BST{
	private:
		
		Nodo<H> *root;
		int size;
		
		//ricerca
			Nodo<H>* ricerca(H key){
				Nodo<H> *explorer = this->root;
				while(explorer != nullptr && explorer->getVal() != key){
					if(key > explorer->getVal()) explorer = explorer->getRight();
					else explorer = explorer->getLeft();	
				}
				return explorer;
			}
			
		//minimo
			Nodo<H>* minimo(Nodo<H> *tmp){
				if(!tmp){
					return nullptr;
				}
				while(tmp->getLeft() != nullptr){
					tmp = tmp->getLeft();
				}
				return tmp;
			}
			
			
		public:
			
			//costruttore
			BST(){
				root = nullptr;
				size = 0;
			}
			
			//metodi getter
			Nodo<H>* getRoot()const{ return this->root;}
			void setRoot(Nodo<H> *r){ return this->root = r;}
			int getSize()const{ return size;}
			
			 
			//inserimento di un nuovo nodo
			void insertBST(H value){
				Nodo<H> *current = this->root;
				Nodo<H> *p = nullptr;
				while(current != nullptr){
					p = current;
					if(value <= current->getVal()){
						current = current->getLeft();
					}
					else current = current->getRight();
				}
				Nodo<H> *nuovo = new Nodo<H>(value);
				nuovo->setParent(p);
				if(root == nullptr){
					root = nuovo;
				}
				if(p != nullptr && value < p->getVal()){
					p->setLeft(nuovo);
				}
				else p->setRight(nuovo);
				size++;
			}
			
			
			BST<H>& remove(H value){
				Nodo<H> *curr = ricerca(value);
				if(!curr){
					cout <<"nessun elemento da cancellare presente nel BST con la chiave passata" <<endl;
					return *this; 
				}
				if(curr->getLeft() != nullptr && curr->getRight() != nullptr){
					Nodo<H> *succ = successore(curr);
					curr->setValue(succ->getVal());
					succ->setValue(value);
					curr = succ;
				}
				Nodo<H> *p = curr->getParent();
				Nodo<H> *y = curr->getLeft();
				if(!y) y = curr->getRight();
				if(p){
					if(p->getVal() >= value){
						p->setLeft(y);
					}
					else p->setRight(y);
				}
				else root = y;
				if(y) y->setParent(p);
				size--;
				return *this;
			}
			
			
			int isLeftChild(Nodo<H>* nd){
				return nd == nd->getParent()->getLeft();
			}
				
			//rotazione sinistra, Esempio IMPORTANTE nel quaderno di SpiderMan utilizzato per il lab di processing
			//x deve diventare il figlio di y
			
			void leftRotate(H key){
				Nodo<H> *x = ricerca(key);
				if(x!=nullptr){
					Nodo<H> *y = x->getRight();
					insertNodeTop(x, y); //mi garantisce lo spostamento verso l'alto di y
					//sistemo i puntatori, quelli di alpha e gamma non li tocco
					x->setRight(y->getLeft());
					if(y->getLeft() != nullptr) //testo se esiste effetivamente il nodo betha, quaderno di spiderman
						y->getLeft()->setParent(x); //prendo il suo puntatore verso il padre
					//avendo spostato il nodo betha posso aggiornare il puntatore sinistro di y facendolo puntare adesso a x 
					y->setLeft(x);
				}
			}
			 
			//rotazione destra, //simmetrica della sinistra, tutti i right diventano left e viceversa
			void rightRotate(H val){
				Nodo<H> *x = ricerca(val);
					if(x!=nullptr){
					Nodo<H> *y = x->getLeft();
					insertNodeTop(x, y); 
					x->setLeft(y->getRight());
					if(y->getRight() != nullptr) 
						y->getRight()->setParent(x); 
					y->setRight(x);
				}
			}
			  
			 
			//successore di un nodo
			Nodo<H>* successore(Nodo<H> *tmp){
				Nodo<H> *explorer = tmp;
				if(!explorer){
					return nullptr;
				}
				else if(explorer->getRight()){
					return minimo(explorer->getRight());
				}
				Nodo<H> *p = explorer->getParent();
				while( p != nullptr && explorer->getVal() > p->getVal()){
					p = p->getParent();
				}
				return p; 
			}
					
			
			void insertNodeTop(Nodo<H> *x, Nodo<H> *child){
				if(x->getParent() != nullptr){ //genitore esistente
					if(isLeftChild(x)){
						x->getParent()->setLeft(child);
					}
					else x->getParent()->setRight(child);
				}
				else root = child;
				child->setParent(x->getParent());
				x->setParent(child); //sistemo il puntatore di x che puntava al suo vecchio padre per farlo puntare al nuovo padre
			}
			 
			//ricerca del minimo
			Nodo<H>* min(){ return minimo(root);}
			//void postOrder(ofstream& out){ _postOrder(root, out);}
			//void inOrder(ofstream& out){ _inOrder(root, out);}
			//void preOrder(ofstream& out){ _preOrder(root, out);}
			//mi sposto con minimo+successore
			void _preOrder(Nodo<H> *tmp, ofstream& out){
				if(tmp!=nullptr){
					out << tmp->getVal() <<" ";
					_preOrder(tmp->getLeft(), out);
					_preOrder(tmp->getRight(), out);
				}
			}
			
			//visita inorder
			void _inOrder(Nodo<H>* tmp, ofstream& out){
				if(tmp!=nullptr){
					_inOrder(tmp->getLeft(), out);
					out << tmp->getVal() <<" ";
					_inOrder(tmp->getRight(), out);
				}
			}	
			
			//visita postorder  _postOrder(out, t->getRoot())
			void _postOrder(Nodo<H>* tmp, ofstream& out){
				if(tmp!=nullptr){
					_postOrder(tmp->getLeft(), out);
					_postOrder(tmp->getRight(), out);
					out << tmp->getVal() <<" ";
				}
			}
};

/*
template <typename H> void BST<H>::print(ofstream& out, string t){
	if(t == "postorder"){
		_postOrder(out, root);
	}
	else if(t == "inorder"){
		_inOrder(out, root);
	}
	else if(t == "preorder"){
		_preOrder(out, root);
	}
	out << endl;
}

*/

int main(){
	
	
	ifstream in("input.txt");
	ofstream outt("output.txt");
	
	/*
	if(!in){
		cerr <<"incapace di aprire file di input: "<< "input.txt" << endl;
		return -1;
	}
	*/
	
	for(int task = 0; task < 100; task++){

		string tipo;
		in >> tipo;
		int N; in >> N;
		int M; in >> M;
		string vis;
		in >> vis;
		
		if(tipo == "int"){
			
			BST<int> *bt = new BST<int>();	
	
			for(int i = 0; i < N+M; i++){
				
				char simbolo;
				in >> simbolo;
				
				if(simbolo == 'i'){
					in.ignore(3);
					int v;
					in >> v;
					bt->insertBST(v);
				}
				else if(simbolo == 'c'){
					in.ignore(4);
					int v;
					in >> v;
					bt->remove(v);	
				}
				else if(simbolo == 'l'){
					in.ignore(4);
					int v;
					in >> v;
					bt->leftRotate(v);
				}
				else if(simbolo == 'r'){
					in.ignore(5);
					int v;
					in >> v;
					bt->rightRotate(v);	
				}
			}
			
				if(vis == "postorder"){
					bt->_postOrder(bt->getRoot(), outt);
					outt << endl;
				}
				else if(vis == "preorder"){
					bt->_preOrder(bt->getRoot(), outt);
					outt << endl;
				}
				else if(vis == "inorder"){
					bt->_inOrder(bt->getRoot(), outt);
					outt << endl;
				}
		}
		else if(tipo == "double"){
			BST<double> *bt = new BST<double>();  //0 <= N <= 200
			for(int j = 0; j < N+M; j++){
				
				char simbolo;
				in >> simbolo;
				
				if(simbolo == 'i'){
					in.ignore(3); //ignora i caratteri 0,1,2,3
					double v;
					in >> v;
					bt->insertBST(v); 
				}
				else if(simbolo == 'c'){
					in.ignore(4);
					double v;
					in >> v;
					bt->remove(v);	
				}
				else if(simbolo == 'r'){
					in.ignore(5);
					double v;
					in >> v;
					bt->rightRotate(v);
				}
				else if(simbolo == 'l'){
					in.ignore(4);
					double v;
					in >> v;
					bt->leftRotate(v);
				}
			}
			
				if(vis == "postorder"){
					bt->_postOrder(bt->getRoot(), outt);
					outt << endl;
				}
				else if(vis == "preorder"){
					bt->_preOrder(bt->getRoot(), outt);
					outt << endl;
				}
				else if(vis == "inorder"){
					bt->_inOrder(bt->getRoot(), outt);
					outt << endl;
				}
			
		}
	} 
	
	in.close();
	outt.close();
	
	return 0;
}

//il metodo put() inserisce un unico carattere nel flusso di output
// ostream& put(char& c);
//il metodo write() viene usato per inserire una stringa nel flusso di output: ostream& write(const char* buf, int num);
//entrambi i metodi restituiscono un oggetto cout.
// frigorifero.put(p);    //quaderno.write("Leggins Luccicanti", 7)
//num rappresenta il numero di caratteri della stringa da visualizzare
//visualizzare caratteri nel flusso di output cout.put('B');