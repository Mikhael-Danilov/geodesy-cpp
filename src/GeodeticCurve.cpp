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

#include "GeodeticCurve.hpp"

namespace geodesy {

using namespace std;

GeodeticCurve::~GeodeticCurve() {
}

GeodeticCurve::GeodeticCurve(double ellipsoidalDistance, double azimuth,
		double reverseAzimuth) :
		mEllipsoidalDistance(ellipsoidalDistance), mAzimuth(azimuth), mReverseAzimuth(
				reverseAzimuth) {
}

double GeodeticCurve::getEllipsoidalDistance() const {
	return mEllipsoidalDistance;
}

double GeodeticCurve::getAzimuth() const {
	return mAzimuth;
}

double GeodeticCurve::getReverseAzimuth() const {
	return mReverseAzimuth;
}

/**
 * Output a GeodeticCurve in a human readable format.
 */
ostream& operator<<(ostream& os, const GeodeticCurve& obj) {
	os << "s=" << obj.getEllipsoidalDistance() //
			<< ";a12=" << obj.getAzimuth() //
			<< ";a21=" << obj.getReverseAzimuth() << ";";

	return os;
}

}
