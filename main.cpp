#include <iostream>
#include <thread>
#include <string>

#define ITERATION_CYCLE 10

void DisplayThreadData(int num, std::string message)
{
	std::cout << "Thread number: " << num << std::endl;
	std::cout << message << std::endl;
}

void threadRef(int& num)
{
	for (size_t i = 0; i < 100000; i++)
	{
		++num;
		std::cout << "thread with id: " << std::this_thread::get_id() << " number: " << num << std::endl;
	}
}

// std::thread threadObject(function, params);

// Napraviti funkciju koja prima referencu na broj, te taj isti broj uvecavati 1000x for <1000 num++
// Ispisati broj u svakoj iteraciji for petlje skupa sa ID-em od threada
// std::ref(num)
// Napraviti 2 threada koja primaju istu referencu!
int main()
{
	std::thread threadWithParams(DisplayThreadData, 10, "Hello thread!");

	threadWithParams.join();
	int i = 0;
	std::thread thr(threadRef, std::ref(i));
	std::thread thr2(threadRef, std::ref(i));

	thr.join();
	thr2.join();

	std::cout << "Final result: " << i << std::endl;
	std::cin.get();
}