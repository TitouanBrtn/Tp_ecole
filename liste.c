/* ==================================== Include    =================================== */
#include <stdio.h>
#include <stdlib.h>

#include "liste.h"

/* ==================================== Functions and procedures =================================== */

int max(int a,int b){
    if(a>b) return a;
    return b;
}

T_liste creer_liste(){
    T_liste l = malloc(sizeof(T_liste));
    l->next = NULL;
    return l;
}

void ajout_entete_liste(T_liste l, int element){
    T_liste new_link = malloc(sizeof(struct link));   //créer un nouveau maillon qui prend la place de l (le premier maillon de la liste)
    new_link->value = l->value;
    new_link->next = l->next;
    l->value = element;                               //définir la nouvelle valeur de l
    l->next = new_link;                               //faire pointer l sur le nouveau maillon
}

T_liste ajouter_entete_fonc(T_liste l, int element){
    T_liste new_link = malloc(sizeof(struct link));     //créer un nouveau maillon (qui sera le premier élément de la nouvelle liste)
    new_link->value = element;                          //définir sa valeur
    new_link->next = l;                                 //le faire pointer sur l
    return new_link;                                    //renvoyer la nouvelle liste
}

void afficher_liste(T_liste l){
    T_liste temp;
    temp = l;
    while((temp->next)!= NULL){
        printf("%d,", temp->value);
        temp = temp->next;
    }
    printf("\n");
}

void fafficher_dir_liste(T_liste l){
    if((l->next)==NULL){
        printf("\n");
    }
    else{
        printf("%d,", l->value);
        fafficher_dir_liste(l->next);
    }
}

void fafficher_inv_liste(T_liste l){
    T_liste lprime = creer_liste();
    while((l->next)!=NULL){
        ajout_entete_liste(lprime, l->value);
        l=l->next;
    }
    afficher_liste(lprime);
}

void inv_mis_list(T_liste* l){ //marche pas
    T_liste* l_premier = l;
    printf("l_prem :");
    afficher_liste(*l_premier);
    printf("\n");
    T_liste temp;
    while((*l)->next!=NULL){
        temp = (*l)->next;
        (*l)->next = temp->next;
        temp->next = *l;
        printf("l :");
        afficher_liste(*l);
        printf("l_prem :");
        afficher_liste(*l_premier);
    }
}

T_liste inv_fonc_list(T_liste l){
    T_liste lprime = creer_liste();
    while((l->next)!=NULL){
        ajout_entete_liste(lprime, l->value);
        l=l->next;
    }
    return lprime;
}


int long_env(T_liste l){
    int taille = -1;
    if(l==NULL){
        return taille;
    }
    else return 1+long_env(l->next);
}


int long_ter(T_liste l, int aux){
    if(l->next==NULL) return aux;
    else{
        aux = long_ter(l->next, aux+1);
        return aux;
    }
}


int max_env(T_liste l){
    int res = l->value;
    if(l->next==NULL) return res;
    else{
        return max(res,max_env(l->next));
    }
}


int max_ter(T_liste l, int aux){
    if(l->next==NULL) return max(aux,l->value);
    else{
        aux = max(aux, l->value);
        return max_ter(l->next, aux);
    }
}


T_liste inversion_rec_env(T_liste l){
    T_liste lprime = creer_liste();
    if(l->next==NULL) return lprime;
    else{
        
        return inversion_rec_env(l->next);
    }
}


int main(){
    T_liste l = creer_liste();
    ajout_entete_liste(l,2);
    ajout_entete_liste(l,4);
    ajout_entete_liste(l,7);
    afficher_liste(l);
    printf("taille de l : %d\n",long_ter(l,0));
    printf("max de l : %d\n", max_ter(l,0));
    T_liste lprime = inversion_rec_env(l);
    printf("l inversé :");
    afficher_liste(lprime);
    //inv_mis_list(&l);
    //afficher_liste(l);
    return EXIT_SUCCESS;
}