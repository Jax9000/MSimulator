#ifndef MFISSILE_H
#define MFISSILE_H
#include "Molecule.h"
#include "MDual_fissile.h"

class MFissile : public Molecule
{
    public:
        MFissile() {};
        template <class T>
        MFissile(T *M1)
        {
            name = M1->show_name();
            this->set_position(M1->show_x(), M1->show_y());
            this->set_velocity(M1->show_vx(), M1->show_vy());
            this->set_mass((M1->show_m())/2);
            this->set_radius(M1->show_r());
        }

        MFissile(double _x, double _y, double _vx, double _vy, double _r, double _m) : Molecule::Molecule(_x,_y,_vx,_vy,_r,_m) {}
        virtual ~MFissile();
        char show_name() { return l; }

    protected:
        char l='F';
    private:
};

#endif // MFISSILE_H
