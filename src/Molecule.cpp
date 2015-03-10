#include "Molecule.h"
#include <iostream>
#include <string>
Molecule::Molecule()
{

}

Molecule::Molecule(double _x, double _y)
{
    x=_x;
    y=_y;
}

Molecule::Molecule(double _x, double _y, double _vx, double _vy, double _r, double _m)
{
    x=_x;
    y=_y;
    vx=_vx;
    vy=_vy;
    r=_r;
    m=_m;
}
Molecule::~Molecule()
{
    std::cout << "DESTRUKTOR";
}

void Molecule::set_velocity(double _vx, double _vy)
{
    vx=_vx;
    vy=_vy;
}

void Molecule::set_position(double _x, double _y)
{
    x=_x;
    y=_y;
}

void Molecule::set_radius(double _r)
{
    r=_r;
}
void Molecule::set_mass(double _m)
{
    m=_m;
}

void Molecule::update()
{
    if (m==0.0)
        delete(this);
}


std::ostream &operator<<( std::ostream &output, const Molecule *M )
{
    if(M->show_type()=='P')
        output << M->show_name() << " " << M->show_x() << " " << M->show_y() << " " << M->show_r();
    else
        output << M->show_name() << " " << M->show_x() << " " << M->show_y() << " " << M->show_r() << " " << M->show_m();
    return output;
}
