
#include"JP_headerfile.h"

extern struct node *macro_array[58];

int main()
{
 char old_file_name[100] = "/home/sunny/Studies/Projects On linux/Preprocessor/testc1.java";
 Data_processor(old_file_name);

 struct node * temp_ptr1=NULL;
 struct node * temp_ptr2=NULL;
/*

 for(int i=0;i<58; i++)
 {
  temp_ptr1=macro_array[i];
  while(temp_ptr1!=NULL)
  {
    printf("macro: %s \t macro_value: %s\n",temp_ptr1->macro,temp_ptr1->macro_value);
    temp_ptr1=temp_ptr1->next;
  }
 }


*/

 int new_fd= creat("/home/sunny/Studies/Projects On linux/Preprocessor/testc1_preprocessed.java", 0777);

 int old_fd = open("/home/sunny/Studies/Projects On linux/Preprocessor/testc1.java", O_RDONLY);

 macro_replacer_and_comment_removal(old_fd, new_fd);
 
 close(old_fd);
 close(new_fd);

 for(int i=0;i<58; i++)
 {
  temp_ptr1=macro_array[i];
  while(temp_ptr1!=NULL)
  {
   temp_ptr2=temp_ptr1->next;   
   
   free(temp_ptr1);
   temp_ptr1=temp_ptr2;
  }

 }

 return 0;
}
