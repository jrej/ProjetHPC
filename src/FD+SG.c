#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#include "nrdef.h"
#include "nrutil.h"
#include "mymacro.h"

//a décrire
#define NN 2

//https://hal.inria.fr/hal-01130889/document
#define VMIN 20
#define VMAX 255

// variables globales

char* nom_imagetm1;
char* nom_imaget ;


float32* moyenne_t;
float32* moyenne_tm1;
float32* imagetm1;
float32* imaget;
float32* imageMoyenne;

int N = 4 ;
int Vmax = 254;
int Vmin = 1;
int estimation = 0;
int olphot[TAILLE_VECTOR];


/*
void Frame_difference(uint8 **image_prec, uint8 **image_suiv, long nrl,long nrh,long ncl,long nch, int seuil){

int i ;
int taille = RH * RL ;

//recuperation nom des Images en variable

char imagetm1 =(char) image_prec;
char Imaget = (char) image_suiv

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

void Sigma_delta_step0(uint8 **image_prec, uint8 **image_suiv, long nrl,long nrh,long ncl,long nch, int seuil){

int i,j;

// image en format uint 8

uint8 ** image_t = LoadPGM_ui8matrix(imaget, &nrl, &nrh, &ncl, &nch);
uint8 ** image_tm1 = LoadPGM_ui8matrix(imagetm1, &nrl, &nrh, &ncl, &nch);

// chargement des données de chaque images
for (i = 0; i < NBPIXELI; i++) {
    for(j = 0 ; j < NBPIXELJ; j++)
        copy_f32matrix_ui8matrix (imagetm1, i,i+1, j, j+1, image_prec);
        copy_f32matrix_ui8matrix (imaget, i,i+1, j, j+1, image_suiv);

}

return ;
}

void Sigma_delta_step1(uint8 **image_prec, uint8 **image_suiv, long nrl,long nrh,long ncl,long nch, int seuil){

imagetm1 = f32vector(RL,RH);
imaget = f32vector(RL,RH);

imageMoyenne = f32vector(RL,RH);

//etape 1 estimation

for(int i = 0; i < TAILLE_VECTOR ; i++){
    if((imageMoyenne) < (imagetm1))
        moyenne_t = moyenne_tm1 + 1;
    else if((moyenne_tm1) > (imaget))
        moyenne_t = moyenne_tm1 - 1;
    else
        moyenne_t = moyenne_tm1;

    //moyenne de chaque pixel des 2 tableaux
    imageMoyenne = ( add( &moyenne_tm1 , &moyenne_t ) / 2); 
    imaget = imaget + i;
    imagetm1 = imagetm1 + i;

    }

return ;
}




void Sigma_delta_step2(uint8 **image_prec, uint8 **image_suiv, uint8 **Et, long nrl,long nrh,long ncl,long nch, int seuil){


imaget = f32vector(RL,RH);

//olpho calculus
for(int i = 0 ; i < TAILLE_VECTOR ; i++){
    olphot[i] = abs((imageMoyenne[i]) - (imaget[i]));
}
return ;
}



void Sigma_delta_step3(uint8 **image_prec, uint8 **image_suiv, uint8 **Et, long nrl,long nrh,long ncl,long nch, int seuil){

//calcul de difference

float variance_t[TAILLE_VECTOR];
float variance_tm1[TAILLE_VECTOR];

// update and clamping
for(int i = 0 ; i < TAILLE_VECTOR ; i++){
    if((variance_tm1[i]) < (NN * olphot[i]))
        variance_t[i] = variance_tm1[i]+1;
    else if((variance_tm1) > (NN * olphot[i]))
        variance_t[i] = variance_tm1[i]+1;
    else
        variance_t[i] = variance_tm1[i];
    }
return ;
}
void Sigma_delta_step4(uint8 **image_prec, uint8 **image_suiv, uint8 **Et, long nrl,long nrh,long ncl,long nch, int seuil){

float variance[TAILLE_VECTOR];
//estimation

for(int i = 0 ; i < TAILLE_VECTOR  ; i++){
    if (olphot[i] < variance[i] )
        estimation = 0;
    else
        estimation = 1;
}

return;
}








