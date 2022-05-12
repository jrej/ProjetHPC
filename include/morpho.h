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
void erosion3x3(uint8 **image_prec, uint8 **image_suiv,long nrl,long nrh,long ncl,long nch);

//algorithme de dilatation 3*3 sur une image pixel noir ou blanc 0 ou 255
void dilatation3x3(uint8 **image_prec, uint8 **image_suiv,long nrl,long nrh,long ncl,long nch);
