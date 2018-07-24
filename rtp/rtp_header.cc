#include <iostream>
#include <stdint.h>
#include <string.h>
#include "rtp_header.h"

#define CHECK_BIT(var, pos) !!((var) & (1 << (pos)))

namespace Rtp
{
using namespace std;

          RTP_Header::RTP_Header()
          {
              version = 0;
              padding = 0;
              extension = 0;
              cc = 0;
              marker = 0;
              pt = 0;
              seq = 0;
              ts = 0;
              ssrc = 0;
              csrc[0] = 0;
              _len = 0;
              _data = NULL;
              _error = true;
              offset = 0;
          }
          RTP_Header::RTP_Header(char *value, size_t len)
          {
              std::cout << "Len" << len << std::endl;
              if (len <= 0)
              {
                  std::cout << "RTP Packet Not allocated by external source failed to process" << std::endl;
                  _len = 0;
                  _data = NULL;
                  _error = true;
                  offset = 0;
              }
              else
              {
                  if(len >= MIN_HEAD_LENGTH)
                  {
                       _len = len;
                       _data = value;
                       offset = 0;
                       if(RTP_ParseFromStream(_data,_len) == false)
                       {
                          _error = true;
                          std::cout << "RTP Packet badly formed error in parsing " << std::endl;
                          return;
                       }
                       else
                       {
                          _error = false;
                          std::cout << "RTP Packet Insitialized " << std::endl;
                       }
                 }
              }
           }

           RTP_Header::RTP_Header(char *value, int len)
           {
               if(len <= 0)
               {
                  std::cout << "RTP Header needs minimum of 12 bytes" << std::endl;
                  _len = 0;
                  _data = NULL;
                  _error = true;
                  offset = 0;
               }
               else
               {
                  _data = new char[len];
                  _len = len;
                  _error = false;
                  offset = 0;
                  memset((_data), 0, len);
               }
            }

           RTP_Header::RTP_Header(const RTP_Header &header)
           {
               _len = header._len;
               _data = new char[header._len];
               memset((_data), 0, _len);
               _data = header._data;
               _error = header._error;
               offset = header.offset;
           }

           RTP_Header::~RTP_Header()
           {
               _len = 0;
               _error = true;
               offset = 0;
               _data = NULL;
               //if(_data != NULL)
               //{
               //    delete _data;
               //}
           }

           int RTP_Header::RTP_GetVersion()
           {
               version = (unsigned int) ((_data[offset] >> 6) & 3);
               return version;
           }

           bool RTP_Header::RTP_GetPadding()
           {
                padding = CHECK_BIT(_data[offset], 5);
                return (bool) CHECK_BIT(_data[offset], 5);
           }

           bool RTP_Header::RTP_GetExtension()
           {
                extension = CHECK_BIT(_data[offset], 4);
                return (bool) CHECK_BIT(_data[offset], 4);
           }

           int RTP_Header::RTP_GetCSRCCount()
           {
               cc = (_data[offset] & 0x0F);
               return cc;
           }

           bool RTP_Header::RTP_GetMarker()
           {
               marker = CHECK_BIT(_data[offset], 8);
               return (bool) CHECK_BIT(_data[offset], 8);
           }

           int RTP_Header::RTP_GetPayloadType()
           {
               pt = _data[offset] & 0x7F;
               return pt;
           }

           unsigned short RTP_Header::RTP_GetSequenceNumber()
           {
               seq = _data[offset] * 256 + _data[offset + 1];
               return seq;
           }

           unsigned long RTP_Header::RTP_GetTimeStamp()
           {
               ts = (_data[offset    ] << 24) |
                    (_data[offset + 1] << 16) |
                    (_data[offset + 2] <<  8) |
                    (_data[offset + 3]);
               return ts;
           }

           unsigned long RTP_Header::RTP_GetSyncSource()
           {
               ssrc = (_data[offset    ] << 24) |
                      (_data[offset + 1] << 16) |
                      (_data[offset + 2] <<  8) |
                      (_data[offset + 3]);
               return ssrc;
           }

           unsigned long RTP_Header::RTP_GetContribSrcCount(int index)
           {
               int cnt = RTP_GetCSRCCount();
               if(index >= cnt)
               {
                    std::cout << "RTP Packet GetCSRCCount index error\n" << std::endl;
                    return 0;
               }
               if( _len > MIN_HEAD_LENGTH + cnt * 4)
               {
                    csrc[cnt] = (_data[offset    ] << 24) |
                                (_data[offset + 1] << 16) |
                                (_data[offset + 2] <<  8) |
                                (_data[offset + 3]);
                    return csrc[cnt];
               }
               return 0;
           }

