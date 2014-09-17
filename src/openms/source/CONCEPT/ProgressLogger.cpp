// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2013.
//
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS.
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// --------------------------------------------------------------------------
// $Maintainer: Stephan Aiche$
// $Authors: Marc Sturm, Stephan Aiche$
// --------------------------------------------------------------------------

#include <OpenMS/CONCEPT/ProgressLogger.h>
#include <OpenMS/CONCEPT/Macros.h>
#include <OpenMS/CONCEPT/Factory.h>

#include <OpenMS/DATASTRUCTURES/String.h>

#include <OpenMS/SYSTEM/StopWatch.h>

#include <QtCore/QString>
#include <QtGui/QProgressDialog>

#include <iostream>

using namespace std;

namespace OpenMS
{
  class CMDProgressLoggerImpl :
    public ProgressLogger::ProgressLoggerImpl
  {
public:
    CMDProgressLoggerImpl() :
      stop_watch_(),
      begin_(0),
      end_(0)
    {
    }

    /// create new object (needed by Factory)
    static ProgressLogger::ProgressLoggerImpl* create()
    {
      return new CMDProgressLoggerImpl();
    }

    /// name of the model (needed by Factory)
    static const String getProductName()
    {
      return "CMD";
    }

    void startProgress(const SignedSize begin, const SignedSize end, const String& label, const int current_recursion_depth) const
    {
      begin_ = begin;
      end_ = end;
      if (current_recursion_depth) cout << '\n';
      cout << string(2 * current_recursion_depth, ' ') << "Progress of '" << label << "':" << endl;
      stop_watch_.reset();
      stop_watch_.start();
    }

    void setProgress(const SignedSize value, const int current_recursion_depth) const
    {
      if (begin_ == end_)
      {
        cout << '.' << flush;
      }
      else if (value < begin_ || value > end_)
      {
        cout << "ProgressLogger: Invalid progress value '" << value
             << "'. Should be between '" << begin_ << "' and '" << end_ << "'!" << endl;
      }
      else
      {
        cout << '\r' << string(2 * current_recursion_depth, ' ') << QString::number(float(value - begin_) / float(end_ - begin_) * 100.0, 'f', 2).toStdString()  << " %               ";
        cout << flush;
      }
    }

    void endProgress(const int current_recursion_depth) const
    {
      stop_watch_.stop();
      if (begin_ == end_)
      {
        if (current_recursion_depth)
        {
          cout << '\n';
        }
        cout << endl << string(2 * current_recursion_depth, ' ') << "-- done [took " << StopWatch::toString(stop_watch_.getCPUTime()) << " (CPU), " << StopWatch::toString(stop_watch_.getClockTime()) << " (Wall)] -- " << endl;
      }
      else
      {
        cout << '\r' << string(2 * current_recursion_depth, ' ') << "-- done [took " << StopWatch::toString(stop_watch_.getCPUTime()) << " (CPU), " << StopWatch::toString(stop_watch_.getClockTime()) << " (Wall)] -- " << endl;
      }
    }

private:
    mutable StopWatch stop_watch_;
    mutable SignedSize begin_;
    mutable SignedSize end_;
  };

  class NoProgressLoggerImpl :
    public ProgressLogger::ProgressLoggerImpl
  {
public:
    /// create new object (needed by Factory)
    static ProgressLogger::ProgressLoggerImpl* create()
    {
      return new NoProgressLoggerImpl();
    }

    /// name of the model (needed by Factory)
    static const String getProductName()
    {
      return "NONE";
    }

    void startProgress(const SignedSize /* begin */, const SignedSize /* end */, const String& /* label */, const int /* current_recursion_depth */) const
    {
    }

    void setProgress(const SignedSize /* value */, const int /* current_recursion_depth */) const
    {
    }

    void endProgress(const int /* current_recursion_depth */) const
    {
    }

  };

  class GUIProgressLoggerImpl :
    public ProgressLogger::ProgressLoggerImpl
  {
public:
    /// create new object (needed by Factory)
    static ProgressLogger::ProgressLoggerImpl* create()
    {
      return new GUIProgressLoggerImpl();
    }

    /// name of the model (needed by Factory)
    static const String getProductName()
    {
      return "GUI";
    }

    GUIProgressLoggerImpl() :
      dlg_(0),
      begin_(0),
      end_(0)
    {
    }

    void startProgress(const SignedSize begin, const SignedSize end, const String& label, const int /* current_recursion_depth */) const
    {
      begin_ = begin;
      end_ = end;
      if (!dlg_)
      {
        dlg_ = new QProgressDialog(label.c_str(), QString(), int(begin), int(end));
      }
      dlg_->setWindowTitle(label.c_str());
      dlg_->setWindowModality(Qt::WindowModal);
      dlg_->show();
    }

    void setProgress(const SignedSize value, const int /* current_recursion_depth */) const
    {
      if (value < begin_ || value > end_)
      {
        cout << "ProgressLogger: Invalid progress value '" << value << "'. Should be between '" << begin_ << "' and '" << end_ << "'!" << endl;
      }
      else
      {
        if (dlg_)
        {
          dlg_->setValue((int)value);
        }
        else
        {
          cout << "ProgressLogger warning: 'setValue' called before 'startProgress'!" << endl;
        }
      }
    }

    void endProgress(const int /* current_recursion_depth */) const
    {
      if (dlg_)
      {
        dlg_->setValue((int)end_);
      }
      else
      {
        cout << "ProgressLogger warning: 'endProgress' called before 'startProgress'!" << endl;
      }
    }

    ~GUIProgressLoggerImpl()
    {
      delete dlg_;
    }

private:
    mutable QProgressDialog* dlg_;
    mutable SignedSize begin_;
    mutable SignedSize end_;
  };

