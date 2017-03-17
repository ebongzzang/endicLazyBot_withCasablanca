#ifndef LISTENER_H
#define LISTENER_H

#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <map>
using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;
using namespace utility;


class Listener
{
	public:
	Listener(utility::string_t url);
	~Listener();
    virtual pplx::task<void>open(){return m_listener.open();}
    virtual pplx::task<void>close(){return m_listener.close();}

	protected:
   	virtual void handle_get(http_request request);
   	virtual void handle_put(http_request request);
   	virtual void handle_post(http_request request);
   	virtual void handle_delete(http_request request);
	std::map<utility::string_t, utility::string_t> dictionary;
	private:
   	http_listener m_listener;

	
};

#endif
