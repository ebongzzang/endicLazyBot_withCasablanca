#include "Listener.h"

Listener::Listener(utility::string_t _url)
{	
	uri_builder uriBuilder(_url);
	url = uriBuilder.to_uri().to_string();
	m_listener = http_listener(url);

	m_listener.support(methods::GET, std::bind(&Listener::handle_get,this,std::placeholders::_1));
	m_listener.support(methods::PUT, std::bind(&Listener::handle_put,this,std::placeholders::_1));
	m_listener.support(methods::POST, std::bind(&Listener::handle_post,this,std::placeholders::_1));
	m_listener.support(methods::DEL, std::bind(&Listener::handle_delete,this,std::placeholders::_1));
}
Listener::~Listener()
{

}
void Listener::handle_get(http_request message)
{
	 message.reply(status_codes::NotFound);
}

void Listener::handle_post(http_request message)
{
	 message.reply(status_codes::NotFound);
}
void Listener::handle_put(http_request message)
{
	 message.reply(status_codes::NotFound);

}
void Listener::handle_delete(http_request message)
{
	 message.reply(status_codes::NotFound);

}
void Listener::start()
{

}
