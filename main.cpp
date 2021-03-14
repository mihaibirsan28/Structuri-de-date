#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
using namespace std::chrono;

ifstream f("teste_in.txt");
ofstream g("afisare_sortari.txt");

unsigned int n,mx;
vector<unsigned long long> v;
vector<unsigned long long> c;

void bubblesort()
{
    int aux, i, j;
    for( i=0; i < v.size()-1; i++)
    {
        for (j = 0; j < v.size() - i - 1; j++)
        {
            if (v[j] > v[j + 1])
            {
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

void QuickSort1(int st, int dr)
{
    if(st < dr)
    {
        int m = (st + dr) / 2;
        int aux = v[st];
        v[st] = v[m];
        v[m] = aux;
        int i = st , j = dr, d = 0;
        while(i < j)
        {
            if(v[i] > v[j])
            {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
                d = 1 - d;
            }
            i += d;
            j -= 1 - d;
        }
        QuickSort1(st , i - 1);
        QuickSort1(i + 1 , dr);
    }
}

int mediana_din_3(int st,int dr)
{
    int mij=(st+dr)/2;
    if(v[dr] < v[st])
        swap(v[st], v[dr]);
    if (v[mij] < v[st])
        swap(v[mij],v[st]);
    if (v[dr] < v[mij])
        swap(v[dr],v[mij]);
    return mij;
}

void QuickSort2(int st,int dr)
{
    if(st<dr)
    {
        int i,j;
        unsigned long long pivot;
        i=st;j=dr;
        pivot=v[mediana_din_3(st,dr)];
        do
        {
            while(v[i]<pivot)i++;
            while(v[j]>pivot)j--;
            if(i<=j)
            {
                swap(v[i],v[j]);
                i++;
                j--;
            }
        }while(i<=j);
        if(st<j)QuickSort2(st,j);
        if(i<dr)QuickSort2(i,dr);
    }
}


/*void interclaseare(int st, int dr)
{
    vector<unsigned long long> w;
    int k=0, mij = (st+dr)/2, i, j;
    i=st;
    j=mij+1;
    while(i<=mij && j<=dr)
    {
        if(v[i]<v[j])
            w[++k]=v[i++];
        else w[++k]=v[j++];
    }
    if(i<=mij)
        for(;i<=mij;i++)
            w[++k]=v[i];
    else for(;j<=dr;j++)
            w[++k]=v[j];
    for(i=st,j=1;i<=dr;i++,j++)
        v[i]=w[j];
}
*/

void MergeSort(int st, int dr)
{
    if(st < dr)
    {
        int m = (st + dr) / 2;
        MergeSort(st , m);
        MergeSort(m + 1 , dr);
        //Interclasare
        int i = st, j = m + 1, k = 0;
        while( i <= m && j <= dr )
            if( v[i] < v[j])
                c[++k] = v[i++];
            else
                c[++k] = v[j++];
        while(i <= m)
            c[++k] = v[i++];
        while(j <= dr)
            c[++k] = v[j++];
        for(i = st , j = 1 ; i <= dr ; i ++ , j ++)
            v[i] = c[j];
    }
}

int maxim()
{
    int mx = v[0];
    int i;
    for(i=1;i<n;i++)
    {
        if (v[i]>mx)
            mx = v[i];
    }
    return mx;
}

void count_sort(int shift)
{
    vector<int> c(v.size(),0);
    int vf[8]={0};
    for(int i=0;i<v.size();i++)
        vf[(v[i]>>shift)&7]++;
    for(int i=1;i<8;i++)
        vf[i]+=vf[i-1];
    for(int i=v.size()-1;i>=0;i--)
    {
        c[vf[(v[i]>>shift)&7]-1]=v[i];
        vf[(v[i]>>shift)&7]--;
    }
    for(int i=0;i<v.size();i++)
        v[i]=c[i];
}

void RadixSort()
{
    for (int shift = 0; (mx >> shift) > 0; shift += 2)
        count_sort(shift);

}

void CountSort()
{
    int mx=maxim();
    unsigned long long frecventa[100001]={0};
    for(int i=0;i<v.size();i++)
    {
        frecventa[v[i]]++;
    }
    v.clear();
    for(int i=0;i<mx;i++)
    {
        while (frecventa[i]>0)
        {
            v.push_back(i);
            frecventa[i]--;
        }
    }
}

void sortSTL()
{
    sort(v.begin(),v.end());
}

int test_sort()
{
    for(int i=0;i<v.size()-1;i++)
            if(v[i]>v[i+1])
            {
                return 0;
            }
    return 1;
}

void Timp_de_executie( int nr_sortare)
{

    auto start = high_resolution_clock::now();
    if(nr_sortare==1)
    {
        bubblesort();
    }
    else if (nr_sortare==2)
    {
        QuickSort1(0,n-1);
    }
    else if (nr_sortare==3)
    {
        MergeSort( 0,n-1);
    }
    else if (nr_sortare==4)
    {
        RadixSort();
    }
    else if (nr_sortare==5)
    {
        CountSort();
    }
    else if (nr_sortare==6)
    {
        sortSTL();
    }
    else if (nr_sortare==7)
    {
        QuickSort2(0,n-1);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end-start);
    int ok;
    ok=test_sort();
    if (ok==1)
        g<<"Algortimul a sortat vectorul corect in "<<duration.count()<<" milisecunde"<<"\n";
    else
    {
        if (nr_sortare==1)g<<"Algoritmul bubblesort nu a sortat corect vectorul"<<"\n";
        else if (nr_sortare==2)g<<"Algoritmul quicksort1 nu a sortat corect vectorul"<<"\n";
        else if (nr_sortare==3)g<<"Algoritmul mergesort nu a sortat corect vectorul"<<"\n";
        else if (nr_sortare==4)g<<"Algoritmul radixsort nu a sortat corect vectorul"<<"\n";
        else if (nr_sortare==5)g<<"Algoritmul countsort nu a sortat corect vectorul"<<"\n";
        else if (nr_sortare==6)g<<"Algoritmul din stl nu a sortat corect vectorul"<<"\n";
        else if (nr_sortare==7)g<<"Algoritmul quicksort2 nu a sortat corect vectorul"<<"\n";
    }
}

int main()
{
    int x,i;
    srand(time(0));
    f>>n;
    for(i=0;i<n;i++)
    {
        x=rand()%1000+1000000;
        v.push_back(x);
        c.push_back(x);
    }
    g<<"n este: "<<n<<"\n";
    mx=maxim();
    Timp_de_executie(1);
    //for(i=0;i<n;i++)
    //{
    //    g<<v[i]<<' ';
    //}
    //return 0;
}