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

#include "GlobalPosition.hpp"

namespace geodesy {

GlobalPosition::~GlobalPosition() {
}

GlobalPosition::GlobalPosition(double latitude, double longitude,
		double elevation) :
		GlobalCoordinates(latitude, longitude), mElevation(elevation) {
}

GlobalPosition::GlobalPosition(const GlobalCoordinates &coords,
		double elevation) :
		GlobalCoordinates(coords.getLatitude(), coords.getLongitude()), mElevation(
				elevation) {
}

double GlobalPosition::getElevation() const {
	return mElevation;
}

void GlobalPosition::setElevation(double elevation) {
	mElevation = elevation;
}

int GlobalPosition::compareTo(const GlobalPosition &other) const {
	int retval = GlobalCoordinates::compareTo(other);

	if (retval == 0) {
		if (getElevation() < other.getElevation()) {
			retval = -1;
		} else if (getElevation() > other.getElevation()) {
			retval = +1;
		}
	}

	return retval;
}

bool GlobalPosition::operator==(const GlobalPosition &other) const {
	return compareTo(other) == 0;
}

bool GlobalPosition::operator!=(const GlobalPosition &other) const {
	return compareTo(other) != 0;
}

bool GlobalPosition::operator<(const GlobalPosition &other) const {
	return compareTo(other) < 0;
}

bool GlobalPosition::operator<=(const GlobalPosition &other) const {
	return compareTo(other) <= 0;
}

bool GlobalPosition::operator>(const GlobalPosition &other) const {
	return compareTo(other) > 0;
}

bool GlobalPosition::operator>=(const GlobalPosition &other) const {
	return compareTo(other) >= 0;
}

std::ostream& operator<<(std::ostream& os, const GlobalPosition& obj) {
	os << static_cast<const GlobalCoordinates &>(obj) //
			<< "elevation=" << obj.getElevation() << "m";

	return os;
}

}
