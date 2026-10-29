#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


template <typename H> class Coppia{
	private:
		
		H x;
		H y;
		
		public:
			
		Coppia(H v1, H v2){
			x = v1;
			y = v2;	
		}
		
		friend bool operator > (Coppia& C1, Coppia& C2){
			if(C1.x > C2.x)
				return 1;
			else if(C1.x == C2.x && C1.y > C2.y)	
				return 1;
			return 0;
		}
		
		friend bool operator == (Coppia& C1, Coppia& C2){
			if(C1.x == C2.x && C1.y == C2.y)
				return 1;
			return 0;
		}
		
		H getX()const{ return x;}
		H getY()const{ return y;}
		void setX(H val){ this->x = val;}
		void setY(H val){ this->y = val;}
		
		friend ostream& operator <<(ostream& os, Coppia &c ){
			return os << "(" << c.x <<" "<< c.y <<")";
		}
		
};


template <typename H> class BinaryMaxHeap{
	private:
		
		int heapSize;
		int count;
		Coppia<H>** arr; 
		
		int Left(int i){ return i << 1;}
		int Right(int i){ return (i << 1)| 1;}
		int Parent(int i){ return i >> 1;}
		
		public:
			
			int getHeapSize()const{ return heapSize;}
			int getCount()const{ return this->count;}
			
			
			BinaryMaxHeap(){
			 	heapSize = 0;
			 	count = 0;
			}
			
			 
			~BinaryMaxHeap(){
				delete []arr;
			}
			
			//(confrontare per valore x e w fra coppie)
			void _heapify(int i){
				if(heapSize >= 1) count++;
				int l = Left(i);
				int r = Right(i);
				int max = i;
				if(l <= heapSize && *arr[l] > *arr[max])
					max = l;
				if(r <= heapSize && *arr[r] > *arr[max])
					max = r;
				if(max != i){
					swap(arr[max], arr[i]);
					_heapify(max);
				}	
			}
			
			
			void buildMaxHeap(Coppia<H>** vec, int n){
				arr = vec;
				heapSize = n;
				
				for(int i = heapSize/2; i > 0; i--){
					_heapify(i);
				}
			}
			
			
			Coppia<H>* extractMax(){
				swap(arr[1], arr[heapSize]);
				Coppia<H>* ext = arr[heapSize];
				heapSize--;
				_heapify(1);
				return ext;
				//return arr[heapSize+1];
			}
			
};

//funzione template
template <typename H> void print(Coppia<H>** v, int size, ofstream& out){
	for(int i = 1; i <= size; i++){
		out << *v[i] <<" ";
	}
	out << endl;
}


int main(){
	
	ifstream in("input.txt");
	ofstream out("output.txt");
	
	for(int task = 0; task < 100; task++){
		
		string tipo;
		in >> tipo;
		int N;
		in >> N; //numero di coppie in input
		  
		if(tipo == "int"){
			
			Coppia<int>** vec = new Coppia<int>*[N+1];
			BinaryMaxHeap<int>* bmh = new BinaryMaxHeap<int>();
			
			for(int j = 1; j <= N; j++){
				char parentesis; in >> parentesis;
				int v1; in >> v1;
				int v2; in >> v2;
				in >> parentesis;
				vec[j] = new Coppia<int>(v1, v2);
			}
			
			Coppia<int>** vo = new Coppia<int>*[N+1];
            bmh->buildMaxHeap(vec, N);
            for(int k = N; k > 0; k--)
            	vo[k] = bmh->extractMax();
			out << bmh->getCount() <<" ";
			print(vo, N, out);
		}
		else if(tipo == "bool"){
			Coppia<bool>** vec = new Coppia<bool>*[N+1];
			BinaryMaxHeap<bool> *bmh = new BinaryMaxHeap<bool>();
			
			for(int j = 1; j <= N; j++){
				char parentesis; in >> parentesis;
				int v1; in >> v1;
				int v2; in >> v2;
				in >> parentesis;
				vec[j] = new Coppia<bool>(v1, v2);
			}
			Coppia<bool>** vo = new Coppia<bool>*[N+1];
			bmh->buildMaxHeap(vec, N);
			for(int k = N; k > 0; k--){
				vo[k] = bmh->extractMax();
			}
			out << bmh->getCount() <<" ";
			print(vo, N, out);
		}
		else if(tipo == "double"){
			Coppia<double>** vec = new Coppia<double>*[N+1];
			BinaryMaxHeap<double> *bmh = new BinaryMaxHeap<double>();
			
			for(int j = 1; j <= N; j++){
				char parentesis; in >> parentesis;
				double v1; in >> v1;
				double v2; in >> v2;
				in >> parentesis;
				vec[j] = new Coppia<double>(v1, v2);
			}
			
			Coppia<double>** vo = new Coppia<double>*[N+1];
                bmh->buildMaxHeap(vec, N);
                for(int k = N; k > 0; k--)
                vo[k] = bmh->extractMax();
                out << bmh->getCount()<< " ";
                print(vo, N, out);
		}
		else if(tipo == "char"){
			Coppia<char> **vec = new Coppia<char>*[N+1];
			BinaryMaxHeap<char> *bmh = new BinaryMaxHeap<char>();
			
			for(int j = 1; j <= N; j++){
				char parentesis; in >> parentesis;
				char v1; in >> v1;
				char v2; in >> v2;
				in >> parentesis;
				vec[j] = new Coppia<char>(v1, v2);			
			}
			
			Coppia<char>** vo = new Coppia<char>*[N+1];
                bmh->buildMaxHeap(vec, N);
                for(int k = N; k > 0; k--)
                vo[k] = bmh->extractMax();
                out << bmh->getCount() << " ";
                print(vo, N, out);
		}
	}
	
	return 0;
}