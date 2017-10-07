#pragma once
#include <string>

class Logger {
public:
	Logger();
	void Clear() const;
	void Write(const std::string& text) const;
	void SetFile(const std::string &fileName);

private:
	std::string file;
};

extern Logger logger;
