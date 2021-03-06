/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2004, 2016
 *
 *  Bugfixes provided by:
 *     Stefano Gualandi
 *
 *  Last modified:
 *     $Date: 2016-09-22 16:19:20 +0200 (Thu, 22 Sep 2016) $ by $Author: schulte $
 *     $Revision: 15169 $
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

#include <gecode/search/sequential/lds.hh>

namespace Gecode { namespace Search { namespace Sequential {

  /*
   * The probing engine: computes all solutions with
   * exact number of discrepancies (solutions with
   * fewer discrepancies are discarded)
   *
   */
  Space*
  LDS::next(void) {
    while (true) {
      Space* s = e.next(opt);
      if (s != NULL)
        return s;
      if (((s == NULL) && e.stopped()) || (++d > opt.d_l) || e.done())
        break;
      if (d == opt.d_l) {
        if (root != NULL)
          e.reset(root,d);
        root = NULL;
      } else if (root != NULL) {
        e.reset(root->clone(),d);
      }
    }
    return NULL;
  }

  bool
  LDS::stopped(void) const {
    return e.stopped();
  }

  Statistics
  LDS::statistics(void) const {
    return e.statistics();
  }

  LDS::~LDS(void) {
    delete root;
  }

}}}

// STATISTICS: search-sequential
