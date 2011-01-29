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

#ifndef GEODETICCURVE_HPP_
#define GEODETICCURVE_HPP_

#include <ostream>

namespace geodesy {

/**
 * This is the outcome of a geodetic calculation. It represents the path and
 * ellipsoidal distance between two GlobalCoordinates for a specified reference
 * ellipsoid.
 *
 * @author Mike Gavaghan
 */
class GeodeticCurve {
public:
	virtual ~GeodeticCurve();

	/**
	 * Create a new GeodeticCurve.
	 * @param ellipsoidalDistance ellipsoidal distance in meters
	 * @param azimuth azimuth in degrees
	 * @param reverseAzimuth reverse azimuth in degrees
	 */
	GeodeticCurve(double ellipsoidalDistance, double azimuth,
			double reverseAzimuth);

	/**
	 * Get the ellipsoidal distance.
	 * @return ellipsoidal distance in meters
	 */
	double getEllipsoidalDistance() const;

	/**
	 * Get the azimuth.
	 * @return azimuth in degrees
	 */
	double getAzimuth() const;

	/**
	 * Get the reverse azimuth.
	 * @return reverse azimuth in degrees
	 */
	double getReverseAzimuth() const;

private:
	/** Ellipsoidal distance (in meters). */
	const double mEllipsoidalDistance;

	/** Azimuth (degrees from north). */
	const double mAzimuth;

	/** Reverse azimuth (degrees from north). */
	const double mReverseAzimuth;


};

ostream& operator<<(ostream& os, const GeodeticCurve& ia);

}
}

#endif /* GEODETICCURVE_HPP_ */
