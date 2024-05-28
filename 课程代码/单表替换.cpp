#include<iostream>   // 引入输入输出流库
#include<string>      // 引入字符串库
using namespace std; // 引入命名空间

void Encrypt(char Substitution[]);   // 声明加密函数
void Decrypt(char Substitution[]);   // 声明解密函数
void setSubstitution(char Substitution[],char ReverseTable[]);  // 声明设置置换表函数

int main() // 主函数
{
    int m; // 声明变量m，用于判断是加密还是解密，加密为1，解密为2
    int flag = 1; // 声明变量 flag，用于控制循环程序是否运行，开始时为1

    while(flag) // 循环运行
    {
        cout<<"单表置换算法加解密："<<endl;
        char SubstitutionTable['z'+1];   // 定义数组，用于保存正向置换表（它的下标是原字符的 ASCII 码，其对应的值是替换后的字符的 ASCII 码），加密时使用，长度为 z+1
        char ReverseTable['Z'+1];  // 定义数组，用于保存反向置换表（它的下标是替换后的字符的 ASCII 码，其对应的值是原字符的 ASCII 码），解密时使用，长度为 Z+1
        cout<<"加密按输入1，解密输入2"<<endl;
        cin>>m;    // 读取用户输入的值，判断是加密还是解密
        setSubstitution(SubstitutionTable, ReverseTable); // 调用设置置换表函数，设置正向置换表和反向置换表

        if(m!=1&&m!=2) // 判断输入是否正确
        {
            cout<<"输入错误，请重新输入"<<endl;
            cin>>m; // 再次读取用户输入的值
        }

        if(m==1) // 判断是否加密
        {
            Encrypt(SubstitutionTable); // 调用加密函数
        }

        if(m==2) // 判断是否解密
        {
            Decrypt(ReverseTable); // 调用解密函数
        }

        cout<<"是否继续加解密运算？[0->退出； 1 or 其他->继续]"<<endl;
        cin>>flag; // 读取用户输入的值，判断是否继续循环
    }
    return 0;
}

void Encrypt(char Substitution[]) // 加密函数
{
    string plain; // 定义字符串变量，用于保存明文
    cout<<endl<<"请输入明文（小写）：";
    cin>>plain; // 读取用户输入的明文
    cout<<plain<<endl; // 输出用户输入的明文
    cout<<"加密后的密文为："<<endl;
    // 遍历明文中的每个字符，利用置换表Substitution对字符进行替换，并输出替换后的字符，生成密文
    for(int i=0; i<plain.length(); i++) // 遍历明文中的每个字符
    {
        if (plain[i] >= 'a' && plain[i] <= 'z') // 如果字符是小写字母
        // 则在置换表中查找该字母对应的密文字母，输出密文字母
        {
            cout << Substitution[plain[i]];
        }
        else cout << plain[i]; // 如果字符不是小写字母，则直接输出原字符
    }
    cout << endl;
}

void Decrypt(char ReverseTable[]) // 解密函数
{
    string cipher;  // 定义字符串变量，用于保存用户输入的密文
    cout<<endl<<"请输入密文（大写）：";
    cin>>cipher; // 读入用户输入的密文并存储到cipher中
    cout<<cipher<<endl; // 输出密文
    cout<<"解密后的明文为："<<endl;
    for(int i=0; i<cipher.length(); i++) // 循环遍历密文中的每一个字符
    {
        if(cipher[i]>='A' && cipher[i]<='Z') // 判断字符是否在大写字母范围内
        // 如果是，则将其对应的反置换表中的字符输出
        {
            cout << ReverseTable[cipher[i]];
        }
        else cout<<cipher[i]; // 否则直接输出原字符
    }
    cout<<endl;
}

void setSubstitution(char SubstitutionTable[],char ReverseTable[])
{
    int i;  // 定义循环变量i和j
    char j;
    string key;  // 定义字符串，用于存储密钥key
    cout<<"请输入密钥（大写）：";
    cin>>key; // 读入密钥
    cout<<key<<endl; // 输出密钥
    cout<<"置换表为："<<endl;
    string s1; // 定义字符串，用于存储处理后的密钥s1
    // 对密钥进行处理（去掉空格和重复的字符）
    for(i = 0 ; i < key.length();i++) // 循环遍历密钥中的每一个字符
    {
        bool sign =0;  // 定义标志变量，判断是否已经出现过该字符，初始化为false
        if(key[i] >= 'A' && key[i] <='Z') // 如果当前字符是大写字母
        {
            for(int j = 0; j < s1.length();j++) // 遍历处理后的密钥字符串s1
            {
                if(key[i] == s1[j]) // 如果当前字符已经在s1中出现过
                {
                    // 如果已经出现，将标志变量sign设为true，跳出循环
                    sign = 1;
                    break;
                }
            }
            // 如果当前字符没有在s1中出现过，则将其加入s1中
            if(sign == 0) s1 = s1 + key[i];
            // 如果当前字符已经出现过，则将标志变量sign设为false
            else sign = 0;
        }
    }
    for( j ='a';j<='z';j++)cout<<j<<" ";cout<<endl; // 输出小写字母 从a到z
    char ch='A'; // 定义变量ch，表示当前未被用作置换表元素的大写字母，初始化为'A'
    // 该循环利用密钥得到置换表
    for( i = 'a' ;i <= 'z'; i++) // 遍历小写字母a~z
    {
        if(i < 'a' + s1.length()) // 如果当前位置i在s1的长度范围内
        {
            // 将i对应的置换表元素设为s1中对应位置的字符
            SubstitutionTable[i] = s1[i - 'a'];
        }
        else // 如果i在s1的长度范围外
        {
            // 遍历s1中的每一个字符
            for(int j = 'a'; j < 'a' + s1.length(); j++)
            {
                if(ch == SubstitutionTable[j]) // 如果当前生成的字符ch已经在置换表中出现过
                {
                    // 将ch加1，重新从头开始搜索
                    ch++;
                    j= 'a';
                    continue;
                }
            }
            // 将i对应的置换表元素设为当前的字符ch，然后将ch加1
            SubstitutionTable[i] = ch;
            ch++;
        }
        cout<<SubstitutionTable[i]<<" "; // 输出生成的置换表元素
    }
    cout<<endl;
    // 该循环用于构建反置换表
    // 将置换表中的字符和它的下标进行反向映射
    for( i='a'; i<= 'z'; i++) //遍历小写字母a~z
    {
        // 循环变量 i 遍历了所有小写字母
        // 对于每个字母，它首先通过置换表找到映射到的字母
        // 然后将该字母作为下标，将当前遍历到的小写字母作为值，存入到反置换表中
        // 这个过程确保了当使用反置换表进行解密时，可以将密文中的字符逆向映射回原来的明文字符
        ReverseTable[ SubstitutionTable[i] ] = i;
    }
    // 输出反置换表
    cout<<"反置换表为："<<endl;
    for( i='A'; i<= 'Z'; i++) // 循环遍历大写字母
    {
        cout<< ReverseTable[i] <<" "; // 输出反置换表中A到Z字母对应的字符，用空格分隔
    }
    cout<<endl;
}
