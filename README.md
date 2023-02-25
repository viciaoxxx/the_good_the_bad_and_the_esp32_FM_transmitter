Modified version for ESP32 TTGO.
Current one includes battery, antenna amplifier, encoder and power switch.
Encoder GPIO: CLK 27, S2 26, S1 25
Antenna output GPIO 44

![WhatsApp Image 2023-02-25 at 11 54 21](https://user-images.githubusercontent.com/59579900/221355404-1c649114-44eb-4622-8bc8-9ad37a6649e3.jpeg)
![WhatsApp Image 2023-02-25 at 11 06 41](https://user-images.githubusercontent.com/59579900/221355387-6fd99fde-617f-4788-8184-12a6ff769a88.jpeg)

Original repo:
# the_good_the_bad_and_the_esp32_FM_transmitter
a basic low quality ESP32 FM trasnmittor 
THIS IS A HEADS UP, using RF filters are a must when using this project or angry HAM operators will call the cops on you , i am not lieable if it happens
this project was inspered by bitluni's AM transmittor video on youtube: https://www.youtube.com/watch?v=lRXHd3HNzEo
if you want a custom audio header here is web based audio to header convevetor :https://bitluni.net/am-radio-transmitter that bitluni made

from personal exprince i get the harmonics up to 130Mhz when "7Mhz" PWM signal was used at 50% duty cycle and i tone to frequncy 101MHz to listion to it on the FM radio but using an SDR would make it allot easier to find the harmonics 


one version uses a pre made audio header while ESP32 FM ADC uses an ADC so you can connect your phone to it to play music(a pre amp is needed as the build in ADC is not sensitive enough)
