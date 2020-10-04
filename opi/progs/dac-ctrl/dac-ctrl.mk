##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=dac-ctrl
ConfigurationName      :=Debug
WorkspacePath          := "/home/artem/work/audio"
ProjectPath            := "/home/artem/work/audio/opi/progs/dac-ctrl"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Олег Артеменко
Date                   :=04/10/20
CodeLitePath           :="/home/artem/.codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
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
ObjectsFileList        :="dac-ctrl.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)../../lib $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)alsaplayer $(LibrarySwitch)asound $(LibrarySwitch)pthread 
ArLibs                 :=  "alsaplayer" "asound" "pthread" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall -Wno-write-strings $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/log_log.c$(ObjectSuffix) $(IntermediateDirectory)/pcf_pcf.c$(ObjectSuffix) $(IntermediateDirectory)/i2c_i2c.c$(ObjectSuffix) $(IntermediateDirectory)/adau17x_adau17x.c$(ObjectSuffix) $(IntermediateDirectory)/alsa_alsa.cpp$(ObjectSuffix) $(IntermediateDirectory)/classes_channel-base.cpp$(ObjectSuffix) $(IntermediateDirectory)/classes_channels.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/artem/work/audio/opi/progs/dac-ctrl/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/log_log.c$(ObjectSuffix): ../../lib/log/log.c $(IntermediateDirectory)/log_log.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/artem/work/audio/opi/lib/log/log.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/log_log.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/log_log.c$(DependSuffix): ../../lib/log/log.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/log_log.c$(ObjectSuffix) -MF$(IntermediateDirectory)/log_log.c$(DependSuffix) -MM "../../lib/log/log.c"

$(IntermediateDirectory)/log_log.c$(PreprocessSuffix): ../../lib/log/log.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/log_log.c$(PreprocessSuffix) "../../lib/log/log.c"

$(IntermediateDirectory)/pcf_pcf.c$(ObjectSuffix): ../../lib/pcf/pcf.c $(IntermediateDirectory)/pcf_pcf.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/artem/work/audio/opi/lib/pcf/pcf.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/pcf_pcf.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pcf_pcf.c$(DependSuffix): ../../lib/pcf/pcf.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pcf_pcf.c$(ObjectSuffix) -MF$(IntermediateDirectory)/pcf_pcf.c$(DependSuffix) -MM "../../lib/pcf/pcf.c"

$(IntermediateDirectory)/pcf_pcf.c$(PreprocessSuffix): ../../lib/pcf/pcf.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pcf_pcf.c$(PreprocessSuffix) "../../lib/pcf/pcf.c"

$(IntermediateDirectory)/i2c_i2c.c$(ObjectSuffix): ../../lib/i2c/i2c.c $(IntermediateDirectory)/i2c_i2c.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/artem/work/audio/opi/lib/i2c/i2c.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/i2c_i2c.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/i2c_i2c.c$(DependSuffix): ../../lib/i2c/i2c.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/i2c_i2c.c$(ObjectSuffix) -MF$(IntermediateDirectory)/i2c_i2c.c$(DependSuffix) -MM "../../lib/i2c/i2c.c"

$(IntermediateDirectory)/i2c_i2c.c$(PreprocessSuffix): ../../lib/i2c/i2c.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/i2c_i2c.c$(PreprocessSuffix) "../../lib/i2c/i2c.c"

$(IntermediateDirectory)/adau17x_adau17x.c$(ObjectSuffix): ../../lib/adau17x/adau17x.c $(IntermediateDirectory)/adau17x_adau17x.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/artem/work/audio/opi/lib/adau17x/adau17x.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/adau17x_adau17x.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/adau17x_adau17x.c$(DependSuffix): ../../lib/adau17x/adau17x.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/adau17x_adau17x.c$(ObjectSuffix) -MF$(IntermediateDirectory)/adau17x_adau17x.c$(DependSuffix) -MM "../../lib/adau17x/adau17x.c"

$(IntermediateDirectory)/adau17x_adau17x.c$(PreprocessSuffix): ../../lib/adau17x/adau17x.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/adau17x_adau17x.c$(PreprocessSuffix) "../../lib/adau17x/adau17x.c"

$(IntermediateDirectory)/alsa_alsa.cpp$(ObjectSuffix): ../../lib/alsa/alsa.cpp $(IntermediateDirectory)/alsa_alsa.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/artem/work/audio/opi/lib/alsa/alsa.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/alsa_alsa.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/alsa_alsa.cpp$(DependSuffix): ../../lib/alsa/alsa.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/alsa_alsa.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/alsa_alsa.cpp$(DependSuffix) -MM "../../lib/alsa/alsa.cpp"

$(IntermediateDirectory)/alsa_alsa.cpp$(PreprocessSuffix): ../../lib/alsa/alsa.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/alsa_alsa.cpp$(PreprocessSuffix) "../../lib/alsa/alsa.cpp"

$(IntermediateDirectory)/classes_channel-base.cpp$(ObjectSuffix): src/classes/channel-base.cpp $(IntermediateDirectory)/classes_channel-base.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/artem/work/audio/opi/progs/dac-ctrl/src/classes/channel-base.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/classes_channel-base.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/classes_channel-base.cpp$(DependSuffix): src/classes/channel-base.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/classes_channel-base.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/classes_channel-base.cpp$(DependSuffix) -MM "src/classes/channel-base.cpp"

$(IntermediateDirectory)/classes_channel-base.cpp$(PreprocessSuffix): src/classes/channel-base.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/classes_channel-base.cpp$(PreprocessSuffix) "src/classes/channel-base.cpp"

$(IntermediateDirectory)/classes_channels.cpp$(ObjectSuffix): src/classes/channels.cpp $(IntermediateDirectory)/classes_channels.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/artem/work/audio/opi/progs/dac-ctrl/src/classes/channels.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/classes_channels.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/classes_channels.cpp$(DependSuffix): src/classes/channels.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/classes_channels.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/classes_channels.cpp$(DependSuffix) -MM "src/classes/channels.cpp"

$(IntermediateDirectory)/classes_channels.cpp$(PreprocessSuffix): src/classes/channels.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/classes_channels.cpp$(PreprocessSuffix) "src/classes/channels.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


