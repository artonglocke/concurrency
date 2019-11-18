#include <iostream>
#include <thread>

#define ITERATION_CYCLE 10

// 1. function pointer
// 2. function object
// 3. Lambda functions
void displayThread()
{
	for (size_t i = 0; i < ITERATION_CYCLE; i++)
	{
		std::cout << "Worker with id: " << std::this_thread::get_id() << " is executing!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

class DisplayThread
{
public:
	void operator()()
	{
		for (size_t i = 0; i < ITERATION_CYCLE; i++)
		{
			std::cout << "I am a object thread!" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

};

int main()
{
	std::thread first(displayThread);
	std::thread second(displayThread);

	first.join();
	if (second.joinable())
	{
		second.detach();
	}

	std::cin.get();
}