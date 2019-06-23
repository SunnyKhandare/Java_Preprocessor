#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#pragma pack(1)

struct node
{
 char macro[50];
 char macro_value[50];
 struct node * next;
};

void Data_processor(char * file_name);

void macro_replacer_and_comment_removal(int old_file_descriptor, int new_file_descriptor );


