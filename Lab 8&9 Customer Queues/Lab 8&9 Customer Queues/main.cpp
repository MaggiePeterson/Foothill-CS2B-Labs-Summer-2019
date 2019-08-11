//
//  main.cpp
//  EfficientQueueing
//
//  Created by Anand Venkataraman on 1/14/19.
//  Copyright © 2019 Anand Venkataraman. All rights reserved.
//
//  As usual, this is for your reference only. I won't test your main()
//  Simply use it as a starting point for your own experimentation.
//

#include <iostream>
#include <sstream>

#include "Simulation.h"

using namespace std;

int main(int argc, const char * argv[]) {
   // Fill in reasonable values for your simulation
   int meanTimeToNextCustomer = 4;
   int meanTransactionTime = 4;
   int numCashiers = 60;
   int simDuration = 100;
   int qJoinThreshold = 20;

   srand((unsigned) time(0L));       // Comment out while testing

   Simulation sim(simDuration, numCashiers, qJoinThreshold,
                  meanTransactionTime, meanTimeToNextCustomer);
   sim.setVerbose();

   cout<<"FRys Strategy 2"<<endl;
   sim.setQJoinThreshold(0); // Fry's style
   stringstream ss1;
   sim.run(ss1);
   cout << ss1.str() <<endl;

   cout << "------------------------------------------------------\n";
   cout<<"Walmart Strategy 1"<<endl;
   sim.setQJoinThreshold(-1); // Walmart Style
   stringstream ss2;
   sim.run(ss2);
   cout << ss2.str() <<endl;
   cout << "------------------------------------------------------\n";

   return 0;
}
