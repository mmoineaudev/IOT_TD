# IOT_TD

Le lien : http://www.i3s.unice.fr/~menez/M1Miage/

Les codes de base :

http://www.i3s.unice.fr/~menez/M1Miage/TP2/readserial/readserial.ino

http://www.i3s.unice.fr/~menez/M1Miage/TP2/wifi_httpwebserver0/wifi_httpwebserver0.ino

http://www.i3s.unice.fr/~menez/M1Miage/TP2/wificonnect/wificonnect.ino

http://www.i3s.unice.fr/~menez/M1Miage/TP2/wifihttp_getonly0/wifihttp_getonly0.ino

http://www.i3s.unice.fr/~menez/M1Miage/TP2/wifihttp_getonly1/wifihttp_getonly1.ino

http://www.i3s.unice.fr/~menez/M1Miage/TP2/wifiscan/wifiscan.ino

<hr>

# Rendu

La partie 1 à été validée en séance de TD

## 2 Connectivité Wifi

- Recherche des SSIDs environnants

On utilise : wifiscan.ino

```


IOT_TD$ python3 readserial.py
3) Network Name : HONORV10
       signal Strength : -55
       MAC Address : 38:37:8B:4F:DE:FB
       Encryption type: WPA2_PSK
4) Network Name : Honor 9 Lite
       signal Strength : -57
       MAC Address : 74:D2:1D:09:DA:5D
       Encryption type: WPA2_PSK
5) Network Name : Téléphone Mi
       signal Strength : -61
       MAC Address : 22:47:DA:6E:92:0E
       Encryption type: WPA2_PSK
6) Network Name : HUAWEI_P20
       signal Strength : -64
       MAC Address : E4:A7:C5:45:81:F9
       Encryption type: WPA2_PSK
7) Network Name : Valhalla
       signal Strength : -68
       MAC Address : 32:07:4D:E7:22:77
       Encryption type: WPA2_PSK
8) Network Name : iPhone de Nikita Gourevitch
       signal Strength : -69
       MAC Address : 7A:40:4E:12:FE:76
       Encryption type: WPA2_PSK
9) Network Name : OnePlus 3
       signal Strength : -70
       MAC Address : C0:EE:FB:DB:BD:12
       Encryption type: WPA2_PSK
10) Network Name : eduroam
       signal Strength : -83
       MAC Address : E8:65:49:22:C6:B3
       Encryption type: WPA2_ENTERPRISE
11) Network Name : Unice-HotSpot
       signal Strength : -83
       MAC Address : E8:65:49:22:C6:B0
       Encryption type: Open
12) Network Name : Unice-HotSpot
       signal Strength : -86
       MAC Address : 54:A2:74:57:D3:90
       Encryption type: Open
13) Network Name : Unice-HotSpot
       signal Strength : -87
       MAC Address : 58:97:1E:ED:44:92
       Encryption type: Open
14) Network Name : eduroam
       signal Strength : -87
       MAC Address : 54:A2:74:57:D3:93
       Encryption type: WPA2_ENTERPRISE
15) Network Name : eduroam
       signal Strength : -90
       MAC Address : 58:97:1E:ED:44:93
       Encryption type: WPA2_ENTERPRISE
16) Network Name : eduroam
       signal Strength : -92
       MAC Address : 58:97:1E:ED:5B:43
       Encryption type: WPA2_ENTERPRISE

```

### Connexion

On utilise : wificonnect.ino

```
python3 readserial.py
WiFi connected
IP address: 192.168.43.227
MAC address: 30:AE:A4:86:62:F4

WiFi connected
IP address: 192.168.43.227
MAC address: 30:AE:A4:86:62:F4

WiFi connected
IP address: 192.168.43.227
MAC address: 30:AE:A4:86:62:F4

```

### Sockets

```
< on a pas le temps >
 -------------------
    \                                  ___-------___
     \                             _-~~             ~~-_
      \                         _-~                    /~-_
             /^\__/^\         /~  \                   /    \
           /|  O|| O|        /      \_______________/        \
          | |___||__|      /       /                \          \
          |          \    /      /                    \          \
          |   (_______) /______/                        \_________ \
          |         / /         \                      /            \
           \         \^\\         \                  /               \     /
             \         ||           \______________/      _-_       //\__//
               \       ||------_-~~-_ ------------- \ --/~   ~\    || __/
                 ~-----||====/~     |==================|       |/~~~~~
                  (_(__/  ./     /                    \_\      \.
                         (_(___/                         \_____)_)

```

### Un client Http

On utilise :

- wifihttp_getonly0.ino

```

IOT_TD$ python3 readserial.py
Connected to local Wifi
WiFi connected
IP address: 192.168.43.227
MAC address: 30:AE:A4:86:62:F4
Received data ...
200
{
  "origin": "37.173.133.223"
}

```

- wifihttp_getonly1.ino

```
IOT_TD$ python3 readserial.py
Attempting to connect ..
Connected to local Wifi
WiFi connected
IP address: 192.168.43.227
MAC address: 30:AE:A4:86:62:F4


connecting...
HTTP/1.1 200 OK
Connection: close
Server: gunicorn/19.9.0
Date: Wed, 06 Feb 2019 14:16:11 GMT
Content-Type: application/json
Content-Length: 31
Access-Control-Allow-Origin: *
Access-Control-Allow-Credentials: true
Via: 1.1 vegur

{
  "origin": "37.173.52.71"
}


```

### Un autre client Http

https://github.com/espressif/arduino-esp32/tree/master/libraries/HTTPClient/examples/HTTPClient/BasicHTTPClient.ino

```
IOT_TD$ python3 readserial.py
[SETUP] WAIT 2...
[SETUP] WAIT 1...





[HTTP] begin...
[HTTP] GET...
[HTTP] GET... code: 200
{
  "origin": "37.173.133.223"
}

```
