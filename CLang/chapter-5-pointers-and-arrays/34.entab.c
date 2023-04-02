#include <stdio.h>

#define MAXLINE 1000

int myGetline(char line[], int maxline);

main(int argc, char *argv[])
{
	int c, len;
	int i;
	char line[MAXLINE];
	int tabstop;
	int spaceCount;

	if (argc == 1)
		tabstop = 8;
	else if (argc == 2)
		tabstop = atoi(*++argv);
	else {
		printf("Usage entab (8)(tabstop)\n");
		return 1;
	}

	while ((len = myGetline(line, MAXLINE)) > 0) {
		spaceCount = 0;

		for (i = 0; i < len; ++i) {
			if (line[i] == ' ')
				spaceCount++;
			else
				spaceCount = 0;

			if (spaceCount == tabstop) {
			}
		}
		printf("%s", line);
	}
}

int myGetline(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
