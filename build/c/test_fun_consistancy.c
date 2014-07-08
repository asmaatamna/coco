#include <stdlib.h>
#include <stdio.h>

#include "numbbo.h"
#include "../../src/bbob2009_fopt.c"

void my_optimizer(numbbo_problem_t *problem) {
    static const int budget = 102;/* 100000;*/
    numbbo_random_state_t *rng = numbbo_new_random(0xdeadbeef);
    double *x = (double *)malloc(problem->number_of_parameters * sizeof(double));
    double y;
    for (int i = 1; i < budget; ++i) {
        bbob2009_unif(x, problem->number_of_parameters, i);
        for (int j = 0; j < problem->number_of_parameters; ++j) {
            /*const double range = problem->upper_bounds[j] - problem->lower_bounds[j];
             x[j] = problem->lower_bounds[j] + numbbo_uniform_random(rng) * range;*/
            x[j] = 20. * x[j] - 10.;
        }
        /*
         FILE *fd;
         fd = open(filename);
         if ( i % 100==0 ){
         printf("%d: [ %f,", i, x[0]);
         printf(" %f ]\n",x[1]);
         }*/
        numbbo_evaluate_function(problem, x, &y);
    }
    numbbo_free_random(rng);
    free(x);
    printf("%s\n",problem->problem_name);
    printf("%s\n",problem->problem_id);
}

int main(int argc, char **argv) {
    numbbo_benchmark("toy_suit", "toy_observer", "random_search", my_optimizer);
}
/*
 params.funcId = ifun;
 params.DIM = dim[idx_dim];
 params.instanceId = instance;
 printf("%d-D f%d, trial: %d\n", dim[idx_dim], ifun, instance);
 fgeneric_initialize(params);
 for (i = 1; i <= 1001; i++)
 {
 unif(indiv, dim[idx_dim], i);
 for (j = 0; j < dim[idx_dim]; j++)
 indiv[j] = 20. * indiv[j] - 10.;
 fgeneric_evaluate(indiv);
 }
 fgeneric_finalize();
 printf("\tDone, elapsed time [h]: %.2f\n", (double)(clock()-t0)/CLOCKS_PER_SEC/60./60.);
 */

