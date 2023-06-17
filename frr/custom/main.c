#include <stdio.h>
#include "command.h"

DEFUN (my_cli,
       my_lci_cmd,
       "sang",
       "abc111111\n"
       "def\n")
{
    vty_out(vty, "hi\n");
	return CMD_SUCCESS;
}

int main()
{
    // printf("hello frr\n");
    cmd_init(1);
    install_element(ENABLE_NODE, &my_lci_cmd);
    return 1;
}