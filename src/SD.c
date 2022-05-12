#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "nrdef.h"
#include "nrutil.h"
#include "mymacro.h"

// variables globales

char nom_imagetm1;
char nom_imaget ;

uint8** moyenne_t;
uint8** moyenne_tm1;
uint8** imagetm1;
uint8** imaget;
uint8** image_vide;
uint8** imageMoyenne;
uint8** variance_t;
uint8** variance_tm1;
uint8** variance;

int NN = 4 ;
int Vmax = 255;
int Vmin = 1;
int estimation = 0;
int olphot;



/*

void Frame_difference(uint8 **image_prec, uint8 **image_suiv, long nrl,long nrh,long ncl,long nch, int seuil){

int i ;
int taille = nch * nrh ;

//variables
int olphot[taille];
int esti[taille];

//chargement images
image_t = LoadPGM_ui8matrix(imagetm1, &nrl, &nrh, &ncl, &nch);
image_tm1 = LoadPGM_ui8matrix(imagetm1, &nrl, &nrh, &ncl, &nch);

    for(i = 0; i< taille ; i++){
        olphot[i] = abs(image_t - image_tm1);
    }
    for (i = 0; i < taille ; i++){
        if (olphot[i] < seuil)
            esti[i] = 0;
        else
            esti[i] = 1 ;
    }



}
*/

void Sigma_delta_step0(uint8 **image_prec, uint8 **image_suiv,uint8 **image_vide,
 long nrl,long nrh,long ncl,long nch){

int i,j;
for (i = nrl; i < nrh; i++) {
    for(j = ncl ; j < nch; j++)
        image_prec[i][j] = image_suiv[i][j];
        image_vide[i][j] = Vmin;
    

}
printf("Sigma_delta_step0 DONE\n");


return ;

}


void Sigma_delta_step1(uint8 **image_prec, uint8 **image_suiv,uint8 **image_vide, long nrl,long nrh,long ncl,long nch){

int i, j ;
        
//etape 1 estimation

for(i = nrl; i <= nrh ; i++){

    for(j = ncl; j <= nrh; j++){
     

        if((imageMoyenne[i][j]) < (imagetm1[i][j]))

            imageMoyenne[i][j] = (uint8)((image_prec[i][j] + image_suiv[i][j])/2) + 1 ;

        else if((imageMoyenne[i][j]) > (imaget[i][j]))
            imageMoyenne[i][j] = (uint8)((image_prec[i][j] + image_suiv[i][j])/2) - 1 ;
        else
            imageMoyenne[i][j] = imageMoyenne[i][j];

       


    }

    
}
printf("Sigma_delta_step1 DONE\n");

return ;
}





void Sigma_delta_step2(uint8 **image_prec, uint8 **image_suiv,uint8 **image_vide, long nrl,long nrh,long ncl,long nch){
int i,j;


//olpho calculus

    

printf("i =%d\n  j =%d\n",i,j );
printf("olpho %d \n",olphot);
printf(" imageprec [%d][%d] = %d \n",i,j,imagetm1[i][j] );
printf(" imagsuiv [%d][%d] = %d \n",i,j,imaget[i][j] );
olphot = abs((imageMoyenne[i][j]) - (image_prec[i][j]));
   


printf("Sigma_delta_step2 DONE\n");

return ;
}



void Sigma_delta_step3(uint8 **image_prec, uint8 **image_suiv,uint8 **image_vide, long nrl,long nrh,long ncl,long nch){

//calcul de difference
int i,j;

// update and clamping
    for(i = nrl ; i <= nrh ; i++){

        for(j = ncl; j <= nch;j++){

            if((variance_tm1[i][j]) < (NN * olphot))
                variance_t[i][j] = variance_tm1[i][j]+1;

            else if((variance_tm1[i][j]) > (NN * olphot))
                variance_t[i][j] = variance_tm1[i][j]+1;

            else
                variance_t[i][j] = variance_tm1[i][j];

        }
    }

return ;

}


void Sigma_delta_step4(uint8 **image_prec, uint8 **image_suiv,uint8 **image_vide, long nrl,long nrh,long ncl,long nch){
int i,j;
//estimation

for(i = nrl ; i <= nrh  ; i++){
    for (j = ncl; i <= nrh; ++i){
        if (olphot <= variance[i][j] )
            estimation = 0;
        else
            estimation = 1;
    }
}

return;
}


void Sigma_delta(){

/////////////// Pour le cycle par point////////////
    double cycles;

    char *format = "%6.4f \n";
    double cycleTotal = 0;
    int iter, niter = 2;
    int run, nrun = 5;
    double t0, t1, dt, tmin, t;
///////////////////////////////////////////////

long nrl, nrh, ncl, nch;
int seuil = 50 ;




//initialisation des images
imagetm1 = LoadPGM_ui8matrix("car3/car_3000.pgm", &nrl, &nrh, &ncl, &nch);
imaget = LoadPGM_ui8matrix("car3/car_3001.pgm", &nrl, &nrh, &ncl, &nch);
image_vide = ui8matrix(nrl, nrh, ncl, nch);
olphot = 10 ;
imageMoyenne = ui8matrix(nrl, nrh, ncl, nch);
variance_t = ui8matrix(nrl, nrh, ncl, nch);;
variance_tm1 = ui8matrix(nrl, nrh, ncl, nch);;
variance = ui8matrix(nrl, nrh, ncl, nch);;

printf("Lancement Sigma_delta_step0\n ");
fflush(stdout);        //  Flush the stream.

Sigma_delta_step0(imagetm1,imaget,image_vide,nrl,nrh,ncl,nch);

printf("Lancement Sigma_delta_step1\n ");
fflush(stdout);        //  Flush the stream.

Sigma_delta_step1(imagetm1,imaget,imageMoyenne,nrl,nrh,ncl,nch);

printf("Lancement Sigma_delta_step2\n ");
fflush(stdout);        //  Flush the stream.

Sigma_delta_step2(imagetm1,imaget,image_vide,nrl,nrh,ncl,nch);

printf("Lancement Sigma_delta_step3\n ");
fflush(stdout);        //  Flush the stream.

Sigma_delta_step3(imagetm1,imaget,image_vide,nrl,nrh,ncl,nch);

printf("Lancement Sigma_delta_step4\n ");
fflush(stdout);        //  Flush the stream.
Sigma_delta_step4(imagetm1,imaget,image_vide,nrl,nrh,ncl,nch);

cycleTotal/=NBIMAGE;
cycleTotal/=((nch+1)*(nrh+1));
BENCH(printf("Cycles SD = "));
BENCH(printf(format, cycleTotal));


}





