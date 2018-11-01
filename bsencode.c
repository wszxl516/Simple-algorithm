#include <stdio.h>
#include <malloc.h>
#include <string.h>
const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

void base64_encode(const char* data);

void base64_decode(const char* data);

static char find_pos(char ch);

void base64_encode(const char* data)

{

int data_len = strlen(data);

int prepare = 0;

int ret_len;

int temp = 0;

char *ret = NULL;

char *f = NULL;

int tmp = 0;

char changed[4];

int i = 0;

ret_len = data_len / 3;

temp = data_len % 3;

if (temp > 0)

{

ret_len += 1;

}

ret_len = ret_len*4 + 1;

ret = (char *)malloc(ret_len);

if ( ret == NULL)

{

printf("No enough memory.\n");

return;

}

memset(ret, 0, ret_len);

f = ret;

while (tmp < data_len)

{

temp = 0;

prepare = 0;

memset(changed, '\0', 4);

while (temp < 3)

{

if (tmp >= data_len)

{

break;

}

prepare = ((prepare << 8) | (data[tmp] & 0xFF));

tmp++;

temp++;

}

prepare = (prepare<<((3-temp)*8));

for (i = 0; i < 4 ;i++ )

{

if (temp < i)

{

changed[i] = 0x40;

}

else

{

changed[i] = (prepare>>((3-i)*6)) & 0x3F;

}

*f = base[(int)changed[i]];


f++;

}

}

*f = '\0';

printf(ret);
free(ret);
}

/* */

static char find_pos(char ch)

{

char *ptr = (char*)strrchr(base, ch);

return (ptr - base);

}

/* */

void base64_decode(const char *data)

{
int data_len = strlen(data);
int ret_len = (data_len / 4) * 3;

int equal_count = 0;

char *ret = NULL;

char *f = NULL;

int tmp = 0;

int temp = 0;

char need[3];

int prepare = 0;

int i = 0;

if (*(data + data_len - 1) == '=')

{

equal_count += 1;

}

if (*(data + data_len - 2) == '=')

{

equal_count += 1;

}

if (*(data + data_len - 3) == '=')

{
    equal_count += 1;
}

switch (equal_count)

{

case 0:

ret_len += 4;//3 + 1 [1 for NULL]

break;

case 1:

ret_len += 4;//Ceil((6*3)/8)+1

break;

case 2:

ret_len += 3;//Ceil((6*2)/8)+1

break;

case 3:

ret_len += 2;//Ceil((6*1)/8)+1

break;

}

ret = (char *)malloc(ret_len);

if (ret == NULL)

{

printf("No enough memory.\n");

return;

}

memset(ret, 0, ret_len);

f = ret;

while (tmp < (data_len - equal_count))

{

temp = 0;

prepare = 0;

memset(need, 0, 4);

while (temp < 4)

{

if (tmp >= (data_len - equal_count))

{

break;

}

prepare = (prepare << 6) | (find_pos(data[tmp]));

temp++;

tmp++;

}

prepare = prepare << ((4-temp) * 6);

for (i=0; i<3 ;i++ )

{

if (i == temp)

{

break;

}
*f = (char)((prepare>>((2-i)*8)) & 0xFF);

f++;

}

}

*f = '\0';

printf("%s",ret);
free(ret);

}

int main(int argc, char *argv[])
{
    const char *codes=NULL;
    if(argc!=3)
    {

        printf("Usage:\n\t%s\n\t-e <code>  encode\n\t-d <code>  decode",argv[0]);
        return 0;
    }
    if(!strcmp(argv[1],"-e"))
    {
        codes = argv[2];
        base64_encode(codes);
    }
    if(!strcmp(argv[1],"-d"))
    {
        codes = argv[2];
        base64_decode(codes);
    }
    return 0;
}
