#include "HMILog.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

#define ANSI_RESET      "\x1b[0m"

#define ANSI_BOLD_ON    "\x1b[1m"
#define ANSI_BOLD_OFF   "\x1b[21m"
#define ANSI_UNDER_ON   "\x1b[4m"
#define ANSI_UNDER_OFF  "\x1b[24m"
#define ANSI_BLINK_ON   "\x1b[5m"
#define ANSI_BLINK_OFF  "\x1b[25m"

#define ANSI_FG_RED     "\x1b[31m"
#define ANSI_FG_GREEN   "\x1b[32m"
#define ANSI_FG_YELLOW  "\x1b[33m"
#define ANSI_FG_BLUE    "\x1b[34m"
#define ANSI_FG_MAGENTA "\x1b[35m"
#define ANSI_FG_CYAN    "\x1b[36m"

#define ANSI_FG_LIGHT_GRAY  "\x1b[90m"
#define ANSI_FG_LIGHT_CYAN  "\x1b[96m"
#define ANSI_FG_DARK_RED    "\x1b[0;31m"
#define ANSI_FG_DARK_YELLOW "\x1b[0;33m"

#define ANSI_BG_RED     "\x1b[41m"
#define ANSI_BG_GREEN   "\x1b[42m"
#define ANSI_BG_YELLOW  "\x1b[43m"
#define ANSI_BG_BLUE    "\x1b[44m"
#define ANSI_BG_MAGENTA "\x1b[45m"
#define ANSI_BG_CYAN    "\x1b[46m"
#define ANSI_BG_WHITE   "\x1b[46m"
#define ANSI_BG_GREY    "\x1b[100m"

#ifdef DEBUG
bool HMILog::LOG_DEBUG = true;
bool HMILog::LOG_ERROR = true;
bool HMILog::LOG_INFO = true;
bool HMILog::LOG_TRACE = true;
bool HMILog::LOG_WARNING = true;
#else
bool HMILog::LOG_DEBUG = false;
bool HMILog::LOG_ERROR = true;
bool HMILog::LOG_INFO = true;
bool HMILog::LOG_TRACE = false;
bool HMILog::LOG_WARNING = true;
#endif

std::chrono::steady_clock::time_point HMILog::START = std::chrono::steady_clock::now();

HMILog::HMILog(const char *p_func) noexcept : m_func(p_func)
{
    if (LOG_TRACE) printf(ANSI_RESET "##hmi## >> %s, at %s (%.2f sec after start-up)\n", m_func, now().c_str(), ellapsed_since_start());
}

HMILog::~HMILog() noexcept
{
    if (LOG_TRACE) printf(ANSI_RESET "##hmi## << %s, at %s (%.2f sec after start-up, %f sec after entering)\n", m_func, now().c_str(), ellapsed_since_start(), ellapsed_since_enter());
}

void HMILog::debug(const char *p_text) const
{
    if (LOG_DEBUG) printf(ANSI_RESET "##hmi##" ANSI_BOLD_ON "%s" ANSI_BOLD_OFF "## %s\n", m_func, p_text);
}

void HMILog::debug(const char *p_name, int p_value) const
{
    if (LOG_DEBUG) printf(ANSI_RESET "##hmi##" ANSI_BOLD_ON "%s" ANSI_BOLD_OFF "## %s: %d\n", m_func, p_name, p_value);
}

void HMILog::debug(const char *p_name, double p_value) const
{
    if (LOG_DEBUG) printf(ANSI_RESET "##hmi##" ANSI_BOLD_ON "%s" ANSI_BOLD_OFF "## %s: %f\n", m_func, p_name, p_value);
}

void HMILog::debug(const char *p_name, const char *p_value) const
{
    if (LOG_DEBUG) printf(ANSI_RESET "##hmi##" ANSI_BOLD_ON "%s" ANSI_BOLD_OFF "## %s: %s\n", m_func, p_name, p_value);
}

void HMILog::info(const char *p_text) const
{
    if (LOG_INFO) printf(ANSI_FG_LIGHT_CYAN "##hmi##" ANSI_BOLD_ON "%s" ANSI_BOLD_OFF "## %s\n" ANSI_RESET, m_func, p_text);
}

