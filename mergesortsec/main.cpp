#include <iostream>
#include <stdlib.h>
#include <ctime>

#define CANTIDAD  400000
#define CANTIRES       5

using namespace std;

void MergeSort(int, int);
void quickSort(int, int);
void radixsort(int);
int insertionSort();


int merge[CANTIDAD];
int quick[CANTIDAD];
int radix[CANTIDAD];
int is[CANTIDAD]; //Insertion sort array


int L[CANTIDAD];
int R[CANTIDAD];
int output[CANTIDAD]; // output array


int compMS = 0;
int interMS = 0;

int compQS = 0;
int interQS = 0;

int compRS = 0;
int interRS = 0;

int main()
{
    int i;
    //srand(time(NULL));
    for(i = 0; i < CANTIDAD; i++)
    {
        merge[i] = rand() % CANTIDAD;
        quick[i] = merge[i];
        radix[i] = quick[i];
        is[i] = radix[i];
    }

    //
    // Algoritmos

    cout.setf(ios::fixed, ios::floatfield);
    cout.setf(ios::showpoint);

    cout << "Para " << CANTIDAD << " elementos: "<< endl;
    cout << endl;


    double start_a = clock();
    for(i = 0; i < CANTIRES; i++)
    {
        MergeSort(0, CANTIDAD -1);
    }
    double stop_a = clock();
    cout << "Merge Sort: " << ((stop_a - start_a)/double(CLOCKS_PER_SEC) * 1000)/CANTIRES << " Comparaciones: " << compMS << ", intercambios: " << interMS << endl;


    double start_b = clock();
    for(i = 0; i < CANTIRES; i++)
    {
        quickSort(0, CANTIDAD);
    }
    double stop_b = clock();
    cout << "Quick Sort: " << ((stop_b - start_b)/double(CLOCKS_PER_SEC) * 1000)/CANTIRES << " Comparaciones: " << compQS << ", intercambios: " << interQS << endl;


    double start_c = clock();
    for(i = 0; i < CANTIRES; i++)
    {
        insertionSort();
    }
    double stop_c = clock();
    cout << "Insertion Sort: " << ((stop_c - start_c)/double(CLOCKS_PER_SEC) * 1000)/CANTIRES << endl;

    /*
    int start_c = clock();
    for(i = 0; i < CANTIRES; i++)
    {
        radixsort(CANTIDAD);
    }
    int stop_c = clock();
    cout << "Radix Sort: " << ((stop_c - start_c)/double(CLOCKS_PER_SEC) * 1000)/CANTIRES << endl;
    */

    return 0;
}


void Merge(int p,int q,int r)
{
    int n1=q-p+1;
    int n2=r-q;

    //Aqui estaban los arreglos L y R

    for(int i=0; i<n1; i++)
        L[i]=merge[p+i];
    for(int j=0; j<n2; j++)
        R[j]=merge[q+1+j];
    int i=0;
    int j=0;
    int n=0;
    while(i!=n1 && j!=n2)
    {
        if(L[i]>R[j])
        {
            merge[p+n]=R[j];
            //interMS++;
            j++;
        }
        else
        {
            merge[p+n]=L[i];
            //interMS++;
            i++;
        }
        n++;
    }
    while(j!=n2)
    {
        merge[p+n]=R[j];
        //interMS++;
        j++;
        n++;
    }
    while(i!=n1)
    {
        merge[p+n]=L[i];
        //interMS++;
        i++;
        n++;
    }
}
void MergeSort(int p,int r)
{
    //compMS++;
    if(r>p)
    {
        int q;
        q=(p+r)/2;
        MergeSort(p,q);
        MergeSort(q+1,r);
        Merge(p,q,r);
    }
}

void quickSort(int low, int high)
{
    int i = low;
    int j = high;
    int pivot = quick[(i + j) / 2];
    int temp;

    while (i <= j)
    {
        while (quick[i] < pivot)
            i++;
        while (quick[j] > pivot)
            j--;
        //compQS++;
        if (i <= j)
        {
            //interQS++;
            temp = quick[i];
            quick[i] = quick[j];
            quick[j] = temp;
            i++;
            j--;
        }
    }
    if (j > low)
        quickSort(low, j);
    if (i < high)
        quickSort(i, high);
}

// A utility function to get maximum value in arr[]
int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(int arr[], int n, int exp)
{
    int i, count[10] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[ (arr[i]/exp)%10 ]++;

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
        count[ (arr[i]/exp)%10 ]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using
// Radix Sort
void radixsort(int n)
{
    // Find the maximum number to know number of digits
    int m = getMax(radix, n);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(radix, n, exp);
}

int insertionSort()
{
    long long comp = 0, swap = 0;
    int time_2 = 0;
    //int time_1 = clock();

    int j, temp, i;

    for(i=0; i<CANTIDAD; i++)
    {
        temp=is[i];
        j=i-1;
        while((temp<is[j]) && (j>=0))
        {
            is[j+1]=is[j];
            j=j-1;
        }
        is[j+1]=temp;
    }
    /*
    time_2 = clock();
    cout << "\nComparaciones: " << comp << " Intercambios: " << swap << endl;
    return ((time_2 - time_1) / double(CLOCKS_PER_SEC) * 1000);*/
}

