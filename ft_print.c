void	print_it(t_token *tokens)
{
	t_token *curr = tokens;
	while (curr)
	{
		printf("\nvalue: (%s)\n[ ", curr->value);
		printf("removed doll: %d\n", curr->removed_doll);
		for (int i = 0; i < curr->vars_len; i++)
			printf("%d ", curr->vars[i].mode);
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
						printf("%d ", curr->args[i].vars[j].mode);
				printf("]\n");
				printf("removed doll: %d\n", curr->args[i].removed_doll);
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
		if (curr->files)
		{
			i = 0;
			printf("I/O Files :\n\n");
			while (curr->files[i].fd != -42)
			{
				switch(curr->files[i].type)
				{
					case 0:
						printf("Infiles: \n");
						printf("File name:[ %s ]\n", curr->files[i].file);
						printf("{Is Input: %d}\n\n", curr->files[i].last_in_out);
						break;
					case 1:
						printf("Heredoc: \n");
						printf("{Is Input: %d}\n\n", curr->files[i].last_in_out);
						break;
					case 2:
						printf("Outfile: \n");
						printf("{Is Output: %d}\n\n", curr->files[i].last_in_out);
						break;
					case 3:
						printf("Append: \n");
						printf("{Is Output: %d}\n\n", curr->files[i].last_in_out);
						break;
				}
				i++;
			}
		}
		printf("=======================\n");
		curr = curr->next;
	}
}