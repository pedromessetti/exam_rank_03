#include <stdarg.h>
#include <unistd.h>
#include <limits.h>

#define HEX "0123456789abcdef"

static void	ft_putchar(char c, unsigned int *size) {
	*size += 1;
	write(1, &c, 1);
}

static void	ft_putstr(char *s, unsigned int *size) {
	int	i = -1;

	if (!s) {
		ft_putstr("(null)", size);
		return ;
	}
	
	while (s[++i])
		ft_putchar(s[i], size);
}

static void	ft_putnbr(int n, unsigned int *size) {
	if (n == -2147483648) {
		ft_putchar('-', size);
		ft_putchar('2', size);
		n = 147483648;
	}
	if (n < 0) {
		ft_putchar('-', size);
		n = -n;
	}
	if (n >= 10) {
		ft_putnbr((n / 10), size);
		ft_putnbr((n % 10), size);
	}
	else
		ft_putchar((n + '0'), size);
}

static void	ft_putnbr_base(unsigned int n, char *base, unsigned int *size) {
	long int	li = n;
	int			baselen = -1;
	
	while (base[++baselen]);
	
	if (li / baselen == 0)
		ft_putchar(base[li % baselen], size);
	else {
		ft_putnbr_base(li / baselen, base, size);
		ft_putchar(base[li % baselen], size);
	}
}

static void	ft_checkflag(const char c, va_list args, unsigned int *size) {
	if (c == 's')
		ft_putstr(va_arg(args, char *), size);
	else if (c == 'd')
		ft_putnbr(va_arg(args, int), size);
	else if (c == 'x')
		ft_putnbr_base(va_arg(args, unsigned int), HEX, size);
}

int	ft_printf(const char *s, ...) {
	va_list args;

	int i = -1;
	unsigned int size = 0;
	va_start(args, s);
	
	while (s[++i]) {
		if (s[i] == '%')
			ft_checkflag(s[++i], args, &size);
		else
			ft_putchar(s[i], &size);
	}
	
	va_end(args);
	return size;
}
