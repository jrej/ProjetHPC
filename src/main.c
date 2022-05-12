/*
main.c par LETTE Gregory projet HPC
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> 
#include <mymacro.h>
#include <mouvement.h>


int main(void){

	//printf("main projet  chargement des variables\n");

	int i ,j, k;
	long nrl, nrh, ncl, nch;
	char nom_image1[100];
	char nom_image2[100];
	char nom_image_vide[100];

   /* FILE *fichier;
    fichier = fopen("sort_pgm.txt","r");
    if(fichier == NULL){
        printf("ERROR FICHER\n");
        return;

    }*/
    //chargement premiere image car/3000 pour initiliser la bibliotheque nrutil.c
    //printf("chargement des variables format uint8 format NRC\n");

    uint8 **image_prec = LoadPGM_ui8matrix("car3/car_3000.pgm", &nrl, &nrh, &ncl, &nch);
    uint8 **image_suiv =  ui8matrix(nrl, nrh, ncl, nch);
    uint8 **image_vide = ui8matrix(nrl, nrh, ncl, nch);

	
	sprintf(nom_image1,"car3/car_3000.pgm");
	sprintf(nom_image2,"car3/car_3001.pgm");


	MLoadPGM_ui8matrix(nom_image1, nrl, nrh, ncl, nch, image_prec);
    MLoadPGM_ui8matrix(nom_image2, nrl, nrh, ncl, nch, image_suiv);
	//MLoadPGM_ui8matrix(nom_image_vide, nrl, nrh, ncl, nch, image_vide);

    //printf("lancement fonction mouvemnt entre 2 images\n");
	mouvement(image_prec,image_suiv);



    return 0;

}



















/*
int i =0;
DIR *dossier;



//ouverture fichier avec nom dans le dossier car3
FILE * fichier_txt;
//struct dirent *dir;
char *dos_image[NBIMAGES];
char * nom_fichier = "sort_pgm.txt";
//dossier = opendir("car3");



   // if (dossier) {

if(fichier_txt = fopen(nom_fichier, "r")){
    printf("OUVERTURE FICHIER %s\n", nom_fichier );
}
else {
    printf("ERREUR OUVERTURE %s\n", nom_fichier);
}

while(i<NBIMAGES){


    printf("DEBUT DE BOUCLE\n");

    fgets(dos_image[i],NBIMAGES,fichier_txt);

    printf(" TEST  Sort ::::: %s\n",dos_image[i]);
    i++;

        }       
     /*   while ((dir = readdir(dossier)) != NULL) {
            
            //mise image dans du fichier le dossier
            if (i < NBIMAGES){
                dos_image[i] = dir ;
                i++;
            }



            printf("TEST image dossier %s", dir->d_name);
        }
    }
    
for (i = 1; i < NBIMAGES; ++i)
{
  mouvement(dos_image[i-1],dos_image[i],RL,RH,CL,CH) ; 
}


    fclose(fichier_txt);
*/





