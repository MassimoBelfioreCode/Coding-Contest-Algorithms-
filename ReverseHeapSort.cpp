#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename H> class BinaryMinHeap{
	private:
		H* arr;
		int heapSize;
		int count;
		
		int Left(int i)const{ return i << 1;}
		int Right(int i)const{ return (i << 1)| 1;}
		int Parent(int i)const{ return i >> 1;}
		
		public:
			
			int getCount()const{ return this->count;}
			int getHeapSize()const{ return heapSize;}
			H* getArr(){ return arr;}
			
			
			BinaryMinHeap(int dim){
				heapSize = 0;
				this->count = 0; 
				arr = new H[dim];
			}
			
			//O(log(n))
			void _heapify(int idx){
				if(heapSize >= 1) count++;
				int l = Left(idx);
				int r = Right(idx);
				
				int min = idx;
				if(l <= heapSize && arr[l] < arr[min])
					 min = l;
				if(r <= heapSize && arr[r] < arr[min])
					min	= r;
				if(min != idx){
					swap(arr[idx], arr[min]);
					_heapify(min);
				}
			}
			
			//O(log(n))
			void enqueue(H v){
				heapSize++;
				arr[heapSize] = v;
				int i = heapSize;
				while(i > 1 && arr[i] < arr[Parent(i)]){
					swap(arr[i], arr[Parent(i)]);
					i = Parent(i);
				}
			}
			
			
			void buildMinHeap(H* v, int n){
				arr = v;
				heapSize = n;
				for(int i = heapSize/2; i > 0; i--)
					_heapify(i);
			}
			
			
			//stampa gli elementi dell' heap
			void print(ofstream& out){
				for(int i = 1; i <= heapSize; i++){
					out << arr[i] <<" ";
				}
				out << endl;
			}
			
			
			void extractMin(){
				swap(arr[1], arr[heapSize]);
				heapSize--;
				_heapify(1);
			}
			
			
			void heapSort(){
				int idx = this->heapSize;
				for(int i = 0; i < idx ; i++){
					this->extractMin();
				}
				heapSize = idx;
			}
			
			/*
			void heapSort(){
					
			}		
					[100] [23] [45] [2] [4]							[100]
																[23]    [45]
															[2]	   [4]
													
			
			 
			*/
			
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
			BinaryMinHeap<int> *bmh = new BinaryMinHeap<int>(N*2);
			int *v = new int[200];
			for(int k = 1; k <= N; k++){
				int var; in >> var;
				v[k] = var;
				bmh->enqueue(v[k]);
			}
			bmh->buildMinHeap(v, N);
			bmh->heapSort();
			out << bmh->getCount() <<" ";
			bmh->print(out);
		}
		else if(tipo == "double"){
			BinaryMinHeap<double> *bmh = new BinaryMinHeap<double>(N*2);
			double *v = new double[200];
			for(int k = 1; k <= N; k++){
				double var; in >> var;
				v[k] = var;
				bmh->enqueue(v[k]);
			}
			bmh->buildMinHeap(v, N);
			bmh->heapSort();
			out << bmh->getCount() <<" ";
			bmh->print(out);
		}
		else if(tipo == "bool"){
			BinaryMinHeap<bool> *bmh = new BinaryMinHeap<bool>(N*2);
			bool *v = new bool[200];
			for(int k = 1; k <= N; k++){
				bool var; in >> var;
				v[k] = var;
				bmh->enqueue(v[k]);	
			}
			bmh->buildMinHeap(v, N);
			bmh->heapSort();
			out << bmh->getCount() <<" ";
			bmh->print(out);
		}
		else if(tipo == "char"){
			BinaryMinHeap<char> *bmh = new BinaryMinHeap<char>(N*2);
			char *v = new char[200];
			for(int k = 1; k <= N; k++){
				char var; in >> var;
				v[k] = var;
				bmh->enqueue(v[k]);
			}
			bmh->buildMinHeap(v, N);
			bmh->heapSort();
			out << bmh->getCount() <<" ";
			bmh->print(out);
		}
	}	
	
	
	in.close();
	out.close();
	
	return 0;
}