todo
---
- calculate eft and est
- correct results

doing
---
- to calculate est create comm_cost function to calculate the cost of the communication from one task to another

future
---
- add argv, argc support so that input can be read from a file - input: number_of_vms,number_of_tasks,node_adgecency(in the form of lines like in the heft main) 

maybe
---
- fix the flow in the todo fucntions
- unify the get cost method
- unify the id method
- transfer fucntions to the right class. for example if a function in broker uses Task task as an argument that can be implemented in the task class Trasfer_time(Task task)->task.transfer_time()

done
---
- fix up_rank
- create makefile
- see if the up_rank values are correct