#include<stdio.h>
#include"stack.c"
#include"linked_liste.c"
#include<string.h>

#define maxe_size 50

LinkedList* read(char *expression) {
    LinkedList *newList = NULL;
    char *current = expression;
    char tmp[maxe_size];
    int i = 0;
    while (*current != '\0') 
    {
        if(*current == ' ' || *current == '(' || *current == ')') {
            if(i > 0) {
                tmp[i] = '\0';
                newList=insert(newList,tmp);
                i= 0;  
            }
            if(*current == '(') {
                newList=insert(newList,"("); 
            }else if(*current == ')') {
                newList=insert(newList,")");  
            }
        }
        else {
            tmp[i++] = *current;
        }
        current++;
    }
    if (i > 0){
        tmp[i]='\0';
        newList=insert(newList,tmp);   
    }
    return newList;

}

 int priority(char *c){  
    if (strncmp(c, "NOT",3) == 0||strncmp(c, "not",3)== 0)
    {
        return 3;
    }
    else if (strncmp(c, "AND",3)==0||strncmp(c, "and",3)== 0)
    {
        return 2;
    }
    else if (strncmp(c, "OR",2)== 0||strncmp(c, "or",2)== 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }  
} 

LinkedList* infix_to_postflix(LinkedList* expression){
    pile* mystack =cree();
    LinkedList *output = NULL;
    LinkedList *current = expression;
    while (current != NULL)
    {//a and  b
        if (strcmp(current->caractre, "(")==0){
            empiler(mystack,"(");  
        }
        
        
        else if (strcmp(current->caractre,")")==0)
        {
            while (!estvide(mystack)&&strcmp(top(mystack),"(")!=0)
            {
                output=insert(output,top(mystack));
                depilage(mystack);
            }
            if (estvide(mystack))
            {
                printf("error:we cant find '('");
                exit(1);
            }
            
            depilage(mystack);
            
        }
        else if(priority(current->caractre)==0 ){
             output =insert(output,current->caractre);
        }
        
        else{
            while (!estvide(mystack) && priority(current->caractre) < priority(top(mystack))&&strcmp(top(mystack), "(") != 0)
            {
                
                output=insert(output,top(mystack));
                depilage(mystack);
            }
            empiler(mystack ,current->caractre);
            
        }
        current=current->next;
    }
    while (!estvide(mystack)){
    if (strcmp(top(mystack),"(")==0){
        printf("we cant find :')'");
        exit(1);
    }
    
    output=insert(output,top(mystack));   
    depilage(mystack);
    }
    return output; 
    
 }
void bollaine(LinkedList*expression){
    LinkedList *current = expression;
    while (current != NULL)
    {  
        if(priority(current->caractre)==0){
           int input;
        do
        {
            printf("entre 1 (true) ou 0 (false) to %s: ",current->caractre);
            scanf("%d",&input);
        } while (input != 0 && input != 1); 
        current->boolvaluer =input;
        }
        current=current->next;
    }
}

 int boolainOperation(int op1,int op2,char* operat){
    if (strcmp(operat, "AND")==0||strcmp(operat, "and")== 0)
    {
        return op1&&op2;
    }
    else if (strcmp(operat, "OR")== 0||strcmp(operat, "or")== 0)
    {
        return op1||op2;
    }
    else
        return 0;
}

