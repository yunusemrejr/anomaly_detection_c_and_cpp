#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <string>
#include <vector>
#include <istream>

class CSVParser {
public:
    static std::vector<std::vector<double>> parseFile(const std::string& filename, 
                                                      bool has_header = false,
                                                      const std::vector<int>& columns = {});
    
    static std::vector<std::vector<double>> parseStream(std::istream& stream,
                                                        bool has_header = false,
                                                        const std::vector<int>& columns = {});
    
    static std::vector<double> flatten(const std::vector<std::vector<double>>& data);
    
private:
    static std::vector<std::string> splitLine(const std::string& line, char delimiter = ',');
    static double parseDouble(const std::string& str, bool& success);
    static std::vector<double> selectColumns(const std::vector<double>& row, 
                                            const std::vector<int>& columns);
};

#endif // CSV_PARSER_H
