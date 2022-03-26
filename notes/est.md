est(task,vm) = max(available_time(vm),ready_time(task))
// later after the task is scheduled we set task.aft to est

---------------

temp_max=0
ready_time(task) =  for task : task.pred 
                        if(task.aft+comm_cost(task,task.pred)>temp_max)
                            temp_max = task.aft+comm_cost(task,task.pred)
                    return temp_max

--------------------

eft= est+get_cost(task,vm)

-----------------------

[comment]: <> (redo)
ready_time 




while there are unscheduled tasks do
for task in tasks:
    for vm in vms:
        calculate eft(task,vm)
        assign task to vm if eft(task,vm) is minimum









        for task in tasks:
            if(task.aft<=vm.eft):
                if(task.aft+get_cost(task,vm)<=vm.eft):
                    schedule(task,vm)
                    task.aft = task.aft+get_cost(task,vm)
                    vm.eft = task.aft+get_cost(task,vm)
                    break