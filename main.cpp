
#include "configFile.h"
#include "vec3.h"
#include "system.h"
#include "diffusion.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
  ConfigFile config("input.txt");
  double dt     = config.read<double>("dt");
  double vs     = config.read<double>("vs");
  double alpha  = config.read<double>("alpha");
  double D      = config.read<double>("D");
  double Dr     = config.read<double>("Dr");
  long int seed = config.read<long int>("seed");

  double totalTime = config.read<double>("totalTime");

  int ntime = config.read<int>("ntime");
  double sampleDt = config.read<double>("sampleDt");

  System system(dt, vs, alpha, D, Dr, seed);

  Diffusion msdX(ntime, sampleDt);
  Diffusion msdY(ntime, sampleDt);
  Diffusion msdZ(ntime, sampleDt);


  double time = 0;
  while( time < totalTime) {

	msdX.sample(system.getPositionX());
	msdY.sample(system.getPositionY());
	msdZ.sample(system.getPositionZ());

	system.integrate(sampleDt);

	
	time += sampleDt;
  }

  msdX.save("msdX.dat");	
  msdY.save("msdY.dat");	
  msdZ.save("msdZ.dat");	

  return 0;
}

