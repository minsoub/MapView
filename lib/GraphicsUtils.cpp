/*
 * GraphicsUtils.cpp
 *
 *  Created on: 2012. 2. 15.
 *      Author: HIST002
 */
#include <math.h>
#include "GraphicsUtils.h"

namespace GuHanLibs
{
#define DONT_INTERSECT	0
#define DO_INTERSECT	1
#define COLLINEAR		2

/**************************************************************
 *                                                            *
 *    NOTE:  The following macro to determine if two numbers  *
 *    have the same sign, is for 2's complement number        *
 *    representation.  It will need to be modified for other  *
 *    number systems.                                         *
 *                                                            *
 **************************************************************/

#define SAME_SIGNS( a, b )	\
		(((long) ((unsigned long) a ^ (unsigned long) b)) >= 0 )

int lines_intersect( long x1, long y1,   /* First line segment */
		     long x2,long  y2,

		     long x3,long  y3,   /* Second line segment */
		     long x4, long y4,

		     long *x,
		     long *y         /* Output value:
		                * point of intersection */
               )
//long
//    x1, y1, x2, y2, x3, y3, x4, y4,
//    *x, *y;
{
    long a1, a2, b1, b2, c1, c2; /* Coefficients of line eqns. */
    long r1, r2, r3, r4;         /* 'Sign' values */
    long denom, offset, num;     /* Intermediate values */

    /* Compute a1, b1, c1, where line joining points 1 and 2
     * is "a1 x  +  b1 y  +  c1  =  0".
     */

    a1 = y2 - y1;
    b1 = x1 - x2;
    c1 = x2 * y1 - x1 * y2;

    /* Compute r3 and r4.
     */


    r3 = a1 * x3 + b1 * y3 + c1;
    r4 = a1 * x4 + b1 * y4 + c1;

    /* Check signs of r3 and r4.  If both point 3 and point 4 lie on
     * same side of line 1, the line segments do not intersect.
     */

    if ( r3 != 0 &&
         r4 != 0 &&
         SAME_SIGNS( r3, r4 ))
        return ( DONT_INTERSECT );

    /* Compute a2, b2, c2 */

    a2 = y4 - y3;
    b2 = x3 - x4;
    c2 = x4 * y3 - x3 * y4;

    /* Compute r1 and r2 */

    r1 = a2 * x1 + b2 * y1 + c2;
    r2 = a2 * x2 + b2 * y2 + c2;

    /* Check signs of r1 and r2.  If both point 1 and point 2 lie
     * on same side of second line segment, the line segments do
     * not intersect.
     */

    if ( r1 != 0 &&
         r2 != 0 &&
         SAME_SIGNS( r1, r2 ))
        return ( DONT_INTERSECT );

    /* Line segments intersect: compute intersection point.
     */

    denom = a1 * b2 - a2 * b1;
    if ( denom == 0 )
        return ( COLLINEAR );
    offset = denom < 0 ? - denom / 2 : denom / 2;

    /* The denom/2 is to get rounding instead of truncating.  It
     * is added or subtracted to the numerator, depending upon the
     * sign of the numerator.
     */

    num = b1 * c2 - b2 * c1;
    *x = ( num < 0 ? num - offset : num + offset ) / denom;

    num = a2 * c1 - a1 * c2;
    *y = ( num < 0 ? num - offset : num + offset ) / denom;

    return ( DO_INTERSECT );
   } /* lines_intersect */
}//end of namespace


double GraphicsUtils::distance(QPoint p1,QPoint p2)
{
	return sqrt((p1.x()-p2.x())*(p1.x()-p2.x())+ (p1.y()-p2.y())*(p1.y()-p2.y()));
}
bool GraphicsUtils::isInsideCircle(QPoint center,int radius,QPoint p)
{
	int d = (int)distance(center,p);
	return (d<radius);
}
bool GraphicsUtils::isDrawable(const QRect& screenRect,const QRect& r2)
{
	if(	r2.bottom() < screenRect.top() ||
		r2.top() > screenRect.bottom() ||
		r2.left() > screenRect.right() ||
		r2.right() < screenRect.left() ) return false;
	return true;
}
bool GraphicsUtils::isIntersect(const QRect& screenRect,const QPoint& p1,const QPoint& p2)
{
	//사각형을 이루는 4개의 선분을 모두 체크한다
	long x1,y1,x2,y2;
	long x3,y3,x4,y4;
	long x,y;
	int check;

	x3 = p1.x(); y3 = p1.y();
	x4 = p2.x(); y4 = p2.y();

	x1 = screenRect.x(); y1 = screenRect.y(); x2 = screenRect.width(); y2 = 0;
	check = GuHanLibs::lines_intersect(x1,y1,x2,y2,x3,y3,x4,y4,&x,&y);
	if(check == 1) return true;

	x1 = screenRect.width(); y1 = 0; x2 = x1; y2 = screenRect.height();
	check = GuHanLibs::lines_intersect(x1,y1,x2,y2,x3,y3,x4,y4,&x,&y);
	if(check == 1) return true;

	x1 = screenRect.width(); y1 = screenRect.height(); x2 = 0; y2 = screenRect.height();
	check = GuHanLibs::lines_intersect(x1,y1,x2,y2,x3,y3,x4,y4,&x,&y);
	if(check == 1) return true;

	x1 = 0; y1 = screenRect.height(); x2 = 0; y2=0;
	check = GuHanLibs::lines_intersect(x1,y1,x2,y2,x3,y3,x4,y4,&x,&y);
	if(check == 1) return true;

	return false;
}

