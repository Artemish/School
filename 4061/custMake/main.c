/*******************************
 * main.c
 *
 * Source code for main
 *
 ******************************/

#include "util.h"
#include "main.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// ************************************

target* getTarget(target_node* listNode, char* name) {	
	while (listNode != NULL) {
		if (!strcmp(listNode->element->name, name)) return listNode->element;
		listNode = listNode->next;
	}

	return NULL;
}

target_node* addTargetNode(target_list* list, char* name) {
    if (list->first == NULL) {
        target_node* add = makeTargetNode(name);
        list->first = add;
        return add;
    }
    target_node* listNode = list->first;
    while (1) {
        if (!strcmp(listNode->element->name, name)) return listNode;
        if (listNode->next == NULL) {
            target_node* add = makeTargetNode(name);
            listNode->next = add;
            add->next = NULL;
	        return add;
        }
        listNode = listNode->next;
    }
    
    return NULL; // should never happen
}

target_node* makeTargetNode(char* name) {
    target_node* node = malloc(sizeof(target_node));
    target* t = malloc(sizeof(target));
    t->name = name;
    node->element = t;
    return node;
}

void addCommand(target* t, char* cmd) {
    cmd_node* current = t->commands;
    cmd_node* add = malloc(sizeof(cmd_node));
    add->command = cmd;
    
    if (!current) {
        t->commands = add;
        return;
    }
    
    while (current->next) current = current->next;
    
    current->next = add;
    return;
}

dep_node* makeDependencyNode(target_node* addition) {
    dep_node* result = malloc(sizeof(dep_node));
    result->element = addition->element;
    return result;
}

void addDependency(target_list* list, target_node* tn, char* name) {
    target_node* dependency = addTargetNode(list, name);
    
    dep_node* current = tn->element->dependencies;
    
    if (!current) {
        dep_node* add = makeDependencyNode(dependency);
        tn->element->dependencies = add;
        return;
    }
    
    while (current != NULL) {
        if (!strcmp(current->element->name, name)) return; 
        if (current->next == NULL) {
            dep_node* add = makeDependencyNode(dependency);
            current->next = add;
            return;
        }
    }
    
    return; // Should never happen
}

/*********
 * Simple usage instructions
 *********/
void custmake_usage(char* progname) {
	fprintf(stderr, "Usage: %s [options] [target]\n", progname);
	fprintf(stderr, "-f FILE\t\tRead FILE as a custMakefile.\n");
	fprintf(stderr, "-h\t\tPrint this message and exit.\n");
	fprintf(stderr, "-n\t\tDon't actually execute commands, just print them.\n");
	exit(0);
}

bool isBlank(char* string){
	while(*string != '\0'){
		if(!isspace(*string) && *string != '\n'){
			return false;
		}
		string++;
	}
	return true;
}

void printList(target_node* node) {
    printf("\n\n **** PRINTING LIST **** \n\n");    
    while (node != NULL) {
        printf("Target: %s\n", node->element->name);
        node = node->next;
    }
    printf("\n **** LIST OVER **** \n\n");
}

char* newString(char* source) {
    if (!source) return NULL;
    char* result = malloc(sizeof(char) * 160);
    strncpy(result, source, 160);
    return result;
}

void printTarget(target_node* tn) {
    printf("Target name: %s\n", tn->element->name);
    dep_node* currentDep = tn->element->dependencies;
    printf("Dependencies: \n");
    while (currentDep) {
        printf("    %s\n", currentDep->element->name);
        currentDep = currentDep->next;
    }
    printf("Commands: \n");
    cmd_node* currentCmd = tn->element->commands;
    while (currentCmd) {
        printf("    %s\n", currentCmd->command);
        currentCmd = currentCmd->next;
    }
    printf("\n");
    return;
}

/****************************** 
 * this is the function that, when given a proper filename, will
 * parse the custMakefile and read in the targets and commands
 ***************/

void run_tests() {
    printf("\n");
}

void parse_file(char* filename) {
	char* line = malloc(160*sizeof(char));
	FILE* fp = file_open(filename);
    
    bool onTarget = true;
	const char delimiter[6] = ": \t\n";
	char* token;
    char* targetName;
    target_list* tl = malloc(sizeof(target_list));
    target_node* parent;
    
    while((line = file_getline(line, fp)) != NULL) {
        if (!isBlank(line) && line != NULL) {
			if (onTarget) {
			    targetName = newString(strtok(line,delimiter));
                printf("Adding target : %s\n", targetName);
                parent = addTargetNode(tl, targetName);
                do {
			    	token = newString(strtok(NULL,delimiter));
			    	if (token != NULL) {
                        addDependency(tl, parent, token);
			    		printf("Adding depend : %s\n", token);
			    	}
			    } while (token != NULL);
                
				onTarget = false;
			} else {
				if (strcmp(line,"end\n")==0) {//other line separators?
					onTarget = true;
				} else {
                    addCommand(parent->element, newString(line));
					printf("adding command: %s",line);
				}
			}
		}
    }
    
    printf("\n\n ** BEGINNING TARGET LIST ** \n\n");
    target_node* current = tl->first;
    while (current != NULL) {
        printTarget(current);
        current = current->next;
    }
    
	fclose(fp);
	free(line);
}



int main(int argc, char* argv[]) {
	// Declarations for getopt
	extern int optind;
	extern char* optarg;
	int ch;
	char* format = "f:hn";
	
	// Variables you'll want to use
	char* filename = "custMakefile";
	// bool execute = true;

	// Use getopt code to take input appropriately (see section 3).
	while((ch = getopt(argc, argv, format)) != -1) {
		switch(ch) {
			case 'f':
				filename = strdup(optarg);
				break;
			case 'n':
				// execute = false;
				break;
			case 'h':
				custmake_usage(argv[0]);
				break;
		}
	}
	argc -= optind;
	argv += optind;

	/* at this point, what is left in argv is the target that was
		specified on the command line. If getopt is still really confusing,
		try printing out what's in argv right here, then just run
		custmake with various command-line arguments. */
    run_tests();
	parse_file(filename);

	/* after parsing the file, you'll want to execute the target
		that was specified on the command line, along with its dependencies, etc. */
	
	return 0;
}
