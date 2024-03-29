// random number related functions.



#include "BasicLibRandom.h"

namespace BasicLib
{

// up to the user to re-seed as needed.
random Random( 0 );
random_percent_inclusive RandomPercent;
random_percent_exclusive RandomPercentExclusive;
random_range_inclusive RandomRange;
random_range_exclusive RandomRangeExclusive;
random_int RandomInt;
random_normal RandomNormal;
random_binomial RandomIntNormal;


} // end BasicLib namespace