           bool RTP_Header::RTP_ParseFromStream(char *data, size_t len)
           {
               int paysize = 0;
               int sz = len;
               int Pcnt = 0;
               if (sz > MIN_HEAD_LENGTH)
               {
                  offset = 0;
                  _len = sz;
                  _data = data;
                  _error = true;
                  do
                  {
                      switch (offset) {
                             case 0:
                                      {
                                      	int  Pver = RTP_GetVersion();  std::cout << "Version = " << Pver << std::endl;
                                      	bool Ppad = RTP_GetPadding();  std::cout << "Padding = " << Ppad << std::endl;
                                      	bool Pext = RTP_GetExtension(); std::cout << "Extension = " << Pext << std::endl;
                                      	     Pcnt = RTP_GetCSRCCount(); std::cout << "CSRC count = " << Pcnt << std::endl;
                                      	offset++;
                                      	break;
                                      }
                             case 1:
                                      {
                                        bool  Pmark = RTP_GetMarker(); std::cout << "Marker = " << Pmark << std::endl;
                                        int   Ptype = RTP_GetPayloadType(); std::cout << "PayloadType = " << Ptype << std::endl;
                                        offset++;
                                        break;
                                      }
                             case 2:
                                      {
                                        unsigned short PSeq = RTP_GetSequenceNumber(); std::cout << "Sequence Num = " << PSeq << std::endl;
                                        offset +=2;
                                        break;
                                      }
                             case 4:
                                      {
                                        unsigned long  Ptstamp = RTP_GetTimeStamp(); std::cout << "Time stamp = "  << Ptstamp << std::endl;
                                        offset +=4;
                                        break;
                                      }
                             case 8:
                                      {
                                        unsigned long PSyncSrc = RTP_GetSyncSource(); std::cout << "Sync Source = " << PSyncSrc << std::endl;
                                        offset +=4;
                                        break;
                                      }
                             case 12:
                                      {
                                       if(Pcnt >=97) {
                                                  unsigned long PConSrc = RTP_GetContribSrcCount(0); std::cout << "Contrib Source = " << PConSrc << std::endl;
                                                  offset +=4;
                                        }
                                        else
                                        {
                                                  offset++; /* come out of header parsing */
                                                  break;
                                        }
                                      }
                             default:
                                      continue;
                        }
                       std::cout << "offset = " << offset << std::endl;
                 }
                 while(offset <= MIN_HEAD_LENGTH);
                 if(RTP_GetSequenceNumber() == 0)
                 {
                       /* we just incremented the offset but CSRC even if the RTP_GetSequenceNumber was zero */
                       /* reverting back that increment */
                       offset--;
                 }
                 std::cout << "Step 1" << std::endl;
                 paysize = sz - offset;
                 std::cout << "resulting paysize " << paysize << std::endl;
                 _payload = new char[paysize];
                 memset(_payload, '\0', sizeof(_payload));
                 memcpy(_payload, _data + offset, paysize);
                 //std::cout << "Inside the payload is = " << _payload << std::endl;
                }
                else
                {
                 _error = false;
                }
             return _error;
          }

          char* RTP_Header::RTP_GetPayLoad()
          {
                return _payload;
          }

          void RTP_Header::RTP_SetVersion(int version)
          {
               unsigned char ver = '\0';
               ver = (char) (version & 0x3);
               ver = ver << 6;
               _data[offset] = ver;
          }

          void RTP_Header::RTP_SetPadding(bool pad)
          {
               unsigned char padding = '\0';
               padding = (pad == true) ? 0x1 : 0x0;
               padding = padding << 5;
               _data[offset] = _data[offset] | padding;
          }

          void RTP_Header::RTP_SetExtension(bool ext)
          {
               unsigned char extension = '\0';
               extension = ( ext == true) ? 0x1 : 0x0;
               extension = extension << 4;
               _data[offset] = _data[offset] | extension;
          }

          void RTP_Header::RTP_SetCSRCCount(int count)
          {
               unsigned char cc = '\0';
               cc = (char) count & 0x0F;
               _data[offset] = _data[offset] | cc;
          }

          void RTP_Header::RTP_SetMarker(bool marker)
          {
               unsigned char mark = '\0';
               mark = (marker == true) ? 0x1 : 0x0;
               mark = mark << 7;
               _data[offset] = _data[offset] | mark;
          }

          void RTP_Header::RTP_SetPayloadType(int type)
          {
               unsigned char payload = '\0';
               payload = (unsigned char) type & 0x7F;
               _data[offset] = _data[offset] | payload;
          }

          void RTP_Header::RTP_SetSequenceNumber(unsigned short sequence)
          {
               _data[offset] = 0x00FF & sequence;
               _data[offset + 1] = 0xFF00 & sequence;
          }

          void RTP_Header::RTP_SetTimeStamp(unsigned long timestamp)
          {
               int hour, min, sec, mill;

               hour = timestamp/(1000 * 60 * 60);
               timestamp = timestamp - ((1000 * 60 * 60) * hour);
               min  =  timestamp /(60 * 1000);
               timestamp = min - (60000 * min);
               sec  = timestamp / 1000;
               mill = timestamp - 1000 * sec;

               _data[offset] = hour;
               _data[offset + 1] = min;
               _data[offset + 2] = sec;
               _data[offset + 3] = mill;
          }

          void RTP_Header::RTP_SetSyncSource(unsigned long timestamp)
          {
               int hour, min, sec, mill;

               hour = timestamp/(1000 * 60 * 60);
               timestamp = timestamp - ((1000 * 60 * 60) * hour);
               min  =  timestamp /(60 * 1000);
               timestamp = min - (60000 * min);
               sec  = timestamp / 1000;
               mill = timestamp - 1000 * sec;

               _data[offset] = hour;
               _data[offset + 1] = min;
               _data[offset + 2] = sec;
               _data[offset + 3] = mill;
          }

          void RTP_Header::RTP_ContribSrcCount(unsigned long contribsource)
          {
               _data[offset] = 0xFF000000 & contribsource;
               _data[offset + 1] = 0x00FF0000 & contribsource;
               _data[offset + 2] = 0x0000FF00 & contribsource;
               _data[offset + 3] = 0x000000FF & contribsource;
          }

          void RTP_Header::RTP_SetPayload(char* payload)
          {
               _payload = payload;
          }

          bool RTP_Header::RTP_IsParsed()
          {
               return _error;
          }
}
