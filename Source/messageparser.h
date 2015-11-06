#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

/**
 * @brief The MessageParser class
 * Factory class
 * Take the buffer and length, decode if and parse to certain object type
 */

#include <QImage>

class MessageParser
{
public:
    MessageParser();
    ~MessageParser();

    static void parseMessage(unsigned int size, unsigned char* buffer, unsigned char &output_type, unsigned char &output_value, QImage& output);
};

#endif // MESSAGEPARSER_H
