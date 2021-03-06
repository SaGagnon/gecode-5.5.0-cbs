/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2017
 *
 *  Last modified:
 *     $Date: 2017-03-17 23:04:57 +0100 (Fri, 17 Mar 2017) $ by $Author: schulte $
 *     $Revision: 15597 $
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <gecode/kernel.hh>

namespace Gecode {

  Propagator*
  TraceRecorder::copy(Space& home, bool share) {
    return new (home) TraceRecorder(home, share, *this);
  }

  size_t
  TraceRecorder::dispose(Space& home) {
    home.ignore(*this, AP_DISPOSE);
    home.ignore(*this, AP_TRACE);
    tf.~TraceFilter();
    (void) Propagator::dispose(home);
    return sizeof(*this);
  }

  PropCost
  TraceRecorder::cost(const Space&, const ModEventDelta&) const {
    return PropCost::record();
  }

  void
  TraceRecorder::reschedule(Space&) {
  }

  ExecStatus
  TraceRecorder::propagate(Space&, const ModEventDelta&) {
    return ES_FIX;
  }

}

// STATISTICS: kernel-trace
