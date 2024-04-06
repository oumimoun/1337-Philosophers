#include <sys/time.h>
#include <stdio.h>

int get_time_now()
{
    time_t time;
    return(gettimeofday(&time, NULL));
}

int main()
{
    printf("time == %d\n", get_time_now());

}