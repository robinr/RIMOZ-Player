#include "rtsp_receiver.h"
#include <string>
#include <sstream>

namespace Rtsp
{

        Rtsp_receiver::Rtsp_receiver(char *ipaddress, int portnumber, char *path)
        {
            _server_address = ipaddress;
            _portnumber = portnumber;
            _path = path;
        }

        Rtsp_receiver::~Rtsp_receiver()
        {
            _server_address = NULL;
            _portnumber = 0;
        }

        void Rtsp_receiver::Rtsp_OPTIONS()
        {
                ostringstream oss("");
                response.clear();
                response.append("OPTIONS rtsp://");
                response.append(_server_address);
                response.append(":");
                oss << _portnumber;
                response.append(oss.str());
                response.append("/");
                response.append(_path);
                response.append(" RTSP/1.0\r\n");
                response.append("CSeq: 1\r\n");
                response.append("\r\n");

        }

        void Rtsp_receiver::Rtsp_DESCRIBE()
        {
                ostringstream oss("");
                response.clear();
                response.append("DESCRIBE rtsp://");
                response.append(_server_address);
                response.append(":");
                oss << _portnumber;
                response.append(oss.str());
                response.append("/");
                response.append(_path);
                response.append(" RTSP/1.0\r\n");
                response.append("CSeq: 1\r\n");
                response.append("Accept: application/sdp\r\n");
                response.append("\r\n");
        }

        void Rtsp_receiver::Rtsp_SETUP()
        {
                ostringstream oss("");
                response.clear();
                response.append("SETUP rtsp://");
                response.append(_server_address);
                response.append(":");
                oss << _portnumber;
                response.append(oss.str());
                response.append("/");
                response.append(_path);
                response.append("/trackID=2");
                response.append(" RTSP/1.0\r\n");
                response.append("CSeq 3\r\n");
                response.append("Transport: RTP/AVP/TCP;unicast;interleaved=0-1\r\n");
                response.append("\r\n");
        }

        void Rtsp_receiver::Rtsp_PLAY()
        {
                ostringstream oss("");
                response.clear();
                response.append("PLAY rtsp://");
                response.append(_server_address);
                response.append(":");
                oss << _portnumber;
                response.append(oss.str());
                response.append("/");
                response.append(_path);
                response.append(" RTSP/1.0\r\n");
                response.append("CSeq 4\r\n");
                response.append("Session: 1111111\r\n");
                response.append("Range: npt=0.00-\r\n");
                response.append("\r\n");
        }

        const char *Rtsp_receiver::Rtsp_GenerateRequest(char *request, int cmd_type)
        {
             switch(cmd_type){
                    case RTSP_OPTIONS:
                    {
                        Rtsp_OPTIONS();
                        break;
                    }
                    case RTSP_DESCRIBE:
                    {
                        Rtsp_DESCRIBE();
                        break;
                    }
                    case RTSP_SETUP:
                    {
                        Rtsp_SETUP();
                        break;
                    }
                    case RTSP_PLAY:
                    {
                        Rtsp_PLAY();
                        break;
                    }
                    default:
                    {
                        return NULL;
                    }
            }
           return response.c_str();
        }

}

