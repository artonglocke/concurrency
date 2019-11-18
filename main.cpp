#include <iostream>
#include <thread>

#define ITERATION_CYCLE 50

// 1. function pointer
// 2. function object
// 3. Lambda functions
void displayFirstThread()
{
	for (size_t i = 0; i < ITERATION_CYCLE; i++)
	{
		std::cout << "I am a first worker thread!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void displaySecondThread()
{
	for (size_t i = 0; i < ITERATION_CYCLE; i++)
	{
		std::cout << "I am a second worker thread!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

// 2. function object
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
	// 1. function pointer thread
	std::thread firstWorker(displayFirstThread);
	std::thread secondWorker(displaySecondThread);
	std::thread objectThread((DisplayThread()));
	std::thread lambdaThread([] {
		for (size_t i = 0; i < ITERATION_CYCLE; i++)
		{
			std::cout << "I am a lambda thread!" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	});

	if (firstWorker.joinable())
	{
		std::cout << "First thread is ready to join" << std::endl;
		firstWorker.join();
	}

	if (secondWorker.joinable())
	{
		std::cout << "Second thread is ready to join" << std::endl;
		secondWorker.join();
	}

	if (objectThread.joinable())
	{
		std::cout << "Object thread is ready to join" << std::endl;
		objectThread.join();
	}

	if (lambdaThread.joinable())
	{
		std::cout << "Lambda thread is ready to join" << std::endl;
		lambdaThread.join();
	}

	for (size_t i = 0; i < ITERATION_CYCLE; i++)
	{
		std::cout << "I am a main thread" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}


	std::cin.get();
}