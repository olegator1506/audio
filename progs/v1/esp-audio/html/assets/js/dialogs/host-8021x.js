angular.module('app').controller('dlgHost8021xCtrl',['$scope', '$uibModalInstance','switchId','dataFactory','$dialogs',function($scope, $uibModalInstance,switchId, dataFactory, $dialogs){
    $scope.close = function(){
        $uibModalInstance.close();
    };
    $scope.generatePassword = function(num){
      var chars = "23456789-asdfghjkzxcvbnmQWERTYUPASDFGHJKLZXCVBNM";
      var max = chars.length;
      var result = "";
      for(var i=0;i<10;i++) {
         var offs = Math.floor(Math.random() * max);
         result += chars.substr(offs,1);
      }
      $scope.hostInfo.attributes[num].value = result;
    };
    $scope.getAttrsByType = function(aType) {
        var result = [];
        $scope.hostInfo.attributes.forEach(function(attr){
            if(attr.attribute == aType) result.push(attr);
        });
        return (result.length == 0) ? false : result;

    }

    $scope.authTypeChange = function() {
        var status = $scope.hostInfo.authType;
        if(status == 'MD5') { // Добавляем атрибут Cleartext-Password
            if(!$scope.getAttrsByType('Cleartext-Password'))
                $scope.hostInfo.attributes.push({attribute:'Cleartext-Password',value:$scope.hostInfo.password,op:':='});
        } else { // Удаляем атрибут Cleartext-Password
            var result = [];
            $scope.hostInfo.attributes.forEach(function(attr){
                if(attr.attribute != 'Cleartext-Password') result.push(attr);
                else $scope.hostInfo.password = attr.value;
            });
            $scope.hostInfo.attributes = result;
        }
        switch(status) {
        }
    };
    $scope.mainStatusChange = function() {
        $scope.statusChanged = true;
        if ($scope.mainStatus)
            $dialogs.confirm('Вы действительно хотите отключить поддержку 802.1x для данного узла(будут удалены ВСЕ связанные с узлом атрибуты и сертификаты) ?', function () {
                dataFactory.sendRq({object:'hosts',action:'8021x',method:'disable',id:switchId}).then(
                    function(response){
                        $scope.loadProgress = false;
                        if(response.data.op_result == 'ok') $scope.close();
                        if(response.data.op_result == 'error') $scope.formErrors = response.data.errors;
                    },function(error){
                        $scope.loadProgress = false;
                        if(error.data.message != undefined)
                            $scope.error = error.data.message;
                        else
                            $scope.error = error.statusText;
                    }

                );
            });
        else {
            $scope.mainStatus = true;
            $scope.statusChanged = true;
        }
    };
    $scope.addAttribute = function(afterIndex){
      $scope.hostInfo.attributes.splice(afterIndex,0,{title:'',attribute:'',op:':=',value:''});
    };

    $scope.deleteAttribute = function(num) {
        $scope.hostInfo.attributes.splice(num,1);
    };
    $scope.submit = function() {
        var data = angular.copy($scope.hostInfo, data);
        $scope.formErrors = false;
        $scope.loadProgress = true;
        dataFactory.sendRq({object:'hosts',action:'8021x', method:$scope.editMode,id:switchId,data:data}).then(
            function(response){
                $scope.loadProgress = false;
                if(response.data.op_result == 'ok') $scope.close();
                if(response.data.op_result == 'error') $scope.formErrors = response.data.errors;
            },
            function(error){
                $scope.loadProgress = false;
                if(error.data.message != undefined)
                    $scope.error = error.data.message;
                else
                    $scope.error = error.statusText;
            }
        );

    };

    $scope.openCertAddForm = function(){
        $scope.certAddForm = {
            visible:true,
            data:{serverId:'',duration:3650,pass1:'',pass2:'',hostId:switchId,subject:{CN:$scope.hostInfo.userName}},
            errors:''
        };
    }
    $scope.certAddSubmit = function() {
        $scope.certAddForm.data.subject.CN = $scope.hostInfo.userName;
        $scope.loadProgress = true;
        $scope.certAddForm.errors = false;
        dataFactory.sendRq({object:'hosts',action:'8021x',method:'cert_create',data:$scope.certAddForm.data}).then(
            function(response) {
                $scope.loadProgress = false;
                if(response.data.op_result == 'error') {
                    $scope.certAddForm.errors = response.data.errors;
                    return;
                }
                $scope.certAddForm.errors = false;
                $scope.hostInfo = response.data.hostInfo;
                $scope.certAddForm = {
                    visible:false,
                    data:{},
                    error:''
                };
            },
            function(error) {
                $scope.loadProgress = false;
                if(error.data.message != undefined)
                    $scope.certAddForm.errors = [error.data.message];
                else
                    $scope.certAddForm.errors = [error.statusText];
            }
        );
    };
    $scope.loadCert = function(num){
        var certInfo = $scope.hostInfo.certificates[num];
        var name = "cert-" + $scope.hostInfo.hostName+"-"+certInfo.serial+".tar";
        var uri="responder.php?object=hosts&action=8021x&method=cert_load&host_id=" + switchId+"&serial=" + certInfo.serial + "&server=" + certInfo.server+"&return_name="+name;
        var link = document.createElement("a");
        link.download = name;
        link.href = uri;
        link.click();
    };

    $scope.revokeCert = function(num){
        var certInfo = $scope.hostInfo.certificates[num];
        $dialogs.confirm("Вы дествительно хотите удалить данный сертификат?",function(){
            dataFactory.sendRq({object:'hosts',action:'8021x',method:'cert_revoke',data:certInfo,hostId:switchId}).then(
                function(response){
                    $scope.loadProgress = false;
                    if(response.data.op_result == 'error') {
                        $scope.error = response.data.error;
                        return;
                    }
                    $dialogs.notify("Сертификат отозван");
                    $scope.hostInfo = response.data.hostInfo;
                },
                function(error){
                    $scope.loadProgress = false;
                    if(error.data.message != undefined)
                        $scope.error = error.data.message;
                    else
                        $scope.error = error.statusText;
                }
            );
        },{},"Отзыв сертификата");


    };
    $scope.init = function(){
        $scope.hostInfo = false;
        $scope.loadProgress = true;
        $scope.setPassMode = false;
        $scope.statusChanged = false;
        $scope.formErrors = false;
        $scope.certHideRevoked = true;
        $scope.certAddForm = {
            visible:false,
            data:{serverId:'',duration:3650,pass1:'',pass2:'',hostId:switchId,subject:{CN:''}},
            errors:''
        };
        $scope.tabs = {
            config:{title:"Основные настройки",visible:false},
            limits:{title:"Ограничения доступа",visible:false},
            certs:{title:"Сертификаты",visible:false}
        };
        dataFactory.sendRq({object:'hosts',action:'8021x',id:switchId,method:'get'}).then(
            function(response){
                $scope.loadProgress = false;
                $scope.hostInfo = response.data.hostInfo;
                $scope.config = response.data.config;
            },
            function(error){
                $scope.loadProgress = false;
                if(error.data.message != undefined)
                    $scope.error = error.data.message;
                else
                    $scope.error = error.statusText;
            }
        );
    };
    $scope.init();
}]);

