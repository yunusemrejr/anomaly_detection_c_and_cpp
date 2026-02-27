#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include <string>
#include <vector>

enum class DetectionMethod {
    ZSCORE,
    IQR,
    MAD,
    MODIFIED_ZSCORE
};

enum class OutputFormat {
    TERMINAL,
    JSON,
    CSV
};

struct CLIOptions {
    std::string input_file;
    std::string output_file;
    DetectionMethod method;
    OutputFormat format;
    double threshold;
    bool use_stdin;
    bool show_help;
    bool show_version;
    bool verbose;
    std::vector<int> columns;
    bool has_header;
    
    CLIOptions() 
        : method(DetectionMethod::ZSCORE)
        , format(OutputFormat::TERMINAL)
        , threshold(2.0)
        , use_stdin(true)
        , show_help(false)
        , show_version(false)
        , verbose(false)
        , has_header(false) {}
};

class CLIParser {
public:
    static CLIOptions parse(int argc, char* argv[]);
    static void printHelp();
    static void printVersion();
    
private:
    static DetectionMethod parseMethod(const std::string& method);
    static OutputFormat parseFormat(const std::string& format);
};

#endif // CLI_PARSER_H
