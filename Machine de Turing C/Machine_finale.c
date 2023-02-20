//WACRENIER NICOLAS 26/10/2021
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/************** Structure demandée ***********/

typedef struct codeTuring {
	int etatDepart;
	char valeurCourante;
	char nouvelleValeur;
	int etatSuivant;
	int deplacement;      // {-1,0,1} 
	struct codeTuring * codeSuivant;
	struct codeTuring * codePrecedent;
} tCodeTuring ; 


typedef struct bandeTuring {
	char valeur;
	struct bandeTuring * placeSuivant;
	struct bandeTuring * placePrecedent;
} tBandeTuring;

tBandeTuring * teteLecture;

/**********************************************/

//Fonction qui permet de vider le buffer pour résoudre le problème du scanf avec la touche entrée
static void purger(void)
{
    int c;
 
    while ((c = getchar()) != '\n' && c != EOF)
    {}
}

//Fonction d'insertion pour la bande
void insertionBande (tBandeTuring *px){
	tBandeTuring *py;
	py = (tBandeTuring *)malloc(sizeof(tBandeTuring));
	py -> placeSuivant = px -> placeSuivant;
	py -> placePrecedent = px;
	px -> placeSuivant -> placePrecedent= py;
	px -> placeSuivant = py;
	
}

//Fonction d'insertion pour le code
void insertionCode (tCodeTuring *px){
	tCodeTuring *py;
	py = (tCodeTuring *)malloc(sizeof(tCodeTuring));
	py -> codeSuivant = px -> codeSuivant;
	py -> codePrecedent = px;
	px -> codeSuivant -> codePrecedent= py;
	px -> codeSuivant = py;
	
}

//Fonction de déplacement du curseur
void gotoLigCol( int lig, int col )
{
// ressources
	COORD mycoord;
	
	mycoord.X = col;
	mycoord.Y = lig;
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}

//Fonction de déplacement du curseur et de suppression de la ligne
void gotoDel(int x, int y){

	//On va à la position demandée
	gotoLigCol(x, y);
	//On efface avec des espaces
	printf("                                                                                                                            ");
	gotoLigCol(x, y);
}

//On définit une entier qui permettra de savoir à combien de ligne fait l'affichage du code
int ligneCodeFin;

//Fonction d'affichage du cadre
void cadre(int x, int y, int haut, int larg){
	int i,j;
	char c,cvertical,  	chorizontal,   	cangleGH,    	cangleGB,    	cangleDH,    	cangleDB;
	cvertical=186;
	chorizontal=205;
	cangleGH=201;
	cangleGB=200;
	cangleDH=187;
	cangleDB=188;
	
	//ligne haut
	gotoLigCol(x,y);
	printf("%c",cangleGH);
	i=larg; 
	while(i>0)	{	
		printf("%c",chorizontal);
		i=i-1;
	};
	printf("%c",cangleDH);
	
	// ligne intermediaires
	j= haut;

	while(j>0){
		gotoLigCol(x+j,y);	
		printf("%c",cvertical);
		i=larg; 
		while(i>0)	{	
			printf("%c",' ');
			i=i-1;
		};
		j=j-1;
		printf("%c",cvertical);
	}
	//ligne bas
	gotoLigCol(x+haut,y);
	printf("%c",cangleGB);
	i=larg; 
	while(i>0)	{	
		printf("%c",chorizontal);
		i=i-1;
	};
	printf("%c",cangleDB);
}

//Fonction pour lire les touches du clavier qui ne sont pas des lettres
int lireCaract(){
	
		char c=10;
		int fnt=0;	
		
		c=getch();
		fnt=c;
		if (c==-32){c=getch();fnt = 400+c;}
		if (c==0)  {c=getch();fnt = 500+c;}
		return fnt;	
}

//Fonction de création de la bande de Turing
void creationBande (tBandeTuring *pDebut, tBandeTuring *pFin){
	
	tBandeTuring *px;
	char i;
	px = pDebut;
	puts("Entrer les valeurs et finir par q ");
	cadre(4,2,2,140);
	do{
		
		gotoDel(5,3);
		scanf("%c", &i);
		
	 	if(i == '1' || i == '0'){	
			insertionBande(px);
			px = px->placeSuivant;
			px->valeur = i;		
		 
		}
		
	}while (i != 'q');
}

//Fonction d'affichage de la bande de turing
void afficheBande(tBandeTuring *pDebut, tBandeTuring *pFin){
	
	tBandeTuring *px;
	
	px = pDebut -> placeSuivant;
	gotoDel(5,3);
	
	while(px != pFin){		
		
		printf("%c", px -> valeur);
		px = px->placeSuivant;
	}	
}

