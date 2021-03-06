/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2009
 *
 *  Last modified:
 *     $Date: 2017-03-15 16:09:31 +0100 (Wed, 15 Mar 2017) $ by $Author: schulte $
 *     $Revision: 15582 $
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

#include "test/int.hh"

#include <gecode/minimodel.hh>

namespace Test { namespace Int {

   /// %Tests for synchronized execution
   namespace Exec {

     /**
      * \defgroup TaskTestIntExec Synchronized execution
      * \ingroup TaskTestInt
      */
     //@{
     /// Simple test for wait (integer variables)
     class IntWait : public Test {
     protected:
       /// Whether to use std::function
       bool sf;
     public:
       /// Create and register test
       IntWait(int n, bool sf0)
         : Test("Wait::Int::"+str(n)+"::"+
                (sf0 ? "std::function" : "funptr"),n,0,n,false), sf(sf0) {}
       /// Check whether \a x is solution
       virtual bool solution(const Assignment& x) const {
         for (int i=0; i<x.size(); i++)
           for (int j=i+1; j<x.size(); j++)
             if (x[i] == x[j])
               return false;
         return true;
       }
       /// Post wait on \a x
       virtual void post(Gecode::Space& home, Gecode::IntVarArray& x) {
         using namespace Gecode;
         auto f = static_cast<std::function<void(Space&)>>
           ([](Space& home) { c(home); });
         if (x.size() > 1) {
           if (sf)
             Gecode::wait(home, x, f);
           else
             Gecode::wait(home, x, &c);
         } else {
           if (sf)
             Gecode::wait(home, x[0], f);
           else
             Gecode::wait(home, x[0], &c);
         }
       }
       /// Continuation to be executed
       static void c(Gecode::Space& _home) {
         TestSpace& home = static_cast<TestSpace&>(_home);
         for (int i=0; i<home.x.size(); i++)
           for (int j=i+1; j<home.x.size(); j++)
             if (home.x[i].val() == home.x[j].val())
               home.fail();
       }
     };

     /// Simple test for wait (Boolean variables)
     class BoolWait : public Test {
     protected:
       /// Whether to use std::function
       bool sf;
     public:
       /// Create and register test
       BoolWait(int n, bool sf0)
         : Test("Wait::Bool::"+str(n)+"::"+
                (sf0 ? "std::function" : "funptr"),n,0,1,false), sf(sf0) {}
       /// Check whether \a x is solution
       virtual bool solution(const Assignment& x) const {
         int t=0;
         for (int i=0; i<x.size(); i++)
           t += x[i];
         return t==2;
       }
       /// Post wait on \a x
       virtual void post(Gecode::Space& home, Gecode::IntVarArray& x) {
         using namespace Gecode;
         BoolVarArgs b(x.size());
         for (int i=b.size(); i--; )
           b[i]=channel(home,x[i]);
         auto f = static_cast<std::function<void(Space&)>>
           ([](Space& home) { c(home); });
         if (b.size() > 1) {
           if (sf)
             Gecode::wait(home, b, f);
           else
             Gecode::wait(home, b, &c);
         } else {
           if (sf)
             Gecode::wait(home, b[0], f);
           else
             Gecode::wait(home, b[0], &c);
         }
       }
       /// Continuation to be executed
       static void c(Gecode::Space& _home) {
         TestSpace& home = static_cast<TestSpace&>(_home);
         int t=0;
         for (int i=0; i<home.x.size(); i++)
           t += home.x[i].val();
         if (t!=2)
           home.fail();
       }
     };

     /// Simple test for when
     class When : public Test {
     protected:
       /// Whether to use std::function
       bool sf;
     public:
       /// Create and register test
       When(bool sf0) 
         : Test(std::string("When::")+
                (sf0 ? "std::function" : "funptr"),1,0,1,false), sf(sf0) {}
       /// Check whether \a x is solution
       virtual bool solution(const Assignment& x) const {
         return x[0]==0;
       }
       /// Post when on \a x
       virtual void post(Gecode::Space& home, Gecode::IntVarArray& x) {
         using namespace Gecode;
         if (sf) {
           auto sft = static_cast<std::function<void(Space&)>>
             ([](Space& home) { t(home); });
           auto sfe = static_cast<std::function<void(Space&)>>
             ([](Space& home) { e(home); });
           when(home, channel(home, x[0]), sft, sfe);
         } else {
           when(home, channel(home, x[0]), &t, &e);
         }
       }
       /// Then-function to be executed
       static void t(Gecode::Space& home) {
         home.fail();
       }
       /// Else-function to be executed
       static void e(Gecode::Space& home) {
         (void) home;
       }
     };

     IntWait iw1t(1,true), iw2t(2,true), iw3t(3,true), iw4t(4,true);
     IntWait iw1f(1,false), iw2f(2,false), iw3f(3,false), iw4f(4,false);
     BoolWait bw1t(1,true), bw2t(2,true), bw3t(3,true), bw4t(4,true);
     BoolWait bw1f(1,false), bw2f(2,false), bw3f(3,false), bw4f(4,false);


     When whent(true);
     When whenf(false);
     //@}

   }

}}

// STATISTICS: test-int
