/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2012
 *
 *  Last modified:
 *     $Date: 2017-02-28 08:29:39 +0100 (Tue, 28 Feb 2017) $ by $Author: schulte $
 *     $Revision: 15527 $
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

#include <gecode/float/branch.hh>

namespace Gecode { namespace Float { namespace Branch {

  ViewSel<FloatView>*
  viewsel(Space& home, const FloatVarBranch& fvb) {
    switch (fvb.select()) {
    case FloatVarBranch::SEL_NONE:
      return new (home) ViewSelNone<FloatView>(home,fvb);
    case FloatVarBranch::SEL_RND:
      return new (home) ViewSelRnd<FloatView>(home,fvb);
    default: break;
    }
    if (fvb.tbl() != NULL) {
      switch (fvb.select()) {
      case FloatVarBranch::SEL_MERIT_MIN:
        return new (home) ViewSelMinTbl<MeritFunction<FloatView>>(home,fvb);
      case FloatVarBranch::SEL_MERIT_MAX:
        return new (home) ViewSelMaxTbl<MeritFunction<FloatView>>(home,fvb);
      case FloatVarBranch::SEL_MIN_MIN:
        return new (home) ViewSelMinTbl<MeritMin>(home,fvb);
      case FloatVarBranch::SEL_MIN_MAX:
        return new (home) ViewSelMaxTbl<MeritMin>(home,fvb);
      case FloatVarBranch::SEL_MAX_MIN:
        return new (home) ViewSelMinTbl<MeritMax>(home,fvb);
      case FloatVarBranch::SEL_MAX_MAX:
        return new (home) ViewSelMaxTbl<MeritMax>(home,fvb);
      case FloatVarBranch::SEL_SIZE_MIN:
        return new (home) ViewSelMinTbl<MeritSize>(home,fvb);
      case FloatVarBranch::SEL_SIZE_MAX:
        return new (home) ViewSelMaxTbl<MeritSize>(home,fvb);
      case FloatVarBranch::SEL_DEGREE_MIN:
        return new (home) ViewSelMinTbl<MeritDegree<FloatView>>(home,fvb);
      case FloatVarBranch::SEL_DEGREE_MAX:
        return new (home) ViewSelMaxTbl<MeritDegree<FloatView>>(home,fvb);
      case FloatVarBranch::SEL_AFC_MIN:
        return new (home) ViewSelMinTbl<MeritAFC<FloatView>>(home,fvb);
      case FloatVarBranch::SEL_AFC_MAX:
        return new (home) ViewSelMaxTbl<MeritAFC<FloatView>>(home,fvb);
      case FloatVarBranch::SEL_ACTION_MIN:
        return new (home) ViewSelMinTbl<MeritAction<FloatView>>(home,fvb);
      case FloatVarBranch::SEL_ACTION_MAX:
        return new (home) ViewSelMaxTbl<MeritAction<FloatView>>(home,fvb);
      case FloatVarBranch::SEL_CHB_MIN:
        return new (home) ViewSelMinTbl<MeritCHB<FloatView>>(home,fvb);
      case FloatVarBranch::SEL_CHB_MAX:
        return new (home) ViewSelMaxTbl<MeritCHB<FloatView>>(home,fvb);
      case FloatVarBranch::SEL_DEGREE_SIZE_MIN:
        return new (home) ViewSelMinTbl<MeritDegreeSize>(home,fvb);
      case FloatVarBranch::SEL_DEGREE_SIZE_MAX:
        return new (home) ViewSelMaxTbl<MeritDegreeSize>(home,fvb);
      case FloatVarBranch::SEL_AFC_SIZE_MIN:
        return new (home) ViewSelMinTbl<MeritAFCSize>(home,fvb);
      case FloatVarBranch::SEL_AFC_SIZE_MAX:
        return new (home) ViewSelMaxTbl<MeritAFCSize>(home,fvb);
      case FloatVarBranch::SEL_ACTION_SIZE_MIN:
        return new (home) ViewSelMinTbl<MeritActionSize>(home,fvb);
      case FloatVarBranch::SEL_ACTION_SIZE_MAX:
        return new (home) ViewSelMaxTbl<MeritActionSize>(home,fvb);
      case FloatVarBranch::SEL_CHB_SIZE_MIN:
        return new (home) ViewSelMinTbl<MeritCHBSize>(home,fvb);
      case FloatVarBranch::SEL_CHB_SIZE_MAX:
        return new (home) ViewSelMaxTbl<MeritCHBSize>(home,fvb);
      default:
        throw UnknownBranching("Float::branch");
      }
    } else {
      switch (fvb.select()) {
      case FloatVarBranch::SEL_MERIT_MIN:
        return new (home) ViewSelMin<MeritFunction<FloatView>>(home,fvb);
      case FloatVarBranch::SEL_MERIT_MAX:
        return new (home) ViewSelMax<MeritFunction<FloatView>>(home,fvb);
      case FloatVarBranch::SEL_MIN_MIN:
        return new (home) ViewSelMin<MeritMin>(home,fvb);
      case FloatVarBranch::SEL_MIN_MAX:
        return new (home) ViewSelMax<MeritMin>(home,fvb);
      case FloatVarBranch::SEL_MAX_MIN:
        return new (home) ViewSelMin<MeritMax>(home,fvb);
      case FloatVarBranch::SEL_MAX_MAX:
        return new (home) ViewSelMax<MeritMax>(home,fvb);
      case FloatVarBranch::SEL_SIZE_MIN:
        return new (home) ViewSelMin<MeritSize>(home,fvb);
      case FloatVarBranch::SEL_SIZE_MAX:
        return new (home) ViewSelMax<MeritSize>(home,fvb);
      case FloatVarBranch::SEL_DEGREE_MIN:
        return new (home) ViewSelMin<MeritDegree<FloatView>>(home,fvb);
      case FloatVarBranch::SEL_DEGREE_MAX:
        return new (home) ViewSelMax<MeritDegree<FloatView>>(home,fvb);
      case FloatVarBranch::SEL_AFC_MIN:
        return new (home) ViewSelMin<MeritAFC<FloatView>>(home,fvb);
      case FloatVarBranch::SEL_AFC_MAX:
        return new (home) ViewSelMax<MeritAFC<FloatView>>(home,fvb);
      case FloatVarBranch::SEL_ACTION_MIN:
        return new (home) ViewSelMin<MeritAction<FloatView>>(home,fvb);
      case FloatVarBranch::SEL_ACTION_MAX:
        return new (home) ViewSelMax<MeritAction<FloatView>>(home,fvb);
      case FloatVarBranch::SEL_CHB_MIN:
        return new (home) ViewSelMin<MeritCHB<FloatView>>(home,fvb);
      case FloatVarBranch::SEL_CHB_MAX:
        return new (home) ViewSelMax<MeritCHB<FloatView>>(home,fvb);
      case FloatVarBranch::SEL_DEGREE_SIZE_MIN:
        return new (home) ViewSelMin<MeritDegreeSize>(home,fvb);
      case FloatVarBranch::SEL_DEGREE_SIZE_MAX:
        return new (home) ViewSelMax<MeritDegreeSize>(home,fvb);
      case FloatVarBranch::SEL_AFC_SIZE_MIN:
        return new (home) ViewSelMin<MeritAFCSize>(home,fvb);
      case FloatVarBranch::SEL_AFC_SIZE_MAX:
        return new (home) ViewSelMax<MeritAFCSize>(home,fvb);
      case FloatVarBranch::SEL_ACTION_SIZE_MIN:
        return new (home) ViewSelMin<MeritActionSize>(home,fvb);
      case FloatVarBranch::SEL_ACTION_SIZE_MAX:
        return new (home) ViewSelMax<MeritActionSize>(home,fvb);
      case FloatVarBranch::SEL_CHB_SIZE_MIN:
        return new (home) ViewSelMin<MeritCHBSize>(home,fvb);
      case FloatVarBranch::SEL_CHB_SIZE_MAX:
        return new (home) ViewSelMax<MeritCHBSize>(home,fvb);
      default:
        throw UnknownBranching("Float::branch");
      }
    }
    GECODE_NEVER;
    return NULL;
  }

}}}


// STATISTICS: float-branch

