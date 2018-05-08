#!/usr/bin/env python3
import paho.mqtt.client as mqtt
import datetime
from pymongo import MongoClient


def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("TrashCan/#")

def on_message(client, userdata, msg):
    receiveTime=datetime.datetime.now()
    message=msg.payload.decode("utf-8")
    val = float(message)
    place = msg.topic[-2:-1]
    if(place == "01"):
        place= "Labtek V - 7602"
    print(str(receiveTime) + ": " + place + " " + str(val))
    post={"timestamp":receiveTime,"location":place,"height":val}
    result=db.TrashHeight.insert_one(post)
    #Step 4: Print to the console the ObjectID of the new document
    print('Created {0} '.format(result.inserted_id))

    #Step 5: Mengirim ke data analytics
    

# Set up client for MongoDB
mongoClient=MongoClient("mongodb+srv://teo-wijaya:imka2018@trashcan-a5b2z.mongodb.net/test")
db=mongoClient.SensorData

# Initialize the client that should connect to the Mosquitto broker
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect("127.0.0.1", 1883, 60)

# Blocking loop to the Mosquitto broker
client.loop_forever()