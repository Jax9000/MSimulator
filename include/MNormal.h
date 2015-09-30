#ifndef MNORMAL_H
#define MNORMAL_H
#include "Molecule.h"

class MNormal : public Molecule
{
    public:
        MNormal(double _x, double _y, double _vx, double _vy, double _r, double _m) : Molecule::Molecule(_x,_y,_vx,_vy,_r,_m) {};
        virtual ~MNormal();
        char show_name() { return l; }
    protected:
        char l = 'N';
    private:
};

#endif // MNORMAL_H
