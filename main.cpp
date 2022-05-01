#include <bits/stdc++.h>
#include <fstream>
#include <cstdlib>


using namespace std;

ifstream fin("meargeheap.in");
ofstream fout("meargeheap.out");

struct nod {
    int val, grad;
    nod * parinte, * fiu, *frate;
};


/*
nod* nodNou(int n) {
    nod * nodNou = new nod;
    nodNou->val = x;
    nodNou->grad = 0;
    nodNou->parinte = NULL;
    nodNou->fiu = NULL;
    nodNou->frate = NULL;
    return nodNou;
}
*/


class BinomialHeap {
private:
    nod *h1;
    nod *h2;

public:
    nod* creareNod(int);
    nod* initializareHeap();
    nod* mergeHeap(nod*, nod*);
    nod* reuniune(nod*, nod*);
    nod* insereaza(nod*, nod*);
    nod* minim(nod*);
    //nod* maxim(nod*);
    int revizuire(nod*);
    BinomialHeap()
        {
            h1 = initializareHeap();
            h2 = initializareHeap();

        }
};

nod* BinomialHeap::creareNod(int x){
    nod * nodNou = new nod;
    nodNou->val = x;
    nodNou->grad = 0;
    nodNou->parinte = NULL;
    nodNou->fiu = NULL;
    nodNou->frate = NULL;
    return nodNou;
}

nod* BinomialHeap::initializareHeap() {
    nod* nd;
    nd = NULL;
    return nd;
}

nod* BinomialHeap::insereaza(nod* h1, nod* n){
    nod* h3 = initializareHeap();
    h3 = n;
    h1 = reuniune(h1, h3);
    return h1;
}

nod* BinomialHeap::mergeHeap(nod* h3, nod* h4){
    nod* h1 = initializareHeap();
    nod* n1;
    nod* n2;
    nod* n3;
    nod* n4;
    n3 = h3;
    n4 = h4;
    if(n3 != NULL)
    {
        if(n4 != NULL)
        {
            if(n3->grad <= n4->grad)
            {
                h1 = n3;
            }
            else if(n3->grad > n4->grad)
            {
                h1 = n4;
            }
            else
            {
                h1 = n3;
            }
        }
    }
    else
    {
        h1 = n4;
    }
    while (n3 != NULL && n4 != NULL)
    {
        if(n3->grad < n4->grad)
        {
            n3 = n3->frate;
        }
        else if(n3->grad == n4->grad)
        {
            n1 = n3->frate;
            n3->frate = n4;
            n3 = n1;
        }
        else
        {
            n2 = n4->frate;
            n4->frate = n3;
            n4 = n2;
        }
    }
    return h1;
}

nod* BinomialHeap::reuniune(nod* h3, nod* h4){
    nod* h1 = initializareHeap();
    h1 = mergeHeap(h3, h4);
    if(h1 == NULL)
        return h1;
    nod* prev_n;
    nod* next_n;
    nod* n;
    n = h1;
    prev_n = NULL;
    next_n = n->frate;
    while(next_n != NULL)
    {
        if((n->grad != next_n->grad) || ((next_n->frate != NULL) && ((next_n->frate)->grad == n->grad)))
        {
            prev_n = n;
            n = next_n;
        }
        else
        {
            if(n->val <= next_n->val)
            {
                n->frate = next_n->frate;

                next_n->parinte = n;
                next_n->frate = n->fiu;
                n->fiu = next_n;
                n->grad = n->grad + 1;
            }
            else
            {
                if(prev_n == NULL)
                {
                    h1 = next_n;
                }
                else
                {
                   prev_n->frate = next_n;
                }
                n->parinte = next_n;
                n->frate = next_n->fiu;
                next_n->fiu = n;
                next_n->grad = next_n->grad + 1;
                n = next_n;
            }
        }
        next_n = n->frate;
    }
    return h1;
}

nod* BinomialHeap::minim(nod* h3) {
    h2 = NULL;
    nod* t = NULL;
    nod* x = h3;
    if(x == NULL)
    {
        fout<<"Heap-ul este gol"<<'\n';
        return x;
    }
    int minn = x->val;
    nod* y = x;
    while(y->frate != NULL)
    {
        if((y->frate)->val < minn)
        {
            minn = (y->frate)->val;
            t = y;
            x = y->frate;
        }
        y = y->frate;
    }
    if(t == NULL && x->frate == NULL)
    {
        h3 = NULL;
    }
    else if(t == NULL)
    {
        h3 = x->frate;
    }
    else if(t->frate == NULL)
    {
        t = NULL;
    }
    else
    {
        t->frate = x->frate;
    }
    if(x->fiu != NULL)
    {
        revizuire(x->fiu);
        (x->fiu)->frate == NULL;
    }
    h1 = reuniune(h3, h2);
    return x;
}

int BinomialHeap::revizuire(nod* n){
    if(n->frate != NULL)
    {
        revizuire(n->frate);
        (n->frate)->frate = n;
    }
    else
    {
        h2 = n;
    }
}

int main()
{
    int rand();
    BinomialHeap heap;
    nod* n1;
    nod* n2;

    nod* n3;
    nod* h;
    h = heap.initializareHeap();
    int nr,q,m,x,op,a,b;
    fin>>nr>>q;
    for(int i=1;i<=q;i++)
    {
        fin>>op;
        if(op == 1)
        {
            fin>>m>>x;
            n1 = heap.initializareHeap();
            n1 = heap.creareNod(m);
            //n2 = heap.creareNod(x);
            for(int i=0; i< 10000; i++)
            {
               n2 = heap.creareNod(rand()%10000);
               h = heap.insereaza(n1,n2);
            }
            //fout<< n1 << n2;
            //h = heap.insereaza(n1,n2);
        }
        else if(op == 2)
        {
            fin >> x;
            n3 = heap.creareNod(x);
            n1 = heap.minim(n3);
            fout<<n1 <<'\n';
        }
        else if(op == 3)
        {
            fin>>a>>b;
            n1 = heap.creareNod(a);
            n2 = heap.creareNod(b);
            h = heap.reuniune(n1,n2);
        }
    }
    return 0;
}
