schedule:

vms <- currently in the pool (probably means number of possible vms available, like 10 or 100 symbolically)

create_estimates()  // computes the runtiumes of task t on all available types of vms
    vector<double> estimates;    
    for task in tasks
        estimates.push_back(get_type_cost())



get_type_cost() // should be brooker helper function which has the data available and does
                // not depend on the vm implementation 
                // probably will have to either take some arguments (such as the ON_DEMAND
                // OR SPOT for either only on demand instances or only spot instances) 
                // or that takes the types as a variable 

cp()?   // look at both the papers and how they describe the cp/uprank of wordflows 
        // which basically is the same thing

lto()?

