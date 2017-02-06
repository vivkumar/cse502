/* Copyright (c) 2015, Rice University

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

1.  Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
2.  Redistributions in binary form must reproduce the above
     copyright notice, this list of conditions and the following
     disclaimer in the documentation and/or other materials provided
     with the distribution.
3.  Neither the name of Rice University
     nor the names of its contributors may be used to endorse or
     promote products derived from this software without specific
     prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

/**
 * 
 * @author <a href="http://shams.web.rice.edu/">Shams Imam</a> (shams@rice.edu)
 */

/*
 * Ported to hclib for CSE502@IIITD: Vivek Kumar (vivekk@iiitd.ac.in)
 */

#include "hclib_cpp.h"
#include <stdlib.h>
#include <time.h>

// Lesser number of accounts mean more contention
#define TOTAL_ACCOUNTS (10 * hclib::num_workers())
#define TOTAL_TRANSACTIONS 1000000
class Account {
  private:
    double bal;
 
  public:
    Account(double b) { bal = b; }
    Account() { bal = 0; }
    double balance() { return bal; }
    bool withdraw(double amount) {
      if (amount > 0 && amount < bal) {
        bal -= amount;
        return true;
      }
      return false;
    }

    bool deposit(double amount) {
      if (amount > 0) {
        bal += amount;
        return true;
      }
      return false;
    }
};

int main(int argc, char ** argv) {
  hclib::launch([&]() {
  int numAccounts = TOTAL_ACCOUNTS;
  int numTransactions = TOTAL_TRANSACTIONS;

  double preSumOfBalances = 0;
  srand(time(NULL));
  Account* bankAccounts = new Account[numAccounts]; 
  void* isolation_objects[numAccounts];
  for (int i = 0; i < numAccounts; i++) {
    double random = rand();
    preSumOfBalances += random;
    bankAccounts[i].deposit(random);
    isolation_objects[i] = &(bankAccounts[i]);
  }

  //register the set of objects on which isolation may be required
  hclib::enable_isolation_n(isolation_objects, numAccounts);

  hclib::loop_domain_t loop = {0, numTransactions, 1, 1};
  hclib::finish([&]() {
    hclib::forasync1D(&loop, [&](int i) {
      double amount = 200.00 * (i+1);
      const int src = rand() % numAccounts;
      int dest = src; 
      while(dest == src) dest =  rand() % numAccounts;
      assert(src<TOTAL_ACCOUNTS && dest<TOTAL_ACCOUNTS);
      //object based isolation using isolated construct
      // Note: This will never deadlock
      hclib::isolated(&(bankAccounts[src]), &(bankAccounts[dest]), [&]() {
        bool success = bankAccounts[src].withdraw(amount);
        if (success) {
          bankAccounts[dest].deposit(amount);
        }
      });
    }, FORASYNC_MODE_RECURSIVE);
  });

  //de-register the set of objects on which isolation was requested
  hclib::disable_isolation_n(isolation_objects, numAccounts);

  double postSumOfBalances = 0;
  for (int i = 0; i < numAccounts; i++) {
    postSumOfBalances += bankAccounts[i].balance();
  }
  delete(bankAccounts);

  assert(preSumOfBalances == postSumOfBalances && "Test Failed");
  printf("Test Passed\n");
  });
  return 0;
}

