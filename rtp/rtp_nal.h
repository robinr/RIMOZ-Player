#ifndef RTP_NAL_H
#define RTP_NAL_H

#define PAYLOAD_MAX 1000000
namespace Rtp
{
          enum {
                 NAL_TYPE_UNDEFINED = 0,
                 NAL_TYPE_SINGLE_NAL_MIN = 1,
                 NAL_TYPE_SINGLE_NAL_MAX = 23,
                 NAL_TYPE_STAP_A         = 24,
                 NAL_TYPE_FU_A           = 28,
                 NAL_TYPE_FU_B           = 29,
                 NAL_TYPE_OUT_OF_RANGE   = 30,
                 NAL_TYPE_INVALID        = 31
               };
           class RTP_Nal {
                        /*
                         * NAL, first byte header
                         *   +---------------+
                         *   |0|1|2|3|4|5|6|7|
                         *   +-+-+-+-+-+-+-+-+
                         *   |F|NRI|  Type   |
                         *   +---------------+
                         */
                private:
                         int nal_forbidden_zero;
                         int nal_nri;
                         int nal_type;
                         char* _payload;
                         bool _error;
                public:
                         /* Getters and Setter of Parameters */
                         int RTP_GetNalForbidden();
                         int RTP_GetNri();
                         int RTP_GetNalType();
                         void RTP_SetNalForbidden(bool forbidden);
                         void RTP_SetNri(unsigned short nri);
                         void RTP_SetNalType(unsigned short type);
                         bool RTP_NalParse();

                        /* Constructor */
                         RTP_Nal();
                         RTP_Nal(char *payload, int len);
                         ~RTP_Nal();
                         int _offset = 0;
           };
}
#endif
