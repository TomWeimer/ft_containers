#include "Logfile.hpp"
#include <cstdlib>
#include <cstring>
Logfile::Logfile(std::string name)
	: filename(name), path() {}

Logfile::Logfile(const Logfile& origin)
	: filename(origin.filename), path(origin.path) {}

Logfile &Logfile::operator=(const Logfile& origin)
{
	if (this == &origin)
		return (*this);
	if (fileIsOpen() == true)
		closeFile();
	this->filename = origin.filename;
	return (*this);
}

Logfile::~Logfile(void)	{}

bool Logfile::fileIsOpen(void)
{
	return (file.is_open());
}

void Logfile::openFile(void)
{
	std::string fullname;
	fullname = path;
	fullname += this->filename;
	file.open(fullname.c_str(), std::ofstream::out | std::ofstream::app);
}

void Logfile::closeFile(void)
{
	file.close();
}

void Logfile::writeToFile(const std::stringstream& content)
{
	file << content.str();
}

void Logfile::clear(void)
{
	std::string fullname;
	if (fileIsOpen())
		closeFile();
	fullname = path;
	fullname += filename;
	file.open(fullname.c_str(), std::ofstream::out | std::ofstream::trunc);
	closeFile();
}

void Logfile::operator<<(const std::stringstream& content)
{
	openFile();
	writeToFile(content);
	closeFile();
}

void Logfile::set_path(const std::string& the_path)
{
	path = the_path;
}

std::string Logfile::get_filename() const
{
	return (filename);
}

std::string Logfile::get_fullname() const
{
	std::string fullname;

	fullname = path;
	fullname += filename;
	return (fullname);
}


bool compare_time(std::string line1, std::string line2)
{
	int timeValue[2];

	line1 = line1.substr(6);
	line2 = line2.substr(6);
	line1.erase(line1.size() - 3, 3);
	line2.erase(line2.size() - 3, 3);
	timeValue[0] = atoi(line1.c_str());
	timeValue[1] = atoi(line2.c_str());
	if (timeValue[0] == 0)
		timeValue[0] = 1;
	if (timeValue[1] == 0)
		timeValue[1] = 1;
	return (timeValue[0] * 40 >= timeValue[1]);
}

bool compare_file(std::string filename_std, std::string filename_ft)
{
	std::ifstream 	infile_std;
	std::ifstream 	infile_ft;
	std::string		line[2];
	bool			testOk = true;

	// std::cerr << "PUTE" << filename_std << " " << filename_ft << " is_open: " << infile_std.is_open()  << std::endl;
	infile_std.open(filename_std.c_str());
	infile_ft.open(filename_ft.c_str());
	while (infile_std.good() && infile_ft.good())
	{
		std::getline(infile_std, line[0]);
		std::getline(infile_ft, line[1]);
		if (line[0] != line[1])
		{
			if (line[0].find("time: ") != std::string::npos
				&& line[1].find("time: ") != std::string::npos) {
				testOk = compare_time(line[0], line[1]);
			}
			else {
				testOk = false;
				break;
			}
		}
		// std::cerr << "std: " << line[0] << "["<< std::endl;
		// std::cerr << "ft: " << line[1] << "[" << std::endl << std::endl;
		// line[0].clear();
		line[1].clear();

	}
	infile_std.close();
	infile_ft.close();
	return (testOk);
}
