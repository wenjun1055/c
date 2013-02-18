#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Running ps with some function\n");

    char *const ps_argv[] = {"ps", "ax", 0};
    char *const ps_envp[] = {"PATH=/bin:/usr/bin", "TERM=console", 0};
    
    /* function 1 */
    execl("/bin/ps", "ps", "ax", 0);

    /* function 2 */
    execlp("ps", "ps", "ax", 0);

    /* function3 */
    execle("/bin/ps", "ps", "ax", 0, ps_envp);

    /* function 4 */
    execv("/bin/ps", ps_argv);

    /* function 5 */
    execvp("ps", ps_argv);

    /* function 6 */
    execve("/bin/ps", ps_argv, ps_envp);

    printf("Done.\n");
    exit(0);
}
