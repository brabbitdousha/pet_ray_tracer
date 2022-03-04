#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>
struct int3
{
	int x,y,z;
};
int3 write_color(color pixel_color) {
    // Write the translated [0,255] value of each color component.
    int3 temp;
    temp.x=static_cast<int>(255.999 * pixel_color.x());
    temp.y=static_cast<int>(255.999 * pixel_color.y());
    temp.z=static_cast<int>(255.999 * pixel_color.z());
    return temp;
}

#endif
