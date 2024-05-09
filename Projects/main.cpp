#include "Words.h"

#include <iostream>

void SubstitueCharDino(char& character)
{
	switch (std::tolower(character))
	{
	case 'a':
	{
		character = 'u';
		break;
	}
	case 'b':
	{
		character = 'r';
		break;
	}
	case 'c':
	{
		character = 's';
		break;
	}
	case 'd':
	{
		character = 't';
		break;
	}
	case 'e':
	{
		character = 'o';
		break;
	}
	case 'f':
	{
		character = 'v';
		break;
	}
	case 'g':
	{
		character = 'w';
		break;
	}
	case 'h':
	{
		character = 'x';
		break;
	}
	case 'i':
	{
		character = 'a';
		break;
	}
	case 'j':
	{
		character = 'z';
		break;
	}
	case 'k':
	{
		character = 'b';
		break;
	}
	case 'l':
	{
		character = 'c';
		break;
	}
	case 'n':
	{
		character = 'd';
		break;
	}
	case 'o':
	{
		character = 'e';
		break;
	}
	case 'p':
	{
		character = 'f';
		break;
	}
	case 'q':
	{
		character = 'g';
		break;
	}
	case 'r':
	{
		character = 'h';
		break;
	}
	case 's':
	{
		character = 'j';
		break;
	}
	case 't':
	{
		character = 'k';
		break;
	}
	case 'u':
	{
		character = 'i';
		break;
	}
	case 'v':
	{
		character = 'l';
		break;
	}
	case 'w':
	{
		character = 'n';
		break;
	}
	case 'x':
	{
		character = 'p';
		break;
	}
	case 'y':
	{
		character = 'o';
		break;
	}
	case 'z':
	{
		character = 'q';
		break;
	}
	}
}

std::string ConvertToDinoTalk(const std::string& string)
{
	std::string newString = string;
	
	for (size_t i = 0; i < newString.size(); i++)
	{
		if (newString[i] == ' ')
		{
			continue;
		}
		else if (newString[i] == 'm') continue;

		SubstitueCharDino(newString[i]);
	}

	return newString;
}

int main()
{
	std::cout << "Articles:" << std::endl;
	for (const std::string& word : articles)
	{
		std::cout << word << " = " << ConvertToDinoTalk(word) << std::endl;
	}

	std::cout << "\nNouns" << std::endl;
	for (const std::string& word : nouns)
	{
		std::cout << word << " = " << ConvertToDinoTalk(word) << std::endl;
	}

	std::cout << "\nPronouns:" << std::endl;
	for (const std::string& word : pronouns)
	{
		std::cout << word << " = " << ConvertToDinoTalk(word) << std::endl;
	}

	std::cout << "\nVerbs:" << std::endl;
	for (const std::string& word : verbs)
	{
		std::cout << word << " = " << ConvertToDinoTalk(word) << std::endl;
	}

	std::cout << "\nAuxiliary Verbs:" << std::endl;
	for (const std::string& word : auxiliaryVerbs)
	{
		std::cout << word << " = " << ConvertToDinoTalk(word) << std::endl;
	}

	std::cout << "\nLinking Verbs:" << std::endl;
	for (const std::string& word : linkingVerbs)
	{
		std::cout << word << " = " << ConvertToDinoTalk(word) << std::endl;
	}

	std::cout << "\nModal Verbs:" << std::endl;
	for (const std::string& word : modalVerbs)
	{
		std::cout << word << " = " << ConvertToDinoTalk(word) << std::endl;
	}

	std::cout << "\nAdjectives:" << std::endl;
	for (const std::string& word : adjectives)
	{
		std::cout << word << " = " << ConvertToDinoTalk(word) << std::endl;
	}

	std::cout << "\nPrepositions:" << std::endl;
	for (const std::string& word : prepositions)
	{
		std::cout << word << " = " << ConvertToDinoTalk(word) << std::endl;
	}

	std::cout << "\nConjunctions:" << std::endl;
	for (const std::string& word : conjunctions)
	{
		std::cout << word << " = " << ConvertToDinoTalk(word) << std::endl;
	}

	std::cout << "\n" << ConvertToDinoTalk("She reads interesting books quietly in the library") << std::endl;

	return 0;
}