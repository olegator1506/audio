var _moduleName = 'hosts';
app.controller('mainCtrl',['$scope','$dialogs','dataFactory','$location','$uibModal','$rootScope',function($scope, $dialogs, dataFactory, $location,$uibModal,$rootScope){
    $scope.loadProgress = true;
    $scope.config = false;
    $scope,dropIsOpen = false;
    $scope.timerId = setInterval(function(){ // Таймер для проверки связи с сервером
        var lastT = dataFactory.lastRqTime;
        var d = new Date();
        var curTime = d.getTime();
        if((curTime - lastT) > 600000) // Если сервер незапрашивался более 10 минут, делаем роверочный запрос
            dataFactory.sendRq({action:'noop'}).then(  // Проверка соединения
                function(response){
                    dataFactory.loadProgress(false);
                }
            );

    },30000); //
    $scope.showDropDown = function($event){
        $event.preventDefault();
        $event.stopPropagation();
        $scope.dropIsOpen = ($event.type == 'mouseover');
    };

    /*
        @summary Выполнеие действия над строкой данных
        @param action структура описывающая действие (см. серверный метод TCommonObject::get_record_actions)

     */
    $scope.rowAction = function(action,rowNum,row) {
        if( (this[action.method] != undefined) && (typeof this[action.method] === 'function') ) {
            this[action.method](row,action);
        } else {
            $scope.execAction(action, row);
        }
    };



    $scope.runSubModule = function(action){
//        $rootScope.$broadcast('exec_submodule',action);
        var el = document.getElementById("main-module");
        var scope = angular.element(el).scope();
        if( (scope[action.method] != undefined) && (typeof scope[action.method] === 'function') ) {
            scope[action.method]();
        } else {
            $scope.execAction(action);
        }
    };

/*

    $scope.$on('exec_submodule',function(event,args){
        var ev = event;
    });
*/
    $scope.handleActionResponse = function(res) {
        if(res.op_result) {
            if( typeof res.data == 'string')
                $dialogs.notify(res.data);
            else if( Array.isArray(res.data))
                $dialogs.notify("",{},res.data);
             if(!((res.extra != undefined) && (res.extra.noReload == true)))
                $scope.$broadcast('data_changed');
        }else
            $dialogs.error(res.message);
    }


/**
 * @summary   Универсальный метод. Вызывает диалог подтверждения с сообщением message и заголовком header
 * В случае согласия отправляет запрос к текущему объекту в котором указывает action - действие, id - идентификатор записи, params - доп. параметры (если есть)
 * @param action - структура описывающая действие, содержит след-е поля:
 *       method
 *       confirmMsg
 *       confirmHdr
 *       noConfirm - если true, диалог подтверждения не вызывается
 *       params - доп.параметры передаваемые в запросе серверу
 *       timeout - время ожидания ответа сервера, сек
 *       noReload  если true, то данные не будут перезагружены после выполнения запроса, используется если запрос не модфицирует данные
    @param row - строка к которой относится запрос (объект) или номер строки в текущей выборке
  */
    $scope.execAction = function(action, row) {
        if(action.method == '_no_action_') return;
        if(row != undefined) {
            if(typeof row != 'object') { // строка задана номером
                var row = this.data.rows[row];// берем строку из выборки
            }
            if(row == undefined) {
                $dialogs.error("Запись № %row_num% не найдена",{row_num:rowNum});
                retrun;
            }
        }
        var keyField = $scope.config.module.key_field;
        var rq = {object:_moduleName, action:action.method};
        if(row)
            rq.id = row[keyField];
        var timeout = (action.timeout == undefined) ? 10 : action.timeout;
        if(action.params !== undefined) rq.params = action.params;
        var extra = {};
        if(action.noReload === true) extra.noReload = true;
        if( action.noConfirm === true ) { // Отправка запроса без пользовательского подтверждения
            $dialogs.serverRq(url,rq, $scope.handleActionResponse,  timeout, extra);
            return;
        }
        var confirmМsg = (action.confirmMsg == undefined) ? action.title : action.confirmMsg;
        var confirmHdr = (action.confirmHdr == undefined) ? 'Подтверждение' : action.confirmHdr;
        if(row) {
            var confirmParams = row;
            if (confirmParams.id == undefined)
                confirmParams.id = rq.id;
        } else confirmParams = {};
        $dialogs.confirm(confirmМsg ,function(){
            $dialogs.serverRq(url,rq,$scope.handleActionResponse, timeout,extra);
        },confirmParams,confirmHdr);
    };
    $scope.keyValue = function(rowNum){
        var keyField = $scope.config.module.key_field;
        return  this.data.rows[rowNum][keyField]; // this а не $scope потому что используется в НАСЛЕДУЕМЫХ контроллерах
    };
    $scope.configDialog = function(){
        var dlg = $uibModal.open({
            size:'lg',
            backdrop:'static',
            templateUrl: 'templates/dialogs/config.html',
            controller: 'configEditCtrl',
            windowClass: 'modalbackground',
            resolve: {
                config: function () {
                    return angular.copy($scope.config);
                }
            }
        }); // end modal.open
        dlg.result.then(function (res) {
            dataFactory.sendRq({action:'set_config',data:res}).then(
                function(response){
                    dataFactory.loadProgress(false);
                    $scope.config = response.data;
                    if(res) $scope.$broadcast('data_changed');
                },
                function(error){
                    dataFactory.loadProgress(false);
                    $scope.error = error.data.message;
                }
            );
        });

    };
    $scope.editRecord = function(record,action) {
        var id = false;
        if(record) {
            var keyField = $scope.config.module.key_field;
            id = record[keyField];
        };
        var data = {
          moduleName: $scope.moduleName,
          config:$scope.config,
          recordId:id,
          title:$scope.moduleTitle
        };
        var dlgParams = {
            size:'lg',
            backdrop:'static',
            templateUrl: 'templates/dialogs/edit-record.html',
            controller: 'formEditRecordCtrl',
            windowClass: 'modalbackground',
            resolve: {
                data: function () {
                    return angular.copy(data);
                }

            }
        };
        var dlg = $uibModal.open(dlgParams);
        dlg.result.then(function (res) {
            if(res) $scope.$broadcast('data_changed');
        });

    };
    $scope.subtable = function(row,action){
        var data = {
            parentId:row.id,
            moduleName:$scope.moduleName,
            subtableId:action.subtableId,
            title:action.title
        };
        var dlg = $uibModal.open({
            size:'lg',
            backdrop:'static',
            templateUrl: 'templates/dialogs/subtable.html',
            controller: 'dlgSubtableCtrl',
            windowClass: 'modalbackground',
            resolve: {
                action: function () {
                    return angular.copy(data);
                }
            }
        });

    };

    $scope.rowTitle = function(row){
        return "";
    };

    $scope.addRecord = function() {
        this.editRecord(false);
    };
    $scope.chpass = function(row,action) {
        var keyField = $scope.config.module.key_field;
        var data = {rowId:row[keyField],module: $scope.moduleName,title:this.rowTitle(row)};
        var dlgParams = {
            size:'md',
            backdrop:'static',
            templateUrl: 'templates/dialogs/change-pass.html',
            controller: 'dlgChangePassCtrl',
            windowClass: 'modalbackground',
            resolve: {
                data: function () {
                    return angular.copy(data);
                }
            }
        };
        var dlg = $uibModal.open(dlgParams);

    };
    $scope.showHistory = function(row, action){
        var data = {filter:action.params.filter,module: $scope.moduleName};
        var dlgParams = {
            size:'lg',
            backdrop:true,
            templateUrl: 'templates/dialogs/event-history.html',
            controller: 'dlgEventHistoryCtrl',
            windowClass: 'modalbackground',
            resolve: {
                data: function () {
                    return angular.copy(data);
                }
            }
        };
        var dlg = $uibModal.open(dlgParams);
    };
    $scope.$on("search_advanced",function(event,opts){
        $scope.advancedFilter = opts.filter;
    });


    $scope.moduleName = _moduleName;
    dataFactory.getConfig(_moduleName).then(
        function(response){
            dataFactory.loadProgress(false);
            $scope.config = response.data;
            $scope.$broadcast("configLoaded",$scope.config);
            $scope.error = false;
            $scope.moduleTitle = $scope.config.config.objects[_moduleName];
        },
        function(error){
            dataFactory.loadProgress(false);
            $scope.loadProgress = false;
            $scope.error = error.data.message;
            $scope.config = false;
        }
    );
}]);

