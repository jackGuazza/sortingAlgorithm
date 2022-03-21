#include <stdio.h>
#include <stdlib.h>
#include <time.h>



//stampaArray
void stampaArray(int array[], int sz){
    int i;
    for( i = 0; i < sz ; i++) {      
        printf("%d ", array[i]);
    }
    printf("\n");
}



//randomArray
void randomArray(int sz, int randArray[]){
    int x = 10000, y = 1;
    for(int i = 0; i < sz; i++){
        randArray[i] = rand() % (x - y + 1) + y;        // Genera numeri da 1 a 10000
    }

}


/*void copyFromL(int i){
}*/


//Merge
void Merge(int array[], int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1]; int R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = array[p + i];
    }

    for (int i = 0; i < n2; i++) {
        R[i] = array[q + i + 1];
    }
    
    int i = 0, j = 0;

    for (int k = p; k <= r; k++) {
        if (i < n1) {
            if(j < n2){
                if (L[i] <= R[j]) {
                    array[k] = L[i];    // copyFromL(i)
                    i++;               
                }else{
                    array[k] = R[j];    // copyFromR(j)
                    j++;
                }               
            }else{
                array[k] = L[i];        // copyFromL(i)
                i++;
            }
        }else{
            array[k] = R[j] ;           // copyFromR(j)
            j++;
        }        
    }
}



//MergeSort
void MergeSort(int A[], int p, int r){
    if(p < r){
        int q = (p + r) / 2;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        Merge(A, p, q, r);
    }
}



//InsertionSort
void insertionSort(int a[], int sz){
    int key, i;
    for (int j = 1; j < sz; j++) {
        key = a[j];
        i = j - 1;
        while ((i >= 0) && (a[i] > key)) {
            a[i+1] = a[i];
            i = i - 1 ;
        }
        a[i+1] = key;
    }
}



//AdaptedInsertionSort
void AdaptedInsertionSort(int A[], int p, int r){
    int key, i;
    for (int j = p+1; j <= r ; j++) {
        key = A[j];
        i = j - 1;
        while ((i >= p) && (A[i] > key)) {
            A[i+1] = A[i];
            i = i-1 ;
        }
        A[i+1] = key;
    }
}



//HybridSort
void HybridSort(int A[], int p, int r) {
    int q; 
    int k = 20;

    if ((r - p) + 1 > k) {
        q = (p + r) / 2;
        HybridSort(A, p, q);
        HybridSort(A, q+1, r);
        Merge(A, p, q, r);
    }else{
        AdaptedInsertionSort(A, p, r);
    }
}



//Meidana di tre
int medianOfThree(int a[], int i, int j, int k){
    if(a[i] > a[j]){
        if(a[j] >= a[k]){
            return j;
        } else if(a[i] < a[k]){
            return i;
        } else {
            return k;
        }
    } else {
        if(a[i] >= a[k]){
            return i;
        } else if (a[j] < a[k]){
            return j;
        } else {
            return k;
        }
    }
}



//Swap
void SwapValue(int a[], int i, int j){
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}



//partizione con mediana di tre
int MedianOfThreePartition(int a[], int p, int r){
    int s ;
    s = medianOfThree(a, p, r, (p + r)/2);
    SwapValue(a, s, r);
    int x = a[r];
    int i = p - 1;

    for (int j = p; j <= r - 1; j++){
        if(a[j] <= x){
            i = i+1;
            SwapValue(a, i, j);
        }    
    }

    SwapValue(a, i+1, r);
    return i + 1;
}



//QuickSort con mediana di tre
void MedianOfThreeQuickSort(int a[], int p, int r){
    if(p < r){
        int q = MedianOfThreePartition(a, p, r);
        MedianOfThreeQuickSort(a, p, q - 1);
        MedianOfThreeQuickSort(a, q + 1, r);
    }
}



//Partition
int partition (int arr[], int p, int r) {
    int x = arr[r];  // pivot
 
    int i = p - 1;  /*Indice dell'elemento più piccolo e indica il
                    giusta posizione del pivot trovata */

    for (int j = p; j <= r - 1; j++) {
        if (arr[j] < x) {           // se l'elemento corrente è piu piccolo del pivot ...
            i++;                    // incremento indice dell'elemento piu piccolo
            SwapValue(arr, i, j); 
        }
    }
    SwapValue(arr , i+1, r);
    return i + 1;
}



//TailQuickSort
void TailQuickSort(int a[], int p, int r){
    int q;
    while (p < r){
        q = partition(a, p, r);
        TailQuickSort(a, p, q-1);
        p = q + 1;
    }
}



