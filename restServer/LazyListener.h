#ifndef LAZY_LISTENER_H
#define LAZY_LISTENER_H
#include "Listener.h"
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;
using namespace utility;


class LazyListener : public Listener 
{
	public:
	LazyListener(utility::string_t _url);
	virtual void start();
	~LazyListener();
	protected:
   	virtual void handle_get(http_request request);
   	virtual void handle_put(http_request request);
   	virtual void handle_post(http_request request);
   	virtual void handle_delete(http_request request);
	private:

	
};

#endif
