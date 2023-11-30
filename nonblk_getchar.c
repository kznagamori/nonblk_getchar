#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

static unsigned int gs_keybuf_pos = 0;

static int kbhit(void)
{
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag = newt.c_lflag & (unsigned int)~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if (ch != EOF) {
		ungetc(ch, stdin);
		return 1;
	}
	return 0;
}

int nonblk_getkey(void) {
	if (kbhit()) {
		unsigned char c;
		c = (unsigned char)getchar();
		return (int)c;
	}
	return -1;
}

int nonblk_getInput(char* buf, size_t len) {
	int ret = -1;
	while (kbhit()) {
		if (gs_keybuf_pos < len - 1) {
			char c = getchar();
			if (c == '\r' || c == '\n') {
				ret = gs_keybuf_pos;
				buf[gs_keybuf_pos] = 0;
				gs_keybuf_pos = 0;
				return ret;
			} else {
				buf[gs_keybuf_pos++] = c;
			}
		} else {
			buf[gs_keybuf_pos] = 0;
			ret = gs_keybuf_pos;
			gs_keybuf_pos = 0;
			return ret;
		}
	}
	return ret;
}