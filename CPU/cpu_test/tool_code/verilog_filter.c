#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
int main(void)
{
	char s[1010];
	freopen("verilog_output.txt","r",stdin);
	//freopen("verilog_ans.txt","w",stdout);
	fgets(s,1010,stdin);
	fgets(s,1010,stdin);
	char *ans;
	while(fgets(s,1010,stdin)!=NULL){
		//ans=s+20;
		ans=s; 
		printf(ans);
	}
	fclose(stdin);
	//fclose(stdout);
	return 0;
}
