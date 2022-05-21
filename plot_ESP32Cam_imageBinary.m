% Real time data collection example
%
% This script is implemented as a function so that it can
%   include sub-functions
%
% This script can be modified to be used on any platform by changing the
% serialPort variable.
% Example:-
% On Linux:     serialPort = '/dev/ttyS0';
% On MacOS:     serialPort = '/dev/tty.KeySerial1';
% On Windows:   serialPort = "\\\\.\\COM5";
%
%To run:
%plot_cams()
%To reset ports: (if MATLAB still thinks they're busy)
%delete(instrfindall)
%
function plot_ESP32Cam_imageBinary
pkg load instrument-control
supportedinterfaces = instrhwinfo().SupportedInterfaces

if ! isempty(strfind (supportedinterfaces , "serial"))
    disp("Serial: Supported")
else
    disp("Serial: Unsupported")
endif
# Opens serial port ttyUSB1 with baudrate of 115200 (config defaults to 8-N-1)
s1 = serial("\\\\.\\COM3", 115200)
# Flush input and output buffers
srl_flush(s1);
set(s1, "baudrate", 115200) # Change baudrate
set(s1, "bytesize", 8)    # Change byte size (config becomes 5-N-1)
set(s1, "parity", "N")    # Changes parity checking (config becomes 5-E-1),
                          # possible values [E]ven, [O]dd, [N]one.
set(s1, "stopbits", 1)    # Changes stop bits (config becomes 5-E-2), possible
                          # values 1, 2.

set(s1, "dataterminalready", "off")  # Enables DTR line
set(s1, "requesttosend", "off")      # Enables RTS line
                                    # possible values "on", "off".
%Send over bluetooth or serial
%serialPort = '\\\\.\\COM5';
%serialObject = serial(serialPort);
%configure serial connection
%serialObject.BaudRate = 115200; %(Default)
%serialObject.BaudRate = 115200;
%serialObject.FlowControl = 'software';

%Initiate serial connection
%fopen(serialObject);

% This gets called on cleanup to ensure the stream gets closed
finishup = onCleanup(@() myCleanupFun(s1));

% Instantiate variables
count = 1;
row = 1;
column=1;
imHeight = 240
imWidth = 320
im = zeros (imHeight, imWidth);
state = 0;

  while (1)
    % send an S to get started
    fprintf("START...\n");
    srl_write(s1, 'S');
    # Blocking read call, returns uint8 array of exactly 1 bytes read
    %
    for row=1:imHeight
      fprintf ("Reading line=%d of %d\n",row, imHeight);
      for column=1:imWidth
      %ne

         val = srl_read(s1, 1);
         %val
         im(row, column) = val;
      %
      endfor
    endfor
    fprintf ("DONE\n");
    f = imshow(im, [0,255]);
    drawnow;

  end % while(1)

% Clean up the serial object
fclose(s1);

clear s1;

end %plot_cams

%*****************************************************************************************************************
%*****************************************************************************************************************

function myCleanupFun(serialObject)
% Clean up the serial object
fclose(s1);

clear s1;
delete(instrfindall);
end
