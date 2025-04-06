#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define maxe_size 50
typedef struct element element;
struct  element{
    char caractere[maxe_size];
    int boolaint;
    element* next;
};
typedef struct pile pile;
struct  pile{
    element* sommet;
};


pile* cree(){
    pile* p=malloc(sizeof(pile));
    p->sommet =NULL;
    return p;
}
int estvide(pile *p){
    if(p->sommet==NULL){
        return 1;
    }
    else
        return 0;
}
void empiler(pile*p,char caractere[]){
    element* newelement =malloc(sizeof(element));
    strcpy(newelement->caractere,caractere);
    newelement->next=p->sommet;
    p->sommet = newelement;
}
void empilerBool(pile*p,int boolint){
    element* newelement =malloc(sizeof(element));
    newelement->boolaint=boolint;
    newelement->next=p->sommet;
    p->sommet = newelement;
}
void depilage(pile *p){
    element *elementdepile=p->sommet;
    p->sommet=elementdepile->next;
    free(elementdepile);

}
void affichageStack(pile* s){
    element* curr=s->sommet;
    while(curr!=NULL){
        printf("|  %s\t|\n---------\n",curr->caractere);
        curr=curr->next;
    }
}
char* top(pile* s){
     return s->sommet->caractere ;
    
}
int topbool(pile* s){
     return s->sommet->boolaint ;
    
}
// int main(){
//     pile*p1=cree();
// empiler(p1,"1");
// empiler(p1,"2");
// empiler(p1,"3");
// empiler(p1,"4");
// empiler(p1,"5");
// affichageStack(p1);
// printf("\n");
// int a=estvide(p1);
// // printf("%d",a);
// printf("\n");
// depilage(p1);
// top(p1);

// affichageStack(p1);

// return 0;
// }
