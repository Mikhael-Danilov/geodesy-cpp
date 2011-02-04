#ifndef GEODESY_GEODETIC_CALCULATOR_TEST_HPP
#define GEODESY_GEODETIC_CALCULATOR_TEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <GeodeticCalculator.hpp>
#include <iostream>

class GeodeticCalculatorTest: public CppUnit::TestFixture {

CPPUNIT_TEST_SUITE( GeodeticCalculatorTest);

		// list all test methods here
		CPPUNIT_TEST(testCalculateGeodeticCurve);
		CPPUNIT_TEST(testCalculateGeodeticMeasurement);
		CPPUNIT_TEST(testAntiPodal1);
		CPPUNIT_TEST(testAntiPodal2);
		CPPUNIT_TEST(testInverseWithDirect);
		CPPUNIT_TEST(testPoleCrossing);
		CPPUNIT_TEST(testZeroDistance);
		CPPUNIT_TEST(testNanAzimuth);

	CPPUNIT_TEST_SUITE_END();

protected:
	void testCalculateGeodeticCurve();
	void testCalculateGeodeticMeasurement();
	void testAntiPodal1();
	void testAntiPodal2();
	void testInverseWithDirect();
	void testPoleCrossing();
	void testZeroDistance();
	void testNanAzimuth();

};

#endif // GEODESY_GEODETIC_CALCULATOR_TEST_HPP
