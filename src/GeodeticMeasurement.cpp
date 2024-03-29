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

#include "GeodeticMeasurement.hpp"

#include <cmath>

namespace geodesy {

using namespace std;

GeodeticMeasurement::~GeodeticMeasurement() {
}

GeodeticMeasurement::GeodeticMeasurement(double ellipsoidalDistance,
		double azimuth, double reverseAzimuth, double elevationChange) :
		GeodeticCurve(ellipsoidalDistance, azimuth, reverseAzimuth), mElevationChange(
				elevationChange), mP2P(
				sqrt(
						ellipsoidalDistance * ellipsoidalDistance
								+ mElevationChange * mElevationChange)) {
}

GeodeticMeasurement::GeodeticMeasurement(const GeodeticCurve &averageCurve,
		double elevationChange) :
		GeodeticCurve(averageCurve.getEllipsoidalDistance(),
				averageCurve.getAzimuth(), averageCurve.getReverseAzimuth()), mElevationChange(
				elevationChange), mP2P(
				sqrt(
						averageCurve.getEllipsoidalDistance()
								* averageCurve.getEllipsoidalDistance()
								+ mElevationChange * mElevationChange)) {
}

double GeodeticMeasurement::getElevationChange() const {
	return mElevationChange;
}

double GeodeticMeasurement::getPointToPointDistance() const {
	return mP2P;
}

std::ostream& operator<<(std::ostream& os, const GeodeticMeasurement& obj) {
	os << static_cast<const GeodeticCurve &>(obj) //
			<< "elev12=" << obj.getElevationChange() //
			<< ";p2p=" << obj.getPointToPointDistance();

	return os;
}

}
