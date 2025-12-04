/* ==================================== Include    =================================== */
#include <stdio.h>
#include <stdlib.h>

#include "liste.h"

/* ==================================== Functions and procedures =================================== */

int max(int a,int b){                            //renvoie le max entre a et b
    if(a>b) return a;
    return b;
}

T_liste creer_liste(){
    return NULL;
}

void ajout_entete_liste(T_liste* l, int element){
    T_liste new_link = malloc(sizeof(struct link));   //créer un nouveau maillon qui prend la place de l (le premier maillon de la liste)
        new_link->value=element;                      //définir la valeur de new_link
        new_link->next=*l;                            //pointer new_link sur la suite de la liste
        *l = new_link;                                //le début de l est maintenant new_link
}

T_liste ajouter_entete_fonc(T_liste* l, int element){
    T_liste new_link = malloc(sizeof(struct link));     //créer un nouveau maillon (qui sera le premier élément de la nouvelle liste)
    new_link->value = element;                          //définir sa valeur
    new_link->next = *l;                                 //le faire pointer sur l
    return new_link;                                    //renvoyer la nouvelle liste
}

void afficher_liste(T_liste l){
    T_liste temp;                                       //maillon temporaire pour parcourir la liste
    temp = l;
    while(temp!= NULL){
        printf("%d,", temp->value);                    //afficher la valeur du maillon courant
        temp = temp->next;                             //passer au maillon suivant
    }
    printf("\n");
}

void fafficher_dir_liste(T_liste l){
    if(l==NULL) printf("\n");
    else{
        printf("%d,", l->value);
        fafficher_dir_liste(l->next);
    }
}

void fafficher_inv_liste(T_liste l){
    T_liste lprime = creer_liste();                    //crée une nouvelle liste qui sera l inversée 
    while(l!=NULL){
        ajout_entete_liste(&lprime, l->value);        //ajoute le maillon actuel de l en tete de lprime
        l=l->next;                                    //avance dans l
    }
    afficher_liste(lprime);                            
}

void inv_mis_list(T_liste* l){ 
    if (l == NULL) return;
    T_liste prec = NULL;
    T_liste cour = *l;
    T_liste suiv = NULL;
    while(cour!=NULL){
        suiv=cour->next;            //sauvegarde la suite de la liste
        cour->next=prec;            //inverse le sens du pointeur next 
        prec=cour;                  //avance dans la liste
        cour=suiv;                  
    }
    *l=prec;                        //prec est la nouvelle tete de liste
}

T_liste inv_fonc_list(T_liste l){
    T_liste lprime = creer_liste();        //nouvelle liste = l inversée
    while(l!=NULL){
        ajout_entete_liste(&lprime, l->value);        //ajouter le maillon l en tete de lprime
        l=l->next;                                    //parcours l 
    }
    return lprime;
}


int long_env(T_liste l){
    int taille = 0;
    if(l==NULL){
        return taille;                      //cas de base : la liste est vide, on renvoie 0
    }
    else return 1+long_env(l->next);        //ajoute 1 pour chaque maillon parcouru
}


int long_ter_aux(T_liste l, int aux){       //fonction auxiliaire de long_ter, qui est appelée avec aux=0
    if(l==NULL) return aux;
    else{
        aux = long_ter_aux(l->next, aux+1);    //ajoute 1 a aux pour chaque maillon parcouru
        return aux;
    }
}

int long_ter(T_liste l){
    return long_ter_aux(l,0);
}

int max_env(T_liste l){
    int res = l->value;            //valeur du premier maillon
    if(l->next==NULL) return res;    //s'il n'y a pas d'autre maillon on renvoie la valeur du premier
    else
        return max(res,max_env(l->next));        //sinon on parcours récursivement la liste en gardant le plus grand élément entre la valeur du maillon actuel et celle du prochain maillon
    }
}


int max_ter_aux(T_liste l, int aux){        //fonction auxiliaire de max_ter, l'argument aux doit être l->value
    if(l==NULL) return aux;        //correspond à l->value si la liste ne contient qu'un seul elem
    else{
        return max_ter_aux(l->next, max(aux, l->value));        //parcours récursivement la liste en gardant le max
    }
}

int max_ter(T_liste l){
    return max_ter_aux(l, l->value);
}

T_liste ajout_fin(T_liste l,int val){    //fonction auxiliaire pour inversion_rec_env
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
    T_liste res = inversion_rec_env(l->next);        //parcours récursivement la liste
    res = ajout_fin(res, l->value);                  //ajoute l'élément courant à la fin de la liste
    return res;
}

T_liste inversion_term_aux(T_liste l, T_liste aux) {    //fonction auxiliaire pour inversion_rec_term, aux doit être NULL
    if (l == NULL) {
        return aux;
    }
    T_liste new = malloc(sizeof(struct link));        //nouveau maillon 
    new->value = l->value;
    new->next = aux;                                  //insère aux en tête de liste
    return inversion_term_aux(l->next, new);          //parcours la liste récursivement
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
