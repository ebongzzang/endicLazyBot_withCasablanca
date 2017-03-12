#include "HTMLCrawler.h"
#include <iostream>
#include <string>
#include <iterator>
int main(void)
{
	std::string test = "http://m.endic.naver.com/search.nhn?searchOption=all&query=consistency&="; 
	std::string temp;
	HTMLCrawler * crawler = new HTMLCrawler(test);

	temp = crawler->getHTML();
	//debug	std::cout <<temp <<std::endl;
	auto name = crawler->write();
	std::cout<< name << std::endl;
	auto vector = crawler->parse_all(true,temp,"//div[@class='section_card']//ul[@class='desc_lst']//li//p");
	//TODO
	for(std::vector<unsigned char *>::iterator it = vector.begin(); it != vector.end(); ++it)
	{
				std::cout << *it << std::endl;
	}
	auto just = crawler->parse(true,temp,"//div[@class='section_card']//ul[@class='desc_lst']//li//p");
	std::cout << just << std::endl;

}
