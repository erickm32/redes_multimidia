mkdir 1080mpd 720mpd 480mpd 1080_bitrate_mpd 720_bitrate_mpd 480_bitrate_mpd


MP4Box -dash 2000 -frag 2000 -rap -profile dashavc264:onDemand -url-template orig/parada_1080p_keyframes.mp4#video orig/parada_1080p_keyframes.mp4#audio -out teste/parada_1080p_keyframes.mpd

#MP4Box -dash 2000 -dash-profile on-demand -segment-name parada_1080p_keyframes-100-seg orig/parada_1080p_keyframes.mp4#video orig/parada_1080p_keyframes.mp4#audio -out teste/parada_1080p_keyframes.mpd
MP4Box -dash 2000 -dash-profile on-demand -segment-name parada_1080p_keyframes-100-seg orig/parada_1080p_keyframes.mp4#video -out teste/parada_1080p_keyframes.mpd
MP4Box -dash 2000 -dash-profile on-demand -url-template orig/parada_1080p_keyframes.mp4#video -out teste/parada_1080p_keyframes.mpd



#mpd para cada arquivo
#MP4Box -dash 2000 -dash-profile on-demand -segment-name parada_1080p_keyframes-100-seg orig/parada_1080p_keyframes.mp4#video -out 1080mpd/parada_1080p_keyframes.mpd
#MP4Box -dash 2000 -dash-profile on-demand -segment-name parada_720p_keyframes-100-seg orig/parada_720p_keyframes.mp4#video -out 720mpd/parada_720p_keyframes.mpd
#MP4Box -dash 2000 -dash-profile on-demand -segment-name parada_480p_keyframes-100-seg orig/parada_480p_keyframes.mp4#video -out 480mpd/parada_480p_keyframes.mpd
MP4Box -dash 2000 -dash-profile on-demand -url-template orig/parada_1080p_keyframes.mp4#video orig/parada_1080p_keyframes.mp4#audio -out 1080mpd/parada_1080p_keyframes.mpd
MP4Box -dash 2000 -dash-profile on-demand -url-template orig/parada_720p_keyframes.mp4#video orig/parada_720p_keyframes.mp4#audio -out 720mpd/parada_720p_keyframes.mpd
MP4Box -dash 2000 -dash-profile on-demand -url-template orig/parada_480p_keyframes.mp4#video orig/parada_480p_keyframes.mp4#audio -out 480mpd/parada_480p_keyframes.mpd

cd 1080_bitrate_mpd
mkdir 80p 60p 40p 20p
#mpd para cada arquivo 1080p com diferente bitrate
#MP4Box -dash 2000 -dash-profile on-demand -segment-name parada_1080p_keyframes-80-seg ../bitrates1080p/parada_1080p_keyframes_b80.mp4#video -out 80p/b80_parada_1080p_keyframes.mpd
#MP4Box -dash 2000 -dash-profile on-demand -segment-name parada_1080p_keyframes-60-seg ../bitrates1080p/parada_1080p_keyframes_b60.mp4#video -out 60p/b60_parada_1080p_keyframes.mpd
#MP4Box -dash 2000 -dash-profile on-demand -segment-name parada_1080p_keyframes-40-seg ../bitrates1080p/parada_1080p_keyframes_b40.mp4#video -out 40p/b40_parada_1080p_keyframes.mpd
#MP4Box -dash 2000 -dash-profile on-demand -segment-name parada_1080p_keyframes-20-seg ../bitrates1080p/parada_1080p_keyframes_b20.mp4#video -out 20p/b20_parada_1080p_keyframes.mpd
MP4Box -dash 2000 -dash-profile on-demand -url-template ../bitrates1080p/parada_1080p_keyframes_b80.mp4#video ../bitrates1080p/parada_1080p_keyframes_b80.mp4#audio -out 80p/b80_parada_1080p_keyframes.mpd
MP4Box -dash 2000 -dash-profile on-demand -url-template ../bitrates1080p/parada_1080p_keyframes_b60.mp4#video ../bitrates1080p/parada_1080p_keyframes_b60.mp4#audio -out 60p/b60_parada_1080p_keyframes.mpd
MP4Box -dash 2000 -dash-profile on-demand -url-template ../bitrates1080p/parada_1080p_keyframes_b40.mp4#video ../bitrates1080p/parada_1080p_keyframes_b40.mp4#audio -out 40p/b40_parada_1080p_keyframes.mpd
MP4Box -dash 2000 -dash-profile on-demand -url-template ../bitrates1080p/parada_1080p_keyframes_b20.mp4#video ../bitrates1080p/parada_1080p_keyframes_b20.mp4#audio -out 20p/b20_parada_1080p_keyframes.mpd

