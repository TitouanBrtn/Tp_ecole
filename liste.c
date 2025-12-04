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
    return NULL;
}

void ajout_entete_liste(T_liste* l, int element){
    T_liste new_link = malloc(sizeof(struct link));   //créer un nouveau maillon qui prend la place de l (le premier maillon de la liste)
        new_link->value=element;
        new_link->next=*l;                               
        *l = new_link;                               //faire pointer l sur le nouveau maillon
}

T_liste ajouter_entete_fonc(T_liste* l, int element){
    T_liste new_link = malloc(sizeof(struct link));     //créer un nouveau maillon (qui sera le premier élément de la nouvelle liste)
    new_link->value = element;                          //définir sa valeur
    new_link->next = *l;                                 //le faire pointer sur l
    return new_link;                                    //renvoyer la nouvelle liste
}

void afficher_liste(T_liste l){
    T_liste temp;
    temp = l;
    while(temp!= NULL){
        printf("%d,", temp->value);
        temp = temp->next;
    }
    printf("\n");
}

void fafficher_dir_liste(T_liste l){
    if(l==NULL){
        printf("\n");
    }
    else{
        printf("%d,", l->value);
        fafficher_dir_liste(l->next);
    }
}

void fafficher_inv_liste(T_liste l){
    T_liste lprime = creer_liste();
    while(l!=NULL){
        ajout_entete_liste(&lprime, l->value);
        l=l->next;
    }
    afficher_liste(lprime);
}

void inv_mis_list(T_liste* l){ 
    if (l == NULL) return;
    T_liste prec = NULL;
    T_liste cour = *l;
    T_liste suiv = NULL;
    while(cour!=NULL){
        suiv=cour->next;
        cour->next=prec;
        prec=cour;
        cour=suiv;
    }
    *l=prec;
}

T_liste inv_fonc_list(T_liste l){
    T_liste lprime = creer_liste();
    while(l!=NULL){
        ajout_entete_liste(&lprime, l->value);
        l=l->next;
    }
    return lprime;
}


int long_env(T_liste l){
    int taille = 0;
    if(l==NULL){
        return taille;
    }
    else return 1+long_env(l->next);
}


int long_ter_aux(T_liste l, int aux){       //aux doit être 0 lorsqu'on appelle la fonction
    if(l==NULL) return aux;
    else{
        aux = long_ter_aux(l->next, aux+1);
        return aux;
    }
}

int long_ter(T_liste l){
    return long_ter_aux(l,0);
}

int max_env(T_liste l){
    int res = l->value;
    if(l->next==NULL) return res;
    else{
        return max(res,max_env(l->next));
    }
}


int max_ter(T_liste l, int aux){        //l'argument aux doit l->value
    if(l==NULL) return aux;
    else{
        return max_ter(l->next, max(aux, l->value));
    }
}

T_liste ajout_fin(T_liste l,int val){
    T_liste new = malloc(sizeof(struct link));
    new->value = val;
    new->next = NULL;
    if(l==NULL) return new;
    T_liste temp = l;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next = new;
    return l;
}

T_liste inversion_rec_env(T_liste l){
    if(l==NULL) return NULL;
    T_liste res = inversion_rec_env(l->next);
    res = ajout_fin(res, l->value);
    return res;
}

T_liste inversion_term_aux(T_liste l, T_liste aux) {
    if (l == NULL) {
        return aux;
    }
    T_liste new = malloc(sizeof(struct link));
    new->value = l->value;
    new->next = aux;
    return inversion_term_aux(l->next, new);
}

T_liste inversion_rec_term(T_liste l) {
    return inversion_term_aux(l, NULL);
}

int main(){
    T_liste l = creer_liste();
    ajout_entete_liste(&l,12);
    ajout_entete_liste(&l,2);
    ajout_entete_liste(&l,4);
    ajouter_entete_fonc(&l,5);
    ajout_entete_liste(&l,7);
    afficher_liste(l);
    printf("taille de l : %d\n",long_ter(l));
    printf("max de l : %d\n", max_ter(l,l->value));
    T_liste lprime = inversion_rec_term(l);
    printf("l inversé :");
    afficher_liste(lprime);
    return EXIT_SUCCESS;
}
