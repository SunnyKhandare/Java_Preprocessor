#include<fcntl.h>
#include<unistd.h>
#include"JP_headerfile.h"

struct node * macro_array[58];

void Data_processor(char * file_name)
{
 
 for(int i=0;i<58;i++)
  macro_array[i]=NULL;

 char input_buffer[4096]={'\0'};
 int input_file_fd=open(file_name,O_RDONLY);
 char buffer[9]="#define ";
 int indicator_bit=1;

 char * byte_mover=NULL;
 char * first_byte_reminder=NULL;
 char * func_macro=NULL;

 int count=4096;
 int j=0;
 int function_macro_bit= 0;

 struct node * temp_ptr=NULL;

 while(1)
 {

  if(count>=4096)
  {
	   count=0;
	   if(!read(input_file_fd,input_buffer,4095))
	   goto finish;
	  
	   byte_mover= input_buffer;   
  }

	  for(int i=0;i<8;i++,byte_mover+=1,count++)
	  {
		   if(buffer[i]!=* byte_mover)
		   {
		   indicator_bit=0;
			break;
		   }
	  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 if(indicator_bit)
 {
  if(count>=4096)
  {
	   if(!read(input_file_fd,input_buffer,4095))
	   goto finish;
	  
	   byte_mover= input_buffer;   
  }


 if(count>=4096)
  {
   if(!read(input_file_fd,input_buffer,4095))
   goto finish;
  
   byte_mover= input_buffer;   
  }

  while(*byte_mover ==32)
 {
	  byte_mover+=1;
	  count++;

	  if(count>=4096)
	 {
		   if(!read(input_file_fd,input_buffer,4095))
		   goto finish;
		  
		   byte_mover= input_buffer;   
	  }
 } 

 

 if(*byte_mover == 92)
  while((*byte_mover == 32 || *byte_mover == 92) || *byte_mover==10)
  {
  byte_mover+=1;
  count++;

   if(count>=4096)
   {
	   if(!read(input_file_fd,input_buffer,4095))
		   goto finish;
		  
	   byte_mover= input_buffer;   
   }
  }

 
 temp_ptr=macro_array[(*byte_mover)-65];

 if(temp_ptr==NULL)
 {
	 temp_ptr= malloc(sizeof(struct node)); 
	 macro_array[(*byte_mover)-65]= temp_ptr;
 } 
 else
 { 
	 while(temp_ptr->next != NULL)
	  temp_ptr=temp_ptr->next;
	 
	  temp_ptr->next= malloc(sizeof(struct node));
 
	  temp_ptr=temp_ptr->next;
 }
  

 memset(temp_ptr,'\0',108);

 temp_ptr->next=NULL; 

 first_byte_reminder= byte_mover;

 while(*byte_mover !=32)
 {
	 byte_mover+=1;
	 count++;
	 
	 if(count>=4096)
	 {
		   if(!read(input_file_fd,input_buffer,4095))
		   goto finish;
		  
		   byte_mover= input_buffer;   
	  }
/////////////////////////////////////////////////////////
	 if(*byte_mover == 40)
	 {
		function_macro_bit =1;
		while(*byte_mover !=41)
		{
			if(count>=4096)
	 		{
		   		if(!read(input_file_fd,input_buffer,4095))
		   		goto finish;
		  
		   		byte_mover= input_buffer;   
	  		}

			byte_mover+=1;
			count++;
		}
	}
/////////////////////////////////////////////////////
 }

 
     j=0;

 if(byte_mover > first_byte_reminder)
 	while(first_byte_reminder < byte_mover)
	{
//////////////////////////////////////////////
		if(*first_byte_reminder !=32)
		{
			temp_ptr->macro[j]=*first_byte_reminder;
			j++;
		}
///////////////////////////////////////////////////
		first_byte_reminder+=1;
	} 
 else
 	{
	       j=0;

		while(*first_byte_reminder != '\0')
  		{
			temp_ptr->macro[j]=*first_byte_reminder;
	 		j++;
		}

		first_byte_reminder= input_buffer;

		while(first_byte_reminder < byte_mover)
		{
			temp_ptr->macro[j]=*first_byte_reminder;
			j++;
		} 	
	}

  while(*byte_mover ==32)
  {
	  byte_mover+=1;
	  count++;
	 
	  if(count>=4096)
	 {
		   if(!read(input_file_fd,input_buffer,4095))
		   goto finish;
		  
		   byte_mover= input_buffer;   
	  }
  }

 

 if(*byte_mover == 92)
  while((*byte_mover == 32 || *byte_mover == 92) || *byte_mover==10)
  {
	  byte_mover+=1;
	  count++;

	  if(count>=4096)
	  {
		   if(!read(input_file_fd,input_buffer,4095))
		   goto finish;
		  
		   byte_mover= input_buffer;   
	  }
  }

 first_byte_reminder= byte_mover;
 ////////////////////////////////////////////////////////
 if(function_macro_bit)
 {
	int backslash_bit = 0;

	while(1)
	{
		if(*byte_mover == 92)
			backslash_bit=1;

		if(*byte_mover==10)
			if(!backslash_bit)
				break;
			else
				backslash_bit=0;

		byte_mover+=1;
		count++;
	}
 }

 else
 {
	 while(*byte_mover !=32 && *byte_mover !=10)
	 {
		 byte_mover+=1;
		 count++;

		 if(count>=4096)
		 {
			   if(!read(input_file_fd,input_buffer,4095))
			   goto finish;
			  
			   byte_mover= input_buffer;   
		  }
	 }
 }
 
   j=0;
 if(byte_mover > first_byte_reminder)
 	while(first_byte_reminder < byte_mover)
	{
		
//////////////////////////////////////////////
		if(*first_byte_reminder !=32)
		{
			temp_ptr->macro_value[j]=*first_byte_reminder;
			j++;
		}
///////////////////////////////////////////////////
		first_byte_reminder+=1;
	} 
 else
 	{
		j=0;
		while(*first_byte_reminder != '\0')
		{
			temp_ptr->macro_value[j]=*first_byte_reminder;
			j++;
		}

		first_byte_reminder= input_buffer;

		while(first_byte_reminder < byte_mover)
		{
			temp_ptr->macro_value[j]=*first_byte_reminder;
			j++;
		}
 	}

 }
 
 while(*byte_mover!= '\n')
 {
	 byte_mover+=1;
	 count++;

	 if(count>=4096)
	 {
		   if(!read(input_file_fd,input_buffer,4095))
		   goto finish;
		  
		   byte_mover= input_buffer;   
	  }
 }

 byte_mover+=1;
 count++;
 indicator_bit=1;
 }

 finish:
       close(input_file_fd);

}

