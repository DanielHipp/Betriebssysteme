#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int
main (int argc, char *const argv[])
{

	int status;
	char *execArray[argc];
	int i = 0;
	while (i < argc)
	{

		execArray[i] = argv[i + 1];

		i++;
	}

	execArray[argc] = (char *) NULL;

	if (argv[1] == NULL)
	{
		perror ("Add a command!");
		return -1;
	}

	pid_t pid = fork ();

	if (pid == (-1))
	{
		perror ("fork failed");
		return -1;
	}
	else if (pid == 0)
	{
		/*Child */
		int err = 0;
		err = execvp (argv[1], execArray);
		if (err != 0)
		{
			perror ("execvp failed");
			return -1;
		}

	}
	else
	{
		/*Parent */
		if (wait (&status) != pid)
		{
			perror ("wait failed");
			return -1;
		}
		printf ("Your Command: ");
		i = 0;
		while (i < argc)
		{
			printf ("%s ", argv[i]);
			i++;
		}
		printf ("\nChild - PID: %d\n", status);
	}
	return 0;
}
