#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>

//#define n 100   //叶子结点数
//#define m 2*n-1  // Huffman树中结点总数
typedef struct {
	char data;   //字符
int weight;	//权值
	int lchild ,  rchild , parent;   //左右孩子及双亲指针
}HTNode;   //树中结点类型
typedef HTNode HuffmanTree[500];	//0号单元不用
typedef char **HuffmanCode;
int count(char a[],int b[]){
    char s[500];
    int t=0;
    char q[500];
    FILE *fp;
     printf("请输入要打开的文件:\n");
     scanf("%s",q);
    fp=fopen(q,"r");
     if((fp=fopen(q,"r"))==NULL)
    {
         printf("The file can not be opened.\n");
        exit(0);
        }
        while(!feof(fp)){
            fscanf(fp,"%c",&s[t]);
            t++;
        }
    printf("字符总数：%d\n",t-1);
    int x=0,i;
    for(i=0;i<t-1;i++){
            if(s[i]=='\0')continue;
       else{
            a[x]=s[i];
            b[x]++;
           for(int j=i+1;j<t-1;j++){
                if(s[i]==s[j]){
                     s[j]='\0';
                     b[x]++;
            }
        }
        x++;
    }
    }
    printf("字符类型数目：%d\n",x);
    printf("各字符及数目：\n");
    for(i=0;i<x;i++){
        printf("%15c %d\n",a[i],b[i]);

    }
    return x;
}
void Select(HuffmanTree &HT,int n,int *s1,int *s2){
    int k,a;
    for(k=1;k<=n;k++){
        if(!HT[k].parent){
            a=HT[k].weight;
            *s1=k;
            break;
    }
    }
    for(k=1;k<=n;k++)
        if(!HT[k].parent)
        if(HT[k].weight<a){
            a=HT[k].weight;
            *s1=k;
        }
    for(k=1;k<=n;k++)
        if(!HT[k].parent&&k!=*s1){
            a=HT[k].weight;
            *s1=k;
            break;
    }
    for(k=1;k<=n;k++)
        if(!HT[k].parent&&k!=*s1)
        if(HT[k].weight<a){
            a=HT[k].weight;
            *s2=k;
        }
}
void BuildTree(HuffmanTree &HT,int b[],int n,char a[]){
    //count();
    int i,m,s1,s2;
    m=2*n-1;
    if(n<=1) return;
    for(i=1;i<=n;i++){
        HT[i].weight=b[i-1];
        HT[i].data=a[i-1];
        HT[i].parent=0;
        HT[i].lchild=0;
        HT[i].rchild=0;
    }
    for(i=n+1;i<=m;i++){
        HT[i].weight=0;
        HT[i].parent=0;
        HT[i].lchild=0;
        HT[i].rchild=0;
    }
    for(i=n+1;i<=m;i++){
        Select(HT,i-1,&s1,&s2);
        HT[s1].parent=i;HT[s2].parent=i;
        HT[i].lchild=s1;HT[i].rchild=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }
}
void HuffmanCoding(HuffmanTree HT,HuffmanCode &HC,int n){

    HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
    char *cd;
    int start,i,c,f;
    cd=(char*)malloc(n*sizeof(char));
    if(n<=1) return;
    cd[n-1]='\0';
    for(i=1;i<=n;i++){
        start=n-1;
        for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
            if(HT[f].lchild==c) cd[--start]='0';
        else cd[--start]='1';
        HC[i]=(char*)malloc((n-start)*sizeof(char));
        strcpy(HC[i],&cd[start]);
    }
    free(cd);
}
void TextCoding(HuffmanCode &TC,char s[],char c[],HuffmanCode HC){
    int len1,len2,i,j;
    len1=strlen(s);
    len2=strlen(c);
    TC=(HuffmanCode)malloc((len2+1)*sizeof(char*));
    if(len2<=1) return;
    for(i=1;i<=len1;i++){
        for(j=1;j<=len2;j++)
            if(s[i-1]==c[j-1])
            break;
        TC[i]=(char*)malloc((strlen(HC[j])+1)*sizeof(char));
        strcpy(TC[i],HC[j]);
    }
    printf("\n密文为：\n");
    for(int j=1;j<=len1;j++){
		printf("%d %s\n",j,TC[j]);
	}
}
void Translate(HuffmanCode TC,char c[],HuffmanCode HC,int len1,int len2){
int i,j;
if(len2<=1) return;
printf("\n翻译加密的正文:\n");
for(i=1;i<=len1;i++){
    for(j=1;j<=len2;j++)
        if(!strcmp(TC[i],HC[j])) break;
        printf("%c",c[j-1]);
}
}
int main(){
	HuffmanTree HT;
	HuffmanCode HC,TC;
	char a[500],s[100];
	int b[500]={0},len;
	int n=count(a,b);
	BuildTree(HT,b,n,a);
	HuffmanCoding(HT,HC,n);
	 printf("请输入要加密的正文:\n");
        scanf("%s",s);
	TextCoding(TC,s,a,HC);
	len=strlen(s);
	Translate(TC,a,HC,len,n);
	return 0;
}
