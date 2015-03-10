#include "MArea.h"
#include <cmath>
#include <iostream>
#include <algorithm>

MArea::MArea(double a, double b)
{
    x=a;
    y=b;
}

MArea::MArea()
{
    x=10.0;
    y=15.0;
}

void MArea::run(Molecule *M)
{
    M->set_position( M->show_x() + M->show_vx()/100, M->show_y() + M->show_vy()/100 );
}


MArea::~MArea()
{
    delete(this);
}
