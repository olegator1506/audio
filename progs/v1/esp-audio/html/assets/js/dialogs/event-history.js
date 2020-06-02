app.controller('dlgEventHistoryCtrl',['$scope', '$uibModalInstance','dataFactory','$dialogs','data',function($scope, $uibModalInstance,dataFactory, $dialogs, data){
    $scope.close = function(){
            $uibModalInstance.close();
    };
    $scope.loadData = function(){
        dataFactory.sendRq({action:'events',_filter:$scope.filter,_pageNum:$scope.pageNum-1,_pageSize:$scope.pageSize}).then(
            function(response){
                $scope.total = response.data.total;
                $scope.records = response.data.records;
                $scope.firstRecord = ($scope.pageNum -1) * $scope.pageSize + 1;
                $scope.lastRecord =  ($scope.pageNum) * $scope.pageSize;
                if($scope.lastRecord > $scope.total)  $scope.lastRecord = $scope.total;
            },
            function(error){
                $scope.error = error.data.message;
            }
        );
    };
    $scope.getDetails = function() {
        return "<p>This is test</p>";
    };
    $scope.myHtml = function(row){
        return row.data;
    };
    $scope.selectRow = function(num) {
      if(num == $scope.selectedRow) $scope.selectedRow = -1;
      else $scope.selectedRow = num;
    };
    $scope.rowIcon = function(num) {
      return ($scope.selectedRow == num) ? 'minus': 'plus';
    };
    $scope.onPageChange = function(pageNum) {
      $scope.pageNum = pageNum;
      $scope.loadData();
    };

    $scope.filter = data.filter;
    $scope.moduleName = data.moduleName;
    $scope.pageNum = 1;
    $scope.pageSize = 10;
    $scope.total = 0;
    $scope.records = false;
    $scope.orderField = 'time';
    $scope.orderDir = 'ASC';
    $scope.selectedRow = -1;
    $scope.fields = {
        ID:'ID',class:'Класс',name:'Имя',severity:'Важность',object:'Объект',description:'Описание',time:'Время'
    };
    $scope.fieldNames = Object.keys($scope.fields);
    dataFactory.loadProgress(false);
    $scope.loadData();
}]);