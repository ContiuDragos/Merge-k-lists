#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Profiler.h"

Profiler p("medie");

typedef struct _Node {
    int lista;
    int info;
    struct _Node *next;
}Node;

typedef struct
{
    int key;
    int lista;
}heapElement;
void swap(heapElement *a, heapElement *b)
{
    heapElement aux=*a;
    *a=*b;
    *b=aux;
}
void printHeap(heapElement v[], int n)
{
    for(int i=0;i<n;i++)
        printf("%d ",v[i].key);
    printf("\n");
}
void afiseazaListe(Node *heads, int nrListe)
{
    Node *p=NULL;
    for(int i=0;i<nrListe;i++)
    {
        printf("Lista %d:",i);
        p=heads[i].next;
        while(p!=NULL)
        {
            printf("%d ",p->info);
            p=p->next;
        }
        printf("\n");
    }
}
void alocaHeap(heapElement **heap, int nrElemente)
{
    heapElement *v=(heapElement*)calloc(nrElemente,sizeof(heapElement));
    if(heap==NULL)
    {
        printf("Nu pot crea\n");
        exit(-1);
    }
    if(v==NULL)
    {
        printf("Nu este memorie\n");
        exit(-2);
    }
    *heap=v;
}
void alocaHeads(Node **Heads, int nrElemente)
{
    Node *v=(Node*)calloc(nrElemente,sizeof(Node));
    if(Heads==NULL)
    {
        printf("Nu pot crea\n");
        exit(-1);
    }
    if(v==NULL)
    {
        printf("Nu este memorie\n");
        exit(-2);
    }
    for(int i=0;i<nrElemente;i++)
    {
        v[i].info=0;
        v[i].next=NULL;
        v[i].lista=i;
    }
    *Heads=v;
}
void creeazaLista(Node** lista, int *v, int nrElemente, int pozitie)
{
    Node *q=NULL;
    Node *l=(Node*)calloc(1,sizeof(Node));

    for(int i=nrElemente-1;i>=0;i--)
    {
        q=(Node*)calloc(1,sizeof(Node));
        q->info=v[i];
        q->lista=pozitie;
        if(l->next==NULL)
        {
            q->next=NULL;
            l->next=q;
        }
        else
        {
            q->next=l->next;
            l->next=q;
        }
    }
    *lista=l;
}
void populeazaListe(Node **heads, int nrListe, int nrElemente)
{
    int *v=NULL;
    srand(time(0));
    int val=0,elementePuse=0;
    Node *lista = NULL;
    for(int i=0;i<nrListe-1;i++)
    {
        val=(rand()%(nrElemente/nrListe-nrElemente/(nrListe*2))+1)+nrElemente/(nrListe*2);    ///calculez nrElem dintr-o lista
        elementePuse+=val;
        v=(int*)calloc(val,sizeof(int));
        FillRandomArray(v,val,0,5000,true,1);
        creeazaLista(&lista,v,val,i);
        (*heads)[i]=*lista;
        free(lista);
        free(v);
    }
    v=(int*)calloc(nrElemente-elementePuse,sizeof(int));
    FillRandomArray(v,nrElemente-elementePuse,0,5000,true,1);
    creeazaLista(&lista,v,nrElemente-elementePuse,nrListe-1);
    (*heads)[nrListe-1]=*lista;

}
void populeazaHeap(heapElement **heap, Node* heads, int nrListe)
{
    for(int i=0;i<nrListe;i++)
    {
        (*heap)[i].lista=i;
        (*heap)[i].key=heads[i].next->info;
        heads[i].next=heads[i].next->next;
    }
}
void heapify(heapElement v[], int n, int i)
{
    int largest=i;
    int left=2*i+1, right=2*i+2;

    if(left<n && v[left].key < v[largest].key)
        largest=left;

    if(right<n && v[right].key < v[largest].key)
        largest=right;

    if(largest!=i) {
        swap(&v[i], &v[largest]);
        heapify(v,n,largest);
    }
}

void buildHeap_bottomUp(heapElement v[], int n)
{
    int index=(n/2)-1;

    for(int i=index;i>=0;i--)
        heapify(v,n,i);
}
void adaugaElementHeap(heapElement **heap, Node **heads, int pozitie, int nrListe)
{
    Node *p=(*heads)[pozitie].next;
    if(p==NULL)
    {
        do
        {
            if(pozitie==nrListe-1)
                pozitie=0;
            else
                pozitie++;
            p=(*heads)[pozitie].next;
        }while(p==NULL);
        (*heap)[0].lista=pozitie;
        (*heap)[0].key=p->info;
        (*heads)[pozitie].next=p->next;
        free(p);
    }
    else
    {
        (*heap)[0].lista=pozitie;
        (*heap)[0].key=p->info;
        (*heads)[pozitie].next=p->next;
        free(p);
    }

}
void merge(heapElement **heap, Node **heads, int nrListe, int nrElemente)
{
    while(nrElemente>0)
    {
        buildHeap_bottomUp(*heap, nrListe);
        printf("%d ",heap[0]->key);
        nrElemente--;
        if(nrElemente>=nrListe)
            adaugaElementHeap(heap,heads,heap[0]->lista,nrListe);
        else
        {
            while(nrElemente>0) {

                for (int i = 0; i < nrElemente; i++) {
                    (*heap)[i].key = (*heap)[i + 1].key;
                    (*heap)[i].lista = (*heap)[i + 1].lista;
                }
                buildHeap_bottomUp(*heap, nrElemente);

                printf("%d ", (*heap)[0].key);
                nrElemente--;
            }
        }
    }
}
void demo()
{
    int n=20;
    int k=5;
    Node *heads=NULL;
    heapElement *heap=NULL;

    alocaHeads(&heads,k);
    populeazaListe(&heads,k,n);
    afiseazaListe(heads,k);

    alocaHeap(&heap,k);
    populeazaHeap(&heap,heads,k);

    printf("Listele interclasate:\n");
    merge(&heap,&heads,k,n);

}
int main() {
    demo();
    return 0;
}
