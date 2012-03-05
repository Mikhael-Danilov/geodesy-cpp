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

#ifndef GEODESY_GEODETIC_CALCULATOR
#define GEODESY_GEODETIC_CALCULATOR

#include <cmath>
#include <tr1/memory>
#include <exception>

#include "GeodeticMeasurement.hpp"
#include "GeodeticCurve.hpp"
#include "GlobalCoordinates.hpp"
#include "Ellipsoid.hpp"
#include "GlobalPosition.hpp"

/**
 * Geodesy library based upon the Java version at
 * http://www.gavaghan.org/blog/free-source-code/geodesy-library-vincentys-formula-java/
 */
namespace geodesy {

/**
 * Thrown when azimuth is NaN.
 */
class InvalidAzimuthException: public std::exception {
public:
	InvalidAzimuthException() {
	}
	virtual ~InvalidAzimuthException() throw () {
	}
	/**
	 * @see exception::what()
	 */
	virtual const char * what() const throw () {
		return "Invalid Azimuth";
	}
};

/**
 * <p>
 * Implementation of Thaddeus Vincenty's algorithms to solve the direct and
 * inverse geodetic problems. For more information, see Vincent's original
 * publication on the NOAA website:
 * </p>
 * See http://www.ngs.noaa.gov/PUBS_LIB/inverse.pdf
 *
 */
class GeodeticCalculator {
public:
	typedef std::tr1::shared_ptr<GeodeticCalculator> Ptr;
	typedef std::tr1::shared_ptr<GeodeticCalculator const> ConstPtr;

	virtual ~GeodeticCalculator();

	/**
	 * Calculate the destination and final bearing after traveling a specified
	 * distance, and a specified starting bearing, for an initial location. This
	 * is the solution to the direct geodetic problem.
	 *
	 * @param ellipsoid reference ellipsoid to use
	 * @param start starting location
	 * @param startBearing starting bearing (degrees)
	 * @param distance distance to travel (meters)
	 * @param endBearing bearing at destination (degrees) (output value)
	 * @param errorTolerance once the change in lambda reaches this value, stop iterating
	 * @param maxIterations maximum number of iterations, even if the error tolerance is not met
	 * @return the ending location
	 */
	static GlobalCoordinates::Ptr
	calculateEndingGlobalCoordinates(Ellipsoid::ConstPtr ellipsoid,
			const GlobalCoordinates &start, double startBearing,
			double distance, double &endBearing, double const errorTolerance =
					1E-13, int const maxIterations = 20)
					throw (InvalidAzimuthException);

	/**
	 * Calculate the geodetic curve between two points on a specified reference
	 * ellipsoid. This is the solution to the inverse geodetic problem.
	 *
	 * @param ellipsoid reference ellipsoid to use
	 * @param start starting coordinates
	 * @param end ending coordinates
	 * @param errorTolerance once the change in lambda reaches this value, stop iterating
	 * @param maxIterations maximum number of iterations, even if the error tolerance is not met
	 * @return the curve
	 */
	static GeodeticCurve::Ptr calculateGeodeticCurve(
			Ellipsoid::ConstPtr ellipsoid, const GlobalCoordinates &start,
			const GlobalCoordinates &end, double const errorTolerance = 1E-13,
			int const maxIterations = 20);

	/**
	 * <p>
	 * Calculate the three dimensional geodetic measurement between two positions
	 * measured in reference to a specified ellipsoid.
	 * </p>
	 * <p>
	 * This calculation is performed by first computing a new ellipsoid by
	 * expanding or contracting the reference ellipsoid such that the new
	 * ellipsoid passes through the average elevation of the two positions. A
	 * geodetic curve across the new ellipsoid is calculated. The point-to-point
	 * distance is calculated as the hypotenuse of a right triangle where the
	 * length of one side is the ellipsoidal distance and the other is the
	 * difference in elevation.
	 * </p>
	 *
	 * @param refEllipsoid reference ellipsoid to use
	 * @param start starting position
	 * @param end ending position
	 * @return the measurement
	 */
	static GeodeticMeasurement::Ptr
	calculateGeodeticMeasurement(Ellipsoid::ConstPtr refEllipsoid,
			const GlobalPosition &start, const GlobalPosition &end);

private:
	// no instances
	GeodeticCalculator() {
	}

};

} // geodesy

#endif //GEODESY_GEODETIC_CALCULATOR
