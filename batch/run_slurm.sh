#!/bin/bash

#SBATCH -D /mnt/pool/nica/8/trshinvv/bmn_hyperons/bmn_particle_finder/log
#SBATCH -p cpu
##SBATCH -t 24:00:00
#SBATCH -J finder
#SBATCH -a 1-100
#SBATCH -o /mnt/pool/nica/8/trshinvv/bmn_hyperons/bmn_particle_finder/log/%A_%a.log

list_dir=/mnt/pool/nica/8/trshinvv/bmn_hyperons/bmn_particle_finder/build/list_dir/
output_dir=/mnt/pool/nica/8/trshinvv/bmn_hyperons/bmn_particle_finder/build/output_dir

id=$SLURM_ARRAY_TASK_ID
input_list=/mnt/pool/nica/8/trshinvv/bmn_hyperons/input_list.txt
split -l 100 -d -a 4 --additional-suffix=.txt $input_list $list_dir
file_list=$( ls $list_dir | head -n $id | tail -n 1 )

mkdir -p $output_dir
cd $output_dir
##mkdir -p room_ks
##cd room_ks
mkdir -p $id
cd $id
source /mnt/pool/nica/7/mam2mih/soft/basov/root-6.28.06/install/bin/thisroot.sh
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/mnt/pool/nica/8/trshinvv/bmn_hyperons/PFSimple/install/lib/:/mnt/pool/nica/8/trshinvv/bmn_hyperons/PFSimple/install/external/lib

echo "/mnt/pool/nica/8/trshinvv/bmn_hyperons/bmn_particle_finder/build/find_candidates /mnt/pool/nica/8/trshinvv/bmn_hyperons/bmn_particle_finder/macro/lambda.cc $list_dir$file_list"

time /mnt/pool/nica/8/trshinvv/bmn_hyperons/bmn_particle_finder/build/find_candidates /mnt/pool/nica/8/trshinvv/bmn_hyperons/bmn_particle_finder/macro/lambda.cc  $list_dir$file_list
time root -l -b -q /mnt/pool/nica/8/trshinvv/bmn_hyperons/bmn_particle_finder/macro/rec_lambda_qa.cc
time mv $output_dir/$id/rec_lambda_qa.root $output_dir/rec_lambda_qa_$id.root
