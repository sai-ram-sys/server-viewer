import sys
import requests
from PyQt5.QtWidgets import (
    QApplication, QWidget, QPushButton, QVBoxLayout,
    QTableWidget, QTableWidgetItem, QMessageBox
)
from PyQt5.QtGui import QIcon

class ViewerApp(QWidget):
    def __init__(self):
        super().__init__()
        self.init_ui()

    def init_ui(self):
        self.setWindowTitle("Viewer with Refresh")
        self.setGeometry(100, 100, 600, 400)

        # Table to show data
        self.table = QTableWidget(self)
        self.table.setRowCount(0)
        self.table.setColumnCount(3)  # Adjust to match your data structure

        # Refresh button with icon (or just text if icon not available)
        self.refresh_button = QPushButton(" Refresh")
        try:
            self.refresh_button.setIcon(QIcon("refresh.png"))  # Optional icon
        except:
            pass  # Skip if icon not found
        self.refresh_button.clicked.connect(self.refresh_data)

        # Layout
        layout = QVBoxLayout()
        layout.addWidget(self.refresh_button)
        layout.addWidget(self.table)
        self.setLayout(layout)

        # Initial load
        self.refresh_data()

    def refresh_data(self):
        try:
            response = requests.get("http://127.0.0.1:8000/table", timeout=5)
            response.raise_for_status()
            data = response.json()  # Should be a list of dicts
            self.update_table(data)

        except requests.exceptions.RequestException as e:
            self.show_error_popup(str(e))

    def update_table(self, data):
        self.table.setRowCount(len(data))

        if data:
            self.table.setColumnCount(len(data[0]))
            self.table.setHorizontalHeaderLabels(data[0].keys())
        else:
            self.table.setColumnCount(0)

        for row, item in enumerate(data):
            for col, (key, value) in enumerate(item.items()):
                self.table.setItem(row, col, QTableWidgetItem(str(value)))

    def show_error_popup(self, error_message):
        msg_box = QMessageBox(self)
        msg_box.setIcon(QMessageBox.Critical)
        msg_box.setWindowTitle("Connection Error")
        msg_box.setText("Failed to connect to the server.")
        msg_box.setInformativeText(error_message)
        msg_box.setStandardButtons(QMessageBox.Retry | QMessageBox.Close)
        msg_box.setDefaultButton(QMessageBox.Retry)

        ret = msg_box.exec_()

        if ret == QMessageBox.Retry:
            self.refresh_data()
        elif ret == QMessageBox.Close:
            QApplication.quit()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    viewer = ViewerApp()
    viewer.show()
    sys.exit(app.exec_())
