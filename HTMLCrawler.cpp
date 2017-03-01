#include "HTMLCrawler.h"

using CURLOPT_WRITEFUNCTION_PTR = size_t(*)(void * ,size_t, size_t, void*);

HTMLCrawler::HTMLCrawler(const std::string _sourceURL) : sourceURL(_sourceURL)
{

}

std::string HTMLCrawler::getHTML(const std::string encode)
{
	auto curl_callback = [](void *contents , size_t size, size_t nmemb, void *stream)->size_t{
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
			return readBuffer;

		else
		{
			std::cout << "curl_easy_perform() failed:" << curl_easy_strerror(res) << std::endl;
			readBuffer.empty();
			return readBuffer;
		}

	  }
}

std::string HTMLCrawler::write()
{
	outputFile.open(sourceURL.substr(13)+".xml",std::ios::out);
	outputFile << readBuffer;
}	//return filename

HTMLCrawler::~HTMLCrawler()
{
	curl_easy_cleanup(curl);
	outputFile.close();
}
