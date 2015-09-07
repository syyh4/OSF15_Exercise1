#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "command.h"

#define MAX_CMD_COUNT 50
#define MAX_CMD_LEN 25


/*
 * PURPOSE: allocate and zero-initialize arrays.The largest number of arrays is 50
 *          for each array, allocate array with largest length equals to 25
 * INPUTS:
 *  pointer of the name of input strings
 *  pointer of the pointer of memory arrays
 * RETURN:
 *  true if there is no problems during process
 *  false for other cases
 **/
bool parse_user_input (const char* input, Commands_t** cmd) {


	char *string = strdup(input);
	
	*cmd = calloc (1,sizeof(Commands_t));
	(*cmd)->cmds = calloc(MAX_CMD_COUNT,sizeof(char*));

	unsigned int i = 0;
	char *token;
	token = strtok(string, " \n");
	for (; token != NULL && i < MAX_CMD_COUNT; ++i) {
		(*cmd)->cmds[i] = calloc(MAX_CMD_LEN,sizeof(char));
		if (!(*cmd)->cmds[i]) {
			perror("Allocation Error\n");
			return false;
		}	
		strncpy((*cmd)->cmds[i],token, strlen(token) + 1);
		(*cmd)->num_cmds++;
		token = strtok(NULL, " \n");
	}
	free(string);
	return true;
}

/*
 * PURPOSE: free all the memories
 * INPUTS:
 *  pointer of the pointer of memory locations
 * RETURN:
 *  nothing
 **/
void destroy_commands(Commands_t** cmd) {

	
	for (int i = 0; i < (*cmd)->num_cmds; ++i) {
		free((*cmd)->cmds[i]);
	}
	free((*cmd)->cmds);
	free((*cmd));
	*cmd = NULL;
}
