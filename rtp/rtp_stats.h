#ifndef RTP_STATS_H
#define RTP_STATS_H

#include <stdint.h>
#include "rtp_header.h"
#include "rtp_nal.h"
#include "rtp_stream.h"

#define  RTP_FREQ        9000
#define  RTP_SPROP       "sprop-parameter-sets="

namespace Rtp
{

   class RTP_Stats {
         /*
         * Agregation packet - STAP-A
         * ------
         * http://www.ietf.org/rfc/rfc3984.txt
         *
         * 0                   1                   2                   3
         * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
         * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         * |                          RTP Header                           |
         * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         * |STAP-A NAL HDR |         NALU 1 Size           | NALU 1 HDR    |
     	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     	 * |                         NALU 1 Data                           |
      	 * :                                                               :
     	 * +               +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     	 * |               | NALU 2 Size                   | NALU 2 HDR    |
     	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     	 * |                         NALU 2 Data                           |
     	 * :                                                               :
     	 * |                               +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     	 * |                               :...OPTIONAL RTP padding        |
         * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         */
         private:
                   uint16_t first_seq;                        /* first sequence                     */
                   uint16_t highest_seq;                      /* highest sequence                   */
                   uint16_t rtp_received;                     /* RTP sequence number received       */
                   uint32_t rtp_identifier;                   /* source identifier                  */
                   uint32_t rtp_ts;                           /* RTP timestamp                      */
                   uint32_t rtp_cum_lost;                     /* RTP cumulative packet lost         */
                   uint32_t rtp_expected_prior;               /* RTP expected prior                 */
                   uint32_t rtp_received_prior;               /* RTP received prir                  */
                   uint32_t transit;                          /* Transit time. RFC3550 A.8          */
                   uint32_t jitter;                           /* Jitter                             */
                   uint32_t lst;
                   uint32_t last_dslr;                        /* Last DLSR                          */
                   uint32_t last_rcv_SR_ts;                   /* Last arrival in RTP format         */
                   uint32_t delay_snc_last_SR;                /* Delay sinde last SR                */
                   struct timeval last_rcv_SR_time;           /* Last SR arrival                    */
                   struct timeval last_rcv_time;
                   double rtt_frac;
          public:
                   RTP_Stats();
                   uint64_t RTP_TimeVal_To_Ntp(struct timeval *tv);
                   void     RTP_Stats_Update(RTP_Header rtp_h);
                   void     RTP_Stats_Reset(void);
                   void     RTP_Stats_Print(void);
                   unsigned int RTP_Parse(unsigned char * raw, unsigned int size);
                   RTP_Header *rtp_header;
                   RTP_Nal    *nal_header;
                   RTP_Stream *rtp_stm;
                   static const int RTP_BUFFER_SIZE  = 8*1024;
          };
}

#endif
