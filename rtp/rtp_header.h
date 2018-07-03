#ifndef RTP_HEADER_H
#define RTP_HEADER_H

#include <stdint.h>
#include <cstring>

namespace Rtp
{

class RTP_Header {
     /*
      * RFC3550.txt and RFC 7798.txt have similar structure with slightly different semantics
      * RTP: A Transport Protocol for Real-Time Applications
      *
      * The RTP header has the following format:
      0                   1                   2                   3
      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |V=2|P|X|  CC   |M|     PT      |       sequence number         |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                           timestamp                           |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |           synchronization source (SSRC) identifier            |
      +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
      |            contributing source (CSRC) identifiers             |
      |                             ....                              |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      * version (V)                 :   2 bits
      * padding (P)                 :   1 bit
      * extension (X)               :   1 bit
      * CSRC Count (CC)             :   4 bits
      * marker (M)                  :   1 bit
      * payload type (PT)           :   7 bits
      * sequence number             :  16 bits
      * timestamp                   :  32 bits
      * SSRC                        :  32 bits
      * CSRC list                   :  0 to 15 items, 32 bits each
      */
    private:
             unsigned int version:2;     /* protocol version */
             unsigned int padding:1;     /* padding flag */
             unsigned int extension:1;   /* header extension flag */
             unsigned int cc:4;          /* CSRC count  */
             unsigned int marker:1;      /* marker bit  */
             unsigned int pt:7;          /* payload type */
             uint16_t     seq:16;        /* sequence number */
             uint32_t     ts;            /* timestamp */
             uint32_t     ssrc;          /* synchronization source */
             uint32_t     csrc[1];       /* optional CSRC list */
     public:
             /* Constructors of RTP Header */
             RTP_Header();                            /* Default constructor */
             RTP_Header(char *value, size_t len);     /* constructor with external pointer value */
             RTP_Header(char *value, int len);        /* allocate to the pointer for utilization */
             RTP_Header(const RTP_Header& header);    /* constructor with header built by setters */
             /* Destructors of RTP Header */
             ~RTP_Header();
             /* Parse RTP Header from a stream */
             bool RTP_ParseFromStream(char *data, size_t len);   /* Read from socket and invoke the parse so getters can be called */
             /* Getters of RTP Header */
             int             RTP_GetVersion();
             bool            RTP_GetPadding();
             bool            RTP_GetExtension();
             int             RTP_GetCSRCCount();
             bool            RTP_GetMarker();
             int             RTP_GetPayloadType();
             unsigned short  RTP_GetSequenceNumber();
             unsigned long   RTP_GetTimeStamp();
             unsigned long   RTP_GetSyncSource();
             unsigned long   RTP_GetContribSrcCount(int index);
             char*           RTP_GetPayLoad();
             /* Setters of RTP Header */
             void            RTP_SetVersion(int version);
             void            RTP_SetPadding(bool pad);
             void            RTP_SetExtension(bool ext);
             void            RTP_SetCSRCCount(int count);
             void            RTP_SetMarker(bool marker);
             void            RTP_SetPayloadType(int type);
             void            RTP_SetSequenceNumber(unsigned short sequence);
             void            RTP_SetTimeStamp(unsigned long timestamp);
             void            RTP_SetSyncSource(unsigned long syncsource);
             void            RTP_ContribSrcCount(unsigned long contribsource);
             void            RTP_SetPayload(char* payload);
             bool            RTP_IsParsed();
     public:
             int    _len;
             char*  _data;
             bool   _error;
             int     offset;
             char*  _payload;
             static const int MIN_HEAD_LENGTH = 12;
             static const int PROTOCOL_VERSION = 2;
             static const int RTP_BUFFER_SIZE  = 8*1024;
};

}
#endif
