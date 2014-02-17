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

typedef struct target_node* TargetList;
typedef struct target* Target;
typedef struct cmd_node* Command;


// ************************************

target* getTarget(target_node* listNode, char* name) {	
	while (listNode != NULL) {
		if (!strcmp(listNode->element->name, name)) return listNode->element;
		listNode = listNode->next;
	}

	return NULL;
}

bool inList(target_node* listNode, char* name) {
	while (listNode != NULL) {
 		if (!strcmp(listNode->element->name, name)) return true;
		listNode = listNode->next;
	}

	return false;
}

void addTargetNode(target_node* listNode, char* name) {
	while (listNode != NULL) {
 		if (!strcmp(listNode->element->name, name)) return;
		if (listNode->next == NULL) { 
			target_node* add = makeNode(name);
            listNode->next = add;
			add->next = NULL;
			return;
		}
		listNode = listNode->next;
	}
	
	return; // Should never occur
}

target_node* makeNode(char* name) {
    target_node* node = malloc(sizeof(target_node));
    target* t = malloc(sizeof(target));
    t->name = name;
    node->element = t;
    return node;
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
		if(!isspace(*string)){
			return false;
		}
		string++;
	}
	return true;
}

target_node* makeList() {
    target* root = malloc(sizeof(target));
    root->dependencies = NULL;
    root->commands = NULL;
    root->name = "Root node.";
    
    target_node* rootNode = makeNode(root->name);
    rootNode->next = NULL;
    
    return rootNode;
}

/****************************** 
 * this is the function that, when given a proper filename, will
 * parse the custMakefile and read in the targets and commands
 ***************/
void parse_file(char* filename) {
	char* line = malloc(160*sizeof(char));
	FILE* fp = file_open(filename);

    bool onTarget = true;
	const char delimiter[6] = ": \t\n";
	char* token;	
    
    TargetList tl = makeList();
    
    while((line = file_getline(line, fp)) != NULL) {
        if (!isBlank(line) && line != NULL){
			if (onTarget){
			    token = strtok(line,delimiter);
                printf("Adding target: %s\n", token);
                addTargetNode(tl, token);
			    while(token != NULL) {
			    	token = strtok(NULL,delimiter);
			    	if (token != NULL){
			    		printf("Adding dependency: %s\n", token);
			    	}
			    }
                
				onTarget = false;
			} else {
				if (strcmp(line,"end\n")==0) {//other line separators?
					onTarget = true;
				} else {
					printf("adding command line: %s",line);
				}
			}
		}
    }
    
    printf("\n\n ** BEGINNING TARGET LIST ** \n\n");
    
    while (tl != NULL) {
        printf("\"%s\"\n", tl->element->name);
        tl = tl->next;
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

	parse_file(filename);

	/* after parsing the file, you'll want to execute the target
		that was specified on the command line, along with its dependencies, etc. */
	
	return 0;
}
