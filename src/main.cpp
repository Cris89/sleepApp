#include <chrono>
#include <random>
#include <thread>
#include <math.h>
#include <iostream>
#include <fstream>

#include "tesiCris_margot_manager.hpp"



void go_to_bed(int sleepTime)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
}



int main()
{
	std::ofstream f;
	f.open( "/home/cris/Documents/serial.txt", std::ofstream::out | std::ofstream::app );
	f << "param1 param2 param3\n";

	std::chrono::steady_clock::time_point tStart = std::chrono::steady_clock::now();

	// amount of milliseconds for go_to_bed() function (computed at runtime)
	int sleepTime;

	// error variable (computed at runtime)
	long double error;

	// noise generation for sleepTime (--> avg_throughput)
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	std::gamma_distribution<double> distribution( 1, 0.3 );

	float errorPercentage = 0.1;

	// application knobs
	int param1;
	int param2;
	int param3;

	std::vector< std::vector<int> > configurations = {	{1,2,3}, 
														{11,22,33}, 
														{111,222,333} };

	int numOPs = 1;

	for(int n = 0; n < numOPs; n++)
	{
		for(int i = 0; i < configurations.size(); i++)
		{
			param1 = configurations[i][0];
			param2 = configurations[i][1];
			param3 = configurations[i][2];

			f << param1 << " " << param2 << " " << param3 << "\n";

			sleepTime  = round( 
								( +7.35 * log(param1) ) + 
								( +38.1 * param2 ) +
								( +52.96 * sqrt(param3) ) );

			sleepTime += round( sleepTime * errorPercentage * distribution(generator) );



			error = 1 / (
							( +0.015 * sqrt(param1) ) + 
							( +0.033 * log(param2) ) +
							( +0.028 * log(param3) )
						);



			std::cout << "\n\n\nparam1 = " << param1 << std::endl;
			std::cout << "param2 = " << param2 << std::endl;
			std::cout << "param3 = " << param3 << std::endl;
			std::cout << "\n\t...zzz... sleeping for " << sleepTime << " milliseconds ...zzz...\n\n\n" << std::endl;
			go_to_bed(sleepTime);
		}
	}

	std::chrono::steady_clock::time_point tStop = std::chrono::steady_clock::now();

	uint64_t delta = std::chrono::duration_cast<std::chrono::microseconds>(tStop - tStart).count();

	f << "\n\n\nExecution time: " << delta << " microseconds" << std::endl;

	f.close();
}