
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxe_size 50
typedef struct LinkedList{
    char caractre[maxe_size];
    int boolvaluer;
    struct LinkedList* next;
}LinkedList;

    LinkedList* insert(LinkedList* head ,char caractre[]){
        LinkedList* curr =head;
        LinkedList*newnode=malloc(sizeof(LinkedList));
        strcpy(newnode->caractre,caractre);
        newnode->next=NULL;
        if(head==NULL){
            head=newnode;
        }
        else{
            while(curr->next!=NULL){
                curr=curr->next;
            }
            curr->next=newnode;
        }
        return head;
    }
void afficherListe(LinkedList* head){
    LinkedList* curr=head;
    while(curr!=NULL){
        printf("%s -> ",curr->caractre);
        curr=curr->next;
    }
    printf("null");
}
// int main(){
//     LinkedList *newList =NULL ;
//     newList =insert(newList,"1");
//     newList =insert(newList,"2");
//     newList =insert(newList,"0");
//     newList =insert(newList,"3");
//     newList =insert(newList,"4");
//     newList =insert(newList,"5");
//     newList =insert(newList,"5");
//     newList =insert(newList,"5");
//     afficherListe(newList);

// return 0;
// }












