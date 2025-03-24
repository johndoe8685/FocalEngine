#include "debugger.h"

namespace NixTools
{
    Debugger::Debugger(std::string componentName, std::string className)
    {
        m_componentName = componentName;
        m_className = className;
    }

    Debugger::Debugger(std::string className)
        :m_componentName("Unknown"), m_className(className)
    {
    }

    void Debugger::giveMessage(DebugLevel level, std::string message)
    {
        if (message != m_previousMessage)
        {
            m_previousMessage = message;
            switch (level)
            {
            case Info:
                std::cout << "[INFO]  " << "[" << m_componentName << "::" << m_className << "] " << "[" << m_className << "> " << message << std::endl;
                break;
            case Warning:
                std::cout << "[WARN]  " << "[" << m_componentName << "::" << m_className << "] " << "[" << m_className << "> " << message << std::endl;
                break;
            case Error:
                std::cout << "[ERROR] " << "[" << m_componentName << "::" << m_className << "] " << "[" << m_className << "> " << message << std::endl;
                break;
            case Unknown:
                std::cout << "[UNKWN] " << "[" << m_componentName << "::" << m_className << "] " << "[" << m_className << "> " << message << std::endl;
                break;
            default:
                break;
            }
        }
    }

    void Debugger::giveMessage(DebugLevel level, std::string title, std::string message)
    {
        if (message != m_previousMessage)
        {
            m_previousMessage = message;
            switch (level)
            {
            case Info:
                std::cout << "[INFO]  " << "[" << m_componentName << "::" << m_className << "] " << "[" << title << "> " << message << std::endl;
                break;
            case Warning:
                std::cout << "[WARN]  " << "[" << m_componentName << "::" << m_className << "] " << "[" << title << "> " << message << std::endl;
                break;
            case Error:
                std::cout << "[ERROR] " << "[" << m_componentName << "::" << m_className << "] " << "[" << title << "> " << message << std::endl;
                break;
            case Unknown:
                std::cout << "[UNKWN] " << "[" << m_componentName << "::" << m_className << "] " << "[" << title << "> " << message << std::endl;
                break;
            default:
                break;
            }
        }
    }

    void Debugger::giveMessage(DebugLevel level, std::string message, int value)
    {
        if (value != m_previousValueInt)
        {
            m_previousValueInt = value;
            switch (level)
            {
            case Info:
                std::cout << "[INFO]  " << "[" << m_componentName << "::" << m_className << "] " << "[" << message << "> " << value << std::endl;
                break;
            case Warning:
                std::cout << "[WARN]  " << "[" << m_componentName << "::" << m_className << "] " << "[" << message << "> " << value << std::endl;
                break;
            case Error:
                std::cout << "[ERROR] " << "[" << m_componentName << "::" << m_className << "] " << "[" << message << "> " << value << std::endl;
                break;
            case Unknown:
                std::cout << "[UNKWN] " << "[" << m_componentName << "::" << m_className << "] " << "[" << message << "> " << value << std::endl;
                break;
            default:
                break;
            }
        }
    }

    void Debugger::giveMessage(DebugLevel level, std::string message, float value)
    {
        if (value != m_previousValueFloat)
        {
            m_previousValueFloat = value;
            switch (level)
            {
            case Info:
                std::cout << "[INFO]  " << "[" << m_componentName << "::" << m_className << "] " << "[" << message << "> " << value << std::endl;
                break;
            case Warning:
                std::cout << "[WARN]  " << "[" << m_componentName << "::" << m_className << "] " << "[" << message << "> " << value << std::endl;
                break;
            case Error:
                std::cout << "[ERROR] " << "[" << m_componentName << "::" << m_className << "] " << "[" << message << "> " << value << std::endl;
                break;
            case Unknown:
                std::cout << "[UNKWN] " << "[" << m_componentName << "::" << m_className << "] " << "[" << message << "> " << value << std::endl;
                break;
            default:
                break;
            }
        }
    }

    template<typename T>
    void Debugger::giveMessage(DebugLevel level, std::string message, T value)
    {
        switch (level)
        {
        case Info:
            std::cout << "[INFO]  " << "[" << m_componentName << "::" << m_className << "] " << "[" << message << "> " << value << std::endl;
            break;
        case Warning:
            std::cout << "[WARN]  " << "[" << m_componentName << "::" << m_className << "] " << "[" << message << "> " << value << std::endl;
            break;
        case Error:
            std::cout << "[ERROR] " << "[" << m_componentName << "::" << m_className << "] " << "[" << message << "> " << value << std::endl;
            break;
        case Unknown:
            std::cout << "[UNKWN] " << "[" << m_componentName << "::" << m_className << "] " << "[" << message << "> " << value << std::endl;
            break;
        default:
            break;
        }
    }

    void Debugger::giveMessage(DebugLevel level, std::string message, unsigned int value)
    {
        if (value != m_previousValueUInt)
        {
            m_previousValueUInt = value;
            switch (level)
            {
            case Info:
                std::cout << "[INFO]  " << "[" << m_componentName << "::" << m_className << "] " << "[" << message << "> " << value << std::endl;
                break;
            case Warning:
                std::cout << "[WARN]  " << "[" << m_componentName << "::" << m_className << "] " << "[" << message << "> " << value << std::endl;
                break;
            case Error:
                std::cout << "[ERROR] " << "[" << m_componentName << "::" << m_className << "] " << "[" << message << "> " << value << std::endl;
                break;
            case Unknown:
                std::cout << "[UNKWN] " << "[" << m_componentName << "::" << m_className << "] " << "[" << message << "> " << value << std::endl;
                break;
            default:
                break;
            }
        }
    }
}
