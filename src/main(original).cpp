#include <chrono>
#include <thread>

/*
 
 The function that will be managed by margot must already be a tunable function
 
 */
void do_work (int trials)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(trials));
}

int main()
{
	int trials = 100;
	int repetitions = 10;
	for (int i = 0; i<repetitions; ++i)
	{
		do_work(trials);
	}



}
