#include "LazyListener.h"

LazyListener::LazyListener(utility::string_t url) : m_listener(url)
{
	m_listener.support(methods::GET, std::bind(&LazyListener::handle_get,this,std::placeholders::_1));
	m_listener.support(methods::PUT, std::bind(&LazyListener::handle_put,this,std::placeholders::_1));
	m_listener.support(methods::POST, std::bind(&LazyListener::handle_post,this,std::placeholders::_1));
	m_listener.support(methods::DEL, std::bind(&LazyListener::handle_delete,this,std::placeholders::_1));
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
	std::cout <<  message.to_string() << std::endl;
	auto paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));

    message.relative_uri().path();
}
void LazyListener::handle_put(http_request message)
{
	std::cout <<  message.to_string() << std::endl;
	auto paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));

    message.relative_uri().path();
}
void LazyListener::handle_delete(http_request message)
{
	std::cout <<  message.to_string() << std::endl;
	auto paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));

	message.relative_uri().path();
}
