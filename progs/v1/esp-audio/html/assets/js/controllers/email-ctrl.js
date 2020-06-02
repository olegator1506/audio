app.controller('emailCtrl', ['$scope','dataFactory','$uibModal','$dialogs',function ($scope, dataFactory,$uibModal,$dialogs) {
    $scope.moduleErrors = [];
    $scope.checkDb = function () {
        dataFactory.sendRq({object: 'email', action: 'check_db'})
            .then(function (response) {
                $scope.moduleErrors = response;
            });
    };
    $scope.rowTitle = function(row){
        return "ФИО: "+ row.fio + "Таб.№ " + row.tn + " E-mail: " + row.email;
    };

    $scope.confirmStdReg = function (data, yesAction) {
        var dlg = $uibModal.open({
            size: 'lg',
            backdrop: 'static',
            templateUrl: 'templates/dialogs/confirm-mail-std-reg.html',
            controller: 'mailConfirmStdRegCtrl',
            windowClass: 'modalbackground',
            resolve: {
                data: function () {
                    return angular.copy(data);
                }
            }
        }); // end modal.open
        dlg.result.then(function (res) {
            yesAction();
        });

    };
    $scope.applyRegister = function(row) {
        dataFactory.sendRq({action: 'register_std', data: row, apply: true})
            .then(
                function (response) {
                        $dialogs.notify("Регистрация учетной записи %email% выполнена успешно",row,response.data.actions);
                        $scope.$broadcast('data_changed');
                },
                function (error) {
                    $dialogs.error("Ошибка регистрации учетной записи", {}, error.data.message.errors);
                    $scope.$broadcast('data_changed');
                }
            );
    };
    $scope.registerStandart = function (row) {
        dataFactory.sendRq({action: 'register_std', data: row, apply: false})
            .then(
                function (response) {
                        $scope.confirmStdReg(response.data, function () {
                            $scope.applyRegister(row);
                        });
                },
                function (error) {
                    $dialogs.error(error.data.message);
                }
            );
    }
}]);



app.controller('mailConfirmStdRegCtrl', ['$scope','data','$uibModalInstance', function ($scope, data, $uibModalInstance) {
    $scope.warnings = data.warnings;
    $scope.actions = data.actions;
    $scope.no = function () {
        $uibModalInstance.dismiss('no');
    }; // end close

    $scope.yes = function () {
        $uibModalInstance.close('yes');
    }; // end yes

}]);