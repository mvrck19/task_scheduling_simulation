todo
---
- correct results

doing
---
- make the assign method account for dependancy execution times
- make the assign method account for communication costs, with the transfer_time() method

future
---
- create makefile
- add argv, argc support so that input can be read from a file - input: number_of_vms,number_of_tasks,node_adgecency(in the form of lines like in the heft main) 

maybe
---
- unify the get cost method
- unify the id method
- transfer fucntions to the right class. for example if a function in broker uses Task task as an argument that can be implemented in the task class Trasfer_time(Task task)->task.transfer_time()

done
---
- see if the up_rank values are correct