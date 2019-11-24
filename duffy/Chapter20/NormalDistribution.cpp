// NormalDistribution.cpp
//

#include "NormalDist.h"

/*#include "float.h"
dd#include "math.h"

#include "assert.h"*/

#include <float.h>
#include <math.h>
#include <assert.h>

//  The finite() function returns a non-zero value if value is neither
//  infinite nor a "not-a-number" (NaN) value, and 0 otherwise.
int _finite(double value);

//  The isnan() function returns a non-zero value if value is
// "not-a-number" (NaN), and 0 otherwise.
int _isnan(double value);

double ErrorFunction(double x){

  // Used by cumulative normal below.
    
  //
  // NOTE: The following copyright notice
  // applies only to the (modified) code of erff.
  //
    
  // erff
  // ====
  //
  // Based on code from the gnu C library, originally written by Sun.
  // Modified to remove reliance on features of gcc and 64-bit width
  // of doubles. No doubt this results in some slight deterioration
  // of efficiency, but this is not really noticeable in testing.
  //

  //
  // ====================================================
  // Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
  //
  // Developed at SunPro, a Sun Microsystems, Inc. business.
  // Permission to use, copy, modify, and distribute this
  // software is freely granted, provided that this notice
  // is preserved.
  // ====================================================
  //
    
  //			       x
  //		        2      |\
  //     erf(x)  =  ---------  | exp(-t*t)dt
  //	 	     sqrt(pi) \|
  //			       0
  //
  //     erfc(x) =  1-erf(x)
  //  Note that
  //		erf(-x) = -erf(x)
  //		erfc(-x) = 2 - erfc(x)
  //
  // Method:
  //	1. For |x| in [0, 0.84375]
  //	    erf(x)  = x + x*R(x^2)
  //          erfc(x) = 1 - erf(x)           if x in [-.84375,0.25]
  //                  = 0.5 + ((0.5-x)-x*R)  if x in [0.25,0.84375]
  //	   where R = P/Q where P is an odd poly of degree 8 and
  //	   Q is an odd poly of degree 10.
  //						 -57.90
  //			| R - (erf(x)-x)/x | <= 2
  //
  //
  //	   Remark. The formula is derived by noting
  //          erf(x) = (2/sqrt(pi))*(x - x^3/3 + x^5/10 - x^7/42 + ....)
  //	   and that
  //          2/sqrt(pi) = 1.128379167095512573896158903121545171688
  //	   is close to one. The interval is chosen because the fix
  //	   point of erf(x) is near 0.6174 (i.e., erf(x)=x when x is
  //	   near 0.6174), and by some experiment, 0.84375 is chosen to
  // 	   guarantee the error is less than one ulp for erf.
  //
  //      2. For |x| in [0.84375,1.25], let s = |x| - 1, and
  //         c = 0.84506291151 rounded to single (24 bits)
  //         	erf(x)  = sign(x) * (c  + P1(s)/Q1(s))
  //         	erfc(x) = (1-c)  - P1(s)/Q1(s) if x > 0
  //			  1+(c+P1(s)/Q1(s))    if x < 0
  //         	|P1/Q1 - (erf(|x|)-c)| <= 2**-59.06
  //	   Remark: here we use the taylor series expansion at x=1.
  //		erf(1+s) = erf(1) + s*Poly(s)
  //			 = 0.845.. + P1(s)/Q1(s)
  //	   That is, we use rational approximation to approximate
  //			erf(1+s) - (c = (single)0.84506291151)
  //	   Note that |P1/Q1|< 0.078 for x in [0.84375,1.25]
  //	   where
  //		P1(s) = degree 6 poly in s
  //		Q1(s) = degree 6 poly in s
  //
  //      3. For x in [1.25,1/0.35(~2.857143)],
  //         	erfc(x) = (1/x)*exp(-x*x-0.5625+R1/S1)
  //         	erf(x)  = 1 - erfc(x)
  //	   where
  //		R1(z) = degree 7 poly in z, (z=1/x^2)
  //		S1(z) = degree 8 poly in z
  //
  //      4. For x in [1/0.35,28]
  //         	erfc(x) = (1/x)*exp(-x*x-0.5625+R2/S2) if x > 0
  //			= 2.0 - (1/x)*exp(-x*x-0.5625+R2/S2) if -6<x<0
  //			= 2.0 - tiny		(if x <= -6)
  //         	erf(x)  = sign(x)*(1.0 - erfc(x)) if x < 6, else
  //         	erf(x)  = sign(x)*(1.0 - tiny)
  //	   where
  //		R2(z) = degree 6 poly in z, (z=1/x^2)
  //		S2(z) = degree 7 poly in z
  //
  //      Note1:
  //	   To compute exp(-x*x-0.5625+R/S), let s be a single
  //	   precision number and s := x; then
  //		-x*x = -s*s + (s-x)*(s+x)
  //	        exp(-x*x-0.5626+R/S) =
  //			exp(-s*s-0.5625)*exp((s-x)*(s+x)+R/S);
  //      Note2:
  //	   Here 4 and 5 make use of the asymptotic series
  //			  exp(-x*x)
  //		erfc(x) ~ ---------- * ( 1 + Poly(1/x^2) )
  //			  x*sqrt(pi)
  //	   We use rational approximation to approximate
  //      	g(s)=f(1/x^2) = log(erfc(x)*x) - x*x + 0.5625
  //	   Here is the error bound for R1/S1 and R2/S2
  //      	|R1/S1 - f(x)|  < 2**(-62.57)
  //      	|R2/S2 - f(x)|  < 2**(-61.52)
  //
  //      5. For inf > x >= 28
  //         	erf(x)  = sign(x) *(1 - tiny)  (raise inexact)
  //         	erfc(x) = tiny*tiny (raise underflow) if x > 0
  //			= 2 - tiny if x<0
  //
  //      7. Special case:
  //         	erf(0)  = 0, erf(inf)  = 1, erf(-inf) = -1,
  //         	erfc(0) = 1, erfc(inf) = 0, erfc(-inf) = 2,
  //	   	erfc/erf(NaN) is NaN
  //

#include <math.h> //DD

  static const double
    tiny	    = 1e-300,
    one =  1.00000000000000000000e+00, /* 0x3FF00000, 0x00000000 */
    /* c = (float)0.84506291151 */
    erx =  8.45062911510467529297e-01, /* 0x3FEB0AC1, 0x60000000 */
    //
    // Coefficients for approximation to  erf on [0,0.84375]
    //
    efx =  1.28379167095512586316e-01, /* 0x3FC06EBA, 0x8214DB69 */
    efx8=  1.02703333676410069053e+00, /* 0x3FF06EBA, 0x8214DB69 */
    pp0  =  1.28379167095512558561e-01, /* 0x3FC06EBA, 0x8214DB68 */
    pp1  = -3.25042107247001499370e-01, /* 0xBFD4CD7D, 0x691CB913 */
    pp2  = -2.84817495755985104766e-02, /* 0xBF9D2A51, 0xDBD7194F */
    pp3  = -5.77027029648944159157e-03, /* 0xBF77A291, 0x236668E4 */
    pp4  = -2.37630166566501626084e-05, /* 0xBEF8EAD6, 0x120016AC */
    qq1  =  3.97917223959155352819e-01, /* 0x3FD97779, 0xCDDADC09 */
    qq2  =  6.50222499887672944485e-02, /* 0x3FB0A54C, 0x5536CEBA */
    qq3  =  5.08130628187576562776e-03, /* 0x3F74D022, 0xC4D36B0F */
    qq4  =  1.32494738004321644526e-04, /* 0x3F215DC9, 0x221C1A10 */
    qq5  = -3.96022827877536812320e-06, /* 0xBED09C43, 0x42A26120 */
    //
    // Coefficients for approximation to  erf  in [0.84375,1.25]
    //
    pa0  = -2.36211856075265944077e-03, /* 0xBF6359B8, 0xBEF77538 */
    pa1  =  4.14856118683748331666e-01, /* 0x3FDA8D00, 0xAD92B34D */
    pa2  = -3.72207876035701323847e-01, /* 0xBFD7D240, 0xFBB8C3F1 */
    pa3  =  3.18346619901161753674e-01, /* 0x3FD45FCA, 0x805120E4 */
    pa4  = -1.10894694282396677476e-01, /* 0xBFBC6398, 0x3D3E28EC */
    pa5  =  3.54783043256182359371e-02, /* 0x3FA22A36, 0x599795EB */
    pa6  = -2.16637559486879084300e-03, /* 0xBF61BF38, 0x0A96073F */
    qa1  =  1.06420880400844228286e-01, /* 0x3FBB3E66, 0x18EEE323 */
    qa2  =  5.40397917702171048937e-01, /* 0x3FE14AF0, 0x92EB6F33 */
    qa3  =  7.18286544141962662868e-02, /* 0x3FB2635C, 0xD99FE9A7 */
    qa4  =  1.26171219808761642112e-01, /* 0x3FC02660, 0xE763351F */
    qa5  =  1.36370839120290507362e-02, /* 0x3F8BEDC2, 0x6B51DD1C */
    qa6  =  1.19844998467991074170e-02, /* 0x3F888B54, 0x5735151D */
    //
    // Coefficients for approximation to  erfc in [1.25,1/0.35]
    //
    ra0  = -9.86494403484714822705e-03, /* 0xBF843412, 0x600D6435 */
    ra1  = -6.93858572707181764372e-01, /* 0xBFE63416, 0xE4BA7360 */
    ra2  = -1.05586262253232909814e+01, /* 0xC0251E04, 0x41B0E726 */
    ra3  = -6.23753324503260060396e+01, /* 0xC04F300A, 0xE4CBA38D */
    ra4  = -1.62396669462573470355e+02, /* 0xC0644CB1, 0x84282266 */
    ra5  = -1.84605092906711035994e+02, /* 0xC067135C, 0xEBCCABB2 */
    ra6  = -8.12874355063065934246e+01, /* 0xC0545265, 0x57E4D2F2 */
    ra7  = -9.81432934416914548592e+00, /* 0xC023A0EF, 0xC69AC25C */
    sa1  =  1.96512716674392571292e+01, /* 0x4033A6B9, 0xBD707687 */
    sa2  =  1.37657754143519042600e+02, /* 0x4061350C, 0x526AE721 */
    sa3  =  4.34565877475229228821e+02, /* 0x407B290D, 0xD58A1A71 */
    sa4  =  6.45387271733267880336e+02, /* 0x40842B19, 0x21EC2868 */
    sa5  =  4.29008140027567833386e+02, /* 0x407AD021, 0x57700314 */
    sa6  =  1.08635005541779435134e+02, /* 0x405B28A3, 0xEE48AE2C */
    sa7  =  6.57024977031928170135e+00, /* 0x401A47EF, 0x8E484A93 */
    sa8  = -6.04244152148580987438e-02, /* 0xBFAEEFF2, 0xEE749A62 */
    //
    // Coefficients for approximation to  erfc in [1/.35,28]
    //
    rb0  = -9.86494292470009928597e-03, /* 0xBF843412, 0x39E86F4A */
    rb1  = -7.99283237680523006574e-01, /* 0xBFE993BA, 0x70C285DE */
    rb2  = -1.77579549177547519889e+01, /* 0xC031C209, 0x555F995A */
    rb3  = -1.60636384855821916062e+02, /* 0xC064145D, 0x43C5ED98 */
    rb4  = -6.37566443368389627722e+02, /* 0xC083EC88, 0x1375F228 */
    rb5  = -1.02509513161107724954e+03, /* 0xC0900461, 0x6A2E5992 */
    rb6  = -4.83519191608651397019e+02, /* 0xC07E384E, 0x9BDC383F */
    sb1  =  3.03380607434824582924e+01, /* 0x403E568B, 0x261D5190 */
    sb2  =  3.25792512996573918826e+02, /* 0x40745CAE, 0x221B9F0A */
    sb3  =  1.53672958608443695994e+03, /* 0x409802EB, 0x189D5118 */
    sb4  =  3.19985821950859553908e+03, /* 0x40A8FFB7, 0x688C246A */
    sb5  =  2.55305040643316442583e+03, /* 0x40A3F219, 0xCEDF3BE6 */
    sb6  =  4.74528541206955367215e+02, /* 0x407DA874, 0xE79FE763 */
    sb7  = -2.24409524465858183362e+01; /* 0xC03670E2, 0x42712D62 */
    
  double R,S,P,Q,s,y,z,r, ax;

  if (!_finite(x)) {
   if (_isnan(x)) 
      return x;
    else
     return   ( x > 0 ? 1 : -1);
  }
    
  ax = fabs(x);

  if(ax < 0.84375) {		/* |x|<0.84375 */
    if(ax < 3.7252902984e-09) { /* |x|<2**-28 */
      if (ax < DBL_MIN*16)
	return 0.125*(8.0*x+efx8*x);  /*avoid underflow */
      return x + efx*x;
    }
    z = x*x;
    r = pp0+z*(pp1+z*(pp2+z*(pp3+z*pp4)));
    s = one+z*(qq1+z*(qq2+z*(qq3+z*(qq4+z*qq5))));
    y = r/s;
    return x + x*y;
  }
  if(ax <1.25) {		/* 0.84375 <= |x| < 1.25 */
    s = ax-one;
    P = pa0+s*(pa1+s*(pa2+s*(pa3+s*(pa4+s*(pa5+s*pa6)))));
    Q = one+s*(qa1+s*(qa2+s*(qa3+s*(qa4+s*(qa5+s*qa6)))));
    if(x>=0) return erx + P/Q; else return -erx - P/Q;
  }
  if (ax >= 6) {		/* inf>|x|>=6 */
    if(x>=0) return one-tiny; else return tiny-one;
  }
    
  /* Starts to lose accuracy when ax~5 */
  s = one/(ax*ax);
    
  if(ax < 2.85714285714285) {	/* |x| < 1/0.35 */
    R=ra0+s*(ra1+s*(ra2+s*(ra3+s*(ra4+s*(
					 ra5+s*(ra6+s*ra7))))));
    S=one+s*(sa1+s*(sa2+s*(sa3+s*(sa4+s*(
					 sa5+s*(sa6+s*(sa7+s*sa8)))))));
  } else {	/* |x| >= 1/0.35 */
    R=rb0+s*(rb1+s*(rb2+s*(rb3+s*(rb4+s*(
					 rb5+s*rb6)))));
    S=one+s*(sb1+s*(sb2+s*(sb3+s*(sb4+s*(
					 sb5+s*(sb6+s*sb7))))));
  }
  r = exp( -ax*ax-0.5625 +R/S);
  if(x>=0) return one-r/ax; else return  r/ax-one;
}

