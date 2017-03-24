#include "HTMLCrawler.h"
#include <vector>
#include <string.h>
using CURLOPT_WRITEFUNCTION_PTR = size_t(*)(void * ,size_t, size_t, void*);

HTMLCrawler::HTMLCrawler(const std::string _sourceURL) : sourceURL(_sourceURL)
{

}

std::string HTMLCrawler::getHTML(const std::string encode)
{
	auto curl_callback = [](void *contents , size_t size, size_t nmemb, void *stream)->size_t
	{
	(reinterpret_cast<std::string *>(stream))->append(reinterpret_cast<char *>(contents),size * nmemb);
	return size * nmemb;
	};
	  curl = curl_easy_init();

	  if (curl)
	  {
		curl_easy_setopt(curl, CURLOPT_URL,sourceURL.c_str());
//curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, static_cast<CURLOPT_WRITEFUNCTION_PTR>(curl_callback));
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0"); //set user-agent
//		curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING,encode.c_str());

		res = curl_easy_perform(curl);

		if(res == CURLE_OK)
		{
				//something else
		}

		else
		{
			std::cout << "curl_easy_perform() failed:" << curl_easy_strerror(res) << std::endl;
			readBuffer.empty();
		}

			return readBuffer;

	  }
return " ";
}

std::vector<unsigned char *> HTMLCrawler::parse_all(bool isFile,bool printText, const std::string sourceHTML, const std::string Parsetag)
{
	std::vector<unsigned char *> resultVector;
	if(isFile)
	{
		doc = htmlReadFile(sourceHTML.c_str(), NULL, HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
	}
	else
	{
		doc = htmlReadMemory(sourceHTML.c_str(),sourceHTML.size(),NULL,NULL, HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
	}
	if (doc == NULL) 
	{
	   //     fprintf(stderr, "Document not parsed successfully.\n");
			resultVector.clear();
			return resultVector;
	   				     
	}

	xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
	//html -> xml DOM

	xmlChar* xpath = (xmlChar*)Parsetag.c_str();
	//xmlChar *xpath = (xmlChar*)"//div[@class='section_card']//ul[@class='desc_lst']//li//p";
	xmlXPathObjectPtr result = xmlXPathEvalExpression(xpath, xpathCtx);
	xmlNodeSetPtr nodeset;

	if(xmlXPathNodeSetIsEmpty(result->nodesetval))
	{
		resultVector.clear();
		return resultVector;
	}

	nodeset = result->nodesetval;
	resultVector.reserve(nodeset->nodeNr);
	for (int i=0; i < nodeset->nodeNr; i++)
   	{
			xmlBufferPtr nodeBuffer = xmlBufferCreate();
			xmlNodeDump(nodeBuffer,doc,nodeset->nodeTab[i],0,0);
			if(printText)
			{
				resultVector.push_back(xmlNodeGetContent(nodeset->nodeTab[i]));
			}
			else
			{
				resultVector.push_back(nodeBuffer->content);	
			}
	}

	return  resultVector;
}

unsigned char * HTMLCrawler::parse(bool isFile, bool printText, const std::string sourceHTML, const std::string Parsetag)
{
	if(isFile)
	{
		doc = htmlReadFile(sourceHTML.c_str(), NULL, HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
	}
	else
	{
		doc = htmlReadMemory(sourceHTML.c_str(),sourceHTML.size(),NULL,NULL,HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
	}

	if (doc == NULL) 
	{
	     //   fprintf(stderr, "Document not parsed successfully.\n");
			return (xmlChar *)"";
	   				     
	}

	xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
	//html -> xml DOM

	xmlChar *xpath = (xmlChar*)Parsetag.c_str();
	//xmlChar *xpath = (xmlChar*)"//div[@class='section_card']//ul[@class='desc_lst']//li//p";
	xmlXPathObjectPtr result = xmlXPathEvalExpression(xpath, xpathCtx);
	xmlNodeSetPtr nodeset;

	if(xmlXPathNodeSetIsEmpty(result->nodesetval))
	{
	//	std::cout << "no result! " << std::endl;
		return (xmlChar *)"";
	}

	nodeset = result->nodesetval;
	for (int i=0; i < 1; i++)// Return only one element
   	{
			xmlBufferPtr nodeBuffer = xmlBufferCreate();
			xmlNodeDump(nodeBuffer,doc,nodeset->nodeTab[i],0,0);
			if(printText)
			{
				return xmlNodeGetContent(nodeset->nodeTab[i]);
			}
			else
			{
				return nodeBuffer->content;
			}
	}
	//	std::cout << "unexpected error" << std::endl;
		return (xmlChar *)"";
}
std::string HTMLCrawler::write()
{
	std::string filename = sourceURL.substr(9,5)+".xml";
	//TODO:: hmm..
	outputFile.open(filename,std::ios::out);
	outputFile << readBuffer;
	return filename;
}

HTMLCrawler::~HTMLCrawler()
{
	curl_easy_cleanup(curl);
	outputFile.close();
}
