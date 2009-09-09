/*********************************************************************
* Software License Agreement (BSD License)
* 
*  Copyright (c) 2007. MBARI.
*  All rights reserved.
* 
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
* 
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the TREX Project nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * @author Conor McGann
 * @brief Defines a performance monitor interface for use by the agent
 */
#include <vector>

namespace TREX {

  class PerformanceMonitor {
  public:
    virtual ~PerformanceMonitor(){}

    virtual void addTickData(const timeval& synchTime, const timeval& deliberationTime){
      m_tickData.push_back(std::pair<timeval, timeval>(synchTime, deliberationTime));
    }

    static PerformanceMonitor& defaultMonitor(){
      static PerformanceMonitor sl_instance;
      return sl_instance;
    }

    const std::vector< std::pair<timeval, timeval> >& getData() const {return m_tickData;}

  protected:
    std::vector< std::pair<timeval, timeval> > m_tickData;
  };


  class StatisticsCollector: public PerformanceMonitor {
  public:
    void addTickData(const timeval& synchTime, const timeval& deliberationTime){
      m_tickData.push_back(std::pair<timeval, timeval>(synchTime, deliberationTime));
    }
  };
}
