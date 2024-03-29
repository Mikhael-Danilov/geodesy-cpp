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

#ifndef GLOBALPOSITION_HPP_
#define GLOBALPOSITION_HPP_

#include "GlobalCoordinates.hpp"

#include <ostream>
#include <tr1/memory>

namespace geodesy {

/**
 * <p>
 * Encapsulates a three dimensional location on a globe (GlobalCoordinates
 * combined with an elevation in meters above a reference ellipsoid).
 * </p>
 * <p>
 * See documentation for GlobalCoordinates for details on how latitude and
 * longitude measurements are canonicalized.
 * </p>
 *
 */
class GlobalPosition: public GlobalCoordinates {
public:
	typedef std::tr1::shared_ptr<GlobalPosition> Ptr;
	typedef std::tr1::shared_ptr<GlobalPosition const> ConstPtr;

	virtual ~GlobalPosition();

	/**
	 * Creates a new instance of GlobalPosition.
	 *
	 * @param latitude latitude in degrees
	 * @param longitude longitude in degrees
	 * @param elevation elevation, in meters, above the reference ellipsoid
	 */
	GlobalPosition(double latitude, double longitude, double elevation);

	/**
	 * Creates a new instance of GlobalPosition.
	 *
	 * @param coords coordinates of the position
	 * @param elevation elevation, in meters, above the reference ellipsoid
	 */
	GlobalPosition(const GlobalCoordinates &coords, double elevation);

	/**
	 * Get elevation.
	 *
	 * @return elevation about the ellipsoid in meters.
	 */
	double getElevation() const;

	/**
	 * Set the elevation.
	 *
	 * @param elevation elevation about the ellipsoid in meters.
	 */
	void setElevation(double elevation);

	/**
	 * Compare this position to another. Western longitudes are less than eastern
	 * logitudes. If longitudes are equal, then southern latitudes are less than
	 * northern latitudes. If coordinates are equal, lower elevations are less
	 * than higher elevations
	 *
	 * @param other instance to compare to
	 * @return -1, 0, or +1 as per Comparable contract
	 */
	int compareTo(const GlobalPosition &other) const;

	/**
	 * @see compareTo()
	 */
	bool operator==(const GlobalPosition &other) const;
	/**
	 * @see compareTo()
	 */
	bool operator!=(const GlobalPosition &other) const;
	/**
	 * @see compareTo()
	 */
	bool operator<(const GlobalPosition &other) const;
	/**
	 * @see compareTo()
	 */
	bool operator<=(const GlobalPosition &other) const;
	/**
	 * @see compareTo()
	 */
	bool operator>(const GlobalPosition &other) const;
	/**
	 * @see compareTo()
	 */
	bool operator>=(const GlobalPosition &other) const;

private:
	/** Elevation, in meters, above the surface of the ellipsoid. */
	double mElevation;

};

std::ostream& operator<<(std::ostream& os, const GlobalPosition& obj);

}

#endif /* GLOBALPOSITION_HPP_ */
