#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <stdint.h>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <boost/asio.hpp>
#include <vector>
#include "http_header.hpp"
#include "rtp_header.h"
#include "rtp_nal.h"
#include "rtp_stats.h"
#include "rtp_stream.h"
#include "rtsp_receiver.h"

using namespace std;
using namespace Rtp;
using namespace http;
using namespace Rtsp;
using namespace boost::asio;
using namespace boost::system;

int main (int argc, char* argv[])
{
    try
    {
        if (argc != 4)
        {
            std::cout << "Usage: rtsp_client <server> <port> <path> \n" << std::endl;
            std::cout << "Example:\n";
            std::cout << " rtsp_client 192.168.1.4 8554 /vod/one.mp4 \n";
        } 

        io_service io_service;

        // Get a list of endpoints corresponding to the server name.
        ip::tcp::resolver resolver(io_service);
        ip::tcp::resolver::query query(ip::tcp::v4(), argv[1], argv[2]);
        ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        ip::tcp::resolver::iterator end;

        // Try each endpoint until we successfully establish a connection.
        ip::tcp::socket socket(io_service);
        error_code error = error::host_not_found;
        while (error && endpoint_iterator != end)
        {
            socket.close();
            socket.connect(*endpoint_iterator++, error);
        }
        if (error)
            throw system_error(error);

        http::HTTP_helper http_helper;
        int port = atoi(argv[2]);
        char *request;
        char *path = (char *) argv[3];

        Rtsp::Rtsp_receiver *rtsp_receiver = new Rtsp_receiver(argv[1],port,path);
        for(size_t i=0; i<4; i++)
        {
          const char *requests = rtsp_receiver->Rtsp_GenerateRequest(request, (int)i);
          int req_len = strlen(requests);
          std::cout << requests << std::endl;
          boost::asio::write(socket,boost::asio::buffer(requests,req_len));

          std::vector<uint8_t> reply;
          reply.reserve(2048);

          do {
              std::vector<uint8_t> buf;
              buf.resize(2048);

              size_t bytes =
			     socket.read_some(boost::asio::buffer(&buf[0],buf.size()));
              buf.resize(bytes);

              std::cout << "Data Obtained as response" << std::endl;

              //std::cout << buf.data() << std::endl;
              http_helper.consume(buf.begin(),buf.end());
              reply.clear();
              http_helper.product(std::back_inserter(reply));
          } while (reply.empty());

          copy(reply.begin(), reply.end(), ostream_iterator<char>(cout));
        }
        RTP_Stats *pkt = new RTP_Stats();
        while (1)
        {
                std::vector<uint8_t> buf;
                buf.resize(4096);
                size_t bytes =
                    socket.read_some(boost::asio::buffer(&buf[0],buf.size()));
                buf.resize(bytes);

                if (buf.empty()) { std::cout << "Exiting the loop " << std::endl; break; }

                unsigned int  raw_offset = pkt->RTP_Parse(buf.data(),bytes);
                std::cout << "****** raw_offset *******" << raw_offset << std::endl;
                //sleep(1);
                
        }
    }
    catch (std::exception& e)
    {
          std::cout << "Exception" << e.what() << "\n";
    }
    return 0;
}

