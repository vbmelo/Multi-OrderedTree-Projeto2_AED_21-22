#!/bin/bash
#### RODANDO COM O NMEC = 101099
while (true); do
   for i in {990000..999999..1}
   do
        echo nmec = $i
        ./multi_ordered_tree $i 100000
   done
done