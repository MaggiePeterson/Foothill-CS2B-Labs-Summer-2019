//
//  Simulation.h
//  EfficientQueueing
//
//  Created by Anand Venkataraman on 1/14/19.
//  Copyright © 2019 Anand Venkataraman. All rights reserved.
//

#ifndef Simulation_h
#define Simulation_h

#include <vector>
#include <queue>
#include <random>

struct Customer {
   int svcDuration; // in secs
   int inTime;      // wall clock at time of entry (secs)

   Customer(int d, int t) : svcDuration(d), inTime(t) {}
};

// The efficiency of a cashier determines how quickly they would complete
// a task. Their average service time is determined by a Normal dist around
// meanCustomerServiceTime/efficiency, where efficiency = efficiencyPct/100
class Cashier {
private:
   int efficiencyPct;

public:
   std::queue<Customer> q;

   static const int MIN_EFF = 25;
   static const int MAX_EFF = 100;

   int getEfficiencyPct() const { return efficiencyPct; }

   bool setEfficiencyPct(int n) {
      if (n > MIN_EFF && n < MAX_EFF) {
         efficiencyPct = n;
         return true;
      }
      efficiencyPct = n < MIN_EFF ? MIN_EFF : MAX_EFF;
      return false;
   }

   Cashier() : efficiencyPct(100) {}
};

// All times are in seconds
class Simulation {
private:
   int simDuration;
   int numCashiers;
   int qJoinThreshold;           // queues joined if their length < this
   int wallClock;

   int meanTimeToNextCustomer;
   int meanSvcTime;

   int timeToNextCustomer;

   std::vector<Cashier> cashiers;

   // All customers line up in a global queue after entering the store until
   // they commit to a particular cashier.
   std::queue<Customer> globalQueue;

   bool verbose = false;         // Use for debugging

   // All times are in seconds below
   static const int DEFAULT_SIM_DURATION = 10 * 3600;         // 10h
   static const int DEFAULT_NUM_CASHIERS = 10;

   // 10 peak times evenly distributed, and 2 times as many shoppers during peaks
   static const int NUM_PEAK_TIMES = 10;
   static const int PEAK_TO_NORMAL_RATIO = 2;

   static const int MIN_MEAN_SVC_TIME = 20;
   static const int MIN_MEAN_TIME_TO_NEXT_CUSTOMER = 20;

   // Private helpers
   bool isPeakTime() const;
   int findViableQueue() const;
   int getNextCustomerArrivalInterval(std::default_random_engine& gen) const;
   void advanceWallClock(int n);

public:
   Simulation (int theSimDuration, int theNumCashiers, int theQJoinThreshold,
               int theMeanSvcTime, int theMeanTimeToNextCustomer);

   int getSimDuration() const { return simDuration; }
   int getNumCashiers() const { return numCashiers; }
   int getQJoinThreshold() const { return qJoinThreshold; }
   int getMeanSvcTime() const { return meanSvcTime; }
   int getMeanTimeToNextCustomer() const { return meanTimeToNextCustomer; }

   // Define setters and the ctr out of line 'cuz you can validate
   bool setSimDuration(int n);
   bool setNumCashiers(int n);
   bool setQJoinThreshold(int n);
   bool setMeanSvcTime(int n);
   bool setMeanTimeToNextCustomer(int n);

   bool setCashierEfficiency(size_t n, int eff);
   bool setVerbose()  { if (verbose) return false; return verbose = true; }
   bool unsetVerbose()  { if (!verbose) return false; return !(verbose = false); }

   void run(std::ostream& os);

   // Make a friend so it can access the cashiers vector directly.
   friend std::ostream& operator<<(std::ostream& os, const Simulation& sim);

   // Friend my unit test
   friend bool unitTest(std::ostream& os);
   friend bool unitTest(std::ofstream& os);
};

#endif /* Simulation_h */
