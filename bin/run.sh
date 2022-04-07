#！/bin/sh
echo -e "create simulate data\n"
./create_seq 6
echo -e "map  the accurate sub_seq to the mis_seq by using blasr\n"

echo -e "command：\n"
echo -e "blasr   ./../sub_seq/sub_seq.fasta\n
        ./../mis_seq/mis_seq.fasta\n
        --header\n
        --bestn 1\n
        -m 5 --out\n
        ./../map_result/map_result.out\n"
blasr   ./../sub_seq/sub_seq.fasta\
        ./../mis_seq/mis_seq.fasta\
        --header\
        --bestn 1\
        -m 5 --out\
        ./../map_result/map_result.out

echo -e "\ncorrect the mis_seq according to the map result\n"
./correct

echo -e "get the similarity between the init_seq and mis_seq and the similarity between the init_seq and corrected_seq\n"

./compare
echo -e "\ncount the microsatellite of the corrected_seq\n"
./mic_count
echo -e "count result:\n"
while read line
do
echo $line
done<./../result/result.out