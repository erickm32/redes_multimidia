#!/bin/bash

echo "Convertendo para H.264"
#ffmpeg -i sintel_trailer_2k_1080p24.y4m sintel_conv.mp4

echo "Escrevendo ffprobe"
ffprobe sintel_conv.mp4 > teste.txt 2>&1

echo "Retirando bitrate"
bitr=$(awk -F ":" '/bitrate/ {print $6 - $7}' teste.txt)

bitr8=$(echo "scale=5 ; $bitr * 0.8" | bc)
bitr6=$(echo "scale=5 ; $bitr * 0.6" | bc)
bitr4=$(echo "scale=5 ; $bitr * 0.4" | bc)
bitr2=$(echo "scale=5 ; $bitr * 0.2" | bc)

bitr8+="k"
bitr6+="k"
bitr4+="k"
bitr2+="k"

echo $bitr

rm -rf teste.txt

echo "Bitrate 80% $bitr8"
ffmpeg -i sintel_conv.mp4 -c:v libx264 -b:v $bitr8 sintel_800k.mp4

echo "Bitrate 60% $bitr6"
ffmpeg -i sintel_conv.mp4 -c:v libx264 -b:v $bitr6 sintel_600k.mp4

echo "Bitrate 40% $bitr4"
ffmpeg -i sintel_conv.mp4 -c:v libx264 -b:v $bitr4 sintel_400k.mp4

echo "Bitrate 20% $bitr2"
ffmpeg -i sintel_conv.mp4 -c:v libx264 -b:v $bitr2 sintel_200k.mp4