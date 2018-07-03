#ifndef SDP_PARSER_H
#define SDP_PARSER_H

#include <string>

#define RTSP_SDP_CR   0x0D
#define RTSP_SDP_LF   0x0A
#define RTSP_SDP_SP   0X20

#define RTSP_SDP_CRLF 					  "\r\n"
#define RTSP_SDP_CRLFCRLF 				  "\r\n\r\n"

#define RTSP_SDP_CSEQ            			  "CSeq: "
#define RTSP_SDP_SERVER          			  "Server: "
#define RTSP_SDP_CACHE_CONTROL   			  "Cache-Control: "
#define RTSP_SDP_EXPIRE          			  "Expires: "
#define RTSP_SDP_CONTENT_LENGTH  			  "Content-Length: "
#define RTSP_SDP_CONTENT_BASE    			  "Content-Base: "
#define RTSP_SDP_DATE            			  "Date: "
#define RTSP_SDP_CONTENT_TYPE    			  "Content-Type: "
#define RTSP_SDP_SESSION         			  "Session: "
#define RTSP_SDP_ATTRIBUTE_TIMEOUT                        "timeout="

#define RTSP_VERSION_ONE         		          "RTSP/1.0"
#define RTSP_VERSION_TWO         			  "RTSP/2.0"  

#define RTSP_SDP_ATTRIBUTE_LANG               		  "sdplang"
#define RTSP_SDP_ATTRIBUTE_RANGE_NTP          		  "range"
#define RTSP_SDP_ATTRIBUTE_CONTROL            		  "control"



namespace Rtsp{

class SDP_parser {
	private:
	        char *_payload;
		int  size;
		bool decode;
		std::string line;
	
	        // RTSP Describe Header holder
		char *protocol_version;  // need to re-visit them as char * to string
		char *cseq_num;
		char *server;
		char *cache;
		char *expire;
		char *content_len;
		char *content_base_url;
		char *time;
		char *content_type;
		char *content_session;

		// Application SDP holder
			
	
	public:
		SDP_parser();
		SDP_parser(char* data, int len);
		bool SDP_Decode();
		~SDP_parser();
        bool IsRTSPOne();
		int   SDP_GetCSeq();
		char* SDP_GetStreamingServer();
		char* SDP_GetCacheControl();
		char* SDP_GetExpires();
		int   SDP_GetContentLength();
		char* SDP_GetContentBaseUrl();
		char* SDP_GetTimeStamp();
		char* SDP_GetContentType();
		char* SDP_GetSessionId();
		int   SDP_GetTimeout();
    };

}

#endif // SDP_PARSER_H
