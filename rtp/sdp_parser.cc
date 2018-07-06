#include "sdp_parser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/foreach.hpp>
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
               std::string input = "Content-Length: 569";
               std::string token = RTSP_SDP_CONTENT_LENGTH;

               std::string result = get_right_of_delim(input, token);
               std::cout << result << std::endl;
               content_len = (char *)result.c_str();
               return atoi(content_len);
        }

	char* SDP_parser::SDP_GetContentBaseUrl()
	{
			   std::string input = "Content-Base: rtsp://192.168.1.6:1935/vod/one.mp4/";
			   std::string token = RTSP_SDP_CONTENT_BASE;
			   
			   std::string result = get_right_of_delim(input, token);
			   std::cout << result << std::endl;
			   content_base_url = (char *)result.c_str();
			   return content_base_url;
	}

	char* SDP_parser::SDP_GetTimeStamp()
	{
			  std::string input = "Date: Mon, 2 Jul 2018 12:47:07 IST";
			  std::string token = RTSP_SDP_DATE;
			  
			  std::string result = get_right_of_delim(input, token);
			  std::cout << result << std::endl;
			  time = (char *)result.c_str();
			  return time;
	}

	char* SDP_parser::SDP_GetContentType()
	{
		      std::string input = "Content-Type: application/sdp";
			  std::string token = RTSP_SDP_CONTENT_TYPE;
			  
			  std::string result = get_right_of_delim(input, token);
			  std::cout << result << std::endl;
			  content_type = (char *)result.c_str();
			  return content_type;
	}

	char* SDP_parser::SDP_GetSessionId()
	{
			std::string input = "Session: 1177817050;timeout=60";
			std::string token = RTSP_SDP_SESSION;
			  
			std::string intrim = get_right_of_delim(input, token);
			std::string result =  intrim.substr(0,intrim.find(";",0));
			std::cout << result << std::endl;
			content_session = (char *)result.c_str();
			return content_session;
	}

	int SDP_parser::SDP_GetTimeout()
	{
		    std::string input = "Session: 1177817050;timeout=60";
			std::string token = RTSP_SDP_SESSION;
			std::string token_time = RTSP_SDP_ATTRIBUTE_TIMEOUT;
			  
			std::string intrim = get_right_of_delim(input, token);
			std::string result = get_right_of_delim(intrim,token_time);
            std::cout << result << std::endl;
			timeout = (char *)result.c_str(); 
			return atoi(timeout);
	}
	
	int SDP_parser::SDP_GetVersion()
    {
			std::string input = "v=0";
			char *version = (char *)input.c_str();
			
			if ((version[0] == 'v') && (version[1] == '='))
			{
				char *number = (version + 2);
				return atoi(number);
			}
		return 0;
	}          
	
	Owner* SDP_parser::SDP_GetOwnerInfo()
	{
			std::string input = "o=- 1177817050 1177817050 IN IP4 127.0.0.1";
			char *own = (char *)input.c_str();
			
			owner = (Owner *)malloc(sizeof(Owner));
			
			if ((own[0] == 'o') && (own[1] == '='))
			{
				typedef std::vector<std::string> Tokens;
				Tokens tokens;
				boost::split(tokens, input, boost::is_any_of(" "));
				
				int size = tokens.size();
				int count = 0;
				BOOST_FOREACH( const std::string& i, tokens) {
					switch(count){
						case 0:
						{
								std::cout << "Owner " << own[2] << std::endl;
								char *value = (char *)i.c_str();
								owner->username = (value + 2);
								break;
						}
						case 1:
						{
						        char *sessionID = (char *)i.c_str();
								int ID = atoi(sessionID);
								std::cout << "Owner SessionID " << i << std::endl;
								owner->sessionID = ID;
								break;
						}
						case 2:
						{
								char *sessionVer = (char *)i.c_str();
								int Ver = atoi(sessionVer);
								std::cout << "Owner Version " << i << std::endl;
								owner->session_version = Ver;
								break;
						}
						case 3:
						{
								owner->networktype = (char *)i.c_str();
								std::cout << "Owner Network Type " << i << std::endl;
								break;
						}
						case 4:
						{
								owner->address_type = (char *)i.c_str();
								std::cout << "Owner Address Type " << i << std::endl;
								break;
						}
						case 5:
						{
								owner->address = (char *)i.c_str();
								std::cout << "Owner IP Address " << i << std::endl;
								break;
						}
						default:
								break;
					}
					count++;
				}
			}
			return owner;
	}
	
	char  *SDP_parser::SDP_GetSessionName()
	{
		std::string input ="s=one.mp4";
		char *s = (char *)input.c_str();
		if((s[0] == 's') && (s[1] == '='))
		{
			session_name = (s + 2);
			std::string sess(session_name);
			std::cout << "Session is " << sess << std::endl;
		}
		return session_name;
	}
	Connect *SDP_parser::SDP_GetConnectionInfo()   
	{
		std::string input = "c=IN IP4 0.0.0.0";
		char *conn = (char *)input.c_str();
		if((conn[0] == 'c') && (conn[1] == '='))
		{
			connect = (Connect *)malloc(sizeof(Connect));
			typedef std::vector<std::string> Tokens;
			Tokens tokens;
			boost::split(tokens, input, boost::is_any_of(" "));
				
			int size = tokens.size();
			int count = 0;
			BOOST_FOREACH( const std::string& i, tokens) {
				switch(count) {
					case 0:
					{
							char *network = (char *)i.c_str();
							connect->networktype = (network + 2);
							std::string val(connect->networktype);
							std::cout << "Network Type :" << val << std::endl;
							break;
					}
					case 1:
					{
							std::cout << "Address Type " << i << std::endl;
							connect->address_type = (char *)i.c_str();
							break;
					}
					case 2:
					{
							std::cout << "Address " << i << std::endl;
						    connect->address = (char *)i.c_str();
							break;
					}
					default:
							break;
				}
				count++;
			}
		}
		return connect;
	}
		
	Time *SDP_parser::SDP_GetTimeParameter()    
	{
		std::string input = "t=0 0";
		char *timeparam = (char *) input.c_str();
		if((timeparam[0] == 't') && (timeparam[1] = '='))
		{
			ttime = (Time *)malloc(sizeof(Time));
			typedef std::vector<std::string> Tokens;
			Tokens tokens;
			boost::split(tokens, input, boost::is_any_of(" "));
				
			int size = tokens.size();
			int count = 0;
			BOOST_FOREACH( const std::string& i, tokens) {
				switch(count) {
					case 0:
					{
							char* stm = (char *)i.c_str();
							ttime->start_time = (stm + 2);
							std::string start_tm(ttime->start_time);
							std::cout << start_tm << std::endl;
							break;
					}
					case 1:
					{
							char* sto = (char *)i.c_str();
							ttime->stop_time = (sto + 2);
							std::string stop_tm(ttime->stop_time);
							std::cout << stop_tm << std::endl;
							break;
					}
					default:
						    break;
				}
				count++;
			}
		}
		return ttime;
	}
		
	PT 	*SDP_parser::SDP_GetSDPAttributes()  
	{
                vector<std::string> res;
		std::string input = "a=sdplang:en\r\na=range:npt=0- 150.883\r\na=control:*";
                split_regex(res, input, boost::regex("(\r\n)+"));
                for (auto& tok : res) 
                {
                    std::cout << "Token: " << tok << std::endl;
                }
		
		return NULL;
	}
	
	AudioAttribute  *SDP_parser::SDP_GetAudioAttributes()  
        {
		return NULL;
	}
	
	VideoAttribute  *SDP_parser::SDP_GetVideoAttributes()
	{
		return NULL;
	}
	
}

int main(int argc, 	char* argv[])
{
		std::string file,line;
		std::ifstream infile("one.sdp");
		Rtsp::SDP_parser *sdp;
		Rtsp::Owner *owns;
		Rtsp::Connect *cons;
		Rtsp::Time *tms;
		Rtsp::PT *pt;
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
		int cnt_len = sdp->SDP_GetContentLength();
		std::cout << cnt_len << std::endl;
		char *base_url = sdp->SDP_GetContentBaseUrl();
		char *tm = sdp->SDP_GetTimeStamp();
		char *cnt_type = sdp->SDP_GetContentType();
		char *id = sdp->SDP_GetSessionId();
		int  tmout = sdp->SDP_GetTimeout();
		std::cout << tmout << std::endl;
		int ver = sdp->SDP_GetVersion();
		std::cout << "version of v=" << ver << std::endl;
		owns = sdp->SDP_GetOwnerInfo();
		char *sess = sdp->SDP_GetSessionName();
		cons = sdp->SDP_GetConnectionInfo();
		tms  = sdp->SDP_GetTimeParameter();
		pt = sdp->SDP_GetSDPAttributes();
}
