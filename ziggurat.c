/*

 Marsaglia, G., & Tsang, W. W. (2000). The Ziggurat Method for
 Generating Random Variables. Journal of Statistical Software,
 5(8), 1–7. https://doi.org/10.18637/jss.v005.i08

 */
#include "mt19937ar.h"

#include <stdint.h>
#include <math.h>

#define RUNI (genrand_real3())
#define IUNI (genrand_int32())

static uint32_t kn[128];
static float wn[128], fn[128];

float ziggurat_gaussian(void)
{
  const float r = 3.442620f;     /* The start of the right tail */
  static float x, y;
  static uint32_t iz;
  static int32_t hz;
  
  hz=IUNI;
  iz=hz&127;
  while (fabs(hz) >= kn[iz]) {
    
    x=hz*wn[iz];      /* iz==0, handles the base strip */
    if (iz==0) {
      do {
	x=-log(RUNI)*0.2904764; y=-log(RUNI);
      } while(y+y<x*x);/* .2904764 is 1/r */
      return (hz>0)? r+x : -r-x;
    }
    /* iz>0, handle the wedges of other strips */
    if( fn[iz]+RUNI*(fn[iz-1]-fn[iz]) < exp(-.5*x*x) ) return x;

    /* initiate, try to exit for(;;) for loop*/
    hz=IUNI;
    iz=hz&127;
  }
  return hz*wn[iz];
}

void ziggurat_gaussian_set(void)
{
  const double m1 = 2147483648.0;
  double dn=3.442619855899,tn=dn,vn=9.91256303526217e-3, q;
  int i;

  q=vn/exp(-.5*dn*dn);
  kn[0]=(dn/q)*m1;
  kn[1]=0;

  wn[0]=q/m1;
  wn[127]=dn/m1;

  fn[0]=1.;
  fn[127]=exp(-.5*dn*dn);

  for (i=126;i>=1;i--) {
    dn=sqrt(-2.*log(vn/dn+exp(-.5*dn*dn)));
    kn[i+1]=(dn/tn)*m1;
    tn=dn;
    fn[i]=exp(-.5*dn*dn);
    wn[i]=dn/m1;
  }
}
