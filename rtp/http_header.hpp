#ifndef HTTP_HEADER_HPP
#define HTTP_HEADER_HPP

#include <iostream>
#include <stdint.h>
#include <sstream>
#include <deque>
#include <algorithm>
#include <boost/lexical_cast.hpp>
#include <sys/stat.h>
#include <unistd.h>

namespace http {
using namespace std;

class HTTP_helper
{
    typedef std::deque<uint8_t> data_type;
    typedef data_type::iterator data_iterator;
public:

    template<typename It>
    void consume(It first, It last)
    {
         std::copy(first,last,std::back_inserter(m_data));
    }

    template<typename It>
    size_t product(It packet)
    {
        size_t packet_size = search_packet();
        if(packet_size>0)
        {
            data_iterator packet_end(m_data.begin());
            std::advance(packet_end, packet_size);
            std::copy(m_data.begin(),packet_end, packet);
            m_data.erase(m_data.begin(), packet_end);
        }
        return packet_size;
    }

    template<typename CharT>
    struct ignore_case_equal
    {
           bool operator()(CharT lhs, CharT rhs)
           {
                return tolower(lhs)==tolower(rhs);
           }
    };

private:

    size_t search_packet()
    {
        std::string sep("\r\n\r\n");
        std::string len("content-length: ");

        /// search the seperator between header and content
        data_iterator sep_begin =
            std::search(m_data.begin(), m_data.end(), sep.begin(), sep.end());

        /// seperator is found
        if (sep_begin!=m_data.end())
        {
            /// search content size's name
            data_iterator len_begin =
                std::search(m_data.begin(), sep_begin,
                    len.begin(), len.end(),
                    ignore_case_equal<uint8_t>());

            if ( len_begin == sep_begin )
            {
                /// content size header is not found, there is no body in packet
                return std::distance(m_data.begin(), sep_begin) + sep.size();
            }
            else   ///< content size header is found
            {
                /// search content size's value
                data_iterator val_begin = len_begin;
                std::advance(val_begin, len.size());
                data_iterator val_end = std::find(val_begin, sep_begin, '\r');

                /// read value
                std::string val_str(val_begin, val_end);
                size_t content_size = boost::lexical_cast<size_t>(val_str);

                data_iterator content_begin = sep_begin;
                std::advance(content_begin, sep.size());

                /// test the size of content
                if ( content_size <= (size_t)std::distance(content_begin, m_data.end()))
                {
                    return std::distance(m_data.begin(),content_begin)
                            + content_size;
                }
            }
        }
        return 0;
    }
 private:
    data_type m_data;
   
};

}

#endif 
