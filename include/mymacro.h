/* ----------------- */
/* --- mymacro.h --- */
/* ------------------*/

#ifndef __MY_MACRO_H__
#define __MY_MACRO_H__

// activer ou desactiver le define ci-dessous pour passer
// du mode de mise au point au mode benchmark

#define ENABLE_BENCHMARK

//https://sourceforge.net/p/predef/wiki/Architectures/

#ifdef __INTEL_COMPILER
#pragma message("icc compiler")
#include <ia32intrin.h>
#endif

#ifdef __GNUC__
#pragma message("gcc compiler ...")
#include <x86intrin.h>
#endif



// configuration des macro BENCH et DEBUG
#ifdef ENABLE_BENCHMARK
#define BENCH(X) X
#define DEBUG(X)
#else
#define BENCH(X) 
#define DEBUG(X) X
#endif

// configuration de la macro BENCHMARK (depend de l'OS *et* du compilateur
#ifdef ENABLE_BENCHMARK
#ifdef OPENMP
#define DUP10(X) X; X; X; X; X; X; X; X; X; X
#define DUP100(X)  DUP10(X); DUP10(X); DUP10(X); DUP10(X); DUP10(X); DUP10(X); DUP10(X); DUP10(X); DUP10(X); DUP10(X)
#define CHRONO(X,t)  tmin = 1e38; for(run=0; run<nrun; run++) { t0 = (double) dcycle(); DUP100(X); t1 = (double) dcycle(); dt=t1-t0; if(dt<tmin) tmin = dt; } t = tmin / (double) 100
#else
#define CHRONO(X,t)  tmin = 1e38; for(run=0; run<nrun; run++) { t0 = (double) dcycle(); for(iter=0; iter<niter; iter++) { X; } t1 = (double) dcycle(); dt=t1-t0; if(dt<tmin) tmin = dt; } t = tmin / (double) niter
#endif // OPENMP
#else
#define CHRONO(X, t) 
#endif

#define NR_END 1 
#define NBBITS 64
#define NBIMAGE 2
typedef unsigned long ulong64;

#endif // __MY_MACRO_H__


