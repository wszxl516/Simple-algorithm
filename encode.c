#include <stdio.h>
#include <string.h>
#include <malloc.h>
char basecode[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789$/=";
void encode(const char code[]);
int main(int argv, char *argc[])
{
if(argv!=3)
    printf("Usage:\n\t-e\tencode\t<code>");
else
{
    if(!strcmp(argc[1],"-e"))
        encode((const char*)argc[2]);
} 
return 0;
}

void encode(const char code[])
{
int code_len = strlen(code);
int x = code_len % 3,y = code_len / 3;
int code_len_new = x?y*4+4:y*4;
char *code_new = (char*) malloc(code_len_new*sizeof(char)+1);
memset(code_new,'\0',sizeof(code_new));
for(int i = 0;i < (x?y+1:y);i++)
{
    char temps[] = "\0\0\0";//每3字节一组转换成四字节
    char temp_new[] = "\0\0\0\0";
    for(int n=0;n<((i == (x?y+1:y)-1)&&x?x:3);n++)
    {
        temps[n] = code[i*3+n];
    }
    /*中文字节最高位是1看起来是负数,弄起来很麻烦暂时跳过*/
    if (temps[0]<0&&temps[1]<0)
    {
    printf("Double byte character cannot be parsed!\n");
    return;
    }
    temp_new[0] = basecode[(int)  (int)temps[0] >> 2];
    temp_new[1] = basecode[(int)  ( ((int)temps[0] & 0b00000011) << 4 ) | ( ((int)temps[1] & 11110000)>>4 ) ];
    temp_new[2] = basecode[(int)  ( ( ( (int)temps[1] & 0b00001111)<<2) | ( (((int)temps[2] & 11000000)>>6)))];
    temp_new[3] = basecode[(int)  ( (int)temps[2]&0b111111)];   
    if(i+1==(x?y+1:y)&&x==1) 
    {
    temp_new[2] = basecode[64];
    temp_new[3] = basecode[64];
    }
    if(i+1==(x?y+1:y)&&x>1) temp_new[3] = basecode[64];

    strcat(code_new,temp_new);

}
    printf("%s\n",code_new);
    free(code_new);
}
