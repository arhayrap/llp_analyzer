#!/bin/sh

mkdir -p log
mkdir -p submit

echo `pwd`

cd ../
RazorAnalyzerDir=`pwd`
cd -

mode=bkg
year=Data2016
inputDir=/store/group/phys_exotica/delayedjets/displacedJetMuonAnalyzer/driftTube/V1p15/${year}/v4/v4/
echo ${inputDir}
outputDir=${inputDir}normalized
job_script=${RazorAnalyzerDir}/scripts_condor/normalize.sh

#Run2_displacedJetMuonNtupler_V1p12_Data2017_Run2017B-HighMET-17Nov2017 \
#Run2_displacedJetMuonNtupler_V1p12_Data2017_Run2017C-HighMET-17Nov2017 \
#Run2_displacedJetMuonNtupler_V1p12_Data2017_Run2017D-HighMET-17Nov2017 \
#Run2_displacedJetMuonNtupler_V1p12_Data2017_Run2017E-HighMET-17Nov2017 \
#Run2_displacedJetMuonNtupler_V1p12_Data2017_Run2017F-HighMET-17Nov2017
#Run2_displacedJetMuonNtupler_V1p12_Data2018_17Sept2018_Run2018B-HighMET-17Sep2018 \
#Run2_displacedJetMuonNtupler_V1p12_Data2018_17Sept2018_Run2018C-HighMET-17Sep2018 \
#Run2_displacedJetMuonNtupler_V1p12_Data2018_17Sept2018_Run2018D-HighMET-PromptReco
for sample in \
Run2_displacedJetMuonNtupler_V1p15_Data2016_Run2016B-HighMET-07Aug17_ver1 \
Run2_displacedJetMuonNtupler_V1p15_Data2016_Run2016B-HighMET-07Aug17_ver2 \
Run2_displacedJetMuonNtupler_V1p15_Data2016_Run2016C-HighMET-07Aug17 \
Run2_displacedJetMuonNtupler_V1p15_Data2016_Run2016D-HighMET-07Aug17 \
Run2_displacedJetMuonNtupler_V1p15_Data2016_Run2016E-HighMET-07Aug17 \
Run2_displacedJetMuonNtupler_V1p15_Data2016_Run2016F-HighMET-07Aug17 \
Run2_displacedJetMuonNtupler_V1p15_Data2016_Run2016G-HighMET-07Aug17 \
Run2_displacedJetMuonNtupler_V1p15_Data2016_Run2016H-HighMET-07Aug17
do
	echo "Sample " ${sample}
	analyzer=llp_MuonSystem
	rm -f submit/${analyzer}_normalize_${mode}_${sample}*.jdl
	rm -f log/${analyzer}_normalize_${mode}_${sample}*
	jdl_file=submit/${analyzer}_normalize_${mode}_${year}_${sample}.jdl
	echo "Universe = vanilla" > ${jdl_file}
	echo "Executable = ${job_script}" >> ${jdl_file}
	echo "Arguments =${mode} yes ${sample} ${inputDir} ${outputDir} ${CMSSW_BASE} ${HOME}/"  >> ${jdl_file}

	echo "Log = log/${analyzer}_normalize_${mode}_${sample}_PC.log" >> ${jdl_file}
	echo "Output = log/${analyzer}_normalize_${mode}_${sample}_\$(Cluster).\$(Process).out" >> ${jdl_file}
	echo "Error = log/${analyzer}_normalize_${mode}_${sample}_\$(Cluster).\$(Process).err" >> ${jdl_file}

	#echo "Requirements=TARGET.OpSysAndVer==\"CentOS7\"" >> ${jdl_file}
	echo "Requirements=(TARGET.OpSysAndVer==\"CentOS7\" && regexp(\"blade.*\", TARGET.Machine))" >> ${jdl_file}
	echo "RequestMemory = 4000" >> ${jdl_file}
	echo "RequestCpus = 1" >> ${jdl_file}
	echo "RequestDisk = 4" >> ${jdl_file}

	echo "+RunAsOwner = True" >> ${jdl_file}
	echo "+InteractiveUser = true" >> ${jdl_file}
	echo "+SingularityImage = \"/cvmfs/singularity.opensciencegrid.org/bbockelm/cms:rhel7\"" >> ${jdl_file}
	echo '+SingularityBindCVMFS = True' >> ${jdl_file}
	echo "run_as_owner = True" >> ${jdl_file}
	echo "x509userproxy = ${HOME}/x509_proxy" >> ${jdl_file}
	echo "should_transfer_files = YES" >> ${jdl_file}
	echo "when_to_transfer_output = ON_EXIT" >> ${jdl_file}
	echo "Queue 1" >> ${jdl_file}
	echo "condor_submit ${jdl_file}"
	condor_submit -batch-name ${sample} ${jdl_file}
	done
