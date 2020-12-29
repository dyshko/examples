#pragma once

#include <iostream>
#include <functional>

namespace RPS {

/**
 * @brief The StreamEntity class a base class for all text based views
 * basically holds the streams members and implements some read from stream functionality
 */
class StreamEntity
{
public:

    /**
     * @brief StreamEntity
     * @param istream input text stream
     * @param ostream out text stream
     */
    StreamEntity(std::istream& istream,
                 std::ostream& ostream);

    /**
     * @brief inputStream getter for the input stream
     * @return
     */
    std::istream& inputStream();

    /**
     * @brief outStream getter for the output stream
     * @return
     */
    std::ostream& outStream();


    template<typename T>
    /**
     * @brief readValueHelper reads a value of the type T from stream displaying the textual prompt
     * Repeats until a valid value of type T is provided
     * @param message - a message to be displayed (like "please enter a number...")
     * @return a valid value of type T
     */
    T readValueHelper(const std::string& message) {
        T value;
        while (true) {
            m_ostream << message;
            m_istream >> value;
            m_ostream << std::endl;
            if (m_istream.fail()){
                m_istream.clear();
                m_istream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else {
                break;
            }
        }
        return value;
    }

    template<typename T>
    /**
     * @brief readConditionedValueHelper reads a value of the type T from stream displaying the textual prompt
     * Repeats until a valid value of type T is provided (that satisfies a condition)
     * @param message same as in @ref readValueHelper
     * @param condition a function predicate for the proper condition on the input. True = valid value.
     * @return a valid value of type T
     */
    T readConditionedValueHelper(const std::string& message, std::function<bool(T)> condition) {
        T result;
        do {
            result = readValueHelper<T>(message);
        } while (!condition(result));
        return result;
    }

private:
    std::istream& m_istream;
    std::ostream& m_ostream;
};

}
