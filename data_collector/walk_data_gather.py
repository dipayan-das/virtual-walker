import serial as sr
import os
import pandas as pd
from pynput.mouse import Listener


class serialProcessing:
    sensor = "IMU"
    serial_port = 'COM4'
    baud_rate = 115200
    source_path = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    mouse_click_interrupt = False

    def __init__(self, **kwargs):
        self.sensor = kwargs.get("sensor", serialProcessing.sensor)
        self.serial_port = kwargs.get("serial_port", serialProcessing.serial_port)
        self.baud_rate = kwargs.get("baud_rate", serialProcessing.baud_rate)
        self.path = os.path.join(serialProcessing.source_path, self.sensor, "text.csv")

    def serialPort(self):
        return sr.Serial(self.serial_port, self.baud_rate)

    def serialRead(self):
        serial_port = self.serialPort()
        data_frame_dictionary = {}
        while serial_port.is_open and not serialProcessing.mouse_click_interrupt:
            try:
                temp_data_frame_dictionary = serial_port.readline().decode('Ascii')
                if len(temp_data_frame_dictionary) > 50:
                    data_frame_dictionary[str(pd.Timestamp.now())] = str(" ") + str(temp_data_frame_dictionary)
            except:
                print("Connection interrupted!!")
                break
        data_frame = pd.DataFrame.from_dict(self.chopSerialData(data_frame_dictionary), orient='index',
                                            columns=['acc_X', 'acc_Y', 'acc_Z'])
        print(data_frame)

    @staticmethod
    def chopSerialData(data):
        for n in list(data.keys()):
            if data[n][1] != 'A':
                del data[n]
            else:
                split_list = data[n].split(" ")
                data[n] = [split_list[3], split_list[5], split_list[8]]
        return data


def on_scroll(x, y, dx, dy):
    serialProcessing.mouse_click_interrupt = True
    print("scrolled")


def checkMouseEvent():
    with Listener(on_scroll=on_scroll, ) as listener:
        listener.join()
