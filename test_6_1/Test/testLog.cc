#include "Log.hpp"

int main()
{
    Log logger;

    // 测试屏幕输出
    logger.Enable(Screen);
    logger(Info, "This is an info log with no parameters");
    logger(Warning, "This is a warning log with one parameter: %d", 42);
    logger(Error, "This is an error log with two parameters: %s and %d", "error_code", 404);

    // 测试单文件输出
    logger.Enable(Onefile);
    logger(Debug, "Debug log to one file with one parameter: %f", 3.14);
    logger(Fatal, "Fatal log to one file with no parameters");

    // 测试分类文件输出
    logger.Enable(Classfile);
    logger(Info, "Info log to class file");
    logger(Warning, "Warning log to class file with two parameters: %s and %d", "test", 123);

    return 0;
}