#include "Simulation.h"
#include "MArea.h"
#include "Molecule.h"
#include "MNormal.h"
#include "MDual.h"
#include "MPhotonic.h"
#include "MDual_fissile.h"
#include "MFissile.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>


Simulation::Simulation(int i)
{
    iteration = i;
}

void Simulation::Start()
{
    std::vector <Molecule*> container;
    int iterations, X, Y;
    double T[6];
    string name;
    std::fstream input;
    input.open("In.txt",std::ios::in);


    input >> X >> Y >> iterations;

    while( true )
    {
        input >> name;
        for(int i=0; i<5; i++)
        input >> T[i];

        if(name[0]=='P')
        {
            MPhotonic *photonic = new MPhotonic(T[0],T[1],T[2],T[3],T[4]);
            photonic->set_name(name);
            container.push_back(photonic);
        }
        else
        {
            input >> T[5];
            if(name[0]=='N')
            {
                MNormal *normal = new MNormal(T[0],T[1],T[2],T[3],T[4],T[5]);
                normal->set_name(name);
                container.push_back(normal);
            }
            else if(name[0]=='D')
            {
                MDual *dual = new MDual(T[0],T[1],T[2],T[3],T[4],T[5]);
                dual->set_name(name);
                container.push_back(dual);
            }
            else if(name[0]=='B')
            {
                MDual_fissile *dual_fissile = new MDual_fissile(T[0],T[1],T[2],T[3],T[4],T[5]);
                dual_fissile->set_name(name);
                container.push_back(dual_fissile);
            }
            else if(name[0]=='F')
            {
                MFissile *fissile = new MFissile(T[0],T[1],T[2],T[3],T[4],T[5]);
                fissile->set_name(name);
                container.push_back(fissile);
            }
        }

        if( !(input.good()) ) // odczytuj dopoki nie ma EOF
        break;
    }
    input.close();


    MArea *AREA = new MArea();
    int molecules = container.size();



    std::fstream file;
    file.open("Out.txt",std::ios::out);
    file.setf(cout.fixed);

    file << X << " " << Y << " " << iterations << std::endl;


    for(int _i=1; _i<=iterations; _i++)
    {

        std::cout << container.size() << std::endl;
        for(int i=0; i<molecules; i++)
            AREA->run(container[i]);

        for(int i=0; i<molecules; i++)
            if( (AREA->x < ( std::abs(container[i]->show_x()) + container[i]->show_r() )) || (AREA->y < ( std::abs(container[i]->show_y()) + container[i]->show_r() )) )
            AREA->hit_wall(container[i]);

        file << "t" << (_i) << "\n\n";

        for(int i=0; i<molecules; i++)
        {
            file << container[i] << std::endl;
            //file << V1[0]->show_y() << std::endl;
        }
            file << std::endl;

        bool guard=1;

        for(int i=0; i<molecules-1; i++)
            for(int j=i+1; j<molecules; j++)
                if ( sqrt( (container[i]->show_x()-container[j]->show_x())*(container[i]->show_x()-container[j]->show_x()) +
                    (container[i]->show_y()-container[j]->show_y())*(container[i]->show_y()-container[j]->show_y()) ) < container[i]->show_r()+container[j]->show_r())
                {//IF
                    if(guard==1)
                    {
                        file << "k" << (_i) << "\n";
                        guard=0;
                    }

                    AREA->colision(container[i],container[j]);
                    file << container[i]->show_name() << " " << container[j]->show_name() << std::endl;
                    //std::cout << typeid(V1[i]).name();

                    bool stra = 1;
                    if(AREA->isdual_fissile(container[i]))
                    {

                        MFissile *mfs = new MFissile(container[i]);
                        MFissile *mfs1 = new MFissile(container[i]);
                        mfs->set_velocity(mfs->show_vx(),mfs->show_vy());
                        container[i]->destroy();
                        container.erase(container.begin()+i);
                        container.push_back(mfs);
                        mfs1->set_velocity(mfs1->show_vx()*(-1),mfs1->show_vy());
                        mfs1->set_position((mfs1->show_x()+mfs1->show_vx())*2*mfs1->show_r(),(mfs1->show_y()+mfs1->show_vy())*2*mfs1->show_r());
                        container.push_back(mfs1);
                        molecules=container.size();
                        std::cout << "WOW\n";
                        stra=0;
                    }

                    if(AREA->isdual_fissile(container[j]))
                    {
                        MFissile *mfs = new MFissile(container[j]);
                        MFissile *mfs1 = new MFissile(container[j]);
                        mfs->set_velocity(mfs->show_vx(),mfs->show_vy());
                        container[j]->destroy();
                        container.erase(container.begin()+j);
                        container.push_back(mfs);
                        mfs1->set_velocity(mfs1->show_vx()*(-1),mfs1->show_vy());
                        mfs1->set_position((mfs1->show_x()+mfs1->show_vx())*2*mfs1->show_r(),(mfs1->show_y()+mfs1->show_vy())*2*mfs1->show_r());
                        container.push_back(mfs1);
                        molecules=container.size();
                        std::cout << "WOW\n";
                        stra=0;
                    }

                    if(AREA->isfissile(container[i],container[j]) && stra==1)
                    {

                        //metode sprawdzajac typ w area
                        MDual_fissile *mdf = new MDual_fissile(container[i],container[j]);
                        //container[i]->destroy();
                        //container[j]->destroy();
                        container.erase(container.begin()+j);
                        container.erase(container.begin()+i);
                        container.push_back(mdf);
                        molecules=container.size();


                    }
                    stra=1;

                }//IF

                if(guard==0)
                    file << std::endl;




        for(int i=0; i<molecules-1; i++)
            for(int j=i+1; j<molecules; j++)
                if ( sqrt( (container[i]->show_x()-container[j]->show_x())*(container[i]->show_x()-container[j]->show_x()) +
                           (container[i]->show_y()-container[j]->show_y())*(container[i]->show_y()-container[j]->show_y()) ) < 2 )
                            AREA->pull(container[i],container[j]);

        for(int i=0; i<molecules; i++)
        if(container[i]->show_m()==0 && !(AREA->isphotonic(container[i])))
        {
            container.erase(container.begin()+i);
            molecules=container.size();
        }



    }


}


Simulation::~Simulation()
{
    //dtor
}