double CumulativeNormal(double z){
  double result;
  result = 0.5 * ( 1 + ErrorFunction( z*ONE_OVER_SQRT_TWO ) ); 
  if (result<=DBL_EPSILON){
    //
    // Asymptotic expansion for very negative z following (26.2.12) on page 408 in
    // M. Abramowitz and A. Stegun, Pocketbook of Mathematical Functions, ISBN 3-87144818-4.
    //
    double sum=1, zsqr=z*z, i=1, g=1, x, y, a=DBL_MAX, lasta;
    do {
      lasta=a;
      x = (4*i-3)/zsqr;
      y = x*((4*i-1)/zsqr);
      a = g*(x-y);
      sum -= a;
      g *= y;
      ++i;
      a = fabs(a);
    } while (lasta>a && a>=fabs(sum*DBL_EPSILON));
    result = -Normal(z)/z*sum;
  }
  return result;
}

// The Inverse cumulative normal distribution function
// by Peter J. Acklam, University of Oslo, Statistics Division.
//
// URL: http://www.math.uio.no/~jacklam/notes/invnorm
//
double InverseCumulativeNormal(double u){

  assert( 0 < u && u < 1 );
    
  // Coefficients for the rational approximation.
  const double
    a1 = -3.969683028665376e+01,
    a2 =  2.209460984245205e+02,
    a3 = -2.759285104469687e+02,
    a4 =  1.383577518672690e+02,
    a5 = -3.066479806614716e+01,
    a6 =  2.506628277459239e+00;
    
  const double
    b1 = -5.447609879822406e+01,
    b2 =  1.615858368580409e+02,
    b3 = -1.556989798598866e+02,
    b4 =  6.680131188771972e+01,
    b5 = -1.328068155288572e+01;
    
  const double
    c1 = -7.784894002430293e-03,
    c2 = -3.223964580411365e-01,
    c3 = -2.400758277161838e+00,
    c4 = -2.549732539343734e+00,
    c5 =  4.374664141464968e+00,
    c6 =  2.938163982698783e+00;
    
  const double
    d1 =  7.784695709041462e-03,
    d2 =  3.224671290700398e-01,
    d3 =  2.445134137142996e+00,
    d4 =  3.754408661907416e+00;
    
  // Limits of the approximation region.
  const double
    u_low   = 0.02425,
    u_high  = 1.0 - u_low;

  register double z, r;

  // Rational approximation for the lower region. ( 0 < u < u_low )
  if( u < u_low ){
    z = sqrt(-2.0*log(u));
    z = (((((c1*z+c2)*z+c3)*z+c4)*z+c5)*z+c6) / ((((d1*z+d2)*z+d3)*z+d4)*z+1.0);
  }
  // Rational approximation for the central region. ( u_low <= u <= u_high )
  else if( u <= u_high ){
    z = u - 0.5;
    r = z*z;
    z = (((((a1*r+a2)*r+a3)*r+a4)*r+a5)*r+a6)*z / (((((b1*r+b2)*r+b3)*r+b4)*r+b5)*r+1.0);
  }
  // Rational approximation for the upper region. ( u_high < u < 1 )
  else {
    z = sqrt(-2.0*log(1.0-u));
    z = -(((((c1*z+c2)*z+c3)*z+c4)*z+c5)*z+c6) /  ((((d1*z+d2)*z+d3)*z+d4)*z+1.0);
  }

//#define REFINE_INVERSECUMULATIVENORMAL_TO_FULL_MACHINE_PRECISION_USING_HALLEYS_METHOD
#ifdef REFINE_INVERSECUMULATIVENORMAL_TO_FULL_MACHINE_PRECISION_USING_HALLEYS_METHOD
  // The relative error of the approximation has absolute value less
  // than 1.15e-9.  One iteration of Halley's rational method (third
  // order) gives full machine precision.

  r = (CumulativeNormal(z) - u) * SQRT_TWO_PI * exp( 0.5 * z * z );	//	f(z)/df(z)
  z -= r/(1+0.5*z*r);							//	Halley's method
#endif

  return z;
}

