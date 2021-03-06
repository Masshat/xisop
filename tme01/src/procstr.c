#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char **argv)
{
	srand(time(NULL));
	if(argc <= 1)
	{
		perror("./procstr [nbproc]");
		exit(EXIT_FAILURE);
	}

	int nb = atoi(argv[1]);

	pid_t* pids = malloc((nb + 1) * sizeof(pid_t));	

	if(!pids)
	{
		perror("cant allocate memory");
		exit(EXIT_FAILURE);
	}

	pids[0] = getpid();
	printf("initial process %d\n", pids[0]);

	int i,r,status;
	for(i = 1; i <= nb; i++)
	{
		pid_t t;

		if((t = fork()) == 0)
		{
			pids[i] = getpid();
			if(i == nb)
			{
				int j;
				
				r = (int)(rand()/(((double)RAND_MAX +1)/100));
				
				for(j = 0; j <= nb; j++)
					printf("%d: %d . %d\n", getpid(), j, pids[j]);
	
				printf("rand : %d\n",r);
				
				exit(r);
			}
		}
		else if ( t == -1)
		{
			perror("cannot create a processus");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			r = WEXITSTATUS(status);
			
			printf("%d: father %d, child %d\n", getpid(), getppid(), t);
			
			if(i == 1)
				printf("rand : %d\n",r);

			exit(r);
		}
		
	}

	return EXIT_SUCCESS;
}
