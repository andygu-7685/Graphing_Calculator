#include "particle.h"













    Particle::Particle(int totalS, int given_UID){
        sides = totalS;
        rate = sides;
        gravity = true;
        drag = true;
        wind = true;
        inelastic = false;
        isRepel = false;
        assign_UID(given_UID);
        randSetup();
    }



    void Particle::randSetup(){
        Random r;
        shape = sf::ConvexShape(sides);
        int distance = r.Next(20,55);
        boxRadius = distance + 10;
        mass = pi * pow(distance, 2) * 10;

        //set all vertex
        for (int i = 0; i < sides; i++) {
            float angle = i * (2 * pi) / sides - pi / 2; // Adjust to start from the top vertex
            float xpos = distance * cos(angle);
            float ypos = distance * sin(angle);
            shape.setPoint(i, sf::Vector2f(xpos, ypos));
        }


        // set random velocity != 0;
        sf::Vector2f newVelo = sf::Vector2f(r.Next(-5, 5), r.Next(-5, 5));
        while(newVelo.x == 0 && newVelo.y == 0)
            newVelo = sf::Vector2f(r.Next(-1, 1), r.Next(-1, 1));

        velocity = newVelo;
        shape.setPosition(r.Next(30, 501), r.Next(30, 501));
        shape.setFillColor(sf::Color(r.Next(0, 255), r.Next(0, 255), r.Next(0, 255)));
    }


    void Particle::deflection(){
        Random r;
        sf::Vector2f pos = shape.getPosition();
        double rVal = 1; // ((r.Next(1, 2) - 1) / 100.0);

        if(gravity)        
            velocity = sf::Vector2f(velocity.x, velocity.y + GRAVITY);                     //gravity

        if(wind && shape.getPosition().x > 450 && shape.getPosition().x < 550)
            velocity = sf::Vector2f(velocity.x + ((r.Next(0, 10) - 5) / 10.0), velocity.y - 0.08);

        if(drag)
            velocity = sf::Vector2f(velocity.x - (FRICTION_COEF * velocity.x), velocity.y - (FRICTION_COEF * velocity.y));     //drag coef
        
        
        if(isRepel){
            if ((pos.x + boxRadius) >= SIDEB_X - 0){
                shape.setPosition(sf::Vector2f(SIDEB_X - boxRadius - 5, shape.getPosition().y));
                repelVelocity = sf::Vector2f(-1, 0);
            }
            else if ((pos.x - boxRadius) <= 0){
                shape.setPosition(sf::Vector2f(boxRadius + 5, shape.getPosition().y));
                repelVelocity = sf::Vector2f(1, 0);
            }
            
            if ((pos.y + boxRadius) >= SCREEN_HEIGHT - 0){
                shape.setPosition(sf::Vector2f(shape.getPosition().x, SCREEN_HEIGHT - boxRadius - 5));
                repelVelocity = sf::Vector2f(0, -1);
            }
            else if ((pos.y - boxRadius) <= 0){
                shape.setPosition(sf::Vector2f(shape.getPosition().x, boxRadius + 5));
                repelVelocity = sf::Vector2f(0, 1);
            }
        }
        else{
            if ((pos.x + boxRadius) >= SIDEB_X - 0)
                velocity = sf::Vector2f(-rVal * velocity.x, rVal * velocity.y);
            if ((pos.x - boxRadius) <= 0)
                velocity = sf::Vector2f(-rVal * velocity.x, rVal * velocity.y);
            if ((pos.y + boxRadius) >= SCREEN_HEIGHT - 0){
                velocity = sf::Vector2f(rVal * velocity.x, -rVal * velocity.y);
                if(inelastic)        //each bounce consume energy: mostly apply when gravity
                    velocity = sf::Vector2f(velocity.x, velocity.y - (COLLISION_COEF * velocity.y));
            }
            if ((pos.y - boxRadius) <= 0)
                velocity = sf::Vector2f(rVal * velocity.x, -rVal * velocity.y);
        }



    }


    //collision between particles
    void Particle::collide(Particle& target){
        if(inelastic)            //each bounce consume energy
            velocity = sf::Vector2f(velocity.x - (COLLISION_COEF * velocity.x), velocity.y - (COLLISION_COEF * velocity.y));
        
        double m1 = mass;
        double m2 = target.get_mass();

        double V1ix = velocity.x;
        double V1iy = velocity.y;
        double V2ix = target.get_velo().x;
        double V2iy = target.get_velo().y;

        double V1fx = V1ix + ((2 * m2) / (m1 + m2)) * (V2ix - V1ix);
        double V1fy = V1iy + ((2 * m2) / (m1 + m2)) * (V2iy - V1iy);
        double V2fx = V2ix + ((2 * m1) / (m1 + m2)) * (V1ix - V2ix);
        double V2fy = V2iy + ((2 * m1) / (m1 + m2)) * (V1iy - V2iy);

        velocity = sf::Vector2f( V1fx, V1fy);
        target.set_velo(V2fx, V2fy);
    }

    void Particle::repel(Particle& target){
        isRepel = true;
        target.set_repel(true);
        sf::Vector2f this_pos = shape.getPosition();
        sf::Vector2f target_pos = target.get_pos();
        double xdiff = this_pos.x - target_pos.x;
        double ydiff = this_pos.y - target_pos.y;
        double Hdiff = get_H(xdiff, ydiff);
        double sinH = ydiff / Hdiff;
        double cosH = xdiff / Hdiff;
        double Vrepel = 3;
        repelVelocity = sf::Vector2f(Vrepel * cosH, Vrepel * sinH);
        target.set_Rvelo(-Vrepel * cosH, -Vrepel * sinH);
    }


    //verify collision between two object
    void Particle::collision(Particle& target){
        Random r;
        sf::Vector2f this_pos = shape.getPosition();
        sf::Vector2f target_pos = target.get_pos();
        double xdiff = fabs(target_pos.x - this_pos.x);
        double ydiff = fabs(target_pos.y - this_pos.y);
        sf::Vector2f target_velo = target.get_velo();
        //true if same sign
        double actualRadius = get_H(xdiff, ydiff);


        if(actualRadius < boxRadius && searchUID(target.get_UID()) == -1){
            //shape.setFillColor(sf::Color(r.Next(0, 255), r.Next(0, 255), r.Next(0, 255)));
            collide(target);
            push_overlap(target.get_UID());
            target.push_overlap(UID);
        }
        else if(actualRadius > (boxRadius + 5) && searchUID(target.get_UID()) != -1){
            isRepel = false;
            target.set_repel(false);
            erase_overlap(searchUID(target.get_UID()));
            target.erase_overlap(target.searchUID(UID));
        }
        else if(actualRadius < (boxRadius - 5) && searchUID(target.get_UID()) != -1 && !isRepel){
            repel(target);
        }
        // else if(overlapUID.empty()){
        //     isRepel = false;
        // }
    }

    double Particle::get_H(double x, double y){
        return pow(pow(x, 2) + pow(y, 2), 1/2.0);
    }





    void Particle::move(){
        if(isRepel){
            shape.move(repelVelocity);
        }
        else{
            shape.move(velocity);
        }
    }

    void Particle::rotate(int rateIn){
        rate = static_cast<int>(pow(pow(velocity.x, 2) + pow(velocity.y, 2), 1/2.0)) / 2;
        shape.rotate(rate);
    }

    void Particle::draw(sf::RenderWindow& window){
        window.draw(shape);
    }


    void Particle::set_Rvelo(double Vx, double Vy){
        repelVelocity = sf::Vector2f(Vx, Vy);
    }
    void Particle::set_velo(double Vx, double Vy){
        velocity = sf::Vector2f(Vx, Vy);
    }


    void Particle::push_overlap( int overlapObjUID){ 
        overlapUID.push_back(overlapObjUID);
    }

    void Particle::erase_overlap( int overlapObjUID){
        overlapUID.erase(overlapUID.begin() + overlapObjUID);
    }

    int Particle::searchUID( int search_this){
        for(int i = 0; i < overlapUID.size(); i++){
            if(overlapUID[i] == search_this)
                return i;
        }
        return -1;
    }



    string Particle::get_stat(int statLine){
        switch(statLine){
            case 1:
                return "UID: " + to_string(UID);
                break;
            case 2:
                return "isRepel: " + to_string(isRepel);
                break;
            case 3:
                if(isRepel){
                    return "RepelUID: " + overlapUID[0];
                }
                else{
                    return "RepelUID: ";
                }
                break;
            default:
                return "";
                break;
        }
    }






