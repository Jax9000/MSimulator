#ifndef MAREA_H
#define MAREA_H
#include "Molecule.h"
#include <iostream>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <typeinfo>
#include "MDual.h"
#include "MPhotonic.h"
#include "MFissile.h"
using namespace std;

class MArea
{
    public:
        MArea();
        MArea(double a, double b);
        virtual ~MArea();
        void run(Molecule *M);

        template<class T>
        void hit_wall(T *M)
        {
            if( this->x <= ( std::abs(M->show_x()) + M->show_r() ) )
            {
                if( M->show_x() > 0)
                {
                    M->set_velocity((-1)*(M->show_vx()), M->show_vy());
                    M->set_position((this->x - M->show_r() + M->show_vx()/100), M->show_y());
                }
                else
                {
                M->set_velocity((-1)*(M->show_vx()), M->show_vy());
                M->set_position((-1)*(this->x) + M->show_r() + M->show_vx()/100, M->show_y() );
                }
            }
            if ( this->y <= ( std::abs(M->show_y()) + M->show_r()) )
            {
                if( M->show_y() > 0)
                {
                    M->set_velocity(M->show_vx(), (-1)*(M->show_vy()));
                    M->set_position(M->show_x(), this->y - M->show_r() + M->show_vy()/100);
                }
                else
                {
                    M->set_velocity(M->show_vx(), (-1)*(M->show_vy()));
                    M->set_position(M->show_x(), (-1)*(this->y) + M->show_r() + M->show_vy()/100 );
                }
            }
        }

        template<class T1, class T2>
        void colision(T1 *M1, T2 *M2)
        {
            M1->set_velocity(M1->show_vx()*(-1),M1->show_vy()*(-1));
            M2->set_velocity(M2->show_vx()*(-1),M2->show_vy()*(-1));
            M1->set_position(M1->show_x()+M1->show_vx()/100, M1->show_y()+M1->show_vy()/100);
            M2->set_position(M2->show_x()+M2->show_vx()/100, M2->show_y()+M2->show_vy()/100);


            srand(time(0));
            double mass=M1->show_m()+M2->show_m();

            if(M1->show_m() == M2->show_m()==1.0);
            else
            {
                mass*=10;
                double mass1=rand()%((int)mass+1);

                while(mass1>10 || (mass-mass1)>10)
                    mass1=rand()%((int)mass+1);

                mass1=1.0*(mass1/10);
                M1->set_mass(mass1);
                mass/=10;
                M2->set_mass(mass - mass1);
            }


            if(typeid(*M1).name()==typeid(MDual).name())
            {
                int radius = rand()%6;
                srand(time(0));
                while(radius==0)
                    radius = rand()%6;
                double _rad = 1.0 * radius/10;
                M1->set_radius(_rad);
                //std::cout << " HEJO\n";
            }

            if (typeid(*M2).name()==typeid(MDual).name())
            {
                int radius = rand()%6;
                srand(time(0));
                while(radius==0)
                    radius = rand()%6;
                double _rad = 1.0 * radius/10;
                M2->set_radius(_rad);
                //std::cout << " HEJO\n";
            }

        }

        template<class T1, class T2>
        double distanceX(T1 *M1, T2 *M2) { return std::abs(M1->show_x()-M2->show_x()); }

        template<class T,class T1>
        double distanceY(T *M1, T1 *M2) { return std::abs(M1->show_y()-M2->show_y()); }

        template <class T1, class T2>
        void pull(T1 *M1, T2 *M2)
        {

            if( typeid(*M1).name()==typeid(MPhotonic).name() || typeid(*M2).name()==typeid(MPhotonic).name());
                //cout << "photonic\n";
            else
            {
                double k = sqrt( distanceX(M1,M2)*distanceX(M1,M2) + distanceY(M1,M2)*distanceY(M1,M2) * 10 );
                double v = M1->show_m() * M2->show_m() * k * std::max(2-k,0.0);
                double vx = distanceX(M1,M2)/k*v;
                double vy = distanceY(M1,M2)/k*v;
                double _vx = (M1->show_x() < M2->show_x()) ? vx : (-1)*vx;
                double _vy = (M1->show_y() < M2->show_y()) ? vy : (-1)*vy;
                M1->set_velocity(M1->show_vx()+_vx, M1->show_vy()+_vy);
                _vx*=(-1);
                _vy*=(-1);
                M2->set_velocity(M2->show_vx()+_vx, M2->show_vy()+_vy);
                //cout << "PULL\n" << endl;
            }

        }
        template <class T1, class T2>
        bool isfissile(T1 *M1, T2 *M2)
        {
            if(typeid(*M1).name() == typeid(MFissile).name() && typeid(*M2).name() == typeid(MFissile).name())
               return 1;
               else
                return 0;
        }

        template <class T>
        bool isdual_fissile(T *M1)
        {
            if(typeid(*M1).name() == typeid(MDual_fissile).name())
                return 1;
            else
                return 0;
        }

        template <class T>
        bool isphotonic(T *M1)
        {
            if(typeid(*M1).name() == typeid(MPhotonic).name())
                return 1;
            else
                return 0;
        }






        double x,y;



    protected:
        //int x,y;
    private:
};

#endif // MAREA_H
