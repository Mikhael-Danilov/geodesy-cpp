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

#include "Ellipsoid.hpp"

namespace geodesy {

Ellipsoid::~Ellipsoid() {
}

Ellipsoid::Ellipsoid(double semiMajor, double semiMinor, double flattening,
		double inverseFlattening) :
		mSemiMajorAxis(semiMajor), mSemiMinorAxis(semiMinor), mFlattening(
				flattening), mInverseFlattening(inverseFlattening) {
}

Ellipsoid::ConstPtr Ellipsoid::WGS84() {
	static Ellipsoid::ConstPtr singleton = fromAAndInverseF(6378137.0,
			298.257223563);
	return singleton;
}

Ellipsoid::ConstPtr Ellipsoid::GRS80() {
	static Ellipsoid::ConstPtr singleton = fromAAndInverseF(6378137.0,
			298.257222101);
	return singleton;
}

Ellipsoid::ConstPtr Ellipsoid::GRS67() {
	static Ellipsoid::ConstPtr singleton = fromAAndInverseF(6378160.0, 298.25);
	return singleton;
}

Ellipsoid::ConstPtr Ellipsoid::ANS() {
	static Ellipsoid::ConstPtr singleton = fromAAndInverseF(6378160.0, 298.25);
	return singleton;
}

Ellipsoid::ConstPtr Ellipsoid::WGS72() {
	static Ellipsoid::ConstPtr singleton = fromAAndInverseF(6378135.0, 298.26);
	return singleton;
}

Ellipsoid::ConstPtr Ellipsoid::Clarke1858() {
	static Ellipsoid::ConstPtr singleton = fromAAndInverseF(6378293.645,
			294.26);
	return singleton;
}

Ellipsoid::ConstPtr Ellipsoid::Clarke1880() {
	static Ellipsoid::ConstPtr singleton = fromAAndInverseF(6378249.145,
			293.465);
	return singleton;
}

Ellipsoid::ConstPtr Ellipsoid::Sphere() {
	static Ellipsoid::ConstPtr singleton = fromAAndF(6371000, 0.0);
	return singleton;
}

Ellipsoid::ConstPtr Ellipsoid::fromAAndInverseF(double semiMajor,
		double inverseFlattening) {
	double f = 1.0 / inverseFlattening;
	double b = (1.0 - f) * semiMajor;

	return Ellipsoid::ConstPtr(
			new Ellipsoid(semiMajor, b, f, inverseFlattening));
}

Ellipsoid::ConstPtr Ellipsoid::fromAAndF(double semiMajor, double flattening) {
	double inverseF = 1.0 / flattening;
	double b = (1.0 - flattening) * semiMajor;

	return Ellipsoid::ConstPtr(
			new Ellipsoid(semiMajor, b, flattening, inverseF));
}

double Ellipsoid::getSemiMajorAxis() const {
	return mSemiMajorAxis;
}

double Ellipsoid::getSemiMinorAxis() const {
	return mSemiMinorAxis;
}

double Ellipsoid::getFlattening() const {
	return mFlattening;
}

double Ellipsoid::getInverseFlattening() const {
	return mInverseFlattening;
}

} // geodesy
