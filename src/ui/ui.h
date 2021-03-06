#ifndef FEUP_AEDA_PROJECT_UI_H
#define FEUP_AEDA_PROJECT_UI_H

#include "model/store/store.h"
#include "util/util.h"

using namespace util;

/**
 * Interface from which all UI pages derive.
 */
class UI {
public:
    /**
     * Construct UI with the store to show
     * @param store to be shown and manipulated
     */
    explicit UI(Store& store);

    /**
     * Show page contents and handle user input commands
     */
    virtual void show() = 0;

protected:
    /**
     * Command handler. Loops while string received is empty.
     * @param lowCase - whether the received string should be lowercased.
     * @return string received, with redundant spaces removed
     */
    static std::string readCommand(bool lowCase = true);

    /**
     * Whether the input is one word, equal to cmd
     * @param input to be tested
     * @param cmd to be compared to
     * @return the validity of the input
     */
    static bool validInput1Cmd(const std::string& input, const std::string &cmd);

    /**
     * Whether the input is two words, the first one being cmd and the second one a valid digit
     * @param input to be tested
     * @param cmd to compare first word to
     * @param acceptFloat whether to accept pointing float as the second input word
     * @return the validity of the input
     */
    static bool validInput1Cmd1ArgDigit(const std::string& input, const std::string &cmd, bool acceptFloat = false);

    /**
     * Whether the input is two words, the first one being cmd and the second arg
     * @param input to be tested
     * @param cmd to compare first word two
     * @param arg to compare second word to
     * @return the validity of the input
     */
    static bool validInput1Cmd1Arg(const std::string& input, const std::string &cmd, const std::string &arg);

    /**
     * Whether the input is three words, the first being cmd and the second and third valid digits
     * @param input to be tested
     * @param cmd to compare first two
     * @param acceptFloatArg2 whether to allow pointing float as the third word
     * @return the validity of the input
     */
    static bool validInput1Cmd2ArgsDigit(const std::string& input, const std::string &cmd, bool acceptFloatArg2 = false);

    /**
     * Print the message, followed by the list of commands, one by line starting with an arrow
     * @param options vector with strings containing the commands user has at his disposition
     * @param message to display before the list of available commands
     */
    static void printOptions(const std::vector<std::string>& options,
                             const std::string& message = "Available commands:");

    /**
     * Print "Unrecognized command. Try again: "
     */
    static void printError();

    /**
     * Print at blue uppercase letters the store name, followed by hyphen and detail
     * @param detail the string to be displayed in front of the store name
     */
    virtual void printLogo(const std::string& detail) const;

    /**
     * UI reserved keyword to go back at each screen
     */
    static const char* BACK;

    /**
     * UI reserved keyword to exit in the first page
     */
    static const char* EXIT;

    /**
     * The store which data gets accessed and manipulated
     */
    Store& _store;
};

#endif //FEUP_AEDA_PROJECT_UI_H
