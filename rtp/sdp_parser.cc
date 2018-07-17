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
#include <stdlib.h>




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
		int count = 0;
		std::string input = "a=sdplang:en\r\na=range:npt=0- 150.883\r\na=control:*";
		split_regex(res, input, boost::regex("(\r\n)+"));
		ppt = (PT *)malloc(sizeof(PT));
		for (auto& tok : res) 
		{
			switch(count){
				case 0 :
				{
					
					std::string token = RTSP_SDP_ATTRIBUTE_LANG;
					std::string result = get_right_of_delim(tok,token);
					char *value = (char *) result.c_str();
					ppt->pt = new ptree();
					ppt->pt->put("sdplang",value);
					std::cout << "sdplang  " << result << std::endl;
					break;
				}
				case 1:
				{
					std::string token = RTSP_SDP_ATTRIBUTE_RANGE_NTP;
					std::string result = get_right_of_delim(tok,token);
					char *value = (char *) result.c_str();
					ppt->pt->put("range",value);
					std::cout << "range  " << result<< std::endl;
					break;
				}
				case 2:
				{
					std::string token = RTSP_SDP_ATTRIBUTE_CONTROL;
					std::string result = get_right_of_delim(tok,token);
					char *value = (char *)result.c_str();
					ppt->pt->put("control",value);
					std::cout << "control " << result << std::endl;
					break;
				}
				default:
					break;
			}
			count++;
			//std::cout << "Token: " << tok << std::endl;
		}
		
		return ppt;
	}
	
	AudioAttribute  *SDP_parser::SDP_GetAudioAttributes()  
	{
		vector<std::string> res;
		int count = 0;
		std::string input = "m=audio 0 RTP/AVP 96\r\na=rtpmap:96 mpeg4-generic/44100/2\r\na=fmtp:96 profile-level-id=1;mode=AAC-hbr;sizelength=13;indexlength=3;indexdeltalength=3;config=1210\r\na=control:trackID=1\r\n";
		split_regex(res, input, boost::regex("(\r\n)+"));
        aat = (AudioAttribute *)malloc(sizeof(AudioAttribute));
		for (auto& tok : res) 
		{
			switch(count){
				case 0:
				{
					  std::string token = RTSP_SDP_ATTRIBUTE_MEDIAID;
					  std::string result = get_right_of_delim(tok,token);
				      aat->audio_RTPAVP = (char *)result.c_str();
					  std::cout << "RTPAVP" << result << std::endl;
					  break;
				}
				case 1:
				{
				      std::string split_me(tok);
					  typedef std::vector<std::string> SubTokens;
					  SubTokens subst;
					  int subcount = 0;
					  boost::split(subst, split_me,boost::is_any_of(" "));
					  BOOST_FOREACH( const std::string& i, subst) {
						  if(subcount == 0)
						  {
							  std::string indelim = RTSP_SDP_ATTRIBUTE_RTPMAP;
							  std::string resultrtp = get_right_of_delim(i ,indelim);
							  char *rtpmap = (char *)resultrtp.c_str();
							  aat->rtpmap = atoi(rtpmap);
							  std::cout << "inner value of rtpmap " << aat->rtpmap << std::endl;
						  }
						  if(subcount == 1)
						  {
							  aat->codec_rate = (char *)i.c_str();
						  }
						  subcount++;
						  std::cout << i << std::endl;
					  }
					  break;
				}				
				case 2:
				{
					  std::string split_me(tok);
					  typedef std::vector<std::string> SubTokens;
					  SubTokens subst;
					  int subcount = 0;
					  boost::split(subst, split_me,boost::is_any_of(" "));
					  BOOST_FOREACH( const std::string& i, subst) {
						  if(subcount == 0)
						  {
							  std::string indelim = RTSP_SDP_ATTRIBUTE_FMTP;
							  std::string resultfmtp = get_right_of_delim(i ,indelim);
							  char *fmtpmap = (char *)resultfmtp.c_str();
							  aat->fmtp = atoi(fmtpmap);
							  std::cout << "inner value of fmtp " << aat->fmtp << std::endl;
						  }
						  if(subcount == 1)
						  {
							  std::string split_inme(i);
					          typedef std::vector<std::string> SubInnerTokens;
							  SubInnerTokens subinst;
					          int subincount = 0;
					          boost::split(subinst, split_inme,boost::is_any_of(";"));
							  
								BOOST_FOREACH( const std::string& j, subinst) {
									switch(subincount){
										case 0:
										{
											std::string in_delim = RTSP_SDP_ATTRIBUTE_PROFILE;
											std::string profile = get_right_of_delim(j,in_delim);
											char *prof = (char *)profile.c_str();
											aat->profile_level_id = atoi(prof);
											std::cout << "profile id : " << aat->profile_level_id << std::endl;
											break;
										}
										case 1:
										{
											std::string in_delim = RTSP_SDP_ATTRIBUTE_MODE;
											std::string mode = get_right_of_delim(j,in_delim);
											char *md = (char *)mode.c_str();
											aat->mode = md;
											std::cout << "mode : " << mode << std::endl;
											break;
										}
										case 2:
										{
											std::string in_delim =  RTSP_SDP_ATTRIBUTE_SIZELENGTH;
											std::string sizelength = get_right_of_delim(j,in_delim);
											char *szlen = (char *)sizelength.c_str();
											aat->sizelength = atoi(szlen);
											std::cout << "size length : " << aat->sizelength << std::endl;
											break;
										}
										case 3:
										{
											std::string in_delim = RTSP_SDP_ATTRIBUTE_INDEXLENGTH;
											std::string idxlength = get_right_of_delim(j, in_delim);
										    char *idlen = (char *)idxlength.c_str();
											aat->indexlength = atoi(idlen);
											std::cout << "index length :" << aat->indexlength << std::endl;
											break;
										}
										case 4:
										{
											std::string in_delim = RTSP_SDP_ATTRIBUTE_INDEXDELTALENGTH;
											std::string idxdeltalen = get_right_of_delim(j, in_delim);
											char* iddellen = (char *)idxdeltalen.c_str();
											aat->indexdeltalength = atoi(iddellen);
											std::cout << "index delta length :" << aat->indexdeltalength << std::endl;
											break;
										}
										case 5:
										{
											std::string in_delim = RTSP_SDP_ATTRIBUTE_CONFIG;
											std::string cfg = get_right_of_delim(j, in_delim);
											char *cfgid = (char *)cfg.c_str();
											aat->config = atoi(cfgid);
											std::cout << "config : " << aat->config << std::endl;
											break;
										}
										default:
											break;
									}
									subincount++;	
									//std::cout << "tokens" << j << std::endl;
								}
								
							}
							  //std::cout << "part 2" << i << std::endl;
						subcount++;
						}
					//std::cout << tok << std::endl;
					break;
				}
				case 3:
				{
					  std::string deli = RTSP_SDP_ATTRIBUTE_CONTROL;
					  std::string result = get_right_of_delim(tok,deli);
					  char *track = (char *)result.c_str();
					  aat->control = track;
				      std::cout << result << std::endl;
					  break;
				}
				default:
					break;
			}
			count++;
		}
		return NULL;
	}
	
	VideoAttribute  *SDP_parser::SDP_GetVideoAttributes()
	{
		vector<std::string> res;
		std::string input ="m=video 0 RTP/AVP 97\r\na=rtpmap:97 H264/90000\r\na=fmtp:97 packetization-mode=1;profile-level-id=4D401E;sprop-parameter-sets=Z01AHuiAUBf8uAiAAAH0gABdwAeLFok=,aOvvIA==\r\na=cliprect:0,0,360,640\r\na=framesize:97 640-360\r\na=framerate:23.98\r\na=control:trackID=2";
		int count = 0;
		split_regex(res, input, boost::regex("(\r\n)+"));
		vat = (VideoAttribute *)malloc(sizeof(VideoAttribute));
		for (auto& tok : res) 
		{
			switch(count){
				case 0:
				{
					std::string token = RTSP_SDP_ATTRIBUTE_MEDIAID;
					std::string result = get_right_of_delim(tok,token);
					vat->video_RTPAVP = (char *)result.c_str();
					std::cout << "RTPAVP" << result << std::endl;
					break;
				}
				case 1:
				{
					std::string split_me(tok);
					typedef std::vector<std::string> SubTokens;
					SubTokens subst;
					int subcount = 0;
					boost::split(subst, split_me,boost::is_any_of(" "));
					BOOST_FOREACH( const std::string& i, subst) {
						  if(subcount == 0)
						  {
							  std::string indelim = RTSP_SDP_ATTRIBUTE_RTPMAP;
							  std::string resultrtp = get_right_of_delim(i ,indelim);
							  char *rtpmap = (char *)resultrtp.c_str();
							  vat->rtpmap = atoi(rtpmap);
							  std::cout << "inner value of rtpmap " << aat->rtpmap << std::endl;
						  }
						  if(subcount == 1)
						  {
							  vat->codec_rate = (char *)i.c_str();							  
						  }
						subcount++;
					}
					//std::cout << "lines " << tok << std::endl;
					break;
				}
				case 2:
				{
					std::string split_me(tok);
					  typedef std::vector<std::string> SubTokens;
					  SubTokens subst;
					  int subcount = 0;
					  boost::split(subst, split_me,boost::is_any_of(" "));
					  BOOST_FOREACH( const std::string& i, subst) {
						  if(subcount == 0)
						  {
							  std::string indelim = RTSP_SDP_ATTRIBUTE_FMTP;
							  std::string resultfmtp = get_right_of_delim(i ,indelim);
							  char *fmtpmap = (char *)resultfmtp.c_str();
							  vat->fmtp = atoi(fmtpmap);
							  std::cout << "inner value of fmtp " << vat->fmtp << std::endl;
						  }
						  if(subcount == 1)
						  {
							  //std::cout << "residue" << i << std::endl;
						  std::string split_inme(i);
					          typedef std::vector<std::string> SubInnerTokens;
							  SubInnerTokens subinst;
					          int subincount = 0;
					          boost::split(subinst, split_inme,boost::is_any_of(";"));
							  
								BOOST_FOREACH( const std::string& j, subinst) {
									switch(subincount){
										case 0:
										{
											std::string delim = RTSP_SDP_ATTRIBUTE_PACKETIZATION_MODE;
											std::string result = get_right_of_delim(j, delim);
											char *packet = (char *)result.c_str();
											vat->packetization_mode = atoi(packet);
											std::cout << "Packetization Mode  " << vat->packetization_mode << std::endl;
											break;
										}
										case 1:
										{
											std::string delim = RTSP_SDP_ATTRIBUTE_PROFILE;
											std::string result = get_right_of_delim(j,delim);
											vat->profile_level_id = (char *)result.c_str();
											std::cout << "Profile Level ID  " << result << std::endl;
											break;
										}
										case 2:
										{
											std::string delim = RTSP_SDP_ATTRIBUTE_SPROP_PARAMETER_SETS;
											std::string result = get_right_of_delim(j,delim);
											vat->sprop_parameter_sets = (char *)result.c_str();
											std::cout << "Profile Level ID  " << result << std::endl;
											break;
										}
										default:
											break;
									}
									subincount++;
						  }
					  }
					  subcount++;
					}
					//std::cout << "lines " <<tok << std::endl;
					break;
				}
				case 3:
				{
					std::string delim = RTSP_SDP_ATTRIBUTE_CLIPRECT;
					std::string result = get_right_of_delim(tok,delim);
					std::string split_me(result);
					  typedef std::vector<std::string> SubTokens;
					  SubTokens subst;
					  int subcount = 0;
					  boost::split(subst, split_me,boost::is_any_of(","));
					  vat->rect = (cliprect *)malloc(sizeof(cliprect));
					  BOOST_FOREACH( const std::string& i, subst) {
							if (subcount == 0)
							{
								char *x1 = (char *)i.c_str();
								vat->rect->x1 = atoi(x1);
								std::cout << "X1 value" << vat->rect->x1 << std::endl;
							}
							if (subcount == 1)
							{
								char *y1 = (char *)i.c_str();
								vat->rect->y1 = atoi(y1);
								std::cout << "Y1 value" << vat->rect->y1 << std::endl;
							}
							if (subcount == 2)
							{
								char *y2 = (char *)i.c_str();
								vat->rect->y2 = atoi(y2);
								std::cout << "Y2 value" << vat->rect->y2 << std::endl;
							}
							if (subcount == 3)
							{
								char *x2 = (char *)i.c_str();
								vat->rect->x2 = atoi(x2);
								std::cout << "X2 value" << vat->rect->x2 << std::endl;
							}
							subcount++;
						  }
					//std::cout << "lines " <<tok << std::endl;
					break;
				}
				case 4:
				{
					std::string delim = RTSP_SDP_ATTRIBUTE_FRAMESIZE;
					std::string result = get_right_of_delim(tok,delim);
					std::string split_me(result);
					  typedef std::vector<std::string> SubTokens;
					  SubTokens subst;
					  int subcount = 0;
					  boost::split(subst, split_me,boost::is_any_of(" "));
					  BOOST_FOREACH( const std::string& i, subst) {
							if (subcount == 0)
							{
								char *frmrt = (char *)i.c_str();
								vat->framesize = atoi(frmrt);
								std::cout << "FrameSize :" << vat->framesize << std::endl;
							}
							if (subcount == 1)
							{
								std::string width_height(i);
								typedef std::vector<std::string> SubinTokens;
								SubinTokens subintk;
								int subincount = 0;
								boost::split(subintk, width_height,boost::is_any_of("-"));
								BOOST_FOREACH( const std::string& j, subintk) {
									if(subincount == 0)
									{
										char *wdth = (char *)j.c_str();
										vat->width = atoi(wdth);
										std::cout << " Width " << vat->width << std::endl;
									}
									if(subincount == 1)
									{
										char *hth = (char *)j.c_str();
										vat->height = atoi(hth);
										std::cout << " Height " << vat->height << std::endl;
									}
									subincount++;
								}
								//std::cout << "width-height" << i << std::endl;
							}
							subcount++;
					  }
					//std::cout << "lines " <<tok << std::endl;
					break;
				}
				case 5:
				{
					std::string delim = RTSP_SDP_ATTRIBUTE_FRAMERATE;
					std::string result = get_right_of_delim(tok,delim);
					char *fmrate = (char *)result.c_str();
					vat->framerate = fmrate;
					std::cout << "FrameRate :" << result << std::endl;
					//std::cout << "lines " << tok << std::endl;
					break;
				}
				case 6:
				{
					std::string delim = RTSP_SDP_ATTRIBUTE_TRACKID;
					std::string result = get_right_of_delim(tok,delim);
					char *ctrl = (char *)result.c_str();
					vat->control = ctrl;
					std::cout << "Control :" << result << std::endl;
					//std::cout << "lines " << tok << std::endl;
					//std::cout << "lines " <<tok << std::endl;
					break;
				}
				default:
					break;
			}
			count++;
		}
		return vat;
	}
}

int main(int argc,char* argv[])
{
		std::string file,line;
		std::ifstream infile("one.sdp");
		Rtsp::SDP_parser *sdp;
		Rtsp::Owner *owns;
		Rtsp::Connect *cons;
		Rtsp::Time *tms;
		Rtsp::PT *pt;
		Rtsp::AudioAttribute *at;
		Rtsp::VideoAttribute *vt;
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
		at = sdp->SDP_GetAudioAttributes();
		vt = sdp->SDP_GetVideoAttributes();
}
