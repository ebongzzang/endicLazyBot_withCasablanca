#include "LazyListener.h"

LazyListener::LazyListener(utility::string_t url) : Listener::Listener(url)
{

}
void LazyListener::handle_get(http_request message)
{
	    std::map<utility::string_t,utility::string_t> dic = {{"type","text"}};
		json::value obj;
	    std::cout <<  message.to_string() << std::endl;

	    for(auto const &p : dic)
		{
			        obj[p.first] = json::value::string(p.second);    
					    
		}    

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
