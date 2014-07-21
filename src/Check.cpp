#include "Check.h"

bool Check::CheckEmail(std::string email) {
			k=2;
			for(int i=0;email[i]!='\0';i++)
				if(email[i]=='@'||email[i]=='.'||email[i]>='0'&&email[i]<='9'||
					email[i]>='A'&&email[i]<='Z'||email[i]>='a'&&email[i]<='z'){}
				else{k=-1;break;}
			if(k==-1)continue;
			int j=0;
			while(email[j]!='@'&&email[j]!='\0'){
				if(email[j]=='.'){
					k=-1;
					break;
				}
				j++;
			}
			if(!j)continue;
			j++;
			if(email[j]=='\0'||k==-1)continue;
			for(int i=j;email[i]!='\0';i++){
				if(s[i]=='.'){
					if(i>j&&s[i+1]!='\0'){j=i+1;k++;continue;}
					else{k=-1;break;}
				}
				if(email[i]=='@'){k=-1;break;}
			}
			if(k>2)
			   return true;
			else
				return false;
}
