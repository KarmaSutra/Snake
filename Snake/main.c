#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>



#define LARGEUR 110
#define LONGUEUR 30
#define TAILLEMAX 50


typedef struct coordonnees{
        int x;
        int y;

}coordonnees;

typedef struct serpent
{

        int taille;
        coordonnees serpent_corps[TAILLEMAX];


}serpent;

typedef struct cake
{
        coordonnees coord_cake;
}cake;

//PROTOTYPES
void gotoxy(int,int);
void map_creation();
void placement_snake(serpent*);
void placement_cake(cake*);
void snake_avance(serpent*,int);
void attendre (float);
int collision(serpent);
void miam (serpent*, cake*,int);
int croque_queue(serpent);




int main(){

    int keypress=VK_RIGHT; //la direction de base du snake est vers la droite



    serpent snake;
    snake.taille=1; //on règle sa taille à un morceau de corps en plus de la tête
    cake gateau;


        srand (time(0));
        map_creation(); //generation de la map
        placement_snake(&snake); //on place le snake dans la map
        placement_cake(&gateau); //on place le gateau dans la map

do{

    if(kbhit()) //recupère la touche pressée par le joueur sans interrompre le flux du jeu
    {
        keypress=getch(); //on stocke la valeur recuperee dans la variable associée
    }
    snake_avance(&snake, keypress); //avancement du snake dans la direction choisie par le joueur (par defaut vers la droite)

if ((collision(snake)==1)|(croque_queue(snake)==1)) //conditions de fin du jeu. Cette boucle se déclenche en toutes circonstances, créant une fermeture instantanée du progralle. Je n'ai pas réussi à identifier la source du problème.
    {
        gotoxy(LONGUEUR+1,LARGEUR/2);
        printf("Perdu\n");
        system("pause");
        return 0; //fin du jeu et fermeture de la fenêtre
    }else{
    miam (&snake,&gateau,keypress); //si conditions sont negatives, on teste si le snake mange le gateau, si oui il grandit et un autre gateau apparait
    attendre(1);}//fonction qui stoppe le programme pendant 1 seconde, laissant un temps au joueur pour planifier ses déplacements et les corriger si besoin
}while(snake.taille<=TAILLEMAX); //taille max pour snake de 50


        gotoxy(LONGUEUR/2,LARGEUR/2);
        printf("Votre snake a atteint la taille maximale.\n Vous avez gagné.\n");
        system("pause");
        return 0;
}




void gotoxy(int a,int b)
{
COORD coord;



coord.Y=a;
coord.X=b;

SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}




void map_creation()
{
int i,j;

   for(i=0;i<LONGUEUR;i++){

        for(j=0;j<LARGEUR;j++){
            switch(i){
            case 0:printf("#");
            break;
            case (LONGUEUR-1):printf("#");
            break;
            default: switch(j){

                      case 0:printf("#");
                      break;
                      case (LARGEUR-1):printf("#");
                      break;
                      default:printf(" ");
                      break;
                     }
            }


        }
        printf("\n");
    }
   }

void placement_snake(serpent *snake)
{
    (*snake).serpent_corps[0].x=(LARGEUR/2)-1;
    (*snake).serpent_corps[0].y=(LONGUEUR/2)-1;
    (*snake).serpent_corps[1].x= ((*snake).serpent_corps[0].x)-1;
    (*snake).serpent_corps[1].y=(*snake).serpent_corps[0].y;

    gotoxy((*snake).serpent_corps[0].y,(*snake).serpent_corps[0].x);
    printf("S");

    gotoxy((*snake).serpent_corps[1].y,(*snake).serpent_corps[1].x);
    printf("s");


}


void placement_cake(cake* gateau)
{
    (*gateau).coord_cake.x=(rand() % (LARGEUR-2))+1;
    (*gateau).coord_cake.y=(rand() % (LONGUEUR-2))+1;

    gotoxy((*gateau).coord_cake.y,(*gateau).coord_cake.x),
    printf ("G");
}


