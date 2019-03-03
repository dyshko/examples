#pragma once

#include <string>

/**
 * @brief The Message class is a basic
 * message representation consisting
 * of a header containing the body size
 * and the actual body of the message:
 * [--message--] = [--header--][--body--]
 */
class Message
{
public:

    Message();
    virtual ~Message() = default;

    /**
     * @brief setBody set the body from the string
     * @param bodyString
     */
    void setBody(const std::string& bodyString);

    /**
     * @brief data
     * @return const pointer to the data of the message
     */
    const char* data() const;

    /**
     * @brief data
     * @return non-const pointer to the data of the message
     */
    char* data();

    /**
     * @brief length
     * @return length of the whole message
     */
    std::size_t length() const;

    /**
     * @brief body
     * @return const pointer to the body
     */
    const char* body() const;

    /**
     * @brief body
     * @return non-const pointer to the body
     */
    char* body();

    /**
     * @brief bodyLength
     * @return length of the body
     */
    std::size_t bodyLength() const;

    /**
     * @brief decodeHeader decodes and stores the length of the
     * body from the header
     * @note for simplicity, endnians are ignored
     */
    void decodeHeader();

    /**
     * @brief encodeHeader encodes the body length
     * to the header
     * @note for simplicity, endnians are ignored
     */
    void encodeHeader();

    /**
     * @brief HEADER_LENGTH - header length - up to 32 bit messages length
     */
    static constexpr size_t HEADER_LENGTH = 4;

private:

    /**
     * @brief setBodyLength sets new body length
     * @param newLength
     */
    void setBodyLength(std::uint32_t newLength);

    /**
     * @brief m_data the message data storage
     */
    std::string m_data;
};
