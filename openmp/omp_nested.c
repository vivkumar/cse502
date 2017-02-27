/*
 * Source: https://docs.oracle.com/cd/E24457_01/html/E21996/aewbe.html
 */
#include <omp.h>
#include <stdio.h>
void report_num_threads(int level)
{
    #pragma omp single
    {
        printf("Level %d: threads=%d\n",
                  level, omp_get_num_threads());
    }
 }
int main()
{
    #pragma omp parallel num_threads(2)
    {
        report_num_threads(1);
        #pragma omp parallel num_threads(2)
        {
            report_num_threads(2);
            #pragma omp parallel num_threads(2)
            {
                report_num_threads(3);
            }
        }
    }
    return(0);
}
