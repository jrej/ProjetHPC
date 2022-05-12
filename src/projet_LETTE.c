#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#include "nrdef.h"
#include "nrutil.h"
#include "mymacro.h"

//a décrire
#define N 2

//https://hal.inria.fr/hal-01130889/document
#define VMIN 20
#define VMAX 255

uint8** imageFramediff =malloc(sizeof(uint8**));
uint8** imagetm1 = malloc(sizeof(uint8**));
uint8** imaget = malloc(sizeof(uint8**));
uint8** imageMoyenne =malloc(sizeof(uint8**));
float moyenne_t[taille];
float moyenne_tm1[taille];
float variance_t[taille];
float variance_tm1[taille];
int olphot[taille];
int N = 4 ;
int Vmax = 254;
int Vmin = 1;
int estimation = 0;

void Frame_difference(uint8 **image_prec, uint8 **image_suiv, uint8 **Et, long nrl,long nrh,long ncl,long nch, int seuil)){

int i ;
int taille = RH * RL ;

//recuperation nom des Images en variable

char imagetm1 =(char) image_prec;
char Imaget = (char) image_suiv

int olphot[taille];
int esti[taille];

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

void Sigma_delta_step0(uint8 **image_prec, uint8 **image_suiv, uint8 **Et, long nrl,long nrh,long ncl,long nch, int seuil){


//recuperation nom des Images en variable

char nom_imagetm1 =(char) image_prec;
char nom_Imaget = (char) image_suiv;

// image en format uint 8

imaget = LoadPGM_ui8matrix(imagetm1, &nrl, &nrh, &ncl, &nch);
imagetm1 = LoadPGM_ui8matrix(Imaget, &nrl, &nrh, &ncl, &nch);

// chargement des données de chaque images
for (int i = 0; i < NB_IMAGES; i++) {
    imaget->gris[i] = calloc(1, snprintf(NULL, 0, "gris %u", i + 1));
    sprintf(imaget->gris[i], "gris %u", i + 1);
    printf("%s\n", imaget->gris[i]);
}

for (int i = 0; i < NB_IMAGES; i++) {
    imagetm1->gris[i] = calloc(1, snprintf(NULL, 0, "gris %u", i + 1));
    sprintf(imagetm1->gris[i], "gris %u", i + 1);
    printf("%s\n", imagetm1->gris[i]);
}

return ;
}

void Sigma_delta_step1(uint8 **image_prec, uint8 **image_suiv, uint8 **Et, long nrl,long nrh,long ncl,long nch, int seuil){

// chargement des données de chaque images
printf("Moyenne image t\n");
for (int i = 0; i < NB_IMAGES; i++) {
    moyenne_t[i] = imaget->gris[i];
    printf("%s\n", moyenne_t[i]);
}

printf("Moyenne image t-1\n");
for (int i = 0; i < NB_IMAGES; i++) {
   moyenne_tm1[i] = imagetm1->gris[i];
    printf("%s\n", moyenne_tm1[i]);
}

//etape 1 estimation

for(int i = 0; i< taille ; i++){
    if(moyenne_tm1[i] < (image_t->data[i]))
        moyenne_t[i] = moyenne_tm1[i] + 1;
    else if(moyenne_tm1[i] > (image_t->data[i]))
        moyenne_t[i] = moyenne_tm1[i] - 1;
    else
        moyenne_t[i] = moyenne_tm1[i];

    }

return ;
}




void Sigma_delta_step2(uint8 **image_prec, uint8 **image_suiv, uint8 **Et, long nrl,long nrh,long ncl,long nch, int seuil){

//olpho calculus
for(int i = 0 ; i < taille ; i++){
    olphot[i] = abs(moyenne_t[i] - (image1->data[i]));
}
return ;
}



void Sigma_delta_step3(uint8 **image_prec, uint8 **image_suiv, uint8 **Et, long nrl,long nrh,long ncl,long nch, int seuil){

//calcul de difference
// update and clamping
for(int i = 0 ; i < taille ; i++){
    if(variance_tm1 < (N * olphot[i]))
        variance_t[i] = variance_tm1[i]+1;
    else if(variance_tm1 > (N * olphot[i]))
        variance_t[i] = variance_tm1[i]+1;
    else
        variance_t[i] = variance_tm1[i];
    }
return ;
}
void Sigma_delta_step4(uint8 **image_prec, uint8 **image_suiv, uint8 **Et, long nrl,long nrh,long ncl,long nch, int seuil){

//estimation
for(int i = 0 ; i < taille ; i++){
    if (olphot[i] < variance_t[i] )
        estimation = 0;
    else
        estimation = 1;
}

return;
}








