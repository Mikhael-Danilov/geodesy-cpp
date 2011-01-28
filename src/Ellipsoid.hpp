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
	//FIXME make these constants be static functions with a static variable to ensure
	// order or elaboration

	/** The WGS84 ellipsoid. */
	static std::tr1::shared_ptr<Ellipsoid> WGS84();

	/** The GRS80 ellipsoid. */
	static std::tr1::shared_ptr<Ellipsoid> GRS80();

	/** The GRS67 ellipsoid. */
	static std::tr1::shared_ptr<Ellipsoid> GRS67();

	/** The ANS ellipsoid. */
	static std::tr1::shared_ptr<Ellipsoid> ANS();

	/** The WGS72 ellipsoid. */
	static std::tr1::shared_ptr<Ellipsoid> WGS72();

	/** The Clarke1858 ellipsoid. */
	static std::tr1::shared_ptr<Ellipsoid> Clarke1858();

	/** The Clarke1880 ellipsoid. */
	static std::tr1::shared_ptr<Ellipsoid> Clarke1880();

	/** A spherical "ellipsoid". */
	static std::tr1::shared_ptr<Ellipsoid> Sphere();

	/**
	 * Build an Ellipsoid from the semi major axis measurement and the inverse flattening.
	 * @param semiMajor semi major axis (meters)
	 * @param inverseFlattening
	 * @return
	 */
	static std::tr1::shared_ptr<Ellipsoid> fromAAndInverseF(double semiMajor,
			double inverseFlattening);

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
