#include "HTMLCrawler.h"
#include <iostream>
#include <string>
int main(void)
{
	std::string test = "http://naver.com"; 
	std::string temp;
	HTMLCrawler * crawler = new HTMLCrawler(test);
	temp = crawler->getHTML();
	std::cout <<temp <<std::endl;
	crawler->write();
}
