//Дан файл, в котором в каждой строчке записано системное время каждого запуска программы в формате :
//номер_запуска - год - месяц - день - час - минута - секунда
//Создайте программу, которая при каждом запуске будет дописывать в файл строку с порядковым номером и временем запуска.

//Предусмотрите автоматическое копирование текстового файла с номером и временем запуска. - ?
//Создайте локальный и удаленный репозитории, синхронизируйте их. (операции commit, push, pull.)

#include <iostream>
#include <chrono>
#include <fstream>
#include <string>

int main()
{
	std::ifstream in("output1.txt");
	int count = 0;

	if (in.is_open())
	{
		std::string line;
		while (std::getline(in, line))
		{
			count++;
		}
	}

	std::ofstream file("output1.txt", std::ios::app); // открываем файл для записи (дополнение в конец файла)

	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	tm* timeinfo = std::localtime(&now_c);

	file << "execution num " << count + 1 << ". Дата: " << timeinfo->tm_year + 1900 << "-" << timeinfo->tm_mon + 1 << "-" << timeinfo->tm_mday << ", Время:" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << std::endl;

	file.close();

	std::cout << "Data written at output1.txt file in build folder" << std::endl;
}
