#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#define DX 3
#define MAXLINES 1000

char* strcpy(char* dst, const char* src)
{
    if (dst == NULL) {
        return NULL;
    }
 
    char *ptr = dst;
 
    while (*src != '\0')
    {
        *dst = *src;
        dst++;
        src++;
    }
 
    *dst = '\0';
    return ptr;
}

int main(int argc, char *argv[])
{
    WINDOW *win;
    const char *ff = "Hello";
    char *line = NULL;
    char *buf;
    char **string;
    int c, x = 0 , y = 0, max = 1024;
    size_t len;
    ssize_t nread;
    FILE *file;
    
    setlocale(LC_ALL, "");
    if (argc != 2)
    {
        fprintf(stderr, "Вызов: %s файл\n", argv[0]);
        exit(1); 
    }                                                 
                                                               
    file = fopen(argv[1], "r");                          
    if (file == NULL)
    {                                    
        perror(argv[1]);                                 
        exit(2);                                          
    }
    
    string = calloc(max, sizeof(char *));
    while ((nread = getline(&line, &len, file)) != -1)
    {
        buf = malloc(sizeof(char)*len);
        strcpy(buf, line);
        string[y] = buf;
        y++;
    }
    
    initscr();
    noecho();
    cbreak();
    printw("File: %s", argv[1]);
    refresh();

    win = newwin(LINES-2*DX, COLS-2*DX, DX, DX);
    keypad(win, TRUE);
    scrollok(win, TRUE);
    box(win, 0, 0);

    len = y;
    y = 0;
    do
    {
        werase(win);
        for (int i = 0; i < LINES-2*DX-2 && i+y < len; i++)
        {
            mvwprintw(win, i+1, 1,  "%d %.*s", i+1+y, COLS-2*DX-2, string[i+y]);
        }
        box(win, 0, 0);
        wrefresh(win);
        if ((c = wgetch(win)) == 27) break;
        else if (c == 32  && y < len-1)
        {
            y = y+1;
        }
    } while (TRUE);

    for (size_t i = 0; i < len; i++)
    {
        free(string[i]);
    }
    
    free(string);
    fclose(file);
    endwin();
    return 0;
}
