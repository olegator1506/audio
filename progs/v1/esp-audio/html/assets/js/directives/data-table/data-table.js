app.controller('dataTableCtrl',function($scope, $rootScope, dataFactory){
    $scope.refresh = function(params){
        $scope.loadProgress = true;
        var rqParams = {action:'get_data_records'};
        if(params != undefined)
            rqParams.params = params;
        dataFactory.sendRq(rqParams).then(
            function(response){ // Success
                dataFactory.loadProgress(false);
                $rootScope.$broadcast("data_table_updated");
                if(response.op_result == 'error') {
                    $scope.error = response.data.error;
                } else {
                    $scope.data = response.data;
                    $scope.error = false;
                    $scope.data = response.data;
                    $scope.page_num = response.data.page_num+1;
                    $scope.firstRecord = (response.data.page_num * response.data.page_rows) +1;
                    $scope.lastRecord =  (response.data.page_num+1) * response.data.page_rows;
                    if($scope.lastRecord > $scope.data.total)
                        $scope.lastRecord = $scope.data.total;
                }
            },
            function(error){
                dataFactory.loadProgress(false);
                $scope.loadProgress = false;
                $scope.error = error.data.message;
                $scope.data = false;
            }
        );

    };
    $scope.$on("search_opt_changed",function(event,opts){
        $scope.refresh(opts);
    });
    $scope.$on("search_advanced",function(event,opts){
        $scope.refresh({mode:'advanced',filter:opts});
    });

    $scope.sort = function(fieldName) {
        if(fieldName == $scope.data.sort_field)
            $scope.refresh({sort_order:($scope.data.sort_order == 'ASC')?'DESC':"ASC"});
        else
            $scope.refresh({sort_field:fieldName,sort_order:'ASC'});
    }
    $scope.onPageChange = function(page){
        $scope.refresh({page_num:page-1});
    }
    $scope.onRPPChange = function(rpp) {
        $scope.refresh({page_num:0,page_rows:rpp});
    }
    $scope.$on('data_changed',function(event){
        $scope.refresh();
    });
    $scope.fieldHtmlText = function(rowNum, fieldName){
      var text = $scope.data.rows[rowNum][fieldName];
      if(fieldName != 'user_info') return text;
      if(text === null) return null;
      text = text.replace('(  )','');
      return text;
    };
    $scope.moduleName = _moduleName;
    $scope.loadProgress = false;
    $scope.error = false;
    $scope.refresh();
});