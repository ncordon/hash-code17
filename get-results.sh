#!/bin/bash

g++ hash.cc

zip codigo.zip hash.cc

(./a.out < ./data/me_at_the_zoo.in) > ./results/me_at_the_zoo.out
(./a.out < ./data/kittens.in) > ./results/kittens.out
(./a.out < ./data/trending_today.in) > ./results/trending_today.out
(./a.out < ./data/videos_worth_spreading.in) > ./results/videos_worth_spreading.out
