ver=V1p17
ver2=/v5/v180/
outputRoot=Run2_displacedJetMuonNtupler_${ver}_Data2016_Data2017_Data2018-ZMu_goodLumi.root
dir1=/storage/af//group/phys_exotica/delayedjets/displacedJetMuonAnalyzer/csc/${ver}/Data2016/${ver2}/normalized/
dir2=/storage/af//group/phys_exotica/delayedjets/displacedJetMuonAnalyzer/csc/${ver}/Data2017/${ver2}/normalized/
dir3=/storage/af//group/phys_exotica/delayedjets/displacedJetMuonAnalyzer/csc/${ver}/Data2018/${ver2}/normalized/

rm -f ${outputRoot}
eval `scram runtime -sh`

hadd $outputRoot ${dir1}/Run2_displacedJetMuonNtupler_${ver}_Data2016_Run2016-ZMu-07Aug17_goodLumi.root ${dir2}/Run2_displacedJetMuonNtupler_${ver}_Data2017_Run2017-ZMu-17Nov2017_goodLumi.root ${dir3}/Run2_displacedJetMuonNtupler_${ver}_Data2018_17Sept2018_Run2018-ZMu-17Sep2018_goodLumi.root 


#/mnt/hadoop/${dir3}/Run2_displacedJetMuonNtupler_${ver}_Data2018_17Sept2018_Run2018AB-ZMu-17Sep2018_goodLumi.root

if [ -f $outputRoot ]
then
        echo "hadd done"
fi

eval `scram unsetenv -sh`
LD_LIBRARY_PATH=/usr/lib64:$LD_LIBRARY_PATH

cp ${outputRoot} ${dir3}/$outputRoot
if [ -f $dir/$outputRoot ]
then
	echo "copy succeed"
	rm $outputRoot
fi
