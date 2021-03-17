# -*- coding: utf-8 -*-
import paho.mqtt.client as mqtt
from time import sleep

class Connection():
	def __init__(self, addr, port=1883):
		print("Connecting to MqTT Broker at port: "+ str(port))
		self.client = mqtt.Client()
		self.connected = False
		self.client.on_connect = self.on_connect
		self.client.on_message = self.on_message
		self.host = addr
		self.port = port
		try:
			self.client.connect(addr, port)
			self.connected = True
		except Exception as e:
			print("MqTT Connection Error:")
			print(e)

	def on_message(self, client, userdata, message):
		msg = bytes(message.payload)
		print("message received: ", message)
		print("message topic: ", message.topic)

	def on_connect(self, client, userdata, flags, rc):
		print("MqTT Connection Established to "+self.host+":"+str(self.port)+"!")
		

	def int_to_bytes(x):
		return int(x).to_bytes(2, byteorder='little', signed=False)

	def send_color(self, cross, arm, hex_color):
		if not self.connected:
			return
		r = int(hex_color[1:3], 16)
		g = int(hex_color[3:5], 16)
		b = int(hex_color[5:], 16)
		self.client.publish("Cross"+str(cross)+"/downstream/color/"+str(arm), bytes([r, g, b]))

	def send_on(self, cross, arm, on):
		if not self.connected:
			return
		self.client.publish("Cross"+str(cross)+"/downstream/on/"+str(arm), bytes([on]))

	def send_angle(self, cross, angle):
		if not self.connected:
			return
		self.client.publish("Cross"+str(cross)+"/downstream/angle", Connection.int_to_bytes(angle))

	def handle(self):
		if not self.connected:
			return
		self.client.loop_start()

image1_conn = Connection("localhost")
image2_conn = Connection("localhost", 1884)