#include <iostream>
#include <fstream>

using namespace std;

template <typename H> class MaxBinaryHeap{
    private:
        int heapsize;
        H* vec;


    public:

        int left(int i)const{ return i << 1; }
        int right(int i)const{ return (i << 1)| 1;}
        int parent(int i)const{ return i >> 1;}

    int getHeapsize()const{ return heapsize;}

    MaxBinaryHeap(){
        heapsize = 0;
    }

    void scambia(int i, int j){
        int aux = i;
        i = j;
        j = aux;
    }

    void _heapify(int i){
        int l = left(i);
        int r = right(i);
        int massimo = i;

        if( l <= heapsize && vec[l] > vec[massimo]){
            massimo = l;
        }
        if(r <= heapsize && vec[r] > vec[massimo])
            massimo = r;
        if(massimo != i){
            swap(vec[i], vec[massimo]);
            _heapify(massimo);
            }
        }


    void buildMaxHeap(H* v, int n){
        heapsize = n;
        vec = v;
        for(int i = heapsize/2; i > 0; i--)
            _heapify(i);
        }


    void stampa()const{
        for(int j = 1; j <= heapsize; j++){
            cout << vec[j]<< " ";
        }
        cout << endl;
    }

};


int main(){

    ifstream in("MHeap.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        string tipo;
        in >> tipo;
        int N;
        in >> N;

        if(tipo == "int"){
            MaxBinaryHeap<int>* A = new MaxBinaryHeap<int>();
            int* vec = new int[200];
            for(int k = 1; k <= N; k++){
                int aux;
                in >> aux;
                vec[k] = aux;
            }
            A->buildMaxHeap(vec, N);
            A->stampa();
            delete A;
            delete []vec;
        }
        else if(tipo == "double"){
            MaxBinaryHeap<double>* B = new MaxBinaryHeap<double>();
            double* vec = new double[200];
            for(int j = 1; j <= N; j++){
                double aux;
                in >> aux;
                vec[j] = aux;
            }
            B->buildMaxHeap(vec, N);
            B->stampa();
            delete B;
            delete []vec;
        }
        else if(tipo == "bool"){
            MaxBinaryHeap<bool>* C = new MaxBinaryHeap<bool>();
            bool* vec = new bool[200];
            for(int k = 1; k <= N; k++){
                bool aux;
                in >> aux;
                vec[k] = aux;
            }
            C->buildMaxHeap(vec, N);
            C->stampa();
            delete C;
            delete []vec;
        }
        else if(tipo == "char"){
            MaxBinaryHeap<char>* D = new MaxBinaryHeap<char>();
            char* vec = new char[200];
            for(int j = 1; j <= N; j++){
                char tmp;
                in >> tmp;
                vec[j] = tmp;
            }
            D->buildMaxHeap(vec, N);
            D->stampa();
            delete D;
            delete []vec;
        }
    }

    in.close();
    out.close();

    return 0;
}
