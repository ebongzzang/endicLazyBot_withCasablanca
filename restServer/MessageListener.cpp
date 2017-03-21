#include "MessageListener.h"

MessageListener::MessageListener(utility::string_t url) : Listener::Listener(url)
{

}
void MessageListener::handle_get(http_request message)
{

}

void MessageListener::handle_post(http_request message)
{

	std::cout <<  message.to_string() << std::endl;
	std::vector<web::json::value> jsonVector;
	auto json = message.extract_json().get();
	//json['key'] = value;
	json::value obj;
	json::value replyMsg;
	json::value keyboard;

	replyMsg["text"] = web::json::value::string(U("succeed!"));
    keyboard["type"] = web::json::value::string(U("buttons"));
	keyboard["buttons"] = web::json::value::array({web::json::value::string("again"),web::json::value::string("bye")});
	//keyboard

	//reply message
	
	obj["message"] = replyMsg;
	obj["keyboard"] = keyboard;
	std::cout << "obj" << obj.serialize() << std::endl;
/*	auto array = json.as_array();
	//add to obj(final return)
	for(size_t i=0; i< array.size(); i++)
	{
		auto userKey = array[i].at(U("user_key")).as_string();
		auto type = array[i].at(U("type")).as_string();
		auto content = array[i].at(U("content")).as_string();
		std::cout << userKey <<std::endl;
		std::cout << type <<std::endl;;
		std::cout << content << std::endl;
	}    
*/
	   // message.reply(status_codes::Created,obj);
	    message.reply(status_codes::OK,obj);

}
void MessageListener::handle_put(http_request message)
{

}
void MessageListener::handle_delete(http_request message)
{

}
