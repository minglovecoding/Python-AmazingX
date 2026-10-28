#启动程序、创建主窗口，把网格界面放进去
import tkinter as tk
from CellMap import CellMap


class CAWrapper(tk.Tk):
    def __init__(self):
        super().__init__()
        self.CELLSIZE = 24  #每个格子的显示边长为 24 像素
        self.FRAMESIZE = 480  # 20 x 20 = 400 living cells
        self.BTNSPACE = 63
        self.HRZSPACE = 8
        self.title("Prisoner's Dilemma")
        self.resizable(False, False)
        self.cell_map = CellMap(
            self, self.FRAMESIZE // self.CELLSIZE,
            self.FRAMESIZE // self.CELLSIZE, self.CELLSIZE)
        self.cell_map.pack(anchor="nw")
        self.update_idletasks()
        width = self.winfo_reqwidth()
        height = self.winfo_reqheight()
        x = max(0, (self.winfo_screenwidth() - width) // 2)  #将窗口居中
        y = max(0, (self.winfo_screenheight() - height) // 2)
        self.geometry(f"{width}x{height}+{x}+{y}")
        self.protocol("WM_DELETE_WINDOW", self.close)  #关闭窗口时的操作

    def close(self):
        self.cell_map.stop()
        self.cell_map.after_cancel(self.cell_map.after_id)
        self.destroy()


if __name__ == "__main__":
    app = CAWrapper()
    app.mainloop()
