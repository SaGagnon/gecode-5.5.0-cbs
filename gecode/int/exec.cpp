/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2009
 *
 *  Last modified:
 *     $Date: 2017-02-16 12:11:51 +0100 (Thu, 16 Feb 2017) $ by $Author: schulte $
 *     $Revision: 15434 $
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

#include <gecode/int/exec.hh>
#include <gecode/kernel/wait.hh>

namespace Gecode {

  void
  wait(Home home, IntVar x, std::function<void(Space& home)> c,
       IntPropLevel) {
    GECODE_POST;
    GECODE_ES_FAIL(Kernel::UnaryWait<Int::IntView>::post(home,x,c));
  }

  void
  wait(Home home, BoolVar x, std::function<void(Space& home)> c,
       IntPropLevel) {
    GECODE_POST;
    GECODE_ES_FAIL(Kernel::UnaryWait<Int::BoolView>::post(home,x,c));
  }

  void
  wait(Home home, const IntVarArgs& x, std::function<void(Space& home)> c,
       IntPropLevel) {
    GECODE_POST;
    ViewArray<Int::IntView> xv(home,x);
    GECODE_ES_FAIL(Kernel::NaryWait<Int::IntView>::post(home,xv,c));
  }

  void
  wait(Home home, const BoolVarArgs& x, std::function<void(Space& home)> c,
       IntPropLevel) {
    GECODE_POST;
    ViewArray<Int::BoolView> xv(home,x);
    GECODE_ES_FAIL(Kernel::NaryWait<Int::BoolView>::post(home,xv,c));
  }


  void
  when(Home home, BoolVar x,
       std::function<void(Space& home)> t,
       std::function<void(Space& home)> e,
       IntPropLevel) {
    GECODE_POST;
    GECODE_ES_FAIL(Int::Exec::When::post(home,x,t,e));
  }

  void
  when(Home home, BoolVar x,
       std::function<void(Space& home)> t,
       IntPropLevel) {
    when(home, x, t, [](Space&) {});
  }

}

// STATISTICS: int-post
