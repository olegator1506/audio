angular.module('app').controller('dlgEdit8021Ctrl',['$scope', '$uibModalInstance','$dialogs', 'switchId','dataFactory',function($scope, $uibModalInstance, $dialogs, switchId, dataFactory){
    $scope.close = function(){
        $uibModalInstance.close();
    };
    $scope.setSelectAll = function(state) {
        $scope.swInfo.ports.forEach(function(port){
            if($scope.portCanChange(port))
                port.selected = state;
        });
    };
    $scope.setSelectRange = function(from,to,state) {
        $scope.swInfo.ports.forEach(function(port){
            if(port.num < from) return;
            if(port.num > to) return;
            if(!$scope.portCanChange(port)) return;
            port.selected = state;
        });
    };

    $scope.toggleFlagAll = function(){
        var val = $scope.formData.all;
        $scope.setSelectAll(val);
    };
    $scope.onSingleSelect = function(port){
        $scope.formData.all = false;
    };
    $scope.onFromToChange = function(){
        var from = parseInt($scope.formData.from);
        var to = parseInt($scope.formData.to);
        if(isNaN(from)) return;
        if(isNaN(to)) return;
        if(from > to) return;
        $scope.setSelectRange(from,to,true);
    };
    $scope.formValid = function(){
        if($scope.formData.state == '') return false;
        var res = false;
        $scope.swInfo.ports.forEach(function(port){if(port.selected) res = true});
        return res;
    };
    $scope.portCanChange = function(port){
        if(port.topology == 'uplink') return false;
        if(port.topology == 'trunk') return false;
        return true;
    };

    $scope.update = function(data){
        $scope.loadProgress = false;
        $scope.swInfo = data;
//        if(data.no_uplink)   $scope.error = "Не удалось определить UpLink порт устройства";
        var ports = $scope.swInfo.ports;
        $scope.swInfo.ports = [];
        $.each(ports, function(i,n) {
            n.num = i;
            $scope.swInfo.ports.push(n);
        });
        $scope.swInfo.synced = true;
        var goodPorts = [];
        $scope.deviceState8021 = data.state802_1x;
        $scope.swInfo.allPortsOff = true;
        $scope.swInfo.ports.forEach(function(port){
            if(port.state_802 == null) return;
            port.selected = false;
            port.num = parseInt(port.num);
            port.stateString = port.state_802 ? 'On':'Off';
            port.dbString = port.db_flag ? 'On':'Off';
            if(port.state_802) $scope.swInfo.allPortsOff = false;
            if(port.state_802 != port.db_flag) {
                $scope.swInfo.synced = false;
                port.rowClass = "bg-info";
            }
            if((port.topology == 'uplink') || (port.topology == 'downlink')) port.rowClass = "bg-primary";
            else if(port.topology == 'trunk') port.rowClass = "bg-warning";
            else if(port.state_802) port.rowClass =  'bg-success';
            else if(!port.state_802) port.rowClass =  'bg-danger';
            if(port.state_802 != port.db_flag) {
                port.rowClass = "bg-info";
            }
            goodPorts.push(port);
        });
        $scope.swInfo.ports = goodPorts;
    };
    $scope.sync = function(){
        dataFactory.sendRq({object:'switch', action:'sync802',switchId:switchId,force:false}).then(
            function(response){
                $dialogs.confirm("Выполнить на устройстве следующий скрипт?",
                    function(){
                        dataFactory.sendRq({object:'switch', action:'sync802',switchId:switchId,force:true}).then(
                            function(response){
                                $scope.init();
                                var message = "Скрипт выполнен " + (response.data.status) ? "успешно":"с ошибками"+" .Время выполнения "+response.data.duration;
                                $dialogs.notify(message,{},response.data.response);
                            },
                            function(error){
                                $scope.loadProgress = false;
                                if(error.data.message != undefined)
                                    $scope.error = error.data.message;
                                else
                                    $scope.error = error.statusText;
                            });
                    },
                    {},'Подтвердите действие',response.data
                );
            },function(error){
                $scope.loadProgress = false;
                if(error.data.message != undefined)
                    $scope.error = error.data.message;
                else
                    $scope.error = error.statusText;
            }
        );
    };
    $scope.setDeviceState = function(state){
        dataFactory.sendRq({object:'switch', action:'config_802',switchId:switchId,state:state,force:false}).then(
            function(response){
                $dialogs.confirm("Выполнить на устройстве следующий скрипт?",
                    function(){
                        dataFactory.sendRq({object:'switch', action:'config_802',switchId:switchId,state:state,force:true}).then(
                            function(response){
                                $scope.init();
                                var message = "Скрипт выполнен " + (response.data.status) ? "успешно":"с ошибками"+" .Время выполнения "+response.data.duration;
                                $dialogs.notify(message,{},response.data.response);
                            },
                            function(error){
                                $scope.loadProgress = false;
                                if(error.data.message != undefined)
                                    $scope.error = error.data.message;
                                else
                                    $scope.error = error.statusText;
                            });
                    },
                    {},'Подтвердите действие',response.data
                );
            },function(error){
                $scope.loadProgress = false;
                if(error.data.message != undefined)
                    $scope.error = error.data.message;
                else
                    $scope.error = error.statusText;
            }
        );
    };
    $scope.formSubmit = function(force){
        var ports = [];
        $scope.error = false;
        $scope.swInfo.ports.forEach(function(port){
            if(port.selected) ports.push(port.num);
        });
        $scope.loadProgress = true;
        dataFactory.sendRq({object:'switch', action:'config_802',switchId:switchId,ports:ports,state:$scope.formData.state,force:force}).then(
            function(response){
                $scope.update(response.data);
            },function(error){
                $scope.loadProgress = false;
                if(error.data.message != undefined)
                    $scope.error = error.data.message;
                else
                    $scope.error = error.statusText;
            }
        );
    };


    $scope.cancellScript = function(){
        $scope.script = false;
        $scope.scriptResult = false;
        $scope.init();
    };
    $scope.init = function(){
        $scope.loadProgress = true;
        $scope.swInfo = false;
        $scope.script = false;
        $scope.formData = {from:'',to:'',all:false,state:''};
        dataFactory.sendRq({object:'switch',action:'get',switchId:switchId}).then(
            function(response){
                dataFactory.loadProgress(false);
                $scope.update(response.data);
            },
            function(error){
                dataFactory.loadProgress(false);
                if(error.data.message != undefined)
                    $scope.error = error.data.message;
                else
                    $scope.error = error.statusText;
            }
        );
    };
    $scope.init();
}]);

