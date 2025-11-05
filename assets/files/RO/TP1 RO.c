/*
 ============================================================================
 Name        : TP1.c
 Author      : Constanza Corentin
 Version     :
 Copyright   : Your copyright notice
 Description : TP 1 RO : Pb du sac à dos
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Poids_Max 10

//----------------------------------------------Fonction----------------------------------------------//

long ProduitScalaire(int *U, int *V,int N)
{
	// Fonction qui renvoie le produit scalaire usuelle des deux vecteurs donné en entré.
	long ps ;
	int i ;
	for (ps=0, i=0; i<N; i++)
	{
		ps += (long)U[i]*V[i];
	}
	return ps;
}

void Affiche(int x[],int n)
{
	// Fonction qui affiche le vecteur (ou tableau) passé en entré.
	// Ici il s'agit d'un tableau de int
	int i;
	for ( i=0;i<n;i++)
	{
		printf("%d ",x[i]);
	}
	printf("\n");
}

void Affiche2(double x[],int n)
{
	//Fonction identique à la précédente mais prend un tableau de double au lieu d'un tableau
	// d'entier en entré.
	int i;
	for ( i=0;i<n;i++)
	{
		printf("%f ",x[i]);
	}
	printf("\n");
}

void  Combinaison(int *T, int k, int n)
{
	//Fonction récursive affichant l'integralité des combinaisons binaires possible dans un tableau T de n cases.
	//Entré:
	//		T : Tableau des combinaisons. Change de valeurs à chaque appel de la fonction
	//			n cases. Contient des valeurs binaires.
	//		n : nombre de case du tableau
	//		k : increment qui nous permet de nous "reperer" dans les appels succesifs de cette focntion recursive.
	//			lorsque k=n nous avons une nouvelle combinaison sinon il faut continuer les appels recursifs.
	//Sortie: aucune
	//rmq : affiche les combianaison dans l'ordre usuel. cad pour n = 2 par exemple : 00;01;10;11 soit 0,1,2,3.

	if (k==n)
	{
		Affiche(T,n);
	}

	else
	{
		T[k]=0;
		Combinaison(T,k+1,n);
		T[k]=1;
		Combinaison(T,k+1,n);
	}
}

void Brut_Force(int *T, int k, int n,int *M, int *Poids, int *Prix)
{
	int i;
	if (k==n)
	{
		if (ProduitScalaire(Poids,T,n)<=Poids_Max)
		{
			if (ProduitScalaire(Prix,T,n)>ProduitScalaire(Prix,M,n))
			{
				for (i=0; i<n;i++)
				{
					M[i]=T[i];
				}

			}
		}

	}

	else
	{
		T[k]=0;
		Brut_Force(T, k+1 ,n, M, Poids, Prix);
		T[k]=1;
		Brut_Force(T, k+1, n, M, Poids, Prix);
	}
}

void tri_bulle(int *T,int n)
{
	//Fonction qui effectue un tri à bulle sur les données stocker dans le tableau T de taille n.
	//entré:
	//		T : Tableau de données à trier
	//		n : Taille de T.

	int i, j, tab_tri, tmp;

	// Parcours de notre tableau. A chaque nouveau passage on parcours un élément en moins car cette élément
	// sera forcement plus grand que tout les éléments que l'on va evaluer au nouveau passage.
	// En effet pour chaque parcours, l'element le plus grand (si l'on trie la taille, cela pourrait être un
	// autre critère) est nécessairement envoyer à la fin du tableau.
	for (i=n-1;i>0;i--)
	{
		tab_tri=1;
		for (j=0;j<i-1;j++)
		{
			//Test si le prochain élément est plus petit, si oui on inverse l'élément actuel et le prochain afin
			//de faire "remonter" les plus grand éléments.
			if (T[j+1]<T[j])
			{
				tmp=T[j+1];
				T[j+1]=T[j];
				T[j]=tmp;

				//On actualise la variable nous permettant de savoir que notre tableau n'est pas encore
				//completement trier.
				tab_tri=0;
			}
		}

		//Lorsque l'on effectue un parcours du Tableau sans permutation et que donc la variable
		//tab_tri n'est pas modifier, cela signifie que notre tableau est trié. On peut donc interrompre
		//notre fonction de tri.
		if (tab_tri==1)
		{
			return;
		}
	}
}

void tri_bulle_appli(double *Ratio, int *numero,int n)
{
	//Application du tri à bulle vu precedament à notre problème. On va trier le ratio Prix/poids
	//On ajoute aussi un deuxième Tableau contenant les numero de chaque objets afin de pouvoir savoir
	//à quel objet correspond tel ratio.
	int i, j, tab_tri;
	double tmp=0;
	for (i=n-1;i>0;i--)
	{
		tab_tri=1;
		for (j=0;j<i-1;j++)
		{
			if (Ratio[j+1]<Ratio[j])
			{
				tmp=Ratio[j+1];
				Ratio[j+1]=Ratio[j];
				Ratio[j]=tmp;

				// On intervertie aussi les numeros d'objets afin de pouvoir savoir à quel objet
				//correspond tel ratio.
				tmp=numero[j+1];
				numero[j+1]=numero[j];
				numero[j]=tmp;

				tab_tri=0;
			}
		}
		if (tab_tri==1)
		{
			return;
		}
	}
}

void Glouton(int *Combinaison, int n, double *Poids, double *Prix)
{
	//Fonction qui resoud le problème du sac à dos en appliquant l'algorithme glouton. L'idée est
	//d'ajouté en priorité les objets les plus efficaces. Dans notre cas ce sont les objets avec le meilleur
	//ratio Prix/Poids.

	//rmq 1 : la complexité de cette algo dépends entièrement de la fonction de tri utiliser. Ici nous avons utilisé un
	//tri à bulle, de complexité O(n²) au maximum et en moyenne. Une optimisation possible est donc d'utiliser
	//un meilleurs tri comme le "quicksort" ou le "tri à fusion" ayant une complexité en O(nlog(n)).

	//rmq 2 : La solution depends aussi du tri utlisé mais sera toujours un resultat valide et proche de la
	//meilleurs solution possible (données par le brute force).
	//En effet siplusieurs objets ont le même ratio (c'est le cas dans notre exemple) leur ordre de tri
	//et donc de priorité pourrait varier d'un algo de tri à l'autre.
	int i;
	double Ratio[n];
	int numero[n];
	int Poids_Dispo = Poids_Max;

	//création du Tableau contenant le ratio de chaques objets
	//et le tableau contenant leur numero.
	for (i=0; i<n;i++)
		{
			Ratio[i]= Prix[i]/Poids[i];
			numero[i]=i;
		}

	//On tri nos objets selon la valeur de leur ratio Prix/Poids (dans l'ordre croissant)
	tri_bulle_appli(Ratio,numero, n);

	//On parcours notre tableau. Comme nos valeurs sont trié dasn l'ordre croissant, on doit parcourir
	//notre tableau à l'envers afin de commencer par l'objet avec le ratio le plus interréssant
	for (i=n-1; i>0; i--)
	{
		//Si l'objet que l'on regarde peut rentré dans le sac, on l'ajoute et on retire son poids
		//au poids disponible.
		if (Poids[numero[i]] <= Poids_Dispo)
		{
			Poids_Dispo=Poids_Dispo-Poids[numero[i]];
			Combinaison[numero[i]]=1;

		}
	}
}

//------------------------------------------------Test------------------------------------------------//

void Test_Combinaison()
{
	int n=3;
	int *T = malloc(n*sizeof(int));
	int k=0;
	Combinaison(T,k,n);
}

void Test_Brut_Force()
{
	int i;
	int n=6;
	int k=0;
	int *T = malloc(n*sizeof(int));
	int *M = malloc(n*sizeof(int));

	for (i=0; i<n;i++)
		{
			M[i]=0;
		}
	int Poids[n];
	int Prix[n];
	Poids[0] = 2;	Prix[0] = 4;
	Poids[1] = 3;	Prix[1] = 5;
	Poids[2] = 4;	Prix[2] = 2;
	Poids[3] = 3;	Prix[3] = 1;
	Poids[4] = 2;	Prix[4] = 4;
	Poids[5] = 7;	Prix[5] = 14;

	Brut_Force(T,k,n,M,Poids,Prix);
	Affiche(M,n);
}

void Test_tri_bulle()
{
	int n=6;
	int Poids[n];
	int Prix[n];
	Poids[0] = 2;	Prix[0] = 4;
	Poids[1] = 3;	Prix[1] = 5;
	Poids[2] = 4;	Prix[2] = 2;
	Poids[3] = 3;	Prix[3] = 1;
	Poids[4] = 2;	Prix[4] = 4;
	Poids[5] = 7;	Prix[5] = 14;
	tri_bulle(Poids, n);
	tri_bulle(Prix, n);
	Affiche(Poids, n);
	Affiche(Prix, n);

}

void Test_tri_bulle_appli()
{
	int i;
	int n=6;
	double Poids[n];
	double Prix[n];
	double Ratio[n];
	int numero[n];
	Poids[0] = 2.;	Prix[0] = 4.;
	Poids[1] = 3.;	Prix[1] = 5.;
	Poids[2] = 4.;	Prix[2] = 2.;
	Poids[3] = 3.;	Prix[3] = 1.;
	Poids[4] = 2.;	Prix[4] = 4.;
	Poids[5] = 7.;	Prix[5] = 14.;

	for (i=0; i<n;i++)
	{
		Ratio[i]= Prix[i]/Poids[i];
		numero[i]=i;
	}

	Affiche2(Ratio, n);
	tri_bulle_appli(Ratio,numero, n);
	Affiche2(Ratio, n);
	Affiche(numero, n);




}

void Test_Glouton()
{
	int i;
	int n=6;
	double Poids[n];
	double Prix[n];
	int Combi[n];

	Poids[0] = 2.;	Prix[0] = 4.;
	Poids[1] = 3.;	Prix[1] = 5.;
	Poids[2] = 4.;	Prix[2] = 2.;
	Poids[3] = 3.;	Prix[3] = 1.;
	Poids[4] = 2.;	Prix[4] = 4.;
	Poids[5] = 7.;	Prix[5] = 14.;
	for (i=0; i<n;i++)
	{
		Combi[i]=0;
	}
	Glouton(Combi, n, Poids, Prix);
	Affiche(Combi, n);
}

//------------------------------------------------Main------------------------------------------------//

int main(void) {

	//Test_Combinaison();		// OK
	//Test_Brut_Force();		// OK
	//Test_tri_bulle();			// OK
	//Test_tri_bulle_appli();	// OK
	Test_Glouton();				// OK

	//Comparaison des resultats : L'algorithme brute force nous donne comme attendu la meilleur
	//combinaison possible avec un prix de 19. Le gouton lui nous donne une combinaison avec un prix totale de
	//18. La solution du glouton n'est donc pas optimal mais reste une bonne approximation. De plus sur des jeu de
	//données avec un n très grand, le glouton sera bien plus rapide que le brute force. Comme le glouton donne
	//au pire une bonne approximation de la meilleur solution et ce dans un temps bien plus rapide que le brute force
	//il est bien plus adapté à l'études de gros jeux de données.
	//rmq : Le resultat du glouton peut varier en fonction de l'implementation du tri utilisé, notamment si plusieurs
	//objets ont le même ratio Prix/Poids.

	//Le brute force quand à lui est utile afin d'avoir une solution exacte sur de petit jeux de données comme
	//celui utiliser en exemple.

	return EXIT_SUCCESS;
}
