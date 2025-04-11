#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>


typedef struct s_message
{
	unsigned char b[4];
	pid_t pid;
	int bit_count;
	int target;
} t_message;

t_message msg;

int get_char_size(unsigned char c)
{
	if ((c & 0x80) == 0x00)
		return 8; 
	else if ((c & 0xE0) == 0xC0)
		return 16;
	else if ((c & 0xF0) == 0xE0)
		return 24;
	else if ((c & 0xF8) == 0xF0)
		return 32;
	return -1;
}

void manage_buffer(int i)
{
    int index;
    int bit_index;

    index = msg.bit_count / 8;
    msg.b[index] = msg.b[index] << 1;
    if(i)
        msg.b[index] = msg.b[index] | 1;
	msg.bit_count++;
	if (msg.bit_count == 8)
		msg.target = get_char_size(msg.b[0]);
	else if (msg.bit_count == msg.target)
    {
        write(1, msg.b, msg.target / 8);
        memset(msg.b, 0, 4);
        msg.bit_count = 0;
        msg.target= 0;
    }
}




int main(void)
{
	int arr[3][8] = {
		{1,1,1,0,0,0,1,0},     // 0xE2
		{1,0,0,1,1,1,0,0},     // 0x9C
		{1,0,0,0,0,1,0,1}      // 0x85
	};

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			manage_buffer(arr[i][j]);
			usleep(100); // optional
		}
	}
}
// #include <stdio.h>
// #include <stdlib.h>
// #include <signal.h>

// int count = 0;

// void sigint_handler(int signum)
// {
//     // The compiler is allowed to run:
//     //
//     //   signal(signum, SIG_DFL)
//     //
//     // when the handler is first called. So we reset the handler here:
//     signal(SIGINT, sigint_handler);

//     (void)signum;   // Get rid of unused variable warning

//     count++;                       // Undefined behavior
//     printf("Count: %d\n", count);  // Undefined behavior
// .
//     if (count == 2) {
//         printf("Exiting!\n");      // Undefined behavior
//         exit(0);
//     }
// }

// int main(void)
// {
//     signal(SIGINT, sigint_handler);

//     printf("Try hitting ^C...\n");

//     for(;;);  // Wait here forever
// }

