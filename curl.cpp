#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>
#include <stdio.h>
#include <libxml2/libxml/HTMLparser.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	(reinterpret_cast<std::string *>(userp))->append(reinterpret_cast<char *>(contents),size * nmemb);
	return size * nmemb;
}

void traverse_dom_trees(xmlNode * a_node)
{
	xmlNode *cur_node = NULL;
    if(NULL == a_node)
	{
		        //printf("Invalid argument a_node %p\n", a_node);
				//        return;
				//         
	}
	for (cur_node = a_node; cur_node; cur_node = cur_node->next) 
	{
	        if (cur_node->type == XML_ELEMENT_NODE) 
			{
				auto attribute = cur_node->properties;
				printf("%s ", cur_node->name); //tag name
			   while(attribute) //iterate node attributes
			   {	   
				std::cout<< attribute->name<< "=" << xmlNodeGetContent(attribute->children) << " "; //attribute = value
				attribute = attribute->next;
				}
			   /* next tag */
			   std::cout <<"\n";
			}			

			else if (cur_node->type == XML_TEXT_NODE)
			{
			/* Process here text node, It is available in cpStr :TODO: */
//	 printf("node type: Text, node content: %s,  content length %d\n", (char *)cur_node->content, strlen((char *)cur_node->content));
													        
			}
				    traverse_dom_trees(cur_node->children); //recursion call
											    
	}

}


int main(int argc, char* argv[])
{
	  CURL *curl;
	  CURLcode res;
	  std::string readBuffer;
	  curl = curl_easy_init();

	  if(curl)
	  {
		curl_easy_setopt(curl, CURLOPT_URL, "http://m.endic.naver.com/search.nhn?searchOption=all&query=consistency");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
		res = curl_easy_perform(curl);

		if(res == CURLE_OK)
		{
	//			std::cout << readBuffer << std::endl;
		}

		else
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}

		curl_easy_cleanup(curl);
	  }

	std::ofstream fileOutput;
	fileOutput.open("output.html",std::ios::out);
	fileOutput << readBuffer;
	fileOutput.close();
	htmlDocPtr doc;
	xmlNode *roo_element = NULL;

	doc = htmlReadFile("output.html", NULL, HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
	if (doc == NULL) 
	{
	        fprintf(stderr, "Document not parsed successfully.\n");
	   		return 0;
	   				     
	}

	roo_element = xmlDocGetRootElement(doc);

	 if (roo_element == NULL) 
	 {
	      fprintf(stderr, "empty document\n");
		  xmlFreeDoc(doc);
		  return 0;
								     
	 }
	     printf("Root Node is %s\n", roo_element->name);
//		 traverse_dom_trees(roo_element);
		 xmlChar *xpath = (xmlChar*) "//div[@class='entry_search_word top']/a[@*]";

		 auto context = xmlXPathNewContext(doc);
		 auto result = xmlXPathEvalExpression(xpath,context);

		 if (result == NULL)
		 {
			printf("Error in xmlXPathEvalExpression\n");
								
		 }
		 if(xmlXPathNodeSetIsEmpty(result->nodesetval))
		 {
			xmlXPathFreeObject(result);
			printf("No result\n");
		 }	
		auto nodeset = result->nodesetval;
		for (int i=0; i < nodeset->nodeNr; i++) {
			auto keyword1 = xmlNodeListGetString(doc, nodeset->nodeTab[i], 1);
			printf("%s\n", keyword1);
}
												
	return 0;

}
