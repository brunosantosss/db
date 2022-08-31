# Bibliotecas
import pyaudio
import audioop  
from kivy.app import App
from kivy.lang import Builder
from kivy.uix.boxlayout import BoxLayout
from kivy.clock import Clock

GUI = Builder.load_file("screen.kv")

###################################### 

p = pyaudio.PyAudio()
WIDTH = 2
RATE = int(p.get_default_input_device_info()['defaultSampleRate'])
DEVICE = p.get_default_input_device_info()['index']
rms = 0
print(p.get_default_input_device_info())

def callback(in_data, frame_count, time_info, status):
    global rms
    rms = audioop.rms(in_data, WIDTH) / 32767
    return in_data, pyaudio.paContinue

stream = p.open(format=p.get_format_from_width(WIDTH),
                input_device_index=DEVICE,
                channels=1,
                rate=RATE,
                input=True,
                output=False,
                stream_callback=callback)

stream.start_stream()

###################################### 

class ChangedB(BoxLayout):
    def __init__(self, *args):
        super().__init__(*args)
        Clock.schedule_interval(self.UpdatedB, 0.1)

    def UpdatedB(self, *args):
        db = int(40 * (10 ** rms))
        self.ids.decibeis.text = f"{str(db)} dB"

        if db <= 40:
            self.ids.img.source = "../verde.jpg"
        elif db >= 41 and db <= 70:
            self.ids.img.source = "../amarelo.jpg"
        elif db >= 71:
            self.ids.img.source = "../vermelho.jpg"

class MyApp(App):
    def build(self):
        return ChangedB()

MyApp().run()

stream.stop_stream()
stream.close()

p.terminate()