void snake_avance (serpent *snake,int keypress)
{

int i;
            gotoxy((*snake).serpent_corps[(*snake).taille].y,(*snake).serpent_corps[(*snake).taille].x);
            printf(" ");

            for(i=(*snake).taille;i>=1;i--)
            {
                (*snake).serpent_corps[i].x=(*snake).serpent_corps[i-1].x;
                (*snake).serpent_corps[i].y=(*snake).serpent_corps[i-1].y;
                gotoxy((*snake).serpent_corps[i].y,(*snake).serpent_corps[i].x);
                printf("s");
            }

         switch (keypress)
                {
                case VK_UP:
                    {       gotoxy((*snake).serpent_corps[0].y,(*snake).serpent_corps[0].x);
                            printf(" ");
                            (*snake).serpent_corps[0].y+=1;
                            gotoxy((*snake).serpent_corps[0].y,(*snake).serpent_corps[0].x);
                            printf("S");
                    }

                case VK_DOWN:
                    {
                            gotoxy((*snake).serpent_corps[0].y,(*snake).serpent_corps[0].x);
                            printf(" ");
                            (*snake).serpent_corps[0].y-=1;
                            gotoxy((*snake).serpent_corps[0].y,(*snake).serpent_corps[0].x);
                            printf("S");

                    }
                case VK_LEFT:
                    {
                            gotoxy((*snake).serpent_corps[0].y,(*snake).serpent_corps[0].x);
                            printf(" ");
                            (*snake).serpent_corps[0].x-=1;
                            gotoxy((*snake).serpent_corps[0].y,(*snake).serpent_corps[0].x);
                            printf("S");
                    }
                case VK_RIGHT:
                    {
                            gotoxy((*snake).serpent_corps[0].y,(*snake).serpent_corps[0].x);
                            printf(" ");
                            (*snake).serpent_corps[0].x+=1;
                            gotoxy((*snake).serpent_corps[0].y,(*snake).serpent_corps[0].x);
                            printf("S");
                    }
                }


}


void attendre(float temps)
{
    clock_t arrivee=clock()+(temps*CLOCKS_PER_SEC); //on stocke dans une variable le temps t d'ouverture du programme auquel on ajoute une seconde. Lorsque le temps d'ouverture du programme a atteint le temps voulu, on sort de la procedure, ce qui a permis un temps de pause de 1 seconde.

    while(clock()<arrivee);
}


int collision(serpent snake)
{

    if ((snake.serpent_corps[0].x==LARGEUR)|(snake.serpent_corps[0].x==0)|(snake.serpent_corps[0].y==LONGUEUR)|(snake.serpent_corps[0].y==0))
    {
        return 1;
    }else{
        return 0;
    }

}



void miam(serpent* snake, cake* gateau, int keypress)
{
    if ((*snake).serpent_corps[0].x==(*gateau).coord_cake.x&&(*snake).serpent_corps[0].y==(*gateau).coord_cake.y)
    {
        switch (keypress)
        {
            case VK_UP:(*snake).serpent_corps[(*snake).taille].x=((*snake).serpent_corps[(*snake).taille-1].x)-1;
            break;
            case VK_DOWN:(*snake).serpent_corps[(*snake).taille].x=((*snake).serpent_corps[(*snake).taille-1].x)+1;
            break;
            case VK_RIGHT:(*snake).serpent_corps[(*snake).taille].y=((*snake).serpent_corps[(*snake).taille-1].y)-1;
            break;
            case VK_LEFT:(*snake).serpent_corps[(*snake).taille].y=((*snake).serpent_corps[(*snake).taille-1].x)+1;
            break;
        }
        gotoxy((*snake).serpent_corps[(*snake).taille].y,(*snake).serpent_corps[(*snake).taille].x);
        printf("s");
        placement_cake(&gateau);

    }
}

int croque_queue(serpent snake) //Je pense que c'est cette fonction qui pose problème et que le snake se mord la queue en toutes circonstances
{
    int reponse;
    int i=1;

    do
    {
        if ((snake.serpent_corps[0].x==snake.serpent_corps[i].x)&(snake.serpent_corps[0].y==snake.serpent_corps[i].y))
        {
            reponse=1;
        }else{
            reponse=0;
        }
        i++;
    }while ((reponse==0)||(i<=snake.taille));

    return reponse;
}





