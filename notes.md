1) see results and if not correct change the mean computation to take a task and calculate the mean computation for that task
- need to change unify the get cost method
- need to unify the (maybe) unify the id method
- need to see if the up_rank values are correct (DONE)
2) create makefile
3) transfer fucntions to the right class (for example if a function in broker uses Task task as an argument that can be implemented in the task class Trasfer_time(Task task)->task.transfer_time())
4) check that the assign method accounts for communication costs
    if it doesnt create the mechanism for it
5) future- add argv, argc support so that input can be read from a file - input: number_of_vms,number_of_tasks,node_adgecency(in the form of lines like in the heft main) 
