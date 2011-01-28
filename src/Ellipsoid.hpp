/*
 * Ellipsoid.hpp
 *
 *  Created on: Jan 27, 2011
 *      Author: jschewe
 */

#ifndef ELLIPSOID_HPP_
#define ELLIPSOID_HPP_

#include <tr1/memory>

namespace geodesy {

/**
 * Encapsulation of an ellipsoid, and declaration of common reference ellipsoids.
 * @author Mike Gavaghan
 */
class Ellipsoid {
public:
	virtual ~Ellipsoid();

public:
	/** The WGS84 ellipsoid. */
	static const Ellipsoid WGS84;

	/** The GRS80 ellipsoid. */
	static const Ellipsoid GRS80;

	/** The GRS67 ellipsoid. */
	static const Ellipsoid GRS67;

	/** The ANS ellipsoid. */
	static const Ellipsoid ANS;

	/** The WGS72 ellipsoid. */
	static const Ellipsoid WGS72;

	/** The Clarke1858 ellipsoid. */
	static const Ellipsoid Clarke1858;

	/** The Clarke1880 ellipsoid. */
	static const Ellipsoid Clarke1880;

	/** A spherical "ellipsoid". */
	static const Ellipsoid Sphere;

	/**
	 * Build an Ellipsoid from the semi major axis measurement and the inverse flattening.
	 * @param semiMajor semi major axis (meters)
	 * @param inverseFlattening
	 * @return
	 */
	static std::tr1:shared_ptr<Ellipsoid> fromAAndInverseF(double semiMajor, double inverseFlattening);

	/**
	 * Build an Ellipsoid from the semi major axis measurement and the flattening.
	 * @param semiMajor semi major axis (meters)
	 * @param flattening
	 * @return
	 */
	static std::tr1::shared_ptr<Ellipsoid> fromAAndF(double semiMajor,
			double flattening);

	/**
	 * Get semi-major axis.
	 * @return semi-major axis (in meters).
	 */
	double getSemiMajorAxis() const;

	/**
	 * Get semi-minor axis.
	 * @return semi-minor axis (in meters).
	 */
	double getSemiMinorAxis() const;

	/**
	 * Get flattening
	 * @return
	 */
	double getFlattening() const;

	/**
	 * Get inverse flattening.
	 * @return
	 */
	double getInverseFlattening() const;


private:
	/** Semi major axis (meters). */
	const double mSemiMajorAxis;

	/** Semi minor axis (meters). */
	const double mSemiMinorAxis;

	/** Flattening. */
	const double mFlattening;

	/** Inverse flattening. */
	const double mInverseFlattening;

	/**
	 * Construct a new Ellipsoid.  This is private to ensure the values are
	 * consistent (flattening = 1.0 / inverseFlattening).  Use the methods
	 * fromAAndInverseF() and fromAAndF() to create new instances.
	 * @param semiMajor
	 * @param semiMinor
	 * @param flattening
	 * @param inverseFlattening
	 */
	Ellipsoid(double semiMajor, double semiMinor, double flattening,
			double inverseFlattening);

};

}

#endif /* ELLIPSOID_HPP_ */
