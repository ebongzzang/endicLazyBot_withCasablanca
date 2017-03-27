#include "MessageListener.h"
#include <unistd.h>
int main(void)
{
	utility::string_t address = ("http://localhost:8082/message");
	uri_builder uri(address);
	auto addr = uri.to_uri().to_string();
	MessageListener * msg = new MessageListener(addr);
	try
	{
		msg->open().wait();
	}

	catch(const std::exception &e)
	{
		printf("Error exception:%s\n", e.what());
	}
	pause();

	msg->close().wait();

	return 0;
}
