#!/bin/bash
#### RODANDO COM O NMEC = 101099
while (true); do
   for i in {4..10000..1}
   do
      echo runing for: $i >> search_time.txt
      echo runing for: $i >> creation_time.txt
      echo runing for: $i >> treeDepth_time.txt
      ./multi_ordered_tree 101099 $i
      echo $'\n' >> search_time.txt
      echo $'\n' >> creation_time.txt
      echo $'\n' >> treeDepth_time.txt
   done
   for i in {10000..50000..100}
   do
      echo runing for: $i >> search_time.txt
      echo runing for: $i >> creation_time.txt
      echo runing for: $i >> treeDepth_time.txt
      ./multi_ordered_tree 101099 $i
      echo $'\n' >> search_time.txt
      echo $'\n' >> creation_time.txt
      echo $'\n' >> treeDepth_time.txt
   done
   for i in {50000..10000000..1000}
   do
      echo runing for: $i >> search_time.txt
      echo runing for: $i >> creation_time.txt
      echo runing for: $i >> treeDepth_time.txt
      ./multi_ordered_tree 101099 $i
      echo $'\n' >> search_time.txt
      echo $'\n' >> creation_time.txt
      echo $'\n' >> treeDepth_time.txt
   done
done