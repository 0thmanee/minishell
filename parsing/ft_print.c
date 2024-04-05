#include "minishell.h"
void	print_it(t_token *tokens)
{
	t_token *curr = tokens;
	while (curr)
	{
		printf("\nvalue: (%s)\n[ ", curr->value);
		for (int i = 0; i < curr->vars_len; i++)
			printf("%d ", curr->vars[i]);
		printf("]\n");
		printf("type: ");
		if (curr->type == CMD)
			printf("CMD\n");
		else if (curr->type == INPUT)
			printf("INPUT\n");
		else if (curr->type == IN_FILE)
			printf("IN_FILE\n");
		else if (curr->type == OUTPUT)
			printf("OUTPUT\n");
		else if (curr->type == OUT_FILE)
			printf("OUT_FILE\n");
		else if (curr->type == HERE_DOC)
			printf("HERE_DOC\n");
		else if (curr->type == DELIMITER)
			printf("DELIMITER\n");
		else if (curr->type == APPEND)
			printf("APPEND\n");
		else if (curr->type == PIPE)
			printf("PIPE\n");
		if (curr->args)
		{
			int i = 0;
			printf("args [%d]:\n", curr->args_len);
			while (i < curr->args_len)
			{
				printf("{%s}\n[ ", curr->args[i].value);
				if (curr->args[i].vars_len)
					for (int j = 0; j < curr->args[i].vars_len; j++)
						printf("%d ", curr->args[i].vars[j]);
				printf("]\n");
				i++;
			}
		}
		printf("=======================\n");
		curr = curr->next;
	}
}

void print_it_2(t_cmd *cmds)
{
	t_cmd	*curr;
	int		i;
	curr = cmds;
	while (curr)
	{
		printf("\nvalue: (%s)\n-----------\n", curr->cmd);
		if (curr->args)
		{
			i = 0;
			printf("args :\n");
			while (curr->args[i])
			{
				printf("{ %s }\n", curr->args[i]);
				i++;
			}
		}
		printf("-----------\n");
		printf("Error: :: %d ::\n", curr->io_error);
		if (curr->infiles)
		{
			i = 0;
			printf("infiles :\n\n");
			while (curr->infiles[i].fd != -42)
			{
				printf("type: %s\n", curr->infiles[i].type == 0 ? "infile" : "here doc");
				curr->infiles[i].type == 0 ? printf("File name:[ %s ]\n", curr->infiles[i].file) : printf("");
				if (curr->infiles[i].type == 1)
					printf("Delimiter: [ %s ]\n", curr->infiles[i].delimiter);
				printf("\n");
				i++;
			}
		}
		if (curr->outfiles)
		{
			i = 0;
			printf("outfiles :\n\n");
			while (curr->outfiles[i].fd != -42)
			{
				printf("type: %s\n", curr->outfiles[i].type == 2 ? "outfile" : "Append");
				printf("File name:[ %s ]\n", curr->outfiles[i].file);
				printf("\n");
				i++;
			}
		}
		printf("=======================\n");
		curr = curr->next;
	}
}