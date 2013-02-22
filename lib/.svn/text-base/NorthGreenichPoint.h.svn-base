/*
 * NorthGreenichPoint.h
 *
 *  Created on: 2012. 1. 25.
 *      Author: HIST002
 */

#ifndef NORTHGREENICHPOINT_H_
#define NORTHGREENICHPOINT_H_

class NorthGreenichPoint {
private:
	double northPoint;
	double greenichPoint;
	double incNorth(double d);
	double incGreenich(double d);
	double decNorth(double d);
	double decGreenich(double d);
	double greenichToLon(double gp);
	double northToLat(double np);
public:
	NorthGreenichPoint() { NorthGreenichPoint(0, 0); };
	NorthGreenichPoint(double np, double gp) { setNorth(np); setGreenich(gp); }

	void setGreenich(double gp) { if (gp >= 0 && gp <= 360) greenichPoint = fmod(gp, 360); }
	void setNorth(double np) { if(np>=0 && np <= 360) northPoint = fmod(np, 360); }
	void set(double np, double gp) { setNorth(np); setGreenich(gp); }

	double north() { return northPoint; }
	double greenich() { return greenichPoint; }

	void goEast(double gp) { setGreenich(gp); }
	void goWest(double gp) { setGreenich(gp); }
	void goNorth(double np) { setNorth(np); }
	void goSouth(double np) { setNorth(np); }

	void moveEast(double delta) { setGreenich(incGreenich(delta)); }
	void moveWest(double delta) { setGreenich(decGreenich(delta)); }
	void moveNorth(double delta) { setNorth(incNorth(delta)); }
	void moveSouth(double delta) { setNorth(decNorth(delta)); }

	double eastDegree(double d) { return incGreenich(d); }
	double westDegree(double d) { return decGreenich(d); }
	double northDegree(double d) { return incNorth(d); }
	double southDegree(double d) { return decNorth(d); }

	double lat() { return northToLat(northPoint); }
	double lon() { return greenichToLon(greenichPoint); }
	double lat(double np) { return northToLat(np); }
	double lon(double np) { return greenichToLon(np); }
};

#endif /* NORTHGREENICHPOINT_H_ */
