#include <iostream>
#include <cmath>
#include <stdexcept>

const double g = 9.81;

struct Vector2D 
{
    double x, y;

    Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    double distance() const {
        return x;
    }
};

class Projectile 
{
    
public:
    double initial_velocity;
    double launch_angle;
    Vector2D position;

    Projectile(double velocity, double angle)
    {
        if (velocity < 0) {
            throw std::invalid_argument("Initial velocity cannot be negative.");
        }
        
        if (angle < 0 || angle > 180) {
            throw std::invalid_argument("Launch angle must be between 0 and 180 degree.");
        }
        
        initial_velocity = velocity;
        launch_angle = angle;
        position = Vector2D(0, 0);
    }
    
    void UpdatePosition(double time) 
    {
        double angle_rad = launch_angle * M_PI / 180.0;
        position.x = initial_velocity * cos(angle_rad) * time;
        position.y = initial_velocity * sin(angle_rad) * time - 0.5 * g * time * time;
    }

    double CalculateDistance() const {
        return position.distance();
    }
};

class ProjectileSimulation 
{
    
public:
    Projectile projectile;
    double target_distance;

    ProjectileSimulation(double velocity, double angle, double target)
        : projectile(velocity, angle), target_distance(target) {
            if (target < 0) {
                throw std::invalid_argument("Target distance cannot be negative.");
            }
        }

    bool RunSimulation() 
    {
        double time = 0.0;
        const double time_step = 0.1;
        while (projectile.position.y >= 0)
        {
            projectile.UpdatePosition(time);
            if (projectile.CalculateDistance() >= target_distance) {
                return true;
            }
            time += time_step;
        }
        return false;
    }
};

#include <cassert>

int main() {
    // TEST
    {
        ProjectileSimulation sim(50, 45, 150);
        bool result = sim.RunSimulation();
        assert(result && "Projectile should hit the target at 150m");
    }
    // TEST_END

    // TEST
    {
        ProjectileSimulation sim(0, 45, 10);
        bool result = sim.RunSimulation();
        assert(!result && "Projectile with zero initial velocity should not hit any target");
    }
    // TEST_END

    // TEST
    {
        ProjectileSimulation sim(30, 180, 1);
        bool result = sim.RunSimulation();
        assert(!result && "Projectile launched horizontally should not cover vertical distance");
    }
    // TEST_END
    
    // TEST 3
    {
        ProjectileSimulation sim(30, 90, 1);
        bool result = sim.RunSimulation();
        assert(!result && "Projectile launched vertically should not cover horizontal distance");
    }
    // TEST_END

    // TEST
    {
        ProjectileSimulation sim(30, 75, 20);
        bool result = sim.RunSimulation();
        assert(result && "Projectile should hit the target at 20m");
    }
    // TEST_END

    // TEST
    {
        ProjectileSimulation sim(50, 45, 300);
        bool result = sim.RunSimulation();
        assert(!result && "Projectile should not hit a target at 300m with given initial velocity and angle");
    }
    // TEST_END
    
    // TEST
    try {
        ProjectileSimulation sim(-10, 45, 100);
        sim.RunSimulation();
    } catch (const std::invalid_argument &e) {
        assert(std::string(e.what()) == "Initial velocity cannot be negative." && "Exception for negative velocity caught as expected.");
    }
    // TEST_END
    
    // TEST
    try {
        ProjectileSimulation sim(10, 1, 100);
        sim.RunSimulation();
    } catch (const std::invalid_argument &e) {
        assert(std::string(e.what()) == "Launch angle must be between 0 and 180 degree." && "Exception for invalid angle caught as expected.");
    }
    // TEST_END
    
    // TEST
    try {
        ProjectileSimulation sim(10, 45, -100);
        sim.RunSimulation();
    } catch (const std::invalid_argument &e) {
        assert(std::string(e.what()) == "Target distance cannot be negative." && "Exception for negative target distance caught as expected.");
    }
    // TEST_END
    
    return 0;
}


