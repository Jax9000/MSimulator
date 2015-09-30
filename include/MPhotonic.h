#ifndef MPHOTONIC_H
#define MPHOTONIC_H
#include "Molecule.h"

class MPhotonic : public Molecule
{
    public:
        MPhotonic(double _x, double _y, double _vx, double _vy, double _r) : Molecule(_x, _y, _vx, _vy, _r, 0) {};
        virtual ~MPhotonic();
        void update();
        char show_name() { return l; }

    protected:
        char l = 'P';
    private:
};

#endif // MPHOTONIC_H
