#include<iostream>
#include<string>
#define num(x) ((x) - 97)
#define Num(x) ((x) - 65)
#define alp(x) char((x) + 97)
#define Alp(x) char((x) + 65)
void enc_out(const std::string& m, const std::string& k)
{
	auto j = k.begin();
	for(auto i: m)
	{
		std::cout << Alp((num(i) + num(*j)) % 26);
		j++;
		if(j == k.end()) j = k.begin();
	}
	std::cout << std::endl;
}
void dec_out(const std::string& m, const std::string& k)
{
	auto j = k.begin();
	for(auto i: m)
	{
		std::cout << alp((Num(i) - num(*j) + 26) % 26);
		j++;
		if(j == k.end()) j = k.begin();
	}
	std::cout << std::endl;
}
int main()
{
	std::cout << "Vigenere\n\n请选择要进行的操作\n";
	int flag;
	do
	{
		std::cout << "1.加密\n2.解密\n";
		std::cin >> flag;
		std::string m, k;
		if(flag == 1)
		{
			std::cout << "明文：";
			std::cin >> m;
			std::cout << "密钥：";
			std::cin >> k;
			std::cout << "密文：";
			enc_out(m, k);
		}
		if(flag == 2)
		{
			std::cout << "密文：";
			std::cin >> m;
			std::cout << "密钥：";
			std::cin >> k;
			std::cout << "明文：";
			dec_out(m, k);
		}
	} while(flag == 1 || flag == 2);
}
