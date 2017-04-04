#ifndef LISTENER_H
#define LISTENER_H

#include <cpprest/http_listener.h>
#include <cpprest/json.h>
using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;


class Listener
{
	public:
	Listener(utility::string_t _url);
	~Listener();
    virtual pplx::task<void>open(){return m_listener.open();}
    virtual pplx::task<void>close(){return m_listener.close();}
	virtual void start();

	protected:
   	virtual void handle_get(http_request request);
   	virtual void handle_put(http_request request);
   	virtual void handle_post(http_request request);
	virtual void handle_delete(http_request request);
    utility::string_t url;

	private:
   	http_listener m_listener;

	
};

#endif
