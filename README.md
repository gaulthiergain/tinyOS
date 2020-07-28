# tinyOS
A small kernel to understand low-level concepts (work in progress). 

### What does it do?

The kernel contains the following features:
- It is loaded via GRUB legacy;
- It maps the first 3MB of memory;
- It manages paging (+ segmentation);
- It configures software and hardware interrupts;
- It sets up the keyboard for input;
- It writes some data to COM1 serial port;
- It logs what it's doing to the screen.

## Building

This code requires `bochs` or `qemu` as emulator(s).

- `cd ~/path/to/repo`
- `make`
- `make run` for qemu or `make run-bochs` for bochs

## References

- <http://www.jamesmolloy.co.uk/tutorial_html/
- <https://littleosbook.github.io/
- <https://github.com/mgadda/littleos>
- <https://github.com/MayankMurali/Creating-a-Little-Operating-System>
