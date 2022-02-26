#ifndef GUARD_SYSTEM_H
#define GUARD_SYSTEM_H
/*
 * To Do:
 *	Check cross product
 *	implement random orientation
 *	implement tumble
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
  void normalizeOrientation();


  // single time step
  void step(double dt);

	
  double dt_; // time step
  double vs_; // swim speed
  double alpha_; // tumble rate
  double D_; // diffusion constant
  double Dr_;// rotational diffusion constant

  Vec3 position_;
  Vec3 orientation_;

  const boost::normal_distribution<double> ndist;
  boost::mt19937 rng;		
  boost::variate_generator<boost::mt19937&, boost::normal_distribution<double> > rndist;
};

System::System(double dt, double vs, double alpha, double D, double Dr, int seed)
    : dt_(dt), vs_(vs), alpha_(alpha), D_(D), Dr_(Dr),
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
 
  position_ += vs_ * orientation_ * dt; 
  position_.x += sqrt(2 * dt * D_) * rndist();
  position_.y += sqrt(2 * dt * D_) * rndist();
  position_.z += sqrt(2 * dt * D_) * rndist();

 
  Vec3 dp(0, 0, 0);
  Vec3 eta(rndist(), rndist(), rndist());

  dp.x = orientation_.y * eta.z - orientation_.z * eta.y;
  dp.y = orientation_.z * eta.x - orientation_.x * eta.z;
  dp.z = orientation_.x * eta.y - orientation_.y * eta.x;

  orientation_ += sqrt(2 * dt * Dr_) * dp;

  normalizeOrientation();

}


void System::randomOrientation()
{
  orientation_.x = 1.; 
  orientation_.y = 0.; 
  orientation_.z = 0.; 
  double dt = 1e-3;
  double t = 0;
  while ( t < 10 * Dr_) {
    Vec3 dp(0, 0, 0);
    Vec3 eta(rndist(), rndist(), rndist());

    dp.x = orientation_.y * eta.z - orientation_.z * eta.y;
    dp.y = orientation_.z * eta.x - orientation_.x * eta.z;
    dp.z = orientation_.x * eta.y - orientation_.y * eta.x;

    orientation_ += sqrt(2 * dt * Dr_) * dp;
	normalizeOrientation();
	t += dt;
  }

}


void System::normalizeOrientation()
{
	double l = 0;
	l += orientation_.x * orientation_.x;
	l += orientation_.y * orientation_.y;
	l += orientation_.z * orientation_.z;

	orientation_ /= sqrt(l);

}


#endif //GUARD_SYSTEM_H
