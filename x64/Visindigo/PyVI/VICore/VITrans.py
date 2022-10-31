from socket import *
import time

class VITransClient:
    def __init__(this):
        this.Size = 1024
        this.Host = '127.0.0.1'
        this.Port = 54179
        this.Address = (this.Host, this.Port)
        this.Socket = socket(AF_INET, SOCK_STREAM)
        this.Socket.connect(this.Address)
        print("PyVI:作为客户端建立通讯")

    def Send(this, str:str):
        this.Socket.send((str+"\n").encode("utf-8"))

    def Receive(this):
        return this.Socket.recv(this.Size).decode("utf-8")

    def __del__(this):
        this.Socket.close()

GVITrans:VITransClient = None
def printV(str):
    GVITrans.Send(str)

def inputV(str):
    GVITrans.Send(str)
    return GVITrans.Receive()