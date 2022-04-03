#!/bin/sh


#  Path to Canu.

bin="/home/zmx/work/canu/build/bin"

#  Report paths.

echo ""
echo "Found perl:"
echo "  " `which perl`
echo "  " `perl --version | grep version`
echo ""
echo "Found java:"
echo "  " `which /usr/local/java/jdk1.8.0_321/bin/java`
echo "  " `/usr/local/java/jdk1.8.0_321/bin/java -showversion 2>&1 | head -n 1`
echo ""
echo "Found canu:"
echo "  " $bin/canu
echo "  " `$bin/canu -version`
echo ""


#  Environment for any object storage.

export CANU_OBJECT_STORE_CLIENT=
export CANU_OBJECT_STORE_CLIENT_UA=
export CANU_OBJECT_STORE_CLIENT_DA=
export CANU_OBJECT_STORE_NAMESPACE=
export CANU_OBJECT_STORE_PROJECT=





/home/zmx/work/canu/build/bin/sqStoreCreate \
  -o ./test.seqStore.BUILDING \
  -minlength 1000 \
  -genomesize 10000 \
  -coverage   200 \
  -bias       0 \
  -raw -pacbio sub_seq /home/zmx/c++/毕设/simulate1/sub_seq/sub_seq.fasta \
&& \
mv ./test.seqStore.BUILDING ./test.seqStore \
&& \
exit 0

exit 1
