//
//  Simulation.cpp
//  EfficientQueueing
//
//  Created by Anand Venkataraman on 1/14/19.
//  Copyright © 2019 Anand Venkataraman. All rights reserved.
//
// In the Gaussian distributions below, we assume that the SD is one half
// of the mean. You can make it an instance or class attribute, but leave it
// at 2 in your submission.
//
// Note: After you have finished this lab, you can use this to demo at the
// STEM showcase instead of the other assigned extra credit project.
//
#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include "Simulation.h"
#include <random>
using namespace std;
// Global helper friend
ostream& operator<<(ostream& os, const Customer& cust) {
  // os << "Cust(inTime = " << cust.inTime << ", svcTime = " << cust.svcDuration << ")";
   return os; }
// Global helper friend
ostream& operator<<(ostream& os, const Simulation& sim) {
   os
   << "Simulation properties:" << endl
   << "  Number of cashiers: " << sim.getNumCashiers() << endl
   << "  Simulation duration: " << sim.getSimDuration() << endl
   << "  Queue joining threshold: " << sim.getQJoinThreshold() << endl
   << endl
   << "  Mean time between successive customers set to: " << sim.getMeanTimeToNextCustomer()
   << endl
   << "  Mean customer service time set to: " << sim.getMeanSvcTime() <<endl
   ;
   os << "  Cashier efficiencies:";
   for (size_t n = 0; n < sim.cashiers.size(); n++)
      os << " " << sim.cashiers[n].getEfficiencyPct();
   return os << endl;
}
// Private helper: find the shortest queue and if its length is at most
// qJoinThreshold, return its index. Else return -1
int Simulation::findViableQueue() const {
   int minQLen = -1, minNdx = -1;

   for (size_t n = 0; n < cashiers.size(); n++) {
      if (minQLen < 0 || (int) cashiers[n].q.size() < minQLen) {
         minQLen = (int) cashiers[n].q.size();
         minNdx = (int) n;
      }
   }
   if (qJoinThreshold < 0 || minQLen <= qJoinThreshold)
      return minNdx;
   return -1; }
// Private helper
// Return if the current wall clock reading indicates peak time
bool Simulation::isPeakTime() const {
   static int numSecondsPerPeriod = simDuration/NUM_PEAK_TIMES;
   int period = wallClock / numSecondsPerPeriod;
   return (period % 2 == 0);
}
// Private helper
// To keep the simulation as comprehensive as possible, we'll take the
// total simulation time and divide it up into NUM_PEAK_PERIODS chunks of time.
// The odd numbered chunks are "peak" times when the given meanTimeToNextCustomer
// is shorter (/= PEAK_TO_NORMAL_RATIO)
int Simulation::getNextCustomerArrivalInterval(default_random_engine& gen) const {
   static double x = meanTimeToNextCustomer;
   static double peakX = meanTimeToNextCustomer/PEAK_TO_NORMAL_RATIO;
   static normal_distribution<double> distroEntry(x, x/2.0);
   static normal_distribution<double> distroEntryPeak(peakX, peakX/2.0);
   int nextAt = isPeakTime() ? distroEntryPeak(gen) : distroEntry(gen);
   return (nextAt >= 0 ? nextAt : 0); // Clip and return
}
// Advance the wall clock by the given number of seconds. When that happens
// both timeToNextCustomer and the individual svc times of customers
// already at a cashier will be decreased by nSecs
void Simulation::advanceWallClock(int nSecs) {
   if (verbose) cout <<wallClock << ": Advancing wall clock by " << nSecs <<endl;
   wallClock += nSecs;
   if (wallClock < simDuration) {
      timeToNextCustomer -= nSecs;
      if (verbose)
         cout << wallClock << ": " << "Time to customer is now " <<timeToNextCustomer <<endl;
   }
   for (size_t n = 0; n < cashiers.size(); n++) {
      if (cashiers[n].q.size() > 0) {
         if (verbose)
            cout << wallClock << ": Cashier #" << n << ": " << cashiers[n].q.front();
         cashiers[n].q.front().svcDuration -= nSecs;

         if (verbose) cout  << " updated to " <<cashiers[n].q.front() <<endl;
      }
   } }