  void ProgressLogger::ProgressLoggerImpl::registerChildren()
  {
    Factory<ProgressLogger::ProgressLoggerImpl>::registerProduct(CMDProgressLoggerImpl::getProductName(), &CMDProgressLoggerImpl::create);
    Factory<ProgressLogger::ProgressLoggerImpl>::registerProduct(GUIProgressLoggerImpl::getProductName(), &GUIProgressLoggerImpl::create);
    Factory<ProgressLogger::ProgressLoggerImpl>::registerProduct(NoProgressLoggerImpl::getProductName(), &NoProgressLoggerImpl::create);
  }

  int ProgressLogger::recursion_depth_ = 0;

  const std::map<ProgressLogger::LogType, String> ProgressLogger::log_type_factory_association_ = ProgressLogger::initializeLogAssociation_();

  std::map<ProgressLogger::LogType, String> ProgressLogger::initializeLogAssociation_()
  {
    std::map<ProgressLogger::LogType, String> tmp_map;
    tmp_map[ProgressLogger::CMD] = "CMD";
    tmp_map[ProgressLogger::NONE] = "NONE";
    tmp_map[ProgressLogger::GUI] = "GUI";

    return tmp_map;
  }

  String ProgressLogger::logTypeToFactoryName(ProgressLogger::LogType type)
  {
    std::map<ProgressLogger::LogType, String>::const_iterator it = log_type_factory_association_.find(type);
    if (it != log_type_factory_association_.end())
    {
      return it->second;
    }
    else
    {
      // should never happen actually
      throw Exception::IllegalArgument(__FILE__, __LINE__, __PRETTY_FUNCTION__, "Their is associated logger for the given LogType.");
    }
  }

  ProgressLogger::ProgressLogger() :
    type_(NONE),
    last_invoke_()
  {
    current_logger_ = Factory<ProgressLogger::ProgressLoggerImpl>::create(logTypeToFactoryName(type_));
  }

  ProgressLogger::ProgressLogger(const ProgressLogger& other) :
    type_(other.type_),
    last_invoke_(other.last_invoke_)
  {
    // recreate our logger
    current_logger_ = Factory<ProgressLogger::ProgressLoggerImpl>::create(logTypeToFactoryName(type_));
  }

  ProgressLogger& ProgressLogger::operator=(const ProgressLogger& other)
  {
    if (&other == this) return *this;

    this->last_invoke_ = other.last_invoke_;
    this->type_ = other.type_;

    // we clean our old logger
    delete current_logger_;

    // .. and get a new one
    current_logger_ = Factory<ProgressLogger::ProgressLoggerImpl>::create(logTypeToFactoryName(type_));

    return *this;
  }

  ProgressLogger::~ProgressLogger()
  {
    delete current_logger_;
  }

  void ProgressLogger::setLogType(LogType type) const
  {
    type_ = type;
    // remove the old logger
    delete current_logger_;

    current_logger_ = Factory<ProgressLogger::ProgressLoggerImpl>::create(logTypeToFactoryName(type_));
  }

  ProgressLogger::LogType ProgressLogger::getLogType() const
  {
    return type_;
  }

  void ProgressLogger::startProgress(SignedSize begin, SignedSize end, const String& label) const
  {
    OPENMS_PRECONDITION(begin <= end, "ProgressLogger::init : invalid range!");
    last_invoke_ = time(NULL);
    current_logger_->startProgress(begin, end, label, recursion_depth_);
    ++recursion_depth_;
  }

  void ProgressLogger::setProgress(SignedSize value) const
  {
    // update only if at least 1 second has passed
    if (last_invoke_ == time(NULL)) return;

    last_invoke_ = time(NULL);
    current_logger_->setProgress(value, recursion_depth_);
  }

  void ProgressLogger::endProgress() const
  {
    if (recursion_depth_)
    {
      --recursion_depth_;
    }
    current_logger_->endProgress(recursion_depth_);
  }

} //namespace OpenMS
