#include"JP_headerfile.h"

extern struct node * macro_array[58];

#define read_data(old_file_descriptor, old_data , new_file_descriptor, new_data) \
	{ \
		if(!read(old_file_descriptor,old_data, 4095))\
		{ \
			new_data[strlen(new_data)]=0; \
			write(new_file_descriptor, new_data , strlen(new_data)); \
			return; \
		} \
		\
		old_data_counter=0; \
	}

void macro_replacer_and_comment_removal(int old_file_descriptor, int new_file_descriptor )
{
 char new_data[4096]={'\0'};
 char old_data[4096]={'\0'};

 int old_data_counter=4096;
 int new_data_counter=4096;

 int multi_line_comment_bit=0;
 int single_line_comment_bit=0;
 int indicator_bit1=0;
 int indicator_bit2=0;
 
 int one_space_bit=0;
 int one_new_line_feed_bit=0;
 int macro_bit=0;
 int star_bit=0;

 struct node * temp=NULL;

 char temp_buffer[50];

 int cnt=0;
 
 int function_macro_bit=0;
 char function_macro_arg[50];
 char function_macro_arg_value[50];
 char old_macro_value_copy[50];
 char new_macro_value_copy[50];
 char temp_copy[50];
 char * tracer=NULL;
 char * tracer2=NULL;
 char * first_byte_reminder_of_FM_arg_substring=NULL;
 char * first_byte_reminder_of_FM_arg_replacement=NULL;
 char * tracer3=NULL;
 char * reminder=NULL;
 char * first_byte_reminder=NULL;
 

  if(old_data_counter>=4095)
 {
	if(!read(old_file_descriptor,old_data, 4095))
		return;
		
	old_data_counter=0;
}
	
new_data_counter=0;


/////////////////////////////  single line comment removal
	if(old_data[old_data_counter] ==47)
	 	indicator_bit1=1;

	if(old_data_counter>=4094)
		read_data(old_file_descriptor, old_data , new_file_descriptor, new_data);

	if((old_data[old_data_counter] == 47 && old_data[old_data_counter +1]==47) || (indicator_bit1 && old_data[old_data_counter] == 47 ) || single_line_comment_bit) 
	{
	 
	if(!single_line_comment_bit)
	{
		 if(old_data[old_data_counter +1]==47)
			old_data_counter+=2;
		 else
			old_data_counter+=1;
	}
	
	
	single_line_comment_removal :

	single_line_comment_bit=1;
	indicator_bit1=0;

	if(old_data_counter==4095)
		read_data(old_file_descriptor, old_data , new_file_descriptor, new_data);

	 while(old_data_counter<4095)
	{
		if(old_data[old_data_counter] == 10)
		{
			single_line_comment_bit=0;
		
			if(old_data_counter==4094)
				read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
			else
				old_data_counter+=1;

			break;
		}

		if(old_data_counter==4094)
			read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
		else
			old_data_counter+=1;
	}
	}
/*        */

/////////////////////////////// multi line comment removal

	if(old_data[old_data_counter] == 47)
		indicator_bit2=1;

	if(old_data_counter == 4094)
		read_data(old_file_descriptor, old_data , new_file_descriptor, new_data);

	if((old_data[old_data_counter] == 47 && old_data[old_data_counter +1]==42) || (indicator_bit2 && old_data[old_data_counter] == 42) || multi_line_comment_bit )
	{
	 if(!multi_line_comment_bit)
	 {
		if(old_data[old_data_counter +1]==42)
		old_data_counter+=2;
	 	else
		old_data_counter+=1;
	 }

	multi_line_comment_removal :

	 multi_line_comment_bit=1;
	 indicator_bit2=0;
	
	 if(old_data_counter==4095)
		read_data(old_file_descriptor, old_data , new_file_descriptor, new_data);
	
	while(old_data_counter < 4095)
	{
		if(old_data[old_data_counter] ==42)
		{
			star_bit=1;

			 if(old_data_counter==4094)
				read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
			else
				old_data_counter+=1;


			if(old_data[old_data_counter] == 47)
			{
				multi_line_comment_bit=0;
		
				if(old_data_counter==4094)
					read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
				else
					old_data_counter+=1;

				break;
			}
			else
				star_bit=0;

		}

		if(old_data_counter==4094)
			read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
		else
			old_data_counter+=1;

	}

	}

	if(indicator_bit1)
		indicator_bit1=0;

	if(indicator_bit2)
		indicator_bit2=0;
	
/////////////////////////////////

while(1)
{

 if(old_data[old_data_counter] == 10)
 {
 	 one_new_line_feed_bit=0;

	  if(new_data_counter == 4094)
	  {
		new_data_counter+=1;
		new_data[new_data_counter] = 0;
		write(new_file_descriptor, new_data, 4095);
		new_data_counter=0;
	  }

	while(old_data[old_data_counter] == 10)
	{
		 if(!one_new_line_feed_bit)
		 {
			  new_data[new_data_counter]=10; //-----------------------------
			  new_data_counter+=1;
			  one_new_line_feed_bit=1;	
	   	 }
		  if(old_data_counter>=4094)
			read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
		 else
		  	old_data_counter+=1;
	}
 }
 else if(old_data[old_data_counter] == 0)
 {
	write(new_file_descriptor, new_data , strlen(new_data));
	return ;
 }
 else if(old_data[old_data_counter] == 47)
 {
	if(old_data_counter == 4094)
		read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
	else
		old_data_counter+=1;
 	
	if(old_data[old_data_counter] == 47)
	{
		if(old_data_counter == 4094)
			read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
		else
			old_data_counter+=1;

		goto single_line_comment_removal;
	}
	else if(old_data[old_data_counter] == 42)
	{
		if(old_data_counter == 4094)
			read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
		else
			old_data_counter+=1;

		goto multi_line_comment_removal;
	}
	else
	{
		  if(new_data_counter == 4094)
		  {
			new_data_counter+=1;
			new_data[new_data_counter] = 0;
			write(new_file_descriptor, new_data, 4095);
			new_data_counter=0;
		  }

	  	 new_data[new_data_counter]=47;

	  	 new_data_counter+=1;
	  
	  	if(old_data_counter>=4094)
			read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
		else
	  		old_data_counter+=1;
	}
 }
 else if(old_data[old_data_counter] == 32)
 {
	  one_space_bit=0;

	  if(new_data_counter == 4094)
	  {
		new_data_counter+=1;
		new_data[new_data_counter] = 0;
		write(new_file_descriptor, new_data, 4095);
		new_data_counter=0;
	  }

	  while(old_data[old_data_counter] == 32)
	  {
		if(!one_space_bit)
		 {
			  new_data[new_data_counter]=32;
			  new_data_counter+=1;
			  one_space_bit=1;	
	   	 }
	  	if(old_data_counter>=4094)
			read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
		else
			old_data_counter+=1;
	  }

 }
 else if(old_data[old_data_counter] == 34)
 {

	if(new_data_counter == 4094)
 	{
		new_data_counter+=1;
		new_data[new_data_counter] = 0;
		write(new_file_descriptor, new_data, 4095);
		new_data_counter=0;
  	}

	new_data[new_data_counter] = old_data[old_data_counter];
	new_data_counter+=1;

	if(old_data_counter>=4094)
		read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
	else
		old_data_counter+=1;

	while(old_data[old_data_counter] != 34)
	{
 		 if(new_data_counter == 4094)
 		 {
			new_data_counter+=1;
			new_data[new_data_counter] = 0;
			write(new_file_descriptor, new_data, 4095);
			new_data_counter=0;
  		 }

		new_data[new_data_counter] = old_data[old_data_counter];
		new_data_counter+=1;

		if(old_data_counter>=4094)
			read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
		else
			old_data_counter+=1;
	}

	if(new_data_counter == 4094)
 	{
		new_data_counter+=1;
		new_data[new_data_counter] = 0;
		write(new_file_descriptor, new_data, 4095);
		new_data_counter=0;
  	}

	new_data[new_data_counter] = old_data[old_data_counter];
	new_data_counter+=1;

	if(old_data_counter>=4094)
		read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
	else
		old_data_counter+=1;
 }
 else if(old_data[old_data_counter] == 35)
 {
	macro_bit=0;

	while(!macro_bit || old_data[old_data_counter]!=10)
	{
		if(new_data_counter == 4094)
 		 {
			new_data_counter+=1;
			new_data[new_data_counter] = 0;
			write(new_file_descriptor, new_data, 4095);
			new_data_counter=0;
  		 }

	//	new_data[new_data_counter] = old_data[old_data_counter];
	//	new_data_counter+=1;

		if(old_data_counter>=4094)
			read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
		else
			old_data_counter+=1;

		if(old_data[old_data_counter]== 92)
			macro_bit=1;

		if(old_data[old_data_counter]==10)
		{
			if(macro_bit)
			macro_bit=0;
			else
			macro_bit=1;
		}
	}

	if(new_data_counter == 4094)
 	{
		new_data_counter+=1;
		new_data[new_data_counter] = 0;
		write(new_file_descriptor, new_data, 4095);
		new_data_counter=0;
  	}

//	new_data[new_data_counter] = old_data[old_data_counter];
//	new_data_counter+=1;

	if(old_data_counter>=4094)
		read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
	else
		old_data_counter+=1;
 }
 else if(old_data[old_data_counter] == 39)
 {
	if(new_data_counter == 4094)
 	{
		new_data_counter+=1;
		new_data[new_data_counter] = 0;
		write(new_file_descriptor, new_data, 4095);
		new_data_counter=0;
  	}

	new_data[new_data_counter] = old_data[old_data_counter];
	new_data_counter+=1;	

	if(old_data_counter>=4094)
		read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
	else
		old_data_counter+=1;

	while(old_data[old_data_counter] != 39)
	{
		if(new_data_counter == 4094)
 		 {
			new_data_counter+=1;
			new_data[new_data_counter] = 0;
			write(new_file_descriptor, new_data, 4095);
			new_data_counter=0;
  		 }

		new_data[new_data_counter] = old_data[old_data_counter];
		new_data_counter+=1;

		if(old_data_counter>=4094)
			read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
		else
			old_data_counter+=1;
	}

	if(new_data_counter == 4094)
 	{
		new_data_counter+=1;
		new_data[new_data_counter] = 0;
		write(new_file_descriptor, new_data, 4095);
		new_data_counter=0;
  	}

	new_data[new_data_counter] = old_data[old_data_counter];
	new_data_counter+=1;

	if(old_data_counter>=4094)
		read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
	else
		old_data_counter+=1;
 }
 else if(old_data[old_data_counter] == 33 || old_data[old_data_counter] == 37 || (old_data[old_data_counter] >=40 && old_data[old_data_counter] <=43 )|| old_data[old_data_counter] == 38 || (old_data[old_data_counter] >=44 && old_data[old_data_counter] <=63) || old_data[old_data_counter] == 91 || (old_data[old_data_counter] >=93 && old_data[old_data_counter] <=95) || (old_data[old_data_counter] >=123 && old_data[old_data_counter] <=126) )
 {
	if(new_data_counter == 4094)
 	{
		new_data_counter+=1;
		new_data[new_data_counter] = 0;
		write(new_file_descriptor, new_data, 4095);
		new_data_counter=0;
  	}

	new_data[new_data_counter] = old_data[old_data_counter];
	new_data_counter+=1;

  	if(old_data_counter>= 4094)
		read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
	else
		old_data_counter+=1;

 }
 else
 {
  temp= macro_array[old_data[old_data_counter] - 65];

  for(int i=0;i<50;i++)
  {
	if( (old_data[old_data_counter]>=65 && old_data[old_data_counter] <=90) || (old_data[old_data_counter]>=97 && old_data[old_data_counter] <=122) )
		temp_buffer[i]= old_data[old_data_counter];
	else
	{
		temp_buffer[i]=0;
		if(old_data_counter> 4094)
			read_data(old_file_descriptor, old_data , new_file_descriptor, new_data);
		break;
	}

	old_data_counter+=1;

	if(old_data_counter> 4094)
		read_data(old_file_descriptor, old_data , new_file_descriptor, new_data);
  }

  while(temp!=NULL)
 {

  	if(!strncmp(temp->macro,temp_buffer, strlen(temp_buffer)))
  	{
		if(strchr(temp->macro, 40))
			function_macro_bit=1;

		break;
	}
  temp= temp->next;
 }

 if(temp)
 {
	if(function_macro_bit)
	{
		if(old_data_counter>= 4094)
			read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
		else
			old_data_counter+=1;

		strcpy(old_macro_value_copy, temp->macro_value);

		old_macro_value_copy[strlen(temp->macro_value)]=0;

		tracer= strchr(temp->macro , 40);

		tracer+=1;

		strcpy(new_macro_value_copy , old_macro_value_copy );

		new_macro_value_copy[strlen(old_macro_value_copy)]=0;

		first_byte_reminder= new_macro_value_copy;

		strcpy(temp_copy, new_macro_value_copy);

		temp_copy[strlen(new_macro_value_copy)] = 0;		

		while(1)
		{
			
			while(*tracer == 32)
				tracer+=1;			

			reminder= function_macro_arg;
			while(*tracer!=32 && *tracer!= 44 && *tracer!=41)
			{
				*reminder= *tracer;
				reminder+=1;
				tracer+=1;
			}

			*reminder= 0;

			reminder= function_macro_arg_value;
			while(old_data[old_data_counter] !=32 && old_data[old_data_counter]!=44 && old_data[old_data_counter]!=41)
			{
				*reminder= old_data[old_data_counter];
				reminder+=1;
				
				if(old_data_counter>=4094)
					read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
				else
					old_data_counter+=1;
			}

			*reminder= 0;

			first_byte_reminder_of_FM_arg_replacement = new_macro_value_copy;

			while(*first_byte_reminder_of_FM_arg_replacement <65 && *first_byte_reminder_of_FM_arg_replacement>122)
			first_byte_reminder_of_FM_arg_replacement+=1;

			while(1)
			{
				if(!(first_byte_reminder_of_FM_arg_substring = strstr(first_byte_reminder_of_FM_arg_replacement , function_macro_arg)))
					break;

				tracer2= first_byte_reminder_of_FM_arg_replacement;

				while(1)
				{
					if(((*tracer2>=65 && *tracer2<=90)|| (*tracer2>=93 && *tracer2<=122) || (*tracer2>=48 && *tracer2<=57) || *tracer2 == 95))
						tracer2+=1;
					else
					{
						if(tracer2 > first_byte_reminder_of_FM_arg_substring)
							break;
						else
						{
							first_byte_reminder_of_FM_arg_replacement= tracer2;
							tracer2+=1;
						}				
					}
				}

				if(first_byte_reminder_of_FM_arg_replacement != new_macro_value_copy)
					first_byte_reminder_of_FM_arg_replacement+=1;


				tracer3= temp_copy + (first_byte_reminder_of_FM_arg_replacement - new_macro_value_copy);

				while((*tracer3>=65 && *tracer3<=90)|| (*tracer3>=93 && *tracer3<=122) || (*tracer3>=48 && *tracer3<=57) || *tracer3 == 95)
					tracer3+=1;

				while((*first_byte_reminder_of_FM_arg_replacement<65 || *first_byte_reminder_of_FM_arg_replacement>90) &&
					(*first_byte_reminder_of_FM_arg_replacement<97 || *first_byte_reminder_of_FM_arg_replacement>122))
					first_byte_reminder_of_FM_arg_replacement+=1;

				if(strncmp(function_macro_arg, first_byte_reminder_of_FM_arg_replacement , (tracer2 - first_byte_reminder_of_FM_arg_replacement)))
					break;
				reminder= function_macro_arg_value;

				tracer3 = tracer2;

				tracer2= first_byte_reminder_of_FM_arg_replacement;

				while(*reminder != 0)
				{
					*tracer2 = *reminder;
					 tracer2+=1;
					 reminder+=1;
				}

				first_byte_reminder_of_FM_arg_replacement = tracer2;

				while(*tracer3 != 0)
				{
					if(tracer2 - first_byte_reminder == 49)
					{
						*tracer2=0;
						break;
					}
					*tracer2= *tracer3;
					tracer2+=1;
					tracer3+=1;
				}

				if(*tracer3==0)
					*tracer2=0;

				strcpy(temp_copy, new_macro_value_copy);

				temp_copy[strlen(new_macro_value_copy)] = 0;		
			}

			while(*tracer == 32 || *tracer == 44)
				tracer+=1;

			while(old_data[old_data_counter] == 32 || old_data[old_data_counter] == 44)
			{
				if(old_data_counter>= 4094)
					read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
				else
					old_data_counter+=1;
			}

			if(*tracer==41)
			{
				if(old_data_counter>= 4094)
					read_data(old_file_descriptor, old_data , new_file_descriptor, new_data)
				else
					old_data_counter+=1;
				tracer+=1;		
				break;
			}
		}

		if(strlen(new_macro_value_copy) > (4094 - new_data_counter + 1))
		{
			new_data[new_data_counter]=0;
			write(new_file_descriptor, new_data , strlen(new_data));
			new_data_counter=0;
		}

		new_data[new_data_counter]=0;
		strcat(new_data, new_macro_value_copy);
		new_data_counter+=strlen(new_macro_value_copy);
		function_macro_bit=0;

	}
	else
	{
		if(strlen(temp->macro_value) > (4094 - new_data_counter + 1))
		{
			new_data[new_data_counter]=0;
			write(new_file_descriptor, new_data , strlen(new_data));
			new_data_counter=0;
		}

		new_data[new_data_counter]=0;
		strcat(new_data, temp->macro_value);
		new_data_counter+=strlen( temp->macro_value);

	}
 }
 else
 {
	if(strlen(temp_buffer) > (4094 - new_data_counter + 1))
	{
		new_data[new_data_counter]=0;
		write(new_file_descriptor, new_data , strlen(new_data));
		new_data_counter=0;
	}

	new_data[new_data_counter]=0;
	strcat(new_data, temp_buffer);
	new_data_counter+=strlen( temp_buffer);

 }

 }

}


}


