#include <iostream>
#include <fstream>
#include <string>

using namespace std;


template <typename H> class BMH{

	private:
	H* arr;
	int count;
	int heapSize;	
		
	int Left(int i){ return i << 1;}
	int Right(int i){ return (i << 1)| 1;}
	int Parent(int i){ return i >> 1;}
		
		
		public:
			
		int getCount()const{ return count;}
		int getHeapSize()const{ return heapSize;}
		H* getArr()const{ return arr;}
		
		BMH(){
			count = 0; 
			heapSize = 0;
		}
		
		
		void _heapify(int i){
			if(heapSize >= 1) count++;
			int l = Left(i);
			int r = Right(i);
			int max = i;
			if( l <= heapSize && arr[l] > arr[max])
				max = l;
			if( r <= heapSize && arr[r] > arr[max])
				max = r;
			if(max != i){
				swap(arr[max], arr[i]);
				_heapify(max);
			}	
		}	


		void buildMaxHeap(H* v, int n){
			heapSize = n;
			arr = v;
			for(int i = heapSize/2; i > 0; i--){
				_heapify(i);
			}
		}
		
		void extractMax(){
				swap(arr[1], arr[heapSize]);
				heapSize--;
				_heapify(1);
		}
		
		void printCount(ofstream& out){
			out << this->count << endl;
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
			BMH<int> *mh = new BMH<int>();
			int *vec = new int[N*2];
			for(int j = 1; j <= N; j++){
				int tmp;
				in >> tmp;
				vec[j] = tmp;
			}
			mh->buildMaxHeap(vec, N);
			for(int k = 0; k != N; k++){
				mh->extractMax();
			}
			mh->printCount(out);
		}
		if(tipo == "double"){
			BMH<double> *mh = new BMH<double>();
			double *vec = new double[N*2];
			for(int j = 1; j <= N; j++){
				double tmp;
				in >> tmp;
				vec[j] = tmp;
			}
			mh->buildMaxHeap(vec, N);
			for(int k = 0; k != N; k++){
				mh->extractMax();
			}
			mh->printCount(out);
		}
		if(tipo == "bool"){
			BMH<bool> *mh = new BMH<bool>();
			bool *vec = new bool[N*2];
			for(int j = 1; j <= N; j++){
				bool tmp;
				in >> tmp;
				vec[j] = tmp;
			}
			mh->buildMaxHeap(vec, N);
			for(int k = 0; k != N; k++){
				mh->extractMax();
			}
			mh->printCount(out);
		}
		if(tipo == "char"){
			BMH<char> *mh = new BMH<char>();
			char *vec = new char[N*2];
			for(int j = 1; j <= N; j++){
				char tmp;
				in >> tmp;
				vec[j] = tmp;
			}
			mh->buildMaxHeap(vec, N);
			for(int k = 0; k != N; k++){
				mh->extractMax();
			}
			mh->printCount(out);
		}
	}
	
	in.close();
	out.close();
	
	return 0;
}
 