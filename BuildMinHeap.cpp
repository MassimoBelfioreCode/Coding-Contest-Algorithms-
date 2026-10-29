#include <iostream>
#include <fstream>
#include <cstring>

using namespace std; 

template <typename H> class BinaryMinHeap{

	private:
		
		//metodi get
		int Left(int i) const{ return i <<1;}
		int Right(int i)const{ return (i << 1)|1;}
		int Parent(int i)const{ return i>>1;}
		
		int heapSize;
		H* v;
			
		public:
			
			BinaryMinHeap(){
				
				this->heapSize = 0;
			}			
		
			int getHeapSize()const{ return heapSize;}
			H* getV() const{ return v;}
			
				
			
		void _heapify(int i){
			//if(i > heapSize) return;
			int l = Left(i);
			int r = Right(i);
			int min = i;
			
			if(l <= this->heapSize && v[l] < v[min])
				min = l;
			if(r <= this->heapSize && v[r] < v[min])
				min = r;
			if(min != i){
				swap(v[i], v[min]);
				_heapify(min);
			}
		}
			
				
			void buildMinHeap(H* arr, int n){
				this->heapSize = n;
				v = arr;
				for(int i = this->getHeapSize()/2; i > 0; i--){
					_heapify(i);
				}
			}
			
		
		void stampa(ofstream& out){
			for(int j = 1; j <= this->heapSize; j++){
                out << v[j]<<"\t";
	    	}
	    	out << endl;
		}
 
			template <typename T> 
			friend ostream& operator<<(ostream& os, const BinaryMinHeap<T>& b); 
			
};


template <typename H> ostream& operator <<(ostream& os, const BinaryMinHeap<H>& b){
	for(int j = 1; j< b.getHeapSize(); j++){
		os << b.v[j] << " ";
	}
	os << "\n";
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
				BinaryMinHeap<int> *mh = new BinaryMinHeap<int>();
				int *arr = new int[200];
				for(int j = 1; j <= N; j++){
					int tmp;
					in >> tmp;
					arr[j] = tmp;
				}
				mh->buildMinHeap(arr, N);
				mh->stampa(out);
				delete mh;
				delete []arr;
			}
			else if(tipo == "double"){
				BinaryMinHeap<double> *mh = new BinaryMinHeap<double>();
				double *arr = new double[200];
				for(int j = 1; j <= N; j++){
					double aux;
					in >> aux;
					arr[j] = aux;
				}
				mh->buildMinHeap(arr, N);
				mh->stampa(out);
				delete mh;
				delete []arr;
			}
			else if(tipo == "bool"){
				BinaryMinHeap<bool> *mh = new BinaryMinHeap<bool>();
				bool *arr = new bool[200];
				for(int j = 1; j <= N; j++){
					bool aux;
					in >> aux;
					arr[j] = aux;
				}
				mh->buildMinHeap(arr, N);
				mh->stampa(out);
				delete mh;
				delete []arr; 
			}
			else if(tipo == "char"){
				BinaryMinHeap<char> *mh = new BinaryMinHeap<char>();
				char *arr = new char[200];
				for(int j = 1; j <= N; j++){
					char aux;
					in >> aux;
					arr[j] = aux;
				}
				mh->buildMinHeap(arr, N);
				mh->stampa(out);
				delete mh;
			 	delete []arr;
			}
		}
	 
	
	in.close();
	out.close();
	
	return 0;
}
