#ifndef LAZY_LISTENER_H
#define LAZY_LISTENER_H

#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <map>
using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;
using namespace utility;


class LazyListener
{
	public:
	LazyListener(utility::string_t url);
	~LazyListener();
    pplx::task<void>open(){return m_listener.open();}
    pplx::task<void>close(){return m_listener.close();}

	protected:

	private:
   	void handle_get(http_request request);
   	void handle_put(http_request request);
   	void handle_post(http_request request);
   	void handle_delete(http_request request);

   	http_listener m_listener;
	std::map<utility::string_t, utility::string_t> dictionary;
	
};

#endif
