#ifndef GUARD_SYSTEM_H
#define GUARD_SYSTEM_H
/*
 * To Do:
 *	Check cross product
 *	implement random orientation
 *
 */

#include "vec3.h"

#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <boost/random.hpp>

#include <iostream>



class System {
 public:
  System(double dt, double vs, double alpha, double D, double Dr, int seed);
   
  // evolve in time
  void integrate(double t);


  double getPositionX() const { return position_.x; };
  double getPositionY() const { return position_.y; };
  double getPositionZ() const { return position_.z; };


 private:
  // set all positions of the particles to 
  void randomOrientation();


  // single time step
  void step(double dt);

	
  double dt_; // time step
  double vs_; // swim speed
  double alpha_; // tumble rate
  double D_; // diffusion constant
  double Dr_;// rotational diffusion constant

  Vec3 position_;
  Vec3 orientaion_;

  const boost::normal_distribution<double> ndist;
  boost::mt19937 rng;		
  boost::variate_generator<boost::mt19937&, boost::normal_distribution<double> > rndist;
};

System::System(double dt, double vs, double alpha, double D, double Dr, int seed)
    : dt_(dt), vs_(vs), alpha_(alpha_), D_(D), Dr_(Dr),
	  position_(), orientation_(),
      ndist(0., 1.), rng(seed), rndist(rng, ndist) 
{ randomOrientation(); };


void System::integrate(double t)
{
  while (t - dt_ > 0) {
    step(dt_); 
    t -= dt_;
  }
  step(t);
}

void System::step(double dt)
{
 
  r += vs * orientation_ * dt; 
  r.x += sqrt(2 * dt * D_) * rndist();
  r.y += sqrt(2 * dt * D_) * rndist();
  r.z += sqrt(2 * dt * D_) * rndist();

 
  Vec3 dp(0, 0, 0);
  Vec3 eta(rndist(), rndist(), rndist());

  dp.x = orientation_.y * eta_.z - orientation_.z * eta_.y;
  dp.y = orientation_.z * eta_.x - orientation_.x * eta_.z;
  dp.z = orientation_.x * eta_.y - orientation_.y * eta_.x;

  p = sqrt(2 * dt * Dr_) * dp;

}


void System::randomOrientation()
{

}




#endif //GUARD_SYSTEM_H
