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

#ifndef GLOBALCOORDINATES_HPP_
#define GLOBALCOORDINATES_HPP_

#include <ostream>

namespace geodesy {

/**
 * <p>
 * Encapsulation of latitude and longitude coordinates on a globe. Negative
 * latitude is southern hemisphere. Negative longitude is western hemisphere.
 * </p>
 * <p>
 * Any angle may be specified for longitude and latitude, but all angles will be
 * canonicalized such that:
 * </p>
 *
 * <pre>
 * -90 <= latitude <= +90 - 180 < longitude <= +180
 * </pre>
 *
 */
class GlobalCoordinates {
public:
	virtual ~GlobalCoordinates();

	/**
	 * Construct a new GlobalCoordinates. Angles will be canonicalized.
	 *
	 * @param latitude latitude in degrees
	 * @param longitude longitude in degrees
	 */
	GlobalCoordinates(double latitude, double longitude);

	/**
	 * Get latitude.
	 *
	 * @return latitude in degrees
	 */
	double getLatitude() const;

	/**
	 * Set latitude. The latitude value will be canonicalized (which might result
	 * in a change to the longitude). Negative latitude is southern hemisphere.
	 *
	 * @param latitude in degrees
	 */
	void setLatitude(double latitude);

	/**
	 * Get longitude.
	 *
	 * @return longitude in degrees
	 */
	double getLongitude() const;

	/**
	 * Set longitude. The longitude value will be canonicalized. Negative
	 * longitude is western hemisphere.
	 *
	 * @param longitude in degrees
	 */
	void setLongitude(double longitude);

	/**
	 * Compare these coordinates to another set of coordiates. Western longitudes
	 * are less than eastern logitudes. If longitudes are equal, then southern
	 * latitudes are less than northern latitudes.
	 *
	 * @param other instance to compare to
	 * @return -1, 0, or +1 as per Comparable contract
	 */
	int compareTo(const GlobalCoordinates &other) const;

	bool operator==(const GlobalCoordinates &other) const;
	bool operator!=(const GlobalCoordinates &other) const;
	bool operator<(const GlobalCoordinates &other) const;
	bool operator<=(const GlobalCoordinates &other) const;
	bool operator>(const GlobalCoordinates &other) const;
	bool operator>=(const GlobalCoordinates &other) const;

private:
	/** Latitude in degrees. Negative latitude is southern hemisphere. */
	double mLatitude;

	/** Longitude in degrees. Negative longitude is western hemisphere. */
	double mLongitude;

	/**
	 * Canonicalize the current latitude and longitude values such that:
	 *
	 * <pre>
	 * -90 &lt;= latitude &lt;= +90 - 180 &lt; longitude &lt;= +180
	 * </pre>
	 */
	void canonicalize();

};

ostream& operator<<(std::ostream& os, const GlobalCoordinates& obj);

}

#endif /* GLOBALCOORDINATES_HPP_ */
