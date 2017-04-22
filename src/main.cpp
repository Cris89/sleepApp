#include <chrono>
#include <thread>
#include <math.h>

#include "tesiCris_margot_manager.hpp"



void go_to_bed (int sleepTime)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
}

// error variable (computed at runtime)
double error;

int main()
{
	// variable for throughput monitor
	int num_threads = 1;

	// amount of milliseconds for go_to_bed function
	int sleepTime;

	

	// tesiCris and margot initialization
	tesiCris_Margot_Manager tmm;
	tmm.init();

	// application knobs
	int param1;
	int param2;
	int param3;

	std::chrono::time_point<std::chrono::steady_clock> duration = std::chrono::steady_clock::now() + std::chrono::minutes(100);

	while (std::chrono::steady_clock::now() < duration)
	{
		// if new OPs are sent by the server_handler, the margot OP list is updated
		tmm.updateOPs();

		//check if the configuration is different wrt the previous one
		//NOTE: trials is an output parameter!
		if (margot::sleeping::update(param1, param2, param3))
		{
			//Writing the "trials" variable is enough to change configuration
			margot::sleeping::manager.configuration_applied();
		}
		//monitors wrap the autotuned function
		margot::sleeping::start_monitor();

		sleepTime = ( 10000 * log(param1) ) + 
					( 50 * param2 ) +
					( 500 + sqrt(param3) );

		go_to_bed(sleepTime);

		// funzione che mi calcola l'errore

		error = float(1) / 666;

		margot::sleeping::stop_monitor( num_threads, error );
		//print values to file
		margot::sleeping::log();

		// the OP is sent to the server_handler
		tmm.sendResult( { param1, param2, param3 }, { margot::sleeping::avg_error, margot::sleeping::avg_throughput } );
	}
}
