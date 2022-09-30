#ifndef LOGFILE_HPP
#define LOGFILE_HPP
#include <iostream>
#include <sstream>
#include <fstream>

class Logfile
{
private:
	std::string		filename;
	std::string		path;
	std::ofstream	file;

public:
	Logfile(std::string name = "logfile.log");
	Logfile(const Logfile &origin);
	Logfile &operator=(const Logfile &origin);
	~Logfile();

private:
	bool fileIsOpen();
	void openFile();
	void closeFile();
	void writeToFile(const std::stringstream& content);

public:
	void clear();
	void operator<<(const std::stringstream& content);
	void set_path(const std::string& path);
	std::string get_filename() const;
	std::string get_fullname() const;
};
bool compare_file(std::string filename_std, std::string filename_ft);
bool compare_time(std::string line1, std::string line2);
#endif