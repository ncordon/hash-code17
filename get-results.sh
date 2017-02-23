#!/bin/bash

g++ hash.cc

(./a.out < ./data/me_at_the_zoo.in) > ./data/me_at_the_zoo.out
(./a.out < ./data/kittens.in) > ./data/kittens.out
(./a.out < ./data/trending_today.in) > ./data/trending_today.out
(./a.out < ./data/videos_worth_spreading.in) > ./data/videos_worth_spreading.out
