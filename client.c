#include "minitalk.h"

static void	send_bit(pid_t server_pid, int bit)
{
	if (bit)
		kill(server_pid, SIGUSR2);
	else
		kill(server_pid, SIGUSR1);
	usleep(200);
}

static void	send_char(pid_t server_pid, char c)
{
	int	bit_position;

	bit_position = 7;
	while (bit_position >= 0)
	{
		send_bit(server_pid, (c >> bit_position) & 1);
		bit_position--;
	}
}

static void	send_string(pid_t server_pid, char *str)
{
	while (*str)
	{
		send_char(server_pid, *str);
		str++;
	}
	send_char(server_pid, '\0');
	usleep(1000);
}

static int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3)
	{
		write(1, "Usage: ./client <server_pid> <message>\n", 39);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		write(1, "Error: Invalid PID\n", 19);
		return (1);
	}
	send_string(server_pid, argv[2]);
	return (0);
}