//
// Example: The following program:
//
//  #include <stdio.h>
//  #include "NormalDistribution.h"
//  int main (long , char *[]) {
//   double x=.335, y = CumulativeNormal(x), z = InverseCumulativeNormal(y);
//   printf("%.16f\n",y);
//   printf("%.16f\n",z);
//  }
//
// produces the following output.:
//
//  0.6311874568912148
//  0.3349999997032685
//
//
// Uncommenting the line
//
//   //#define REFINE_INVERSECUMULATIVENORMAL_TO_FULL_MACHINE_PRECISION_USING_HALLEYS_METHOD
//
// above, and rerunning the program, produces
//
//  0.6311874568912148
//  0.3350000000000000
//

// d1 for Black Scholes formula
double d1(double F, double T, double r, double vv)
{
	return (log(F) + vv*vv/2*T)/(vv*sqrt(T));
}

// d2 for Black Scholes formula
double d2(double F, double T, double r, double vv)
{
	return (log(F) - vv*vv/2*T)/(vv*sqrt(T));
}

double vv(double F1, double F2, double X, double sig1, double sig2, double rho)
{
	return sqrt(sig1 * sig1 + (sig2*F2 / (F2+X))*(sig2*F2 / (F2+X))-2 * rho * sig1 * sig2 * F2/(F2+X));
}

double cnderf(double z)
{
	// DD return (1+ ErrorFunction(z / sqrt(2)))/2;
	return (1.0+ ErrorFunction(z / ::sqrt(2.0)))/2.0;
}