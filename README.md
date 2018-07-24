RIMOZ-Player is a SMIL3.0 player to play back media content
it has in built RTSP and HLS Stack for streaming media.

Dependency
==========
Boost 1_57_0
Asio  1.12.1


Folder structure
================
   RIMOZ-Player+
               /rtp        -> contains RTSP Player
               /RTSP       -> contains Code::Blocks Project workspace
               /RTSPClient -> contains Code::Lite Project workspace (active)

Pre-requiste to test
====================
   Install Wowza Streaming server 4.6 in any machine.
    
   Inside the vod application put few of the MPEG4 - H.264 (AVC) (Part 10) encoded video.
   
   a) Test the url in a VLC player like rtsp://192.168.1.9:1935/vod/one.mp4 and verify if plays
   b) The compiled client will produce rtsp_client as binary file
   c) Run the client using the following command.
   
      ./rtsp_client <IP address> <port> <path>

      eg:-
      ./rtsp_client 192.168.1.9  1935  vod/one.mp4

   d) H.264 would RTP Payload will be recorded in the file 'h264dump.sock'.


Next Steps
==========
    Development of HLS Stack