//Fonction de creation du code de Turing
void creationCode (tCodeTuring *pDebut, tCodeTuring *pFin){
	
	tCodeTuring *px;
	char c = '0';
	int etatS = 1;
	int i;
	px = pDebut;
	gotoDel(9,2);
	printf("Entrer le code, et mettre l'etat suivant a 0 pour terminer");
	while (etatS != 0){
		
		insertionCode(px);
		px = px->codeSuivant;

		gotoDel(10,2);
		printf("Etat de depart : ");
		gotoDel(11,2);
		scanf("%d", &i);
		px -> etatDepart = i;
		
		
		purger();
		gotoDel(10,2);
		printf("Valeur courante (0 ou 1) : ");
		gotoDel(11,2);
		scanf("%c", &c);		
		//Tant que la valeur n'est pas 0 ou 1 on redemande d'entrer la valeur
		while(c != '1' && c != '0'){
			gotoDel(10,2);
			puts("Rentrez une valeur correcte (0 ou 1) :");
			gotoDel(11,2);
			purger();
			scanf("%c", &c);		
		}
		px -> valeurCourante = c;
		
		
		purger();
		gotoDel(10,2);	
		printf("Nouvelle valeur (0 ou 1) : ");
		gotoDel(11,2);
		scanf("%c", &c);		
		while(c != '1' && c != '0'){
			gotoDel(10,2);
			puts("Rentrez une valeur correcte (0 ou 1) :");
			gotoDel(11,2);
			purger();
			scanf("%c", &c);		
		}
		px -> nouvelleValeur = c;


		purger();
		gotoDel(10,2);
		printf("Deplacement (-1, 0 ou 1) : ");
		gotoDel(11,2);
		scanf("%d", &i);
		while(i != 1 && i != 0 && i != -1){	
			gotoDel(10,2);
			puts("Rentrez un deplacement correct (-1, 0 ou 1) :");	
			gotoDel(11,2);
			purger();
			scanf("%d", &i);		
		}
		px -> deplacement = i;
		
		
		purger();
		gotoDel(10,2);
		printf("Etat Suivant : ");
		gotoDel(11,2);
		scanf("%d", &etatS); 
		px -> etatSuivant = etatS;
		puts("\n");
		purger();
		
	}
}

//Fonction d'affichage du code de Turing
void afficheCode(tCodeTuring *pDebut, tCodeTuring *pFin){
   
    tCodeTuring *px;
	int i = 1;
   
	gotoDel(10,2);
    printf("Code de Turing : ");
   
    px = pDebut -> codeSuivant;
   
    while(px != pFin){
       
		gotoDel(10 + i,2);
        printf("q%d    ",px -> etatDepart);
        printf("%c    ",px -> valeurCourante);
        printf("%c",px -> nouvelleValeur);
        if(px->deplacement==1){printf(" -> ");}
        else if(px->deplacement==-1){printf(" <- ");}
        else{printf(" - ");}
        printf("q%d",px -> etatSuivant);
           
        px = px -> codeSuivant;
		i++;
    }

	//On compte combien de ligne fait le code pour pouvoir afficher le reste après celui-ci
	ligneCodeFin = i;
}

//Fonction de sélection du mode d'exécution du code qui retourne le choix souhaité
int ModeAffichage(){
	
	int Choix;
	gotoLigCol(14 + ligneCodeFin, 2);
	printf("Entrez 1 si vous choisissez le mode etape par etape, sinon, entrez 0 si vous choisissez le mode automatique :");
	gotoLigCol(15 + ligneCodeFin, 2);
	scanf("%d", &Choix);
	
	return Choix;
}

//Fonction appelée pour modifier le code de Turing après sa création
void ModifCode (tCodeTuring *pDebut, tCodeTuring *pFin, tCodeTuring *px, int x, int y){
	
	char c = '0';
	int i;
	gotoDel(x, y);
	printf("Entrez les nouvelles donnees de votre ligne :");

		
	gotoDel(x, y);
	printf("Etat de depart a remplacer");
	gotoDel(x +1, y);
	scanf("%d", &i);
	px -> etatDepart = i;
		
		
	purger();
	gotoDel(x, y);
	printf("Valeur courante a remplacer (0 ou 1)");
	gotoDel(x+1, y);
	scanf("%c", &c);		
	while(c != '1' && c != '0'){
		gotoDel(x, y);
		puts("Rentrez une valeur correcte (0 ou 1) :");
		purger();
		gotoDel(x+1, y);
		scanf("%c", &c);		
	}
	px -> valeurCourante = c;
	
	
	purger();
	gotoDel(x, y);
	printf("Nouvelle valeur a remplacer(0 ou 1)");
	gotoDel(x+1, y);
	scanf("%c", &c);		
	while(c != '1' && c != '0'){
		gotoDel(x, y);
		puts("Rentrez une valeur correcte (0 ou 1) :");
		gotoDel(x+1, y);
		purger();
		scanf("%c", &c);		
	}
	px -> nouvelleValeur = c;

	purger();
	gotoDel(x, y);
	printf("Deplacement a remplacer(-1, 0 ou 1)");
	gotoDel(x+1, y);
	scanf("%d", &i);
	while(i != 1 && i != 0 && i != -1){	
		gotoDel(x, y);
		puts("Rentrez un deplacement correct (-1, 0 ou 1) :");	
		gotoDel(x+1, y);
		purger();
		scanf("%d", &i);		
	}
	px -> deplacement = i;
	
	
	purger();
	gotoDel(x, y);
	printf("Etat Suivant a remplacer");
	gotoDel(x+1, y);
	scanf("%d", &i); 
	px -> etatSuivant = i;
	purger();	
	
}

