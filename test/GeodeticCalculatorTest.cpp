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

#include "GeodeticCalculatorTest.hpp"

#include <cppunit/extensions/HelperMacros.h>

#include <GeodeticCalculator.hpp>
#include <tr1/memory>

using namespace geodesy;
using namespace std;
using namespace std::tr1;
CPPUNIT_TEST_SUITE_REGISTRATION( GeodeticCalculatorTest );

void GeodeticCalculatorTest::testCalculateGeodeticCurve() {
	// select a reference elllipsoid
	shared_ptr<const Ellipsoid> reference = Ellipsoid::WGS84();

	// set Lincoln Memorial coordinates
	GlobalCoordinates lincolnMemorial(38.88922, -77.04978);

	// set Eiffel Tower coordinates
	GlobalCoordinates eiffelTower(48.85889, 2.29583);

	// calculate the geodetic curve
	shared_ptr<GeodeticCurve> geoCurve =
			GeodeticCalculator::calculateGeodeticCurve(reference,
					lincolnMemorial, eiffelTower);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(6179016.136, geoCurve->getEllipsoidalDistance(), 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(51.76792142, geoCurve->getAzimuth(), 0.0000001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(291.75529334, geoCurve->getReverseAzimuth(), 0.0000001);
}

void GeodeticCalculatorTest::testCalculateGeodeticMeasurement() {
	// select a reference elllipsoid
	shared_ptr<const Ellipsoid> reference = Ellipsoid::WGS84();

	// set Pike's Peak position
	GlobalPosition pikesPeak(38.840511, -105.0445896, 4301.0);

	// set Alcatraz Island coordinates
	GlobalPosition alcatrazIsland(37.826389, -122.4225, 0.0);

	// calculate the geodetic measurement
	shared_ptr<GeodeticMeasurement> geoMeasurement =
			GeodeticCalculator::calculateGeodeticMeasurement(reference, pikesPeak,
					alcatrazIsland);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(-4301.0, geoMeasurement->getElevationChange(), 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1521788.826, geoMeasurement->getPointToPointDistance(), 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1521782.748, geoMeasurement->getEllipsoidalDistance(), 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(271.21039153, geoMeasurement->getAzimuth(), 0.0000001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(80.38029386, geoMeasurement->getReverseAzimuth(), 0.0000001);
}

#if 0

void GeodeticCalculatorTest::testAntiPodal1()
{
	// select a reference elllipsoid
	shared_ptr<const Ellipsoid> reference = Ellipsoid::WGS84();

	// set position 1
	GlobalCoordinates p1(10, 80.6);

	// set position 2
	GlobalCoordinates p2(-10, -100);

	// calculate the geodetic measurement
	shared_ptr<GeodeticCurve> geoCurve = geoCalc.calculateGeodeticCurve(reference, p1, p2);

	assertEquals( 19970718.422432076, geoCurve.getEllipsoidalDistance(), 0.001);
	assertEquals(90.0004877491174, geoCurve.getAzimuth(), 0.0000001);
	assertEquals(270.0004877491174, geoCurve.getReverseAzimuth(), 0.0000001);
}

public void testAntiPodal2()
{
	// instantiate the calculator
	GeodeticCalculator geoCalc = new GeodeticCalculator();

	// select a reference elllipsoid
	Ellipsoid reference = Ellipsoid.WGS84;

	// set position 1
	GlobalCoordinates p1;
	p1 = new GlobalCoordinates(11, 80);

	// set position 2
	GlobalCoordinates p2;
	p2 = new GlobalCoordinates(-10, -100);

	// calculate the geodetic measurement
	GeodeticCurve geoCurve;

	geoCurve = geoCalc.calculateGeodeticCurve(reference, p1, p2);

	assertEquals( 19893320.272061437, geoCurve.getEllipsoidalDistance(), 0.001);
	assertEquals(360.0, geoCurve.getAzimuth(), 0.0000001);
	assertEquals(0.0, geoCurve.getReverseAzimuth(), 0.0000001);
}

public void testInverseWithDirect()
{
	// instantiate the calculator
	GeodeticCalculator geoCalc = new GeodeticCalculator();

	// select a reference elllipsoid
	Ellipsoid reference = Ellipsoid.WGS84;

	// set Lincoln Memorial coordinates
	GlobalCoordinates lincolnMemorial;
	lincolnMemorial = new GlobalCoordinates(38.88922, -77.04978);

	// set Eiffel Tower coordinates
	GlobalCoordinates eiffelTower;
	eiffelTower = new GlobalCoordinates(48.85889, 2.29583);

	// calculate the geodetic curve
	GeodeticCurve geoCurve = geoCalc.calculateGeodeticCurve(reference, lincolnMemorial, eiffelTower);

	// now, plug the result into to direct solution
	GlobalCoordinates dest;
	double[] endBearing = new double[1];

	dest = geoCalc.calculateEndingGlobalCoordinates(reference, lincolnMemorial, geoCurve.getAzimuth(), geoCurve.getEllipsoidalDistance(), endBearing);

	assertEquals( eiffelTower.getLatitude(), dest.getLatitude(), 0.0000001 );
	assertEquals( eiffelTower.getLongitude(), dest.getLongitude(), 0.0000001 );
}

public void testPoleCrossing()
{
	// instantiate the calculator
	GeodeticCalculator geoCalc = new GeodeticCalculator();

	// select a reference elllipsoid
	Ellipsoid reference = Ellipsoid.WGS84;

	// set Lincoln Memorial coordinates
	GlobalCoordinates lincolnMemorial;
	lincolnMemorial = new GlobalCoordinates(38.88922, -77.04978);

	// set a bearing of 1.0deg (almost straight up) and a distance
	double startBearing = 1.0;
	double distance = 6179016.13586;

	// set the expected destination
	GlobalCoordinates expected;
	expected = new GlobalCoordinates(85.60006433, 92.17243943);

	// calculate the ending global coordinates
	GlobalCoordinates dest = geoCalc.calculateEndingGlobalCoordinates(reference, lincolnMemorial, startBearing, distance );

	assertEquals(expected.getLatitude(), dest.getLatitude(), 0.0000001);
	assertEquals(expected.getLongitude(), dest.getLongitude(), 0.0000001);
}
}
#endif
