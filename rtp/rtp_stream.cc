#include <fstream>
#include <stdint.h>
#include <cstring>
#include "rtp_stream.h"

namespace Rtp
{
      RTP_Stream::RTP_Stream()
      {
          rtp_file.open(name, std::fstream::out | std::fstream::binary);
          size = 0;
          std::cout << "Entering the RTP_Stream" << name << std::endl;
      }

      void RTP_Stream::RTP_Stream_write_nal()
      {
          uint8_t nal_header[4] = {0x00, 0x00, 0x00, 0x01};

          rtp_file.seekg(0, rtp_file.end);
          rtp_file.write((const char*)&nal_header, 4 * sizeof(uint8_t));
          size = size + (4 * sizeof(uint8_t));
          rtp_file.flush();
      }

      void RTP_Stream::RTP_Stream_write(void *buf, size_t count)
      {
          rtp_file.seekg(0, rtp_file.end);
          rtp_file.write((const char*)buf, count * sizeof(uint8_t));
          size = size + (count * sizeof(uint8_t));
          std::cout << "********** File COUNT **********" << size << std::endl;
          rtp_file.flush();
      }

      RTP_Stream::~RTP_Stream()
      {
          rtp_file.close();
      }
}

