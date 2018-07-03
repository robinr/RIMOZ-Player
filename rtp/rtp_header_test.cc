
#include <iostream>
#include <stdint.h>
#include <string.h>
#include "rtp_header.h"
#include "rtp_stats.h"
#include "rtp_nal.h"
#include "rtp_stream.h"

using namespace std;
using namespace Rtp;

int main()
{
    unsigned char test_buff[20] = { 0x80, 0x80, 0x25, 0x26, 0x27, 0x28, 0x29, 0x30, 0x23, 0x24, 0x25, 0x26, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    unsigned int size = 20;
    RTP_Stats *pkt = new RTP_Stats();
    uint64_t status = pkt->RTP_Parse(test_buff, size);
    return 0;
}
