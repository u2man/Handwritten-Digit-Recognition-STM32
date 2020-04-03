HANDRITTEN RECOGNITION ON STM32F429

STM32F429 run STM32Cube.AI. Dataset for digit recognition using MNIST dataset in Keras.
STM32F429 will use LCD and touch screen. Calibration needed for the touch screen.

A box, 140x140 pixel is provided for writting area. The program will read this box area then convert it to 28x28 pixel. And save in a float type array with 28x28 (784) in size.This array then convert to 32 bit float and save to AI input data.
This input data then feed to AI network by call ai_run function.
The result the read from ai_output data and display to LCD.
IDE = STM32CubeIDE

video https://youtu.be/tkzUW-2sKvI
