for each in /proc/sys/net/ipv4/conf/*

 do

     echo 0 > $each/accept_redirects

     echo 0 > $each/send_redirects

 done
