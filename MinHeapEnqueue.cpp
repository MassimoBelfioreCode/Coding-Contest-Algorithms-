#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//si devono inserire gli elementi in coda con la procedura enqueue


template <typename H> class BinaryMinHeap{
	private:
		
		int heapsize;
		H* vec;	
		
		int left(int i)const{ return i << 1;}
		int right(int i)const{ return (i << 1)|1;}
		int parent(int i)const{ return i >> 1;}
		
		
		public:
			 
			BinaryMinHeap(){
				heapsize = 0;
			}
			
			BinaryMinHeap(int n){
				heapsize = 0;
				vec = new H[n];
			}
			
			int getHeapsize()const{ return heapsize;}
			H* getVett()const{ return vec;}
			
			/*
			void scambia(int i, int j){
				int aux = i;
				i = j;
				j = aux;
			}
			*/
		
			void _heapify(int i){
				int l = left(i);
				int r = right(i);
				int min = i;
				
				if(l <= heapsize && vec[l] < vec[min])
					min = l;
				if(r <= heapsize && vec[r] < vec[min])
					min = r;
				if(min != i){
					swap(vec[i], vec[min]);
					_heapify(min);
				}
			}
			
			
			void buildMinHeap(H* v, int n){
				this->heapsize = n;
				vec = v;
				for(int i = heapsize/2; i > 0; i--){
					_heapify(i);
				}
			}
			
			
			void enqueue(H x){
				heapsize++;
				vec[heapsize] = x;
				int j = heapsize;
				while(j > 1 && vec[parent(j)] > vec[j]){
					swap(vec[parent(j)], vec[j]);
					j = parent(j);
				}
			}
			
			
			void stampa(ofstream& out){
				for(int i = 1 ; i <= heapsize; i++){
					out << vec[i] <<" ";
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
		int N;
		in >> N;
		
			if(tipo == "int"){
				BinaryMinHeap<int> *mh = new BinaryMinHeap<int>(200);
				for(int j = 1; j <= N; j++){
					int aux;
					in >> aux;
					mh->enqueue(aux);
				}
				mh->stampa(out);
				delete mh;
			}
			else if(tipo == "double"){
				BinaryMinHeap<double> *mh = new BinaryMinHeap<double>(200);
				for(int j = 1; j <= N; j++){
					double aux;
					in >> aux;
					mh->enqueue(aux);
				}
				mh->stampa(out);
				delete mh;
			}
			else if(tipo == "bool"){
				BinaryMinHeap<bool> *mh = new BinaryMinHeap<bool>(200);
				for(int j = 1; j <= N; j++){
					bool aux;
					in >> aux;
					mh->enqueue(aux);
				}
				mh->stampa(out);
				delete mh; 
			}
			else if(tipo == "char"){
				BinaryMinHeap<char> *mh = new BinaryMinHeap<char>(200);
				for(int j = 1; j <= N; j++){
					char aux;
					in >> aux;
					mh->enqueue(aux);
				}
				mh->stampa(out);
				delete mh;
			}
		}
		
	in.close();
	out.close();
	
	return 0;
}
