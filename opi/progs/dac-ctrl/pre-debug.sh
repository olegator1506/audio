#!/bin/sh
RemoteTargetDir=/home/artem/work/audio/opi/progs/dac-ctrl
TargetHost=pi2
GDBServerPort=1025
ProjectName=dac-ctrl
OutputFile=./Debug/${ProjectName}
### Kill gdbserver on target host
#ssh ${TargetHost} killall gdbserver
# Remove old executable on target host
#ssh ${TargetHost}  rm ${RemoteTargetDir}/${ProjectName}
# Copy new binary to target host
#scp ${OutputFile} ${TargetHost}:${RemoteTargetDir}/
#ssh ${TargetHost} "nohup gdbserver :1025 ${RemoteTargetDir}/${ProjectName} > /dev/null 2>&1 &"
#ssh ${TargetHost} "gdbserver --once :1025 ${RemoteTargetDir}/${ProjectName}"
scp main.cpp src/classes/* src/commands.h src/http-server.cpp ${TargetHost}:${RemoteTargetDir}
ssh ${TargetHost} "cd ${RemoteTargetDir}&&make -f dac-ctrl.mk"
ssh ${TargetHost} "gdbserver --once :1025 ${RemoteTargetDir}/Debug/${ProjectName}"

