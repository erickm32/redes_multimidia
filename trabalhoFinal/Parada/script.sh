#!/bin/bash

echo "Convertendo para H.264"
echo "Vídeo já está em h264 e aac"

#echo "adicionando keyframes"
ffmpeg -r 30 -i parada_original.mp4 -c:v libx264 -bufsize 250k -x264opts keyint=60:min-keyint=60:scenecut=-1 -c:a copy -f mp4 parada_1080p_keyframes.mp4

echo "Escrevendo ffprobe"
ffprobe parada_1080p_keyframes.mp4 > teste.txt 2>&1

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
ffmpeg -i parada_1080p_keyframes.mp4 -c:v libx264 -b:v $bitr8 -c:a copy -f mp4 parada_1080p_keyframes_b80.mp4

echo "Bitrate 60% $bitr6"
ffmpeg -i parada_1080p_keyframes.mp4 -c:v libx264 -b:v $bitr6 -c:a copy -f mp4 parada_1080p_keyframes_b60.mp4

echo "Bitrate 40% $bitr4"
ffmpeg -i parada_1080p_keyframes.mp4 -c:v libx264 -b:v $bitr4 -c:a copy -f mp4 parada_1080p_keyframes_b40.mp4

echo "Bitrate 20% $bitr2"
ffmpeg -i parada_1080p_keyframes.mp4 -c:v libx264 -b:v $bitr2 -c:a copy -f mp4 parada_1080p_keyframes_b20.mp4


echo "Começando 720p"
#echo "adicionando keyframes"
ffmpeg -r 30 -i parada_original.mp4 -vf scale=1280:720 -c:v libx264 -bufsize 250k -x264opts keyint=60:min-keyint=60:scenecut=-1 -c:a copy -f mp4 parada_720p_keyframes.mp4
echo "Escrevendo ffprobe"
ffprobe parada_720p_keyframes.mp4 > teste.txt 2>&1

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
ffmpeg -i parada_720p_keyframes.mp4 -c:v libx264 -b:v $bitr8 -c:a copy -f mp4 parada_720p_keyframes_b80.mp4

echo "Bitrate 60% $bitr6"
ffmpeg -i parada_720p_keyframes.mp4 -c:v libx264 -b:v $bitr6 -c:a copy -f mp4 parada_720p_keyframes_b60.mp4

echo "Bitrate 40% $bitr4"
ffmpeg -i parada_720p_keyframes.mp4 -c:v libx264 -b:v $bitr4 -c:a copy -f mp4 parada_720p_keyframes_b40.mp4

echo "Bitrate 20% $bitr2"
ffmpeg -i parada_720p_keyframes.mp4 -c:v libx264 -b:v $bitr2 -c:a copy -f mp4 parada_720p_keyframes_b20.mp4




echo "Começando 480p"
#echo "adicionando keyframes"
ffmpeg -r 30 -i parada_original.mp4 -vf scale=720:480 -c:v libx264 -bufsize 250k -x264opts keyint=60:min-keyint=60:scenecut=-1 -c:a copy -f mp4 parada_480p_keyframes.mp4
echo "Escrevendo ffprobe"
ffprobe parada_480p_keyframes.mp4 > teste.txt 2>&1

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
ffmpeg -i parada_480p_keyframes.mp4 -c:v libx264 -b:v $bitr8 -c:a copy -f mp4 parada_480p_keyframes_b80.mp4

echo "Bitrate 60% $bitr6"
ffmpeg -i parada_480p_keyframes.mp4 -c:v libx264 -b:v $bitr6 -c:a copy -f mp4 parada_480p_keyframes_b60.mp4

echo "Bitrate 40% $bitr4"
ffmpeg -i parada_480p_keyframes.mp4 -c:v libx264 -b:v $bitr4 -c:a copy -f mp4 parada_480p_keyframes_b40.mp4

echo "Bitrate 20% $bitr2"
ffmpeg -i parada_480p_keyframes.mp4 -c:v libx264 -b:v $bitr2 -c:a copy -f mp4 parada_480p_keyframes_b20.mp4
