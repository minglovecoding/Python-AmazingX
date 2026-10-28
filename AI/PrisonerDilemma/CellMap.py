#管理界面和动画：显示细胞、处理按钮和鼠标操作，调用算法推进下一代，并刷新颜色。
#点击 Start → 定时执行 _tick() → 调用算法 → 绘制网格 → 更新文字。
import tkinter as tk
from tkinter import messagebox
from GA import GA
from datetime import datetime

try:
    from PIL import Image, ImageDraw, ImageTk
    PIL_AVAILABLE = True
except ImportError:
    PIL_AVAILABLE = False


class CellMap(tk.Frame):  #CellMap 是一个容器，不只是一个格子
    """School cellular-automaton GUI adapted to spatial prisoner dilemma."""

    def __init__(self, parent, x_dim, y_dim, cell_size):
        super().__init__(parent, bg="lightgray")

        self.gen_count = 0
        self.gen_skip = 1  #一次刷新先连续计算n代，再显示最后一代；中间n-1代仍计算，只是不画出来
        self.size = cell_size
        self.rows = x_dim
        self.cols = y_dim
        self.is_running = False
        self.mouse_draw = True
        self.mouse_coords = (-1, -1)

        # Match the Java speed options as closely as practical.
        self.speeds = [900, 400, 100, 0]
        self.speed_index = 2

        self.strategy_length_text = tk.StringVar(value="20")
        self.mutation_text = tk.StringVar(value="0.03")
        self.gen_skip_text = tk.StringVar(value="1")

        self.ga = GA(self.rows, self.cols, length=20, mutRate=0.03)
        self.cells = self.ga.pop

        self._build_controls()  #创建按钮与输入框

        #创建画布并注册鼠标操作
        self.canvas = tk.Canvas(
            self,
            width=self.cols * self.size,
            height=self.rows * self.size,
            bg="white",
            highlightthickness=0,
        )
        self.canvas.grid(row=1, column=0, rowspan=8, columnspan=6, sticky="nw",
                         padx=1, pady=1)
        #鼠标动作
        self.canvas.bind("<Button-1>", self.on_mouse_press)
        self.canvas.bind("<B1-Motion>", self.on_mouse_drag)
        self.canvas.bind("<Motion>", self.on_mouse_move)

        self._render()
        self._update_labels()
        self.after_id = self.after(self.speeds[self.speed_index], self._tick)

    def _build_controls(self):  
        tk.Button(self, text="Start", command=self.start).grid(row=0, column=0, padx=2)
        tk.Button(self, text="Stop", command=self.stop).grid(row=0, column=1, padx=2)
        tk.Button(self, text="Reset", command=self.clear).grid(row=0, column=2, padx=2)
        self.speed_button = tk.Button(self, text="Speed = Fast", command=self.change_speed)
        self.speed_button.grid(row=0, column=3, padx=2)

        self.generations_label = tk.Label(self, text="Generations: 0", bg="lightgray")
        self.generations_label.grid(row=0, column=4, padx=10)
        self.mouse_label = tk.Label(self, text="Mouse off-grid", bg="lightgray")
        self.mouse_label.grid(row=0, column=5, padx=10)

        tk.Button(self, text="Save Picture", command=self.save_picture).grid(
            row=1, column=6, sticky="ew", padx=4
        )

        tk.Label(self, text="Skip Generations", bg="lightgray").grid(
            row=2, column=6, sticky="ew", padx=4
        )
        tk.Entry(self, textvariable=self.gen_skip_text, width=8).grid(
            row=3, column=6, sticky="ew", padx=4
        )

        tk.Label(self, text="Strategy Length (20/50)", bg="lightgray").grid(
            row=4, column=6, sticky="ew", padx=4
        )
        tk.Entry(self, textvariable=self.strategy_length_text, width=8).grid(
            row=5, column=6, sticky="ew", padx=4
        )

        tk.Label(self, text="Mutation (per child)", bg="lightgray").grid(
            row=6, column=6, sticky="ew", padx=4
        )
        tk.Entry(self, textvariable=self.mutation_text, width=8).grid(
            row=7, column=6, sticky="ew", padx=4
        )

        tk.Label(self, text="Red = all D; Green = all C", bg="lightgray").grid(
            row=9, column=0, columnspan=6, sticky="w")
        tk.Label(self, text="Click/drag: set all C or all D", bg="lightgray").grid(
            row=10, column=0, columnspan=6, sticky="w")

        # Press Enter in a field to apply its value.
        for widget in self.winfo_children():
            if isinstance(widget, tk.Entry):
                widget.bind("<Return>", lambda event: self.update_rules())

    def update_rules(self): #进化输入参数
        # 所有输入先校验成功，再统一应用。
        try:
            skip = int(self.gen_skip_text.get())
            length = int(self.strategy_length_text.get())
            mutation = float(self.mutation_text.get())
            if skip < 1 or length not in (20, 50) or not 0 <= mutation <= 1:
                raise ValueError
        except ValueError:
            messagebox.showerror(
                "Invalid value", "Skip must be positive; length 20 or 50; mutation 0 to 1.")
            return False
        self.gen_skip = skip
        if length != self.ga.length:
            self.ga = GA(self.rows, self.cols, length=length, mutRate=mutation)
            self.cells = self.ga.pop
            self.gen_count = 0
        else:
            self.ga.mutProb = mutation
        self._render()
        self._update_labels()
        return True

    def start(self):
        if self.update_rules():
            self.is_running = True

    def stop(self):
        self.is_running = False

    def clear(self):
        # 所有细胞始终存活，原 Clear 改为重新随机初始化。
        self.is_running = False
        if not self.update_rules():
            return
        self.ga.initialize()
        self.cells = self.ga.pop
        self.gen_count = 0
        self._render()
        self._update_labels()

    def change_speed(self):
        self.speed_index = (self.speed_index + 1) % len(self.speeds)
        labels = ["Slow", "Med", "Fast", "Whoa"]
        self.speed_button.config(text=f"Speed = {labels[self.speed_index]}")

    def count_neighbors(self, row, col):
        # 保留学校接口；这里每格始终有 8 个存活邻居。
        return len(list(self.ga.neighbors(row, col)))

    def update_cells(self):
        for _ in range(self.gen_skip):
            self.ga.createNewPop()
        self.cells = self.ga.pop
        self.gen_count = self.ga.generation

    @staticmethod
    def cell_color(cell):#根据合作比例算颜色
        cooperation = cell.code.count("C") / len(cell.code)
        red = round(230 * (1 - cooperation) + 35 * cooperation)
        green = round(55 * (1 - cooperation) + 190 * cooperation)
        return f"#{red:02x}{green:02x}46"

    def _render(self):  #绘制网格
        self.canvas.delete("all")
        for row in range(self.rows):
            y1 = row * self.size
            for col in range(self.cols):
                x1 = col * self.size
                self.canvas.create_rectangle(
                    x1, y1, x1 + self.size, y1 + self.size,
                    fill=self.cell_color(self.cells[row][col]), outline="lightgray")

    def _update_labels(self):  #更新文字
        self.generations_label.config(
            text=f"Generations: {self.gen_count} | C: {self.ga.cooperation():.1%}")
        row, col = self.mouse_coords
        if 0 <= row < self.rows and 0 <= col < self.cols:
            cell = self.cells[row][col]
            self.mouse_label.config(
                text=f"({row}, {col}) C: {cell.code.count('C') / len(cell.code):.0%} "
                     f"Score: {cell.fitness}")
        else:
            self.mouse_label.config(text="Mouse off-grid")

    def _cell_from_event(self, event):
        col = event.x // self.size
        row = event.y // self.size
        if 0 <= row < self.rows and 0 <= col < self.cols:
            return row, col
        return None

    def on_mouse_press(self, event):
        cell = self._cell_from_event(event)
        if cell is not None:
            row, col = cell
            self.mouse_coords = cell
            # 点击切换为全合作/全背叛，拖动时使用相同选择。
            self.mouse_draw = self.cells[row][col].code != "C" * self.ga.length
            self.cells[row][col].setCode(("C" if self.mouse_draw else "D") * self.ga.length)
            self.ga.calculateFitness()
            self._render()
            self._update_labels()

    def on_mouse_move(self, event):
        cell = self._cell_from_event(event)
        self.mouse_coords = cell if cell is not None else (-1, -1)
        self._update_labels()

    def on_mouse_drag(self, event):
        cell = self._cell_from_event(event)
        if cell is not None:
            row, col = cell
            self.cells[row][col].setCode(("C" if self.mouse_draw else "D") * self.ga.length)
            self.ga.calculateFitness()
            self.mouse_coords = cell
            self._render()
            self._update_labels()

    def save_picture(self):
        filename = f"prisoner_gen{self.gen_count}_{datetime.now().strftime('%Y%m%d_%H%M%S_%f')}.png"
        if PIL_AVAILABLE:
            image = Image.new("RGB", (self.cols * self.size, self.rows * self.size), "white")
            draw = ImageDraw.Draw(image)
            for row in range(self.rows):
                for col in range(self.cols):
                    x1, y1 = col * self.size, row * self.size
                    draw.rectangle(
                        [x1, y1, x1 + self.size - 1, y1 + self.size - 1],
                        fill=self.cell_color(self.cells[row][col]),
                    )
            image.save(filename)
            messagebox.showinfo("Saved", f"Picture saved as:\n{filename}")
        else:
            messagebox.showerror(
                "Pillow required",
                "To save a PNG, install Pillow by running:\npython3 -m pip install pillow",
            )

    #暂停后，_tick() 仍会被调用，只是不再推进 GA。点击 Start 也不会额外创建一条计时链，它只改变 is_running。
    def _tick(self):    #定时刷新函数，让模拟自动一代代运行
        if self.is_running:
            self.update_cells()
            self._render()
        self._update_labels()
        delay = self.speeds[self.speed_index]
        # Tkinter's after() delay must be positive.
        self.after_id = self.after(max(1, delay), self._tick)


if __name__ == "__main__":
    # 正式入口集中在 CAWrapper，避免两套窗口类相互覆盖。
    from CAWrapper import CAWrapper
    app = CAWrapper()
    app.mainloop()
