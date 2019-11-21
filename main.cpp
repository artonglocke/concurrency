#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <mutex>

#define THREAD_COUNT 5
#define COUNT 100

class Wallet
{
public:
	Wallet() : _balance(0) {};
	~Wallet() {};

	void addToBalance(int ammount)
	{
		_mutex.lock();
		for (int i = 0; i < ammount; ++i)
		{
			_balance++;
			std::cout << "Thread: " << std::this_thread::get_id() << " Current balance: " << _balance << std::endl;
		}
		_mutex.unlock();
	}

	int getBalance()
	{
		return _balance;
	}

private:
	int _balance;
	std::mutex _mutex;
};

int multithreadedWallet()
{
	Wallet wallet;
	std::vector<std::thread> threads;
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		threads.push_back(std::thread(&Wallet::addToBalance, &wallet, COUNT));
	}

	for (int i = 0; i < threads.size(); i++)
	{
		threads[i].join();
	}
	return wallet.getBalance();
}

int main()
{
	int value = 0;
	for (int i = 0; i < COUNT; i++)
	{
		if ((value = multithreadedWallet()) != COUNT * THREAD_COUNT)
		{
			std::cout << "error at: " << i << " Current balance: " << value << std::endl;
		}
	}
	std::cout << "Final value = " << value;
	std::cin.get();
}