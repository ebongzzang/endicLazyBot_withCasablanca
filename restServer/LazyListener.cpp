#include "LazyListener.h"

LazyListener::LazyListener(utility::string_t _url) : Listener::Listener(_url)
{

}
LazyListener::~LazyListener()
{

}
void LazyListener::handle_get(http_request message)
{
		json::value obj;
	    std::cout <<  message.to_string() << std::endl;
		
/*		obj["type"] = web::json::value::string("buttons");
		obj["buttons"] = web::json::value::array({web::json::value::string("Search Word"), web::json::value::string("Enter Yourself")});
*/
		obj["type"] = json::value::string("text");
	    message.reply(status_codes::OK,obj);

}

void LazyListener::handle_post(http_request message)
{

}
void LazyListener::handle_put(http_request message)
{

}
void LazyListener::handle_delete(http_request message)
{

}

void LazyListener::start()
{
	try
	{
		open().wait();
	}

	catch(const std::exception &e)
	{
		printf("Error exception:%s\n", e.what());
	}
	pause();
	close().wait();

}
