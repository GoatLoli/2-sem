#include <iostream>
#include <chrono>
#include <fstream>
#include <string>

int main()
{
	std::ifstream in("output1.txt");
	void counter(int count)

		if (in.is_open())
		{
			std::string line;
			while (std::getline(in, line))
			{
				count++;
			}
		}
	

	void open()
	{
		std::ofstream file("output1.txt", std::ios::app); // открываем файл для записи (дополнение в конец файла)
	}

	void getAndConvertTime()
	{
		//извлекает текущее системное время и преобразует его в структуру tm
		auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);

		tm* timeinfo = std::localtime(&now_c);
	}

	void writeClose()
	{
		file << "execution num " << count + 1 << ". Дата: " << timeinfo->tm_year + 1900 << "-" << timeinfo->tm_mon + 1 << "-" << timeinfo->tm_mday << ", Время:" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << std::endl;

		file.close();
	}
}
