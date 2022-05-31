//Using pipes to handle two strings
//One process takes strings as input and writes them to the pipe 
//Other process reads from the pipe and changes the string to uppercase.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{

	int fd1[2];
	int fd2[2];

	char fixed_str[] = "uppercase";
	pid_t p;

	if (pipe(fd1) == -1) {
		fprintf(stderr, "Pipe Failed");
		return 1;
	}
	if (pipe(fd2) == -1) {
		fprintf(stderr, "Pipe Failed");
		return 1;
	}


	p = fork();

	if (p < 0) {
		fprintf(stderr, "Fork Failed");
		return 1;
	}

	// Parent process
	else if (p > 0) {
		char str[100];

		close(fd1[0]); 


		write(fd1[1], fixed_str, strlen(fixed_str) + 1);
		close(fd1[1]);

		wait(NULL);

		close(fd2[1]);
		read(fd2[0], str, 100);
        printf("String before conversion is: %s\n", fixed_str);
		printf("Converted string is: %s\n", str);
		close(fd2[0]);
	}


	else {
		close(fd1[1]);

		char str[100];
		read(fd1[0], str, 100);

		int k = strlen(str);
		int i;
		for (i = 0; i < fixed_str[i]!='\0'; i++){
			if(fixed_str[i]>='a' && fixed_str[i]<='z')
                str[i]=fixed_str[i]-32;
        }

		str[k] = '\0';

		close(fd1[0]);
		close(fd2[0]);

		write(fd2[1], str, strlen(str) + 1);
		close(fd2[1]);

		exit(0);
	}
}
