#include "sdp_parser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <stdio.h>




namespace Rtsp 
{
using namespace std;
using namespace boost;
	SDP_parser::SDP_parser() {
			protocol_version = NULL;
			cseq_num = NULL;
			server = NULL;
			cache = NULL;
			expire = NULL;
			content_len = NULL;
			content_base_url= NULL;
			time = NULL;
			content_type = NULL;
			content_session = NULL;
			_payload = NULL;
			size = 0;
	}

	SDP_parser::SDP_parser(char *data, int len)
	{
			_payload = data;
			size = len;
			decode = false;
	}

	SDP_parser::~SDP_parser()
	{
			_payload = NULL;
			size = 0;
			decode = false;
	}

	bool SDP_parser::SDP_Decode()
	{
		if(size == 0)
		{
			std::cout <<"SDP data is empty" << std::endl;
			decode = false;
			
		}
		return decode;
	} 

    std::string get_right_of_delim(std::string const& str, std::string const& delim)
	{
	     return str.substr(str.find(delim) + delim.size());	
	}
	
	bool SDP_parser::IsRTSPOne()
	{
		std::string input = "RTSP/1.0 200 OK";
		std::string token = RTSP_VERSION_ONE;
		
		return contains(input,token);
	}

	int SDP_parser::SDP_GetCSeq()
	{
		std::string input = "CSeq: 1";
		std::string token = RTSP_SDP_CSEQ;
		
		std::string result = get_right_of_delim(input,token);
		cseq_num = (char *)result.c_str();
		return atoi(cseq_num);
		
	}

	char* SDP_parser::SDP_GetStreamingServer()
	{
		std::string input = "Server: Wowza Streaming Engine 4.7.5 build21763";
                std::string token = RTSP_SDP_SERVER;

                std::string result = get_right_of_delim(input, token);
                std::cout << result << std::endl;
                server = (char *)result.c_str();
		return server;
	}

	char* SDP_parser::SDP_GetCacheControl()
	{
		std::string input = "Cache-Control: no-cache";
                std::string token = RTSP_SDP_CACHE_CONTROL;

                std::string result = get_right_of_delim(input, token);
                std::cout << result << std::endl;
                cache = (char *)result.c_str();
		return cache;
	}

	char* SDP_parser::SDP_GetExpires()
	{
		std::string input = "Expires: Mon, 2 Jul 2018 12:47:07 IST";
                std::string token = RTSP_SDP_EXPIRE;

                std::string result = get_right_of_delim(input, token);
                std::cout << result << std::endl;
                expire = (char *)result.c_str();
		return expire;
	}

	int SDP_parser::SDP_GetContentLength()
	{
               return 0;
	}

	char* SDP_parser::SDP_GetContentBaseUrl()
	{
			return NULL;
	}

	char* SDP_parser::SDP_GetTimeStamp()
	{
			return NULL;
	}

	char* SDP_parser::SDP_GetContentType()
	{
			return NULL;
	}

	char* SDP_parser::SDP_GetSessionId()
	{
			return NULL;
	}

	int SDP_parser::SDP_GetTimeout()
	{
			return 0;
	}
}

int main(int argc, 	char* argv[])
{
		std::string file,line;
		std::ifstream infile("one.sdp");
		Rtsp::SDP_parser *sdp;
		char *data = NULL;
		int len = 0;
		while( getline(infile,line))
		{
			line = line+RTSP_SDP_CRLF;
			file = file+line;
			
		}
		std::cout << file << std::endl;
		len = file.length();
		//data = new char[len+1];
		data = (char *)file.c_str();
		sdp = new Rtsp::SDP_parser(data,len);
		bool one = sdp->IsRTSPOne();
		std::cout << one << std::endl;
		std::cout << sdp->SDP_GetCSeq() << std::endl;
                char *server = sdp->SDP_GetStreamingServer();
                char *cache  = sdp->SDP_GetCacheControl();
                char *expire = sdp->SDP_GetExpires();
}