//Fonction d'affichage du code de Turing en ligne pour une sélection avec la flèche en vue de sa modification 
void affichageCodeModif(tCodeTuring *codeDebut, tCodeTuring *codeFin, int lig, int col){
	tCodeTuring *px;
	int i,a; 

	px=codeDebut->codeSuivant;  
	i=0;
	
	while (i!=27){

		gotoLigCol(lig,col);
		printf("Selectionner la ligne avec les fleches haut et bas");
		
		//On affiche une ligne du code de Turing 
		gotoDel(lig+1,col);
		printf("q%d    ",px -> etatDepart);
        printf("%c    ",px -> valeurCourante);
        printf("%c",px -> nouvelleValeur);
        if(px->deplacement==1){printf(" -> ");}
        else if(px->deplacement==-1){printf(" <- ");}
        else{printf(" - ");}
        printf("q%d",px -> etatSuivant);
        
		gotoLigCol(lig+2,col);
        printf("Appuyer sur \"m\" pour modifier le code de Turing ou Echap pour quitter");

		//On analyse quelle touche est appuyée
	  	i=lireCaract();	
	  	if      (i== 13){} // entree
	  	else if (i==109){gotoLigCol(lig+3,col);ModifCode(codeDebut, codeFin, px,lig+3, col);
		  				gotoLigCol(lig,col);afficheCode(codeDebut, codeFin);} // On entre m pour modifier la ligne affichée du code de Turing (on modifie le code et le réaffiche)
		else if (i==472){if(px->codePrecedent!=codeDebut)px=px->codePrecedent;} // fleche haut, on va au code précedent 
		else if (i==480){if (px->codeSuivant!=codeFin)px=px->codeSuivant;} // fleche bas, on va au code suivant
		else if (i== 27){} 					// touche ESC sortir du programme
		else {   
	   }

		//On efface les lignes de modification du code
	   for (a = 0; a < 5; a++)
	   {
		   gotoDel(lig+a,col);
	   }
	   
	}
}

//Fonction d'exécution du code de Turing
void calcul(tCodeTuring *codeDebut, tCodeTuring *codeFin, tBandeTuring *bandeDebut, tBandeTuring *bandeFin){
	
	int t=0;
	int i = 0;
	tCodeTuring *px;
	tCodeTuring *py;
	px = codeDebut -> codeSuivant;
	//Variable de sauvegarde pour l'état suivant
	int etatSave=px->etatDepart;
	
	teteLecture = bandeDebut -> placeSuivant;
	
	//On récupère la valeur entrée pour le mode d'affichage
	switch(ModeAffichage()){
			
		case 1:
			t=1;
			break;
		
		case 0:
			t=0;
			break;
	}

	//Tant que l'état suivant n'est pas égal à 0
	while(etatSave!=0){
		
		gotoLigCol(6,2 +i);
		printf("^");

		//Si l'état suivant est plus grand que l'état de départ
		//On cherche la valeur suivante après cette valeur
		if(etatSave>=px->etatDepart){

			//Tant que l'état de départ n'est pas égal à l'état suivant
			while(px->etatDepart!=etatSave){
				px=px->codeSuivant;
			}
		}
		//Sinon on cherche l'état suivant à partir du départ
		if(etatSave<px->etatDepart){
			px=codeDebut->codeSuivant;
			while(px->etatDepart!=etatSave){
				px=px->codeSuivant;
			}
		}
		
		//Si la valeur courante est la même que la valeur de pointé sur la bande
		if(teteLecture -> valeur == px -> valeurCourante){
			//On change la valeur de la bande avec la nouvelle valeur
			teteLecture -> valeur = px -> nouvelleValeur;
			//Sauvegarde de l'état suivant
			etatSave=px->etatSuivant;
			
			//On récupère la valeur du déplacement sur la bande
			switch(px->deplacement){
				
				//Si le déplacement est de 1
				case 1:
					//Si on arrive à la fin de la bande (bande infinie)
					if(teteLecture->placeSuivant==bandeFin){
						//On ajoute des 0 à la bande 
						insertionBande(teteLecture);
						teteLecture->placeSuivant->valeur='0';
					}
					//On passe à la valeur suivante de la bande 
					teteLecture = teteLecture -> placeSuivant;
					i++;
					break;
				
				//Si le déplacement est de -1
				case -1:
					//Si on arrive au début de la bande (bande infinie)
					if(teteLecture->placePrecedent==bandeDebut){
						//On ajoute des 0 à la bande 
						insertionBande(teteLecture->placePrecedent);
						teteLecture->placePrecedent->valeur='0';
					}
					//On passe à la valeur précédente de la bande  
					teteLecture = teteLecture -> placePrecedent;
					i--;
					break;
				//Si le déplacement est de 0
				case 0:
					//Ne fait rien
					i = i;
					break;		
			}
			
			//Si la valeur entrée pour l'exécution est 1
			if(t==1){

				//On affiche la bande à chaque étape
				char c;
				gotoDel(2,2);
				printf("Appuyer sur entrer pour passer a l etape suivante");
				while(c = getchar() != '\n'){}
				cadre(4,2,2,140);
				afficheBande(bandeDebut, bandeFin);
			}	
		}
		//Sinon on passe au code suivant
		else{
			px=px->codeSuivant;
		}

		//Si la valeur pour l'exécution est 0, on affiche toute la bande 
		if(t==0){
			gotoDel(2,2);
			afficheBande(bandeDebut, bandeFin);	
		}
	}

	gotoDel(2,2);
	printf("Calcul termine");
}

