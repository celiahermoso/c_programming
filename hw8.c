#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "predefined.h"
//#include "minigrind.h"


struct node_t {
    float re;
    float im;
    struct node_t *next;
};


struct node_t *insert_tail (struct node_t *head, float re, float im){
    
    struct node_t *new_node = (struct node_t *) malloc (1*sizeof(struct node_t));
    
    if (new_node == NULL) {
        return head;
    }
    
    new_node->re = re;
    new_node->im = im;
    new_node->next = NULL;

    if (head == NULL) {
        return new_node;
    }
    
    struct node_t *curr = head;
    while(curr->next != NULL)
        curr = curr->next;
    
    curr->next = new_node;
    return head;
}

void print_list(struct node_t *head){
    
    struct node_t *aux = head;
    int first = 0;
    
    printf ("[");
    
    while(aux != NULL){
        if(first == 1) {
            printf(",");
        }
        printf ("%.2f", aux->re);
        if(aux->im >= 0){
            printf("+%.2f", aux->im);
            printf("i");
        }
        if(aux->im < 0) {
            printf("%.2f", aux->im);
            printf("i");
        }
        first = 1;
        aux = aux->next;
    }
    
    printf("]\n");
    
}

void insert_head (struct node_t **head_pointer, float re, float im){
    
    struct node_t *new_node = (struct node_t *) malloc (1*sizeof(struct node_t ));
    new_node->re = re;
    new_node->im = im;
    new_node->next = (*head_pointer);
    (*head_pointer) = new_node;
}

float distance (float re1, float im1, float re2, float im2) {
    
    float dist;
    dist = sqrt((re1-re2)*(re1-re2)+(im1-im2)*(im1-im2));
    return dist;
}

struct node_t *find_closest (struct node_t *head, float re, float im) {
    
    struct node_t *aux = head;
    struct node_t *closest = head;
    
    if (head == NULL){
        return head;
    }
    float dist = distance(aux->re, aux->im, re, im);
    /*if (dist == distance(aux->re, aux->im, re, im))
        return closest;*/
    
    while(aux!=NULL) {
        if (dist > distance(aux->re, aux->im, re, im)) {
            dist = distance(aux->re, aux->im, re, im);
            closest = aux;
        }
        aux = aux->next;
    }
    return closest;
}

struct node_t *insert_after_closest (struct node_t *head, float re, float im){
    
    struct node_t *closest = find_closest(head, re, im);
    
    struct node_t *new_node = (struct node_t *) malloc (1*sizeof(struct node_t ));
    new_node->re = re;
    new_node->im = im;
    new_node->next = NULL;
    if (head!=NULL) {
        new_node->next = closest->next;
        closest->next = new_node;
        return head;
    } 
    
    return new_node;
}

void insert_before_closest (struct node_t **head, float re, float im) {
    
    struct node_t *closest = find_closest((*head), re, im);
    struct node_t *aux = (*head);
    struct node_t *prev = NULL;
    
    struct node_t *new_node = (struct node_t *) malloc (1*sizeof(struct node_t ));
    new_node->re = re;
    new_node->im = im;
    
    if ((*head) == NULL) {
        (*head) = new_node;
        new_node->next = NULL;
    } else {
        if ((*head) == closest) {
            new_node->next = closest;
            (*head) = new_node;
        } else {
            while(aux != closest){
                prev = aux;
                aux = aux->next;
            }
            new_node->next = closest;
            prev->next = new_node;
        }
    }
}

void print_list_reverse(struct node_t *head) {
    if (head == NULL) {
        return;
    }
    
    print_list_reverse(head->next);
    if(head->next != NULL) printf(",");
    printf ("%.2f", head->re);
        if(head->im >= 0){
            printf("+%.2f", head->im);
            printf("i");
        }
        if(head->im < 0) {
            printf("%.2f", head->im);
            printf("i");
        }
}

struct node_t *remove_front(struct node_t *head){
    
    struct node_t *curr = head;
    if (head != NULL)
        head = head->next;
    
    free(curr);
    return head;
}

void remove_end(struct node_t **head_pointer){
    
    struct node_t *curr = *(head_pointer);
    struct node_t *prev = NULL;
    
    if(curr != NULL) { //There is at least one element
    //For lists with 2 or more elements
        while(curr->next != NULL){
            prev = curr;
            curr = curr->next;
        }
        if(prev != NULL){
            prev->next = NULL;
            curr = NULL;
            free(curr);
        }
        //Lists of one element
        if(curr != NULL && curr->next == NULL) {
            curr = NULL;
            (*head_pointer) = NULL;
            free(curr);
        }
    }
}

struct node_t *remove_closest(struct node_t *head, float re, float im){
    
    struct node_t *found = find_closest(head, re, im);
    struct node_t *curr = head;
    struct node_t *prev = NULL;
    
    if(head==NULL)
        return head;
    
    while(curr != NULL) {
        if(curr == found){//First element is the one
            head = curr->next;
            curr = NULL;
            free(found);
            return head;
        }
        prev = curr;
        curr = curr->next;
        if(curr == found){
            prev->next = curr->next;
            curr = NULL;
            free(found);
        }
    }
    return head;
}


int main(void){
    
    char cmd;
    struct node_t *head = NULL;
    float re, im;
    struct node_t *closest = NULL;
    
    do{
        printf("Command: ");
        scanf(" %c", &cmd);
        
        switch(cmd){
            
            case 'q':
                while(head != NULL)
                    head = remove_front(head);
                printf("Bye!\n");
            break;
            
            case 't':
               printf("re, im? ");
               scanf("%f %f", &re, &im); 
               head = insert_tail(head, re, im);
            break;
            
            case 'p':
                print_list(head);
            break;
            
            case 'h':
                printf("re, im? ");
                scanf("%f %f", &re, &im);
                insert_head(&head, re, im);
            break;
            
            case 'c':
                printf("re, im? ");
                scanf("%f %f", &re, &im);
                closest = find_closest(head, re, im);
                if (closest == NULL) {
                    printf("No closest node found\n");
                } else {
                    if (closest->im >= 0) {
                        printf("Closest node is %.2f+%.2fi\n", closest->re, closest->im);
                    } else if (closest->im < 0) {
                        printf("Closest node is %.2f%.2fi\n", closest->re, closest->im);
                    }
                }
            break;
            
            case 'd'://pynq board
            break;
            
            case 'a':
                printf("re, im? ");
                scanf("%f %f", &re, &im);
                head = insert_after_closest (head, re, im);
            break;
            
            case 'b':
                printf("re, im? ");
                scanf("%f %f", &re, &im);
                insert_before_closest (&head, re, im);
            break;
            
            case 'v':
                printf("[");
                print_list_reverse(head);
                printf("]\n");
            break;
            
            case 'f':
                head = remove_front(head);
            break;
            
            case 'e':
                remove_end(&head);
            break;
            
            case 'r':
                printf("re, im? ");
                scanf("%f %f", &re, &im);
                head = remove_closest(head, re, im);
            break;
        
            default:
                printf("Unknown command '%c'\n", cmd);
            break;
        
        }
    } while (cmd != 'q');
    
    
}