#include "minitalk.h"

static int		g_received_byte = 0;
static int		g_bit_count = 0;
static pid_t	g_client_pid = 0;

static void	reset_bit_count(void)
{
	g_bit_count = 0;
	g_received_byte = 0;
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (g_client_pid == 0)
		g_client_pid = info->si_pid;
	g_received_byte <<= 1;
	if (sig == SIGUSR2)
		g_received_byte |= 1;
	g_bit_count++;
	if (g_bit_count == 8)
	{
		if (g_client_pid != 0)
			kill(g_client_pid, SIGUSR1);
		if (g_received_byte == 0)
		{
			write(1, "\n", 1);
			reset_bit_count();
			g_client_pid = 0;
			return ;
		}
		write(1, &g_received_byte, 1);
		reset_bit_count();
	}
}

static void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

static void	print_pid(void)
{
	char	buffer[16];
	int		i;
	pid_t	pid;

	i = 0;
	pid = getpid();
	if (pid == 0)
	{
		write(1, "0", 1);
		return ;
	}
	while (pid > 0)
	{
		buffer[i++] = (pid % 10) + '0';
		pid /= 10;
	}
	while (i > 0)
		write(1, &buffer[--i], 1);
}

int	main(void)
{
	write(1, "Server PID: ", 12);
	print_pid();
	write(1, "\n", 1);
	setup_signal_handlers();
	while (1)
		pause();
	return (0);
}
