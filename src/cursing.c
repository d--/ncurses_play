#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <ncurses.h>
#include <string.h>

static struct timespec sleep_time = {
    .tv_sec = 0,
    .tv_nsec = 16666666,
};

static bool running = TRUE;

static void quit(void) {
    running = FALSE;
}

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    int rows, cols;
    initscr();

    raw();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    start_color();
    use_default_colors();

    char num[BUFSIZ];
    int iterations = 0;
    int ch;
    while (running) {
        ch = getch();
        if (ch == KEY_UP || ch == 'q') {
            quit();
        }
        iterations++;

        erase();

        getmaxyx(stdscr, rows, cols);
        snprintf(num, BUFSIZ, "%d, rows: %d, cols: %d", iterations, rows, cols);
        init_pair(1, (iterations) % 7, -1);
        attron(COLOR_PAIR(1));
        mvprintw(rows / 2, (cols - strlen(num)) / 2, "%s", num);
        attroff(COLOR_PAIR(1));

        refresh();
        nanosleep(&sleep_time, NULL);
    }
    endwin();
    return 0;
}
