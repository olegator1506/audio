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
Date                   :=30/09/20
CodeLitePath           :="/home/artem/.codelite"
LinkerName             :=/usr/bin/arm-linux-gnueabi-gcc
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
RemoteTargetDir	       :=/home/artem/work/audio/opi/progs/dac-ctrl
TargetHost	       :=pi2
##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/arm-linux-gnueabi-gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as
ARCH 	 := -march=armv7-a -mcpu=cortex-a7 
#--sysroot=/lib/arm-linux-gnueabihf

##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/log_log.c$(ObjectSuffix) $(IntermediateDirectory)/pcf_pcf.c$(ObjectSuffix) $(IntermediateDirectory)/i2c_i2c.c$(ObjectSuffix) 



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
	$(LinkerName) $(ARCH) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions) -static
#	./pre-debug.sh
MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/artem/work/audio/opi/progs/dac-ctrl/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM "main.c"

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) "main.c"

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


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/
#	ssh $(TargetHost) killall gdbserver
# Remove old executable on target host
#	ssh $(TargetHost)  rm $(RemoteTargetDir)/$(ProjectName)


