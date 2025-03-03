#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

const double epsilon = 1e-5;;

struct Vector2D {
    double x_coordinate, y_coordinate;
    
    Vector2D(double x = 0.0, double y = 0.0) : x_coordinate(x), y_coordinate(y) {}
    
    Vector2D operator+(const Vector2D &other) const {
        return Vector2D(x_coordinate + other.x_coordinate, y_coordinate + other.y_coordinate);
    }
    
    Vector2D operator-(const Vector2D &other) const {
        return Vector2D(x_coordinate - other.x_coordinate, y_coordinate - other.y_coordinate);
    }
    
    Vector2D &operator+=(const Vector2D &other) {
        x_coordinate += other.x_coordinate;
        y_coordinate += other.y_coordinate;
        return *this;
    }
    
    Vector2D operator*(double scalar) const {
            return Vector2D(x_coordinate * scalar, y_coordinate * scalar);
        }

        double Magnitude() const {
            return sqrt(x_coordinate * x_coordinate + y_coordinate * y_coordinate);
        }

        Vector2D Normalize() const {
            double magnitude = this->Magnitude();
            if (magnitude == 0) return Vector2D(1, 0);
            return Vector2D(x_coordinate / magnitude, y_coordinate / magnitude);
        }
    };

    class Ball {
    public:
        Vector2D position;
        Vector2D velocity;
        double radius;

        Ball(Vector2D pos, Vector2D vel, double rad) : position(pos), velocity(vel), radius(rad) {}

        void Update(double time_step) {
            position += velocity * time_step;
        }

        bool CheckCollision(double boundary_radius) {
            return position.Magnitude() + radius > boundary_radius;
        }

        void ResolveCollision(double boundary_radius) {
            if (position.Magnitude() == 0) return;
            Vector2D normalized_position = position.Normalize();
            position = normalized_position * (boundary_radius - radius);
            velocity = Vector2D(-velocity.x_coordinate, -velocity.y_coordinate);
        }
    };

    class Simulation {
    public:
        double simulation_boundary_radius;
        std::vector<Ball> balls;

        Simulation(double radius) : simulation_boundary_radius(radius) {}

        void AddBall(Vector2D pos, Vector2D vel, double rad) {
            balls.emplace_back(pos, vel, rad);
        }

        void Run(int steps, double delta_time = 0.1) {
            for (int i = 0; i < steps; i++) {
                for (auto& ball : balls) {
                    ball.Update(delta_time);
                    if (ball.CheckCollision(simulation_boundary_radius)) {
                        ball.ResolveCollision(simulation_boundary_radius);
                    }
                }
            }
        }
    };

    int main() {
        double boundary_radius = 100.0;
        double delta_time = 0.1;
        Simulation sim(boundary_radius);

        // TEST
        sim.AddBall(Vector2D(0, 0), Vector2D(10, 10), 10);
        assert(sim.balls.size() == 1 && "Ball should be added to the simulation");
        // TEST_END

        // TEST
        sim.balls[0].Update(delta_time);
        assert(sim.balls[0].position.x_coordinate == 1 && sim.balls[0].position.y_coordinate == 1 && "Ball should move correctly");
        // TEST_END

        // TEST
        sim.AddBall(Vector2D(boundary_radius - 10, 0), Vector2D(0, 0), 10);
        sim.balls[1].Update(delta_time);
        assert(!sim.balls[1].CheckCollision(boundary_radius) && "Ball on edge should not collide");
        // TEST_END

        // TEST
        sim.AddBall(Vector2D(boundary_radius - 10, 0), Vector2D(50, 0), 10);
        sim.balls[2].Update(delta_time);
        assert(sim.balls[2].CheckCollision(boundary_radius) && "Ball should detect collision");
        sim.balls[2].ResolveCollision(boundary_radius);
        assert(fabs(sim.balls[2].position.x_coordinate + 10 - boundary_radius) < epsilon && "Collision should be resolved correctly");
        // TEST_END
        
        // TEST
        sim.AddBall(Vector2D(boundary_radius - 20, 0), Vector2D(-10, 0), 10);
        sim.balls[3].Update(delta_time);
        assert(!sim.balls[3].CheckCollision(boundary_radius) && "Ball moving away should not collide");
        // TEST_END
        
        // TEST
        double initial_velocityX = sim.balls[2].velocity.x_coordinate;
        sim.balls[2].ResolveCollision(boundary_radius);
        assert(sim.balls[2].velocity.x_coordinate == -initial_velocityX && "Velocity should be reflected correctly");
        // TEST_END
        
        // TEST
        sim.Run(1, delta_time);
        assert(sim.balls.size() == 4 && "Simulation should handle multiple balls correctly");
        // TEST_END
        
        return 0;
    }

