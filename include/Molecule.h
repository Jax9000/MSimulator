#ifndef MOLECULE_H
#define MOLECULE_H
#include <string>
#include <iostream>



class Molecule
{
    public:
        Molecule();
        Molecule(double _x, double _y);
        Molecule(double _x, double _y, double _vx, double _vy, double _r, double _m);
        ~Molecule();

        void set_velocity(double _vx, double _vy);
        void set_position(double _x, double _y);
        void set_radius(double _r);
        void set_mass(double _m);
        void set_label(int _n) {n=_n;}
        void set_name(std::string _name) { name = _name; }

        double show_x() const { return x; }
        double show_y() const { return y; }
        double show_vx() const { return vx; }
        double show_vy() const { return vy; }
        double show_r() const { return r; }
        double show_m() const { return m; }
        char show_type() const { return name[0]; }
        int show_label() { return n; }
        std::string show_name() const { return name; }
        virtual void update();
        void destroy() { delete this; }


        friend std::ostream & operator <<( std::ostream & s, const Molecule *M );



    protected:
        double x,y,vx,vy,r,m;
        int n;
        std::string name;
    private:

};

#endif // MOLECULE_H
