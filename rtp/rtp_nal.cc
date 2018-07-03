#include <iostream>
#include <stdint.h>
#include <string.h>
#include "rtp_nal.h"

#define CHECK_BIT(var, pos) !!((var) & (1 << (pos)))

namespace Rtp
{
using namespace std;

          RTP_Nal::RTP_Nal()
          {
              nal_forbidden_zero = 0;
              nal_nri = 0;
              nal_type = 0;
              _payload = NULL;
              _error = false;
              _offset = 0;
          }

          RTP_Nal::RTP_Nal(char *payload, int len)
          {
                if(len == 0)
                {
                   std::cout << "RTP PayLoad Error" << std::endl;
                   _error = true;
                   _payload = NULL;
                   _offset = 0;
                   //return NULL;
                }
                else
                {
                   _payload = payload;
                   _offset = len;
                   _error = RTP_NalParse();
                }
          }

          RTP_Nal::~RTP_Nal()
          {
               _error = true;
                _payload = NULL;
                _offset = 0;
          }

          int RTP_Nal::RTP_GetNalForbidden()
          {
              nal_forbidden_zero = CHECK_BIT(_payload[0], 7);
              return nal_forbidden_zero;
          }

          int RTP_Nal::RTP_GetNri()
          {
              nal_nri = (_payload[0] & 0x60) >> 5;
              return nal_nri;
          }

          int RTP_Nal::RTP_GetNalType()
          {
              nal_type = (_payload[0] & 0x1F);
              return nal_type;
          }

          bool RTP_Nal::RTP_NalParse()
          {
              int forbidden = RTP_GetNalForbidden();
              int nri       = RTP_GetNri();
              int type      = RTP_GetNalType();
              if((type >= NAL_TYPE_SINGLE_NAL_MIN) || (type <= NAL_TYPE_FU_A))
              {
                  _error = true;
              }
              else
              {
                  _error = false;
              }
              return _error;
          }

          void RTP_Nal::RTP_SetNalForbidden(bool forbidden)
          {
              if(forbidden)
              {
                  nal_forbidden_zero = nal_forbidden_zero & 0x80;
                  _payload[0] = _payload[0] | nal_forbidden_zero;
              }
              else
              {
                  std::cout << "nothing to set " << std::endl;
                  _payload[0] = 0x00;
               }
          }

          void RTP_Nal::RTP_SetNri(unsigned short nri)
          {
               if((nri >= 0) && (nri <= 3))
                {
                     unsigned char nnri = (unsigned char) nri;
                     nnri = nnri << 5;
                     _payload[0] = _payload[0] | nnri;
                }
               else
                {
                    std::cout << "Error in nri value"  << std::endl;
                }
          }

          void RTP_Nal::RTP_SetNalType(unsigned short type)
          {
              if((type >= 0) && (type <= 0x1F))
              {
                  unsigned char ntype = (unsigned char) type;
                  _payload[0] = _payload[0] | ntype;
              }
              else
              {
                  std::cout << "Error in Type value" << std::endl;
              }
          }
}


