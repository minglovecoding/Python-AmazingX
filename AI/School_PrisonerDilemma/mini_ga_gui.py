import tkinter as tk
from GA import GA


class Demo(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("GA animation demo")
        self.model = GA(rows=10, cols=10, length=20, mutRate=0.03, seed=42)
        self.size = 24
        self.running = False
        self.after_id = None

        controls = tk.Frame(self)
        controls.pack()
        tk.Button(controls, text="Start", command=self.start).pack(side="left")
        tk.Button(controls, text="Stop", command=self.stop).pack(side="left")
        tk.Button(controls, text="Step", command=self.step).pack(side="left")
        self.status = tk.StringVar()
        tk.Label(self, textvariable=self.status).pack()
        self.canvas = tk.Canvas(self, width=240, height=240, highlightthickness=0)
        self.canvas.pack()
        self.protocol("WM_DELETE_WINDOW", self.close)
        self.draw()

    def draw(self):
        self.canvas.delete("all")
        for row in range(self.model.rows):
            for col in range(self.model.cols):
                code = self.model.pop[row][col].getCode()
                ratio = code.count("C") / len(code)
                red = round(230 * (1 - ratio) + 35 * ratio)
                green = round(55 * (1 - ratio) + 190 * ratio)
                color = f"#{red:02x}{green:02x}46"
                x, y = col * self.size, row * self.size
                self.canvas.create_rectangle(
                    x, y, x + self.size, y + self.size,
                    fill=color, outline="white")
        self.status.set(
            f"Generation: {self.model.generation} | C: {self.model.cooperation():.1%}")

    def step(self):
        # 演示约定：单步先暂停，再推进一次。
        self.stop()
        self.model.createNewPop()
        self.draw()

    def start(self):
        if self.running:
            return  # 防止重复 Start 建立多条刷新链
        self.running = True
        self.tick()

    def tick(self):
        self.after_id = None
        if not self.running:
            return
        self.model.createNewPop()
        self.draw()
        self.after_id = self.after(200, self.tick)

    def stop(self):
        self.running = False
        if self.after_id is not None:
            self.after_cancel(self.after_id)
            self.after_id = None

    def close(self):
        self.stop()
        self.destroy()


if __name__ == "__main__":
    app = Demo()
    app.mainloop()