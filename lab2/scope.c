#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "symbol.h"

# define DEBUG (0)

struct scope_stack_node {
    struct hash_table *current_scope;
    struct scope_stack_node *prev;
};

struct scope_stack_node *head = NULL;

void scope_enter(){
    struct scope_stack_node *new_scope =(struct scope_stack_node *) malloc(sizeof(struct scope_stack_node));
    new_scope->current_scope= hash_table_create(0, NULL);
    new_scope->prev = head;
    head=new_scope;
    if DEBUG printf("curr scope on enter: %d\n",scope_level());
}
void scope_exit(){
    struct scope_stack_node *tmp =head->prev;
    hash_table_delete(head->current_scope);
    free(head);
    head=tmp;
    if DEBUG printf("curr scope on exit: %d\n",scope_level());
}
int scope_level(){
    int level=0;
    struct scope_stack_node *curr = head;
    while(curr!=NULL){
        curr = curr->prev;
        level++;
    }
    return level;
}
void scope_bind(const char *name, struct symbol *sym){
    if DEBUG printf("name : %s entered scope : %d\n", name, scope_level());
    hash_table_insert(head->current_scope,name,sym);
}
struct symbol *scope_lookup(const char *name){
    struct scope_stack_node *curr = head;
    struct symbol *ret = 0;
    while(curr != NULL&&ret==0){
        ret = hash_table_lookup(curr->current_scope,name);
        curr = curr->prev;
    }
    if DEBUG printf("scope lookup name : %d\n", ret->name);
    return ret;
}
struct symbol *scope_lookup_current(const char *name){
    return hash_table_lookup(head ->current_scope ,name);
}


