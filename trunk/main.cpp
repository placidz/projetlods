#include <stdlib.h>
#include <iostream>

#include "Vec3.h"


int main()
{
    Vec3d vec1 = Vec3d(0.0, 0.0, 0.0);
    Vec3d vec2 = Vec3d(1.0, 1.0, 0.0);

    std::cout<<distance(vec1, vec2)<<std::endl;

    system("PAUSE");
    return 0;
}
