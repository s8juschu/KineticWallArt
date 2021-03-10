# -*- coding: utf-8 -*-
import paho.mqtt.client as mqtt
from time import sleep

class Connection():
	client = mqtt.Client()
	connected = False

	def __init__(self, addr):
		print("Connecting to MqTT Broker")
		self.client.on_connect = Connection.on_connect
		self.client.on_message = Connection.on_message
		try:
			self.client.connect(addr)
			self.connected = True
		except Exception as e:
			print("MqTT Connection Error:")
			print(e)

	def on_message(client, userdata, message):
		msg = bytes(message.payload)
		print("message received: ", message)
		print("message topic: ", message.topic)

	def on_connect(client, userdata, flags, rc):
		print("MqTT Connection Established!")
		

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

conn = Connection("localhost")
