#ifndef JAVEIN_ERRORS_HPP
#define JAVEIN_ERRORS_HPP

#include <iostream>

using namespace std;

enum class ErrorCode
{
    // LEXER

    INVALID_NUMBER,
    UNEXPECTED_END_INPUT,
    UNTERMINATED_CHAR,
    UNTERMINATED_STRING,

    // PARSER

    UNEXPECTED_END,
    UNEXPECTED_END_IN_BLOCK,
    UNEPECTED_END_LOGICAL_OP,
    EXPECTED_OPEN_BRACK,
    EXPECTED_CLOSE_BRACK,
    EXPECTED_OPEN_PARENT,
    EXPECTED_CLOSE_PARENT,
    EXPECTED_ID,
    EXPECTED_ASSIGN,
    EXPECTED_KEY,
    EXPECTED_RETURN_TYPE,
    EXPECTED_RETURN_VALUE,
    EXPECTED_DEFAULT_VALUE,
    INVALID_TOKEN,
    INVALID_PARAM_TYPE,
    INVALID_TYPE,
    INVALID_VALUE,
    INVALID_OP,
    MISSING_SEMICOLUMN,
    ATTEMPT_TO_ADVANCE_BEYOND_END,
};

class Error
{
public:
    static void throwError(ErrorCode code, const string &blockType = "")
    {
        printError(code, blockType);
        exit(static_cast<int>(code));
    }

private:
    static void printError(ErrorCode errorCode, const string &blockType)
    {
        cerr << "Error (" << static_cast<int>(errorCode) << "): " << getErrorMessage(errorCode, blockType) << endl;
    }

    static string getErrorMessage(ErrorCode errorCode, const string &blockType)
    {
        switch (errorCode) {
            case ErrorCode::INVALID_NUMBER:
                return "Invalid number";
            case ErrorCode::UNEXPECTED_END_INPUT:
                return "Unexpected end of input";
            case ErrorCode::UNTERMINATED_CHAR:
                return "Unterminated char literal";
            case ErrorCode::UNTERMINATED_STRING:
                return "Unterminated string literal";
            case ErrorCode::UNEXPECTED_END:
                return "Unexpected end of tokens";
            case ErrorCode::UNEXPECTED_END_IN_BLOCK:
                return "Unexpected end of tokens inside " + blockType + " statement";
            case ErrorCode::UNEPECTED_END_LOGICAL_OP:
                return "Unexpected end of tokens after logical operator";
            case ErrorCode::EXPECTED_OPEN_BRACK:
                return "Expected '{' after statement";
            case ErrorCode::EXPECTED_CLOSE_BRACK:
                return "Expected '}' after statement";
            case ErrorCode::EXPECTED_OPEN_PARENT:
                return "Expected '(' after statement";
            case ErrorCode::EXPECTED_CLOSE_PARENT:
                return "Expected ')' after statement";
            case ErrorCode::EXPECTED_ID:
                return "Expected identifier after statement";
            case ErrorCode::EXPECTED_ASSIGN:
                return "Expected '=' after statement";
            case ErrorCode::EXPECTED_KEY:
                return "Expected " + blockType + " statement";
            case ErrorCode::EXPECTED_RETURN_TYPE:
                return "Expected return type after statement";
            case ErrorCode::EXPECTED_RETURN_VALUE:
                return "Expected return value after statement";
            case ErrorCode::EXPECTED_DEFAULT_VALUE:
                return "Expected default parameter value";
            case ErrorCode::INVALID_TOKEN:
                return "Invalid token encountered";
            case ErrorCode::INVALID_PARAM_TYPE:
                return "Expected parameter type";
            case ErrorCode::INVALID_TYPE:
                return "Invalid type";
            case ErrorCode::INVALID_VALUE:
                return "Invalid value";
            case ErrorCode::INVALID_OP:
                return "Invalid operator";
            case ErrorCode::MISSING_SEMICOLUMN:
                return "Missing ';' after statement";
            case ErrorCode::ATTEMPT_TO_ADVANCE_BEYOND_END:
                return "Attempted to advance beyond the end of tokens";
            default:
                return "Unknown error";
        }
    }
};

#endif
