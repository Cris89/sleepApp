#include <chrono>
#include <thread>
#include <math.h>

#include "tesiCris_margot_manager.hpp"



void go_to_bed(int sleepTime)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
}



int main()
{
	// variable for throughput monitor
	int num_threads = 1;

	// amount of milliseconds for go_to_bed() function (computed at runtime)
	int sleepTime;

	// error variable (computed at runtime)
	long double error;

	// tesiCris and margot initialization
	tesiCris_Margot_Manager tmm;
	tmm.init();

	// application knobs
	int param1;
	int param2;
	int param3;

	std::chrono::time_point<std::chrono::steady_clock> duration = std::chrono::steady_clock::now() + std::chrono::hours(100);

	while (std::chrono::steady_clock::now() < duration)
	{
		// if new OPs are sent by the server_handler, the margot OP list is updated
		tmm.updateOPs();

		//check if the configuration is different wrt the previous one
		if (margot::sleeping::update(param1, param2, param3))
		{
			margot::sleeping::manager.configuration_applied();
		}
		//monitors wrap the autotuned function
		margot::sleeping::start_monitor();

		/*sleepTime = ( 10000 * log(param1) ) + 
					( 50 * param2 ) +
					( 500 + sqrt(param3) );*/

		sleepTime = ( 10 * log(param1) ) + 
					( 5 * param2 ) +
					( 50 + sqrt(param3) );

		go_to_bed(sleepTime);

		/*error = float(1) / ( ( 6 * (1 / param1) ) - 
							 ( 18.97 * log(param2) ) +
							 ( 79.81 * param3 ) );*/

		error = ( 6 * (1 / param1) ) - 
				( 1.97 * log(param2) ) +
				( 7.81 * param3 );

		margot::sleeping::stop_monitor( num_threads, error );
		margot::sleeping::log();

		// the OP is sent to the server_handler
		tmm.sendResult( { param1, param2, param3 }, { margot::sleeping::avg_error, margot::sleeping::avg_throughput } );
	}
}