void GraphicsUtils::DistanceFromLine(double cx, double cy, double ax, double ay ,
					  double bx, double by, double &distanceSegment,
					  double &distanceLine)
{

	//
	// find the distance from the point (cx,cy) to the line
	// determined by the points (ax,ay) and (bx,by)
	//
	// distanceSegment = distance from the point to the line segment
	// distanceLine = distance from the point to the line (assuming
	//					infinite extent in both directions
	//

/*

Subject 1.02: How do I find the distance from a point to a line?


    Let the point be C (Cx,Cy) and the line be AB (Ax,Ay) to (Bx,By).
    Let P be the point of perpendicular projection of C on AB.  The parameter
    r, which indicates P's position along AB, is computed by the dot product
    of AC and AB divided by the square of the length of AB:

    (1)     AC dot AB
        r = ---------
            ||AB||^2

    r has the following meaning:

        r=0      P = A
        r=1      P = B
        r<0      P is on the backward extension of AB
        r>1      P is on the forward extension of AB
        0<r<1    P is interior to AB

    The length of a line segment in d dimensions, AB is computed by:

        L = sqrt( (Bx-Ax)^2 + (By-Ay)^2 + ... + (Bd-Ad)^2)

    so in 2D:

        L = sqrt( (Bx-Ax)^2 + (By-Ay)^2 )

    and the dot product of two vectors in d dimensions, U dot V is computed:

        D = (Ux * Vx) + (Uy * Vy) + ... + (Ud * Vd)

    so in 2D:

        D = (Ux * Vx) + (Uy * Vy)

    So (1) expands to:

            (Cx-Ax)(Bx-Ax) + (Cy-Ay)(By-Ay)
        r = -------------------------------
                          L^2

    The point P can then be found:

        Px = Ax + r(Bx-Ax)
        Py = Ay + r(By-Ay)

    And the distance from A to P = r*L.

    Use another parameter s to indicate the location along PC, with the
    following meaning:
           s<0      C is left of AB
           s>0      C is right of AB
           s=0      C is on AB

    Compute s as follows:

            (Ay-Cy)(Bx-Ax)-(Ax-Cx)(By-Ay)
        s = -----------------------------
                        L^2

    Then the distance from C to P = |s|*L.

*/
	double r_numerator = (cx-ax)*(bx-ax) + (cy-ay)*(by-ay);
	double r_denomenator = (bx-ax)*(bx-ax) + (by-ay)*(by-ay);
	double r = r_numerator / r_denomenator;
//
    double px = ax + r*(bx-ax);
    double py = ay + r*(by-ay);
//
	double s =  ((ay-cy)*(bx-ax)-(ax-cx)*(by-ay) ) / r_denomenator;
	distanceLine = fabs(s)*sqrt(r_denomenator);
//
// (xx,yy) is the point on the lineSegment closest to (cx,cy)
//
	double xx = px;
	double yy = py;
	if ( (r >= 0) && (r <= 1) )
	{
		distanceSegment = distanceLine;
	}
	else
	{
		double dist1 = (cx-ax)*(cx-ax) + (cy-ay)*(cy-ay);
		double dist2 = (cx-bx)*(cx-bx) + (cy-by)*(cy-by);
		if (dist1 < dist2)
		{
			xx = ax;
			yy = ay;
			distanceSegment = sqrt(dist1);
		}
		else
		{
			xx = bx;
			yy = by;
			distanceSegment = sqrt(dist2);
		}
	}
	return;
}
//ex,ey : ellipse center
//w : width,h :height
//px,py : test point
bool GraphicsUtils::isInsideEllipse(int ex,int ey,int w,int h,int px,int py) {
    //Determine and normalize quadrant.
    int dx = abs(ex-px);
    int dy = abs(ey-py);
    //double l;

    //Shortcut
    if( dx > w/2 || dy > h/2 ) {
      return false;
    }
	double ea = w/2;
	double eb = h/2;
    //Calculate the semi-latus rectum of the ellipse at the given point
    //l = sqrt( (double)((1-((dx^2)/(w^2))) * (h^2)) );
    //return dy < l;
	return(dx*dx)/(ea*ea) + (dy*dy)/(eb*eb) <= 1;
}
int  GraphicsUtils::DistanceFromLine(const QPoint& p1, const QPoint& p2, const QPoint& mouseP)
{
	double cx,cy,ax,ay,bx,by,d1,d2;
	cx = mouseP.x(); cy = mouseP.y();
	ax = p1.x(); ay = p1.y();
	bx = p2.x(); by = p2.y();

	DistanceFromLine(cx,cy,ax,ay,bx,by,d1,d2);
	return (int)floor(d1);
}
bool GraphicsUtils::isPickLine(const QRect& rect,const QPoint& mouseP)
{
	QPoint p1 = rect.topLeft();
	QPoint p2 = rect.bottomRight();

	double cx,cy,ax,ay,bx,by,d1,d2;
	cx = mouseP.x(); cy = mouseP.y();
	ax = p1.x(); ay = p1.y();
	bx = p2.x(); by = p2.y();
	DistanceFromLine(cx,cy,ax,ay,bx,by,d1,d2);
	if(d1 <= 2) return true;
	return false;
}
bool GraphicsUtils::isPickCircle(const QRect& rect,const QPoint& mouseP)
{
	int r = rect.width() / 2;
	return isInsideCircle(rect.center(),r,mouseP);
}
bool GraphicsUtils::isPickEllipse(const QRect& rect,const QPoint& mouseP)
{
	//bool isInsideEllipse(int ex,int ey,int w,int h,int px,int py) ;
	QPoint center = rect.center();
	int ex = center.x();
	int ey = center.y();
	int w = rect.width();
	int h = rect.height();
	int px = mouseP.x();
	int py = mouseP.y();
	return isInsideEllipse(ex,ey,w,h,px,py) ;

}
bool GraphicsUtils::isPickText(const QRect& rect,const QPoint& mouseP)
{
	return isPickRect(rect,mouseP);
}
bool GraphicsUtils::isPickRect(const QRect& rect,const QPoint& mouseP)
{
	return rect.contains(mouseP);
}
bool GraphicsUtils::isPickArc(const QRect& rect,const QPoint& mouseP)
{
	return rect.contains(mouseP);
}
bool GraphicsUtils::isPickPolygon(const QVector<QPoint>& dataxy,const QPoint& mouseP)
{

  int i, j=dataxy.count()-1 ;
  bool  oddNodes=false      ;
  int x = mouseP.x();
  int y = mouseP.y();
  for (i=0; i<dataxy.count(); i++) {
  	if (((dataxy[i].y()<y) && (dataxy[j].y()>=y)) ||
	    ((dataxy[j].y()<y) && (dataxy[i].y()>=y))){
		if(dataxy[i].x() + (y-dataxy[i].y()) / (dataxy[j].y()-dataxy[i].y())* (dataxy[j].x()-dataxy[i].x()) < x){
			oddNodes = !oddNodes;
		}
	}
    j=i;
   }

  return oddNodes;
}
bool GraphicsUtils::isPickPolyline(const QVector<QPoint>& dataxy,const QPoint& mouseP)
{
	if(dataxy.count() < 2) return false;
	QPoint p1,p2;
	p1 = dataxy[0];
	for(int i=1;i< dataxy.count();i++){
		p2 = dataxy[i];
		int d = DistanceFromLine(p1,p2,mouseP);
		if(d < 2){
			return true;
		}
		p1 = p2;
	}
	return false;
}

