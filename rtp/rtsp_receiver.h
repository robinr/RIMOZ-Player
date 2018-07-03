#ifndef RTSP_RECEIVER_H
#define RTSP_RECEIVER_H

#include <string>

using namespace std;
namespace Rtsp
{

// supported commands
enum RTSP_CMD_TYPES
{
     RTSP_OPTIONS,
     RTSP_DESCRIBE,
     RTSP_SETUP,
     RTSP_PLAY,
     RTSP_TEARDOWN,
     RTSP_UNKNOWN
};

class Rtsp_receiver
{
      public:
             Rtsp_receiver(char *ipaddress, int portnumber, char *path);
             ~Rtsp_receiver();
             const char *Rtsp_GenerateRequest(char *request, int cmd_type);
      private:
             char *_server_address;
             int  _portnumber;
             char *_path;
             std::string response;


             void Rtsp_OPTIONS();
             void Rtsp_DESCRIBE();
             void Rtsp_SETUP();
             void Rtsp_PLAY();

   };
}

#endif
