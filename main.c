/***

Write a telbook program or set of programs that will provide the following functionality:

1.Allow creation of telbook file with user specified name and size. The size is in terms of number of telbook entries. Each entry will be 40 characters long: 20 characters for Name and 20 characters for Telephone number. (Hint: Use lseek to create file with hole)

2.On user providing index number program should show the entry corresponding to that index number. (Hint: Use lseek to jump to appropriate offset)

3.On user providing index number and entry (name + telephone number) the program should write the entry at the specified index in the telbook.

All system calls that are used in the above program must be checked for error return. All assignments should be accompanied by a makefile.


		*************************************************************************************************
					submitted by UMA SANKAR(Regd. No. ---> 16008)
		*************************************************************************************************

***/


#include <stdio.h>
#include <unistd.h>
#include "apue.h"
#include <fcntl.h>
#include <limits.h>


char name[21], telno[21], BUF_SIZE[42];
int size, ind, flag;


int printing_the_index(int fd)
{
	printf("Enter the index number (except '0') : ");
	scanf("%d", &ind);

	if(ind > size)
		printf("Sorry !!! Index is out of range\n");

	else
	{
		lseek(fd, sizeof(size) + (ind-1) * 43, SEEK_SET);
		if( (read(fd, &flag, 1)) != 1)
			return -1;

		if( flag!= 1)
		{
			printf("\nThere are no entries in the specified index\n");
			exit(1);
		}

		read(fd, BUF_SIZE, 42);
		strcpy(name, BUF_SIZE);
		strcpy(telno, BUF_SIZE+21);

		printf("\nRequested entry is : -------------->");
		printf("\nName : %s", name);
		printf("\nTelephone number : %s", telno);
	}

	return 0;
}


void writing_the_entries(int fd)
{
	printf("\nNow, enter the entry that has to be added : --------------->");

	printf("\nName : ");
	scanf("%s",name);

	printf("\nTelephone Number : ");
	scanf("%s",telno);

	printf("Enter the index(except '0') at which the entry to be added : ");
	scanf("%d",&ind);

	if(ind > size)
		printf("Sorry !!! Index is out of range\n");
	else
	{	lseek(fd, sizeof(size) + (ind-1) * 43, SEEK_SET);
		flag = 1;
		write(fd,&flag,1);
		strcpy(BUF_SIZE, name);
		strcpy(BUF_SIZE + 21, telno);
		write(fd, BUF_SIZE, 42);
	}
}



int main()
{

	char choice, filename[25];
	int filedes;	//file descriptor

	printf("\nNow, enter the name of the telbook file : ");
	scanf("%s", filename);

	if( (filedes = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR )) == -1)
	{
		printf("\nSORRY !!! File could not be opened.\n");
		return 0;
	}

	printf("\nNext, enter the size of the telbook : ");
	scanf("%d",&size);

	printf("\nTelbook file has been created successfully.");

	while(1)
	{
		printf("\nHAI !!! Please choose the following options : ");
		printf("\n1. Showing corresponding entry of the index no. entered by you (ENTER '1')");
		printf("\n2. Writing the entry at the specified index in the telbook (ENTER '2')");
		printf("\n3. Exit the program\n");

		getchar();
		scanf("%c", &choice);

		switch( choice )
		{
			case '1' : 	
					if(printing_the_index(filedes) == -1)
					{
						printf("\nSorry !!! Couldn't read the data.\n");
						exit(-1);
					}

					break;

			case '2' :
					writing_the_entries(filedes);
                              		break;

			case '3' :
					printf("\nExiting the program\n");
					exit(0);
					break;

			default  : 	printf("\nSORRY !!! There are only 3 options");
					break;
		}
	}

}
