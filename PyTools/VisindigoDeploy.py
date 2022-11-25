from PySide2.QtWidgets import QApplication
import sys

from VisindigoResource.VisindigoLanguage import *
if __name__  == "__main__":
    app = QApplication(sys.argv)
    w = CELanguageCreator()
    w.show()
    sys.exit(app.exec_())
