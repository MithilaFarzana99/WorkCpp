#include <iostream>
#include <cmath>

class BounceBall {
public:
    class Particle {
    public:
        double position;
        double velocity;
        double acceleration;

        Particle(double pos, double vel, double acc)
            : position(pos), velocity(vel), acceleration(acc) {}

        void update(double delta_time) {
            position += velocity * delta_time + 0.5 * acceleration * pow(delta_time, 2);
            velocity += acceleration * delta_time;
        }
    };

    Particle ball;
    double time_step;
    int total_steps;

    BounceBall(double pos, double vel, double acc, double delta_time, int steps)
        : ball(pos, vel, acc), time_step(delta_time), total_steps(steps) {}

    void RunSimulation() {
        for (int i = 0; i < total_steps; ++i) {
            ball.update(time_step);
        }
    }

    double get_final_position() { return ball.position; }
    double get_final_velocity() { return ball.velocity; }
};

#include <cassert>

int main() 
{
    // TEST
    BounceBall sim1(0.0, 0.0, 0.0, 0.1, 10);
    sim1.RunSimulation();
    assert(sim1.ball.position == 0.0 && sim1.ball.velocity == 0.0);
    // TEST_END
    
    // TEST
    BounceBall sim2(0.0, 100.0, -9.81, 0.1, 10);
    sim2.RunSimulation();
    double expected_final_velocity = 100.0 - 9.81 * 1.0;
    assert(fabs(sim2.get_final_velocity() - expected_final_velocity) < 0.5);
    // TEST_END
    
    // TEST
    BounceBall sim3(-10.0, 0.0, 9.81, 0.1, 10);
    sim3.RunSimulation();
    assert(sim3.ball.position > -10.0);
    // TEST_END
    
    return 0;
}
