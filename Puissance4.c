#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define COLONNE 10//7
#define LIGNE 12//6

/*---------------------TOUR DES JOUEURS-------------------------*/

void joueur_nom(char p1[256], char p2[256], int i){

  //p1=malloc(256*sizeof(*p2));//NE SERT STRICTEMENT A RIEN
  //p2=malloc(256*sizeof(*p2));//NE SERT STRICTEMENT A RIEN
  //VAUDRAIT MIEUX METTRE DES TABLEAUX STATIQUES

  if(i==0){
    printf("\n");
    printf("Donnez le nom du premier joueur: ");
    scanf("%s",p1);
    printf("Donnez le nom du deuxième joueur: ");
    scanf("%s",p2);

    printf("Bonjour\n\n");
    printf("Player 1: %s\n",p1);
    printf("Player 2: %s\n",p2);
  }

  if((i%2)!=0)
    printf("C'est à  %s de jouer !\n",p1);
  else
    printf("C'est à %s de jouer !\n",p2);


}


/*--------------------TOUR DES PIONS (PLAYER)-------------*/

char joueur_tour(char j1, char j2, int i){ //char mis ici
  if((i%2)!=0)return j1;
  else return j2;
}

/*---------------------Affichage-------------------*/

void Affichage(char tab[COLONNE][LIGNE]){
  int i;
  int j;
  int s;

  for(i=LIGNE-1;i>=0;i--){
    printf("\n");
    printf("\t\t");
    for(j=0;j<COLONNE;j++){
      printf("|__%c__|",tab[j][i]);
    }
  }

  printf("\n\t\t______________________________________________________________________\n");
  printf("\t\t");
  for(s=0;s<COLONNE;s++){
    printf("|  %d  |",s);
  }
  printf("\n");
}



 /*------Initialisation d'un tableau à '_'----------------*/
void initialisation(char tab[COLONNE][LIGNE]){
  int k, j;
  for(j=0;j<COLONNE;j++){
    for(k=LIGNE-1;k>=0;k--){
      tab[j][k]='_';
    }
  }
}

/*--------------interdiction---------------*/

/*Celle-ci permet de faire un choix en interdisant les nombres dans une intervalle*/

int interdiction_colonne(int choix,char tab[COLONNE][LIGNE]){
  while((choix<0 || choix>=COLONNE)||(tab[choix][11]!='_'))
    {

      printf("\n");
      printf("++++Choix incorrect, veuillez choisir un nombre entre 0 à 6...\n");
      printf("Entrez un nombre: ");
      scanf("%d",&choix);
      printf("\n");
    }
  return choix;
}

/*--------------GRAVITER----------------*/

void graviter(char tab[COLONNE][LIGNE], char pion, int choix){
  int i=0;
  choix=interdiction_colonne(choix,tab);

  while( (tab[choix][i]!='_') && (i < LIGNE-1) ){
    //interdiction_ligne(i);
    printf("tab[%d][%d]=%d\n",choix,i,tab[choix][i]);
    i++;
  }

  if(tab[choix][i]=='_'){
    tab[choix][i]=pion;
    //tour_joueur--;
  }

}

//renvoie juste 0 sii le pion a été posé sinon 1; cette fonction permet de gérer le tour des joueurs



/*----------------------Vertical---------------*/

int vertical(char tab[COLONNE][LIGNE], int choix){
  int i=0;

  while(tab[choix][i]!='_'){
    i++;
  }
  return i-1;
}

/*------------------Horizontal--------------------*/

int horizontal(char tab[COLONNE][LIGNE], int choix){
  int i=0;
  i=0;
  while(tab[choix][i]!='_'){
    i++;
  }
  return choix;
}

/*---------------------GAGNER------------------------*/

//Jouer is perfect. A RECTIFIER

int jouer(char tab[COLONNE][LIGNE],char pion, int nbr){
  int i=0;
  int j=0;
  int stock=0;

  int x;
  x=horizontal(tab,nbr);
  //printf("Colonne/vertical: %d\n",x);

  int y;
  y=vertical(tab,nbr);
  //printf("Ligne/horizontal: %d\n",y);

  /*------------horizontal----------------*/

  if(tab[nbr][y]==pion){

    while(tab[nbr][y]==tab[x+i][y]){
      i++;

      if(i>=6)return 1;
       if(i>6)return i;
    }

    while(tab[nbr][y]==tab[x-j][y]){

      j++;
      if(j>=6)return 1;
      if(j>6)return j;
    }

    stock=i+j;
    if(stock>=7)return 1;
  }


  /*---------------vertical--------------*/

  i=0;
  j=0;

  if(tab[nbr][y]==pion){
    while(tab[nbr][y]==tab[x][y-i]){
      i++;
      if(i>=6)return 1;
    }
  }
  return 0;
}
/* -------------------MAIN---------------------------*/



//REVOIR LE MAIN QUI PUE
int main(){

  /*---------Initialisation des joueurs + pions------------*/
  char p1[256],  p2[256], tab[COLONNE][LIGNE];;

  int nbr,n,i=0;

    /*---------Initialisation tableau------------*/
  initialisation(tab);

  printf("\n");

  /*--------------Demande le nom du joueur-------------------*/

    printf("\n");
    printf("Donnez le nom du premier joueur: ");
    scanf("%s",p1);
    printf("Donnez le nom du deuxième joueur: ");
    scanf("%s",p2);


    printf("\n\n");
    printf("Player 1: %s\n",p1);
    printf("Player 2: %s\n",p2);


    /*-----------------JEU MULTIJOUEUR------------------*/

    while(1){
      printf("\n");

      if(i==0){
	Affichage(tab);
      }

      /*-----------TOUR DES JOUEURS------------------*/

      printf("\n");
      if((i%2)!=0){
	printf("C'est à %s de jouer !\n",p2);
      }
      else
	{
	  printf("C'est à %s de jouer !\n",p1);
	}
      printf("\n");
      /*----------------------------------------*/

      printf("Choisir un déplacement: ");

      scanf("%d",&nbr);
      n=joueur_tour('X','O',i);
      graviter(tab, n ,nbr);

      Affichage(tab);
      i++;

      if((jouer(tab,n,nbr))==1){
	Affichage(tab);
	printf("\n");
	printf("Les %c ont gagné\n\n",n);
	return 0;
      }

      if(i==COLONNE*LIGNE){
	Affichage(tab);
	printf("\n");
	printf("Aucun joueur n'a gagner \n\n");
	return 0;
      }

    }
    /*-----------------------------------------------*/
    free(p1);
    free(p2);

  return 0;
}

//REVOIR LA SAISI D'UN NOMBRE ; SCANF EST POUR LES DÉBILES; revoir getchar ou fprintf(stdin, "Veuillez saisir un nombre : %d\n"); (FACILE)

//REVOIR COLLISION EN HAUT (FACILE) fait en JAVAFX



/*-----------Memo personnelle------------------------*/

/*Revoir le tableau qui est tr??s tr??s tr??s bizarre + malloc + realloc*/
/*Revoir le main pour:*/
//Jouer avec le pion que le joueur 1 choisi.



// comparer le plus grand entre COLONNE et LIGNE avec le pions mit

// si COLONNE est plus grand que LIGNE
//------Regarder à droite et à gauche du pion tant qu'il y a des pions

