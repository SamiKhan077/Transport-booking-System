/*This module validate the password criteria :
Funcion name: pass_validate(String)
Return value: 
    1->Password Accepted
    0->Password not Accepted
*/
int pass_validate(char pass[])
{
    int out,len,i,a[4]={},flag=1;
    len=strlen(pass);

    if(len>8)
    {
    for(i=0;i<len;i++)
    {
        if('A'<=pass[i] && pass[i]<='Z')
        a[0]++;

        if('a'<=pass[i] && pass[i]<='z')
        a[1]++;

        if('0'<=pass[i] && pass[i]<='9')
        a[2]++;

        if('!'<=pass[i] && pass[i]<='/'||':'<=pass[i] && pass[i]<='@'||'['<=pass[i] && pass[i]<='.'||'{'<=pass[i] && pass[i]<='`')
        a[3]++;

    }
    }
    else
    {
        printf("Password must have atleast 8 characters:(\n");
        return 0;
    }

    
    for(i=0;i<4;i++)
    {
        if(a[i]==0)
        {
            switch (i)
            {
                case 0:
                printf("Password must have atleast 1 Capital Alphabet:(\n");
                break;

                case 1:
                printf("Password must have atleast 1 Small Alphabet:(\n");
                break;

                case 2:
                printf("Password must have atleast 1 Numerical Value:(\n");
                break;

                 case 3:
                printf("Password must have atleast 1 Special Symbol:(\n");

            }
            flag =0;
        }
    }

    if (flag==0)
    return 0;
    else
    {
        return 1;
    }
    
    

}


