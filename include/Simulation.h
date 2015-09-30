#ifndef SIMULATION_H
#define SIMULATION_H


class Simulation
{
    public:
        Simulation(int i);
        virtual ~Simulation();
        void set_iterations(int i) { iteration = i; }
        void Start();
    protected:
    private:
        int iteration;
};

#endif // SIMULATION_H
