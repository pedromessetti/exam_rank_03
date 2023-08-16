#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

int	ft_strlen(const char *s) {
	int	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	return ++i;
}

char	*ft_strjoin(char *s1, char *s2) {
	int	i = 0;
	int	j = 0;

	if (!*s2)
		return 0;

	char	*new_s = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_s)
		return NULL;
	
	while (s1 && s1[j])
		new_s[i++] = s1[j++];
	
	j = 0;
	while (s2 && s2[j] != '\n' && s2[j])
		new_s[i++] = s2[j++];
	
	if (s2[j] == '\n')
		new_s[i++] = '\n';
	new_s[i] = '\0';
	
	free(s1);
	return new_s;
}

int	ft_clear(char *s) {
	int	i = 0;
	int	j = 0;
	int		is_new_line = 0;

	while (s[i]) {
		if (is_new_line)
			s[j++] = s[i];
		if (s[i] == '\n')
			is_new_line = 1;
		s[i++] = '\0';
	}
	
	return is_new_line;
}

char	*get_next_line(int fd) {
	static char	buf[BUFFER_SIZE + 1];

	if (fd == -1 || BUFFER_SIZE < 1)
		return NULL;
	
	char *line = ft_strjoin(0, buf);
	if (ft_clear(buf))
		return line;
	
	int	read_bytes = read(fd, buf, BUFFER_SIZE);
	if (read_bytes < 0)	{
		free(line);
		return NULL;
	}
	
	while (read_bytes) {
		line = ft_strjoin(line, buf);
		if (ft_clear(buf))
			break ;
		read_bytes = read(fd, buf, BUFFER_SIZE);
	}

	return line;
}
