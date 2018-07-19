#ifndef SDP_PARSER_H
#define SDP_PARSER_H

#include <boost/property_tree/ptree.hpp>
#include <string>

#define RTSP_SDP_CR   0x0D
#define RTSP_SDP_LF   0x0A
#define RTSP_SDP_SP   0X20

#define RTSP_SDP_CRLF 				    "\r\n"
#define RTSP_SDP_CRLFCRLF 			    "\r\n\r\n"

/* RFC 6871 defines the Session Description Protocol (SDP) Media Capabilities Negotiation */
/* This file implements the parsing of content type "application/sdp" for RTSP DESCRIBE Response */

#define RTSP_SDP_CSEQ            		    "CSeq: "
#define RTSP_SDP_SERVER          		    "Server: "
#define RTSP_SDP_CACHE_CONTROL   		    "Cache-Control: "
#define RTSP_SDP_EXPIRE          		    "Expires: "
#define RTSP_SDP_CONTENT_LENGTH  		    "Content-Length: "
#define RTSP_SDP_CONTENT_BASE    		    "Content-Base: "
#define RTSP_SDP_DATE            		    "Date: "
#define RTSP_SDP_CONTENT_TYPE    		    "Content-Type: "
#define RTSP_SDP_SESSION			    "Session: "
#define RTSP_SDP_ATTRIBUTE_TIMEOUT  		    "timeout="

#define RTSP_VERSION_ONE        		    "RTSP/1.0"
#define RTSP_VERSION_TWO         		    "RTSP/2.0"  

#define RTSP_SDP_ATTRIBUTE_LANG                    "sdplang:"
#define RTSP_SDP_ATTRIBUTE_RANGE_NTP               "range:"
#define RTSP_SDP_ATTRIBUTE_CONTROL                 "control:"
#define RTSP_SDP_ATTRIBUTE_RTPMAP                  "rtpmap:"
#define RTSP_SDP_ATTRIBUTE_FMTP                    "fmtp:"
#define RTSP_SDP_ATTRIBUTE_PROFILE                 "profile-level-id="
#define RTSP_SDP_ATTRIBUTE_MODE                    "mode="
#define RTSP_SDP_ATTRIBUTE_SIZELENGTH              "sizelength="
#define RTSP_SDP_ATTRIBUTE_INDEXLENGTH             "indexlength="
#define RTSP_SDP_ATTRIBUTE_INDEXDELTALENGTH        "indexdeltalength="
#define RTSP_SDP_ATTRIBUTE_CONFIG                  "config="
#define RTSP_SDP_ATTRIBUTE_PACKETIZATION_MODE      "packetization-mode="
#define RTSP_SDP_ATTRIBUTE_SPROP_PARAMETER_SETS    "sprop-parameter-sets="
#define RTSP_SDP_ATTRIBUTE_CLIPRECT                "cliprect:"
#define RTSP_SDP_ATTRIBUTE_FRAMESIZE               "framesize:"
#define RTSP_SDP_ATTRIBUTE_FRAMERATE               "framerate:"
#define RTSP_SDP_ATTRIBUTE_TRACKID                 "trackID="
#define RTSP_SDP_ATTRIBUTE_MEDIAID                 "m="
#define RTSP_SDP_ATTRIBUTE_MEDIA_SUB_ATTRIBUTE_ID  "a="


namespace Rtsp{
using boost::property_tree::ptree;

typedef struct {
			char *username;
			int   sessionID;
			int   session_version;
			char *networktype;
			char *address_type;  // IP4 IP6
			char *address;       // XX.XX.XX.XX
		}Owner;
		typedef struct {
			char *networktype;   // IN 
			char *address_type;  // IP4 IP6
			char *address;       // XX.XX.XX.XX
		}Connect;
		
		typedef struct {
			char *start_time;    // UTC Time
			char *stop_time;     // UTC Time
		}Time;
		
		typedef struct {
			ptree *pt;
		}PT;
	
	    typedef struct {
			char  *audio_RTPAVP;
			int   rtpmap;
			char *codec_rate;
			int   fmtp;
			int   profile_level_id;
			char *mode;
			int   sizelength;
			int   indexlength;
			int   indexdeltalength;
			int   config;
			char  *control;
		}AudioAttribute;
		
		typedef struct {
			int x1;
			int y1;
			int x2;
			int y2;
		}cliprect;
		
		typedef struct {
			char     *video_RTPAVP;	
			int       rtpmap;
			char     *codec_rate;
			int       fmtp;
			int       packetization_mode;
			char     *profile_level_id;
			char     *sprop_parameter_sets;
			cliprect *rect;                                          
			int       framesize;
			int       width;
			int       height;
			char     *framerate;
			char     *control;
		}VideoAttribute;

class SDP_parser {
	private:
		std::string _payload;
		int  size;
		bool decode;
	
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
		char *timeout;

		// Application SDP holder
	public:
		std::string input;
		int   version;
		Owner *owner;
		char *session_name;
		Connect *connect;
		Time    *ttime;
		PT      *ppt;
		AudioAttribute  *aat;
		VideoAttribute  *vat; 
	public:
		SDP_parser();
		SDP_parser(std::string data, int len);
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
		
		int      		 SDP_GetVersion();          // v= 
		Owner   		*SDP_GetOwnerInfo();        // o=
		char    		*SDP_GetSessionName();      // s=
		Connect 		*SDP_GetConnectionInfo();   // c=
		Time    		*SDP_GetTimeParameter();    // t=
		PT 			*SDP_GetSDPAttributes();    // a=<attribute>:<value>  
		AudioAttribute  *SDP_GetAudioAttributes();  // m= audio (rtpmap,ftmp,profile-level-id,
		                                            //           mode,sizelength,indexlength,
						    	    //           indexdeltalength,config)
                                                            //           control)
                VideoAttribute  *SDP_GetVideoAttributes();  // m= video (rtpmap,ftmp,packetization-mode,
                                                            //           profile-level-id,sprop-parameter-sets,
                                                            //           cliprect:(X1,Y1,X2,Y2)
                                                            //           framesize:XX width:height
                                                            //           framerate:xx.xx
                                                            //           control)                                                        
		                           
    };

}

#endif // SDP_PARSER_H
