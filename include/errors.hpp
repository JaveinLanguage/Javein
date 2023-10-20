#ifndef JAVEIN_ERRORS_HPP
#define JAVEIN_ERRORS_HPP

#include <iostream>

using namespace std;

enum class ErrorCode
{
    UNEXPECTED_END,
    EXPECTED_OPEN_BRACK,
    UNEXPECTED_END_IN_BLOCK,
    EXPECTED_CLOSE_BRACK,
    INVALID_TOKEN,
    ATTEMPT_TO_ADVANCE_BEYOND_END,
};

class Error
{
public:
    static void throwError(ErrorCode code, const string &blockType = "")
    {
        printError(code);
        exit(static_cast<int>(code));
    }

private:
    ErrorCode errorCode;

    static void printError(ErrorCode errorCode, const string &blockType)
    {
        cerr << "Error (" << static_cast<int>(errorCode) << "): " << getErrorMessage(errorCode, blockType) << std::endl;
    }

    static string getErrorMessage(ErrorCode code, const string &blockType)
    {
        switch (code)
        {
            case ErrorCode::UNEXPECTED_END:
                return "Unexpected end of tokens";
            case ErrorCode::EXPECTED_OPEN_BRACK:
                return "Expected '{' after statement";
            case ErrorCode::UNEXPECTED_END_IN_BLOCK:
                return "Unexpected end of tokens inside " + blockType + " statement";
            case ErrorCode::EXPECTED_CLOSE_BRACK:
                return "Expected '}' after statement";
            case ErrorCode::INVALID_TOKEN:
                return "Invalid token encountered";
            case ErrorCode::ATTEMPT_TO_ADVANCE_BEYOND_END:
                return "Attempted to advance beyond the end of tokens";
            default:
                return "Unknown error";
        }
    }
};

#endif
