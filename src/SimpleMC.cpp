/*
 * SimpleMC.cpp
 *
 *  Created on: Dec 3, 2015
 *      Author: gergelyc
 */

#include "SimpleMC.h"
#include "Random1.h"
#include <cmath>

double SimpleMonteCarlo(
	const PayOff& thePayOff,
	double Expiry,
	double Spot,
	double Vol,
	double r,
	unsigned long NumberOfPaths)
{
	double variance = Vol * Vol * Expiry;
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5 * variance;

	double movedSpot = Spot * exp(r * Expiry + itoCorrection);
	double thisSpot;
	double runningSum = 0;

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double thisGaussian = GetOneGaussianByBoxMuller();
		thisSpot = movedSpot * exp(rootVariance * thisGaussian);
		runningSum += thePayOff(thisSpot);
	}

	double mean = runningSum / NumberOfPaths;
	mean *= exp(-r * Expiry);
	return mean;
}


