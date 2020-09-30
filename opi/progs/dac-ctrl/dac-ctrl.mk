##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=dac-ctrl
ConfigurationName      :=Debug
WorkspacePath          :=/home/artem/work/audio
ProjectPath            :=/home/artem/work/audio/opi/progs/dac-ctrl
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Oleg Artemenko
Date                   :=09/30/20
CodeLitePath           :=/home/artem/.codelite
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
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/up_up_lib_i2c_i2c.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_lib_log_log.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_lib_pcf_pcf.c$(ObjectSuffix) $(IntermediateDirectory)/main.c$(ObjectSuffix) 



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
$(IntermediateDirectory)/up_up_lib_i2c_i2c.c$(ObjectSuffix): ../../lib/i2c/i2c.c $(IntermediateDirectory)/up_up_lib_i2c_i2c.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/artem/work/audio/opi/lib/i2c/i2c.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_lib_i2c_i2c.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_lib_i2c_i2c.c$(DependSuffix): ../../lib/i2c/i2c.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_lib_i2c_i2c.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_lib_i2c_i2c.c$(DependSuffix) -MM ../../lib/i2c/i2c.c

$(IntermediateDirectory)/up_up_lib_i2c_i2c.c$(PreprocessSuffix): ../../lib/i2c/i2c.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_lib_i2c_i2c.c$(PreprocessSuffix) ../../lib/i2c/i2c.c

$(IntermediateDirectory)/up_up_lib_log_log.c$(ObjectSuffix): ../../lib/log/log.c $(IntermediateDirectory)/up_up_lib_log_log.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/artem/work/audio/opi/lib/log/log.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_lib_log_log.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_lib_log_log.c$(DependSuffix): ../../lib/log/log.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_lib_log_log.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_lib_log_log.c$(DependSuffix) -MM ../../lib/log/log.c

$(IntermediateDirectory)/up_up_lib_log_log.c$(PreprocessSuffix): ../../lib/log/log.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_lib_log_log.c$(PreprocessSuffix) ../../lib/log/log.c

$(IntermediateDirectory)/up_up_lib_pcf_pcf.c$(ObjectSuffix): ../../lib/pcf/pcf.c $(IntermediateDirectory)/up_up_lib_pcf_pcf.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/artem/work/audio/opi/lib/pcf/pcf.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_lib_pcf_pcf.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_lib_pcf_pcf.c$(DependSuffix): ../../lib/pcf/pcf.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_lib_pcf_pcf.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_lib_pcf_pcf.c$(DependSuffix) -MM ../../lib/pcf/pcf.c

$(IntermediateDirectory)/up_up_lib_pcf_pcf.c$(PreprocessSuffix): ../../lib/pcf/pcf.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_lib_pcf_pcf.c$(PreprocessSuffix) ../../lib/pcf/pcf.c

$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/artem/work/audio/opi/progs/dac-ctrl/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM main.c

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) main.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


