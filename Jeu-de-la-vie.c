#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define TAILLE_L 40
#define TAILLE_C 100
#define Intervalle 200000


void affiche(int monde[TAILLE_L][TAILLE_C])
{
   int i,j;

   for(i=0;i<TAILLE_L;++i)
   {
      for(j=0;j<TAILLE_C;++j)
      {
         if(monde[i][j]!=0) printf("◆");

         else printf(" ");
      }
      printf("\n");
   }
   printf("\n");
}

int voisin(int coord_L, int coord_C, int damier[TAILLE_L][TAILLE_C]){

        int nb_voisins=0;

        if (damier[coord_L+1][coord_C] == 1) nb_voisins++;
        if (damier[coord_L+1][coord_C-1] == 1) nb_voisins++;
        if (damier[coord_L][coord_C-1] == 1) nb_voisins++;
        if (damier[coord_L-1][coord_C-1] == 1) nb_voisins++;
        if (damier[coord_L-1][coord_C] == 1) nb_voisins++;
        if (damier[coord_L-1][coord_C+1] == 1) nb_voisins++;
        if (damier[coord_L][coord_C+1] == 1) nb_voisins++;
        if (damier[coord_L+1][coord_C+1] == 1) nb_voisins++;

        return nb_voisins;
}

void next_gen(int damier[TAILLE_L][TAILLE_C]){

        int i,j;
        int copie_damier[TAILLE_L][TAILLE_C];

        for(i=0;i<TAILLE_L;++i){
                for(j=0;j<TAILLE_C;++j){
                        copie_damier[i][j] = damier[i][j]; //Damier temporaire évitant l'influence des changements en cours sur la prochaine génération
                }
        }

        for(i=0;i<TAILLE_L;++i){
                for(j=0;j<TAILLE_C;++j){
                        int nb_vois = voisin(i, j, damier);
                        if (nb_vois>=4 || nb_vois<=1) copie_damier[i][j]=0; //Condition de mort d'une cellule
                        if (damier[i][j]== 0 && nb_vois==3) copie_damier[i][j]=1;   //Condition de naissance d'une cellule
                }
        }

        for(i=0;i<TAILLE_L;++i){
                for(j=0;j<TAILLE_C;++j){
                        damier[i][j] = copie_damier[i][j];
                }
        }
}

int main(){

        int tab[TAILLE_L][TAILLE_C] = {}; // Tableau permettant d'afficher les automates cellulaires
        tab[TAILLE_L/2][TAILLE_C/2] =1;   // Initialisation de la première génération de cellules :
        tab[TAILLE_L/2-1][TAILLE_C/2+1] =1;
        tab[TAILLE_L/2-2][TAILLE_C/2+1] =1;
        tab[TAILLE_L/2-1][TAILLE_C/2-1] =1;
        tab[TAILLE_L/2-2][TAILLE_C/2-1] =1;
        tab[TAILLE_L/2][1+TAILLE_C/2] =1;
        tab[TAILLE_L/2][TAILLE_C/2-1] =1;
        system("clear");
        affiche(tab);
        for (int i=0; i<=1000;i++) { //Limitation à l'affichage de 1000 génération
                next_gen(tab);
                usleep(Intervalle); // Intervalle d'affichage
                system("clear"); // Efface le shell
                affiche(tab);

        }
        return 0;
}
