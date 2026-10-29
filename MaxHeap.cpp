#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> //fornisce i metodi atoi, atof, atol, utilizzate per convertire stringhe in numeri

using namespace std;

template <typename H> class MaxHeap{
	private:
		
		int heapSize;
		H* arr;
		int count;
		int n;
			
		int Left(int i){ return i << 1;}
		int Right(int i){ return (i << 1)| 1;}
		int Parent(int i){ return i >> 1;}
		
		void _heapify(int idx){
			if(heapSize >= 1) count++;
			int l = Left(idx);
			int r = Right(idx);
			int max = idx;
			
			if(l <= heapSize && arr[l] > arr[max]){
				max = l;
			} 
			if(r <= heapSize && arr[r] > arr[max]){
				max = r;
			}
			if(idx != max){
				swap(arr[max], arr[idx]);
				_heapify(max);
			}
		}
		
		
		public:
			
			
			
			MaxHeap(int dim): n(dim){
				heapSize = 0;
				count = 0;
				arr = new H[n];
			}
			
			int getHeapSize()const{ return this->heapSize;}
			int getCount()const { return this->count;}
			//enqueue, extractmax
			
			void enqueue(H v){
				heapSize++;
				arr[heapSize] = v;	
				int index = heapSize;
				while(index > 1 && arr[index] > arr[Parent(index)]){
					swap(arr[index], arr[Parent(index)]);
					index = Parent(index);
				}
			}
			 
				
			void extractMax(){
					swap( arr[1], arr[heapSize]);
					this->heapSize--;
					_heapify(1);
				}

			
			//tutti gli elementi nel sottoarray A[(floor(n/2))] + 1.....n sono foglie dell'albero binario che sono
			// già degli heap di un solo elemento 
			
			void stampa(ofstream& out){
				for(int i = 1; i <= this->heapSize; i++)
					out << arr[i] <<" ";
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
				MaxHeap<int> *mh = new MaxHeap<int>(200);
				for(int j = 0; j < N; j++){
					
					string s; in >> s;
					
					if(s == "extract"){
						mh->extractMax();
					}
					else{//int atoi(const char *str) //cifre da convertire, stringa, array di char;
						string v = s.substr(2, s.length());
						int var = stoi(v);
						mh->enqueue(var);
					}
				}	
					out << mh->getCount() << " ";
					mh->stampa(out);
					delete mh;		
			}
			if(tipo == "double"){
				MaxHeap<double> *mh = new MaxHeap<double>(200);
				for(int j = 0; j < N; j++){
					
					string s; in >> s;
					
					if(s == "extract"){
						mh->extractMax();
					}
					else{
						string v = s.substr(2, s.length());
						double var = stod(v);
						mh->enqueue(var);
					}
				}
				out << mh->getCount() << " ";
				mh->stampa(out);
				delete mh;
			}
			if(tipo == "bool"){
				MaxHeap<bool> *mh = new MaxHeap<bool>(200);
				for(int j = 0; j < N; j++){
					
					string s; in >> s;
					
					if(s == "extract"){
						mh->extractMax();
					}
					else {
						string v = s.substr(2 , s.length());
						bool var = stoi(v);
						mh->enqueue(var);
					}
				}
				out << mh->getCount() << " ";
				mh->stampa(out);
				delete mh;
			}
			if(tipo == "char"){
				MaxHeap<char> *mh = new MaxHeap<char>(200);
				for( int j = 0; j < N; j++){
					
					string s; in >> s;
					if(s == "extract"){
						mh->extractMax();
					}
					else{
						char var = s[2];
						mh->enqueue(var);
					}
				}
				out << mh->getCount() << " ";
				mh->stampa(out);
				delete mh;
			}
		}
	
	
	in.close();
	out.close();
	
	return 0;
	
}