#pragma once

#include <chrono>
#include <string>

class HMILog
{
public:
    explicit HMILog(const char *p_func) noexcept;
    ~HMILog() noexcept;

    static bool LOG_DEBUG;
    static bool LOG_ERROR;
    static bool LOG_INFO;
    static bool LOG_TRACE;
    static bool LOG_WARNING;

    /**
     * @brief Debug level log functions
     */
    void debug(const char *p_text) const;
    void debug(const char *p_name, int p_value) const;
    void debug(const char *p_name, double p_value) const;
    void debug(const char *p_name, const char *p_value) const;

    /**
     * @brief Info level log functions
     */
    void info(const char *p_text) const;
    void info(const char *p_name, int p_value) const;
    void info(const char *p_name, double p_value) const;
    void info(const char *p_name, const char *p_value) const;

    /**
     * @brief Warning level log functions
     */
    void warning(const char *p_text) const;
    void warning(const char *p_name, int p_value) const;
    void warning(const char *p_name, double p_value) const;
    void warning(const char *p_name, const char *p_value) const;

    /**
     * @brief Error level log functions
     */
    void error(const char *p_text) const;
    void error(const char *p_name, int p_value) const;
    void error(const char *p_name, double p_value) const;
    void error(const char *p_name, const char *p_value) const;

private:
    /**
     * @brief Get ellapsed time in seconds since enter function / start service
     */
    double ellapsed_since_enter() const;
    double ellapsed_since_start() const;

    /**
     * @brief Get current system time as formatted string
     */
    std::string now() const;

    /**
     * @brief Function name
     * HMILog will not retain ownership of the pointer
     */
    const char *m_func;

    /**
     * @brief Function enter time
     */
    std::chrono::steady_clock::time_point m_enter = std::chrono::steady_clock::now();

    /**
     * @brief Service start-up time
     */
    static std::chrono::steady_clock::time_point START;
};