void HMILog::info(const char *p_name, int p_value) const
{
    if (LOG_INFO) printf(ANSI_FG_LIGHT_CYAN "##hmi##" ANSI_BOLD_ON "%s" ANSI_BOLD_OFF "## %s: %d\n" ANSI_RESET, m_func, p_name, p_value);
}

void HMILog::info(const char *p_name, double p_value) const
{
    if (LOG_INFO) printf(ANSI_FG_LIGHT_CYAN "##hmi##" ANSI_BOLD_ON "%s" ANSI_BOLD_OFF "## %s: %f\n" ANSI_RESET, m_func, p_name, p_value);
}

void HMILog::info(const char *p_name, const char *p_value) const
{
    if (LOG_INFO) printf(ANSI_FG_LIGHT_CYAN "##hmi##" ANSI_BOLD_ON "%s" ANSI_BOLD_OFF "## %s: %s\n" ANSI_RESET, m_func, p_name, p_value);
}

void HMILog::warning(const char *p_text) const
{
    if (LOG_WARNING) printf(ANSI_FG_DARK_YELLOW "##hmi##" ANSI_BOLD_ON "%s" ANSI_BOLD_OFF "## %s\n" ANSI_RESET, m_func, p_text);
}

void HMILog::warning(const char *p_name, int p_value) const
{
    if (LOG_WARNING) printf(ANSI_FG_DARK_YELLOW "##hmi##" ANSI_BOLD_ON "%s" ANSI_BOLD_OFF "## %s: %d\n" ANSI_RESET, m_func, p_name, p_value);
}

void HMILog::warning(const char *p_name, double p_value) const
{
    if (LOG_WARNING) printf(ANSI_FG_DARK_YELLOW "##hmi##" ANSI_BOLD_ON "%s" ANSI_BOLD_OFF "## %s: %f\n" ANSI_RESET, m_func, p_name, p_value);
}

void HMILog::warning(const char *p_name, const char *p_value) const
{
    if (LOG_WARNING) printf(ANSI_FG_DARK_YELLOW "##hmi##" ANSI_BOLD_ON "%s" ANSI_BOLD_OFF "## %s: %s\n" ANSI_RESET, m_func, p_name, p_value);
}

void HMILog::error(const char *p_text) const
{
    if (LOG_ERROR) printf(ANSI_FG_RED "##hmi##" ANSI_BOLD_ON "%s" ANSI_BOLD_OFF "## %s\n" ANSI_RESET, m_func, p_text);
}

void HMILog::error(const char *p_name, int p_value) const
{
    if (LOG_ERROR) printf(ANSI_FG_RED "##hmi##" ANSI_BOLD_ON "%s" ANSI_BOLD_OFF "## %s: %d\n" ANSI_RESET, m_func, p_name, p_value);
}

void HMILog::error(const char *p_name, double p_value) const
{
    if (LOG_ERROR) printf(ANSI_FG_RED "##hmi##" ANSI_BOLD_ON "%s" ANSI_BOLD_OFF "## %s: %f\n" ANSI_RESET, m_func, p_name, p_value);
}

void HMILog::error(const char *p_name, const char *p_value) const
{
    if (LOG_ERROR) printf(ANSI_FG_RED "##hmi##" ANSI_BOLD_ON "%s" ANSI_BOLD_OFF "## %s: %s\n" ANSI_RESET, m_func, p_name, p_value);
}

double HMILog::ellapsed_since_enter() const
{
    using namespace std::chrono;

    return duration_cast<duration<double, std::milli>>(steady_clock::now() - m_enter).count() * 0.001;
}

double HMILog::ellapsed_since_start() const
{
    using namespace std::chrono;

    return duration_cast<duration<double, std::milli>>(steady_clock::now() - START).count() * 0.001;
}

std::string HMILog::now() const
{
    time_t rawtime = time(nullptr);

    char buffer[80];
    strftime(buffer, 80, "%c", localtime(&rawtime));

    return buffer;
}
