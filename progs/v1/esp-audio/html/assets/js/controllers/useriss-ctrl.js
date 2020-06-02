app.controller('user_issCtrl', ['$scope','dataFactory','$dialogs','$uibModal',function ($scope, dataFactory, $dialogs, $uibModal) {
    $scope.moduleErrors =[];
    $scope.rowTitle = function(row){
        return "ФИО: "+ row.fio + "Таб.№ " + row.tn + " Логин: " + row.login;
    };

    $scope.registeeUser = function(data){
        var dlg = $uibModal.open({
            size: 'lg',
            backdrop: 'static',
            templateUrl: 'templates/dialogs/user-register.html',
            controller: 'userIssRegisterCtrl',
            windowClass: 'modalbackground',
            resolve: {
                data: function () {
                    return angular.copy(data);
                }
            }
        }); // end modal.open
        dlg.result.then(function (res) {
            $dialogs.notify("Учетная запись создана");
            $scope.$broadcast('data_changed');
        });


    }
}]);

app.controller('userIssRegisterCtrl',['$scope','$uibModalInstance','dataFactory','data',function($scope, $uibModalInstance, dataFactory,data){
    $scope.data = data;
    $scope.loginSelect = function(choice) {
        $scope.login = choice;
        $scope.login2 = choice;
        $scope.loginSelected = true;
    };
    $scope.submitForm = function(){
      $scope.errors = [];
      var pass1 = $scope.pass1.trim(); var pass2 = $scope.pass2.trim();
      if((pass1.length == 0) || (pass2.length == 0)) $scope.errors.push("Не указан пароль");
      if(pass1 != pass2)   $scope.errors.push("Паароли не совпадают");
      if($scope.errors.length >0) return;
      dataFactory.sendRq({object:'user_iss',action:'register',id:data.tn,login:$scope.login2,password:pass1})
            .then(function(response){
                dataFactory.loadProgress(false);
                $uibModalInstance.close(true);
            },function(error){
                dataFactory.loadProgress(false);
                $scope.errors = [error.data.message];
            });

    };
    $scope.cancell = function() {
        $uibModalInstance.dismiss(false);
    };
    dataFactory.sendRq({object:'user_iss',action:'login_variants',id:data.tn})
        .then(function(response){
            dataFactory.loadProgress(false);
            $scope.loginVariants = response.data;
            $scope.loginSelect($scope.loginVariants[0]);
        });
    $scope.dropDownStatus = false;
    $scope.pass1 ="";$scope.pass2 ="";
}]);
