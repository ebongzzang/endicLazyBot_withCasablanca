#include "LazyListener.h"
#include "MessageListener.h"
#include <thread>
#include <vector>

int main(void)
{
	LazyListener lazy("http://localhost:8081/keyboard");
	MessageListener msg("http://localhost:8082/message");

	std::thread lazyTh(&LazyListener::start,&lazy);
	std::thread msgTh(&MessageListener::start,&msg);

	lazyTh.join();
	msgTh.join();

	return 0;

}
