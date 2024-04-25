README.TXT

Instructions for Compiling and Running the Program:

Using the mcb32tools in msys terminal:
    1. In bash navigate to the folder with the code to compile and install
    2. Enter the cross compile environment . /opt/mcb32tools/environment (Important space after the dot)
    3. Connect your chipkit device
    4. In Windows Device Manager, under "Ports (COM & LTP)" look for your device, and note the COM number (ex COM4)
    5. Compile your code with 'make' (dont use the '')
    6. Install your code with 'make install TTYDEV=/dev/ttySX' (dont use the ''), replace the X with the COM number for your device (ex TTYDEV=/dev/ttyS4)

Additional Notes:
   - Ensure that you have the necessary dependencies installed (if any) before compiling the program.
   - If you encounter any errors during compilation or execution, refer to the error messages for troubleshooting.
   - For more detailed information on usage, consult the documentation or comments within the source code files.
