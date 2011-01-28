#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/TextOutputter.h>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;
using namespace CppUnit;

int main(int argc, char **argv)
{
    //  TestResult controller;
    //  TestResultCollector result;
    //  controller.addListener(&result);

    TextTestRunner runner;

    runner.addTest(TestFactoryRegistry::getRegistry().makeTest());
    // this outputs to stdout
    runner.run();

    ofstream xmlFileOut("cpptestresults.xml");
    XmlOutputter xmlOut(&runner.result(), xmlFileOut);
    xmlOut.write();

    //  xmlOut.close();
    xmlFileOut.close();

    //return wasSuccessful;
    return 0;
}
