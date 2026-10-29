#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename H> class BinaryMaxHeap{
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
			
			
			BinaryMaxHeap(int dim){
				heapSize = 0;
				this->count = 0; 
				arr = new H[dim];
			}
			
			//O(log(n))
			void _heapify(int idx){
				if(heapSize >= 1) count++;
				int l = Left(idx);
				int r = Right(idx);
				
				int max = idx;
				if(l <= heapSize && arr[l] > arr[max])
					 max = l;
				if(r <= heapSize && arr[r] > arr[max])
					max	= r;
				if(max != idx){
					swap(arr[idx], arr[max]);
					_heapify(max);
				}
			}
			
			//O(log(n))
			void enqueue(H v){
				heapSize++;
				arr[heapSize] = v;
				int i = heapSize;
				while(i > 1 && arr[i] > arr[Parent(i)]){
					swap(arr[i], arr[Parent(i)]);
					i = Parent(i);
				}
			}
			
			
			void buildMaxHeap(H* v, int n){
				arr = v;
				heapSize = n;
				for(int i = heapSize/2; i > 0; i--)
					_heapify(i);
			}
			
			
			//stampa gli elementi dell' heap
			void print(ofstream& out){
				for(int i = 1; i <= heapSize; i++){
					out << arr[i] << " ";
				}
				out << endl;
			}
			
			
			void extractMax(){
				swap(arr[1], arr[heapSize]);
				heapSize--;
				_heapify(1);
			}
			
			
			void heapSort(){
				int idx = heapSize;
				for(int i = 0; i < idx; i++){
					extractMax();
				}
				heapSize = idx;
			}
			
			/*
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
			BinaryMaxHeap<int> *bmh = new BinaryMaxHeap<int>(N*2);
			int *v = new int[200];
			for(int k = 1; k <= N; k++){
				int var; in >> var;
				v[k] = var;
				bmh->enqueue(v[k]);
			}
			bmh->buildMaxHeap(v, N);
			bmh->heapSort();
			out << bmh->getCount() <<" ";
			bmh->print(out);
		}
		else if(tipo == "double"){
			BinaryMaxHeap<double> *bmh = new BinaryMaxHeap<double>(N*2);
			double *v = new double[200];
			for(int k = 1; k <= N; k++){
				double var; in >> var;
				v[k] = var;
				bmh->enqueue(v[k]);
			}
			bmh->buildMaxHeap(v, N);
			bmh->heapSort();
			out << bmh->getCount() <<" ";
			bmh->print(out);
		}
		else if(tipo == "bool"){
			BinaryMaxHeap<bool> *bmh = new BinaryMaxHeap<bool>(N*2);
			bool *v = new bool[200];
			for(int k = 1; k <= N; k++){
				bool var; in >> var;
				v[k] = var;
				bmh->enqueue(v[k]);	
			}
			bmh->buildMaxHeap(v, N);
			bmh->heapSort();
			out << bmh->getCount() <<" ";
			bmh->print(out);
		}
		else if(tipo == "char"){
			BinaryMaxHeap<char> *bmh = new BinaryMaxHeap<char>(N*2);
			char *v = new char[200];
			for(int k = 1; k <= N; k++){
				char var; in >> var;
				v[k] = var;
				bmh->enqueue(v[k]);
			}
			bmh->buildMaxHeap(v, N);
			bmh->heapSort();
			out << bmh->getCount() <<" ";
			bmh->print(out);
		}
	}	
	
	
	in.close();
	out.close();
	
	return 0;
}
