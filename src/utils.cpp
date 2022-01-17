#include "../include/utils.hpp"

GLfloat smallest_dimension(Dimensions dimensions)
{
    if (dimensions.width < dimensions.height)
        return dimensions.width;
    else
        return dimensions.height;
}
