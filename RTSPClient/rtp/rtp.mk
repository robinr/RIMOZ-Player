##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=rtp
ConfigurationName      :=Debug
WorkspacePath          :=/home/raghu/do/root/protocol/RTSPClient
ProjectPath            :=/home/raghu/do/root/protocol/RTSPClient/rtp
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Raghavendra
Date                   :=02/07/18
CodeLitePath           :=/home/raghu/.codelite
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="rtp.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/up_up_rtp_rtsp_receiver.cc$(ObjectSuffix) $(IntermediateDirectory)/up_up_rtp_rtp_nal.cc$(ObjectSuffix) $(IntermediateDirectory)/up_up_rtp_rtp_header.cc$(ObjectSuffix) $(IntermediateDirectory)/up_up_rtp_rtp_stats.cc$(ObjectSuffix) $(IntermediateDirectory)/up_up_rtp_rtp_stream.cc$(ObjectSuffix) $(IntermediateDirectory)/up_up_rtp_rtsp_client.cc$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/up_up_rtp_rtsp_receiver.cc$(ObjectSuffix): ../../rtp/rtsp_receiver.cc $(IntermediateDirectory)/up_up_rtp_rtsp_receiver.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/raghu/do/root/protocol/rtp/rtsp_receiver.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_rtp_rtsp_receiver.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_rtp_rtsp_receiver.cc$(DependSuffix): ../../rtp/rtsp_receiver.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_rtp_rtsp_receiver.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_rtp_rtsp_receiver.cc$(DependSuffix) -MM ../../rtp/rtsp_receiver.cc

$(IntermediateDirectory)/up_up_rtp_rtsp_receiver.cc$(PreprocessSuffix): ../../rtp/rtsp_receiver.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_rtp_rtsp_receiver.cc$(PreprocessSuffix) ../../rtp/rtsp_receiver.cc

$(IntermediateDirectory)/up_up_rtp_rtp_nal.cc$(ObjectSuffix): ../../rtp/rtp_nal.cc $(IntermediateDirectory)/up_up_rtp_rtp_nal.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/raghu/do/root/protocol/rtp/rtp_nal.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_rtp_rtp_nal.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_rtp_rtp_nal.cc$(DependSuffix): ../../rtp/rtp_nal.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_rtp_rtp_nal.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_rtp_rtp_nal.cc$(DependSuffix) -MM ../../rtp/rtp_nal.cc

$(IntermediateDirectory)/up_up_rtp_rtp_nal.cc$(PreprocessSuffix): ../../rtp/rtp_nal.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_rtp_rtp_nal.cc$(PreprocessSuffix) ../../rtp/rtp_nal.cc

$(IntermediateDirectory)/up_up_rtp_rtp_header.cc$(ObjectSuffix): ../../rtp/rtp_header.cc $(IntermediateDirectory)/up_up_rtp_rtp_header.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/raghu/do/root/protocol/rtp/rtp_header.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_rtp_rtp_header.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_rtp_rtp_header.cc$(DependSuffix): ../../rtp/rtp_header.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_rtp_rtp_header.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_rtp_rtp_header.cc$(DependSuffix) -MM ../../rtp/rtp_header.cc

$(IntermediateDirectory)/up_up_rtp_rtp_header.cc$(PreprocessSuffix): ../../rtp/rtp_header.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_rtp_rtp_header.cc$(PreprocessSuffix) ../../rtp/rtp_header.cc

$(IntermediateDirectory)/up_up_rtp_rtp_stats.cc$(ObjectSuffix): ../../rtp/rtp_stats.cc $(IntermediateDirectory)/up_up_rtp_rtp_stats.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/raghu/do/root/protocol/rtp/rtp_stats.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_rtp_rtp_stats.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_rtp_rtp_stats.cc$(DependSuffix): ../../rtp/rtp_stats.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_rtp_rtp_stats.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_rtp_rtp_stats.cc$(DependSuffix) -MM ../../rtp/rtp_stats.cc

$(IntermediateDirectory)/up_up_rtp_rtp_stats.cc$(PreprocessSuffix): ../../rtp/rtp_stats.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_rtp_rtp_stats.cc$(PreprocessSuffix) ../../rtp/rtp_stats.cc

$(IntermediateDirectory)/up_up_rtp_rtp_stream.cc$(ObjectSuffix): ../../rtp/rtp_stream.cc $(IntermediateDirectory)/up_up_rtp_rtp_stream.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/raghu/do/root/protocol/rtp/rtp_stream.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_rtp_rtp_stream.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_rtp_rtp_stream.cc$(DependSuffix): ../../rtp/rtp_stream.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_rtp_rtp_stream.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_rtp_rtp_stream.cc$(DependSuffix) -MM ../../rtp/rtp_stream.cc

$(IntermediateDirectory)/up_up_rtp_rtp_stream.cc$(PreprocessSuffix): ../../rtp/rtp_stream.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_rtp_rtp_stream.cc$(PreprocessSuffix) ../../rtp/rtp_stream.cc

$(IntermediateDirectory)/up_up_rtp_rtsp_client.cc$(ObjectSuffix): ../../rtp/rtsp_client.cc $(IntermediateDirectory)/up_up_rtp_rtsp_client.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/raghu/do/root/protocol/rtp/rtsp_client.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_rtp_rtsp_client.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_rtp_rtsp_client.cc$(DependSuffix): ../../rtp/rtsp_client.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_rtp_rtsp_client.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_rtp_rtsp_client.cc$(DependSuffix) -MM ../../rtp/rtsp_client.cc

$(IntermediateDirectory)/up_up_rtp_rtsp_client.cc$(PreprocessSuffix): ../../rtp/rtsp_client.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_rtp_rtsp_client.cc$(PreprocessSuffix) ../../rtp/rtsp_client.cc


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


