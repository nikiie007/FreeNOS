/**
 * Logging utilities and definitions.
 *
 * @author Niek Linnenbank
 * @date 5 march 2015
 */

#ifndef _LOG_H
#define _LOG_H

#include "Singleton.h"
#include "Macros.h"

/**
 * Output a log line to the system log (syslog).
 *
 * @param type Log level
 * @param msg Message to output
 */
#define MAKE_LOG(type, msg) \
    {\
     if (Log::instance && type <= Log::instance->getMinimumLogLevel())  \
        (*Log::instance) << "[" #type "] " << __FILE__ ":" <<  __LINE__ << " " << __FUNCTION__ << " -- " << msg << "\r\n"; \
    }

/**
 * Output a critical message and terminate program immediatly.
 * @param msg The critical message.
 */
#define FATAL(msg)   MAKE_LOG(Log::Emergency, msg)

/**
 * Output an error message.
 * @param msg The error message.
 */
#define ERROR(msg)   MAKE_LOG(Log::Error, msg)

/**
 * Output a warning message.
 * @param msg The warning message.
 */
#define WARNING(msg) MAKE_LOG(Log::Warning, msg)

/**
 * Output a notice message.
 */
#define NOTICE(msg)  MAKE_LOG(Log::Notice, msg)

/**
 * Output a regular message to standard output.
 */
#define INFO(msg)    MAKE_LOG(Log::Info, msg)

/**
 * Output a debug message to standard output.
 *
 * @param msg The message to output
 */
#define DEBUG(msg)   MAKE_LOG(Log::Debug, msg)

/**
 * Logging class.
 *
 * @note This class is a singleton
 */
class Log : public Singleton<Log>
{
  public:

    /** Logging level values */
    enum Level
    {
        Emergency,
        Alert,
        Critical,
        Error,
        Warning,
        Notice,
        Info,
        Debug
    };

    /**
     * Constructor.
     */
    Log();

    /**
     * Destructor
     */
    ~Log();

    /**
     * Get the minimum logging level.
     */
    Level getMinimumLogLevel();

    /**
     * Set the minimum logging level.
     */
    void setMinimumLogLevel(Level level);

    /**
     * Write to the actual output device.
     */
    virtual void write(const char *str) = 0;

    /**
     * Set log identity.
     */
    void setIdent(const char *ident);

    /**
     * Retrieve log identify.
     */
    const char * getIdent();

  private:
    
    /** Minimum log level required to log. */
    Level m_minimumLogLevel;

    /** Identity */
    const char *m_ident;
};

/**
 * @name Operators to output various standard types to the log
 * @{
 */

// TODO: #warning move inside the Log class plz.

Log & operator << (Log &log, const char *str);

Log & operator << (Log &log, int number);

Log & operator << (Log &log, unsigned number);

Log & operator << (Log &log, unsigned long number);

Log & operator << (Log &log, void *ptr);    

/**
 * @}
 */

#endif /* _LOG_H */
