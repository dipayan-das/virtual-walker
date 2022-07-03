from data_collector.walk_data_gather import serialProcessing, checkMouseEvent
from threading import Thread

if __name__ == '__main__':
    adafruit_IMU = serialProcessing(sensor="LSM9DS1", serial_port='COM4', baud_rate=115200)
    Thread(target=checkMouseEvent).start()
    Thread(target=adafruit_IMU.serialRead).start()
