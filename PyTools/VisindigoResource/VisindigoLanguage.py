#这玩意，理论上所有CEL格式，也就是遵从"键:值"的格式的文件都可以用这个来读取

from PySide2.QtCore import *
from PySide2.QtGui import *
from PySide2.QtWidgets import *

class CELanguageCreator(QWidget):
    CurrentLayout:QGridLayout
    NewCELProjectButton:QPushButton
    LoadRawFileButton:QPushButton
    LoadTranslationFileButton:QPushButton
    SaveTranslationFileButton:QPushButton
    SaveRawFileButton:QPushButton
    EditWidget:QTableView
    Data:QStandardItemModel
    def __init__(this, parent:QWidget = None):
        super().__init__(parent)
        this.setMinimumSize(800, 600)
        this.setWindowTitle("CommonEdit Language Creator")
        this.NewCELProjectButton = QPushButton("New CEL Project", this)
        this.LoadRawFileButton = QPushButton("Load Raw File", this)
        this.LoadTranslationFileButton = QPushButton("Load Translation File", this)
        this.SaveTranslationFileButton = QPushButton("Save Translation File", this)
        this.SaveRawFileButton = QPushButton("Save Raw File", this)
        this.NewCELProjectButton.clicked.connect(this.newCELProject)
        this.LoadRawFileButton.clicked.connect(this.loadRawFile)
        this.LoadTranslationFileButton.clicked.connect(this.loadTranslationFile)
        this.SaveTranslationFileButton.clicked.connect(this.saveTranslationFile)
        this.SaveRawFileButton.clicked.connect(this.saveRawFile)
        this.EditWidget = QTableView(this)
        this.Data = QStandardItemModel(this)
        this.EditWidget.setModel(this.Data)
        
        this.CurrentLayout = QGridLayout(this)
        this.CurrentLayout.addWidget(this.LoadRawFileButton, 0, 0, 1, 1)
        this.CurrentLayout.addWidget(this.LoadTranslationFileButton, 0, 1, 1, 1)
        this.CurrentLayout.addWidget(this.SaveTranslationFileButton, 0, 2, 1, 1)
        this.CurrentLayout.addWidget(this.NewCELProjectButton, 1, 0, 1, 1)
        this.CurrentLayout.addWidget(this.SaveRawFileButton, 1, 1, 1, 1)
        this.CurrentLayout.addWidget(this.EditWidget, 2, 0, 1, 3)

    def newCELProject(this):
        if this.Data.rowCount() > 0:
            if QMessageBox.warning(this, "Warning", "Data is not empty, are you sure to continue?", QMessageBox.Yes | QMessageBox.No) == QMessageBox.No:
                return
        # clear data
        this.Data.clear()
        this.Data.setHorizontalHeaderLabels(["Key","Raw","Translation"])
        this.Data.appendRow([QStandardItem("CE_Init_Hello_World"), QStandardItem("Hello world!"), QStandardItem("你好，世界！")])
        this.setWindowTitle("CommonEdit Language Creator - New Project")
        
    def loadRawFile(this):
        fileName, _ = QFileDialog.getOpenFileName(this, "Open Raw File", "", "CommonEdit Language File (*.celang)")
        if fileName:
            #if data is not empty, create a warning dialog
            if this.Data.rowCount() > 0:
                if QMessageBox.warning(this, "Warning", "Data is not empty, are you sure to continue?", QMessageBox.Yes | QMessageBox.No) == QMessageBox.No:
                    return
            # clear data
            this.Data.clear()
            this.Data.setHorizontalHeaderLabels(["Key","Raw","Translation"])
            with open(fileName, "r", encoding="utf-8") as f:
                for line in f.readlines():
                    if line[0] == "" or line[0] == "#" or line[0] == "\n":
                        continue
                    key, value = line.split(":", 1)
                    this.Data.appendRow([QStandardItem(key), QStandardItem(value.replace("\n","")), QStandardItem("")])
            this.setWindowTitle("CommonEdit Language Creator - " + fileName)

    def loadTranslationFile(this):
        fileName, _ = QFileDialog.getOpenFileName(this, "Open Translation File", "", "CommonEdit Language File (*.celang)")
        if fileName:
            with open(fileName, "r", encoding="utf-8") as f:
                for line in f.readlines():
                    if line[0] == "" or line[0] == "#" or line[0] == "\n":
                        continue
                    key, value = line.split(":", 1)
                    for i in range(this.Data.rowCount()):
                        if this.Data.item(i, 0).text() == key:
                            this.Data.item(i, 2).setText(value.replace("\n",""))
                            break

    def saveTranslationFile(this):
        fileName, _ = QFileDialog.getSaveFileName(this, "Save Translation File", "", "CommonEdit Language File (*.celang)")
        if fileName:
            #if data is empty, create a warning dialog
            if this.Data.rowCount() == 0:
                QMessageBox.warning(this, "Warning", "Data is empty, nothing to save.")
                return
            with open(fileName, "w", encoding="utf-8") as f:
                for i in range(this.Data.rowCount()):
                    f.write(this.Data.item(i, 0).text() + ":" + this.Data.item(i, 2).text() + "\n" )

    def saveRawFile(this):
        fileName, _ = QFileDialog.getSaveFileName(this, "Save Raw File", "", "CommonEdit Language File (*.celang)")
        if fileName:
            #if data is empty, create a warning dialog
            if this.Data.rowCount() == 0:
                QMessageBox.warning(this, "Warning", "Data is empty, nothing to save.")
                return
            with open(fileName, "w", encoding="utf-8") as f:
                for i in range(this.Data.rowCount()):
                    f.write(this.Data.item(i, 0).text() + ":" + this.Data.item(i, 1).text() + "\n" )
        
