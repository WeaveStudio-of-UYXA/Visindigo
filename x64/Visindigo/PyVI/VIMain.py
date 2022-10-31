import sys
from PyVI.VICore import VITrans



class VIMain:
    def __init__(this):
        this.VITrans = VITrans.VITransClient()
        VITrans.GVITrans = this.VITrans
        this.main()
        this.VITrans.__del__()
