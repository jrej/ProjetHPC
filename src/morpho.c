#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#include "nrdef.h"
#include "nrutil.h"
#include "mymacro.h"


ulong64** createlong64matrix(long brl, long brh, long bcl, long bch){

    long i; 
    long brow=brh-brl+1;
    long bcol=bch-bcl+1;
    long **b;

  /* allocate pointers to rows */
  b=(long **) malloc((size_t)((brow+NR_END)*sizeof(ulong64*)));
  if (!b) strerror("allocation failure 1 in ulong64()");
  b += NR_END;
  b -= brl;

  /* allocate rows and set pointers to them */
  b[brl]=(ulong64 *) malloc((size_t)((brow*bcol+NR_END)*sizeof(ulong64)));

  if (!b[brl]) strerror("allocation failure 2 in ui8matrix()");
  b[brl] += NR_END;
  b[brl] -= bcl;

  for(i=brl+1;i<=brh;i++) b[i]=b[i-1]+bcol;

  /* return pointer to array of pointers to rows */
  return b;


}

char** charmatrix(long nrl, long nrh, long ncl, long nch)
/* -------------------------------------------------- */
/* allocate an char matrix with subscript range m[nrl..nrh][ncl..nch] */
{
  long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
  char **c;

  /* allocate pointers to rows */
  c=(char**) malloc((size_t)((nrow+NR_END)*sizeof(char*)));
  if (!c) strerror("allocation failure 1 in charmatrix()");
  c += NR_END;
  c -= nrl;

  /* allocate rows and set pointers to them */
  c[nrl]=(char*) malloc((size_t)((nrow*ncol+NR_END)*sizeof(char)));
  if (!c[nrl]) strerror("allocation failure 2 in charmatrix()");
  c[nrl] += NR_END;
  c[nrl] -= ncl;

  for(i=nrl+1;i<=nrh;i++) c[i]=c[i-1]+ncol;

  /* return pointer to array of pointers to rows */
  return c;
}





void imageint_to_bin(uint8 **image, ulong64 **image_bin,long nrl,long nrh,long ncl,long nch){

    int i, j ,k;


    uint8 val;
     
    for (i = nrl; i <= nrh; i++){
        k = 0;
        image_bin[i][k] = 0 ;


        for(j = ncl; j <= nch; j++){
           // printf(" image [%d][%d] = %d \n",i,j,image[i][j] );
            val = image[i][j] ;

            if(j % NBBITS == 0 ){
                k++;
                image_bin[i][k] = 0; 
            }
           
            if(image[i][j] == 255){
                image_bin[i][k] |= 1 << ((NBBITS-1)-j%NBBITS);

            }

           // printf(" image binaire [%d][%d] = %ld \n",i,j,image_bin[i][j]);

        }
    }
     
}

void imagebin_to_uint(ulong64 **image_bin,uint8 **imageuint,long nrl,long nrh,long ncl,long nch){

    int i, j ,k;


    uint8 val;
     
    for (i = nrl; i <= nrh; i++){
        
        k = 0;

        for(j = ncl; j <= nch; j++){
            //printf(" image binaire [%d][%d] = %ld \n",i,j,image_bin[i][j]);

            imageuint[i][j] = 0;
            val =  0 ;

            if(j % NBBITS == 0 ){
                k++; 
            }

            val = (image_bin[i][k] >> ((NBBITS-1)-j%NBBITS) ) & 1;

            imageuint[i][j] = (val==1 ? 255:0);

           // printf(" image [%d][%d] = %d \n",i,j,imageuint[i][j] );


        }
    }
     
}
/*
void imageToChar(long **imagebin, char **imagechar, long nrl, long nrh, long ncl, long nch){
    
    int i, j;
    int var,valeur ;
    char one = "1";
    char zero = "0";
    
    for (i = nrl; i <= nrh; i++){
        var = 0;
        for(j = ncl; j <= nch; j++){
            printf(" imagebin [%d][%d] = %ld \n",i,j,imagebin[i][j] );
            printf(" imagechar [%d][%d] = %c \n",i,j,imagechar[i][j] );

            var = j ;

            if(j > NBBITS){

                if(j % NBBITS == 0 ){
               sprintf(imagechar[i][j],one); 
            }
            else{
                sprintf(imagechar[i][j],zero); 
            }


            }


            

            
            printf(" imagechar [%d][%d] = %d \n",i,j,imagechar[i][j] );

        }
    }

}
*/


