/* gcc -W -Wall YALAP_Joseph_Final.c -o ex  */
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<unistd.h>

#define FOURMILIERE_L 13
#define FOURMILIERE_C 13
#define N 27 

int demiTour(int orientation);
int detectionFourmiliere(int *i, int *j);
int detectionObstacle(int *i, int *j, int orientation, int Map[N][N]);
int rotationFourmi(int orientationint);
int updateOrientationRecherche(int orientation);
int updateOrientationRetour(int *i, int *j);
void move(int *i, int *j, int orientation);
int detectionNourriture(int *i, int *j, int orientation, int Map[N][N]);
int detectionNourriture1(int *i, int *j, int orientation, int Map[N][N]);
void printFourmi(int Map[N][N], int *i, int *j);


int main()
{
	int Map[N][N]={{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		     {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		     {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,-1},
		     {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,-1},
		     {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,-1},
		     {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,-1},
		     {-1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,0,0,0,0,0,-1},
		     {-1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		     {-1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		     {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		     {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		     {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		     {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		     {-1,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		     {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		     {-1,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		     {-1,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		     {-1,0,0,0,1,1,1,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		     {-1,0,0,0,1,1,1,0,-1,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,0,0,0,0,-1},
		     {-1,0,0,0,1,1,1,0,-1,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,-1},
		     {-1,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,-1,0,1,1,1,1,0,-1},
		     {-1,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,-1,0,1,1,1,1,0,-1},
		     {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,-1},
		     {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,-1},
		     {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		     {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		     {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}};
	
	int orientation;
	int fourmilierL; 
	int fourmilierC;
	fourmilierL = FOURMILIERE_L; 
	fourmilierC = FOURMILIERE_C;
	int *i = &fourmilierL; 
	int *j = &fourmilierC; // démarre de la fourmiliere
	int conscience; // variable pour representer l'inteligence de la fourmi
	int rotation;
	int stop;
	int e;
	int resultat;
	int memoire;
	int continu = 1; // variable pour réguler la vitesse de refresh
	int mode=0;
	srand(time(NULL));
	orientation = (int)((7-0)*(rand() / (double)RAND_MAX ) ); 
	rotation  = (int)((1-0)* (rand() / (double)RAND_MAX) ); // les preference de la fourmi
	if(rotation == 0)
	{
		rotation = -1; // pour avoir -1 ou 1
	}

	do
	{	
		if(mode == 0)
		{	
			mode = detectionNourriture(i, j, orientation ,Map);
			if(mode == 0)
			{			
				orientation = updateOrientationRecherche(orientation);
				while (detectionObstacle(i, j, orientation, Map) != 1)
				{
					orientation = rotationFourmi(orientation);	
				}				
			}
		}
		else 
		{
			if(Map[*i][*j] == 1)
			{
				Map[*i][*j] = Map[*i][*j] - 1;
				memoire = memoire +1;
				e = e+1;
			}
			if (detectionFourmiliere(i, j) == 1)
			{
				orientation = demiTour(orientation);
				mode = 0;
			}
			else
			{		
				orientation = updateOrientationRetour(i, j);
				conscience = (int)(91 * (rand() / (double)RAND_MAX) ); // Selon la doc 
				if(conscience < 5)
				{
					orientation = orientation +1;
				}
				else if(conscience == 5)
				{
					orientation = orientation +2;
				}
				else if(conscience > 84)
				{
					orientation = orientation -1;
				}
				else if(conscience == 84)
				{
					orientation = orientation -2;
				}
				while (detectionObstacle(i, j, orientation, Map) != 1) 
				{
				orientation = rotationFourmi(orientation);	
				}
				while(detectionNourriture1(i, j, orientation, Map) != 1)
				{
					orientation = rotationFourmi(orientation);
				}
			}
		}
		move(i, j, orientation);
		printFourmi(Map, i,j);
		continu = continu-1;
		if(continu == 0)
		{
			printf("Combien de tours doivent se dérouler ?\n");
			scanf("%d",&continu);
			if(stop == 1)
			{
				printf("Voulez-vous arretez le jeu ? Oui-1/Non-0\n");
				scanf("%d",&stop);
				if(stop == 1)
				{
					printf("Voulez-vous voir combien d'unité de nourriture vous avez récolté ? Oui-1/Non-0\n");
					scanf("%d",&resultat);
					if(resultat == 1)
					{
						printf("Vous avez récolté %d d'unité de nourriture\n",e);
						return EXIT_SUCCESS;
					}
					else 
					{
						return EXIT_SUCCESS;
					}
				}
			}
		}
	stop = 1;
	usleep(100000);	
	}
	while (continu > 0 && stop == 1);	
	return EXIT_SUCCESS;
}

/*

	printFourmi(Map, N);
	demiTour(orientation);
	
	detectionFourmiliere(i, j);
	detectionObstacle(i, j, orientation);
	rotationFourmi(orientation);
	updateOrientationRecherche(orientation);
	updateOrientationRetour(i, j);
	move(&i, &j, orientation);
	detectionNourriture(i, j, orientation);
*/

int demiTour(int orientation)
{
	return (orientation + 4)%8;
		
}

int detectionFourmiliere(int *i, int *j)
{
	return *i == FOURMILIERE_L && *j == FOURMILIERE_C ? 1 : 0;
}

int detectionObstacle(int *i, int *j, int orientation, int Map[N][N])
{
	switch(orientation)
	{
		case(0):
			return Map[*i-1][*j] == -1 ? 0 : 1; // -1 sur une case sera notre obstacle 
			break;
		case(1):
			return Map[*i-1][*j+1] == -1 ? 0 : 1;
			break;
		case(2):
			return Map[*i][*j+1] == -1 ? 0 : 1;
			break;
		case(3):
			return Map[*i+1][*j+1] == -1 ? 0 : 1;
			break;
		case(4):
			return Map[*i+1][*j] == -1 ? 0 : 1;
			break;
		case(5):
			return Map[*i+1][*j-1] == -1 ? 0 : 1;
			break;
		case(6):
			return Map[*i][*j-1] == -1 ? 0 : 1;
			break;
		case(7):
			return Map[*i-1][*j-1] == -1 ? 0 : 1;
			break;
		default:		
			break;
	}
	return 0;
}

int detectionNourriture1(int *i, int *j, int orientation, int Map[N][N])
{
	switch(orientation)
	{
		case(0):
			return Map[*i-1][*j] == 1 ? 0 : 1; // -1 sur une case sera notre obstacle 
			break;
		case(1):
			return Map[*i-1][*j+1] == 1 ? 0 : 1;
			break;
		case(2):
			return Map[*i][*j+1] == 1 ? 0 : 1;
			break;
		case(3):
			return Map[*i+1][*j+1] == 1 ? 0 : 1;
			break;
		case(4):
			return Map[*i+1][*j] == 1 ? 0 : 1;
			break;
		case(5):
			return Map[*i+1][*j-1] == 1 ? 0 : 1;
			break;
		case(6):
			return Map[*i][*j-1] == 1 ? 0 : 1;
			break;
		case(7):
			return Map[*i-1][*j-1] == 1 ? 0 : 1;
			break;
		default:		
			break;
	}
	return 0;
}

int rotationFourmi(int orientation)
{
	orientation = (orientation + 1) %8;
	return orientation;
}

int OrientationMemoire(int *i, int *j, int memoire)
{
	if(memoire > 4)
	{
		memoire = memoire - 4;
	}
	if(memoire == 1)
	{
		if((*i > 5) && (*j < 24))
		{
			return 2;
		}
		else if((*i == 5) && (*j < 24))
		{
			return 3;
		}
		else if((*i > 5) && (*j == 24))
		{
			return 7;
		}
	}
	else if(memoire == 2)
	{	
		if((*i < 25) && (*j < 24))
		{
			return 4;
		}
		else if((*i == 25) && (*j < 24))
		{
			return 3;
		}
		else if((*i < 25) && (*j == 24))
		{
			return 5;
		}
	}
	else if(memoire == 3)
	{
		if((*i < 18) && (*j > 5))
		{
			return 6;
		}
		else if((*i < 18) && (*j == 5))
		{
			return 5;
		}
		else if((*i == 18) && (*j > 5))
		{
			return 7;
		}
	}
	else if(memoire == 4)
	{
		if((*i > 9) && (*j > 7))
		{
			return 0;
		}	
		else if((*i == 9) && (*j > 7))
		{
			return 7;
		}
		else if((*i > 9) && (*j == 7))
		{
			return 1;
		}
	}		
	return 0;
}

int updateOrientationRecherche(int orientation)
{

	srand(time(NULL));
	int randoom = (int)( (32) * (rand() / (double)RAND_MAX) )+1; 

	if(randoom<=16)
	{
		if(randoom <= 12)
		{
			orientation = orientation;
		}
		else if(randoom > 12 && randoom < 15)
		{
			orientation = orientation +1 ;
		}
		if(randoom == 15)
		{
			orientation = orientation +2 ;
		}
		else if(randoom == 16)
		{
			orientation = orientation +3 ;
		}
	}
	else 
	{
		if(randoom <= 28)
		{
			orientation = orientation;
		}
		else if(randoom > 28 && randoom < 31)
		{
			orientation = orientation -1 ;
		}
		if(randoom == 31)
		{
			orientation = orientation -2 ;
		}
		else if(randoom == 32)
		{
			orientation = orientation -3 ;
		}
	}

	if(orientation > 31)
		{
			orientation = orientation -2 ;
		}
		else if(randoom == 32)
		{
			orientation = orientation -3 ;
		}
	return orientation;	
}

int updateOrientationRetour(int *i, int *j)
{
		if(*i < (N/2) && *j < (N/2) )
		{
			return 3;
		}
		else if(*i < (N/2) && *j == (N/2) )
		{
			return 4;
		}
		else if(*i < (N/2) && *j > (N/2) )
		{
			return 5;
		}
		else if(*i == (N/2) && *j > (N/2) )
		{
			return 6;
		}
		else if(*i > (N/2) && *j > (N/2) )
		{
			return 7;
		}
		else if(*i > (N/2) && *j == (N/2) )
		{
			return 0;
		}
		else if(*i > (N/2) && *j < (N/2) )
		{
			return 1;
		}	
		else if(*i == (N/2) && *j < (N/2) )
		{
			return 2;
		}
			
	return 0;
}

void move(int *i, int *j, int orientation)
{
		switch(orientation)
		{
			case(0):
				*i=*i-1;
				break;

			case(1):
				*i=*i-1;
				*j=*j+1;
				break;

			case(2):
				*j=*j+1;
				break;

			case(3):
				*i=*i+1;
				*j=*j+1;
				break;

			case(4):
				*i=*i+1;
				break;

			case(5):
				*i=*i+1;
				*j=*j-1;
				break;

			case(6):
				*j=*j-1;
				break;

			 case(7):
				*i=*i-1;
				*j=*j-1;
				break;

			default:		
				break;
		}
}

int detectionNourriture(int *i, int *j, int orientation, int Map[N][N])
{
	 switch(orientation)
	{
		case(0):
			return Map[*i-1][*j] == 1 ? 1 : 0;
			break;
		case(1):
			return Map[*i-1][*j+1] == 1 ? 1 : 0;
			break;
		case(2):
			return Map[*i][*j+1] == 1 ? 1 : 0;
			break;
		case(3):
			return Map[*i+1][*j+1] == 1 ? 1 : 0;	
			break;
		case(4):
			return Map[*i+1][*j] == 1 ? 1 : 0;
			break;
		case(5):
			return Map[*i+1][*j-1] == 1 ? 1 : 0;
			break;
		case(6):
			return Map[*i][*j-1] == 1 ? 1 : 0;
			break;
		case(7):
			return Map[*i-1][*j-1] == 1 ? 1 : 0;
			break;
		
		default:		
			break;
	}
	return 0; 


}

void printFourmi(int Map[N][N], int *i, int *j)
{
	int ii,jj;
	for(ii=0;ii<N;ii++)
	{
		for(jj=0;jj<N;jj++)
		{
			if(ii==*i && jj==*j)
			{
				//char *c = "🐜";
				//sprintf(c,"%c","\uD83D\uDC1C");
				printf("🐜");
			}
			else
			{
				switch(Map[ii][jj])
				{
					case(-2):
						printf("🎪");
						break;
					case(-1):
						printf(" *");
						break;					
					case(0):
						printf("  ");
						break;
					case(1):
						printf("🍏");
						break;
					default:
						printf("!");
						break;						
				}
			}
		}
		printf(" \n");
	}
	printf(" \n");
}