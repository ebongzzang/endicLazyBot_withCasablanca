#include "HTMLCrawler.h"

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

std::string HTMLCrawler::Parse(const std::string Parsetag)
{
	doc = htmlReadFile(Parsetag.c_str(), NULL, HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
	if (doc == NULL) 
	{
	        fprintf(stderr, "Document not parsed successfully.\n");
	   		return 0;
	   				     
	}
	xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);

    xmlChar *xpath = (xmlChar*) "//a[@class='h_word']";
	xmlXPathObjectPtr result = xmlXPathEvalExpression(xpath, xpathCtx);
	xmlNodeSetPtr nodeset;
//xmlChar *keyword;
//
	if(xmlXPathNodeSetIsEmpty(result->nodesetval))
	{
		std::cout << "no result! " << std::endl;
	}

	nodeset = result->nodesetval;
	xmlBufferPtr nodeBuffer = xmlBufferCreate();

	for (int i=0; i < nodeset->nodeNr; i++)
   	{
			xmlNodeDump(nodeBuffer,doc,nodeset->nodeTab[i],0,1);
			std::cout << nodeBuffer->content << std::endl;
			std::cout << "done!!"<< std::endl;
			sleep(2);
	}


//
	return "hi";
}

std::string HTMLCrawler::write()
{
	std::string filename = sourceURL.substr(9,5)+".xml";
	outputFile.open(filename,std::ios::out);
	outputFile << readBuffer;
	return filename;
}

HTMLCrawler::~HTMLCrawler()
{
	curl_easy_cleanup(curl);
	outputFile.close();
}
