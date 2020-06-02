angular.module('app').controller('dlgSubtableCtrl',['$scope', '$uibModalInstance','action','dataFactory',function($scope, $uibModalInstance, action, dataFactory){
    $scope.close = function(){
        $uibModalInstance.close();
    };
    $scope.update = function(){
        $scope.loadProgress = true;
        var rq = {
            object:action.moduleName,
            action:'subtable',
            id:action.parentId,
            rpp:$scope.rpp,
            page:$scope.page,
            subtable:action.subtableId,
            sortField:$scope.sortField,
            sortDir:$scope.sortDir
        };
        dataFactory.sendRq(rq).then(
            function(response){
                dataFactory.loadProgress(false);
                $scope.headers = response.data.headers;
                $scope.total = response.data.total;
                $scope.records = response.data.records;
                $scope.firstRecord = response.data.first;
                $scope.lastRecord = response.data.last;
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
    $scope.onPageChange = function(pageNum){
        $scope.page = pageNum;
        $scope.update();
    };
    $scope.sort = function(fieldName){
        if(fieldName == $scope.sortField){
            $scope.sortDir = ($scope.sortDir == 'ASC') ? 'DESC':'ASC';
        } else {
            $scope.sortField = fieldName;
            $scope.sortDir = 'ASC';
        }
        $scope.sortIcon =  ($scope.sortDir == 'ASC') ? 'up.png':'down.png';
        $scope.update();
    };
    $scope.init = function(){
        $scope.title = action.title;
        $scope.page = 1;
        $scope.rpp = 20;// Потом надо будет сделать чтобы запоминалось (если клиент попросит)
        $scope.sortField = false;
        $scope.sortDir = 'ASC';
        $scope.update();

    };
    $scope.init();
}]);

