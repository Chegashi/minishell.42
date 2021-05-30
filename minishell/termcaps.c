#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <termcap.h>
#include <sys/ioctl.h>
//gcc -ltermcap termcaps.c
int ft_putchar(int c)
{
    return (write(1, &c, 1));
}
int main(int argc, char **argv, char **envp)
{
    char str[2000];
    int l;
    struct termios term;
    char *term_name = getenv("TERM");
    tcgetattr(0, &term); // get the parameters associated with the terminal
    term.c_lflag &= ~(ECHO); // If this bit is set, echoing of input characters back to the terminal is enabled.
    term.c_lflag &= ~(ICANON); // This bit, if set, enables canonical input processing mode
    //If optional_actions is TCSANOW, the change shall occur immediately.
    tcsetattr(0, TCSANOW, &term); // set the parameters associated with the terminal
    tgetent(0, term_name); // get the setting of our terminal working with
    int n;
    while (strcmp(str, "\4"))
    {
        tputs(save_cursor, 1, ft_putchar);
        do
        {
            iostl(0, FIONREAD, &n);
            l = read(0, str, 100);
            if(!strcmp(str, "\e[A"))
            {
                tputs(restore_cursor, 1, ft_putchar);
                tputs(tigetstr("ed"), 1, ft_putchar);
                write(1, "prev", 6);
            }
            // next line
            else if(!strcmp(str, "\e[B"))
            {
                tputs(restore_cursor, 1, ft_putchar);
                tputs(tigetstr("ed"), 1, ft_putchar);
                write(1, "next", 6);
            }
            else if (!strcmp(str, key_backspace) && !strcmp(str, "\177"))
            {
                //tputs(cursor_left, 1, ft_putchar);
                //tputs(tgetstr("dc", 0), 1, ft_putchar);
                //tputs(tigetstr("ed"), 1, ft_putchar);
                //tputs(delete_character, 1, ft_putchar);
                write(1, "del", 6);
            }
            else
                write(1, str, l);
        } while (strcmp(str, "\n") && strcmp(str, "\4"));
        write(1, "\n", l);
        return (0);
    }
}