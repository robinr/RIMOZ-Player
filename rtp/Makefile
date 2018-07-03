rtsp_client:	rtsp_client.o rtp_header.o rtp_nal.o rtp_stream.o rtp_stats.o rtsp_receiver.o rtsp_client.o
		g++ -o rtsp_client rtp_header.o rtp_nal.o rtp_stream.o rtp_stats.o rtsp_receiver.o rtsp_client.o -pthread -lboost_system -lboost_filesystem -lboost_thread -I/usr/local/include -I/usr/include -L/usr/local/lib -std=gnu++11

rtsp_client.o:		rtsp_client.cc http_header.hpp
		g++ -c rtsp_client.cc -I/usr/local/include -I/usr/include -L/usr/local/lib

rtp_header_test.o:	rtp_header.h rtp_header_test.cc
		g++ -c rtp_header_test.cc

rtp_header.o:		rtp_header.h rtp_header.cc
		g++ -c rtp_header.cc

rtp_nal.o:		rtp_nal.h rtp_nal.cc
		g++ -c rtp_nal.cc

rtp_stream.o:		rtp_stream.h rtp_stream.cc
		g++ -c rtp_stream.cc

rtp_stats.o:		rtp_stats.h rtp_stats.cc
		g++ -c rtp_stats.cc

rtsp_receiver.o:	rtsp_receiver.h rtsp_receiver.cc
		g++ -c rtsp_receiver.cc

clean:
		@rm *.o
		@rm rtsp_client 
		@echo "Clean done"
