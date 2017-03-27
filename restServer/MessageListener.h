#ifndef MESSAGE_LISTENER_H
#define MESSAGE_LISTENER_H
#include "Listener.h"
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <map>
#include <string>
using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;
using namespace utility;


class MessageListener : public Listener 
{
	public:
	MessageListener(utility::string_t url);
	~MessageListener();
	protected:
   	virtual void handle_get(http_request request);
   	virtual void handle_put(http_request request);
   	virtual void handle_post(http_request request);
   	virtual void handle_delete(http_request request);
	std::string getNaverEndic(std::string word);
	private:

	
};

#endif
