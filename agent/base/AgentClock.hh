#ifndef H_AgentClock
#define H_AgentClock

#include "TREXDefs.hh"
#include "TeleoReactor.hh"
#include "RStat.hh"
#include <sys/time.h>
#include "Mutex.hh"

/**
 * @brief Declaration of clock interface and implementation sub-classes
 */


namespace TREX {

  /**
   * @brief Abstract class to plug in different clocks
   */
  class Clock {
  public:
    virtual ~Clock(){}


    void doStart();


    virtual TICK getNextTick() = 0;

    /**
     * @brief Accessor for seconds per tick
     */
    virtual double getSecondsPerTick() const {return 1.0;}

    /**
     * @brief Helper method to provide a high-resolution sleep method
     * @see sleep(sleepDuration)
     */
    void sleep() const;

    /**
     * @brief Utility to implement high-resolution sleep
     * @param sleepDuration The sleep duration in seconds. Accurate up to nanoseconds.
     */
    static void sleep(double sleepDuration);

    bool debugStats() const {
      return m_processStats;
    }
    
    /** @brief Global process statistics.
     *
     * @return the stats collected for the whole duration of the process.
     */
    RStat const &totalStat() const {
      return m_cur;
    }
    /** @brief Last tick process statistics.
     *
     * @return the stats of the process during the lasst tick.
     */
    RStat const &lastTickStat() const {
      return m_diff;
    }

  protected:
    virtual double getSleepDelay() const {
      return m_sleepSeconds;
    }
    /**
     * @brief Constructor
     * @param sleepSeconds The number of seconds to sleep within the control loop before checking for work to do or clock updates
     */
    Clock(double sleepSeconds, bool stats = true)
      : m_sleepSeconds(sleepSeconds), m_processStats(stats){}

    const double m_sleepSeconds;

    /**
     * @brief Called to start the clock counting
     */
    virtual void start(){}

    /** @brief Advance tick and update the stats.
     *
     * @param tick The main tick for clock
     *
     * Increment @e tick and update the process statisitcs for the last tick.
     *
     * @note This function has to be used only for the main clock tick.
     */
    void advanceTick(TICK &tick); 
    
  private:
    bool m_processStats;
    RStat m_diff, m_cur;
  };

  /**
   * @brief Simple clock for stepping the code on the main thread
   */
  class PseudoClock: public Clock {
  public:
    PseudoClock(double sleepSeconds, unsigned int stepsPerTick, bool stats = true);

    TICK getNextTick();

  private:
    static TICK selectStep(unsigned int stepsPerTick);

    TICK m_tick;
    TICK m_internalTicks;
    const TICK m_stepsPerTick;
  };

  /**
   * @brief A clock that monitors time on a separate thread and generates updates to the tick.
   */
  class RealTimeClock: public Clock {
  public:
    RealTimeClock(double secondsPerTick, bool stats = true);

    /**
     * @brief Will idle till this is called.
     */
    void start();

    /**
     * @brief Retrieve the tick
     */
    TICK getNextTick();

  protected:
    double getSleepDelay() const;
    virtual double getSecondsPerTick() const ;

  private:
    static void getDate(timeval &val);
    void setNextTickDate(unsigned factor=1);
    double timeLeft() const;

    bool m_started;
    TICK m_tick;
    double m_floatTick;
    timeval m_secondsPerTick;
    timeval m_nextTickDate;
    mutable Mutex m_lock;

  };
    
}

#endif
