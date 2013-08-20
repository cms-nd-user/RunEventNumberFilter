// -*- C++ -*-
//
// Package:    RunEventNumberFilter
// Class:      RunEventNumberFilter
// 
/**\class RunEventNumberFilter RunEventNumberFilter.cc RunEventNumberFilter/RunEventNumberFilter/src/RunEventNumberFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Douglas Ryan Berry,512 1-008,+41227670494,
//         Created:  Thu Jul 15 17:01:34 CEST 2010
// $Id: RunEventNumberFilter.cc,v 1.4 2012/03/16 10:17:21 drberry Exp $
//
//


// system include files
#include <memory>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

using namespace std;
//
// class declaration
//

class RunEventNumberFilter : public edm::EDFilter {
   public:
      explicit RunEventNumberFilter(const edm::ParameterSet&);
      ~RunEventNumberFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      // ----------member data ---------------------------
  bool debug_;
  string filename_;
  vector <unsigned int> runs;
  vector <unsigned int> lumis;
  vector <unsigned int> events;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
RunEventNumberFilter::RunEventNumberFilter(const edm::ParameterSet& iConfig)
{
  //now do what ever initialization is needed
  filename_ = iConfig.getParameter<string>("filename");
  debug_ = iConfig.getParameter<bool>("debug");
  if (debug_) cout << "Reading file: " << filename_ << endl;
  ifstream eventfile(filename_.data());
  while (!eventfile.eof()){
    unsigned int run;
    unsigned int lumi;
    unsigned int event;
    eventfile >> run;
    eventfile >> lumi;
    eventfile >> event;
    if (debug_) cout << "Keeping event " << event << "in lumiBlock " << lumi << " in run " << run << endl;
    runs.push_back(run);
    lumis.push_back(lumi);
    events.push_back(event);
  }
  eventfile.close();
}


RunEventNumberFilter::~RunEventNumberFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
RunEventNumberFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   RunNumber_t runNumber = iEvent.id().run();
   unsigned int lumiNumber = iEvent.id().luminosityBlock();
   EventNumber_t eventNumber = iEvent.id().event();
   bool FilterResult = false;

   if (debug_) cout << "The run number is " << runNumber << " and the Luminosity Block is " << lumiNumber << " and the event number is " << eventNumber << endl;

   for (unsigned int i=0; i<events.size(); i++) {
     if (runs[i]==runNumber && lumis[i]==lumiNumber && events[i]==eventNumber) {
       FilterResult = true;
       break;
     }
   }

   if (debug_ && FilterResult) cout << "Found an event that passes: " << runNumber << ":" << lumiNumber << ":" <<eventNumber << endl;
   
   return FilterResult;

}

// ------------ method called once each job just before starting event loop  ------------
void 
RunEventNumberFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RunEventNumberFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(RunEventNumberFilter);