void imagebinfile(char *nom ,uint8 **image, long nrl, long nrh, long ncl, long nch){

int i,j;
FILE * imagebin;
imagebin = fopen(nom, "w");
fputs(nom,imagebin);
fputs("\n",imagebin);

if(imagebin == NULL){
        
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

for (i = nrl; i <= nrh; ++i){

    for(j = ncl; j <= nch ; j++){

        //printf("%d\n",image[i][j]);

        if(image[i][j] == 0 ){

            fputs("0",imagebin);
        }
        else if(image[i][j] == 255){

            fputs("1",imagebin);
        }
        else{
            fputs("X",imagebin);
        }

    }
}
fclose(imagebin);
}



//algorithme d'erosion 3*3 sur une image pixel pixel noir ou blanc 0 ou 255
void erosion3x3(uint8 **image, uint8 **res_erosion,long nrl,long nrh,long ncl,long nch) {

int i,j;
int k, l;
uint8 res;

i = 1;
j = 1;

 
//erosion
for(i = nrl; i <= nrh; i++){

    for(j = ncl; j <= nch; j++){

        res = 0;
        
        for(k = i - 1 ; k < i + 2 ; k++){

            for(l = j - 1; l < j + 2 ; l++){

                    res |= image[k][l];
                    //printf("res erosion3x3 = %d\n",res );

            }
        }

        res_erosion[i][j] = res;
    }
}

return;
}

void erosion_bin(ulong64 **image_prec,ulong64 **image_suiv, long brl,long brh,long bcl,long bch){
int i,j;
ulong64 res,gauche,droite;
    
    for(i=brl; i<=brh; i++){

        for(j=bcl; j<=bch; j++){

            res = 0;
            res = ~res;
            res &= image_prec[i-1][j] & image_prec[i][j] & image_prec[i+1][j];

            droite = (image_prec[i-1][j+1] & image_prec[i][j+1] & image_prec[i+1][j+1]);
            droite = (res << 1) | (droite >> (NBBITS-1) & 1) ;

            gauche = (image_prec[i-1][j-1] & image_prec[i][j-1] & image_prec[i+1][j-1]);
            gauche = ( (res >> 1) & ~(1<<(NBBITS-1)) ) | (gauche & 1) << (NBBITS-1);

            res &= gauche & droite;

            image_suiv[i][j] = res;
        }
    }
}


//algorithme de dilatation 3*3 sur une image pixel noir ou blanc 0 ou 255
void dilatation3x3(uint8 **image,uint8 **res_dilatation,long nrl,long nrh,long ncl,long nch){

int i,j,k,l;
uint8 res;

//dilatation
    for(i = nrl; i <= nrh; i++){

    for(j = ncl; j <= nch; j++){

        res = 0;

        for(k = i-1 ; k < i+2 ; k++){

            for(l = j-1; l<j+2 ; l++){

                res &= image[k][l];
                printf("res erosion3x3 = %d\n",res );
            }
        }

        res_dilatation[i][j] = res;
    }
}

return;
}

void dilatation_bin(ulong64 **image_prec,ulong64 **image_suiv, long brl,long brh,long bcl,long bch){
int i,j;
ulong64 res,gauche,droite;
    
    for(i=brl; i<=brh; i++){

        for(j=bcl; j<=bch; j++){

            res = 0;
            res = ~res;
            res &= image_prec[i-1][j] | image_prec[i][j] | image_prec[i+1][j];

            droite = (image_prec[i-1][j+1] | image_prec[i][j+1] | image_prec[i+1][j+1]);
            droite = (res << 1) | (droite >> (NBBITS-1) & 1) ;

            gauche = (image_prec[i-1][j-1] | image_prec[i][j-1] | image_prec[i+1][j-1]);
            gauche = ( (res >> 1) & ~(1<<(NBBITS-1)) ) | (gauche & 1) << (NBBITS-1);

            res |= gauche | droite;

            image_suiv[i][j] = res;
        }
    }
}

void morpho(){

long nrl, nrh, ncl, nch;
int seuil = 50 ;
char *nom = "file.txt";
//char *format = "binbin";

uint8 **image;
uint8 **res_dilatation ;
uint8 **res ;
uint8 **imaget;
ulong64 **image_bin;
ulong64 **image_bin_vide;


char **image_char_bin;

long brl = (long) nrl ;
long brh = (long) nrh + 1;
long bcl = (long) ncl ;
long bch = (long) nch + 1;

//initialisation des images

/////////////// Pour le cycle par point////////////
    double cycles;

    char *format = "%6.4f \n";
    double cycleTotal = 0;
    int iter, niter = 2;
    int run, nrun = 5;
    double t0, t1, dt, tmin, t;
///////////////////////////////////////////////



image_bin = createlong64matrix(brl, brh, bcl, bch);

//imagetm1 = LoadPGM_ui8matrix("car3/car_3000.pgm", &nrl, &nrh, &ncl, &nch);
imaget = LoadPGM_ui8matrix("car3/car_3001.pgm", &nrl, &nrh, &ncl, &nch);
res = ui8matrix(nrl,nrh,ncl,nch);


printf("Creation de l'image binaire\n");


////image_vide = ui8matrix(nrl, nrh, ncl, nch);

printf("Creation de int to  binaire\n");
fflush(stdout);        //  Flush the stream.

imageint_to_bin(imaget, image_bin,nrl,nrh,ncl,nch);

printf("Creation de binaire to  uint8\n");
fflush(stdout);        //  Flush the stream.

imagebin_to_uint(image_bin,imaget, nrl,nrh,ncl,nch);

imagebinfile(nom ,imaget,nrl,nrh,ncl,nch);

//SavePGM_ui8matrix(imaget,nrl,nrh,ncl,nch, nom);

/*
erosion3x3(imaget,res,nrl,nrh,ncl,nch);
printf("Lancement 1 dilatation3x3\n");

dilatation3x3(imaget,res,nrl,nrh,ncl,nch);
printf("Lancement 2 dilatation3x3\n");

dilatation3x3(imaget,res,nrl,nrh,ncl,nch);
printf("Lancement erosion3x3\n");

erosion3x3(imaget,res,nrl,nrh,ncl,nch);
printf("DONE\n");
*/

cycleTotal/=NBIMAGE;
cycleTotal/=((nch+1)*(nrh+1));
BENCH(printf("Cycles morpho = "));
BENCH(printf(format, cycleTotal));


//display_ui8matrix (imaget,nrl,nrh,ncl,nch, format, nom);



//imageToChar(image_bin, image_char_bin,nrl,nrh,ncl,nch);

//imagebinfile(nom ,image_char_bin,nrl,nrh,ncl,nch);


return;









 




}