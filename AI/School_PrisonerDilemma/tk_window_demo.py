"""
import tkinter as tk

root = tk.Tk()
root.title("Tkinter demo")
label = tk.Label(root, text="Hello, GUI!")
label.pack(padx=20, pady=20)
root.mainloop()
"""

import tkinter as tk

root = tk.Tk()
root.title("Counter")
count = 0
status = tk.StringVar(value="Count: 0")


def add_one():
    global count
    count += 1 
    status.set(f"Count: {count}")


tk.Label(root, textvariable=status).pack(padx=20, pady=10)
tk.Button(root, text="Add one", command=add_one).pack(pady=10)
root.mainloop()