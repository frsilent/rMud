//contains the basic types


#ifndef BASICLIBTYPES_H
#define BASICLIBTYPES_H
#include <iostream>
#include <fstream>
#include <string>


namespace BasicLib
{

//  defines the 64 bit datatype
// ---------------------------------------------------------

	#include <stddef.h>
	#include <sys/types.h>
	#include <stdint.h>
    typedef int64_t sint64;
    typedef uint64_t uint64;


typedef signed long int sint32;
typedef unsigned long int uint32;
typedef signed short int sint16;
typedef unsigned short int uint16;
typedef signed char sint8;
typedef unsigned char uint8;


const double pi = 3.1415926535897932384626433832795;







} // end BasicLib namespace


#endif

