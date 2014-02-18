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

void run_tests();
void custmake_usage(char*);
void parse_file(char*);
bool isBlank(char*);

typedef struct target_list {
    struct target_node* first;
} target_list;

typedef struct target {
	struct dep_node* dependencies;
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

typedef struct dep_node {
	struct target* element;
	struct dep_node* next;
} dep_node;

target_node* makeTargetNode(char* name);
target_node* addTargetNode(target_list* listNode, char* name);
#endif
