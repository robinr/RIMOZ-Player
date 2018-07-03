#include "rtp_header.h"
#include "rtp_nal.h"
#include "rtp_stats.h"
#include <stdint.h>
#include <sys/time.h>

namespace Rtp
{
     uint64_t RTP_Stats::RTP_TimeVal_To_Ntp(struct timeval *tv)
     {
              uint64_t msw;
              uint64_t lsw;

              /* 0x83AA7E80 is the number of seconds from 1900 to 1970 */
              msw = tv->tv_sec + 0x83AA7E80;
              lsw = (uint32_t)((double)tv->tv_usec*(double)(((uint64_t)1)<<32)*1.0e-6);

              return ((msw << 32) | lsw);
     }

     void RTP_Stats::RTP_Stats_Update(RTP_Header rtp_h)
     {
         uint32_t utransit;
         int      delta;
         struct   timeval now;
         int      sequence;

         gettimeofday(&now, NULL);
         rtp_received++;

         /* Highest sequence */
         sequence = rtp_h.RTP_GetSequenceNumber();
         if(sequence > highest_seq) {
              highest_seq = sequence;
         }

         /* Update RTP timestamp */
         if(last_rcv_time.tv_sec == 0)
         {
             first_seq = sequence;
             gettimeofday(&last_rcv_time, NULL);
         }

         transit = delay_snc_last_SR;
         delta = utransit - transit;
         transit = utransit;
         if(delta < 0) {
              delta = -delta;
         }

         jitter +=((1.0/16.0) * ((double) delta - jitter));

         rtp_ts = rtp_h.RTP_GetTimeStamp();
         RTP_Stats_Print();
     }

     void RTP_Stats::RTP_Stats_Print()
     {
           std::cout << ">> RTP Status " << std::endl;
           std::cout << "     First Sequence   : " << first_seq << std::endl;
           std::cout << "     Highest Sequence : " << highest_seq << std::endl;
           std::cout << "     RTP Received     : " << rtp_received << std::endl;
           std::cout << "     RTP Identifier   : " << rtp_identifier << std::endl;
           std::cout << "     RTP Timestamp    : " << rtp_ts << std::endl;
           std::cout << "     Jitter           : " << jitter << std::endl;
           std::cout << "     Last DLSR        : " << last_dslr << std::endl;
     }

     RTP_Stats::RTP_Stats()
     {
            first_seq    = 0x00;
            highest_seq  = 0x00;
            rtp_received = 0x00;
            rtp_identifier = 0x0000;
            rtp_ts         = 0x0000;
            rtp_cum_lost   = 0x0000;
            rtp_expected_prior = 0x0000;
            rtp_received_prior = 0x0000;
            transit            = 0x0000;
            jitter             = 0x0000;
            lst                = 0x0000;
            last_dslr          = 0x0000;
            last_rcv_SR_ts     = 0x0000;
            delay_snc_last_SR  = 0x0000;
            last_rcv_SR_time.tv_sec = 0;
            last_rcv_SR_time.tv_usec = 0;
            last_rcv_time.tv_sec = 0;
            last_rcv_time.tv_usec = 0;
            rtt_frac = 0.0;
            rtp_header = NULL;
            nal_header = NULL;
            rtp_stm = new RTP_Stream();
      }

     unsigned int RTP_Stats::RTP_Parse(unsigned char *raw, unsigned int size)
     {
         unsigned int raw_offset = 0;
         unsigned int rtp_length = size;
         unsigned int paysize;
         unsigned char payload[RTP_BUFFER_SIZE];
         int nal_type;

         rtp_header = new RTP_Header((char *)raw, (size_t)size);

         if(rtp_header->RTP_IsParsed() == false)
         {
                rtp_identifier = rtp_header->RTP_GetSequenceNumber();
                raw_offset = rtp_header->offset;
                paysize = rtp_length - raw_offset;

                memset(payload, '\0', sizeof(payload));
                memcpy(&payload, raw + raw_offset, paysize);

                //RTP_Stats_Update(*rtp_header);

                nal_header = new RTP_Nal((char *)payload,paysize);
                /* Single NAL unit packet */
                nal_type = nal_header->RTP_GetNalType();
                std::cout << "Nal Type is ===>" << nal_type << std::endl;

                if(nal_type >= NAL_TYPE_SINGLE_NAL_MIN &&
                   nal_type <= NAL_TYPE_SINGLE_NAL_MAX) {

                   /* Write NAL header */
                   std::cout << "Entering to write in file" << std::endl;
                   rtp_stm->RTP_Stream_write_nal();
                   std::cout << "Wrote the header data" << std::endl;

                   /* Write NAL unit */
                   rtp_stm->RTP_Stream_write(payload, paysize);

                }
                else if(nal_type == NAL_TYPE_STAP_A) {
                   uint8_t *q;
                   uint16_t nalu_size;

                   q = payload + 1;
                   int nidx = 0;

                   while(nidx < paysize - 1) {
                   /* Write NAL unit */
                    rtp_stm->RTP_Stream_write_nal();

                   /* get NALU size */
                    nalu_size = (q[nidx] << 8) | (q[nidx + 1]);
                     std::cout << "nidx = " << nidx << "NAL size = " << nalu_size << " RAW offset =" << raw_offset << std::endl;
                    nidx +=2;

                    rtp_stm->RTP_Stream_write(&nalu_size, 1);

                    if(nalu_size == 0) {
                        nidx++;
                        continue;
                    }

                   /* write NAL data */
                   rtp_stm->RTP_Stream_write(q + nidx, nalu_size);
                   nidx +=nalu_size;
                  }
                }
                else if(nal_type == NAL_TYPE_FU_A) {
                    std::cout << "Fragmentation Unit"  << std::endl;

                    uint8_t *q;
                    q = payload;

                    uint8_t h264_start_bit = q[1] & 0x80;
                    uint8_t h264_end_bit   = q[1] & 0x40;
                    uint8_t h264_type      = q[1] & 0x1F;
                    uint8_t h264_nri       = (q[0] & 0x60) >> 5;
                    uint8_t h264_key       = (h264_nri << 5) | h264_type;

                    if (h264_start_bit) {
                       /* write NAL header */
                       rtp_stm->RTP_Stream_write_nal();
                       /* write NAL data */
                       rtp_stm->RTP_Stream_write(&h264_key, sizeof(h264_key));
                    }

                    rtp_stm->RTP_Stream_write(q + 2, paysize -2);
                    if (h264_end_bit) {
                        /* nothing to do .. */
                    }
                }
                else if(nal_type == NAL_TYPE_UNDEFINED || nal_type == NAL_TYPE_FU_B || nal_type == NAL_TYPE_OUT_OF_RANGE || nal_type == NAL_TYPE_INVALID) {

                }
          else {
                std::cout << "OTHER NAL!:" << std::endl;
                raw_offset++;
          }
          raw_offset += paysize;

          if(rtp_header->RTP_GetSequenceNumber() > highest_seq) {
                 highest_seq = rtp_header->RTP_GetSequenceNumber();
          }
        }
         //RTP_Stats_Print();
         return raw_offset;
     }

}
