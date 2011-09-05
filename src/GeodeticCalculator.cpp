/*
 * Copyright (c) 2011
 *      Jon Schewe.  All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * I'd appreciate comments/suggestions on the code jpschewe@mtu.net
 */

#include "GeodeticCalculator.hpp"
#include "Angle.hpp"

#include <cmath>

namespace geodesy {

using namespace std;

GlobalCoordinates::Ptr GeodeticCalculator::calculateEndingGlobalCoordinates(
		Ellipsoid::ConstPtr ellipsoid, const GlobalCoordinates &start,
		double startBearing, double distance, double &endBearing)
				throw (InvalidAzimuthException) {
	if (isnan(startBearing)) {
		throw InvalidAzimuthException();
	}

	double a = ellipsoid->getSemiMajorAxis();
	double b = ellipsoid->getSemiMinorAxis();
	double aSquared = a * a;
	double bSquared = b * b;
	double f = ellipsoid->getFlattening();
	double phi1 = Angle::toRadians(start.getLatitude());
	double alpha1 = Angle::toRadians(startBearing);
	double cosAlpha1 = cos(alpha1);
	double sinAlpha1 = sin(alpha1);
	double s = distance;
	double tanU1 = (1.0 - f) * tan(phi1);
	double cosU1 = 1.0 / sqrt(1.0 + tanU1 * tanU1);
	double sinU1 = tanU1 * cosU1;

	// eq. 1
	double sigma1 = atan2(tanU1, cosAlpha1);

	// eq. 2
	double sinAlpha = cosU1 * sinAlpha1;

	double sin2Alpha = sinAlpha * sinAlpha;
	double cos2Alpha = 1 - sin2Alpha;
	double uSquared = cos2Alpha * (aSquared - bSquared) / bSquared;

	// eq. 3
	double A =
			1
					+ (uSquared / 16384)
							* (4096
									+ uSquared
											* (-768
													+ uSquared
															* (320
																	- 175
																			* uSquared)));

	// eq. 4
	double B = (uSquared / 1024)
			* (256 + uSquared * (-128 + uSquared * (74 - 47 * uSquared)));

	// iterate until there is a negligible change in sigma
	double deltaSigma;
	double sOverbA = s / (b * A);
	double sigma = sOverbA;
	double sinSigma;
	double prevSigma = sOverbA;
	double sigmaM2;
	double cosSigmaM2;
	double cos2SigmaM2;

	for (;;) {
		// eq. 5
		sigmaM2 = 2.0 * sigma1 + sigma;
		cosSigmaM2 = cos(sigmaM2);
		cos2SigmaM2 = cosSigmaM2 * cosSigmaM2;
		sinSigma = sin(sigma);
		double cosSignma = cos(sigma);

		// eq. 6
		deltaSigma = B * sinSigma
				* (cosSigmaM2
						+ (B / 4.0)
								* (cosSignma * (-1 + 2 * cos2SigmaM2)
										- (B / 6.0) * cosSigmaM2
												* (-3 + 4 * sinSigma * sinSigma)
												* (-3 + 4 * cos2SigmaM2)));

		// eq. 7
		sigma = sOverbA + deltaSigma;

		// break after converging to tolerance
		if (fabs(sigma - prevSigma) < 0.0000000000001)
			break;

		prevSigma = sigma;
	}

	sigmaM2 = 2.0 * sigma1 + sigma;
	cosSigmaM2 = cos(sigmaM2);
	cos2SigmaM2 = cosSigmaM2 * cosSigmaM2;

	double cosSigma = cos(sigma);
	sinSigma = sin(sigma);

	// eq. 8
	double phi2 = atan2(
			sinU1 * cosSigma + cosU1 * sinSigma * cosAlpha1,
			(1.0 - f)
					* sqrt(
							sin2Alpha
									+ pow(
											sinU1 * sinSigma
													- cosU1 * cosSigma
															* cosAlpha1, 2.0)));

	// eq. 9
	// This fixes the pole crossing defect spotted by Matt Feemster. When a
	// path passes a pole and essentially crosses a line of latitude twice -
	// once in each direction - the longitude calculation got messed up. Using
	// atan2 instead of atan fixes the defect. The change is in the next 3
	// lines.
	// double tanLambda = sinSigma * sinAlpha1 / (cosU1 * cosSigma - sinU1 * sinSigma * cosAlpha1);
	// double lambda = atan(tanLambda);
	double lambda = atan2(sinSigma * sinAlpha1,
			(cosU1 * cosSigma - sinU1 * sinSigma * cosAlpha1));

	// eq. 10
	double C = (f / 16) * cos2Alpha * (4 + f * (4 - 3 * cos2Alpha));

	// eq. 11
	double L = lambda
			- (1 - C) * f * sinAlpha
					* (sigma
							+ C * sinSigma
									* (cosSigmaM2
											+ C * cosSigma
													* (-1 + 2 * cos2SigmaM2)));

	// eq. 12
	double alpha2 = atan2(sinAlpha,
			-sinU1 * sinSigma + cosU1 * cosSigma * cosAlpha1);

	// build result
	double latitude = Angle::toDegrees(phi2);
	double longitude = start.getLongitude() + Angle::toDegrees(L);

	endBearing = Angle::toDegrees(alpha2);

	return GlobalCoordinates::Ptr(new GlobalCoordinates(latitude, longitude));
}

GlobalCoordinates::Ptr GeodeticCalculator::calculateEndingGlobalCoordinates(
		Ellipsoid::ConstPtr ellipsoid, const GlobalCoordinates &start,
		double startBearing, double distance) throw (InvalidAzimuthException) {
	double dummy;
	return calculateEndingGlobalCoordinates(ellipsoid, start, startBearing,
			distance, dummy);
}

GeodeticCurve::Ptr GeodeticCalculator::calculateGeodeticCurve(
		Ellipsoid::ConstPtr ellipsoid, const GlobalCoordinates &start,
		const GlobalCoordinates &end) {
	//
	// All equation numbers refer back to Vincenty's publication:
	// See http://www.ngs.noaa.gov/PUBS_LIB/inverse.pdf
	//

	// get constants
	double a = ellipsoid->getSemiMajorAxis();
	double b = ellipsoid->getSemiMinorAxis();
	double f = ellipsoid->getFlattening();

	// get parameters as radians
	double phi1 = Angle::toRadians(start.getLatitude());
	double lambda1 = Angle::toRadians(start.getLongitude());
	double phi2 = Angle::toRadians(end.getLatitude());
	double lambda2 = Angle::toRadians(end.getLongitude());

	// calculations
	double a2 = a * a;
	double b2 = b * b;
	double a2b2b2 = (a2 - b2) / b2;

	double omega = lambda2 - lambda1;

	double tanphi1 = tan(phi1);
	double tanU1 = (1.0 - f) * tanphi1;
	double U1 = atan(tanU1);
	double sinU1 = sin(U1);
	double cosU1 = cos(U1);

	double tanphi2 = tan(phi2);
	double tanU2 = (1.0 - f) * tanphi2;
	double U2 = atan(tanU2);
	double sinU2 = sin(U2);
	double cosU2 = cos(U2);

	double sinU1sinU2 = sinU1 * sinU2;
	double cosU1sinU2 = cosU1 * sinU2;
	double sinU1cosU2 = sinU1 * cosU2;
	double cosU1cosU2 = cosU1 * cosU2;

	// eq. 13
	double lambda = omega;

	// intermediates we'll need to compute 's'
	double A = 0.0;
	double B = 0.0;
	double sigma = 0.0;
	double deltasigma = 0.0;
	double lambda0;
	bool converged = false;

	for (int i = 0; i < 20; i++) {
		lambda0 = lambda;

		double sinlambda = sin(lambda);
		double coslambda = cos(lambda);

		// eq. 14
		double sin2sigma = (cosU2 * sinlambda * cosU2 * sinlambda)
				+ (cosU1sinU2 - sinU1cosU2 * coslambda)
						* (cosU1sinU2 - sinU1cosU2 * coslambda);
		double sinsigma = sqrt(sin2sigma);

		// eq. 15
		double cossigma = sinU1sinU2 + (cosU1cosU2 * coslambda);

		// eq. 16
		sigma = atan2(sinsigma, cossigma);

		// eq. 17 Careful! sin2sigma might be almost 0!
		double sinalpha =
				(sin2sigma == 0) ? 0.0 : cosU1cosU2 * sinlambda / sinsigma;
		double alpha = asin(sinalpha);
		double cosalpha = cos(alpha);
		double cos2alpha = cosalpha * cosalpha;

		// eq. 18 Careful! cos2alpha might be almost 0!
		double cos2sigmam =
				cos2alpha == 0.0 ? 0.0 : cossigma - 2 * sinU1sinU2 / cos2alpha;
		double u2 = cos2alpha * a2b2b2;

		double cos2sigmam2 = cos2sigmam * cos2sigmam;

		// eq. 3
		A = 1.0 + u2 / 16384 * (4096 + u2 * (-768 + u2 * (320 - 175 * u2)));

		// eq. 4
		B = u2 / 1024 * (256 + u2 * (-128 + u2 * (74 - 47 * u2)));

		// eq. 6
		deltasigma = B * sinsigma
				* (cos2sigmam
						+ B / 4
								* (cossigma * (-1 + 2 * cos2sigmam2)
										- B / 6 * cos2sigmam
												* (-3 + 4 * sin2sigma)
												* (-3 + 4 * cos2sigmam2)));

		// eq. 10
		double C = f / 16 * cos2alpha * (4 + f * (4 - 3 * cos2alpha));

		// eq. 11 (modified)
		lambda =
				omega
						+ (1 - C) * f * sinalpha
								* (sigma
										+ C * sinsigma
												* (cos2sigmam
														+ C * cossigma
																* (-1
																		+ 2
																				* cos2sigmam2)));

		// see how much improvement we got
		double change = fabs((lambda - lambda0) / lambda);

		if ((i > 1) && (change < 0.0000000000001)) {
			converged = true;
			break;
		}
	}

	// eq. 19
	double s = b * A * (sigma - deltasigma);
	double alpha1;
	double alpha2;

	// didn't converge? must be N/S
	if (!converged) {
		if (phi1 > phi2) {
			alpha1 = 180.0;
			alpha2 = 0.0;
		} else if (phi1 < phi2) {
			alpha1 = 0.0;
			alpha2 = 180.0;
		} else {
			alpha1 = nan("");
			alpha2 = nan("");
		}
	}

	// else, it converged, so do the math
	else {
		static const double TwoPi = 2.0 * M_PI;

		double radians;

		// eq. 20
		radians = atan2(cosU2 * sin(lambda),
				(cosU1sinU2 - sinU1cosU2 * cos(lambda)));
		if (radians < 0.0)
			radians += TwoPi;
		alpha1 = Angle::toDegrees(radians);

		// eq. 21
		radians = atan2(cosU1 * sin(lambda),
				(-sinU1cosU2 + cosU1sinU2 * cos(lambda))) + M_PI;
		if (radians < 0.0)
			radians += TwoPi;
		alpha2 = Angle::toDegrees(radians);
	}

	if (alpha1 >= 360.0)
		alpha1 -= 360.0;
	if (alpha2 >= 360.0)
		alpha2 -= 360.0;

	return GeodeticCurve::Ptr(new GeodeticCurve(s, alpha1, alpha2));
}
GeodeticMeasurement::Ptr GeodeticCalculator::calculateGeodeticMeasurement(
		Ellipsoid::ConstPtr refEllipsoid, const GlobalPosition &start,
		const GlobalPosition &end) {
	// calculate elevation differences
	double elev1 = start.getElevation();
	double elev2 = end.getElevation();
	double elev12 = (elev1 + elev2) / 2.0;

	// calculate latitude differences
	double phi1 = Angle::toRadians(start.getLatitude());
	double phi2 = Angle::toRadians(end.getLatitude());
	double phi12 = (phi1 + phi2) / 2.0;

	// calculate a new ellipsoid to accommodate average elevation
	double refA = refEllipsoid->getSemiMajorAxis();
	double f = refEllipsoid->getFlattening();
	double a = refA + elev12 * (1.0 + f * sin(phi12));
	Ellipsoid::ConstPtr ellipsoid = Ellipsoid::fromAAndF(a, f);

	// calculate the curve at the average elevation
	GeodeticCurve::Ptr averageCurve = calculateGeodeticCurve(ellipsoid, start,
			end);

	// return the measurement
	return GeodeticMeasurement::Ptr(
			new GeodeticMeasurement(*averageCurve, elev2 - elev1));
}

} // geodesy
