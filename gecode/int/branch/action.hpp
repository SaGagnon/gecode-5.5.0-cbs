/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2012
 *
 *  Last modified:
 *     $Date: 2017-02-22 04:53:03 +0100 (Wed, 22 Feb 2017) $ by $Author: schulte $
 *     $Revision: 15469 $
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

namespace Gecode {

  forceinline
  IntAction::IntAction(void) {}

  forceinline
  IntAction::IntAction(const IntAction& a)
    : Action(a) {}

  forceinline IntAction&
  IntAction::operator =(const IntAction& a) {
    return static_cast<IntAction&>(Action::operator =(a));
  }


  forceinline
  BoolAction::BoolAction(void) {}

  forceinline
  BoolAction::BoolAction(const BoolAction& a)
    : Action(a) {}

  forceinline BoolAction&
  BoolAction::operator =(const BoolAction& a) {
    return static_cast<BoolAction&>(Action::operator =(a));
  }

}

// STATISTICS: int-branch