//Fonction d'affichage du menu de sélection
void menu(tCodeTuring *codeDebut, tCodeTuring *codeFin, tBandeTuring *bandeDebut, tBandeTuring *bandeFin){

	int i= ' ';

	//On affiche le menu après le code de Turing
	gotoLigCol(11 + ligneCodeFin, 2);
	printf("F3 : Modifier le code");
	gotoLigCol(12 + ligneCodeFin, 2);
	printf("F4 : Executer le code");
	gotoLigCol(13 + ligneCodeFin, 2);
	printf("F10 : Quitter");
	
	//Tant qu'on appuie pas sur F10
	while(i!= 568){

		gotoLigCol(11 + ligneCodeFin, 2);
		i=lireCaract();	
		if(i == 13) {}
		else if (i==561){affichageCodeModif(codeDebut, codeFin,15 + ligneCodeFin, 2 );} // F3, modification du code de Turing
		else if (i==562){calcul(codeDebut, codeFin, bandeDebut, bandeFin);} // F4, execution du code de Turing

	}	
}

//Fonction que permet de renter et d'afficher la bande et le code de Turing
void affiche(tCodeTuring *codeDebut, tCodeTuring *codeFin, tBandeTuring *bandeDebut, tBandeTuring *bandeFin){

	//On nettoie la console 
	system("clear");
	//On met en plein écran la console
	HWND hwnd=GetForegroundWindow();
	ShowWindow(hwnd, SW_MAXIMIZE);

	//On crée un grand cadre qui contiendra tous nos éléments
	cadre(0,0,40,150);
	//On crée un petit cadre pour la bande
	cadre(4,2,2,140);

	//On entre la bande dans le cadre
	gotoDel(2, 2);
	creationBande(bandeDebut, bandeFin);

	//On affiche la bande dans le cadre
	gotoDel(2, 2);
	printf("Les termes de la liste : ");
	afficheBande(bandeDebut,bandeFin);

	//On entre le code en dessous du petit cadre
	gotoDel(10,2);
	creationCode(codeDebut, codeFin);

	//On affiche le code en dessous du petit cadre
	gotoDel(10,2);
	afficheCode(codeDebut, codeFin);

	//On affiche le menu
	menu(codeDebut, codeFin, bandeDebut, bandeFin);
}

void main (){

	//Initialisation de la liste doublement chainée pour la bande de Turing
	tBandeTuring *bandeDebut, *bandeFin;
	bandeDebut = (tBandeTuring *)malloc(sizeof(tBandeTuring));
	bandeFin = (tBandeTuring *)malloc(sizeof(tBandeTuring));
	bandeDebut -> placeSuivant = bandeFin;
	
	//Initialisation de la liste doublement chainée pour le code de Turing
	tCodeTuring *codeDebut, *codeFin;
	codeDebut = (tCodeTuring *)malloc(sizeof(tCodeTuring));
	codeFin = (tCodeTuring *)malloc(sizeof(tCodeTuring));
	codeDebut -> codeSuivant = codeFin;		
	
	affiche(codeDebut, codeFin, bandeDebut, bandeFin);
}