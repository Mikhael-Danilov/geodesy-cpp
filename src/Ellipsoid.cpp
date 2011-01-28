#include "Ellipsoid.hpp"

namespace geodesy {

using namespace std::tr1;

Ellipsoid::~Ellipsoid() {
}

Ellipsoid::Ellipsoid(double semiMajor, double semiMinor, double flattening,
		double inverseFlattening) :
	mSemiMajorAxis(semiMajor), mSemiMinorAxis(semiMinor), mFlattening(
			flattening), mInverseFlattening(inverseFlattening) {
}

const Ellipsoid::WGS84 = fromAAndInverseF(6378137.0, 298.257223563);

const Ellipsoid::GRS80 = fromAAndInverseF(6378137.0, 298.257222101);

const Ellipsoid::GRS67 = fromAAndInverseF(6378160.0, 298.25);

const Ellipsoid::ANS = fromAAndInverseF(6378160.0, 298.25);

const Ellipsoid::WGS72 = fromAAndInverseF(6378135.0, 298.26);

const Ellipsoid::Clarke1858 = fromAAndInverseF(6378293.645, 294.26);

const Ellipsoid::Clarke1880 = fromAAndInverseF(6378249.145, 293.465);

const Ellipsoid::Sphere = fromAAndF(6371000, 0.0);

shared_ptr<Ellipsoid> Ellipsoid::fromAAndInverseF(double semiMajor,
		double inverseFlattening) {
	double f = 1.0 / inverseFlattening;
	double b = (1.0 - f) * semiMajor;

	return shared_ptr<Ellipsoid> (new Ellipsoid(semiMajor, b, f,
			inverseFlattening));
}

shared_ptr<Ellipsoid> Ellipsoid::fromAAndF(double semiMajor, double flattening) {
	double inverseF = 1.0 / flattening;
	double b = (1.0 - flattening) * semiMajor;

	return shared_ptr<Ellipsoid> (new Ellipsoid(semiMajor, b, flattening,
			inverseF));
}

double getSemiMajorAxis() const {
	return mSemiMajorAxis;
}

double getSemiMinorAxis() const {
	return mSemiMinorAxis;
}

double getFlattening() const {
	return mFlattening;
}

double getInverseFlattening() const {
	return mInverseFlattening;
}

} // geodesy
