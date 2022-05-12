#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#include "nrdef.h"
#include "nrutil.h"
#include "mymacro.h"

float32* imagetm1;
float32* imaget;
float32* res_erosion ;



//algorithme d'erosion 3*3 sur une image pixel pixel noir ou blanc 0 ou 255
void erosion3x3(uint8 **image_prec, uint8 **image_suiv,long nrl,long nrh,long ncl,long nch) {

int i,j,k,l;
 

// image en format uint 8

uint8 ** image_t = LoadPGM_ui8matrix(imaget, RL,RH,CL,CH);
uint8 ** image_tm1 = LoadPGM_ui8matrix(imagetm1, RL,RH,CL,CH);

// chargement des données de chaque images
for (i = 0; i < NBPIXELI; i++) {
    for(j = 0 ; j < NBPIXELJ; j++)
        copy_f32matrix_ui8matrix (imagetm1, i,i+1, j, j+1, image_prec);
        copy_f32matrix_ui8matrix (imaget, i,i+1, j, j+1, image_suiv);

}

// vecteur 3*3 en ligne

float32* zone1 = f32matrix_map_1D_pitch (image_t, 3,3,3,3,imaget, 0);
float32* zone2 = f32matrix_map_1D_pitch (image_t, 3,3,3,3,imaget, 0);

//erosion

    for(i = nrl; i < nch; i++){

        for(j = ncl; j < nch; j++){

            res_erosion = 255;

            for(k = i-1; k < i+2; k++){

                for(l = j-1; l < j+2; l++){

                    res_erosion = zone1;
                }
            }
        zone2 = res_erosion ;

        }
    }

}

//algorithme de dilatation 3*3 sur une image pixel noir ou blanc 0 ou 255
void dilatation3x3(uint8 **image_prec, uint8 **image_suiv,long nrl,long nrh,long ncl,long nch){

int i,j,k,l;
uint8 res_dilatation ;

// image en format uint 8

uint8 ** image_t = LoadPGM_ui8matrix(imaget, RL,RH,CL,CH);
uint8 ** image_tm1 = LoadPGM_ui8matrix(imagetm1, RL,RH,CL,CH);

// chargement des données de chaque images
for (i = 0; i < NBPIXELI; i++) {
    for(j = 0 ; j < NBPIXELJ; j++)
        copy_f32matrix_ui8matrix (imagetm1, i,i+1, j, j+1, image_prec);
        copy_f32matrix_ui8matrix (imaget, i,i+1, j, j+1, image_suiv);

}

// vecteur 3*3 en ligne

float32* zone1 = f32matrix_map_1D_pitch (image_t, 3,3,3,3,imaget, 0);
float32* zone2 = f32matrix_map_1D_pitch (image_t, 3,3,3,3,imaget, 0);

//dilatation
    for(i = nrl; i < nch; i++){

        for(j = ncl; j < nch; j++){

            res_dilatation = 255;

            for(k = i-1; k < i+2; k++){

                for(l = j-1; l < j+2; l++){

                    res_dilatation = zone1;
                }
            }
        zone2 = res_dilatation;

        }
    }

}
