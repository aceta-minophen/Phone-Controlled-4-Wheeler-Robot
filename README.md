# Phone Controlled (joystick) Robot Car Project

An IoT based project using Wi-Fi Module and MIT App Inventor with intuitive control. A 4 wheeler robot car which runs smoothly using the joystick controls from the app on your phone!

![image](https://user-images.githubusercontent.com/87569188/150325641-e0a42600-f4db-40e1-9b8c-95a69af98902.png)

> A detailed documentation for this can be found in the [Arduino Project Hub](https://create.arduino.cc/projecthub/suk_/phone-controlled-robot-car-using-wi-fi-module-6c8146?ref=user&ref_id=1881187&offset=0)



## About 📝
This is a fairly simple IoT project with a lot of learning opportunities.

I'll begin with a detailed overview of the steps one should go through before directly diving into creating the final product. While there was already a lot of material on DIY robot cars available on the internet, a lot of painstaking days went by without any significant progress while working on this particular project, especially since I'm a fair beginner in the subject of IoT. So, I bring to you a step-by-step guide for how _I_ successfully got through with this project and all the issues I ran into (and obviously how to overcome them).

## Components Used 🧮
First make sure to acquire all the hardware components listed below:

| Component  | Amount  | Utility |
|---| :-: |---|
| Arduino Uno | x1 | Microcontroller |
| NodeMCU ESP8266 Board | x1 | WiFi Module |
| L298N Dual H-Bridge Motor Driver | x2 | Controlling 4 motors (2 motors connected to each motor driver) |
| DC Motors (9V/12V) | x4 | For driving 4 wheels |
|Lithium Polymer Battery 11.1V | x1 | Power supply with desired current output |

## Schematics 🏗️

Make the connections between your components as follows:
### Interfacing L298n motor driver with Arduino and Motors
![image](https://user-images.githubusercontent.com/87569188/150327415-b83a9a47-2d90-4fa4-ad04-2b6224777e03.png)
> We direct the power to the Arduino via the L298n motor driver.

### Speed and Direction Control Circuit
![image](https://user-images.githubusercontent.com/87569188/150327546-5bdd881e-8e14-4732-b5bf-3c5ae56b66f8.png)

> I used 2 motor drivers to control my 4 motors. Due to a lack of GPIO pins on my Arduino board, I couldn't possibly write a program to control all 4 of the motors separately. Therefore, the only solution to my problem was to connect my two motor drivers in parallel. I appointed one motor driver for the rear and another for the front in my 4WD. So, my arrangement was such that when given a particular input, both the left motors (of both motor drivers) would undergo the same change (in speed and direction). As with the right motors in both front and rear.

### Interfacing NodeMCU with Arduino
![image](https://user-images.githubusercontent.com/87569188/150327943-6b40c113-36ae-4e44-ab6f-9235e8e20f0b.png)
> To power the NodeMCU, just connect the 3V3 pin on the Wi-Fi module to 3.3V port on Arduino.

## Step-by-Step Guide 👩‍💻

### 1. Arduino Uno and the motor drivers
I chose to work with L298N motor driver modules (because that is what the internet recommended). A detailed overview of how the motor drivers work and how to interface them with your Arduino board has been provided [here](https://create.arduino.cc/projecthub/ryanchan/how-to-use-the-l298n-motor-driver-b124c5). This webpage really helped me a lot in getting started with making my RC car.
#### Problems You Might Face 🤔

| Issues | Solution |
|---|---|
| Motors working with direct supply but not after connecting to motor driver | This could be because of **low voltage supply or the motors are drawing more current than being supplied**. First of all, make sure that your voltage supply is greater than 7V. Anything less than 6.5V may cause the motor driver to start fluctuating (flickering LED is a symptom of this) and the motors will not turn. Secondly, you need a battery which can supply current as required. |
| Both motors not rotating with the same speed | This again happens due to **lack of required current supply**. Your battery may be giving a voltage output of 12V, but one of the connected motors still might run at half the speed of the other, which will cause uneven movement after the final assembly is done. At least a 5A current supply would be enough for all 4 motors to run smoothly. |

> Personally, I used 11.1V 3S 2200mAh 25/30C Li-Po Rechargeable Battery with XT60 connector. This was pretty expensive and I'd only recommend this to you if you plan on using the same for other projects (it is awesome for drone applications!) as I had to purchase more necessary accessories for it like the Male XT60 to Female JST adapter (to use the battery with jumper wires) and a Li-Po charger obviously. The main goal is to achieve a sufficiently large current supply, so you can look for a battery to satisfy your requirements.

## Code 💻
The [code](https://github.com/aceta-minophen/Makeshift-Gimbal/blob/main/gimbal_code.ino) is given above and the [project report](https://github.com/aceta-minophen/Makeshift-Gimbal/blob/main/Drone%20Report.pdf) for this workshop can also be found.

## The Setup 🛠️
![image](https://user-images.githubusercontent.com/87569188/150323228-532ed5e7-e3b9-4c45-b6a4-4ad6227e4be3.png)

As I didn't have a 3D printer available for physically implimenting the gimbal, I used scrap thermocol ♻️ to join the two servos perpendicularly to make the two-axis gimbal.
> The following research paper discusses 3 axis gimbals with 3 degrees of freedom, namely: _roll, pitch_ & _yaw_. https://www.researchgate.net/publication/326995081_Three_Axis_Gimbal_Design_and_Its_Application

The gimbal we are creating will work on 2 axis and hence will only have 2 degrees of freedom: _roll_ & _pitch_.
