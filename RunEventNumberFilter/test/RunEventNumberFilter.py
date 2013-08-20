# Auto generated configuration file
# using: 
# Revision: 1.168.2.1 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: SingleGammaPt35_cfi.py -s GEN,SIM,DIGI,DIGI2RAW,RAW2DIGI,RECO -n 2 --conditions FrontierConditions_GlobalTag,MC_36Y_V10::All --eventcontent RECOSIM --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('GetEvents')


#### Turn off printing every event ####
process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)


# import of standard configurations
#process.load('Configuration.StandardSequences.Services_cff')


#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#process.load('Configuration.EventContent.EventContent_cff')

#process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
#process.GlobalTag.globaltag = 'MC_3XY_V26::All'
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )


# Input source
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring(
	'file:/afs/crc.nd.edu/user/j/jslaunwh/RAW/8EE30C05-18E9-E211-A9A7-002618943810.root'
	))

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

#Event Selection
process.selectEventsByRunEventNumber = cms.EDFilter("RunEventNumberFilter",
													debug = cms.bool(False),
													filename = cms.string('inputs.txt')
													)

# Output definition
process.outputA = cms.OutputModule("PoolOutputModule",
	#fastCloning = cms.untracked.bool(False),
    fileName = cms.untracked.string('SkimRunEvent.root'),
    SelectEvents = cms.untracked.PSet (
      SelectEvents = cms.vstring('selectByRunEvent')
    )                                  
                                  
)

# Path and EndPath definitions
process.selectByRunEvent = cms.Path(process.selectEventsByRunEventNumber)

process.Aoutput = cms.EndPath(process.outputA)
