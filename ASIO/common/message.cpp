#include "message.h"

#include <cstring>

Message::Message()
{
    m_data.resize(HEADER_LENGTH);
}

const char* Message::data() const
{
    return m_data.data();
}

char* Message::data()
{
    return &m_data[0];
}

std::size_t Message::length() const
{
    return m_data.length();
}

const char* Message::body() const
{
    return data() + HEADER_LENGTH;
}

char* Message::body()
{
    return data() +  HEADER_LENGTH;
}

std::size_t Message::bodyLength() const
{
    return m_data.length() - HEADER_LENGTH;
}

void Message::setBodyLength(std::uint32_t newLength)
{
    m_data.resize(HEADER_LENGTH + newLength);
}

void Message::setBody(const std::string& bodyString)
{
    setBodyLength(bodyString.length());
    std::memcpy(body(), bodyString.data(), bodyLength());
    encodeHeader();
}

void Message::decodeHeader()
{
    uint32_t len;
    std::memcpy(&len, static_cast<const void*>(m_data.data()), HEADER_LENGTH);
    setBodyLength(len);
}

void Message::encodeHeader()
{
    uint32_t len = bodyLength();
    std::memcpy(data(), reinterpret_cast<char*>(&len), HEADER_LENGTH);
}
