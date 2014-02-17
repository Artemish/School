/**************************
 * maum.h -- the header file for maum.c 
 *
 *
 *
 *
 *************************/

#ifndef _MAIN_H_
#define _MAIN_H_

#define true 1
#define false 0
typedef int bool;

void custmake_usage(char*);
void parse_file(char*);
bool isBlank(char*);

typedef struct target {
	struct target_node* dependencies;
	struct cmd_node* commands;
	char* name;
} target;

typedef struct cmd_node {
	char* command;
	struct cmd_node* next;
} cmd_node;

typedef struct target_node {
	target* element;
	struct target_node* next;
} target_node;

target_node* makeNode(char* name);
void addTargetNode(target_node* listNode, char* name);
#endif
