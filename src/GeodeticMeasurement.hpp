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

#ifndef GEODETICMEASUREMENT_HPP_
#define GEODETICMEASUREMENT_HPP_

#include "GeodeticCurve.hpp"

namespace geodesy {

class GeodeticMeasurement: public GeodeticCurve {
public:
	virtual ~GeodeticMeasurement();
	/**
	 * Creates a new instance of GeodeticMeasurement.
	 *
	 * @param ellipsoidalDistance ellipsoidal distance in meters
	 * @param azimuth azimuth in degrees
	 * @param reverseAzimuth reverse azimuth in degrees
	 * @param elevationChange the change in elevation, in meters, going from the
	 *           starting point to the ending point
	 */
	GeodeticMeasurement(double ellipsoidalDistance, double azimuth,
			double reverseAzimuth, double elevationChange);

	/**
	 * Creates a new instance of GeodeticMeasurement.
	 *
	 * @param averageCurve average geodetic curve
	 * @param elevationChange the change in elevation, in meters, going from the
	 *           starting point to the ending point
	 */
	GeodeticMeasurement(const GeodeticCurve &averageCurve,
			double elevationChange);

	/**
	 * Get the elevation change.
	 *
	 * @return elevation change, in meters, going from the starting to the ending
	 *         point
	 */
	double getElevationChange() const;

	/**
	 * Get the point-to-point distance.
	 *
	 * @return the distance traveled, in meters, going from one point to the
	 *         next
	 */
	double getPointToPointDistance() const;

private:
	/**
	 * The elevation change, in meters, going from the starting to the ending
	 * point.
	 */
	const double mElevationChange;

	/** The distance traveled, in meters, going from one point to the next. */
	const double mP2P;

};

std::ostream& operator<<(std::ostream& os, const GeodeticMeasurement& obj);

}

#endif /* GEODETICMEASUREMENT_HPP_ */
