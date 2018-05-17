#!/usr/bin/env python3
import paho.mqtt.client as mqtt
import time
from pymongo import MongoClient


def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("TrashCan/#")

def on_message(client, userdata, msg):
    receiveTime= time.time()
    receiveTime= int(receiveTime)
    message=msg.payload.decode("utf-8")
    val = float(message)
    receiveTime=time.time()
    db.trash_bins.update({'name':"Sasana Olahraga Ganesha"}, {'$push':{"history":{"time": receiveTime, "volume":val}}})
    db.trash_bins.update({'name':"Sasana Olahraga Ganesha"}, {'$set':{"lastmodified": receiveTime, "volume":val}})


# Set up client for MongoDB
client = mqtt.Client()
client.on_connect = on_connect
mongoClient=MongoClient("mongodb+srv://teo-wijaya:imka2018@trashcan-a5b2z.mongodb.net/test")
db=mongoClient.SensorData

# Initialize the client that should connect to the Mosquitto broker

client.on_message = on_message
client.connect("127.0.0.1", 1883, 60)

# Blocking loop to the Mosquitto broker
client.loop_forever()