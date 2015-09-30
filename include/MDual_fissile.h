#ifndef MDUAL_FISSILE_H
#define MDUAL_FISSILE_H
#include "Molecule.h"


class MDual_fissile : public Molecule
{
    public:
        MDual_fissile(double _x, double _y, double _vx, double _vy, double _r, double _m) : Molecule::Molecule(_x,_y,_vx,_vy,_r,_m) {};

        template <class T>
        MDual_fissile(T *M1, T *M2)
        {
            name = M1->show_name();
            x = (M1->show_x() + M2->show_x())/2;
            y = (M1->show_y() + M2->show_y())/2;
            vx = M1->show_vx() + M2->show_vx();
            vy = M1->show_vy() + M2->show_vy();
            m = M1->show_m() + M2->show_m();
            r = M1->show_r();
            if (m>1) m=1;
        }
        char show_name() { return l; }

        virtual ~MDual_fissile();

    protected:
        char l = 'B';
    private:
};

#endif // MDUAL_FISSILE_H