app.controller('networksCtrl', function ($scope, dataFactory) {
    $scope.moduleErrors =[];
});

app.controller('dns_zonesCtrl', function ($scope, dataFactory) {
    $scope.moduleErrors =[];
});

app.controller('dns_recordsCtrl', function ($scope, dataFactory) {
    $scope.moduleErrors =[];
});

app.controller('usersCtrl', function ($scope, dataFactory) {
    $scope.moduleErrors =[];
});

app.controller('squidCtrl', function ($scope, dataFactory) {
    $scope.moduleErrors =[];
});

app.controller('switchCtrl', function ($scope, dataFactory, $dialogs, $uibModal) {
    $scope.moduleErrors =[];
    $scope.edit8021 = function(row) {
        var dlg = $uibModal.open({
            backdrop:'static',
            templateUrl: 'templates/dialogs/edit-8021.html',
            controller: 'dlgEdit8021Ctrl',
            windowClass: 'modalbackground',
            resolve: {
                switchId: function () {
                    return angular.copy(row.id);
                }
            }
        }); // end modal.open
        dlg.result.then(function (res) {
            if(res == 'yes') yesAction();
        });
    };
});







app.controller('swportsCtrl', function ($scope, dataFactory) {
    $scope.moduleErrors =[];
});
app.controller('swmacsCtrl', function ($scope, dataFactory) {
    $scope.moduleErrors =[];
});
app.controller('divisionsCtrl', function ($scope, dataFactory) {
    $scope.moduleErrors =[];
    $scope.checkDb = function() {
        dataFactory.sendRq({object:'divisions',action:'check_db'})
            .then(function(response){
                dataFactory.loadProgress(false);
                $scope.moduleErrors = response;
            });
    };
});
app.controller('user_issCtrl', function ($scope, dataFactory) {
    $scope.moduleErrors =[];
});

app.controller('arpCtrl', function ($scope, dataFactory) {
    $scope.moduleErrors =[];
});

app.controller('blacklistCtrl', function ($scope, dataFactory) {
    $scope.moduleErrors =[];
});

app.controller('fw_rulesCtrl', function ($scope, dataFactory) {
    $scope.moduleErrors =[];
});


