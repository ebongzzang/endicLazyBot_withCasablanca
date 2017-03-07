#include "HTMLCrawler.h"
#include <iostream>
#include <string>
int main(void)
{
	std::string test = "http://m.endic.naver.com/search.nhn?searchOption=all&query=consistency&="; 
	std::string temp;
	HTMLCrawler * crawler = new HTMLCrawler(test);
	temp = crawler->getHTML();
	std::cout <<temp <<std::endl;
	auto name = crawler->write();
	std::cout<< name << std::endl;
	crawler->Parse(name);
}