//HybridTailQuickSort
void optimizedQuicksort(int A[], int p, int r) {
    int k = 10, q;     // da verificare

    if((r - p) + 1 > k){
        while (p < r){
            q = MedianOfThreePartition(A, p, r);
            optimizedQuicksort(A, p, q-1);
            p = q+1;
        }
    } else {
        AdaptedInsertionSort(A, p, r);
    }
}



// FUNZIONE ANTAGONISTA
void AntagonistFunct(int ar[], int sz){             
    for (int i = 0; i < sz-1 ; i++){
        if(ar[i+1] >= ar[i]){
            printf("ord\n");
        }else{
            printf("non ord\n");
            exit(22);
        }
    }
}



//SingleExperiment
float SingleExperiment(int lenght, int max_instances, int alg){
    float t_tot = 0;
    int t_start, t_end, t_elapsed;
    float t_final;

    for (int instance = 1; instance <= max_instances; instance++){
        int randArray[lenght];
        randomArray(lenght, randArray);                 // creo array casuale con dim lenght
        //stampaArray(randArray, lenght);                 // stampo array NON ordinato

        if(alg == 0){           
            t_start = clock();
            insertionSort(randArray, lenght);                             // InsertionSort
            //stampaArray(randArray, lenght);  printf("--> IS <--");      // stampo array ordinato
            //AntagonistFunct(randArray, lenght);
            t_end = clock();

        } else if(alg == 1){    
            t_start = clock();
            MergeSort(randArray, 0, lenght-1);                          // MergeSort
            //stampaArray(randArray, lenght);  printf("--> MS <--");           
            //AntagonistFunct(randArray, lenght);
            t_end = clock();

        } else if(alg == 2){                  
            t_start = clock();
            HybridSort(randArray, 0, lenght-1);                         // HybridSort
            //stampaArray(randArray, lenght);  printf("--> HS <--");        
            //AntagonistFunct(randArray, lenght);
            t_end = clock();

        } else if(alg == 3){
            t_start = clock();
            MedianOfThreeQuickSort(randArray, 0, lenght-1);             // MedianOfThreeQuickSort
            //stampaArray(randArray, lenght);  printf("--> MEDO3 <--");          
            //AntagonistFunct(randArray, lenght);
            t_end = clock();

        } else if(alg == 4){
            t_start = clock();
            TailQuickSort(randArray, 0, lenght-1);                       // TailQuickSort
            //stampaArray(randArray, lenght);  printf("--> TQ <--");     
            //AntagonistFunct(randArray, lenght);
            t_end = clock();
        
        } else {
            t_start = clock();
            optimizedQuicksort(randArray, 0, lenght-1);                  // HybridTailQuickSort
            //stampaArray(randArray, lenght);  printf("--> HTQ <--"); 
            //AntagonistFunct(randArray, lenght);
            t_end = clock();       
        }
        t_elapsed = t_end - t_start;
        t_tot = t_tot + t_elapsed;
        //printf("\n");
    }
    t_final = t_tot / max_instances;
    return t_final;
}



//Experiment
void Experiment(int min_lenght, int max_lenght, int seed){
    int max_instances = 20;   // ripetizioni
    int step = 5;

    for (int lenght = min_lenght; lenght <= max_lenght; lenght+=step) {
        srand(seed);
        float timeIS = SingleExperiment(lenght, max_instances, 0);      // InsertionSort
        srand(seed);
        float timeMS = SingleExperiment(lenght, max_instances, 1);      // MergeSort
        srand(seed);        
        float timeHS = SingleExperiment(lenght, max_instances, 2);      // HybridSort
        srand(seed);
        float timeQM = SingleExperiment(lenght, max_instances, 3);      // QuicksortMedianOfThree
        srand(seed);
        float timeQT = SingleExperiment(lenght, max_instances, 4);      // QuicksortTailRecursive
        srand(seed);
        float timeHT = SingleExperiment(lenght, max_instances, 5);      // HybridTailQuickSort

        printf("lenght : %d   %.3f  %.3f  %.3f  %.3f  %.3f  %.3f\n", lenght, timeIS, timeMS, timeHS, timeQM, timeQT, timeHT);
        seed++;
    }
}



//Main
int main(int argc, char const *argv[]) {
    
    printf("lenght, InsertionSort, MergeSort, HybridSort, QuicksortMedianOfThree, QuickTailRecursive, HybridTailQuick\n");

    Experiment(500, 10000, 10);         // min, max, seed
    
    return 0;
}

/*
  es: se max_instances = 2 (iterazioni)  , stampa IS 2 volte di seguito e cosi via
*/