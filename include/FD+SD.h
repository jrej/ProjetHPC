#ifndef __FD+SG_H__
#define __FD+SG_H__

#pragma message("include FD+SG.h")

#ifdef __cplusplus
#pragma message ("C++")
extern "C" {
#endif


#define NR_END 0
#define FREE_ARG char*
void Frame_difference(uint8 **image_prec, uint8 **image_suiv, uint8 **Et, long nrl,long nrh,long ncl,long nch, int seuil);
void Sigma_delta_step0(uint8 **image_prec, uint8 **image_suiv, uint8 **Et, long nrl,long nrh,long ncl,long nch, int seuil);
void Sigma_delta_step1(uint8 **image_prec, uint8 **image_suiv, uint8 **Et, long nrl,long nrh,long ncl,long nch, int seuil);
void Sigma_delta_step2(uint8 **image_prec, uint8 **image_suiv, uint8 **Et, long nrl,long nrh,long ncl,long nch, int seuil);
void Sigma_delta_step3(uint8 **image_prec, uint8 **image_suiv, uint8 **Et, long nrl,long nrh,long ncl,long nch, int seuil);
void Sigma_delta_step4(uint8 **image_prec, uint8 **image_suiv, uint8 **Et, long nrl,long nrh,long ncl,long nch, int seuil);
#ifdef __cplusplus
}
#endif

#endif
