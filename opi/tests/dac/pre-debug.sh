#!/bin/sh
RemoteTargetDir=/home/artem/work/audio/opi/tests/dac
TargetHost=pi2
GDBServerPort=1025
ProjectName=dac
OutputFile=./Debug/${ProjectName}
### Kill gdbserver on target host
#ssh ${TargetHost} killall gdbserver
# Remove old executable on target host
ssh ${TargetHost}  rm ${RemoteTargetDir}/${ProjectName}
# Copy new binary to target host
scp ${OutputFile} ${TargetHost}:${RemoteTargetDir}/
#ssh ${TargetHost} "nohup gdbserver :1025 ${RemoteTargetDir}/${ProjectName} > /dev/null 2>&1 &"
ssh ${TargetHost} "gdbserver --once :1025 ${RemoteTargetDir}/${ProjectName}"
