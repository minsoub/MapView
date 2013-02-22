#ifndef _USERMATHUTIL_
#define _USERMATHUTIL_

#include <math.h>
#include <limits>

namespace usermathutils {

	static double Round1(double x, int n)
	{
		int i;
		// 자릿수맞춤
		for ( i = 0; i < n; ++i ) x *= 10;
		if ( x - (int)x >= 0.5 )
			x = ceil(x); // 소수점이하부분이0.5보다크거나같으면올림
		else
			x = floor(x);// 작으면버림
		// 자릿수복구
		for ( i = 0; i < n; ++i ) x /= 10;
		return x;
	}

	static double tenpow (int n)
	{
		double y = 10.0;
		while (--n > 0)
			y *= 10.0;
		return y;
	}
	/** 64-bit double precision ~ 15 digits. */
	static int nMax = std::numeric_limits<int>::max();

	/** Round off with Banker's method, n in -15..15 */
	static double Round (double x, int n)
	{
  bool neg = (x < 0.0);
  double ipart, fpart;
  double y, p;
  int id;
  if (neg)
    x = -x;
  if (n > 0)
    {
      double yy;
      fpart = modf (x, &ipart);
      if (n > nMax)
	n = nMax;
      p = tenpow (n);
      y = fpart * p;
      fpart = modf (y, &yy);
      if (fpart < 0.5)
	fpart = 0.0;
      else if (fpart > 0.5)
	fpart = 1.0;
      else
	{			/* Banker's Method */
	  id = (int) fmod (yy, 10.0);
	  fpart = (id & 1) ? 1.0 : 0.0;
	}
      yy += fpart;
      y = ipart + yy / p;
    }
  else if (n < 0)
    {
      if (n < nMax)
	n = -nMax;
      p = tenpow (-n);
      y = x / p;
      y = Round (y, 0) * p;
    }
  else
    {				/* n == 0 */
      fpart = modf (x, &ipart);
      if (fpart > 0.5)
	ipart += 1.0;
      else if (fpart < 0.5)
	;
      else
	{			/* Banker's Method */
	  id = (int) fmod (ipart, 10.0);
	  if ((id & 1) != 0)
	    ipart += 1.0;
	}
      y = ipart;
    }
  return neg ? -y : y;
}

/** Symmetric arithmetic rounding, n in -15..15 */
	static double round (double x, int n)
{
  bool neg = (x < 0.0);
  double ipart, fpart;
  double y, p;
  if (neg)
    x = -x;
  if (n > 0)
    {
      double yy;
      fpart = modf (x, &ipart);
      if (n > nMax)
	n = nMax;
      p = tenpow (n);
      y = fpart * p;
      fpart = modf (y, &yy);
      if (fpart < 0.5)
	yy += 1.0;
      y = ipart + yy / p;
    }
  else if (n < 0)
    {
      if (n < -nMax)
	n = -nMax;
      p = tenpow (-n);
      y = x / p;
      y = round (y, 0) * p;
    }
  else
    {				/* n == 0 */
      fpart = modf (x, &ipart);
      y = (fpart < 0.5) ? ipart : ipart + 1;
    }
  return neg ? -y : y;
}
#ifdef mod
#undef mod
#endif

	static double mod(const double y,const double x)
	{
		return (y-(x*floor(y/x)));
	}

} //end of namespace
#endif
