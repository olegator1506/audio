app.controller('dlgCheckInetCtrl',['$scope', '$uibModalInstance','hostId','dataFactory',
    function($scope, $uibModalInstance,hostId, dataFactory){
        $scope.init = function() {
            $scope.hostId = hostId;
            $scope.detailRows = [];
            $scope.checkRules = [
                {title:'Проверка наличия записи для компьютера в конфигурации ASA firewall',module:'hosts',action:'check_inet',method:'asa'},
                {title:'Проверка наличия конфигурации AD',module:'hosts',action:'check_inet',method:'ad'},
                {title:'Проверка соответствия пользователя и IP адреса (ip-link)',module:'hosts',action:'check_inet',method:'ip_link'}

            ];
            for(var i =0;i<$scope.checkRules.length;i++) {
                $scope.checkRules[i].message = 'Выполняется проверка';
                $scope.checkRules[i].statusImage = 'assets/icons/ajax-loader.gif';
                dataFactory.sendRq({object:$scope.checkRules[i].module,action:$scope.checkRules[i].action,method:$scope.checkRules[i].method, id:$scope.hostId,ruleNum:i})
                    .then(function(response){
                        dataFactory.loadProgress(false);
                        var ruleNum = response.data.rule_num;
                        $scope.checkRules[ruleNum].status = response.data.statusText;
                        $scope.checkRules[ruleNum].statusImage = response.data.op_result ? 'assets/icons/ok.png' :'assets/icons/disable.png';
                        $scope.checkRules[ruleNum].details = response.data.details;
                        $scope.checkRules[ruleNum].message = response.data.message;
                    });
            }
        };
        $scope.selectRule = function(ruleNum) {
            $scope.selRule = $scope.checkRules[ruleNum];
        };
        $scope.close = function(){
            $uibModalInstance.close();
        };
        $scope.init();
    }]);
