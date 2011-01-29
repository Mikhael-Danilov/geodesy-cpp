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

#include "GlobalCoordinates.hpp"

#include <ostream>
#include <cmath>

namespace geodesy {

using namespace std;

GlobalCoordinates::~GlobalCoordinates() {
}

void GlobalCoordinates::canonicalize() {
	mLatitude = fmod((mLatitude + 180),  360);
	if (mLatitude < 0) {
		mLatitude += 360;
	}
	mLatitude -= 180;

	if (mLatitude > 90) {
		mLatitude = 180 - mLatitude;
		mLongitude += 180;
	} else if (mLatitude < -90) {
		mLatitude = -180 - mLatitude;
		mLongitude += 180;
	}

	mLongitude = fmod((mLongitude + 180), 360);
	if (mLongitude <= 0) {
		mLongitude += 360;
	}
	mLongitude -= 180;
}

GlobalCoordinates::GlobalCoordinates(double latitude, double longitude) :
	mLatitude(latitude), mLongitude(longitude) {
	canonicalize();
}

double GlobalCoordinates::getLatitude() const {
	return mLatitude;
}

void GlobalCoordinates::setLatitude(double latitude) {
	mLatitude = latitude;
	canonicalize();
}

double GlobalCoordinates::getLongitude() const {
	return mLongitude;
}

void GlobalCoordinates::setLongitude(double longitude) {
	mLongitude = longitude;
	canonicalize();
}

int GlobalCoordinates::compareTo(const GlobalCoordinates &other) const {
	int retval;

	if (getLongitude() < other.getLongitude()) {
		retval = -1;
	} else if (getLongitude() > other.getLongitude()) {
		retval = +1;
	} else if (getLatitude() < other.getLatitude()) {
		retval = -1;
	} else if (getLatitude() > other.getLatitude()) {
		retval = +1;
	} else {
		retval = 0;
	}

	return retval;
}

bool GlobalCoordinates::operator==(const GlobalCoordinates &other) const {
	return this->compareTo(other) == 0;
}

bool GlobalCoordinates::operator!=(const GlobalCoordinates &other) const {
	return this->compareTo(other) != 0;
}

bool GlobalCoordinates::operator<(const GlobalCoordinates &other) const {
	return this->compareTo(other) < 0;
}

bool GlobalCoordinates::operator<=(const GlobalCoordinates &other) const {
	return this->compareTo(other) <= 0;
}

bool GlobalCoordinates::operator>(const GlobalCoordinates &other) const {
	return this->compareTo(other) > 0;
}

bool GlobalCoordinates::operator>=(const GlobalCoordinates &other) const {
	return this->compareTo(other) >= 0;
}

ostream& operator<<(ostream& os, const GlobalCoordinates& obj) {
	os << fabs(obj.getLatitude()) << ((obj.getLatitude() >= 0) ? 'N' : 'S') //
			<< ";" //
			<< fabs(obj.getLongitude()) << ((obj.getLongitude() >= 0) ? 'E'
			: 'W') //
			<< ";";

	return os;
}

}
