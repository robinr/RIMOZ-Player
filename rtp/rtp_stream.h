#ifndef RTP_STREAM_H
#define RTP_STREAM_H

#include <iostream>
#include <fstream>
#include <stdint.h>


namespace Rtp
{
      class RTP_Stream {
                public:
                        RTP_Stream();
                        void RTP_Stream_write_nal();
                        void RTP_Stream_write(void *buf, size_t count);
                        ~RTP_Stream();
                private:
                        std::fstream rtp_file;
                        char *name="h264dump.sock";
                        int size;
                };
}

#endif // RTP_STREAM_H
