#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <ncurses.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

static char* MLG_AIRHORN = "mlg-airhorn.ogx";

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

    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    int result = 0;
    int flags = MIX_INIT_OGG;
    if (flags != (result = Mix_Init(flags))) {
        printf("Could not initialize mixer (result: %d).\n", result);
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }

    Mix_OpenAudio(44100, AUDIO_F32, 2, 4096);
    Mix_Music *music = Mix_LoadMUS(MLG_AIRHORN);

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
        if (ch != ERR) {
            Mix_PlayMusic(music, 1);   
        }
        /*
        if(ch == KEY_UP || ch == 'q') {
            quit();
        }
        */
        iterations++;

        erase();

        getmaxyx(stdscr, rows, cols);
        //snprintf(num, BUFSIZ, "%d, rows: %d, cols: %d", iterations, rows, cols);
        init_pair(1, (iterations) % 7, -1);
        attron(COLOR_PAIR(1));
        attron(A_REVERSE);
        char *string_one = "hello brandon";
        char *string_two = "please enjoy this program";
        char *string_three = "it enjoys you";
        mvprintw((rows / 2) - 2, (cols - strlen(string_one)) / 2, "%s", string_one);
        mvprintw((rows / 2), (cols - strlen(string_two)) / 2, "%s", string_two);
        mvprintw((rows / 2) + 2, (cols - strlen(string_three)) / 2, "%s", string_three);
        attroff(COLOR_PAIR(1));
        attroff(A_REVERSE);

        refresh();
        nanosleep(&sleep_time, NULL);
    }
    endwin();
    return 0;
}