cd ../
cd 720_bitrate_mpd
mkdir 80p 60p 40p 20p
#mpd para cada arquivo 720p com diferente bitrate
#MP4Box -dash 2000 -dash-profile on-demand -segment-name parada_720p_keyframes_b80-seg ../bitrates720p/parada_720p_keyframes_b80.mp4#video -out 80p/b80_parada_720p_keyframes.mpd
#MP4Box -dash 2000 -dash-profile on-demand -segment-name parada_720p_keyframes_b60-seg ../bitrates720p/parada_720p_keyframes_b60.mp4#video -out 60p/b60_parada_720p_keyframes.mpd
#MP4Box -dash 2000 -dash-profile on-demand -segment-name parada_720p_keyframes_b40-seg ../bitrates720p/parada_720p_keyframes_b40.mp4#video -out 40p/b40_parada_720p_keyframes.mpd
#MP4Box -dash 2000 -dash-profile on-demand -segment-name parada_720p_keyframes_b20-seg ../bitrates720p/parada_720p_keyframes_b20.mp4#video -out 20p/b20_parada_720p_keyframes.mpd
MP4Box -dash 2000 -dash-profile on-demand -url-template ../bitrates720p/parada_720p_keyframes_b80.mp4#video ../bitrates720p/parada_720p_keyframes_b80.mp4#audio -out 80p/b80_parada_720p_keyframes.mpd
MP4Box -dash 2000 -dash-profile on-demand -url-template ../bitrates720p/parada_720p_keyframes_b60.mp4#video ../bitrates720p/parada_720p_keyframes_b60.mp4#audio -out 60p/b60_parada_720p_keyframes.mpd
MP4Box -dash 2000 -dash-profile on-demand -url-template ../bitrates720p/parada_720p_keyframes_b40.mp4#video ../bitrates720p/parada_720p_keyframes_b40.mp4#audio -out 40p/b40_parada_720p_keyframes.mpd
MP4Box -dash 2000 -dash-profile on-demand -url-template ../bitrates720p/parada_720p_keyframes_b20.mp4#video ../bitrates720p/parada_720p_keyframes_b20.mp4#audio -out 20p/b20_parada_720p_keyframes.mpd

cd ../
cd 480_bitrate_mpd
mkdir 80p 60p 40p 20p

#mpd para cada arquivo 480p com diferente bitrate
#mano do céu isso não acaba mais

#MP4Box -dash 2000 -dash-profile on-demand -segment-name parada_480p_keyframes_b80 ../bitrates480p/parada_480p_keyframes_b80.mp4#video -out 80p/b80_parada_480p_keyframes.mpd
#MP4Box -dash 2000 -dash-profile on-demand -segment-name parada_480p_keyframes_b60 ../bitrates480p/parada_480p_keyframes_b60.mp4#video -out 60p/b60_parada_480p_keyframes.mpd
#MP4Box -dash 2000 -dash-profile on-demand -segment-name parada_480p_keyframes_b40 ../bitrates480p/parada_480p_keyframes_b40.mp4#video -out 40p/b40_parada_480p_keyframes.mpd
#MP4Box -dash 2000 -dash-profile on-demand -segment-name parada_480p_keyframes_b20 ../bitrates480p/parada_480p_keyframes_b20.mp4#video -out 20p/b20_parada_480p_keyframes.mpd
MP4Box -dash 2000 -dash-profile on-demand -url-template ../bitrates480p/parada_480p_keyframes_b80.mp4#video ../bitrates480p/parada_480p_keyframes_b80.mp4#audio -out 80p/b80_parada_480p_keyframes.mpd
MP4Box -dash 2000 -dash-profile on-demand -url-template ../bitrates480p/parada_480p_keyframes_b60.mp4#video ../bitrates480p/parada_480p_keyframes_b60.mp4#audio -out 60p/b60_parada_480p_keyframes.mpd
MP4Box -dash 2000 -dash-profile on-demand -url-template ../bitrates480p/parada_480p_keyframes_b40.mp4#video ../bitrates480p/parada_480p_keyframes_b40.mp4#audio -out 40p/b40_parada_480p_keyframes.mpd
MP4Box -dash 2000 -dash-profile on-demand -url-template ../bitrates480p/parada_480p_keyframes_b20.mp4#video ../bitrates480p/parada_480p_keyframes_b20.mp4#audio -out 20p/b20_parada_480p_keyframes.mpd

cd ../
#acabou Deus é mais