//typedef struct {
//   double x,y;
//} Point;
//
//double PolygonArea(Point *polygon,int N)
//{
//   int i,j;
//   double area = 0;
//
//   for (i=0;i<N;i++) {
//      j = (i + 1) % N;
//      area += polygon[i].x * polygon[j].y;
//      area -= polygon[i].y * polygon[j].x;
//   }
//
//   area /= 2;
//   return(area < 0 ? -area : area);
//}

double GraphicsUtils::PolygonArea(QVector<QPointF>&polygon)
{
   int i,j;
   double area = 0;
   int N;
   N = polygon.count();
   for (i=0;i<N;i++) {
      j = (i + 1) % N;
      area += polygon[i].x() * polygon[j].y();
      area -= polygon[i].y() * polygon[j].x();
   }

   area /= 2;
   return(area < 0 ? -area : area);
}

/**
 * Function to calculate the center of mass for a given polygon, according
 * ot the algorithm defined at
 * http://local.wasp.uwa.edu.au/~pbourke/geometry/polyarea/
 *
 * @param polyPoints
 *            array of points in the polygon
 * @return point that is the center of mass
 */

QPointF GraphicsUtils::centerOfPolygon(QVector<QPointF>&polyPoints)
{
	double cx = 0, cy = 0;
	double area = PolygonArea(polyPoints);
	QPointF res;
	int i,j,n;
	n = polyPoints.count();
	double factor = 0;
	for (i = 0; i < n; i++) {
		j = (i + 1) % n;
		factor = (polyPoints[i].x() * polyPoints[j].y()
				- polyPoints[j].x() * polyPoints[i].y());
		cx += (polyPoints[i].x() + polyPoints[j].x()) * factor;
		cy += (polyPoints[i].y() + polyPoints[j].y()) * factor;
	}
	area *= 6.0f;
	factor = 1 / area;
	cx *= factor;
	cy *= factor;
	res.setX(cx);
	res.setY(cy);
	return res;
}

