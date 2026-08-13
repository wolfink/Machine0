#!/bin/bash

./build.sh
((!$?)) && carla-single vst3 bin/VST3/Machine0.vst3
