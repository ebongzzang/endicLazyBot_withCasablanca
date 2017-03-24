#include "HTMLCrawler.h"
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <cstring>

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

int main(int argc,char ** argv)
{
	std::string argu(argv[1]);
	//std::string test = "http://m.endic.naver.com/search.nhn?searchOption=all&query=" + argu.replace(argu.find(" "),1, "");
	std::string test = "http://m.endic.naver.com/search.nhn?searchOption=all&query=" + argu;
	std::string htmlBuffer;
	std::vector<unsigned char *>::iterator it;

	HTMLCrawler * crawler = new HTMLCrawler(test);
	htmlBuffer = crawler->getHTML();
	std::string htmlfilename = crawler->write();
	auto entryVector = crawler->parse_all(false,false,htmlBuffer,"//div[@class='entry_search_word top']");

	for(std::vector<unsigned char *>::iterator it = entryVector.begin(); it != entryVector.end(); ++it)
	{
		auto word = crawler->parse(false,true,std::string(reinterpret_cast<char *>(*it)),"//strong[@class='target']");
		std::string wordStr(reinterpret_cast<char *>(word));
		trim(wordStr);
		std::cout << wordStr << std::endl;
		std::cout << '\n';

		auto wordMean = crawler->parse_all(false,true,std::string(reinterpret_cast<char *>(*it)),"//li");

		for(std::vector<unsigned char *>::iterator it2 = wordMean.begin(); it2 != wordMean.end(); ++it2)
		{
			std::string temp(reinterpret_cast<char *>(*it2));
			trim(temp);
			std::cout << temp << std::endl;
		}
		std::cout << '\n';

		 auto wordExamStc = crawler->parse(false,false,std::string(reinterpret_cast<char *>(*it)),"//p[@class='example_stc']");
		 auto wordExamStcVec = crawler->parse_all(false,true,std::string(reinterpret_cast<char *>(wordExamStc)),"//a");

			for(std::vector<unsigned char *>::iterator it2 = wordExamStcVec.begin(); it2 != wordExamStcVec.end(); ++it2)
			{
				if(std::string(reinterpret_cast<char *>(*it2)).find("발음듣기") != std::string::npos)
					break;
				std::cout << *it2 << " ";
			}

			std::cout << '\n';

			auto wordExamMean = crawler->parse(false,true,std::string(reinterpret_cast<char *>(*it)),"//p[@class='example_mean']");
			std::string temp(reinterpret_cast<char *>(wordExamMean));
			trim(temp);

			std::cout << temp <<std::endl;
			std::cout <<'\n';

	}
}

