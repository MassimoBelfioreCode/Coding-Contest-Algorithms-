#include <iostream>

using namespace std;


template <typename T> class PriorityQueue{
    public:
        virtual T* extract() = 0; //quindi è una classe astratta
        virtual PriorityQueue<T>* enqueue(T x) = 0;
        virtual double compare(T *a, T* b) = 0;
        virtual void printKey(int i) = 0;
};

//vogliamo una coda di max priority
template <typename T> class MaxBinaryHeap: public PriorityQueue<T>{
    private:

        int queueLength;
        int heapSize;
        T** coda;

    public:

        int left(int i)const{ return i << 1;} //faccio scorrere la rappresentazione binaria di i di una posizione a sinistra
        int right(int i)const{ return (i << 1) | 1;} //aggiungo un 1 nel bit meno significativo del nostro registro
        int parent(int i)const{ return i >> 1;}


        void scambia(int k, int j){
            T* tmp = coda[k];
            coda[k] = coda[j];
            coda[j] = tmp;
        }

        //versione iterativa abbiamo bisogno o di un ciclo for o di un ciclo while
        void heapify(int i){
            int index = i; //usiamo il while
            while(index <= this->heapSize/2){
                int massimo = index;
                int l = left(index);
                int r = right(index);
                if(l <= this->heapSize && coda[l] > coda[index]){
                    massimo = l;
                }
                if(r <= this->heapSize && coda[r] > coda[massimo]){
                    massimo = r;
                }
                if(massimo != index) scambia(coda[index], coda[massimo]);
                else break;
                i = massimo;
            }
        }

        int getLength()const{ return this->queueLength;}
        int getheapSize()const{ return this->heapSize;}

        void stampa()const{
            for(int i = 1; i <= getheapSize(); i++){
                cout << *coda[i]<<" ";
            }
            cout << endl;
        }

    public:

        virtual double compare(T* a, T* b) = 0;
        virtual void printKey(int i)const = 0;

        MaxBinaryHeap(int n){
            queueLength = 0;
            this->heapSize = 0;
            coda = new T*[n+1];
        }

        //se invece partiamo con un certo numero di elementi che non costituiscono una heap
        MaxBinaryHeap(T** C, int n){
            coda = C;
            queueLength = n;
            heapSize = n-1;
            //buildHeap();
        }

        void buildMaxHeap(){
            int index = heapSize/2;
            while(index > 0){
                heapify(index);
                index--;
            }
        }

        //metodo per estrarre una chiave da una coda di priorità implementata con heap

        T* extract(){
            if(heapSize==0) return nullptr;
            else{
                scambia(1 , heapSize);
                heapSize = heapSize-1;
                heapify(1);
                return coda[heapSize + 1];
            }
        }

        //incrementare o decrementare, a seconda dei casi, il valore di una chiave
        void modify(int i, T key){
            if(i < 1 || i > heapSize || compare(coda[i], &key) >= 0)
                return;
            delete coda[i];
            coda[i] = new T(key); // perchè passo la chiave per copia, aggiornamento della chiave

            while(i > 1 && compare(coda[i], coda[parent(i)]) > 0){
                scambia(i, parent(i));
                i = parent(i); //per risalire
            }
        }

        //la funzione vuole che io restituisca un puntatore alla funzione stessa in modo tale che io possa fare enqueue in successione
        MaxBinaryHeap<T>* enqueue(T x){
             if(heapSize == queueLength - 1) return this; //come se fosse heapsize = a size -1
             //se fallisce l'if vuol dire che ho almeno una posizione libera nella struttura dati dove inserire
             coda[heapSize+1] = new T(x);
             //utilizzare una funzione che fa questo while per poi richiamarla dove ci serve
             int i = heapSize;
             while(i > 1 && compare(coda[i], coda[parent(i)]) > 0){
                scambia(i, parent(i));
                i = parent(i); //per risalire
            }
            return this;
        }

        void heapSort(){
            int n = heapSize;
            for(int i = 0; i <= n; i++){
                extract();
                heapSize = n;
            }
        }

};

/* double compare(T* a, T* b){
        return (*a) - (*b);
    }

