#include "MessageListener.h"
#include "../HTMLCrawler.h"
#include <fstream>
#include <regex>
#include <locale>
static inline void ltrim(std::string &s)
{
	    s.erase(s.begin(), std::find_if(s.begin(), s.end(),std::not1(std::ptr_fun<int, int>(std::isspace))));

}

static inline void rtrim(std::string &s)
{
	    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());

}

// trim from both ends (in place)
 static inline void trim(std::string &s)
{
     ltrim(s);
     rtrim(s);
 }


MessageListener::MessageListener(utility::string_t _url) : Listener::Listener(_url)
{

}
MessageListener::~MessageListener()
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

//	replyMsg["text"] = web::json::value::string(U("succeed!"));
	//keyboard

	//reply message
	

	auto userKey = json.at("user_key").serialize();
	auto type = json.at("type").serialize();
	auto content = json.at("content").serialize();
	std::string searchResult = getNaverEndic(content); 

	replyMsg["text"] = web::json::value::string(U(searchResult));
    keyboard["type"] = web::json::value::string(U("text"));
	//keyboard["buttons"] = web::json::value::array({web::json::value::string("again"),web::json::value::string("bye")});

	obj["message"] = replyMsg;
	obj["keyboard"] = keyboard;

	std::cout << obj.serialize() << std::endl;

	   // message.reply(status_codes::Created,obj);
	    message.reply(status_codes::OK,obj);

}

void MessageListener::handle_put(http_request message)
{

}

void MessageListener::handle_delete(http_request message)
{

}

void MessageListener::start()
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

std::string MessageListener::getNaverEndic(std::string word)
{
	std::string result;
	std::locale loc;
	std::regex space("[[:space:]]");
	std::vector<unsigned char *> entryVector;
	std::string word_replace = std::regex_replace(word,space,"%20");

	std::string test = "http://m.endic.naver.com/search.nhn?searchOption=all&query=" + word_replace;
	std::cout << test <<std::endl;
	std::string htmlBuffer;
	std::vector<unsigned char *>::iterator it;

	HTMLCrawler * crawler = new HTMLCrawler(test);
	htmlBuffer = crawler->getHTML();
	if(std::isalpha(word.at(1),loc))
	{
		entryVector = crawler->parse_all(false,false,htmlBuffer,"//div[@class='entry_search_word top']");
	}
	else
	{
		entryVector = crawler->parse_all(false,false,htmlBuffer,"//div[@class='entry_search_word top kr']");
	}

	std::string htmlfilename = crawler->write();

	for(std::vector<unsigned char *>::iterator it = entryVector.begin(); it != entryVector.end(); ++it)
	{
		auto word = crawler->parse(false,true,std::string(reinterpret_cast<char *>(*it)),"//strong[@class='target']");
		std::string wordStr(reinterpret_cast<char *>(word));
		trim(wordStr);
		std::cout << wordStr + '\n' << std::endl;
		result.append(wordStr + '\n');

		auto wordMean = crawler->parse_all(false,true,std::string(reinterpret_cast<char *>(*it)),"//li");

		for(std::vector<unsigned char *>::iterator it2 = wordMean.begin(); it2 != wordMean.end(); ++it2)
		{
			std::string temp(reinterpret_cast<char *>(*it2));
			trim(temp);
			std::cout << temp << std::endl;
			result.append(temp + '\n');
		}
		std::cout << '\n';
		result.append("\n\n");
	}
		return result;
}
