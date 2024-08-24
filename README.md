<h1 style="text-align: center;">Progress-Bar</h1>

![](img.webp)

<h3>About the Project</h3>
An implementation of a progress bar. The progress bar implemented by this project can accurately change its size even if the dimensions of the terminal window running the program changes 

There are two components in this project 

- Writer
- Progress bar

The writer allows you to send your data to the progess bar through functions offered by the program.
<br>
The progress bar reads the data sent and then shows the appropriate progress on the bar
<br>
Writer functions offered:
```
    - init
    - get_data
    - finish
```

Progess bar functions offered:
```
    - progress_bar
```
This project has been implemented in C and as such can only be used by C projects

A sample program is available in the example directory

<h3>Getting Started</h3>
1. Copy the project directory to your project
<br>
2. Include the header files in your program

```
    - progress_bar.h
    - writer.h
    - struct.h
```
<br>
3. Run the `progress_bar` function thorugh a thread
<br>
4. Call the writer functions in the following order

```
    - init
    - get_data
    -finish
```
<br>
5. `init` will initialize the shared memory buffer and return a pointer to it. Pass the max data value to it
<br>
6. Pass the current data value to `get_data` for it reflect the progress on the progress bar
<br>
7. `finish` should be called at the end of your program to detach from the shared memory
<br>
8. Cleaning and handling of thread used to run progress bar should be handled by your program
