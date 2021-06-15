import os

file_fd = os.open(r"boot.img", os.O_RDONLY | os.O_BINARY)
data = os.read(file_fd, os.stat(r"boot.img").st_size)
os.close(file_fd)

usb_fd = os.open(r"F:\\", os.O_WRONLY | os.O_BINARY)
os.write(usb_fd, data)
os.close(usb_fd)