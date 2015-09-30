#ifndef MDUAL_H
#define MDUAL_H
#include "Molecule.h"


class MDual : public Molecule
{
    public:
        MDual(double _x, double _y, double _vx, double _vy, double _r, double _m) : Molecule::Molecule(_x,_y,_vx,_vy,_r,_m) {}
        virtual ~MDual();
        char show_name() { return l; }
    protected:
        char l = 'D';
    private:
};

#endif // MDUAL_H
