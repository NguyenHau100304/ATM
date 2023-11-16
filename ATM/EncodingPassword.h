#pragma once



#include<string>


std::string encoding(std::string pw) {
	for (char& c : pw)
	{
		c = c - 3;
		if (c < 48)
			c = 58 - (48 - c);
	}
	return pw;
}
std::string decoding(std::string pw) {
	for (char& c : pw)
	{
		c = c + 3;
		if (c > 57)
			c = 47 + (c - 57);
	}
	return pw;
}