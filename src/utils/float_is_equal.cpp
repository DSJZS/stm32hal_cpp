#include "../../inc/utils/float_is_equal.hpp"
#include <cmath>

bool float_is_equal( float x, float y, float rel_tol, float abs_tol)
{
    if( std::isnan(x) || std::isnan(y) )
        return false;
    
    if( std::isinf(x) && std::isinf(y) )
        return ( std::signbit(x) == std::signbit(y) );
    else if( std::isinf(x) || std::isinf(y) )
        return false;
    
    float diff = std::abs( x - y );
    if( diff < abs_tol )
        return true;
    float scale = std::max( std::abs(x), std::abs(y));

    return ( diff < rel_tol * scale );
}