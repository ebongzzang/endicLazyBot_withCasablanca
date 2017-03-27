#include "LazyListener.h"
#include <unistd.h>
int main(void)
{
	utility::string_t address = ("http://localhost:8081/keyboard");
	uri_builder uri(address);
	auto addr = uri.to_uri().to_string();
	LazyListener * lazy = new LazyListener(addr);
	try
	{
		lazy->open().wait();
	}

	catch(const std::exception &e)
	{
		printf("Error exception:%s\n", e.what());
	}
	pause();
	lazy->close().wait();

	return 0;
}
