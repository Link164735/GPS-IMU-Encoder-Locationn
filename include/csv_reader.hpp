#ifndef CSV_READER_HPP
#define CSV_READER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

class CsvReader {
public:
    // 构造函数
    CsvReader(const std::string& filename);

    // 读取整个 CSV 文件到内存中
    bool read();

    // 获取 CSV 文件中的数据
    std::vector<std::vector<std::string>> getData() const;

private:
    std::string filename;  // CSV 文件的路径
    std::vector<std::vector<std::string>> data;  // 存储读取的数据

    // 将一行字符串分割为字段
    std::vector<std::string> split(const std::string& line, char delimiter) const;
};

#endif // CSV_READER_HPP
