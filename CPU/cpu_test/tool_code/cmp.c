#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
int main(void)
{
	FILE *ans,*output;
	ans=fopen("MARS_ans.txt","r");
	output=fopen("verilog_ans.txt","r");
	freopen("cmp_result.txt","w",stdout); 
	char s1[101],s2[101];
	char *judge1,*judge2;
	int rownum=0;
	int tag=0;		//表示共同长度内是否出现不匹配 
	while(1){
		rownum++;
		judge1=fgets(s1,101,ans);
		judge2=fgets(s2,101,output);
		if(s1[0]=='\n')judge1=NULL;
		if(s2[0]=='\n')judge2=NULL;
		if(s1[strlen(s1)-1]=='\n')s1[strlen(s1)-1]='\0';	//文本读入时只有\n 二进制打开才有\r\n
		if(s2[strlen(s2)-1]=='\n')s2[strlen(s2)-1]='\0';
		if((judge1==NULL)+(judge2==NULL)==1){
			if(tag||rownum==1){
				puts("The lengths of two files are different.");
			}
			else puts("Finished");
			return 0;
		}
		else if((judge1==NULL)+(judge2==NULL)==2){
			puts("Finished");
			fclose(ans);
			fclose(output);
			fclose(stdout);
			return 0;
		}
		else if(strcmp(s1,s2)){
			printf("line %d has a mismatch when doing %s in MARS,%s in verilog\n",rownum,s1,s2);
			tag=1; 
		}
	}
	return 0;
}
