#ifndef HTMLCRAWLER_H
#define HTMLCRAWLER_H

#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <fstream>
#include <stdio.h>
#include <libxml2/libxml/HTMLparser.h>
#include <libxml2/libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <vector>

class HTMLCrawler
{
	public:
	HTMLCrawler(const std::string _sourceURL);
	std::string getHTML(const std::string encode = " "); //return contents of html, default encode = UTF-8
	std::string write(); //return filename
	std::vector<unsigned char *> parse_all(bool isFile, bool printText, const std::string sourceHTML, const std::string Parsetag);
	//memory = true .html = false 
	unsigned char * parse(bool isFile, bool printText, const std::string sourceHTML, const std::string Parsetag);
	//memory = true .html = false 

	~HTMLCrawler();

	private:
	CURL *curl;
	CURLcode res;
	std::string readBuffer;
	std::ofstream outputFile;
	std::string sourceURL;
	htmlDocPtr doc;

};





#endif