int postfix_evalute(LinkedList* expression){
    pile* myStackEvalution=cree();
    LinkedList *current = expression; 
    
    while (current != NULL){
        if (priority(current->caractre)==0){
            empilerBool(myStackEvalution,current->boolvaluer);
        }
        else if(strcmp(current->caractre,"NOT")==0 || strcmp(current->caractre,"not")==0){
            if (estvide(myStackEvalution))
            {
                printf("error:missing operand for not\n");
                exit(1);
            }
            
            int op =topbool(myStackEvalution);
            depilage(myStackEvalution);
            empilerBool(myStackEvalution ,!op);
        }
        else{
            if (estvide(myStackEvalution))
            {
                printf("error:missing operand for %s\n",current->caractre);
                exit(1);
            }
            
            int op2 =topbool(myStackEvalution);
            depilage(myStackEvalution);
            if (estvide(myStackEvalution))
            {
                printf("error:missing second operand for %s\n",current->caractre);
                exit(1);
            }

            int op1=topbool(myStackEvalution);
            depilage(myStackEvalution);

            int result=boolainOperation(op1,op2,current->caractre);
            empilerBool(myStackEvalution,result);
        }
    current=current->next;
    }
    if (estvide(myStackEvalution))
    {
        printf("error:empty stack sfter evaluation\n");
        exit(1);
    }
    int final_result =topbool(myStackEvalution);
    return final_result;
}
// infix_to_postfix(){}
// evaluate_the_expression(){}
// manage_negation(){}
// simplifies_the_expression(){}
// optimize_memory_usage(){}

LinkedList* gereLaNegasine(LinkedList* expression){
    LinkedList *current = expression;
    LinkedList *prev=current;
    while (current != NULL && current->next !=NULL){//a b NOT NOT
        if (priority(current->caractre)==3 && priority(current->next->caractre)==3){
            LinkedList*not1=current;
            LinkedList*not2=current->next;
            if (prev==NULL){
                expression =not2->next;
                current=expression;
            }
            else{
                prev->next =not2->next;
                current =prev->next;
            }
            free(not1);
            free(not2);
        }
        else{
            prev =current;
            current=current->next;
        }
    }
    return expression; 
 }
LinkedList* simplifieRexpression(LinkedList* expression){
    LinkedList *current = expression;
    LinkedList *prev=current;
    while (current != NULL && current->next !=NULL){//a b NOT NOT
        if ( priority(current->caractre)==3 && priority(current->next->caractre)==3)
        {
            gereLaNegasine(expression);
        }
        
        else if (current->next->next!=NULL){
            if (priority(current->next->caractre)==2 &&     current->next->next->boolvaluer==1&& strcmp(current->next->next->caractre,"true")==0){
                free(current->next);
                free(current->next->next);
                current->next=current->next->next->next;
                continue;
            }
            if (priority(current->next->caractre)==1 &&     current->next->next->boolvaluer==0&& strcmp(current->next->next->caractre,"false")==0){
                free(current->next);
                free(current->next->next);
                current->next=current->next->next->next;
                continue;
            }
        }
        prev =current;
        current=current->next;
        }
    return expression; 
 }

int main(){
    // char chaineCractere[]="a and b or c";
    // LinkedList *newList =NULL ;
    // LinkedList* output=NULL;
    
    // newList =read("a AND b)");
    // afficherListe(newList);
    // printf("\n");
    // output =infix_to_postflix(newList);
    // afficherListe(output);
    // pile *pile =cree(pile);
    // char yo[]=" and c";
    // char c[]="c";
    // // int num =priority(c);
    // printf("%d\n",num);
    // empiler(pile, 4);
    // empiler(pile, 3);
    // empiler(pile, 444);
    // empiler(pile, 7);
    // empiler(pile, 757);
    // empiler(pile,0);
    // top(pile);
    // affichage(pile);
    // printf("%s",yo);


    // LinkedList *infix = read("(a AND b) OR NOT c");
    // printf("Infix expression: ");
    // afficherListe(infix);
    // printf("\n");
    // LinkedList *postfix = infix_to_postflix(infix);
    // printf("Postfix expression: ");
    // afficherListe(postfix);
    // printf("\n");
    // bollaine(postfix);  // Ask user for values of a, b, c
    // int result = postfix_evalute(postfix);
    // printf("Result: %d\n", result);

    LinkedList *infix = read("a not not b");
     printf("Infix expression: ");
     afficherListe(infix);
     printf("\n");
    
    LinkedList *postfix = infix_to_postflix(infix);
    printf("Postfix expression: ");
     afficherListe(postfix);
     printf("\n");
    
    // bollaine(postfix);
    // int result = postfix_evalute(postfix);
    // printf("Result: %d\n", result);


    LinkedList *expr =gereLaNegasine(postfix);
    afficherListe(expr);

    return 0;
    

    

}