// ---- Public API ------------------------------------------
Simulation::Simulation(int theSimDuration, int theNumCashiers,
                       int theQJoinThreshold, int theMeanSvcTime,
                       int theMeanTimeToNextCustomer) {
   // Silently default to sensible values in the ctr
   setSimDuration(theSimDuration);
   setNumCashiers(theNumCashiers);
   setQJoinThreshold(theQJoinThreshold);
   setMeanSvcTime(theMeanSvcTime);
   setMeanTimeToNextCustomer(theMeanTimeToNextCustomer);
   cashiers.resize(numCashiers);
}
bool Simulation::setSimDuration(int n) {
   if (n <= 0) {
      simDuration = DEFAULT_SIM_DURATION;
      return false;
   }
   simDuration = n;
   return true;
}
bool Simulation::setNumCashiers(int n) {
   if (n <= 0) {
      numCashiers = DEFAULT_NUM_CASHIERS;
      return false;
   }
   numCashiers = n;
   cashiers.resize(numCashiers);
   return true;
}
bool Simulation::setQJoinThreshold(int n) {
   if (n < -1) {
      qJoinThreshold = 0; // Case 2 (Fry's style)
      return false;
   }
   qJoinThreshold = n;
   return true;
}
bool Simulation::setMeanSvcTime(int n) {
   if (n < MIN_MEAN_SVC_TIME) {
      meanSvcTime = MIN_MEAN_SVC_TIME;
      return false;
   }
   meanSvcTime = n;
   return true;

}
bool Simulation::setMeanTimeToNextCustomer(int n) {
   if (n < MIN_MEAN_TIME_TO_NEXT_CUSTOMER) {
      meanTimeToNextCustomer = MIN_MEAN_TIME_TO_NEXT_CUSTOMER;
      return false;
   }
   meanTimeToNextCustomer = n;
   return true;
}
bool Simulation::setCashierEfficiency(size_t n, int eff) {
   if (n >= cashiers.size())
      return false;
   return cashiers[n].setEfficiencyPct(eff);
}
void Simulation::run(ostream& os) {
   unsigned long numCustomers = 0, numCustomersProcessed = 0;
   unsigned long totalCustomerTime = 0;
   // You're free to ignore the next three lines - It is a way to generate
   // random numbers that are Normally distributed (like in real life)
   // instead of uniformly (which is what rand() provides)
   default_random_engine generator(rand());
   normal_distribution<double> distroSvc(meanSvcTime, meanSvcTime/2.0);
   // We will increment wallClock and stop the simulation when it rolls past
   // simDuration secs.
   this->wallClock = 0;
   // All cashier queues start off at length 0
   cashiers.resize(numCashiers);
   // The next customer will arrive in this many seconds
   timeToNextCustomer = getNextCustomerArrivalInterval(generator);
   if (verbose)
      cout << wallClock << ": Next customer will arrive in " << timeToNextCustomer <<endl;
   // We loop until the global queue has been emptied. When wallClock >
   // simDuration, new user creation (and enqueueing) will stop, and so
   // at some finite time after that the global queue will deplete to 0.
   while(wallClock < simDuration || numCustomersProcessed < numCustomers) {
      if (verbose) {
         cout << "--- TOP OF LOOP : " << (isPeakTime() ? "PEAK TIME" : "OFF-PEAK TIME")
         << " ---------------------------------------------------------\n";
      }
      // At the beginning of each iteration, move as many customers as
      // possible from the global queue into the cashier queues. Typically
      // this will move no more than 1 customer.
      while (globalQueue.size() > 0) {

         int n = findViableQueue();
         if (n < 0) // No viable queues
            break;
         if (verbose) {
            cout << wallClock << ": " << globalQueue.front()
            << " joined cashier #" << n << " at pos #" << cashiers[n].q.size() <<endl;
         }
         // Update the customer record with the actual service duration
         // which we now know because we know the cashier's efficiency.
         globalQueue.front().svcDuration *= 100;
         globalQueue.front().svcDuration /= cashiers[n].getEfficiencyPct();
         cashiers[n].q.push(globalQueue.front());
         globalQueue.pop();
      }
      // Is the next event a customer arrival or exit? Let's find out.
      // Determine the shortest svc time of all the non-empty cashier queues
      int minSvcDur = std::numeric_limits<int>::max();
      size_t cNdx = 0;
      for (size_t n = 0; n < cashiers.size(); n++) {
         if (cashiers[n].q.size() == 0) continue;
         if (cashiers[n].q.front().svcDuration < minSvcDur) {
            minSvcDur = cashiers[n].q.front().svcDuration;
            cNdx = n; // remember the first cashier to become free
         }
      }
      if (minSvcDur < timeToNextCustomer || wallClock > simDuration) {
         if (verbose)
            cout << wallClock << ": CHECKOUT " << cashiers[cNdx].q.front() << endl;
         advanceWallClock(minSvcDur);
         totalCustomerTime += (wallClock - cashiers[cNdx].q.front().inTime);
         cashiers[cNdx].q.pop();
         ++numCustomersProcessed;
      } else {
         if (verbose) cout << wallClock << ": ENTRY" << endl;
         advanceWallClock(timeToNextCustomer);
         // Add the new customer to global queue, but don't create a
         // new customer if the simulation has ended (Still need to empty
         // the queue of existing customers)
         if (wallClock < simDuration) {
            int svcTime = distroSvc(generator);
            if (svcTime < 0) svcTime = 0; // Clip
            globalQueue.push(Customer(svcTime, wallClock));
            ++numCustomers;
            // Set the time the next customer will arrive
            timeToNextCustomer = getNextCustomerArrivalInterval(generator);

            if (verbose) {
               cout << wallClock << ": " << globalQueue.back() << " joined global queue";
               if (wallClock < simDuration)
                  cout << "\tNext customer will arrive in " << timeToNextCustomer <<endl;
            } }
      }
      if (verbose) {
         cout << "\tGlobal queue length = " << globalQueue.size() <<endl;
         cout << "\tNum customers: " << numCustomers << " (" << numCustomersProcessed << " processed)\n";
         cout << "\tCashier queue lengths:";
         for (size_t n = 0; n < cashiers.size(); n++) cout << " " << cashiers[n].q.size();
         cout << endl;
      }
   }
   os << *this << "\n\n"
   << "Final wall clock reading: " <<wallClock << endl
   <<"Total number of customers served: " << numCustomers <<endl
   <<"Total customer time: " << totalCustomerTime <<endl
   <<"Average wait time per customer: " << totalCustomerTime / numCustomers <<endl;
}
