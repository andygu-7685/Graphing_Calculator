#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "random.h"
#include "..\constants.h"

using namespace std;

class Particle {
public:
    Particle(){}

    Particle(int totalS, int given_UID);



    void randSetup();


    void deflection();


    //collision between particles
    void collide(Particle& target);

    void repel(Particle& target);


    //verify collision between two object
    void collision(Particle& target);

    double get_H(double x, double y);





    void move();

    void rotate(int rateIn = 0);

    void draw(sf::RenderWindow& window);


    void set_Rvelo(double Vx, double Vy);
    void set_velo(double Vx, double Vy);

    sf::Vector2f get_velo(){ return velocity; }
    const sf::Vector2f get_velo()const { return velocity; }

    sf::Vector2f get_pos(){ return shape.getPosition(); }
    const sf::Vector2f get_pos()const { return shape.getPosition(); }

    double get_radius(){ return boxRadius; }
    const double get_radius()const { return boxRadius; }

    int get_UID(){ return UID; }
    const int get_UID()const { return UID; }

    double get_mass(){ return mass; }
    const double get_mass()const { return mass; }

    bool get_repel(){ return isRepel; }
    const bool get_repel()const { return isRepel; }
    void set_repel(bool statIn){ isRepel = statIn; }

    void assign_UID(int givenUID){ UID = givenUID; }

    void push_overlap( int overlapObjUID);
    void erase_overlap( int overlapObjUID);

    int searchUID( int search_this);



    string get_stat(int statLine);


private:
    sf::ConvexShape shape;
    sf::Vector2f velocity; 
    sf::Vector2f repelVelocity; 
    int sides;
    double boxRadius;
    int UID;
    vector<int> overlapUID;
    int rate;
    bool gravity;
    bool drag;
    bool inelastic;
    double mass;
    bool isRepel;
    bool wind;
    
};

#endif