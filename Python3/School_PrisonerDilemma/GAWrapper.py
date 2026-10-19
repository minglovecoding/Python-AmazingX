"""Alternative entry point, replacing the school's target-text GA demo."""
from CAWrapper import CAWrapper


def main():
    app = CAWrapper()
    app.mainloop()


if __name__ == '__main__':
    main()
