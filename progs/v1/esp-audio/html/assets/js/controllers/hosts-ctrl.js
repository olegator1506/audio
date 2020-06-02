app.controller('hostsCtrl', ['$scope','dataFactory','$dialogs','$uibModal',function ($scope, dataFactory, $dialogs,$uibModal) {
    $scope.moduleErrors =[];
    $scope.network = {};
    /*
      $scope.runMethod = function( method, rowNum, params ) {
        switch (method) {
            case 'adminGrant':

        }
            $scope[method](rowNum,params);
        }
    */
    $scope.bump = function() {
        $dialogs.serverRq('responder.php',{object:'hosts',action:'bump'},function(result){
            if(result.data.status)
                $dialogs.notify("Операция обновления сетевой конфигурации выполнена успешно. Время выполнения: %duration% сек.",{duration:result.data.duration},result.data.response);
            else{
                $dialogs.error(result.data.message,{},result.data.response)
            }

        },300);
    };
    $scope.getHdwrConfig = function(rowNum) {
        var pcId  = $scope.keyValue(rowNum);
        dataFactory.sendRq({object:'hosts',action:'get_hdwr',id:pcId})
            .then(function(response){
                if(!response.status)
                    $dialogs.error(response.message);
                else {
                    var lines = [];
                    for(var i=0; i<response.data.data.length;i++)
                        lines.push(response.data.data[i].title +  ': ' + response.data.data[i].device);
                    $dialogs.notify('Конфигурация компьютера %id%',{id:pcId}, lines);
                }
            });
    };
    $scope.renameDefault = function(id) {
        dataFactory.sendRq({object:'hosts',action:'get_default_name',id:id})
            .then(function(response){
                if(!response.status)  {
                    $dialogs.error(response.message);
                } else {
                    var newName = response.name;
                    $dialogs.confirm("Вы действительно хотите переименовать узел в %new_name%",
                        function(){
                            dataFactory.sendRq({object:'hosts',action:'rename',id:id,name:newName})
                                .then(function(response){
                                    if(response.status) {
                                        location.reload();
                                    } else {
                                        $dialogs.error(response.message);
                                    }
                                });
                        },{new_name:newName},'Переименование узла');
                }
            });

    };
    $scope.checkInet = function(host) {
        var dlg = $uibModal.open({
            backdrop:'static',
            templateUrl: 'templates/dialogs/check-inet.html',
            controller: 'dlgCheckInetCtrl',
            windowClass: 'modalbackground',
            resolve: {
                hostId: function () {
                    return angular.copy(host.id);
                }
            }
        }); // end modal.open
        dlg.result.then(function (res) {
            if(res == 'yes') yesAction();
        });

    };
    $scope.edit8021x = function(host) {
        var hostId = host.id;
        var dlg = $uibModal.open({
            backdrop:'static',
            templateUrl: 'templates/dialogs/host-8021x.html',
            controller: 'dlgHost8021xCtrl',
            windowClass: 'modalbackground',
            resolve: {
                switchId: function () {
                    return angular.copy(host.id);
                }
            }
        }); // end modal.open
        dlg.result.then(function (res) {
            if(res == 'yes') yesAction();
        });

    };

    $scope.editRecord = function(host) {
        var dlgParams = {
            size:'lg',
            backdrop:'static',
            templateUrl: 'templates/dialogs/edit-host.html',
            controller: 'formEditHostCtrl',
            windowClass: 'modalbackground',
            resolve: {
                hostId: function () {
                    return host ? angular.copy(host.id) : false;
                }
            }
        };
        var dlg = $uibModal.open(dlgParams);
        dlg.result.then(function (res) {
            if(res) {
                $scope.$broadcast('data_changed');
            }
        });

    };
    $scope.addRecord = function(){
      $scope.editRecord(false);
    };
    dataFactory.sendRq({object:'hosts',action:'get_networks'})
        .then(function(response){
            $scope.networks = response.networks;
            $scope.clientNet = response.client_network;
        });

}]);
