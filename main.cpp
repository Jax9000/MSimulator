#include <iostream>
#include <cmath>
#include "Molecule.h"
#include "Simulation.h"
#include "MArea.h"

using namespace std;

int main()
{
    Simulation *sim = new Simulation(30000);
    sim->Start();


    cout << "Hello world!" << endl;
    return 0;
}




/*
-Simulation
-MArea
-Molecule
-MNormal
-MDual
-MFissile
-MDualFissile
-MPhotonic
*/
